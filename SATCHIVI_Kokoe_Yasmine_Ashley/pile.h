/* Author : SATCHIVI Kokoe Yasmine Ashley, 2025 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef PILE_H
#define PILE_H
 
/*
    Un noeurd correspond à une configuration (q,w)
    q : l'état dans lequel on se trouveaprès avoir lu w
    w : le caractère lu
*/
typedef struct NoeudPile NoeudPile;
struct NoeudPile{
    signed char w; 
    char q; 
    struct NoeudPile *suivant;
};

typedef struct Pile Pile;
struct Pile{
    NoeudPile *tete;
};

/* Crée une pile vide*/
Pile* creerPile();

/* Vérifie si la pile est vide */
int estVide(Pile* pile);

/* Permets de commencer l'analyse dans l'état 0*/
void preparer_pile(Pile* pile);

/* Permet d'afficher la pile*/
char * afficher_Pile(Pile *p);

/* Ajoute une configuration (noeud) dans la pile (caractere lue et etat dans lequdel on se trouve)*/
void Empiler(Pile* p, char w, char q);

/* Enlever un noeud dans la pile */
void Depiler(Pile* p);

/* Libère la  mémoire de la pile*/
void LibererPile(Pile *p);

#endif /*PILE_H*/
