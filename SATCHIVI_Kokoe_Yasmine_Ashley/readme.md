
<!-- Author : SATCHIVI Kokoe Yasmine Ashley, 2025  -->

Pour garantir la bonne exécution de l'analyseur LR, il faudra respecter les étapes suivantes: 


# Problème des fins de ligne selon les systèmes 

Pour que le fichier " read_file.c " puisse bien décomposer les fichiers test, il faudra utiliser ces commandes pour gérer le caractère de fin de ligne selon le système d'exploitation.

    1. Linux 
        sed -i 's/\r$//' test test2 test3 test4

    2. Windows 
        sed -i 's/\r$//' test test2 test3 test4

    3. MacOS
        sed -i '' 's/\r$//' test test2 test3 test4


# Exécution du fichier 

Pour exécuter le fichier, il faudra saisir les commande : 

* make clean 
* make 
* ./LRanalyzer ../nom_du_fichier mot_a_executer