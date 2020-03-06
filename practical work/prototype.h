#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdarg.h>

typedef struct Cell
{
    char *str;
    struct Cell *s;
} Cellule;

typedef Cellule *Liste;

char **fileToText(char *nom, int *i); //Convertit un fichier en tableau de chaîne
void addEndFile(char *nom, char *str); // Ajout en fin de fichier un mot donné
void strIntab(char **tab, char *str, int i); // Affiche les mots du tableau contenant la chaîne donnée
void addIFile(char *nom, char *str, int i); // Ajoute un mot en position i dans le fichier
char **addTab(char **mot, char *str, int i, int *n); // Ajoute un mot dans le tableau à la position i
void triBulle(char **tab, int n); // Tri le tableau de mot avec un tri à bulle
int lexicoTri(const void * a, const void *b); // Fonction pour qsort avec l'ordre lexicographique
int lenTri (const void * a, const void *b); // Fonction pour qsort avec taille puis ordre lexicographique
void triQsort(char **tab, int n,  int (*compar)(const void *, const void *)); //Trie un tableau de mot avec qsort
void catFile(char *nom, char **tab, int n); //Stocke le tableau de mot dans un fichier
int maxScrabble(char **tab, int n, int *nbMot); //Retourne le score maximal selon le score du scrabble
int maxScrabbleFile(char *nom, char **tab, int n, int *nbMot); // Retourne le score maximal selon un fichier donné
char **freeAll(char **tab, int n); //Libère tout le tableau de mot

Liste *init(); //Initialise le tableau de liste
Liste chainInsert(Liste l, char *str); // Ajoute le mot dans la liste afin qu'elle soit rangée de manière lexicographique
Liste *fileToChain(Liste *tab, char *nom); // Transforme un fichier en un tableau de liste chainé
Liste *tabToChain(Liste *tab, char **mot, int n); //Transforme un tableau de chaîne en un tableau de liste
int searchInChain(Liste *tab, char *str); //On cherche un mot dans le tableau de liste
int searchInTab(char **tab, char *str, int n); //Recherche dans le tableau avec recherche par dichotomie
void affChain(Liste *tab, char *str);//Affiche toute les chaines du tableau de liste contenant une autre chaine
void freeChain(Liste l); //On libère une chaîne de manière récursive
Liste *freeTabChain(Liste *tab);//Pour chaque ligne du tableau, on libère la chaîne corespondante