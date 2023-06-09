//
// Created by lucas on 24/05/2023.
//

#ifndef PROJET_IF2B_2_VERIFICATION_H
#define PROJET_IF2B_2_VERIFICATION_H

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "joueur.h"

bool verifLettresMot(char* lettresUtilisees, joueur* joueur);
bool verifierPlacement(const char plateau[][14], int x, int y, char sens, char* mot, char* lettresUtilisees);
bool verificationJoker(char* mot);
bool verifierPositionInitial(char plateau[][14], int x, int y);
bool rechercheMotFichier(char* fichier, char* mot);
bool grilleBonne(char grille[][14], char* fichier, int dimGrille, int* motFaux);
bool contactAvecMotsExistants(char plateau[][14], char* mot, char sens, int x, int y, int tours, int* motFaux);
bool mainVide(joueur joueur, int tours, int numJoueur);
bool verifTemps(joueur* joueurActif, long long tempsDebut, long long tempsFin);

#endif //PROJET_IF2B_2_VERIFICATION_H

