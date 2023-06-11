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


void initGrille(char (*plateau)[14]){
    for (int i = 0; i < 14; ++i) {
        for (int j = 0; j < 14; ++j) {
            plateau[i][j]='_';
        }
    }
}

void affichageGrille(int dimGrille, char (*plateau)[14]){
    printf("  ");
    for (int i = 0; i < dimGrille/8; ++i) {
        printf("      ");
    }
    printf("**--Plateau de jeu--**\n");
    printf("     ");
    for (int i = 1; i < dimGrille + 1; ++i) {
        if (i >= 11) {
            printf("%d  ", i);
        } else {
            printf(" %d  ", i);
        }
    }
    printf("\n");
    for (int i = 1; i < dimGrille + 1; ++i) {
        if(i>=10){
            printf(" %d ", i);
        } else{
            printf(" %d  ", i);
        }
        for (int j = 1; j < dimGrille + 1; ++j) {
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
void demanderCoordonnees(char* sens, int* x, int* y, int dimGrille, int tours) {
    int decalage = 0;
    if (tours < 1) {
        decalage = 1;
    }

    do {
        printf("Voulez-vous placer le mot verticalement (v) ou horizontalement (h)?\n");
        scanf(" %c", sens);
    } while (*sens != 'v' && *sens != 'h');

    // Afficher le sens du mot choisi
    if (*sens == 'v') {
        printf("Vous allez placer votre mot verticalement. Quelles sont les coordonnees de la 1ere lettre?\n");
        printf("Attention, (1,1) correspond au coin en haut a gauche du plateau!\n");
        printf("Coordonnee en y (lignes) : y = ");
        scanf("%d", y);
        printf("Coordonnee en x (colonnes) : x = ");
        scanf("%d", x);

        while (*y < 1 || *y > dimGrille - decalage || *x < 1 || *x > dimGrille) {
            printf("/// Mauvaise saisie ! ///\n");
            printf("Coordonnee en y comprise entre 1 et %d : y = ", dimGrille - decalage);
            scanf("%d", y);
            printf("Coordonnee en x comprise entre 1 et %d : x = ", dimGrille);
            scanf("%d", x);
        }
    } else {
        printf("Vous allez placer votre mot horizontalement. Quelles sont les coordonnees de la 1ere lettre?\n");
        printf("Coordonnee en y (lignes) : y = ");
        scanf("%d", y);
        printf("Coordonnee en x (colonnes) : x = ");
        scanf("%d", x);

        while (*y < 1 || *y > dimGrille || *x < 1 || *x > dimGrille - decalage) {
            printf("/// Mauvaise saisie ! ///\n");
            printf("Coordonnee en y comprise entre 1 et %d : y = ", dimGrille);
            scanf("%d", y);
            printf("Coordonnee en x comprise entre 1 et %d : x = ", dimGrille - decalage);
            scanf("%d", x);
        }
    }
}

void placerMot(char (*plateau)[14], int x, int y, char sens, const char* mot, int passerTour) {
    int lenMot = strlen(mot);
    if(passerTour != 1) {
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
}

void retirerMot(char plateau[][14], int x, int y, char sens, char* mot, int motFaux, char* lettreUtilisees) {
    // Vérifier si le mot doit être retiré
    if (motFaux == 1) {
        int tailleMot = strlen(mot);

        // Parcourir le mot et retirer les lettres de la grille
        for (int i = 0; i < tailleMot; i++) {
            if(lettreUtilisees[i] != '*') {
                if (sens == 'h') {
                    plateau[y][x + i] = '_';
                } else {
                    plateau[y + i][x] = '_';
                }
            }
        }
    }
}


void JouerTours(char plateau[][14], int dimGrille, joueur* j1, joueur* j2, int nbrJoueur, int tours) {
    char mot[dimGrille + 1];
    char sens = 'h'; //initialisation au hasard pour éviter les bugs
    char lettresUtilisees[12]; // 12 car c'est le nombre maxi de lettres qui pourraient être jouer
    joueur* joueurActif;
    int x = 0, y = 0, motFaux = 0, passerTour = 0, numJoueur;
    long long tempsDebut, tempsFin;
    do {
        if (nbrJoueur == 2){
            if (j1->perdu && j2->perdu) {
                printf("les 2 joueurs n'ont plus de temps, fin de la partie!\n");
                return;
            }
        } else {
            if (j1->perdu) {
                printf("Vous n'avez plus de temps, fin de la partie!\n");
                return;
            }
        }
        tempsDebut = time(NULL);
        if (tours % nbrJoueur + 1 == 1) {
            joueurActif = j1;
            numJoueur = 1;
        } else {
            joueurActif = j2;
            numJoueur = 2;
        }
        if (j1->perdu){
            joueurActif = j2;
            numJoueur = 2;
        }
        if (j2->perdu){
            joueurActif = j1;
            numJoueur = 1;
        }
        printf("Tours num%d, le joueur actif est le joueur num%d\n", tours + 1, numJoueur);

        do {
            do {
                retirerMot(plateau, x, y, sens, mot, motFaux, lettresUtilisees);
                for (int i = 0; i < dimGrille; ++i) {
                    mot[i] = '\0';
                }
                for (int i = 0; i < 12; ++i) {
                    lettresUtilisees[i] = '\0';
                }
                do {
                    do {
                        do {
                            retirerIndicePlacement(plateau, dimGrille);
                            affichageGrille(dimGrille, plateau);
                            printf("voici votre temps: %d et ", joueurActif->temps);
                            afficherMain(joueurActif);
                            demanderCoordonnees(&sens, &x, &y, dimGrille, tours);
                        } while (!verifierPositionInitial(plateau, x, y));
                        getchar();
                        plateau[y][x] = '#';
                        acquisitionMot(mot, dimGrille, joueurActif, plateau, sens, x, y, lettresUtilisees, tours);
                        if (strcmp(mot, "/S") == 0) { // Vérifier si le joueur veut sauvegarder la partie
                            retirerIndicePlacement(plateau, dimGrille);
                            sauvegarderPartie(j1, nbrJoueur, dimGrille, plateau, tours); // Appeler une fonction pour sauvegarder la partie
                            sauvegarderJoueur2(j2);
                            return; // Sortir de la fonction après avoir sauvegardé la partie
                        } else if (strcmp(mot, "/P") == 0) {
                            passerTour = 1;
                        } else if (strcmp(mot, "/Q") == 0) {
                            printf("Vous avez terminez la partie.\n");
                            return;
                        }
                        verificationJoker(mot);
                    } while (passerTour == 0 && !verifierPlacement(plateau, x, y, sens, mot, lettresUtilisees));
                } while (!verifLettresMot(lettresUtilisees, joueurActif));
                affichageMot(mot);
                placerMot(plateau, x, y ,sens, mot, passerTour);
            } while (passerTour == 0 && !contactAvecMotsExistants(plateau, mot, sens, x, y, tours, &motFaux));
        } while (passerTour == 0 && !grilleBonne(plateau, "../data/liste_francais.txt", dimGrille, &motFaux));
        retirerLettresMain(joueurActif, lettresUtilisees, passerTour);
        tours++;
        motFaux = 0;
        passerTour = 0;
        tempsFin = time(NULL);
        verifTemps(joueurActif, tempsDebut, tempsFin);
    } while (!mainVide(*joueurActif, tours-1, nbrJoueur));
}


void acquisitionMot(char* mot, int dimGrille, joueur* joueur, char (*plateau)[14], char sens, int x, int y, char* lettresUtilisees, int tours) {
    int limite, n = (tours > 0) ? 0 : 1;
    affichageGrille(dimGrille, plateau);
    afficherMain(joueur);
    if(sens == 'v'){
        limite = y-1;
    } else {
        limite = x-1;
    }
    do {
        for (int i = 0; i < dimGrille + 1; ++i) {
            // initialiser le mot avec des \0
            mot[i] = '\0';
        }
        printf("\nVous pouvez passer votre tours avec */p*, quittez avec */q* ou sauvegardez avec */s*");
        printf("\n/// Veuillez entrer un mot de %d lettres maximum /// :", dimGrille - limite);
        gets(mot);
        mot[strcspn(mot, "\n")] = '\0'; // supprimer le '\n' de l'entrée
        for (int i = 0; i < strlen(mot); ++i) {
            // mettre le mot en majuscule
            mot[i] = toupper(mot[i]);
        }
    } while(strlen(mot) < 1 + n || strlen(mot) > dimGrille - limite);
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

void retirerIndicePlacement(char plateau[][14], int dimGrille){
    for (int i = 1; i < dimGrille + 1; ++i) {
        for (int j = 1; j < dimGrille + 1; ++j) {
            if(plateau[i][j]=='#'){
                plateau[i][j] = '_';
                break;
            }
        }
    }
}