//
//  main.c
//  demineur
//
//  Created by Thomas Faugier on 03/12/2016.
//  Copyright © 2016 Thomas Faugier. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "matrice.h"
#include "shuffle.h"
#include "secure.h"

#ifdef __WIN32__
    #define CLEAR system("cls")
#else /*Le reste, UNIX en particulier*/
    #define CLEAR system("clear")
#endif


int main()
{
    char rep = 0;
    
    do
    {
        int** matrice = NULL;
        int nbrColonnes = 0;
        int nbrLignes = 0;
        int nbrMines = 0;
        int i = 0;
        
        int action = 0;
        int coordx = 0;
        int coordy = 0;
        
        time_t start = 0;
        time_t end = 0;
        
        srand((unsigned int)time(NULL)); //initialisation de rand
        
        CLEAR;
        
        printf("Selectionnez le nombre de colonnes (entre 2 et 50) > ");
        scanf("%d", &nbrColonnes);
        
        //sécurisation saisie du nombre de colonnes
        purger();
        while (nbrColonnes < 2 || nbrColonnes > 51)
        {
            printf("Saisie incorrecte, veuillez choisir un nombre entre 2 et 50 > ");
            scanf("%d", &nbrColonnes);
            purger();
        }
        
        printf("Selectionnez le nombre de lignes > ");
        scanf("%d", &nbrLignes);
        
        //sécurisation saisie du nombre de lignes
        purger();
        while (nbrLignes < 2)
        {
            printf("Saisie incorrecte, veuillez choisir un nombre superieur ou egale a 2 > ");
            scanf("%d", &nbrLignes);
            purger();
        }
        
        printf("Sélectionnez le nombre de mines (entre 1 et %d) > ", (nbrLignes*nbrColonnes)-1);
        scanf("%d", &nbrMines);
        
        //sécurisation saisie du nombre de mines
        purger();
        while (nbrMines < 1 || nbrMines > (nbrLignes*nbrColonnes)-1)
        {
            printf("Saisie incorrecte, veuillez choisir un nombre entre 1 et %d > ", (nbrLignes*nbrColonnes)-1);
            scanf("%d", &nbrMines);
            purger();
        }
        
        //création d'un tableau 2D dynamique
        matrice = (int**)malloc(nbrLignes*sizeof(int*));
        
        secure_malloc((int*)matrice);
        
        for (i=0; i<nbrLignes; i++)
        {
            matrice[i] = malloc(nbrColonnes*sizeof(int));
            
            secure_malloc(matrice[i]);
        }
        
        //initialisation du tableau 2D dynamique à 0
        init_matrice(matrice, nbrColonnes, nbrLignes);
        
        //implémentation des mines dans le tableau 2D dynamique
        init_mines(matrice, nbrColonnes, nbrLignes, nbrMines);
        
        //mélange du tableau 100 fois avec la navette de knuth
        for (i=0; i<100; i++)
        {
            navette_knuth(matrice, nbrColonnes, nbrLignes);
        }
        
        //initialisation des cellules proches des mines
        init_demineur(matrice, nbrColonnes, nbrLignes);
        
        //affichage du démineur initialisé
        printf("\n");
        print_demineur(matrice, nbrColonnes, nbrLignes, nbrMines);
        printf("\n");
        
        //intéraction avec le démineur initialisé
        
        start = time(NULL);
        
        do
        {
            //réinitialisation des variables au début de chaque boucle
            action = 0;
            coordy = 0;
            coordx = 0;
            
            
            
            printf("1) Deminer.\n2) Poser/enlever un drapeau.\n3) Poser/enlever \"?\"\n4) Quitter.\nQue voulez-vous faire ? ");
            scanf("%d", &action);
            
            //sécurisation saisie du choix
            purger();
            while (action < 1 || action > 4)
            {
                printf("Saisie incorrecte, veuillez choisir parmi les choix proposes (1 ou 4) > ");
                scanf("%d", &action);
                purger();
            }
            printf("\n");
            
            if (action == 1 || action == 2 || action == 3) //sélection des coordonnées pour les choix 1,2 et 3
            {
                printf("Choisissez les coordonnees de la case :\nEn abscisse > ");
                scanf("%d", &coordx);
                
                //sécurisation saisie de la coordonnée en abscisse
                purger();
                while (coordx < 1 || coordx > nbrColonnes)
                {
                    printf("Saisie incorrecte, veuillez saisir une coordonnee valide sur l'axe des abcisses > ");
                    scanf("%d", &coordx);
                    purger();
                }
                
                printf("En ordonnee > ");
                scanf("%d", &coordy);
                
                //sécurisation saisie de la coordonnée en ordonnée
                purger();
                while (coordy < 1 || coordy > nbrLignes)
                {
                    printf("Saisie incorrecte, veuillez saisir une coordonnee valide sur l'axe des ordonnees > ");
                    scanf("%d", &coordy);
                    purger();
                }
            }
            else //choix 4
            {
                //action = 0 est utilisée pour quitter la boucle do (autrement dit, pour quitter la partie en cours)
                action = 0;
            }
            
            if (action == 1) //deminer
            {
                if (matrice[coordy-1][coordx-1] == 9) //deminer une case qui contient une bombe
                {
                    CLEAR;
                    print_end_demineur(matrice, nbrColonnes, nbrLignes); //on affiche le tableau complet de la partie terminée
                    end = time(NULL);
                    printf("\n");
                    printf("Vous avez perdu en %d secondes !", (int)(end-start));
                    printf("\n");
                    action = 0; //on quitte la boucle do (autrement dit, on quitte la partie en cours)
                }
                else if (matrice[coordy-1][coordx-1] == 0) //deminer une case vide
                {
                    CLEAR;
                    matrice[coordy-1][coordx-1] += 10; //on affiche la case
                    empty_cell(matrice, coordy-1, coordx-1, nbrColonnes, nbrLignes); //on affiche les cases contigües aux cases vides
                    
                    if (verif_win_demineur(matrice, nbrColonnes, nbrLignes) == 1) //on vérifie que les cases récemment dévoilées n'étaient pas les dernières pour finir la partie
                    {
                        print_end_demineur(matrice, nbrColonnes, nbrLignes); //on affiche le tableau complet de la partie terminée
                        end = time(NULL);
                        printf("\n");
                        printf("Vous avez gagné en %d secondes, et votre score est de %d !", (int)(end-start), score(nbrColonnes, nbrLignes, nbrColonnes)/((int)(end-start)));
                        printf("\n");
                        action = 0; //on quitte la boucle do (autrement dit, on quitte la partie en cours)
                    }
                    else
                    {
                        print_demineur(matrice, nbrColonnes, nbrLignes, nbrMines); //on affiche le tableau après l'action
                    }
                }
                else if (matrice[coordy-1][coordx-1] < 10) //on démine une case qui n'est pas une mine
                {
                    CLEAR;
                    matrice[coordy-1][coordx-1] += 10; //on affiche la case
                    
                    if (verif_win_demineur(matrice, nbrColonnes, nbrLignes) == 1) //on vérifie que la case récemment dévoilée n'était pas la dernière pour finir la partie
                    {
                        print_end_demineur(matrice, nbrColonnes, nbrLignes); //on affiche le tableau complet de la partie terminée
                        end = time(NULL);
                        printf("\n");
                        printf("Vous avez gagné en %d secondes, et votre score est de %d !", (int)(end-start), score(nbrColonnes, nbrLignes, nbrColonnes)/((int)(end-start)));
                        printf("\n");
                        action = 0; //on quitte la boucle do (autrement dit, on quitte la partie en cours)
                    }
                    else
                    {
                        print_demineur(matrice, nbrColonnes, nbrLignes, nbrMines); //on affiche le tableau après l'action
                    }
                }
                else
                {
                    printf("\n");
                    printf("Cellule deja deminee ou occupee.");
                    printf("\n");
                }
                printf("\n");
            }
            else if (action == 2) //placer ou enlever un drapeau
            {
                if (matrice[coordy-1][coordx-1] > 99 && matrice[coordy-1][coordx-1] < 1000) //enlever un drapeau sur une case qui en contient un drapeau
                {
                    CLEAR;
                    matrice[coordy-1][coordx-1] %= 100;
                    print_demineur(matrice, nbrColonnes, nbrLignes, nbrMines); //on affiche le tableau après avoir enlevé le drapeau sur la case
                }
                else if (matrice[coordy-1][coordx-1] < 10) //poser un drapeau sur une case qui n'en contient pas et qui n'est pas déjà affichée (c'est-à-dire déjà déminée)
                {
                    CLEAR;
                    matrice[coordy-1][coordx-1] += 100; //on ajoute 100 à la valeur de la case pour indiquer à l'afficheur que c'est un drapeau
                    
                    if (verif_win_demineur(matrice, nbrColonnes, nbrLignes) == 1) //on vérifie que la case où l'on dépose le drapeau n'était pas la dernière pour finir la partie
                    {
                        print_end_demineur(matrice, nbrColonnes, nbrLignes); //on affiche le tableau complet de la partie terminée
                        end = time(NULL);
                        printf("\n");
                        printf("Vous avez gagné en %d secondes, et votre score est de %d !", (int)(end-start), score(nbrColonnes, nbrLignes, nbrColonnes)/((int)(end-start)));
                        printf("\n");
                        action = 0; //on quitte la boucle do (autrement dit, on quitte la partie en cours)
                    }
                    else
                    {
                        print_demineur(matrice, nbrColonnes, nbrLignes, nbrMines); //on affiche le tableau après l'action
                    }
                }
                else
                {
                    printf("\n");
                    printf("Cellule deja deminee ou occupee.");
                    printf("\n");
                }
                printf("\n");
            }
            else if (action == 3) //pacer ou enlever "?"
            {
                if (matrice[coordy-1][coordx-1] > 999) //enlever un "?" sur une case qui en contient un "?"
                {
                    CLEAR;
                    matrice[coordy-1][coordx-1] %= 1000;
                    print_demineur(matrice, nbrColonnes, nbrLignes, nbrMines); //on affiche le tableau après avoir enlevé le "?" sur la case
                }
                else if (matrice[coordy-1][coordx-1] < 10)
                {
                    CLEAR;
                    matrice[coordy-1][coordx-1] += 1000; //on ajoute 1000 à la valeur de la case pour indiquer à l'afficheur que c'est un "?"
                    print_demineur(matrice, nbrColonnes, nbrLignes, nbrMines); //on affiche le tableau après l'action
                }
                else
                {
                    printf("\n");
                    printf("Cellule deja deminee ou occupee.");
                    printf("\n");
                }
                printf("\n");
            }
            
        } while (action != 0);
        
        printf("Voulez-vous recommencer (o/n) ? ");
        scanf(" %c", &rep);
        
        //sécurisation saisie de la réponse
        while(rep != 'o' && rep != 'n')
        {
            printf("\nVeuillez choisir entre les deux seuls choix autorises (o ou n) > ");
            scanf(" %c", &rep);
        }
        
        free_2D(matrice, nbrLignes); //on libère l'allocation mémoire du tableau 2D de la partie
        
    } while (rep == 'o');
    
    return 0;
}
