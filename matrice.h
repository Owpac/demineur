//
//  matrice.h
//  demineur
//
//  Created by Thomas Faugier on 16/12/2016.
//  Copyright © 2016 Thomas Faugier. All rights reserved.
//

#ifndef matrice_h
#define matrice_h

#include <stdio.h>

void init_matrice(int** matrice, int nbrColonnes, int nbrLignes);
void init_mines(int** matrice, int nbrColonnes, int nbrLignes, int nbrMines);
void init_demineur(int** matrice, int nbrColonnes, int nbrLignes);
void print_demineur(int** matrice, int nbrColonnes, int nbrLignes, int nbrMines);
void empty_cell(int** matrice, int coordy, int coordx, int nbrColonnes, int nbrLignes);
void print_demineur(int** matrice, int nbrColonnes, int nbrLignes, int nbrMines);
void print_end_demineur(int** matrice, int nbrColonnes, int nbrLignes);
int verif_win_demineur(int** matrice, int nbrColonnes, int nbrLignes);
int compteur_mines(int** matrice, int nbrColonnes, int nbrLignes, int nbrMines);
int score(int nbrColonnes, int nbrLignes, int nbrMines);
void print_matrice(char* label, int** matrice, int nbrColonnes, int nbrLignes);

#endif /* matrice_h */
