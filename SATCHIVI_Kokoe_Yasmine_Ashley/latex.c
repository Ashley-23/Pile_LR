/* Author : SATCHIVI Kokoe Yasmine Ashley, 2025 */

#include "latex.h"


void latex_inserer_en_tete(const char *mot){
    
    FILE *f = fopen("arbre_analyse.tex", "w");
    if (!f) {
        fprintf(stderr, "Erreur: impossible de créer arbre_analyse.tex\n");
        return;
    }

    // Elements de l'en-tête 

    fprintf(f, "\\documentclass{article}\n");
    fprintf(f, "\\usepackage{forest}\n");
    fprintf(f, "\\usepackage{xcolor}\n");
    fprintf(f, "\\usepackage{geometry}\n");
    fprintf(f, "\\usepackage{longtable}\n");

    fprintf(f, "\\title{Arbre d'analyse syntaxique}\n");
    fprintf(f, "\\author{SATCHIVI Kokoe Yasmine Ashley}\n");
    fprintf(f, "\\date{\\today}\n\n");

    fprintf(f, "\\begin{document}\n");
    fprintf(f, "\\maketitle\n\n");


    // Affichage du mot analysé
    fprintf(f, "\\section{Mot analysé}\n");
    fprintf(f, "Le mot analysé est : \\texttt{%s}\n\n", mot);

    fclose(f);
}

void latex_debut_declaration_tableau(){
    FILE *f = fopen("arbre_analyse.tex", "a");
    if (!f) {
        fprintf(stderr, "Erreur: impossible d’ouvrir arbre_analyse.tex\n");
        return;
    }

    // Affichage du début du tableau
    fprintf(f, "\\section{Analyse LR}\n");
    fprintf(f, "\\begin{longtable}{|c|r|l|}\n");
    fprintf(f, "\\hline \n");
    fprintf(f, " &Flot&Pile \\endhead \n");
    fprintf(f, "\\hline \n");

    fclose(f);
}

void latex_inserer_decalage(signed char action, int i, int longueur_texte, char * texte_saisi, Pile *pile0 ){
    FILE *f = fopen("arbre_analyse.tex", "a");
    if (!f) {
        fprintf(stderr, "Erreur: impossible d’ouvrir arbre_analyse.tex\n");
        return;
    }

    char * flot = affichage_flot( i, longueur_texte, texte_saisi); // récupération du flot  
    char * pile = afficher_Pile(pile0); // récupération de la pile 

    fprintf(f, "d%d & %s & %s\\\\ \n", action, flot, pile );
    
    fclose(f);
}

void latex_inserer_reduction( signed char action, int i, int longueur_texte, char * texte_saisi, Pile *pile0 ){
    FILE *f = fopen("arbre_analyse.tex", "a");
    if (!f) {
        fprintf(stderr, "Erreur: impossible d’ouvrir arbre_analyse.tex\n");
        return;
    }
    
    char * flot = affichage_flot( i, longueur_texte, texte_saisi); // récupération du flot  
    char * pile = afficher_Pile(pile0); // récupération de la pile 
    
    fprintf(f, "r%d & %s & %s\\\\ \n", (-action-1), flot, pile );
    
    fclose(f);
}

void latex_fin_declaration_tableau(){
    FILE *f = fopen("arbre_analyse.tex", "a");
    if (!f) {
        fprintf(stderr, "Erreur: impossible d’ouvrir arbre_analyse.tex\n");
        return;
    }

    // fini la déclaration du tableau
    fprintf(f, "\\hline \n");
    fprintf(f, "\\end{longtable} \n\n");
    
    fclose(f);
}


void afficher_arbre_latex_recursif(NoeudArbre *racine, FILE *f) {
    if (!racine) return;
    
    fprintf(f, "[{");
    if (racine->valeur == '\0') {
        fprintf(f, " ");
    } else if (racine->valeur >= 65 && racine->valeur <= 90) {
        fprintf(f, "\\textcolor{blue}{\\textbf{%c}}", racine->valeur); // Non-terminal
    } else {
        fprintf(f, "\\textcolor{red}{%c}", racine->valeur); // Terminal
    }
    fprintf(f, "}");
    
    if (racine->fils) {
        fprintf(f, "\n");
        NoeudArbre *racine_sous_arbre = racine->fils;
        while (racine_sous_arbre) {
            afficher_arbre_latex_recursif(racine_sous_arbre, f);
            racine_sous_arbre = racine_sous_arbre->frere;
        }
    }
    
    fprintf(f, "]\n");
}


void latex_afficher_arbre(NoeudArbre *racine){

    FILE *f = fopen("arbre_analyse.tex", "a");
    if (!f) {
        fprintf(stderr, "Erreur: impossible d’ouvrir arbre_analyse.tex\n");
        return;
    }
    
    fprintf(f, "\\section{Arbre d'analyse}\n\n");
    fprintf(f, "\\begin{center}\n");
    fprintf(f, "\\begin{forest}\n");
    fprintf(f, "  for tree={circle, draw, minimum size=3em, s sep=10mm, l sep=15mm}\n");
    

    afficher_arbre_latex_recursif(racine, f);
    
    fprintf(f, "\\end{forest}\n");
    fprintf(f, "\\end{center}\n\n");
    
    fprintf(f, "\\end{document}\n");
    
    fclose(f);

}

void latex_nettoyer_fichier() {
    FILE *f = fopen("arbre_analyse.tex", "w");
    if (!f) {
        fprintf(stderr, "Erreur: impossible de nettoyer le fichier arbre_analyse.tex\n");
        return;
    }
    fclose(f); 
}
