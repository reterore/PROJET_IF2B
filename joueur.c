//
// Created by lucas on 17/05/2023.
//

#include "joueur.h"


void initialiserJoueur(joueur* joueur, int dimGrille, int temps, int nbrJoueur) {
    int tailleMain;

    if (nbrJoueur == 1) {
        tailleMain = pow(dimGrille, 1);
    } else if (nbrJoueur == 2) {
        tailleMain = (pow(dimGrille, 1)) / 2;
    } else {
        printf("Erreur : nombre de joueurs invalide!\n");
        return;
    }

    joueur->mainJoueur = malloc(tailleMain * sizeof(char));
    joueur->temps = temps;
    joueur->tailleMain = tailleMain;

    distribuerMain(joueur, joueur->tailleMain);
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

void afficherMain(joueur joueur) {
    int i = 0;
    printf("\n");
    printf("Vos lettres:\n");
    do {
        if(joueur.mainJoueur[i] != '*') {
            printf("|%c", joueur.mainJoueur[i]);
        }
        i++;
    } while(i<joueur.tailleMain);
    printf("|\n");
}

void retirerLettresMain(joueur* j, char* lettresUtilisees, int passerTours) {
    int tailleLettres = strlen(lettresUtilisees);
    int tailleMain = strlen(j->mainJoueur);
    if(passerTours != 1) {
        // Parcourir les lettres spécifiées
        for (int i = 0; i < tailleLettres; i++) {
            char lettre = lettresUtilisees[i];

            // Rechercher et remplacer les lettres dans la main du joueur
            for (int k = 0; k < tailleMain; k++) {
                if (j->mainJoueur[k] == lettre) {
                    j->mainJoueur[k] = '*';
                    break;
                }
            }
        }
    }
}


void sauvegarderPartie(joueur* joueur1, joueur* joueur2, int nbrJoueur, int dimGrille, char plateau[][14], int tours) {
    // Ouvrir le fichier en mode d'écriture
    FILE* fichier = fopen("../data/sauvegarde.txt", "w");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return;
    }
    // Écrire les informations dans le fichier
    fprintf(fichier, "%d\n", nbrJoueur);
    fprintf(fichier, "%d\n", dimGrille);
    fprintf(fichier, "%d\n", tours);
    fprintf(fichier, "%s\n", joueur1->mainJoueur);
    fprintf(fichier, "%d\n", joueur1->temps);
    fprintf(fichier, "%d\n", joueur1->tailleMain);
    fprintf(fichier, "%s\n", joueur2->mainJoueur);
    fprintf(fichier, "%d\n", joueur2->temps);
    fprintf(fichier, "%d\n", joueur2->tailleMain);
    // Écrire le plateau de jeu
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 14; j++) {
            fprintf(fichier, "%c\n", plateau[i][j]);
        }
    }
    // Fermer le fichier
    fclose(fichier);
    printf("La partie a ete sauvegardee avec succes dans le fichier sauvegarde.txt.\n");
}

void chargerPartie(joueur* joueur1, joueur* joueur2, int* nbrJoueur, int* dimGrille, char plateau[][14], int* tours) {
    // Ouvrir le fichier en mode de lecture
    FILE* fichier = fopen("../data/sauvegarde.txt", "r");
    if (fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde.\n");
        return;
    }
    // Lire les informations du fichier
    fscanf(fichier, "%d\n", nbrJoueur);
    printf("%d\n", *nbrJoueur);
    fscanf(fichier, "%d\n", dimGrille);
    printf("%d\n", *dimGrille);
    fscanf(fichier, "%d\n", tours);
    printf("%d\n", *tours);
    fscanf(fichier, "%s\n", joueur1->mainJoueur);
    printf("Main du joueur : %s\n", joueur1->mainJoueur);
    fscanf(fichier, "%d\n", &joueur1->temps);
    printf("%d\n", joueur1->temps);
    fscanf(fichier, "%d\n", &joueur1->tailleMain);
    printf("%d\n", joueur1->tailleMain);
    printf("le bug se situe juste ici\n");
    fscanf(fichier, "%s\n", joueur2->mainJoueur);
    printf("test");
    fscanf(fichier, "%d\n", &joueur2->temps);
    printf("test");
    fscanf(fichier, "%d\n", &joueur2->tailleMain);
    printf("test\n");



    // Lire le plateau de jeu
    for (int i = 0; i < 14; i++) {
        for (int j = 0; j < 14; j++) {
            fscanf(fichier, " %c", &plateau[i][j]);
        }
    }
    // Fermer le fichier
    fclose(fichier);
    printf("La partie a été chargée avec succès à partir du fichier sauvegarde.txt.\n");
}