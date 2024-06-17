#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define N 4
#define TAILLE (N * N)

const char CROIX[2] = "+";
const char COL[2] = "|";
const char LIG[15] = "--------------";
const char ESPACE[15] = " ";

typedef int tGrille[TAILLE][TAILLE];

void chargerGrille(tGrille g)
{
    char nomFichier[30];
    FILE *f;
    printf("Nom du fichier ? ");
    scanf("%s", nomFichier);
    f = fopen(nomFichier, "rb");
    if (f == NULL)
    {
        printf("\n ERREUR sur le fichier %s\n", nomFichier);
    }
    else
    {
        fread(g, sizeof(int), TAILLE * TAILLE, f);
    }
    fclose(f);
}

void affichegrille(tGrille g)
{
    int ligne, colonne, compteur1, compteur2;
    printf("\n");
    printf("    ");

    for (ligne = 0; ligne < TAILLE; ligne++)
    {
        if ((ligne == N) || (ligne == N * 2) || (ligne == N * 3) || (ligne == TAILLE))
        {
            printf("   ");
        }
        if (ligne < 10)
        {
            printf("  %d", ligne + 1);
        }
        else
        {

            printf(" %d", ligne + 1);
        }
    }
    printf("\n");
    printf("   ");
    // 1er ligne avec croix
    for (compteur1 = 0; compteur1 < N; compteur1++)
    {
        printf(CROIX);
        printf(LIG);
    }
    printf(CROIX);
    printf("\n");
    //
    compteur1 = 1;
    for (ligne = 0; ligne < TAILLE; ligne++)
    {
        if (compteur1 > 9)
        {
            printf("%d | ", compteur1);
            compteur1 = compteur1 + 1;
        }
        if (compteur1 < 10)
        {
            printf("%d  | ", compteur1);
            compteur1 = compteur1 + 1;
        }
        for (colonne = 0; colonne < TAILLE; colonne++)
        {
            if (g[ligne][colonne] != 0 && g[ligne][colonne] > 9)
            {
                printf("%d ", g[ligne][colonne]);
            }
            else if (g[ligne][colonne] != 0 && g[ligne][colonne] < 10)
            {
                printf(" %d ", g[ligne][colonne]);
            }
            else
            {
                printf(" . ");
            }

            if ((colonne == N - 1) || (colonne == (N * 2 - 1)) || (colonne == (N * 3 - 1)) || (colonne == TAILLE - 1))
            {
                printf(" | ");
            }
        }
        printf("\n");
        if ((ligne == N - 1) || (ligne == (N * 2 - 1)) || (ligne == (N * 3 - 1)) || (ligne == TAILLE - 1))
        {
            printf("   ");
            for (compteur2 = 0; compteur2 < N; compteur2++)
            {
                printf(CROIX);
                printf(LIG);
            }
            printf(CROIX);
            printf("\n");
        }
    }
}

bool absentSurLigne(int val, tGrille g, int ligID)
{
    int i;
    for (i = 0; i < TAILLE; i++)
    {
        if (val == g[ligID][i])
        {
            return false;
        }
    }
    return true;
}

bool absentSurColonne(int val, tGrille g, int colID)
{
    int i;
    for (i = 0; i < TAILLE; i++)
    {
        if (val == g[i][colID])
        {
            return false;
        }
    }
    return true;
}

bool absentSurBloc(int val, tGrille g, int i, int j)
{
    int ligneBloc = i / N;
    int colloneBloc = j / N;
    int initialx, initialy, x, y;
    initialx = ligneBloc * N;
    initialy = colloneBloc * N;
    for (x = initialx; x < initialx + N; x++)
    {
        for (y = initialy; y < initialy + N; y++)
        {
            if (g[x][y] == val)
            {
                return false;
            }
        }
    }

    return true;
}

bool backtracking(tGrille grille, int numeroCase)
{
    int ligne, colonne;
    bool resultat = false;

    if (numeroCase == TAILLE * TAILLE)
    {
        // Toutes les cases sont traitées, la grille est résolue
        return true;
    }
    else
    {
        // Calcul des coordonnées de la case
        ligne = numeroCase / TAILLE;
        colonne = numeroCase % TAILLE;

        if (grille[ligne][colonne] != 0)
        {
            // La case n'est pas vide, passer à la suivante (appel récursif)
            resultat = backtracking(grille, numeroCase + 1);
        }
        else
        {
            // La case est vide, essayer toutes les valeurs possibles
            for (int valeur = 1; valeur <= TAILLE; ++valeur)
            {
                if (absentSurLigne(valeur, grille, ligne) &&
                    absentSurColonne(valeur, grille, colonne) &&
                    absentSurBloc(valeur, grille, ligne, colonne))
                {

                    // La valeur est autorisée, l'assigner à la case
                    grille[ligne][colonne] = valeur;

                    // Appel récursif pour vérifier si ce choix est bon par la suite
                    if (backtracking(grille, numeroCase + 1))
                    {
                        resultat = true;
                    }
                    else
                    {
                        // Annuler l'assignation si le choix n'est pas bon
                        grille[ligne][colonne] = 0;
                    }
                }
            }
        }
        return resultat;
    }
}


int main()
{
    tGrille g;
    int numeroCase;
    numeroCase = 0;
    chargerGrille(g);
    printf("Grille initial : ");
    affichegrille(g);
    clock_t begin = clock(); 
    backtracking(g, numeroCase);
    clock_t end = clock();
     printf("Grille finale : ");
    affichegrille(g);
    double tmpsCPU = (end - begin) * 1.0 / CLOCKS_PER_SEC;
    printf("Temps CPU = %.6f secondes\n", tmpsCPU);
    return 0;
}
