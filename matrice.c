//
//  matrice.c
//  demineur
//
//  Created by Thomas Faugier on 16/12/2016.
//  Copyright © 2016 Thomas Faugier. All rights reserved.
//

#include "matrice.h"


//fonction qui initialise toutes les cases du tableau 2D dynamique à 0
void init_matrice(int** matrice, int nbrColonnes, int nbrLignes)
{
    int i = 0;
    int j = 0;
    
    for (i=0; i<nbrLignes; i++)
    {
        for (j=0; j<nbrColonnes; j++)
        {
            matrice[i][j] = 0;
        }
    }
    
    return;
}


//fonction qui implémente les mines dans le tableau 2D dynamique
void init_mines(int** matrice, int nbrColonnes, int nbrLignes, int nbrMines)
{
    int i = 0;
    int j = 0;
    
    for (i=0; i<nbrLignes; i++)
    {
        for (j=0; j<nbrColonnes; j++)
        {
            matrice[i][j] = 9;
            nbrMines--;
            
            if (nbrMines == 0)
            {
                return;
            }
        }
    }
    
    return;
}

//fonction qui initialise les cases proches des mines
void init_demineur(int** matrice, int nbrColonnes, int nbrLignes)
{
    int i = 0;
    int j = 0;
    
    for (i=0; i<nbrLignes; i++)
    {
        for (j=0; j<nbrColonnes; j++)
        {
            if (matrice[i][j] == 9)
            {
                if (i>0 && j>0 && matrice[i-1][j-1] != 9) //case haut droite
                {
                    matrice[i-1][j-1]++;
                }
                
                if (i>0 && matrice[i-1][j] != 9) //case haut
                {
                    matrice[i-1][j]++;
                }
                
                if (i>0 && j<nbrColonnes-1 && matrice[i-1][j+1] != 9) //case haut droite
                {
                    matrice[i-1][j+1]++;
                }
                
                if (j<nbrColonnes-1 && matrice[i][j+1] != 9) //case droite
                {
                    matrice[i][j+1]++;
                }
                
                if (i<nbrLignes-1 && j<nbrColonnes-1 && matrice[i+1][j+1] != 9) //case bas droite
                {
                    matrice[i+1][j+1]++;
                }
                
                if (i<nbrLignes-1 && matrice[i+1][j] != 9) //case bas
                {
                    matrice[i+1][j]++;
                }
                
                if (i<nbrLignes-1 && j>0 && matrice[i+1][j-1] != 9) //case bas gauche
                {
                    matrice[i+1][j-1]++;
                }
                
                if (j>0 && matrice[i][j-1] != 9) //case gauche
                {
                    matrice[i][j-1]++;
                }
            }
        }
    }
    
    return;
}


//fonction qui affiche les cases contigües aux cases vides
void empty_cell(int** matrice, int coordy, int coordx, int nbrColonnes, int nbrLignes)
{
    if (coordy>0 && coordx>0 && matrice[coordy-1][coordx-1]%100 < 9) //case haut gauche
    {
        matrice[coordy-1][coordx-1] = matrice[coordy-1][coordx-1]%100 + 10;
        
        if (matrice[coordy-1][coordx-1] == 10)
        {
            empty_cell(matrice, coordy-1, coordx-1, nbrColonnes, nbrLignes);
        }
    }
    
    if (coordy>0 && matrice[coordy-1][coordx]%100 < 9) //case haut
    {
        matrice[coordy-1][coordx] = matrice[coordy-1][coordx]%100 + 10;
        
        if (matrice[coordy-1][coordx] == 10)
        {
            empty_cell(matrice, coordy-1, coordx, nbrColonnes, nbrLignes);
        }
    }
    
    if (coordy>0 && coordx<nbrColonnes-1 && matrice[coordy-1][coordx+1]%100 < 9) //case haut droite
    {
        matrice[coordy-1][coordx+1] = matrice[coordy-1][coordx+1]%100 + 10;
        
        if (matrice[coordy-1][coordx+1] == 10)
        {
            empty_cell(matrice, coordy-1, coordx+1, nbrColonnes, nbrLignes);
        }
    }
    
    if (coordx<nbrColonnes-1 && matrice[coordy][coordx+1]%100 < 9) //case droite
    {
        matrice[coordy][coordx+1] = matrice[coordy][coordx+1]%100 + 10;
        
        if (matrice[coordy][coordx+1] == 10)
        {
            empty_cell(matrice, coordy, coordx+1, nbrColonnes, nbrLignes);
        }
    }
    
    if (coordy<nbrLignes-1 && coordx<nbrColonnes-1 && matrice[coordy+1][coordx+1]%100 < 9) //case bas droite
    {
        matrice[coordy+1][coordx+1] = matrice[coordy+1][coordx+1]%100 + 10;
        
        if (matrice[coordy+1][coordx+1] == 10)
        {
            empty_cell(matrice, coordy+1, coordx+1, nbrColonnes, nbrLignes);
        }
    }
    
    if (coordy<nbrLignes-1 && matrice[coordy+1][coordx]%100 < 9) //case bas
    {
        matrice[coordy+1][coordx] = matrice[coordy+1][coordx]%100 + 10;
        
        if (matrice[coordy+1][coordx] == 10)
        {
            empty_cell(matrice, coordy+1, coordx, nbrColonnes, nbrLignes);
        }
    }
    
    if (coordy<nbrLignes-1 && coordx>0 && matrice[coordy+1][coordx-1]%100 < 9) //case bas gauche
    {
        matrice[coordy+1][coordx-1] = matrice[coordy+1][coordx-1]%100 + 10;
        
        if (matrice[coordy+1][coordx-1] == 10)
        {
            empty_cell(matrice, coordy+1, coordx-1, nbrColonnes, nbrLignes);
        }
    }
    
    if (coordx>0 && matrice[coordy][coordx-1]%100 < 9) //case gauche
    {
        matrice[coordy][coordx-1] = matrice[coordy][coordx-1]%100 + 10;
        
        if (matrice[coordy][coordx-1] == 10)
        {
            empty_cell(matrice, coordy, coordx-1, nbrColonnes, nbrLignes);
        }
    }
    
    return;
}


//fonction qui affiche le tableau de la partie en cours
void print_demineur(int** matrice, int nbrColonnes, int nbrLignes, int nbrMines)
{
    int i = 0;
    int j = 0;
    int n = 0;
    
    for (i=0; i<nbrLignes; i++)
    {
        if (i == 0) //affichage numéro de colonne
        {
            printf("   |");
            
            for (n=0; n<nbrColonnes; n++) //adaptation du nombre de caractères en fonction du numéro
            {
                if (n+1<10)
                {
                    printf(" %d |", n+1);
                }
                else if (n+1<100)
                {
                    printf("%d |", n+1);
                }
                else if (n+1<1000)
                {
                    printf("%d|", n+1);
                }
            }
            printf("\n");
        }
        
        for (n=0; n<nbrColonnes+1; n++) //affichage tirets entre lignes
        {
            printf("----");
        }
        printf("\n");
        
        //affichage numéro de ligne
        if (i+1<10) //adaptation du nombre de caractères en fonction du numéro
        {
            printf(" %d ", i+1);
        }
        else if (i+1<100)
        {
            printf("%d ", i+1);
        }
        else
        {
            printf("%d", i+1);
        }
        
        for (j=0; j<nbrColonnes; j++) //affichage des cases
        {
            printf("|");
            if (matrice[i][j] < 10) //case non affichée
            {
                printf("   ");
            }
            else if (matrice[i][j] > 9 && matrice[i][j] < 100) //case déminée et à afficher
            {
                printf(" %d ", matrice[i][j]%10);
            }
            else if (matrice[i][j] > 99 && matrice[i][j] < 1000) //case avec drapeau
            {
                printf(" X ");
            }
            else if (matrice[i][j] > 999) //case avec "?"
            {
                printf(" ? ");
            }
        }
        printf("|\n");
    }
    
    printf("\nNombre de mines restantes : %d.\n", compteur_mines(matrice, nbrColonnes, nbrLignes, nbrMines));
    
    return;
}


//fonction qui affiche le tableau complet de la partie terminée
void print_end_demineur(int** matrice, int nbrColonnes, int nbrLignes)
{
    int i = 0;
    int j = 0;
    int n = 0;
    
    for (i=0; i<nbrLignes; i++)
    {
        if (i == 0) //affichage numéro de colonne
        {
            printf("   |");
            for (n=0; n<nbrColonnes; n++) //adaptation du nombre de caractères en fonction du numéro
            {
                if (n+1<10)
                {
                    printf(" %d |", n+1);
                }
                else if (n+1<100)
                {
                    printf("%d |", n+1);
                }
                else if (n+1<1000)
                {
                    printf("%d|", n+1);
                }
            }
            printf("\n");
        }
        
        for (n=0; n<nbrColonnes+1; n++) //affichage tirets entre lignes
        {
            printf("----");
        }
        printf("\n");
        
        //affichage numéro de ligne
        if (i+1<10) //adaptation du nombre de caractères en fonction du numéro
        {
            printf(" %d ", i+1);
        }
        else if (i+1<100)
        {
            printf("%d ", i+1);
        }
        else
        {
            printf("%d", i+1);
        }
        
        for (j=0; j<nbrColonnes; j++)
        {
            printf("|");
            
            if (matrice[i][j] == 9) //case contenant une mine
            {
                printf(" * ");
            }
            else if (matrice[i][j] < 9) //case ne contenant ni mines ni drapeaux
            {
                printf(" %d ", matrice[i][j]);
            }
            else if (matrice[i][j] > 9 && matrice[i][j] < 100) //case ne contenant ni mines ni drapeaux mais étant déjà déjà deminée et affichée
            {
                printf(" %d ", matrice[i][j]%10);
            }
            else if (matrice[i][j] > 99 && matrice[i][j]%100 != 9) //case contenant un drapeau mais pas de mines
            {
                printf(" %d ", matrice[i][j]%100);
            }
            else if (matrice[i][j] > 99 && matrice[i][j]%100 == 9) //case contenant un drapeau et une mine
            {
                printf(" * ");
            }
        }
        printf("|\n");
    }
    
    return;
}


//fonction qui vérifie si la partie est terminée ou non
int verif_win_demineur(int** matrice, int nbrColonnes, int nbrLignes)
{
    int i = 0;
    int j = 0;
    
    for (i=0; i<nbrLignes; i++) {
            for (j=0; j<nbrColonnes; j++) {
                if(matrice[i][j] < 10 || matrice[i][j] > 999 || (matrice[i][j] > 99 && matrice[i][j]%100 != 9))
                {
                    return 0; //pas gagné
                }
            }
        }
    
    return 1; //gagné
}


//fonction qui compte le nombre restant de mines par rapport au nombre de drapeaux posés
int compteur_mines(int** matrice, int nbrColonnes, int nbrLignes, int nbrMines)
{
    int i = 0;
    int j = 0;
    
    for (i=0; i<nbrLignes; i++)
    {
        for (j=0; j<nbrColonnes; j++)
        {
            if (matrice[i][j] > 99 && matrice[i][j] < 1000) //Si la case est un drapeau, on retire 1 au nombre total de mines de la matrice
            {
                nbrMines--;
            }
        }
    }
    
    return nbrMines;
}


int score(int nbrColonnes, int nbrLignes, int nbrMines)
{
    int taille = 0;
    int scoreMines= 0;
    
    taille = nbrColonnes*nbrLignes;
    scoreMines = 10*nbrMines*(taille-1); //taille-1 est le nombre maximum de mines que peut avoir le démineur
    
    return scoreMines;
}


//fonction qui affiche un tableau 2D avec un message de description
void print_matrice(char* label, int** matrice, int nbrColonnes, int nbrLignes)
{
    int i = 0;
    int j = 0;
    
    if (label)
    {
        printf("\n%s : \n", label);
    }
    
    for (i=0; i<nbrLignes; i++)
    {
        for (j=0; j<nbrColonnes; j++)
        {
            printf(" | %d", matrice[i][j]);
        }
        printf(" |\n");
    }
    
    return;
}
