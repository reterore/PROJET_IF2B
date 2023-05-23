//
// Created by lucas on 16/05/2023.
//

#ifndef PROJET_IF2B_PLATEAU_H
#define PROJET_IF2B_PLATEAU_H



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#include "joueur.h"

#endif //PROJET_IF2B_PLATEAU_H


void initGrille(int dimGrille, char plateau[12][12]);
void affichageGrille(int dimGrille, char plateau[][dimGrille]);
int asquisitionNbrJoueur();
int acquisitionDimGrille();
int acquisitionTemps();
int annoncePartie(int nbrJoueur, int dimGrille, int temps);
void placerMot(char plateau[12][12],  int dimGrille, joueur joueur);
void acquisitionMot(char* mot, int dimGrille);
void affichageMot(char* mot);

int verifLettres(char* mot, joueur joueur, int dimGrille);
