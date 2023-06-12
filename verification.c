//
// Created by lucas on 24/05/2023.
//

#include "verification.h"

bool verifLettresMot(char* lettresUtilisees, joueur* joueur) {
    char motSansEtoiles[13]; // Tableau pour stocker le mot sans les étoiles
    int index = 0;

    for (int i = 0; i < strlen(lettresUtilisees); ++i) {
        if (lettresUtilisees[i] != '*') {
            motSansEtoiles[index++] = lettresUtilisees[i];
        }
    }

    motSansEtoiles[index] = '\0'; // Ajouter le caractère de fin de chaîne

    for (int i = 0; i < strlen(motSansEtoiles); ++i) {
        char* lettre = strchr(joueur->mainJoueur, motSansEtoiles[i]);

        if (lettre == NULL) {
            printf("!!!vous n'avez pas les bonnes lettres pour faire ce mot!!!\n");
            return false; // La lettre du mot n'est pas présente dans la main du joueur
        }
    }

    return true; // Toutes les lettres du mot sont présentes dans la main du joueur
}


bool verifierPlacement(const char plateau[][14], int x, int y, char sens, char* mot, char* lettresUtilisees) {
    int longueurMot = strlen(mot), n;
    if(sens == 'h'){
        for (int i = 0; i < longueurMot; ++i) {
            if(plateau[y][x+i] != '_' && plateau[y+i][x+i] != '#'){
                if (plateau[y][x+i] != mot[i]){
                    printf("une lettre est poser sur une lettre differentes!\n");
                    return false;
                }else{
                    lettresUtilisees[i] = '*';
                }
            }
        }
    } else{
        for (int i = 0; i < longueurMot; ++i) {
            if(plateau[y+i][x] != '_' && plateau[y+i][x] != '#'){
                if (plateau[y+i][x] != mot[i]){
                    printf("une lettre est poser sur une lettre differentes!\n");
                    return false;
                }else{
                    for (int j = 0; j < strlen(lettresUtilisees); ++j) {
                        if(lettresUtilisees[j] == mot[i]){
                            lettresUtilisees[j] = '*';
                            j = 12;
                        }
                    }
                }
            }
        }
    }
    printf("\n");
    return true;
}

bool verificationJoker(char* mot) {
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
    printf("Vous avez créer le mot %s qui n'existe pas!\n", mot);
    return false;
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

bool contactAvecMotsExistants(char plateau[][14], char* mot,char sens, int x, int y, int tours, int* motFaux) {
    int longueurMot = strlen(mot);
    if (tours < 1) { // pas de contact requis au premier tour
        return true;
    }

    if (sens == 'h') {
        if (longueurMot == 1){
            if (plateau[y - 1][x] != '_' || plateau[y + 1][x] != '_' || plateau[y][x - 1] != '_' || plateau[y][x + 1] != '_') {
                return true;
            }
        } else {
            if (plateau[y - 1][x] != '_' || plateau[y + 1][x] != '_' || plateau[y][x - 1] != '_') {
                return true;
            }
            if (longueurMot > 2) {
                for (int i = 1; i < longueurMot - 1; ++i) {
                    if (plateau[y - 1][x + i] != '_' || plateau[y + 1][x + i] != '_') {
                        return true;
                    }
                }
            }
            if (plateau[y - 1][x + longueurMot - 1] != '_' || plateau[y + 1][x + longueurMot - 1] != '_' ||
                plateau[y + longueurMot][x + 1] != '_') {
                return true;
            }
        }
    } else if (sens == 'v') {
        if (longueurMot == 1){
            if (plateau[y][x - 1] != '_' || plateau[y][x + 1] != '_' || plateau[y - 1][x] != '_' || plateau[y + 1][x] != '_') {
                return true;
            }
        } else {
            if (plateau[y][x - 1] != '_' || plateau[y][x + 1] != '_' || plateau[y - 1][x] != '_') {
                return true;
            }
            if (longueurMot > 2) {
                for (int i = 1; i < longueurMot - 1; ++i) {
                    if (plateau[y + i][x - 1] != '_' || plateau[y + i][x + 1] != '_') {
                        return true;
                    }
                }
            }
            if (plateau[y + longueurMot - 1][x - 1] != '_' || plateau[y + longueurMot - 1][x + 1] != '_' ||
                plateau[y + longueurMot][x] != '_') {
                return true;
            }
        }
    }
    printf("Vous devez etre en contact avec une lettre deja sur le plateau !\n");
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

bool mainVide(joueur joueur, int tours, int numJoueur) {
    for (int i = 0; i < joueur.tailleMain; ++i) {
        if (joueur.mainJoueur[i] != '*' && joueur.mainJoueur[i] != '\0') {
            return false;
        }
    }
    printf("bravo, vous avez gagne au tours %d, joueur num%d\n", tours + 1, numJoueur);
    return true;
}
bool verifTemps(joueur* joueurActif, long long tempsDebut, long long tempsFin){
    double duree = difftime(tempsFin, tempsDebut);
    if (joueurActif->temps > duree){
        joueurActif->temps = joueurActif->temps - duree;
        return true;
    } else{
        printf("vous n'avez plus de temps, vous ne pouvez plus posez de lettres\n");
        joueurActif->perdu = true;
        return false;
    }
}