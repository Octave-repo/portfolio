#include "prototype.h"

/* Initialise le tableau de liste */
Liste *init()
{
    Liste *tab;

    tab = malloc(26 * sizeof(Liste *)); // Alloue dynamiquement un tableau de 26 liste (une par lettre de l'alphabet)
    assert(tab);
    for (int i ; i < 26 ; i++) // On parcoure l'entierté du tableau
    {
        tab[i] = malloc(sizeof(Liste)); // On creé une nouvelle liste
        assert(tab[i]);
        tab[i] = NULL; // Que l'on initialise à 0
    }
    return tab;
}

/* Insert dans une liste 'l', une chaîne 'str' */
Liste chainInsert(Liste l, char *str) // Ajoute le mot dans la liste afin qu'elle soit rangée de manière lexicographique
{
    Liste new;
    Liste temp;
    Liste current;

    new = malloc(sizeof(Liste)); // On alloue la place pour la nouvelle cellule
    assert(new);
    new->str = malloc( (1 + strlen(str)) * sizeof(char)); //On alloue de la place pour la chaine dans la cellule
    assert(new->str);
    strcpy(new->str, str);
    current = l;
    if (!l) // Si la liste est vide la nouvelle cellule devient la tête de liste
    {
        new->s = NULL;
        l = new;
        return l;
    }
    while (strcmp(current->str, str) < 0 && current->s) // On parcoure la taille jusqu'à ce que la chaine suivante soit "plus grande" que la chaine à ajouter
        current = current->s;
    if (current == l) //Si la nouvelle cellule est la chaine qui arrive lexicographiquement la première de toute la liste, elle devient tête de liste.
    {
        new->s = current;
        l = new;
    }
    else // Sinon, on l'insert au bon endroit
    {
        temp = current->s;
        current->s = new;
        new->s = temp;
    }
    return l;
}

/* Transforme un fichier de nom 'nom' en un tableau de liste chainé 'tab'*/
Liste *fileToChain(Liste *tab, char *nom)
{
    FILE *f;
    char buffer[1000];

    f = fopen(nom, "r");
    assert(f);
    while(fscanf(f, "%s", buffer) != EOF) // On parcours le fichier
        tab[buffer[0]-65] = chainInsert(tab[buffer[0]-65], buffer); /* En fonction de la première lettre du mot, on insère
le mot dans la bonne liste chainée (indice du tableau 0, lettre 'A', indice du tableau 1, lettre 'B' etc...*/    
    fclose(f);
    return tab;
}

/*Transforme un tableau de chaîne 'mot' de taille 'n' en un tableau de liste 'l'*/
Liste *tabToChain(Liste *tab, char **mot, int n)
{
    for (int i = 0 ; i < n ; i++) // On parcours le tableau de chaine
        tab[mot[i][0]-65] = chainInsert(tab[mot[i][0]-65], mot[i]); // Même chose que la fonction ci dessus, mais insère depuis le tableau de chaîne
    return tab;
}

/* On cherche la chaîne 'str' dans le tableau de liste 'tab' */
int searchInChain(Liste *tab, char *str) 
{
    Liste current;

    current = tab[str[0]- 65]; //On fait la recherche du mot dans le tableau corepsondant à la première lettre du mot
    while (current) //On parcours la liste
    {
        if (!(strcmp(current->str, str))) //Si la chaîne actuelle est la chaîne recherchée, on retourne 1
            return 1;
        current = current->s;
    }
    return 0; // Sinon, on retourne 0
}

/* Recherche la chaîne 'str' dans un tableau 'tab' de taille 'n' par dichotomie retourne 1 si il a été trouvé, 0 sinon*/
int searchInTab(char **tab, char *str, int n) 
{
    int m;
    int j;

    j = 0;
    qsort(tab, n, sizeof(char *), lexicoTri); //On commence par trier le tableau dans l'ordre lexicographique
    while (n >= j) //On fait la recherche par dichotomie
    { 
        m = j + ( n - j) / 2;
        if (!(strcmp(tab[m], str))) 
            return 1; 
        if (strcmp(tab[m],str) < 0) 
            n = m - 1;
        else
            j = m + 1;
    }
    return 0;  
}

/* Affiche toute les chaines du tableau de liste 'tab' contenant une autre chaine 'str' */
void affChain(Liste *tab, char *str)
{
    Liste current;
    for (int i = 0 ; i < 26 ; i++)
    {
        current = tab[i];
        while(current)
        {
            if (strstr(current->str, str))
                printf("%s\n", current->str);
            current = current->s;
        }
    }
}

/* On libère une chaîne de manière récursive */
void freeChain(Liste l)
{
    if (l)
    {
        freeChain(l->s);
        free(l);
    }
}

/* Pour chaque ligne du tableau 'tab', on libère la chaîne corespondante */
Liste *freeTabChain(Liste *tab) 
{
    for (int i = 0 ; i < 26 ; i++)
        freeChain(tab[i]);
    free(tab);
    return NULL;
}