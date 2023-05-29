cmake_minimum_required(VERSION 3.24)
project(PROJET_IF2B C)

set(CMAKE_C_STANDARD 99)

add_executable(PROJET_IF2B main.c plateau.c plateau.h joueur.c joueur.h verification.c verification.h JeuDeLettre.c JeuDeLettre.h)
