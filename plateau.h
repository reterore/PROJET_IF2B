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
#include "verification.h"

#endif //PROJET_IF2B_PLATEAU_H


void initGrille(char plateau[][14]);
void affichageGrille(int dimGrille, char plateau[][dimGrille]);
int asquisitionNbrJoueur();
int acquisitionDimGrille();
int acquisitionTemps();
void placerMot(char plateau[][14], int x, int y, char sens, const char* mot);
void demanderCoordonnees(char* sens, int* x, int* y, int dimGrille, int tours);
int annoncePartie(int nbrJoueur, int dimGrille, int temps);
void JouerTours(char (*plateau)[14],  int dimGrille, joueur j1, joueur j2, int nbrJoueur, int tours);
void acquisitionMot(char* mot, int dimGrille, joueur joueur, char (*plateau)[14], char sens, int x, int y, char* lettresUtilisees, int tours);
void affichageMot(char* mot);
void retirerMot(char plateau[][14], int x, int y, char sens, char* mot, int motFaux);
void retirerIndicePlacement(char plateau[][14], int dimGrille);