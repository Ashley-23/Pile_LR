/* Author : SATCHIVI Kokoe Yasmine Ashley, 2025 */

#include "arbre.h"

NoeudArbre* creerNoeudArbre(char v) {
    NoeudArbre* n = (NoeudArbre*)malloc(sizeof(NoeudArbre));
    if (!n) exit(EXIT_FAILURE);
    n->valeur = v;
    n->fils = NULL;
    n->frere = NULL;
    return n;
}
 
void ajouterFils(NoeudArbre* parent, NoeudArbre* fils){
    if (parent != NULL && fils != NULL){
        parent->fils = fils;
    }
}

void supprimerFils( NoeudArbre* parent){
    parent->fils = NULL;
}

void ajouterFrere( NoeudArbre* aine, NoeudArbre* frere){
    if (aine != NULL && frere != NULL){
        aine->frere = frere;
    }
}

void supprimerFrere( NoeudArbre* aine){
    aine->frere = NULL;
}



/* Gestion de la pile liée à l'arbre */



PileArbre* creerPileArbre() {
    PileArbre* pile = (PileArbre*)malloc(sizeof(PileArbre));
    if (pile != NULL) {
        pile->tete = NULL;
    }
    return pile;
}

int estVidePileArbre(PileArbre* pile) {
    if (pile == NULL || pile->tete == NULL) {
        return 1; // vide 
    } else {
        return 0; // non vide 
    }
}

void EmpilerPileArbre(PileArbre* p, NoeudArbre* np) {
    if (p == NULL) {
        return;
    }
    NoeudPileDelArbre* n = (NoeudPileDelArbre*)malloc(sizeof(NoeudPileDelArbre));
    if (n != NULL) {   
        n->noeud = np;   // le caractère lu 
        n->suivant = p->tete;// Relier le nouveau nœud à l’ancienne pile
        p->tete = n;// On empile à la tête (Mettre à jour la tête de la pile)
    }
}

void DepilerPileArbre(PileArbre* p) {
    if (p == NULL || p->tete == NULL) {
        fprintf(stderr, "Erreur: Tentative de dépiler une pile vide.\n");
        exit(EXIT_FAILURE);
    }

    NoeudPileDelArbre* n = p->tete;
    p->tete = n->suivant;
    free(n);
}

void LibererPileArbre(PileArbre *p) {
    if (p == NULL) {
        return;
    }

    NoeudPileDelArbre* n = p->tete;
    while (n != NULL) {
        NoeudPileDelArbre* temp = n;
        n = n->suivant;
        free(temp);
    }
    free(p);
}

void afficher_Arbre(NoeudArbre *racine) {
    if (!racine) return;

    printf("%c", racine->valeur);

    if (racine->fils) {
        printf("(");
        NoeudArbre *racine_sous_arbre = racine->fils;
        while (racine_sous_arbre) {
            afficher_Arbre(racine_sous_arbre);
            racine_sous_arbre = racine_sous_arbre->frere;
        }
        printf(")");
    } else {
        printf("()"); // on est dans le cas d'une feuille mais on affiche quand même ()         
    }
}

