//
//  secure.h
//  demineur
//
//  Created by Thomas Faugier on 15/12/2016.
//  Copyright © 2016 Thomas Faugier. All rights reserved.
//

#ifndef secure_h
#define secure_h

#include <stdio.h>
#include <stdlib.h>

int secure_malloc (int* ptr);
void purger();
void free_2D(int** matrice, int nbrLignes);

#endif /* secure_h */
