#include <stdio.h>
#include "plateau.h"
#include "joueur.h"
#include <stdlib.h>



int main() {
    joueur j1, j2;
    int nbrJoueur, dimGrille, temps;
    char choixMenu;
    char plateau[dimGrille][dimGrille];
    printf("/// Bienvenue dans le jeu de lettre! ///\n");
    do{
        do{
            printf("Voulez-vous: reprendre une partie (r), commencer une nouvelle partie (n) ou quitter (q) ?\n");
            scanf(" %c", &choixMenu);
        } while (choixMenu != 'r' && choixMenu != 'n' && choixMenu != 'q');
        switch (choixMenu) {
            case 'r':
                printf("vous avez decidez de reprendre votre partie.\n");
                break;
            case 'n':
                do{
                    printf("combien de joueur? 1 ou 2 ?\n");
                    scanf("%d", &nbrJoueur);
                } while (nbrJoueur !=1 && nbrJoueur != 2);
                dimGrille = acquisitionDimGrille();//demande et prends la valeur de la taille de la grille
                temps = acquisitionTemps();//demande et prends la valeur du temps de la partie
                partie(nbrJoueur, dimGrille, temps);// affiche un texte pour l'instant
                initGrille(dimGrille, plateau);
                affichageGrille(dimGrille, plateau);
                printf("test");
                distribuerMain(&j1, dimGrille);
                printf("votre main: \n");
                afficherMain(j1);
                break;
            case 'q':
                break;
        }
    }while(choixMenu != 'q');
    return 0;
}
