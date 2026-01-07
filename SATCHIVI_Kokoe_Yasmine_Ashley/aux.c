/* Author : SATCHIVI Kokoe Yasmine Ashley, 2025 */
 
/*
    Contient toutes les fonctions auxiliaires dont on aura besoin dans le projet
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "aux.h"

#define TAILLE_BUFFER 256

void char_to_table (const char* input, char* tab) {
    if (input == NULL || tab == NULL) {
        printf("Erreur : L'entrée ou le tableau est NULL.\n");
        return;
    }
    // Copier la chaîne d'entrée dans le tableau
    int i;
    for (i = 0; input[i] != '\0'; i++) {
        tab[i] = input[i];
    }
}

int nb_char_rhs(rule regle){
    int j=0;
    while(regle.rhs[j]!='\0'){
      j++;
    }
    return j;
}

char* affichage_flot(int i, int longueur_texte, char * texte_saisi){
    int k = 0; // parcours la chaine de caractère qu'on veut écrire
    int j = 0; // parcours le mot
    static char flot[TAILLE_BUFFER];
    for(j=i; j<longueur_texte; j++){
        if (k < TAILLE_BUFFER-1){
            flot[k] = texte_saisi[j+1];
            k++;
        } 
    }
    flot[k] = '\0';
    return flot;
}

void affichage_flot_pile_action(int longueur_texte, char * texte){
    printf("%-4s   %30s | %-31s\n", " ", "Flot", "Pile");
    printf("      ----------------------------------------------------------------\n");  
    printf("%-4s \t", " ");
    char * mon_flot = affichage_flot( -1, longueur_texte, texte); // récupération du flot 
    printf("%30s", mon_flot); // affichage du flot 
    printf("|\t");
    printf("%-31s", "0"); // Au début on est dans l'état 0 dans la pile 
    printf("\n");
}

void affichage_ligne_decalage(signed char action, int i, int longueur_texte, char * texte_saisi, Pile *pile0){  
    printf("d%d \t", action);
    
    char * mon_flot = affichage_flot( i, longueur_texte, texte_saisi); // récupération du flot  
    printf("%30s", mon_flot); // affichage du flot
    printf("|\t");
    char * ma_pile = afficher_Pile(pile0); // récupération de la pile 
    printf("%-31s", ma_pile); // affichage de la pile  
}

void affichage_ligne_reduction (signed char action, int i, int longueur_texte, char * texte_saisi, Pile *pile0){
    //affichage de la réduction
    printf("r%d \t", (-action-1));
    char * mon_flot = affichage_flot( i, longueur_texte, texte_saisi); // récupération du flot  
    printf("%30s", mon_flot); // affichage du flot
    printf("|\t");
    char * ma_pile = afficher_Pile(pile0); // récupération de la pile     
    printf("%-31s", ma_pile); // affichage de la pile  
}
