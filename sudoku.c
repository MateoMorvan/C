/**
* \brief Programme de jeu SUDOKU
* \author Morvan Mateo
* \version 1.0
* \date 3 Décembre 2023
* Ce programme permet de jouer au jeu du SUDOKU dans l'interface du terminal. 
* Il est possible de choisir la ligne et la colonne où l'on veut placer notre valeur et ainsi de l'insérer.
* La grille du jeu est générer à partir d'un fichier externe qui sera lu à l'aide d'une procédure.
* La grille est afficher et modifier si l'ajout de la valeur est possible.
* Le jeu se termine quand la grille est compléter.
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

/**
* \def TAILLE
* \brief Taille maximale du Tableau de la grille du sudoku
*
* Définie le nombre maximum de valeur à rentrer dans le tableau à deux entrées
*/
#define TAILLE 9

/**
* \def TAILLEBLOC
* \brief Taille maximale d'un bloc de la grille du sudoku qui est de 3*3
*
* C'est le nombre maximum de valeur qui peut y  avoir dans un bloc 
*/
#define TAILLEBLOC 3

const char CROIX[2] = "+"; /**CONSTANTE pour la procédure affiche grille*/
const char COL[2] = "|"; /**CONSTANTE pour la procédure affiche grille*/
const char LIG[10] = "---------"; /**CONSTANTE pour la procédure affiche grille*/
const char ESPACE[10] = " "; /**CONSTANTE pour la procédure affiche grille*/

/**********************************************************/
/*                 Définition des tableaux                */
/**********************************************************/

/**
* \typedef tgrille
* \brief Tableau à double entrée pour la grille du sudoku
*
* Il va stocker les valeurs de la grille du sudoku ainsi que les nouvelles qui vont être ajouter, Il se sera de taille TAILLE*TAILLE (9*9)
*/
typedef int tgrille[TAILLE][TAILLE];


/**
* \fn void chargerGrille(tgrille grille1)
* \brief charge une grille du sudoku venant d'un fichier externe
* \param grille1 : paramètre d'entrée, il est le tableau qui va contenir la grille
*
* insère les valeurs lu du fichier grille et les insères dans le tableau tgrille g afin 
* d'utiliser cette grille comme le début de la grille sudoku pour pouvoir jouer
*/
void chargerGrille(tgrille grille1)
{
    char nomFichier[30];
    FILE *f;
    printf("Nom du fichier ? ");
    scanf("%s", nomFichier); /**saisie du nom du fichier*/
    f = fopen(nomFichier, "rb");  /**Permet de lire le fichier*/
    if (f == NULL)
    {
        printf("\n ERREUR sur le fichier %s\n", nomFichier); /**Affiche une erreur si le fichier n'est pas trouver*/
    }
    else
    {
        fread(grille1, sizeof(int), TAILLE * TAILLE, f); /**insert les valeurs du fichier dans le tableau*/
    }
    fclose(f); /**Ferme le fichier ouvert*/
}

/**********************************************************/
/*                       Affichage                        */
/**********************************************************/

/**
* \fn void affichegrille(tgrille grille1)
* \brief Affiche la grille du sudoku à partir des valeurs du tableau tgrille grille1
* \param grille1 : paramètre d'entrée, il possède les valeurs qui vont être afficher dans le jeu sudoku
*
* Permet d'afficher une grille du sudoku avec les valeurs du tableau tgrille grille1 dedans. Il sera présenter de la même manière 
* qu'un sudoku classique.
*/
void affichegrille(tgrille grille1) 
{
    int ligne, colonne, compteur1, compteur2;
    char c;
    compteur1 = 1;
    printf("\n"); /**retour à la ligne*/
    printf("   "); /** 3 espaces pour placer le nombre de ligne correctement*/
    for (ligne = 0; ligne < TAILLE; ligne++) /**première boucle pour */
    {
        if ((ligne == TAILLEBLOC) || (ligne == 6) || (ligne == TAILLE)) /** affiche le numéro de colonne*/
        {
            printf(" ");
        }

        printf(" %d ", ligne + 1);
    }
    printf("\n");
    printf("  ");
    for (compteur2 = 0; compteur2 < TAILLEBLOC; compteur2++) /** deuxième boucle pour pour écrire la première ligne séparatrice*/
    {
        printf(CROIX);/**écrit une croix*/
        printf(LIG);/**écrit une ligne*/
    }
    printf(CROIX); /**termine la ligne séparatrice avec une croix*/
    printf("\n"); /** on revient à la ligne*/
    for (ligne = 0; ligne < TAILLE; ligne++) /** troisième boucle pour, elle va permettre d'écrire l'intérireur du SUDOKU*/
    {
        for (colonne = 0; colonne < TAILLE; colonne++)
        {
            if (grille1[ligne][colonne] == 0) /** permet de remplacer les 0 par des '.'*/
            {
                c = '.'; 
            }
            else
            {
                c = '0' + grille1[ligne][colonne]; 
            }
            if (colonne == 0) 
            {
                printf("%d | %c ", compteur1, c); /**affiche le numéro de ligne*/
                compteur1 = compteur1 + 1;
            }
            else
            {
                printf(" %c ", c);
            }
            if ((colonne == 2) || (colonne == 5) || (colonne == TAILLE)) /** permet de savoir si quand on met un séparateur de colonne*/
            {
                printf(COL);
            }
        }
        printf(COL); /**écrit un séparateur de colonne à la fin de la ligne*/
        if ((ligne == 2) || (ligne == 5) || (ligne == TAILLE)) /**Permet d'écrire la séparation de ligne*/
        {
            printf("\n");
            printf("  ");
            for (compteur2 = 0; compteur2 < TAILLEBLOC; compteur2++)
            {
                printf(CROIX);
                printf(LIG);
            }
            printf(CROIX);
        }
        printf("\n");
    }
    printf("  ");
    for (compteur2 = 0; compteur2 < TAILLEBLOC; compteur2++) /**écrit le dernier séparateur de ligne à la toute fin*/
    {
        printf(CROIX);
        printf(LIG);
    }
    printf(CROIX);
    printf("\n");
}

/**********************************************************/
/*                        Saisie                          */
/**********************************************************/

/**
* \fn int taille(int val)
* \brief Permet de savoir si la valeur est comprise entre 1 et 9 inclus
* \param val : Il est la valeur saisie par l'utilsateur
* \return on retourne val qui doit être entre 1 et 9 inclus
*
* permet de vérifier la taille de val et redemande la saisie de val si celui ci est trop petit ou trop grand
*/
int taille(int val)
{
    while ((val > TAILLE) || (val < 1)) /**si la valeur est supérieur à 9 ou inférieur à 1, L'utilisateur rentre dans la boucle et doit saisir de nouveau qui doit être entre 1 et 9 inclus pour sortir de la boucle*/
    {
        printf("erreur, la valeur n'est pas entre 1 et 9 veuillez de nouveau saisir : ");
        scanf("%d", &val);
        printf("\n");
    }
    return val;
}

/**
* \fn void saisir(int *val)
* \brief permet la saisie et la vérification de la valeur val saisie par l'utilisateur 
* \param val : paramètre d'entrée/sortie, val est saisie en entrée et peut être modifier donc il est aussi en sortie
*
* permet de saisir une valeur et de la modifier si celle ci n'est pas valable (c'est à dire entre 1 et 9 inclus)
*/
void saisir(int *val)
{
    scanf("%d", *&val);
    *val = taille(*val);
}

/**********************************************************/
/*                   Vérification valeur                  */
/**********************************************************/

/**
* \fn possible(tgrille grille1, int ligne; int colonne, int valeur)
* \brief Fonction booléen qui permet de savoir si la valeur peut être placer dans la case de coordonée ligne et colonne
* \param grille1 : paramètres d'entrée, tableau qui possède toute les valeurs de la grille sudoku
* \param ligne : paramètre d'entrée, Elle est la ligne choisis par l'utilisateur dans la procédure saisie
* \param colonne : paramètre d'entrée, Elle est la colonne choisis par l'utilisateur dans la procédure saisie
* \param valeur : paramètre d'entrée, Elle est la valeur choisis par l'utilisateur pour être insérer dans le tableau grille1 à l'aide
* des coordonées colonne et ligne.
* \return retourne true si la valeur peut être placer et false si ce n'est pas le cas
*/
bool possible(tgrille grille1, int ligne, int colonne, int valeur)
{
    bool res;
    res = true;
    int i, j;

    for (j = 0; j < TAILLE; ++j) /**permet de vérifier si dans la ligne choisis il n'y a pas d'autre valeur égal à la valeur choisis par l'utilisateur*/
    {
        if (grille1[ligne - 1][j] == valeur)
        {
            printf("Erreur, La valeur %d est déjà présente sur la même ligne.\n", valeur);
            res = false;
        }
    }

    for (i = 0; i < TAILLE; ++i) /**permet de vérifier si dans la colonne choisis il n'y a pas d'autre valeur égal à la valeur choisis par l'utilisateur*/
    {
        if (grille1[i][colonne - 1] == valeur)
        {
            printf("Erreur, La valeur %d est déjà présente sur la même colonne.\n", valeur);
            res = false;
        }
    }

    /**permet de vérifier si il n'y a pas le chiffre déjà présent dans le bloc*/
    int LigBloc = ((ligne - 1) / TAILLEBLOC) * TAILLEBLOC; 
    int ColBloc = ((colonne - 1) / TAILLEBLOC) * TAILLEBLOC;
    int x, y;

    for (x = LigBloc; x < LigBloc + TAILLEBLOC; x++)
    {
        for (y = ColBloc; y < ColBloc + TAILLEBLOC; y++)
        {
            if (grille1[x][y] == valeur)
            {
                printf("Erreur, La valeur %d est déjà présente dans le même bloc.\n", valeur);
                res = false;
            }
        }
    }
    return res;
}

/**********************************************************/
/*                       Fin de partie                    */
/**********************************************************/
/**
* \fn int finJeu(tgrille grille1)
* \brief Permet de savoir si la grille du sudoku est complète ou non afin de sortir de la boucle
* \param grille1 : paramètre d'entrée, possède tout les chiffres de la grille sudoku
* \return on retourne 1 si la grille est pleine sinon on retourne 0 si ce n'est pas le cas
*
* permet de finir le jeu du sudoku si la grille du sudoku est complète, le jeu s'arrêtera.
*/
int finJeu(tgrille grille1)
{
    int res;
    res = 1;
    int i, j;
    for (i = 0; i < TAILLE; ++i) 
    {
        for (j = 0; j < TAILLE; ++j)
        {
            if (grille1[i][j] == 0) /**vérifie si tout la cases est égale à 0 ou non.*/
            {
                res = 0;
            }
        }
    }
    return res;
}

/**********************************************************/
/*                   Programme Principale                 */
/**********************************************************/

/**
* \fn int main()
* \brief Programme principal.
* \return Code de sortie du programme (0 : sortie normale).
* 
* Le programme principal permet de mettre de l'ordre dans tout les fonctions et procédures du programme afin qu'il s'éxecute correctement
* Il possède une boucle qui fera tourner en boucle le jeu du sudoku dans que la grille ne sera pas complète. Puis quand elle sera complète
* il affichera un message de fin signalant que la grille est complète.
*/
int main()
{
    tgrille grille1; 
    int numLigne, numColonne, valeur, res;
    chargerGrille(grille1);
    while ((res = finJeu(grille1)) == 0) /**boucle du jeu sudoku*/
    {
        affichegrille(grille1);
        printf("Indices de la case ? ");
        saisir(&numLigne);
        saisir(&numColonne);
        if (grille1[numLigne - 1][numColonne - 1] != 0)
        {
            printf("IMPOSSIBLE, la case n'est pas libre.");
        }
        else
        {
            printf("Valeur à insérer ? ");
            saisir(&valeur);
            if (possible(grille1, numLigne, numColonne, valeur) == true)
            {
                grille1[numLigne - 1][numColonne - 1] = valeur;
            }
        }
    }
    printf("Grille pleine, fin de partie");
    return 0;
}