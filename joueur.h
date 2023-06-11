//
// Created by lucas on 17/05/2023.
//

#ifndef PROJET_IF2B_JOUEUR_H
#define PROJET_IF2B_JOUEUR_H



#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

typedef struct{
    char *mainJoueur;
    int temps;
    int tailleMain;
    bool perdu;
}joueur;



void initialiserJoueur(joueur* joueur1, int dimGrille, int temps, int nbrJoueur);
void ReprendreJoueur(joueur* joueur, int dimGrille, int temps, int nbrJoueur);
void distribuerMain(joueur* joueur);
void afficherMain(joueur* joueur);
void retirerLettresMain(joueur* j, char* lettresUtilisees, int passerTour);
void sauvegarderPartie(joueur* joueur1, int nbrJoueur, int dimGrille, char plateau[][14], int tours);
void sauvegarderJoueur2(joueur* joueur);
joueur creerJoueur1DepuisSauvegarde(int* nbrJoueur, int* dimGrille, char plateau[][14], int* tours);
joueur creerJoueur2DepuisSauvegarde();
#endif //PROJET_IF2B_JOUEUR_H