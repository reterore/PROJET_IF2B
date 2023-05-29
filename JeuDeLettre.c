//
// Created by lucas on 26/05/2023.
//


#include "JeuDeLettre.h"

void jeuDeLettres(){
    joueur j1, j2;
    int nbrJoueur, dimGrille, temps;
    char choixMenu;
    char plateau[12][12];
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
                break;
            case 'n':
                nbrJoueur = asquisitionNbrJoueur();
                dimGrille = acquisitionDimGrille();//demande et prends la valeur de la taille de la grille
                temps = acquisitionTemps();//demande et prends la valeur du temps de la partie
                initGrille(plateau);// initialise la grille en fonction de la dimension donnée
                if(nbrJoueur == 1){
                    initialiserJoueur(&j1, dimGrille, temps, nbrJoueur);
                    initialiserJoueur(&j2, dimGrille, temps, nbrJoueur);
                }else {
                    initialiserJoueur(&j1, dimGrille, temps/2, nbrJoueur);
                    initialiserJoueur(&j2, dimGrille, temps/2, nbrJoueur);
                }
                partie(j1 , j2, plateau, dimGrille, nbrJoueur);
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
    }while(choixMenu != 'q');
}

void partie(joueur j1, joueur j2, char plateau[][12], int dimGrille, int nbrJoueur){
    JouerTours(plateau, dimGrille, j1, j2, nbrJoueur);
}