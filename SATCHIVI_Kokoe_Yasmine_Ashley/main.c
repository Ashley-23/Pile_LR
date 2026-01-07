/* Author : SATCHIVI Kokoe Yasmine Ashley, 2025 */

#include <stdio.h>
#include <stdlib.h>

#include "LRGrammar.h"
#include "read_file.h"

#include "pile.h" 
#include "aux.h"
#include "arbre.h"
#include "latex.h"

#define EPSILONE '\0'

char consignes[] =
  " Un fichier \"arbre_analyse.tex\" a ete cree\n"
  " Pour voir le contenu du fichier, allez sur le site : https://www.overleaf.com/ \n"
  " \t - Appuyez sur new project puis sur blank project pour créer un nouveau projet vide \n "
  " \t - Copiez-y le contenu du fichier « arbre_analyse.tex » puis compilez.\n";



int main(int argc, char** argv) {
    
    int i = 0; 
    int statut = 0; 

    /* 
        Récupération des arguments
        1 - fichier contenant la grammaire et la table
        2 - récupération du texte à analyser 
        3 - récupération du mot sous forme de tableau de caractères 
    */

    char * fichier = NULL;
    char *texte_saisi = NULL; 
    if (argc > 1 ){ fichier = argv[1]; }    // 1
    if (argc > 2 ){ texte_saisi = argv[2]; }    // 2

    grammar grammaire;
    table table;
    file_read lecture_complete = read_file(fichier); 
    grammaire = lecture_complete.G;
    table = lecture_complete.t;

    // Création du fichier en latex et insertion de l'en tête
    latex_inserer_en_tete(texte_saisi);
  
    /* 3 */ 
    int longueur_texte = strlen(texte_saisi);
    char* tableau_texte = (char*)malloc((longueur_texte) * sizeof(char));
    if (tableau_texte == NULL) {
        printf("Erreur d'allocation de mémoire.\n");
    }
    char_to_table(texte_saisi, tableau_texte);
    

    /* 
        CREATION DE LA PILE LR
        1 - etat de depart
        2 - caractère lu
        3 - etat d'arrivé après avoir lu le caractère "w"
        4 - afficher l'en-tête de la table d'affichage   
        5 - création de la pile d'arbre  
        6 - on parcourt le mot saisi pour faire les décalages et reductions  
    */

    Pile *pile0 = creerPile();
    preparer_pile(pile0);
    int etat_q = pile0->tete->q; // 1 
    signed char w ; // 2 
    int etat_q_prime = 0; // 3 
    affichage_flot_pile_action(longueur_texte, texte_saisi); // 4 

    PileArbre *pilearbre = creerPileArbre(); // 5

    // Déclaration du tableau d'analyse de la pile LR en latex
    latex_debut_declaration_tableau();

    /* 6 */  
    for( i=0; i<=longueur_texte; i++){

        /*
            1 - caractère courant
            2 - symbole $ (fin de chaîne '\0')
            3 - On récupère l'action lié à la lecture du caractère "w" dans l'état q (etat_q) 
            4 - ON EST DANS LE CAS D'UN DÉCALAGE 
            5 - on récupère l'état d'arrivée 
            6 - On empile l'état et le caractère lu
            7 - Le nouvel état dans lequel on arrive
        */

        if(i < longueur_texte){
            w = texte_saisi[i]; // 1
        } else {
            w = 0; // 2
        }

        signed char action = table.trans[256*etat_q + w]; // 3 

        if (action > 0) { // 4 

            etat_q_prime = action;   // 5 
            Empiler(pile0, w, etat_q_prime);    //  6 
            etat_q = etat_q_prime; // 7 
           
            NoeudArbre *feuille = creerNoeudArbre(w);
            EmpilerPileArbre(pilearbre, feuille);

            affichage_ligne_decalage(action, i, longueur_texte, texte_saisi, pile0);

            // ajout de la ligne de décalage dans le fichier latex
            latex_inserer_decalage(action, i, longueur_texte, texte_saisi, pile0);

        }else if(action < 0 && action != -127){ // ON FAIT UNE REDUCTION

            /*
                1- on recupère le numéro de la règle à réduire 
                2- Récupération de la règle à reduire (-1 car c'est un tableau de règles commençant par l'indice 0)
                3 - Nombre de caractères de la règle 
                ex : E -> (#E) a 3 caractères à dépiler dans la partie droite
                4 - si le caractere dans le noeud de tete est le n-ieme caractere de la regle, on dépile le caractère 
                (N-1) car le tableau commence par l'indice 0 et se termine à N-1
                5 - Récupération de delta(q,S) avec :
                    * q l'état au sommet de la pile  
                    * S le caractère de l'axiome de la règle qu'on a réduit  
                    * On fait (-regle.lhs) car -regle.lhs est un non terminal donc il est encodé en négatif
                6 - On empile S et delta(q,S)
                7 - Le nouvel état dans lequel on arrive
                8 - On n'a pas encore lu le caractère qui nous a fait faire une réduction donc on reste sur le carcrère courant 

            */

            int numero_regle = -action;                         // 1    
            rule regle = grammaire.rules[numero_regle-1];       // 2    
            int N = nb_char_rhs(regle);                         // 3    
            int j = 0;

            NoeudArbre ** noeuds = NULL;
            if(N>0){
                noeuds = malloc( (N) * sizeof(NoeudArbre*));
                if (noeuds == NULL) {
                    fprintf(stderr, "Erreur d'allocation mémoire\n");
                    exit(EXIT_FAILURE);
                }
            }

            for(j=N-1; j>=0; j--){

                noeuds[j] = pilearbre->tete->noeud;

                if((pile0->tete->w >= 65 ) && ( pile0->tete->w <= 91 )){// NON TERMINAL
                    w = 256 - w; // ON LE MET A -1                
                } else if( pile0->tete->w == regle.rhs[j]){  // 4 // TERMINAL 
                    // ne rien faire
                }
                else{
                    statut = 1;
                    break;
                }
                DepilerPileArbre(pilearbre);
                Depiler(pile0);
            }

            etat_q = (int) pile0->tete->q;  
            w = regle.lhs; // Non terminal réduit 

            NoeudArbre *parent = creerNoeudArbre(w);

            if(N>0){
                ajouterFils(parent, noeuds[0]);

                for(j=0; j< (N-1) ; j++ ){
                    ajouterFrere(noeuds[j], noeuds[j+1]);
                }
                free(noeuds); 
            }

            EmpilerPileArbre(pilearbre, parent);
            
            signed char delta_q_s = table.trans[256*etat_q + (256 - w) ]; //5

            Empiler(pile0, regle.lhs, delta_q_s ); // 6        
            etat_q = delta_q_s; // 7
            i --; // 8

            affichage_ligne_reduction(action, i, longueur_texte, texte_saisi, pile0);

            // ajout de la ligne de réduction dans le fichier latex
            latex_inserer_reduction(action, i, longueur_texte, texte_saisi, pile0);

        }else if(action == -127){ // ON EST DANS LE CAS D'UNE ACCEPTATION         
            printf(" \n %-31s [ ACCEPT ] \n", "");
        }else{ // AUCUNE ACTION N'HESISTE POUR CE CAS
            statut = 2; 
            break;
        }
        printf("\n");
    }

    // fin de la déclaration du tableau de pile et flot en latex
    latex_fin_declaration_tableau();

    if(statut == 1){
        printf("\n %-31s  [ REJECT] \n IMPOSSIBLE DE REDUIRE", "" );
        printf("\n");
        latex_nettoyer_fichier();
        return 0;
    }else if(statut == 2){
        printf("\n %-31s [ REJECT] \n AUCUNE TRANSITION N'EXISTE SUR CE CARACTERE ", "" );
        printf("\n");
        latex_nettoyer_fichier();
        return 0;
    }

    printf("\n");
    afficher_Arbre(pilearbre->tete->noeud); 
    printf("\n\n");

    latex_afficher_arbre(pilearbre->tete->noeud);

    fprintf(stderr, "%s", consignes);

    printf("\n");


    LibererPileArbre(pilearbre);
    LibererPile(pile0);
    return 0;
}
