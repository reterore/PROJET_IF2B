//
// Created by lucas on 17/05/2023.
//

#ifndef PROJET_IF2B_JOUEUR_H
#define PROJET_IF2B_JOUEUR_H



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>


typedef struct{
    char *mainJoueur;
    int temps;
    int tailleMain;
}joueur;

void initialiserJoueur(joueur* joueur1, int dimGrille, int temps, int nbrJoueur);
void distribuerMain(joueur* joueur, int tailleMain);
void afficherMain(joueur joueur);
void retirerLettresMain(joueur* j, char* mot);
#endif //PROJET_IF2B_JOUEUR_H