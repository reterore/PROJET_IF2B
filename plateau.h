//
// Created by lucas on 16/05/2023.
//

#ifndef PROJET_IF2B_PLATEAU_H
#define PROJET_IF2B_PLATEAU_H

#endif //PROJET_IF2B_PLATEAU_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>




void initGrille(int dimGrille, char plateau[][dimGrille]);
void affichageGrille(int dimGrille, char plateau[][dimGrille]);


int acquisitionDimGrille();
int acquisitionTemps();
int partie(int nbrJoueur, int dimGrille, int temps);
