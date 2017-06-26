//
//  shuffle.h
//  demineur
//
//  Created by Thomas Faugier on 10/12/2016.
//  Copyright © 2016 Thomas Faugier. All rights reserved.
//

#ifndef shuffle_h
#define shuffle_h

#include <stdio.h>
#include <stdlib.h>

void navette_knuth(int** tab, int nbrColonnes, int nbrLignes);
int nbr_aleatoire(int min, int max);
void swap(int** tab, int nbrColonnes, int cellule, int celluleAleatoire);

#endif /* shuffle_h */
