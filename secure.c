//
//  secure.c
//  demineur
//
//  Created by Thomas Faugier on 15/12/2016.
//  Copyright © 2016 Thomas Faugier. All rights reserved.
//

#include "secure.h"

//sécurisation de l'allocation mémoire dynamique
int secure_malloc (int* ptr)
{
    if (ptr == NULL) // On vérifie si l'allocation n'a pas fonctionné
    {
        printf("Erreur, mémoire insuffisante.");
        exit(0); // L'allocation n'a pas fonctionnée, on arrête tout
    }
    
    return 1; // L'allocation a fonctionné
}

//sécurisation de la saisie de caractère dans un scanf destiné aux nombres
void purger()
{
    char c;
    
    while ((c = getchar()) != '\n' && c != EOF);
    
    return;
}

//fonction qui libère l'allocation mémoire d'un tableau 2D
void free_2D(int** matrice, int nbrLignes)
{
    int i = 0;
    
    for(i=0; i<nbrLignes; i++)
    {
        free(matrice[i]); //libérer la ième ligne
    }
    
    free(matrice);
    
    return;
}
