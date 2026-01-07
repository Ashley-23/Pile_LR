/* Author : SATCHIVI Kokoe Yasmine Ashley, 2025 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LRGrammar.h"
#include "read_file.h"
#include "pile.h"
#include "arbre.h"
#include "aux.h"

#ifndef LATEX_H
#define LATEX_H

/* Prépare l'en tete du fichier latex */
void latex_inserer_en_tete(const char *mot);

/* affiche le début de la déclaration d'un tableau en latex */
void latex_debut_declaration_tableau();

/* affiche une ligne de décalage  */ 
void latex_inserer_decalage(signed char action, int i, int longueur_texte, char * texte_saisi, Pile *pile0 );

/* affiche une ligne de réduction */ 
void latex_inserer_reduction( signed char action, int i, int longueur_texte, char * texte_saisi, Pile *pile0 );

/* affiche la fin de la déclaration d'un tableau en latex */
void latex_fin_declaration_tableau();

/* affiche l'arbre en latex */
void afficher_arbre_latex_recursif(NoeudArbre *racine, FILE *f);

/* affiche la déclaration d'un arbre en latex */
void latex_afficher_arbre(NoeudArbre *racine);

/* Vide le contenu du fichier */
void latex_nettoyer_fichier();

#endif /* LATEX_H */

