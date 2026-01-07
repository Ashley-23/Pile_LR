/* Author : SATCHIVI Kokoe Yasmine Ashley, 2025 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef ARBRE_H
#define ARBRE_H

 
// Structure du nœud 
typedef struct NoeudArbre {
    char valeur;                // Caractère lu  
    struct NoeudArbre* fils;    // Premier fils  
    struct NoeudArbre* frere;   // Frère suivant  
} NoeudArbre;

// on va affecter l'axiome à ce noeud arbre. axiome = caractère non terminal de la première règle 
typedef struct NoeudArbre* Arbre;

// Créer un noeud avec une valeur 
NoeudArbre* creerNoeudArbre(char v); 

// Permets d'ajouter un fils à un noeud 
void ajouterFils(NoeudArbre* parent, NoeudArbre* fils);

// Supprimer un fils 
void supprimerFils(NoeudArbre* parent);

// Permet d'ajouter un frère à un noeud 
void ajouterFrere( NoeudArbre* aine, NoeudArbre* frere);

// Supprimer un frère 
void supprimerFrere(NoeudArbre* aine);




/* Pile pour la gestion de l'arbre */ 

/* Structure du nœud de la pile d'arbre */
typedef struct NoeudPileDelArbre NoeudPileDelArbre;
struct NoeudPileDelArbre{
    struct NoeudArbre * noeud; // le noeud de l'arbre à empiler 
    struct NoeudPileDelArbre *suivant; // noeud dans la pile de l'arbre 
};

/* Pile de l'arbre */
typedef struct PileArbre PileArbre;
struct PileArbre{
    NoeudPileDelArbre *tete;
};

/* Crée une pile vide*/
PileArbre* creerPileArbre();

/* Vérifie si la pile de l'arbre est vide */
int estVidePileArbre(PileArbre* pile);

/* Ajouter une feuille dans la pile de l'arbre */
void EmpilerPileArbre(PileArbre* p, NoeudArbre* np);

/* Enlever un noeud dans la pile de l'arbre */
void DepilerPileArbre(PileArbre* p);

/* Libère la mémoire de la pile de l'arbre */ 
void LibererPileArbre(PileArbre *p);

/* Permet d'afficher l'arbre */
void afficher_Arbre(NoeudArbre *racine);

#endif /*ARBRE_H*/
