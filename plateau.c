//
// Created by lucas on 16/05/2023.
//

#include "plateau.h"

int asquisitionNbrJoueur(){
    int nbrJoueur;
    printf("Combien de joueur? \n");
    scanf("%d", &nbrJoueur);
    while (nbrJoueur < 0 || nbrJoueur > 2){
        printf("Vous ne pouvez jouer qu'a 2 joueurs maximum, recommencez\n");
        scanf("%d", &nbrJoueur);
    }
    return nbrJoueur;
}

int acquisitionDimGrille(){
    int dimGrille;
    printf("quelle est la dimension de votre grille?\n");
    scanf("%d", &dimGrille);
    while (dimGrille < 6 || dimGrille > 12){
        printf("la taille de la grille doit etre comprise entre 6 et 12, recommencez\n");
        scanf("%d", &dimGrille);
    }
    return dimGrille;
}


void initGrille(int dimGrille, char plateau[12][12]){
    for (int i = 0; i < dimGrille; ++i) {
        for (int j = 0; j < dimGrille; ++j) {
            plateau[i][j]='.';
        }
    }
}

void affichageGrille(int dimGrille, char plateau[][dimGrille]){
    for (int i = 0; i < dimGrille; ++i) {
        for (int j = 0; j < dimGrille; ++j) {
            printf("|%c", plateau[i][j]);
        }
        printf("|\n");
    }
}



int acquisitionTemps() {
    int temps;
    printf("Combien de temps dure la partie?\n");
    scanf("%d", &temps);
    while (temps < 60 || temps > 240) {
        printf("Le temps de la partie doit etre compris entre 60 et 240 secondes, recommencez\n");
        scanf("%d", &temps);
    }
    return temps;
}


int annoncePartie(int nbrJoueur, int dimGrille, int temps){
    if( nbrJoueur==1){
        printf("/// votre partie va se jouer seul sur une grille de %dX%d, vous avez %d secondes pour finir, bonne chance! ///\n", dimGrille, dimGrille, temps);
    }else{
        printf("/// votre partie va se jouer en versus sur une grille de %dX%d, vous avez %d secondes chacun pour finir! ///\n", dimGrille,dimGrille, temps/2);
    }
    return 0;
}

//void placerMots(char plateau[12][12], int dimGrille){
//    char mot[dimGrille];
//    do {
//        printf("voulez-vous placer le mot verticalement (v) ou horizontalement (h)?");
//        fgets()
//    }
//}
