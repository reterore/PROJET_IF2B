#include <stdio.h>
#include "plateau.h"
#include "joueur.h"



int main() {
    joueur j1, j2;
    int nbrJoueur = 0, dimGrille, temps;
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

                annoncePartie(nbrJoueur, dimGrille, temps);// affiche un texte pour l'instant
                initGrille(dimGrille, plateau);// initialise la grille en fonction de la dimension donnée
                affichageGrille(dimGrille, plateau);//affiche la grille
                printf("test\n");
                if(nbrJoueur == 1){
                    initialiserJoueur(&j1, dimGrille, temps, nbrJoueur);
                    printf("\nVotres temps :%d secondes\n", j1.temps);
                }else {
                    initialiserJoueur(&j1, dimGrille, temps/2, nbrJoueur);
                    printf("\nVotres temps :%d secondes\n", j1.temps);
                    initialiserJoueur(&j2, dimGrille, temps/2, nbrJoueur);
                    printf("\nVotres temps :%d secondes\n", j2.temps);
                }
                placerMot(plateau, dimGrille, j1);
                break;
            case 'q':
                printf("/// --- Au revoir! --- ///");
                break;

        }
        if(nbrJoueur == 1){
            free(j1.mainJoueur);
        }else{
            free(j1.mainJoueur);
            free(j2.mainJoueur);
        }

    }while(choixMenu != 'q');
    return 0;
}
