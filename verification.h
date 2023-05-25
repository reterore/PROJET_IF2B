//
// Created by lucas on 24/05/2023.
//

#ifndef PROJET_IF2B_2_VERIFICATION_H
#define PROJET_IF2B_2_VERIFICATION_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include "joueur.h"

bool verifLettresMot(char* mot, joueur joueur);
bool verifEmplacement(char sens, int x,int y, char* mot, int dimGrille);
#endif //PROJET_IF2B_2_VERIFICATION_H

