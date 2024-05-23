#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**
*
* \brief Programme de génération d'une partie de sudoku.
*
* \author Yan Ait ouazzou 1A1
*
* \version 1.0
*
* \date 13 novembre 2023
*
* Ce programme génère une grille permettant de jouer au sudoku.
* Il demande les coordonnées d'une case puis une valeur a insérer dans le tableau 2 dimensions
* représentant le sudoku. Une fois toutes les cases remplies, la partie se termine.
*
*/

/*****************************************************
*              DECLARATION CONSTANTES                *
*                  ET PROTOTYPES                     *
*****************************************************/

/**
 * @def N
 * 
 * @brief constante pour définir les dimensions du tableau.
 * 
 */
#define N 3

/**
 * @def TAILLE
 * 
 * @brief constante pour définir la taille (nombre lignes/colonnes/blocs) du tableau.
 * 
 */
#define TAILLE N*N

/**
 * @def TAILLE_MAX
 * 
 * @brief constante pour la Taille Max du tableau.
 * 
 */
const int TAILLE_MAX = 81;

/**
 * @def CAR_LIGNE
 * 
 * @brief constante pour définir le caractère qui divisera les blocs horizontalement.
 * 
 */
const char CAR_LIGNE[35] = "   +---------+---------+---------+";

/**
 * @def CAR_DIV_HOR
 * 
 * @brief constante pour définir le caractère qui divisera les blocs verticalement.
 * 
 */
const char CAR_DIV_VER = '|';

/**
 * @def VAL_DEF
 * 
 * @brief constante pour définir le caractère à afficher si aucune valeur (0) n'appartient à la case.
 * 
 */
const char VAL_DEF = '.';

/**
 * @brief SEUIL_MIN
 * 
 * @brief constante pour définir le seuil minimale d'une valeur (d'une case/ligne/colonne)
 * 
 */
const int SEUIL_MIN = 1;

/**
 * @brief SEUIL_MAX
 * 
 * @brief constante pour définir le seuil maximale d'une valeur (d'une case/ligne/colonne)
 * 
 */
const int SEUIL_MAX = TAILLE+1;

/**
 * @typedef tGrille
 * 
 * @brief type tableau en 2 dimensions de TAILLE*TAILLE entier.
 * 
 * Le type tGrille sert à créer un tableau 2 dimensions représentant la grille du sudoku.
 * 
 */
typedef int tGrille[TAILLE][TAILLE];



void chargerGrille(tGrille);

int compterCases(tGrille);

void afficherGrille(tGrille);

void saisir(int *);

bool possible(tGrille, int, int, int);

/*****************************************************
*                PROGRAMME PRINCIPAL                 *
*****************************************************/

int main(){
    tGrille grille;
    int numLigne;
    int numColonne;
    int valeur;
    chargerGrille(grille);
    while(compterCases(grille) != TAILLE_MAX){
        afficherGrille(grille);
        printf("Indices de la case ? ");
        saisir(&numLigne);
        saisir(&numColonne);
        numLigne--;  //ajustement pour une indexation basée sur 0
        numColonne--;  //ajustement pour une indexation basée sur 0
        if (grille[numLigne][numColonne] != 0){
            printf("IMPOSSIBLE, la case n'est pas libre.\n");
        } else{
            printf("Valeur a inserer ? ");
            saisir(&valeur);
            if (possible(grille, numLigne, numColonne, valeur)){
                grille[numLigne][numColonne] = valeur;
            }
        }
    }
    printf("\nGrille pleine, fin de partie");
}

/*****************************************************
*              FONCTIONS ET PROCEDURES               *
*****************************************************/

/**
 * @fn void chargerGrille(tGrille g)
 * 
 * @brief Fonction qui initialise une grille de sudoku.
 * 
 * @param g : la grille de sudoku à initialiser
 * 
 * Demande le nom du fichier contenant la grille de sudoku et l'applique au
 * tableau contenant representant la grille du sudoku
 * 
 */
void chargerGrille(tGrille g){
    char nomFichier[30];
    FILE * f;
    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
    if (f==NULL){
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    } else {
        fread(g, sizeof(int), TAILLE*TAILLE, f);
        fclose(f);
    }
}

/**
 * @fn int compterCases(tGrille g)
 * 
 * @brief Fonction qui donne le nombre de cases remplies.
 * 
 * @param g : le tableau 2 dimensions représentant la grille de sudoku
 * 
 * @return le nombre de cases remplies
 * 
 * Parcoure le tableau case par case representant la grille de sudoku et compte le nombre de fois où
 * la valeur d'une case n'est pas '.'
 * 
 */
int compterCases(tGrille g){
    int compte;
    compte = 0;
    for (int i = 0; i < TAILLE; i++){
        for (int j = 0; j < TAILLE; j++){
            if (g[i][j] != 0){
                compte++;
            }
        }
    }
    return compte;
}

/**
 * @fn void afficherGrille(tGrille g)
 * 
 * @brief Affiche la grille de sudoku.
 * 
 * @param g : le tableau 2 dimensions représentant la grille de sudoku
 * 
 * Affiche le tableau 2 dimensions representant la grille de sudoku de manière plus lisible et
 * compréhensible pour l'utilisateur
 * 
 */
void afficherGrille(tGrille g){
    printf("%6d%3d%3d%4d%3d%3d%4d%3d%3d\n", 1, 2, 3, 4, 5, 6, 7, 8, 9);
    printf("%s\n", CAR_LIGNE);
    for (int i = 0; i < TAILLE; i++)
    {
        printf("%d%3c", i+1, CAR_DIV_VER);
        for (int j = 0; j < TAILLE; j++)
        {
            if (g[i][j] == 0)
            {
                printf("%2c ", VAL_DEF);
            } else{
                printf("%2d ", g[i][j]);
            }
            if ((j+1) % 3 == 0){
                printf("%c", CAR_DIV_VER);
            }
        }
        printf("\n");
        if ((i+1) % 3 == 0){
            printf("%s\n", CAR_LIGNE);
        }
    }
}

/**
 * @fn void saisir(x)
 * 
 * @brief Fonction qui permet à l'utilisateur de saisir une valeur.
 * 
 * @param x : la valeur lue, entier compris entre 1 et TAILLE
 * 
 * Demande une valeur à l'utilisateur tant que la valeur n'est pas un entier compris entre 1 et TAILLE
 * 
 */
void saisir(int *x){
    char valeur[10];
    scanf("%s", valeur);
    while ((sscanf(valeur, "%d", &(*x)) == 0) || (*x < SEUIL_MIN || *x > SEUIL_MAX)){
        if (sscanf(valeur, "%d", &(*x)) == 0){
            printf("Le nombre n'est pas un entier ");
            scanf("%s", valeur);
        } else{
            printf("Valeur hors normes, recommencez: ");
            scanf("%s", valeur);
        }
    }
}

/**
 * @fn bool possible(tGrille g, int numL, int numC, int val)
 * 
 * @brief Cette fonction vérifie si une valeur peut être ajoutée dans une case particulière de la grille.
 * 
 * @param g : le tableau 2 dimensions représentant la grille de sudoku
 * @param numL : le numéro de ligne de la case visée
 * @param numC : le numéro de colonne de la case visée
 * @param val : la valeur à insérer dans la grille
 * 
 * @return true si la valeur peut être insérée, false sinon
 * 
 * Vérifie si la valeur peut être ajoutée, elle peut être ajoutée si:
 * - la valeur n’est pas déjà présente sur la même ligne que la case
 * - la valeur n’est pas déjà présente sur la même colonne que la case
 * - la valeur n’est pas déjà présente dans le même bloc que la case
 * 
 */
bool possible(tGrille g, int numL, int numC, int val){
    bool ajout;
    int i;
    int debutLigne;
    int debutColonne;
    int ligne;
    int colonne;
    ajout = true;
    i = 0;
    debutLigne = numL - numL % 3;   //indice de la ligne de la première case du bloc
    debutColonne = numC - numC % 3; //indice de la colonne de la première case du bloc
    ligne = 0;
    colonne = 0;
    //vérifie si la valeur est déjà présente dans la ligne/colonne
    while ((i < TAILLE) && (ajout == true)){
        if ((g[numL][i] == val) || (g[i][numC] == val)){
            ajout = false;
        }
        i++;
    }

    //vérifie si la valeur est déjà présente dans le bloc
    while ((ligne < N) && (ajout == true)){
        colonne = 0;
        while ((colonne < N) && (ajout == true)){
            if (g[debutLigne + ligne][debutColonne + colonne] == val){
                ajout = false;
            }
            colonne++;
        }
        ligne++;
    }

    return ajout;
}