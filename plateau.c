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


void initGrille(char (*plateau)[12]){
    for (int i = 0; i < 12; ++i) {
        for (int j = 0; j < 12; ++j) {
            plateau[i][j]='_';
        }
    }
}

void affichageGrille(int dimGrille, char (*plateau)[12]){
    printf("***** Le plateau *****\n");
    printf("     ");
    for (int i = 0; i < dimGrille; ++i) {
        if (i >= 11) {
            printf("%d  ", i);
        } else {
            printf(" %d  ", i);
        }
    }
    printf("\n");
    for (int i = 0; i < dimGrille; ++i) {
        if(i>=10){
            printf(" %d ", i);
        } else{
            printf(" %d  ", i);
        }
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
void demanderCoordonnees(char* sens, int* x, int* y, int dimGrille) {
    do {
        printf("Voulez-vous placer le mot verticalement (v) ou horizontalement (h)?\n");
        scanf(" %c", sens);
    } while (*sens != 'v' && *sens != 'h');

    // Afficher le sens du mot choisi
    if (*sens == 'v') {
        printf("Vous allez placer votre mot verticalement, ");
        printf("quelles sont les coordonnees de la 1ere lettre?\n!!!Attention, (0,0) correspond au coin en haut a gauche du plateau!!!\n");
        printf("Coordonnee en x (lignes) : x =");
        scanf("%d", x);
        printf("Coordonnee en y (colonnes) : y =");
        scanf("%d", y);

        while ((*x < 0 || *x >= dimGrille) || (*y < 0 || *y > dimGrille - 2)) {
            printf("/// Mauvaise saisie ! ///\n");
            printf("Coordonnee en x comprise entre 0 et %d : x =", dimGrille - 1);
            scanf("%d", x);
            printf("Coordonnee en y comprise entre 0 et %d : y =", dimGrille - 2);
            scanf("%d", y);
        }
    } else {
        printf("Vous allez placer votre mot horizontalement.\n");
        printf("quelles sont les coordonnees de la 1ere lettre?\n");
        printf("Coordonnee en x (lignes) : x =");
        scanf("%d", x);
        printf("Coordonnee en y (colonnes) : y =");
        scanf("%d", y);

        while ((*x < 0 || *x > dimGrille - 2) || (*y < 0 || *y >= dimGrille)) {
            printf("/// Mauvaise saisie ! ///\n");
            printf("Coordonnee en x comprise entre 0 et %d : x =", dimGrille - 2);
            scanf("%d", x);
            printf("Coordonnee en y comprise entre 0 et %d : y =", dimGrille-1);
            scanf("%d", y);
        }
    }
}

void placerMot(char (*plateau)[12], int x, int y, char sens, const char* mot) {
    int lenMot = strlen(mot);

    if (sens == 'h') {
        // Placement horizontal
        for (int i = 0; i < lenMot; i++) {
            plateau[y][x + i] = mot[i];
        }
    } else if (sens == 'v') {
        // Placement vertical
        for (int i = 0; i < lenMot; i++) {
            plateau[y + i][x] = mot[i];
        }
    }
}

void retirerMot(char plateau[][12], int x, int y, char sens, char* mot, int motFaux) {
    // Vérifier si le mot doit être retiré
    if (motFaux == 1) {
        int tailleMot = strlen(mot);

        // Parcourir le mot et retirer les lettres de la grille
        for (int i = 0; i < tailleMot; i++) {
            if (sens == 'h') {
                plateau[y][x + i] = '_';
            } else {
                plateau[y + i][x] = '_';
            }
        }
    }
}


void JouerTours(char plateau[][12], int dimGrille, joueur j1, joueur j2, int nbrJoueur) {
    char mot[dimGrille + 1];
    char sens = 'h'; //initialisation au hasard pour éviter les bugs
    char lettresUtilisees[41]; // 41 car c'est le nombre maxi de carte que pourrais posséder une main
    joueur joueurActif;
    int x = 0, y = 0, tours = 0, motFaux = 0;
    int jokerMis = 0;
    do {
        if (tours % nbrJoueur + 1 == 1) {
            joueurActif = j1;
        } else {
            joueurActif = j2;
        }
        printf("Tours num%d, le joueur actif est le joueur num%d\n", tours + 1, tours % nbrJoueur + 1);
        do {
            do {
                retirerMot(plateau, x, y, sens, mot, motFaux);
                for (int i = 0; i < dimGrille; ++i) {
                    mot[i] = '\0';
                }
                for (int i = 0; i < 41; ++i) {
                    lettresUtilisees[i] = '\0';
                }
                do {
                    do {
                        do {
                            affichageGrille(dimGrille, plateau);
                            afficherMain(joueurActif);
                            demanderCoordonnees(&sens, &x, &y, dimGrille);
                        } while (!verifierPositionInitial(plateau, x, y));
                        getchar();
                        retirerIndicePlacement(plateau, dimGrille);
                        plateau[x][y] = '#';
                        acquisitionMot(mot, dimGrille, joueurActif, plateau, sens, x, y, lettresUtilisees);
                    } while (!verifLettresMot(mot, joueurActif));
                } while (!verifierConflit(plateau, x, y, sens, mot));
                verificationJoker(mot, &jokerMis);
                affichageMot(mot);
                placerMot(plateau, x, y ,sens, mot);
            } while (!contactAvecMotsExistants(plateau, dimGrille, mot, sens, x, y, tours, &motFaux));
        } while (!grilleBonne(plateau, "../data/liste_francais.txt", dimGrille, &motFaux));
        retirerLettresMain(&joueurActif, lettresUtilisees);
        tours++;
        motFaux = 0;
        jokerMis = 0;
    } while (!mainVide(joueurActif));
}


void acquisitionMot(char* mot, int dimGrille, joueur joueur, char (*plateau)[12], char sens, int x, int y, char* lettresUtilisees) {
    int limite;
    affichageGrille(dimGrille, plateau);
    afficherMain(joueur);
    if(sens == 'v'){
        limite = y;
    }else{
        limite = x;
    }
    do {
        for (int i = 0; i < dimGrille + 1; ++i) { // initilaiser le mot avec des \0
            mot[i] = '\0';
        }
        printf("\n/// Veuillez entrer un mot de %d lettres maximum :", dimGrille-limite);
        gets(mot);
    } while(strlen(mot)>=dimGrille-limite+1 || strlen(mot)<=1);
    mot[strcspn(mot, "\n")] = '\0'; // supprime le '\n' de l'entrée
    for (int i = 0; i < strlen(mot); ++i) { // met le mot en majuscule
        mot[i] = toupper(mot[i]);
    }
    for (int i = 0; i < strlen(mot); ++i) {
        lettresUtilisees[i] = mot[i];
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

void retirerIndicePlacement(char plateau[][12], int dimGrille){
    for (int i = 0; i < dimGrille; ++i) {
        for (int j = 0; j < dimGrille; ++j) {
            if(plateau[i][j]=='#'){
                plateau[i][j] = '_';
                break;
            }
        }
    }
}