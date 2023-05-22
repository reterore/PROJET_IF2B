//
// Created by lucas on 17/05/2023.
//

#include "joueur.h"


void initialiserJoueur(joueur* joueur1, int dimGrille, int temps, int nbrJoueur) {
    int tailleMain;

    if (nbrJoueur == 1) {
        tailleMain = pow(dimGrille, 1.5);
    } else if (nbrJoueur == 2) {
        tailleMain = (pow(dimGrille, 1.67)) / 2;
    } else {
        printf("Erreur : nombre de joueurs invalide!\n");
        return;
    }

    joueur1->mainJoueur = malloc(tailleMain * sizeof(char));
    joueur1->temps = temps;

    distribuerMain(joueur1, tailleMain);
    afficherMain(*joueur1, tailleMain);
}



// distribuerMain, distrube la main du joueur en fonction de la dimension de la grille
void distribuerMain(joueur* joueur, int tailleMain) {
    int lettre;
    char totalLettres[10000];
    int frequencesMultiple[26];
    char lettres[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    double frequences[] = {0.0818, 0.009, 0.0335, 0.0367, 0.1673, 0.0107, 0.0087, 0.0074, 0.0759, 0.0061, 0.0007, 0.0546, 0.0297, 0.071, 0.058, 0.0252, 0.0136, 0.067, 0.0796, 0.0725, 0.0632, 0.0184, 0.0005, 0.0043, 0.0013, 0.0033};
    for (int i = 0; i < 26; ++i) {
        frequencesMultiple[i] = 0;
    }
    // Calculer les fréquences multiples
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < i+1; ++j) {
            frequencesMultiple[i] = frequencesMultiple[i] + 10000* frequences[j];
        }
    }
    int j = 0;
    // Créer la liste en fonction des fréquences
    for (int i = 0; i < 10000; ++i) {
        totalLettres[i] = lettres[j];
        if (frequencesMultiple[j] <= i) {
            j++;
        }
    }
    for (int i = 0; i <= tailleMain-2; ++i) {
        lettre = rand()%10000;
        joueur->mainJoueur[i] = totalLettres[lettre];
    }
    joueur->mainJoueur[tailleMain - 1] = '?';
    joueur->mainJoueur[tailleMain] = '\0'; // On ajoute le caractère de fin de chaîne

}

void afficherMain(joueur joueur, int tailleMain) {
    int i = 0;
    printf("\n");
    printf("Vos lettres:\n");
    do {
        printf("|%c", joueur.mainJoueur[i]);
        i++;
    } while(i<tailleMain);
    printf("|");
}