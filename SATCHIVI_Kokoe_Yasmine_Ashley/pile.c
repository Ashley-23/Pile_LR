/* Author : SATCHIVI Kokoe Yasmine Ashley, 2025 */
 
#include "pile.h"

#define EPSILONE '\0'
#define TAILLE_BUFFER 256

Pile* creerPile() {
    Pile* pile = (Pile*)malloc(sizeof(Pile));
    if (pile != NULL) {
        pile->tete = NULL;
    }
    return pile;
}

int estVide(Pile* pile) {
    if (pile == NULL || pile->tete == NULL) {
        return 1; // vide 
    } else {
        return 0; // non vide 
    }
}

void preparer_pile(Pile* pile){
    if(estVide(pile) == 1){
    // on crée une configuration
    NoeudPile *n = (NoeudPile*)malloc(sizeof(NoeudPile));
    n->q = 0;           // On commence par l'état 0
    n->w = EPSILONE;    // On ne lit rien avant d'arriver à l'état 
    n->suivant = NULL;
    // On empile à la tête 
    pile->tete = n;
    }
}

char * afficher_Pile(Pile *p){
    static char flot[TAILLE_BUFFER];
    int i = 0;
    int j = 0;

    if (estVide(p) == 1) {
        snprintf(flot, TAILLE_BUFFER, "La pile est vide");
        return flot;
    }

    int nb_el = 0;// On compte le nombre d'éléments de la pile 
    NoeudPile *n = p->tete;
    while (n != NULL) {
        nb_el++;
        n = n->suivant;
    }

    // On cée un tableau temporaire pour inverser l'ordre ( car la pile contient les éléments dans l'ordre inverse )     
    NoeudPile **tableau = malloc(nb_el * sizeof(NoeudPile*));
    n = p->tete;
    for (i = 0; i < nb_el; i++) {
        tableau[i] = n;
        n = n->suivant;
    }

    // On affiche dans le bon ordre (de la 0 vers le sommet)
    for (i = (nb_el-1); ((i >= 0) && (j < TAILLE_BUFFER - 1)) ; i--) {
        // Afficher w
        if (tableau[i]->w != '\0' && j < TAILLE_BUFFER - 1) {
            flot[j++] = tableau[i]->w;
        }
        // Afficher q
        j += snprintf(flot + j, TAILLE_BUFFER - j, "%d", tableau[i]->q);
    }
    
    flot[j] = '\0';
    free(tableau);
    return flot;
}


void Empiler(Pile* p, char w, char q) { 
    if (p == NULL) {
        return;
    }

    NoeudPile *n = (NoeudPile*)malloc(sizeof(NoeudPile)); // on crée une configuration

    if (n != NULL) {   
        n->w = w;   // le caractère lu 
        n->q = q;   // l'état dans lequel on se trouve après avoir lu w
        n->suivant = p->tete; // Relier le nouveau nœud à l’ancienne pile
        p->tete = n; // On empile à la tête (Mettre à jour la tête de la pile)
    }
}

void Depiler(Pile* p) {
    if (p == NULL || p->tete == NULL) {
        fprintf(stderr, "Erreur: Tentative de dépiler une pile vide.\n");
        exit(EXIT_FAILURE);
    }

    NoeudPile* n = p->tete;
    p->tete = n->suivant;
    free(n);
}

void LibererPile(Pile *p) {
    if (p == NULL) {
        return;
    }

    NoeudPile* n = p->tete;
    while (n != NULL) {
        NoeudPile* temp = n;
        n = n->suivant;
        free(temp);
    }
    free(p);
}
