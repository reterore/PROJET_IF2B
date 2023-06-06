//
// Created by lucas on 24/05/2023.
//

#include "verification.h"



bool verifLettresMot(char* mot, joueur joueur) {
    char copieMain[strlen(joueur.mainJoueur) + 1];
    strcpy(copieMain, joueur.mainJoueur);

    for (int i = 0; i < strlen(mot); ++i) {
        char* lettre = strchr(copieMain, mot[i]);

        if (lettre == NULL) {
            printf("!!!vous n'avez pas les bonnes lettres pour faire ce mot!!!\n");
            return false; // La lettre du mot n'est pas présente dans la main du joueur
        } else {
            *lettre = ' '; // Marquer la lettre comme utilisée en la remplaçant par un espace
        }
    }

    return true; // Toutes les lettres du mot sont présentes dans la main du joueur
}

bool verificationJoker(char* mot, int* jokerMis) {
    int i = 0;
    char joker;
    while (mot[i] != '\0') {
        if (mot[i] == '?') {
            printf("Quelle lettre votre joker remplace-t-il ?\n");
            scanf(" %c", &joker);
            mot[i] = toupper(joker);
            printf("Vous avez créé le mot : %s\n", mot);
            break;
        }
        i++;
    }
    return true;
}

bool rechercheMotFichier(char* fichier, char* mot) {
    FILE* Fichier = fopen(fichier, "r");
    if (Fichier == NULL) {
        printf("Erreur lors de l'ouverture du fichier.\n");
        return false;
    }
    char motFichier[12];
    while (fgets(motFichier, sizeof(motFichier), Fichier) != NULL) {
        motFichier[strcspn(motFichier, "\n")] = '\0';

        if (strcmp(mot, motFichier) == 0 && strlen(motFichier) == strlen(mot)) {
            fclose(Fichier);
            printf("mot valide! %s : %s \n", mot, motFichier);
            return true;
        }
    }

    fclose(Fichier);
    printf("le mot %s n'existe pas!\n", mot);
    return false;
}
bool verifierConflit(const char plateau[][14], int x, int y, char sens, const char* mot) {
    int lenMot = strlen(mot);

    if (sens == 'h') {
        // Vérification pour un placement horizontal
        for (int i = 0; i < lenMot; i++) {
            if ((plateau[y][x + i] != '_' && plateau[y][x + i] != '#' ) && plateau[y][x + i] != mot[i]) {
                printf("Le mot ne peut pas etre place a cet endroit. Il y a deja une lettres.\n");
                return false;
            }
        }
    } else if (sens == 'v') {
        // Vérification pour un placement vertical
        for (int i = 0; i < lenMot; i++) {
            if (plateau[y + i][x] != '_' && plateau[y][x + i] != '#' && plateau[y + i][x] != mot[i]) {
                printf("Le mot ne peut pas etre place a cet endroit. Il y a deja une lettres.\n");
                return false;
            }
        }
    }

    return true;
}


bool grilleBonne(char grille[][14], char* fichier, int dimGrille, int *motFaux) {
    // Vérification des mots horizontaux
    for (int i = 1; i < dimGrille+1; i++) {
        int j = 0;
        while (j < dimGrille) {
            if (grille[i][j] != ' ' && grille[i][j] != '_') {
                char mot[12];
                int k = j;
                int index = 0;
                while (k < dimGrille && grille[i][k] != ' ' && grille[i][k] != '_') {
                    mot[index++] = grille[i][k];
                    k++;
                }
                mot[index] = '\0';

                if (index > 1 && !rechercheMotFichier(fichier, mot)) {
                    printf("vous ne pouver pas posez ce mot ici!\n");
                    *motFaux = 1;
                    return false;
                }

                j = k; // Continuer à partir de la position après le mot
            } else {
                j++;
            }
        }
    }

    // Vérification des mots verticaux
    for (int i = 1; i < dimGrille+1; i++) {
        int j = 0;
        while (j < dimGrille) {
            if (grille[j][i] != ' ' && grille[j][i] != '_') {
                char mot[12];
                int k = j;
                int index = 0;
                while (k < dimGrille && grille[k][i] != ' ' && grille[k][i] != '_') {
                    mot[index++] = grille[k][i];
                    k++;
                }
                mot[index] = '\0';

                if (index > 1 && !rechercheMotFichier(fichier, mot)) {
                    printf("vous ne pouver pas posez ce mot ici!\n");
                    *motFaux = 1;
                    return false;
                }

                j = k; // Continuer à partir de la position après le mot
            } else {
                j++;
            }
        }
    }
    return true;
}

bool contactAvecMotsExistants(char plateau[][14], int dimGrille, char mot[], char sens, int x, int y, int tours, int* motFaux) {
    int longueurMot = strlen(mot);
    if (tours < 1) { // pas de contact requis au premier tour
        return true;
    }

    if (sens == 'h') {
        if (longueurMot == 1){
            if (plateau[y - 1][x] != '_' || plateau[y + 1][x] != '_' || plateau[y][x - 1] != '_' || plateau[y][x + 1] != '_') {
                printf("0Caractères en contact : %c %c %c %c\n", plateau[y - 1][x], plateau[y + 1][x],
                       plateau[y][x - 1], plateau[y][x + 1]);
                return true;
            }
        } else {
            if (plateau[y - 1][x] != '_' || plateau[y + 1][x] != '_' || plateau[y][x - 1] != '_') {
                printf("1Caractères en contact : %c %c %c\n", plateau[y - 1][x], plateau[y + 1][x], plateau[y][x - 1]);
                return true;
            }
            if (longueurMot < 2) {
                for (int i = 1; i < longueurMot - 1; ++i) {
                    printf("2Caractères en contact : %c %c\n", plateau[y - 1][x + i], plateau[y + 1][x + i]);
                    if (plateau[y - 1][x + i] != '_' || plateau[y + 1][x + i] != '_') {
                        printf("2Caractères en contact : %c %c\n", plateau[y - 1][x + i], plateau[y + 1][x + i]);
                        return true;
                    }
                }
            }
            printf("3Caractères en contact : %c %c %c\n", plateau[y - 1][x + longueurMot - 1],
                   plateau[y + 1][x + longueurMot - 1], plateau[y + longueurMot][x]);
            if (plateau[y - 1][x + longueurMot - 1] != '_' || plateau[y + 1][x + longueurMot - 1] != '_' ||
                plateau[y + longueurMot][x + 1] != '_') {
                printf("3Caractères en contact : %c %c %c\n", plateau[y - 1][x + longueurMot - 1],
                       plateau[y + 1][x + longueurMot - 1], plateau[y + longueurMot][x]);
                return true;
            }
        }
    } else if (sens == 'v') {
        if (longueurMot == 1){
            if (plateau[y][x - 1] != '_' || plateau[y][x + 1] != '_' || plateau[y - 1][x] != '_' || plateau[y + 1][x] != '_') {
                printf("0Caractères en contact : %c %c %c %c\n", plateau[y][x - 1], plateau[y][x + 1],
                       plateau[y - 1][x], plateau[y + 1][x]);
                return true;
            }
        } else {
            if (plateau[y][x - 1] != '_' || plateau[y][x + 1] != '_' || plateau[y - 1][x] != '_') {
                printf("1Caractères en contact : %c %c %c\n", plateau[y][x - 1], plateau[y][x + 1], plateau[y - 1][x]);
                return true;
            }
            if (longueurMot < 2) {
                for (int i = 1; i < longueurMot - 1; ++i) {
                    printf("2Caractères en contact : %c %c\n", plateau[y + i][x - 1], plateau[y + i][x + 1]);
                    if (plateau[y + i][x - 1] != '_' || plateau[y + i][x + 1] != '_') {
                        printf("2Caractères en contact : %c %c\n", plateau[y + i][x - 1], plateau[y + i][x + 1]);
                        return true;
                    }
                }
            }
            printf("3Caractères en contact : %c %c %c\n", plateau[y + longueurMot - 1][x - 1],
                   plateau[y + longueurMot - 1][x + 1], plateau[y + longueurMot][x]);
            if (plateau[y + longueurMot - 1][x - 1] != '_' || plateau[y + longueurMot - 1][x + 1] != '_' ||
                plateau[y + longueurMot][x] != '_') {
                printf("3Caractères en contact : %c %c %c\n", plateau[y + longueurMot - 1][x - 1],
                       plateau[y + longueurMot - 1][x + 1], plateau[y + longueurMot][x]);
                return true;
            }
        }
    }
    printf("Vous devez être en contact avec une lettre déjà sur le plateau !\n");
    *motFaux = 1;
    return false;
}
bool verifierPositionInitial(char plateau[][14], int x, int y) {
    if (plateau[y][x] != '_' && plateau[y][x] != '#' ) {
        printf("!!il ya deja une lettre a cette emplacement!!\n");
        return false;
    }
    return true;
}

bool mainVide(joueur joueur, int tours, int nbrJoueur) {
    for (int i = 0; i < joueur.tailleMain; ++i) {
        if (joueur.mainJoueur[i] != '*' && joueur.mainJoueur[i] != '\0') {
            return false;
        }
    }
    printf("bravo, vous avez gagne au tours %d, joueur num%d\n", tours + 1, tours%nbrJoueur + 1);
    return true;
}