/* Author : SATCHIVI Kokoe Yasmine Ashley, 2025 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LRGrammar.h"
#include "read_file.h"
#include "pile.h"

#ifndef AUX_H
#define AUX_H

/* TRansforme une chaine de caractère en tableau de caractères */
void char_to_table (const char* input, char* tab);

/* Calcul le nombre de caractère dans la partie droite de la regle (ça facilite la réduction) */
int nb_char_rhs(rule regle); 

/* Affiche les caractères du flot au fur et à mesure */
char* affichage_flot(int i, int longueur_texte, char * texte_saisi);

/* Affiche l'en-tête du tableau de pile et de flot */
void affichage_flot_pile_action(int longueur_texte, char * texte);

/* Affiche une ligne de décalage (dX, flot, pile)*/
void affichage_ligne_decalage(signed char action, int i, int longueur_texte, char * texte_saisi, Pile *pile0);

/*Affiche une ligne de réduction (rX, flot, pile)*/
void affichage_ligne_reduction (signed char action, int i, int longueur_texte, char * texte_saisi, Pile *pile0);

#endif /* AUX_H */

