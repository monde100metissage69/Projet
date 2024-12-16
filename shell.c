#include "game.h"

#!/bin/bash

# Vérification des paramètres
if [[ "$1" == "-h" || $# -lt 3 ]]; then
    echo "Usage : $0 <chemin_fichier> <type_station> <type_consommateur> [id_centrale]"
    echo "  <chemin_fichier> : Chemin vers le fichier CSV d'entrée."
    echo "  <type_station> : hvb | hva | lv"
    echo "  <type_consommateur> : comp | indiv | all"
    echo "  [id_centrale] : (optionnel) Identifiant de la centrale."
    echo "  Options interdites : hvb indiv, hvb all, hva indiv, hva all."
    exit 1
fi

# Paramètres
input_file="$1"
type_station="$2"
type_consommateur="$3"
id_centrale="$4"

# Vérification des options interdites
if [[ "$type_station" == "hvb" && "$type_consommateur" != "comp" ]] ||
   [[ "$type_station" == "hva" && "$type_consommateur" != "comp" ]]; then
    echo "Erreur : Les options hvb indiv, hvb all, hva indiv, hva all sont interdites."
    exit 1
fi

# Vérification de l'existence du fichier
if [[ ! -f "$input_file" ]]; then
    echo "Erreur : Fichier d'entrée introuvable."
    exit 1
fi

# Création des dossiers nécessaires
mkdir -p tmp graphs

# Compilation du programme C
if [[ ! -f ./codeC/main ]]; then
    echo "Compilation du programme C..."
    make -C codeC
    if [[ $? -ne 0 ]]; then
        echo "Erreur : Échec de la compilation du programme C."
        exit 1
    fi
fi

# Filtrage des données
filtered_file="tmp/filtered_data.csv"
awk -F';' -v station="$type_station" -v consumer="$type_consommateur" -v central="$id_centrale" '
    BEGIN {
        OFS = ";"
    }
    {
        if (station == "hvb" && $2 != "-" && consumer == "comp") {
            print $1, $2, "-", "-", $5, "-", $7, $8
        }
        else if (station == "hva" && $3 != "-" && consumer == "comp") {
            print $1, "-", $3, "-", $5, "-", $7, $8
        }
        else if (station == "lv" && $4 != "-" && consumer != "") {
            print $1, "-", "-", $4, "-", (consumer == "comp" ? $5 : $6), $7, $8
        }
    }
' "$input_file" > "$filtered_file"

if [[ ! -s "$filtered_file" ]]; then
    echo "Erreur : Aucun résultat correspondant aux critères."
    exit 1
fi

# Exécution du programme C
output_file="tmp/results.csv"
./codeC/main "$filtered_file" "$output_file"
if [[ $? -ne 0 ]]; then
    echo "Erreur : Échec du traitement par le programme C."
    exit 1
fi

# Tri des résultats
sorted_file="tmp/sorted_results.csv"
sort -t';' -k7 -n "$output_file" > "$sorted_file"

# Gestion des postes LV pour lv all
if [[ "$type_station" == "lv" && "$type_consommateur" == "all" ]]; then
    top10_file="tmp/lv_all_minmax.csv"
    head -n 10 "$sorted_file" > "$top10_file"
    tail -n 10 "$sorted_file" >> "$top10_file"

    # Bonus : Création du graphique
    gnuplot -e "
        set terminal png size 800,600;
        set output 'graphs/lv_all_minmax.png';
        set style data histogram;
        set style fill solid;
        set boxwidth 0.9;
        set xtics rotate;
        plot '$top10_file' using 2:xtic(1) title 'Consommation (kWh)'"
fi

# Fin
echo "Traitement terminé. Résultats disponibles dans $sorted_file."
exit 0
