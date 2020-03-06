#include "prototype.h"

/* Fonction de l'exercice 1, convertit les données du fichier en un tableau de chaine
prend en paramètre le nom du fichier ainsi qu'un pointeur sur i qui contiendra la taille du tableau*/
char **fileToText(char *nom, int *i)
{
    FILE *f;
    char **tab;
    char buffer[1000];

    *i = 0;
    f = fopen(nom, "r");
    assert(f);
    while (fscanf(f, "%s", buffer) != EOF) //On compte le nombre de mot dans le fichier
        *i = *i +1;
    assert(*i);
    tab = (char **)malloc((*i) * sizeof(char *)); //On assigne le bon nombre de mot dans le fichier
    assert(tab);

    fclose(f);
    f = fopen(nom, "r");
    assert(f);
    for (int n = 0 ; n < *i ; n++) //Pour chaque mot on assigne le bon nombre de lettre
    {
        fscanf(f, "%s", buffer);
        tab[n] = (char *) malloc((strlen(buffer) + 1) * sizeof(char));
        assert(tab[n]);
        strcpy(tab[n], buffer);
    }
    fclose(f);
    return tab;
}
/* Ajoute un mot à la fin du fichier
nom : le nom du fichier ; str : le mot à ajouter */
void addEndFile(char *nom, char *str)
{
    FILE *f;

    f = fopen(nom, "a");
    assert(f);
    fprintf(f, "%s\n", str); // Fonctionne sur Linux, cependant, il semble que sur windows le format doit être "\n%s"
    fclose(f);
}


/* Affiche tout les mots dans le tableau 'tab' de taille 'i' de la chaine donnée 'str'
*/
void strIntab(char **tab, char *str, int i)
{
    int n;

    for (n = 0 ; n < i ; n ++)
    {
        if (strstr(tab[n], str))
            printf("%s\n", tab[n]);
    }
}

/*
Ajoute dans le fichier 'nom' le mot 'str' à la position 'i'
*/
void addIFile(char *nom, char *str, int i)
{
    int n;
    int j;
    FILE *f;
    char **tab;

    tab = fileToText(nom, &n);
    if (i <= 0 || i > n)
        fprintf(stderr, "Position invalide\n");
    else
    {
        f = fopen("temp.txt", "w");
        assert(f);
        for (j = 0 ; j < n ; j ++)
        {
            if ((j + 1) == i)
                fprintf(f, "%s\n", str);
            fprintf(f, "%s\n", tab[j]);
        }
        fclose(f);
        remove(nom);
        rename("temp.txt", nom);
    }
}

/*
Retourne un tableau de chaine
Il s'agit du tableau 'mot' de taille 'n' auquel on ajoute le mot 'str' à la position 'i'
*/
char **addTab(char **mot, char *str, int i, int *n)
{
    int j;

    j = *n;
    if (i < 0 || i > *n)
        fprintf(stderr, "Position invalide\n");
    mot = realloc(mot, (((*n)+1) * sizeof(char *)));
    assert(mot);
    while (j > i)
    {
        if (j)
            mot[j] = mot[j-1];
        j--;
    }
    mot[j] = realloc(mot[j], (strlen(str) + 1) * sizeof(char));
    strcpy(mot[j], str);
    *n = *n+1;
    return mot;
}

/*
Tri le tableau 'tab' de taille 'n' dans l'ordre lexicographique avec la méthode du tri à bulle (longue)
*/
void triBulle(char **tab, int n)
{
    int i;
    int bool;
    int act;
    char *temp;

    i = 0;
    bool = 1;
    while (bool)
    {
        bool = 0;
        i ++;
        for (act = 0 ; act < n - i ; act++)
        {
            if (strcmp(tab[act], tab[act+1]) > 0)
            {
                bool = 1;
                temp = tab[act];
                tab[act] = tab[act+1];
                tab[act+1] = temp;
            }
        }
    }
    printf("Durée d'éxecution : %.3f secondes.\n", (float)clock()/CLOCKS_PER_SEC);
}

/* Fonction de tri lexicograpgique de qsort */
int lexicoTri(const void * a, const void *b)
{
    return strcmp(* (char * const *) a, * (char * const *) b);
}

/* Fonction de tri par taille de qsort*/
int lenTri (const void * a, const void *b)
{
    if (strlen(* (char * const *) a) == strlen(* (char * const *) b))
        return (lexicoTri(a, b));
    else
    {
        return (strlen(* (char * const *) a) - strlen(* (char * const *) b));
    }
    
}

/* Fonction qui trie en grâce à qsort
*/
void triQsort(char **tab, int n,  int (*compar)(const void *, const void *))
{
    qsort(tab, n, sizeof(char *), compar);
    printf("Durée d'éxecution : %.3f secondes.\n", (float)clock()/CLOCKS_PER_SEC);
}

/*
Stocke un tableau de mot 'tab' de taille 'i' dans un fichier de nom 'nom'
*/
void catFile(char *nom, char **tab, int n)
{
    int j;
    FILE *f;

    if (n <= 0)
        fprintf(stderr, "Position invalide\n");
    else
    {
        f = fopen(nom, "w");
        assert(f);
        for (j = 0 ; j < n ; j ++)
        {
            fprintf(f, "%s\n", tab[j]);
        }
        fclose(f);
    }
}

/* Retourne le score maximal d'un tableau 'tab' de taille 'n' selon les règles du scrabble
 'nbMot' correspond au nombre de mot ayant le score maximal */
int maxScrabble(char **tab, int n, int *nbMot)
{
    int i;
    int total;
    int max;
    int mot[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 10, 1, 2, 1, 1, 3, 8, 1 ,1, 1, 1, 4, 10, 10, 10, 10};

    max = 0;
    *nbMot = 0;
    for (i = 0 ; i < n ; i++)
    {
        total = 0;
        while (*tab[i])
        {
            if (*tab[i] >= 'A' && *tab[i] <= 'Z')
            {
                total += mot[(*tab[i]) - 65];
            }
            tab[i]++;
        }
        if (total == max)
            *nbMot = *nbMot + 1;
        if (total > max)
        {
            max = total;
            *nbMot = 1;
        }
    }
    return max;
}

/* Retourne le score maximal d'un tableau 'tab' de taille 'n' selon le score d'un fichier 'nom'
 'nbMot' correspond au nombre de mot ayant le score maximal */
int maxScrabbleFile(char *nom, char **tab, int n, int *nbMot)
{
    FILE *f;
    int max;
    int total;
    int i;
    int mot[26] = {0};
    char buffer[255];

    *nbMot = 0;
    f = fopen(nom, "r");
    assert(f);
    while(fscanf(f, "%s", buffer) != EOF)
    {
        i = buffer[0] - 97;
        fscanf(f, "%s", buffer);
        mot[i] = atoi(buffer);
    }
    fclose(f);
    max = 0;
    for (i = 0 ; i < n ; i++)
    {
        total = 0;
        while (*tab[i])
        {
            if (*tab[i] >= 'A' && *tab[i] <= 'Z')
                total += mot[(*tab[i]) - 65];
            tab[i]++;
        }
        if (total == max)
            *nbMot = *nbMot + 1;
        if (total > max)
        {
            max = total;
            *nbMot = 1;
        }
    }
    return max;
}

/* Libère un tableau de chaîne 'tab' de taille 'n' */
char **freeAll(char **tab, int n)
{
    int i;
    for (i = 0 ; i < n ;i++)
        free(tab[i]);
    free(tab);
    return NULL;
}