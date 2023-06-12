//
// Created by lucas on 26/05/2023.
//


#include "JeuDeLettre.h"

void jeuDeLettres() {
    joueur j1, j2;
    int nbrJoueur, dimGrille, temps, tours = 0;
    char choixMenu;
    char plateau[14][14];

    srand(time(NULL));

    printf("\n/// Bienvenue dans le jeu de lettres! ///\n");

    do {
        do {
            printf("\nVoulez-vous : reprendre une partie (r), commencer une nouvelle partie (n) ou quitter (q) ?\n");
            scanf(" %c", &choixMenu);
        } while (choixMenu != 'r' && choixMenu != 'n' && choixMenu != 'q');
        nbrJoueur = 0;
        switch (choixMenu) {
            case 'r': // reprendre une partie sauvegardée
                printf("Vous avez choisi de reprendre votre partie.\n");
                j1 = creerJoueur1DepuisSauvegarde(&nbrJoueur, &dimGrille, plateau, &tours);
                j2 = creerJoueur2DepuisSauvegarde();
                printf("%d %d %d %s %s\n", dimGrille, tours, nbrJoueur, j1.mainJoueur, j2.mainJoueur);
                printf("test");
                JouerTours(plateau, dimGrille, &j1, &j2, nbrJoueur, tours);
                break;

            case 'n': // nouvelle partie
                nbrJoueur = acquisitionNbrJoueur();  // Demande le nombre de joueurs
                dimGrille = acquisitionDimGrille();  // Demande la dimension de la grille
                temps = acquisitionTemps();  // Demande la durée de la partie
                initGrille(plateau);  // Initialise la grille en fonction de la dimension donnée
                initialiserJoueur(&j1, dimGrille, temps / nbrJoueur, nbrJoueur);
                initialiserJoueur(&j2, dimGrille, temps / nbrJoueur, nbrJoueur);
                annoncePartie(nbrJoueur, dimGrille, temps);
                JouerTours(plateau, dimGrille, &j1, &j2, nbrJoueur, tours);
                break;

            case 'q': // quitter
                printf("/// --- Au revoir! --- ///");
                break;

            default:
                printf("Erreur! Choix invalide.");
                break;
        }

        free(j1.mainJoueur);
        free(j2.mainJoueur);
    } while (choixMenu != 'q'); // itérer le menu tant que le joueur ne fais pas quitter
}



