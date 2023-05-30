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

        if (strcmp(mot, motFichier) == 0) {
            fclose(Fichier);
            printf("mot valide! %s : %s \n", mot, motFichier);
            return true;
        }
    }

    fclose(Fichier);
    printf("le mot %s n'existe pas!\n", mot);
    return false;
}
bool verifierConflit(const char plateau[][12], int x, int y, char sens, const char* mot) {
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


bool grilleBonne(char grille[][12], char* fichier, int dimGrille, int *motFaux) {
    // Vérification des mots horizontaux
    for (int i = 0; i < dimGrille; i++) {
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
    for (int i = 0; i < dimGrille; i++) {
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

bool contactAvecMotsExistants(char plateau[][12], int dimGrille, char mot[], char sens, int x, int y, int tours, int* motFaux) {
    int longueurMot = strlen(mot);
    if (tours < 1) {
        return true;
    }

    if (sens == 'h') {
        if ((x > 0 && plateau[x - 1][y] != '_') ||                                           // Vérification bord gauche
            (x + longueurMot < dimGrille && plateau[x + longueurMot][y] != '_')) {           // Vérification bord droit
            printf("%c %c %c %d %d\n", plateau[x - 1][y], plateau[x + longueurMot][y], plateau[x][y - 1], x - 1, y);
            return true;
        }
        if (longueurMot > 2) {
            for (int i = 1; i < longueurMot - 1; ++i) {
                if (plateau[x][y + i] != '_') {
                    return true;
                }
            }
        }
        if (x + longueurMot < dimGrille) {
            if (plateau[x + longueurMot][y] != '_' || plateau[x][y + 1] != '_' || plateau[x][y - 1] != '_') {
                return true;
            } else {
                if (plateau[x + longueurMot][y] != '_' || plateau[x][y + 1] != '_') {
                    return true;
                }
            }
        }
    } else if (sens == 'v') {
        if ((y > 0 && plateau[x][y - 1] != '_') ||                                           // Vérification bord haut
            (y + longueurMot < dimGrille && plateau[x][y + longueurMot] != '_')) {           // Vérification bord bas
            printf("%c %c %c %d %d\n", plateau[x][y - 1], plateau[x][y + longueurMot], plateau[x - 1][y], x, y - 1);
            return true;
        }
        if (longueurMot > 2) {
            for (int i = 1; i < longueurMot - 1; ++i) {
                if (plateau[x + i][y] != '_') {
                    return true;
                }
            }
        }
        if (y + longueurMot < dimGrille) {
            if (plateau[x][y + longueurMot] != '_' || plateau[x + 1][y] != '_' || plateau[x - 1][y] != '_') {
                return true;
            } else {
                if (plateau[x][y + longueurMot] != '_' || plateau[x + 1][y] != '_') {
                    return true;
                }
            }
        }
    }

    printf("Vous devez etre en contact avec une lettre deja sur le plateau !\n");
    *motFaux = 1;
    return false;
}
bool verifierPositionInitial(char plateau[][12], int x, int y) {
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
    printf("bravo, vous avez gagne au tours %d, joueur num%d\n", tours, tours%nbrJoueur + 1);
    return true;
}