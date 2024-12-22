#!/bin/bash
# Timer global
lancement_script_temps=$(date +%s)  # Capture the start time in seconds

# Vérification du nombre d'arguments
if [ $# -ne 3 ]; then # Si le nombre d'arguments est incorrect
    echo "Usage : $0 <chemin> <station> <consommation>"
    exit 1
fi

chemin=$1 # Premier argument
station=$2 # Deuxième argument
consommation=$3 # Troisième argument

if [ ! -f "$cwire" ]; then # Si le chemin est incorrect
    echo "Erreur : $chemin est incorrect"
    exit 2
fi

if [[ "$station" != "hvb" && "$station" != "hva" && "$station" != "lv" ]]; then # Si le type de station est incorrect
    echo "Erreur : Le type de station $station est incorrect"
    exit 3
fi

if [[ "$consommation" != "comp" && "$consommation" != "indiv" && "$consommation" != "all" ]]; then # Si le type de consommation est incorrect
    echo "Erreur : Le type de consommation $consommation est incorrect"
    exit 4

fi

# Vérification de l'existence du programme à exécuter

exec="codeC/c_wire"

if [[ ! -f "$exec" ]]; then # Si le programme n'existe pas
    echo "Erreur : $exec n'existe pas. Compilation..."
    cd codeC
    make clean
    make all
    cd ..

    if [[ ! -f "$exec" ]]; then
        echo "Erreur : $exec n'a pas pu être compilé."
        exit 5
    fi
fi

# Vérification et création du répertoire temporaire

tmp="tmp"

if [[ ! -d "$tmp" ]]; then # Si le répertoire n'existe pas
    echo "Erreur : $tmp n'existe pas. Création du répertoire."
    mkdir "$tmp"
else
    rm -rf "$tmp/*" # Si le répertoire existe, nettoyage des fichiers temporaires
fi

# Traitement des différents cas

if [[ "$station" == "hvb" && "$consommation" == "comp" ]]; then
    variable_case="hvb_comp"
    temp="$tmp/temp_${variable_case}.csv"
    fichier="tests/${variable_case}.csv"
        # Extraction des colonnes pertinentes et remplacement des tirets par 2
       if awk '($2 != "-" && $5 != "-") || ($2 != "-" && $7 != "-")' input/c-wire_v00.dat > /dev/null; then
        awk '{print $2 ";" $7 ";" $8}' c-wire_v00.dat > "$temp"
        sed -i 's/-/2/g' "$temp"  # Remplacer les tirets par 2
        echo "Données extraites pour hvb-comp"
        fi
    # Lancer ton programme ici

    ./codeC/c_wire "$temp" "$fichier" > /dev/null
    echo "Programme exécuté avec succès."
    # Trier et sauvegarder dans le fichier final
    sort -t';' -k1,1 -k2,2 "$temp" > "$fichier"
    echo "Fichier final sauvegardé dans : $fichier"

elif [[ "$station" == "hva" && "$consommation" == "comp" ]]; then
    variable_case="hva_comp"
    temp="$tmp/temp_${variable_case}.csv"
    fichier="tests/${variable_case}.csv"

    if [[ $3 != "-" && $5 != "-" ]]; then
        awk -F";" '{if ($3 != "-" && $5 != "-") print $3 ";" $7 ";" $8}' "$chemin" > "$temp"
        sed -i 's/-/2/g' "$temp"  # Remplacer les tirets par 2
        echo "Données extraites pour hva-comp"
    else
    echo "Données non valides pour hva-comp"
    fi

    # Lancer ton programme ici
    ./codeC/c_wire "$temp" "$fichier" > /dev/null
    echo "Programme exécuté avec succès."
    sort -t';' -k1,1 -k2,2 "$temp" > "$fichier"
    echo "Fichier final sauvegardé dans : $fichier"

elif [[ "$station" == "lv" && "$consommation" == "comp" ]]; then
    variable_case="lv_comp"
    temp="$tmp/temp_${variable_case}.csv"
    fichier="tests/${variable_case}.csv"

    if [[ $4 != "-" && $5 != "-" ]]; then
        awk -F";" '{if ($4 != "-" && $5 != "-") print $4 ";" $7 ";" $8}' "$chemin" > "$temp"
        sed -i 's/-/2/g' "$temp"  # Remplacer les tirets par 
        echo "Données extraites pour lv-comp"
    else
        echo "Données non valides pour lv-comp"
    fi

    # Lancer ton programme ici
    ./codeC/c_wire "$temp" "$fichier" > /dev/null
    echo "Programme exécuté avec succès."
    sort -t';' -k1,1 -k2,2 "$temp" > "$fichier"
    echo "Fichier final sauvegardé dans : $fichier"

elif [[ "$station" == "lv" && "$consommation" == "all" ]]; then
    variable_case="lv_all"
    temp="$tmp/temp_${variable_case}.csv"
    fichier="tests/${variable_case}.csv"

    if [[ $4 != "-" ]]; then
        awk -F";" '{if ($4 != "-" && ($5 != "-" || $6 != "-" || $7 != "-")) print $4 ";" $7 ";" $8}' "$chemin" > "$temp"
        sed -i 's/-/2/g' "$temp"  # Remplacer les tirets par 2
        echo "Données extraites pour lv-all"
    else
        echo "Données non valides pour lv-all"
    fi

    # Lancer ton programme ici
    ./codeC/w_wire "$temp" "$fichier" > /dev/null
    echo "Programme exécuté avec succès."
    sort -t';' -k1,1 -k2,2 "$temp" > "$fichier"
    echo "Fichier final sauvegardé dans : $fichier"

# Ajoute ici d'autres conditions pour d'autres cas si nécessaire

# Fin du chronomètre global

fin_script_temps=$(date +%s)  # Capture l'heure de fin en secondes
temps_total=$((fin_script_temps - lancement_script_temps))  # Temps total en secondes
echo "Temps d'exécution total du script : $temps_total secondes"
