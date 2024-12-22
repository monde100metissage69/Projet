Le projet C-Wire a pour objectif d’analyser un réseau de distribution d’électricité en France en simulant des données issues de centrales électriques, de sous-stations HV (High Voltage) et LV (Low Voltage), ainsi que des consommateurs (particuliers et entreprises).

À partir d’un fichier CSV volumineux, nous avons conçu :
    Un script Shell pour filtrer les données, compiler le programme C et orchestrer les traitements.
    Un programme en C, utilisant un arbre AVL, pour calculer les consommations et évaluer les performances énergétiques des stations.

-Fonctionnalités principales:
    Filtrage des données selon le type de station (HV-B, HV-A, LV) et les catégories de clients (entreprises ou particuliers).
    Calcul de la consommation totale par station, comparaison avec les capacités et détection des surcharges ou sous-charges.
    Génération de fichiers de résultats structurés et triés, avec une possibilité de visualisation graphique (en option).

Pour lancer le code, il vous suffit d'ouvrir le terminal et d'écrire la commande suivante :
./c-wire.sh input/c-wire_v25.dat (la station) (compagnie ou particulier)
Les données trier seront ainsi stockés dans un dossier crée par le script shell.

-Équipe:
    ZERARGUI Abderrahmane
    BENYOUCEF Loqman
    HAIDAR Ilyas

Ce projet met en avant la collaboration, la gestion de données massives et l’optimisation algorithmique.
