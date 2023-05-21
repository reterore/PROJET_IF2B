//
// Created by lucas on 17/05/2023.
//

#include "joueur.h"

# distribuerMain, distrube la main du joueur en fonction de la dimension de la grille
void distribuerMain(joueur* joueur, int dimGrille) {
    char lettres[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    double frequences[] = {0.0818, 0.009, 0.0335, 0.0367, 0.1673, 0.0107, 0.0087, 0.0074, 0.0759, 0.0061, 0.0007, 0.0546, 0.0297, 0.071, 0.058, 0.0252, 0.0136, 0.067, 0.0796, 0.0725, 0.0632, 0.0184, 0.0005, 0.0043, 0.0013, 0.0033};    int taille = sizeof(lettres) / sizeof(lettres[0]);

    srand(time(NULL));

    for (int i = 0; i < pow(dimGrille, 1.5) ; ++i) {
        double choix = ((double)rand() / RAND_MAX);
        double sommeFrequences = 0.0;
        int indexLettre = 0;

        while (sommeFrequences <= choix) {
            sommeFrequences += frequences[indexLettre];
            ++indexLettre;
        }

        joueur->mainJoueur[i] = lettres[indexLettre - 1];
    }
    joueur->mainJoueur[10] = '\0'; // On ajoute le caractère de fin de chaîne
}

void afficherMain(joueur joueur) {
    int i = 0;
    while (joueur.mainJoueur[i] != '\0') {
        printf("|%c", joueur.mainJoueur[i]);
        i++;
    }
    printf("|");
}