#include "c-wire.sh"

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
fichier_entree="$1"
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
if [[ ! -f "$fichier_entree" ]]; then
    echo "Erreur : Fichier d'entrée introuvable."
    exit 1
fi

# Création des dossiers nécessaires
mkdir -p tmp graphs

# Compilation du programme C
if [[ ! -f ./codeC/principal ]]; then
    echo "Compilation du programme C..."
    make -C codeC
    if [[ $? -ne 0 ]]; then
        echo "Erreur : Échec de la compilation du programme C."
        exit 1
    fi
fi

# Filtrage des données
fichier_filtre="tmp/donnees_filtrees.csv"
awk -F';' -v station="$type_station" -v consommateur="$type_consommateur" -v centrale="$id_centrale" '
    BEGIN {
        OFS = ";"
    }
    {
        if (station == "hvb" && $2 != "-" && consommateur == "comp") {
            print $1, $2, "-", "-", $5, "-", $7, $8
        }
        else if (station == "hva" && $3 != "-" && consommateur == "comp") {
            print $1, "-", $3, "-", $5, "-", $7, $8
        }
        else if (station == "lv" && $4 != "-" && consommateur != "") {
            print $1, "-", "-", $4, "-", (consommateur == "comp" ? $5 : $6), $7, $8
        }
    }
' "$fichier_entree" > "$fichier_filtre"

if [[ ! -s "$fichier_filtre" ]]; then
    echo "Erreur : Aucun résultat correspondant aux critères."
    exit 1
fi

# Exécution du programme C
fichier_sortie="tmp/resultats.csv"
./codeC/principal "$fichier_filtre" "$fichier_sortie"
if [[ $? -ne 0 ]]; then
    echo "Erreur : Échec du traitement par le programme C."
    exit 1
fi

# Tri des résultats
fichier_trie="tmp/resultats_tries.csv"
sort -t';' -k7 -n "$fichier_sortie" > "$fichier_trie"

# Gestion des postes LV pour lv all
if [[ "$type_station" == "lv" && "$type_consommateur" == "all" ]]; then
    fichier_top10="tmp/lv_all_minmax.csv"
    head -n 10 "$fichier_trie" > "$fichier_top10"
    tail -n 10 "$fichier_trie" >> "$fichier_top10"

    # Bonus : Création du graphique
    gnuplot -e "
        set terminal png size 800,600;
        set output 'graphs/lv_all_minmax.png';
        set style data histogram;
        set style fill solid;
        set boxwidth 0.9;
        set xtics rotate;
        plot '$fichier_top10' using 2:xtic(1) title 'Consommation (kWh)'"
fi

# Fin
echo "Traitement terminé. Résultats disponibles dans $fichier_trie."
exit 0

