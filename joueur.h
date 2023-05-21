//
// Created by lucas on 17/05/2023.
//

#ifndef PROJET_IF2B_JOUEUR_H
#define PROJET_IF2B_JOUEUR_H

#endif //PROJET_IF2B_JOUEUR_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


typedef struct{
    char *mainJoueur;
    int temps;
}joueur;

void distribuerMain(joueur* joueur, int dimGrille);
void afficherMain(joueur* joueur);