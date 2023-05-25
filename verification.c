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

bool verifEmplacement(char sens, int x,int y, char* mot, int dimGrille){
    if(sens == 'v'){
        if(x + strlen(mot)> dimGrille){
            printf("!!!le mot ne rentre pas dans l'espace disponible!!!\n");
            return false; // le mot sort de la grille
        }else{
            return true; // le mot rentre dans la grille
        }

    }else{
        if(y + strlen(mot)> dimGrille){
            printf("le mot ne rentre pas dans l'espace disponible!\n");
            return false;
        }else{
            printf("le mot ne rentre pas dans l'espace disponible!");
            return true;
        }
    }
}