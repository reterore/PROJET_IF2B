//
// Created by lucas on 26/05/2023.
//


#include "JeuDeLettre.h"

void jeuDeLettres(){
    joueur j1, j2;
    int nbrJoueur, dimGrille, temps, tours = 0;
    int partieSauvegarder = 0;
    char choixMenu;
    char plateau[14][14];
    srand(time(NULL));
    printf("\n/// Bienvenue dans le jeu de lettre! ///\n");
    do{
        do{
            printf("\nVoulez-vous: reprendre une partie (r), commencer une nouvelle partie (n) ou quitter (q) ?\n");
            scanf(" %c", &choixMenu);
        } while (choixMenu != 'r' && choixMenu != 'n' && choixMenu != 'q');
        nbrJoueur = 0;
        switch (choixMenu) {
            case 'r':
                printf("vous avez decidez de reprendre votre partie.\n");
                chargerPartie(&j1, &j2, &nbrJoueur, &dimGrille, plateau, &tours);
                printf("%d %d %d %s %s ", dimGrille, tours, nbrJoueur, j1.mainJoueur, j2.mainJoueur);
                JouerTours(plateau, dimGrille, j1, j2, nbrJoueur, tours);
                break;
            case 'n':
                nbrJoueur = asquisitionNbrJoueur();
                dimGrille = acquisitionDimGrille();//demande et prends la valeur de la taille de la grille
                temps = acquisitionTemps();//demande et prends la valeur du temps de la partie
                initGrille(plateau);// initialise la grille en fonction de la dimension donnée
                initialiserJoueur(&j1, dimGrille, temps/nbrJoueur, nbrJoueur);
                initialiserJoueur(&j2, dimGrille, temps/nbrJoueur, nbrJoueur);
                printf("test");
                JouerTours(plateau, dimGrille, j1, j2, nbrJoueur, tours);
                break;
            case 'q':
                printf("/// --- Au revoir! --- ///");
                break;
            default:
                printf("erreur!");
                break;
        }
        if(nbrJoueur == 1){
            free(j1.mainJoueur);
            free(j2.mainJoueur);
        }else{
            free(j1.mainJoueur);
            free(j2.mainJoueur);
        }
    }while(choixMenu != 'q' || partieSauvegarder == 0);
}



