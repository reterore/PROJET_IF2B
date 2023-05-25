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


void initGrille(char plateau[12][12]){
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            plateau[i][j]='_';
        }
    }
}

void affichageGrille(int dimGrille, char plateau[][dimGrille]){
    for (int i = 0; i < dimGrille; ++i) {
        for (int j = 0; j < dimGrille; ++j) {
            printf("| %c ", plateau[i][j]);
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

void placerMot(char plateau[12][12], int dimGrille, joueur joueur){
    char mot[dimGrille+1];
    char sens;
    int x, y;
    int test1 = 0, test2 = 0, test3 = 0; // variables pour les tests des mots
    //demander le sens du mot
    do {
        printf("Voulez-vous placer le mot verticalement (v) ou horizontalement (h)?\n");
        scanf(" %c", &sens);
        getchar();
    } while (sens != 'v' && sens != 'h');
    //afficher le sens du mot choisis
    if (sens == 'v') {
        printf("Vous allez placer votre mot verticalement.\n");
    } else {
        printf("Vous allez placer votre mot horizontalement.\n");
    }
    printf("quelles sont les coordonnee de la premiere lettres?\n");
    printf("coordonnee en x (ligne): x =");
    scanf("%d", &x);
    printf("coordonnee en y (ligne): y =");
    scanf("%d", &y);
    while((x<0  || x>dimGrille-1)||(y<0 || y>dimGrille-1)){
        printf("/// Mauvaise saisie! ///\n");
        printf("coordonnee en x comprise entre 0 et %d: x =", dimGrille-1);
        scanf("%d", &x);
        printf("coordonnee en y comprise entre 0 et %d: y =", dimGrille-1);
        scanf("%d", &y);
    }
    getchar();
    do {
        for (int i = 0; i < dimGrille; ++i) {
            mot[i] = ' ';
        }
        mot[dimGrille+1] = '\0';
        acquisitionMot(mot, dimGrille, joueur, plateau, sens, x, y);
        affichageMot(mot);
    } while (verifLettresMot(mot, joueur) == false || verifEmplacement(sens, x, y, mot, dimGrille) == false || mot[0] == '\n');
}


void acquisitionMot(char* mot, int dimGrille, joueur joueur, char* plateau, char sens, int x, int y) {
    int limite;
    affichageGrille(dimGrille, plateau);
    afficherMain(joueur);
    if(sens == 'v'){
        limite = y;
    }else{
        limite = x;
    }
    do {
        for (int i = 0; i < dimGrille; ++i) {
            mot[i] = ' ';
        }
        printf("\n/// Veuillez entrer un mot de %d lettres maximum :", dimGrille-limite);
        fgets(mot, dimGrille - limite + 2, stdin);
    } while(strlen(mot)>=dimGrille-limite+1 && mot[0] == '\n');
    mot[strcspn(mot, "\n")] = '\0'; // supprime le '\n' de l'entrée
    for (int i = 0; i < dimGrille; ++i) { // met le mot en majuscule
        mot[i] = toupper(mot[i]);
    }
}

void affichageMot(char* mot) { // affiche le mot
    int j = 0;
    do{
        printf("%c|", mot[j]);
        j++;
    } while (mot[j]!= '\0');

    printf("\n");
}
