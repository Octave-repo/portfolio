#include "prototype.h"

char *creStr(char *ch, ...)
{
    va_list p;
    char *str;
    char *buffer;
    
    va_start(p, ch);
    str = malloc((strlen(ch) + 1) * sizeof(char));
    strcpy(str, ch);
    buffer = va_arg(p, char *);
    while (strcmp(buffer, "."))
    {
        str = realloc(str, (strlen(str) + 1) * sizeof(buffer));
        strcat(str, " ");
        strcat(str, buffer);
        buffer = va_arg(p, char *);
    }
    va_end(p);
    strcat(str, ".");
    return str;

}

char **part1(int *i)
{
    int n;
    char nom[255];
    char mot[255];
    int misc;
    char **tab; 

    tab = NULL;
    n = -1;
    *i = 0;
    while (n)
    {
        printf("╞═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╡\n");
        printf("\t* Création d'un tableau de mot (1)\n\t* Chercher une chaîne dans le tableau (2)\n\t* Ajouter un mot à la fin du fichier (3)");
        printf("\n\t* Ajouter dans le fichier à la position i (4)\n\t* Ajoute un mot dans le tableau à la position i (5)\n\t* Trier le tableau ");
        printf(" avec le tri à bulle (6)\n\t* Trier le tableau avec qsort (7)\n\t* Recopie le tableau de mot dans un fichier (8)\n\t* Afficher le nombre de");
        printf(" mot avec le plus haut score et le plus haut score selon le barème du scrabble (9)\n\t* Afficher le nombre de");
        printf(" mot avec le plus haut score et le plus haut score selon le barème du fichier (10)\n\t* Libérer le tableau de mot (11)\n");
        printf("\t* Retour en arrière (0)\n");
        printf("╞═════════════════════════════════════════════════════════════════════════════════════════════════════════════════════════╡\n");
        printf("\t* Choisisez votre fonctionalité: ");
        n = -1;
        scanf("%d", &n);
        getc(stdin);
        switch (n)
        {
            case 1 :
            {
                printf("\t* Nom du fichier : ");
                scanf("%s", nom);
                tab = fileToText(nom, i);
                printf("\t* Le tableau à été crée\n");
            } break;

            case 2 :
            {
                if (!tab)
                    fprintf(stderr, "\t* Attention le tableau est vide !\n");
                printf("\t* Chaîne a rechercher : ");
                scanf("%s", mot);
                printf("\t* Mot contenant le chaîne %s :\n", mot);
                strIntab(tab, mot, *i);
                printf("\n");
            } break ;

            case 3 :
            {
                printf("\t* Mot à ajouter : ");
                scanf("%s", mot);
                printf("\t* Nom du fichier : ");
                scanf("%s", nom);
                addEndFile(nom, mot);
                printf("\t* Le mot à été ajouter à la fin du fichier\n");
            } break;

            case 4 :
            {
                printf("\t* Mot à ajouter : ");
                scanf("%s", mot);
                printf("\t* Nom du fichier : ");
                scanf("%s", nom);
                printf("\t* Position : ");
                scanf("%d", &misc);
                getc(stdin);
                addIFile(nom, mot, misc);
                printf("\t* Le mot à été ajouter à la position %d du fichier\n", misc);
            } break;

            case 5 :
            {
                if (!tab)
                    fprintf(stderr, "\t* Attention le tableau est vide !\n");
                printf("\t* Mot à ajouter : ");
                scanf("%s", mot);
                printf("\t* Position : ");
                scanf("%d", &misc);
                getc(stdin);
                tab = addTab(tab, mot, misc, i);
                printf("\t* Le mot à été ajouter à la position %d du tableau\n", misc);
            } break;

            case 6 :
            {
                if (!tab)
                    fprintf(stderr, "\t* Attention le tableau est vide !\n");
                printf("\t* Attention, la vitesse d'éxecution quasi nulle si le tableau est déjà trié.\n\t* Attention, la vitesse d'éxecution peut être longue (~5 minutes avec liste_eval.txt)\n");
                triBulle(tab, *i);
                printf("\t* Le tableau a été trié.\n");
            } break;

            case 7 :
            {
                if (!tab)
                    fprintf(stderr, "\t* Attention le tableau est vide !\n");
                printf("\t* Attention, la vitesse d'éxecution quasi nulle si le tableau est déjà trié.\n");
                while (n)
                {
                    printf("\t *Tri lexicographique(1)\n\t* Tri par taille (2)\n\t* Annuler (0)\n");
                    n = -1;
                    scanf("%d", &n);
                    getc(stdin);
                    switch (n)
                    {
                        case 1 :
                        {
                            triQsort(tab, *i, lexicoTri);
                            printf("\t* Le tableau a été trié.\n\n");
                            n = 0;
                        } break;
                        
                        case 2 :
                        {
                            triQsort(tab, *i, lenTri);
                            printf("\t* Le tableau a été trié.\n\n");
                            n = 0;
                        } break;

                        case 0 :
                        n = 0;
                        break ;

                        default :
                        printf("\t* Mauvaise commande\n\n");
                        break;
                    }
                }
                n = -1;
            } break;

            case 8 :
            {
                printf("\t* Nom du fichier : ");
                scanf("%s", nom);
                catFile(nom, tab, *i);
                printf("\t* Le tableau a été écrit dans le fichier.\n");
            } break;

            case 9 :
            {
                if (!tab)
                    fprintf(stderr, "\t* Attention le tableau est vide !\n");
                printf("\t* Selon les règles du scrabble, le score le plus haut du tableau est : %d et il y'a", maxScrabble(tab, *i, &misc));
                printf(" %d mots\n\n", misc);
            } break;

            case 10 :
            {
                if (!tab)
                    fprintf(stderr, "\t* Attention le tableau est vide !\n");
                printf("\t* Nom du fichier : ");
                scanf("%s", nom);
                printf("\t* Selon les règles du fichier, le score le plus haut du tableau est : %d et il y'a", maxScrabbleFile(nom, tab, *i, &misc));
                printf(" %d mots\n\n", misc);
            } break;

            case 11 :
            {
                tab = freeAll(tab, *i);
                printf("\t* Le tableau a été libéré.\n\n");
            } break;
            default :
            {
                printf("\t* Mauvaise commande\n\n");
            } break;
        }
    }
    return tab;
}

void part2(char **mots, int i)
{
    Liste *tab;
    int n;
    char nom[255];

    n = -1;
    tab = init();
    while (n)
    {
        printf("╞═══════════════════════════════════════════════════════════════════════════════════════════════════╡\n");
        printf("\t* Construire un tableau de liste en fonction d'un fichier (1)\n\t* Construire un tableau de liste en fonction d'un tableau de mot (2)");
        printf("\n\t* Recherche un mot dans le tableau de liste (3)\n\t* Recherche un mot dans un tableau de mot (4)");
        printf("\n\t* Afficher tous les mots contenant une chaîne donné dans le tableau de chaîne (5)\n\t* Libérer la chaîne (6)");
        printf("\n\t* Quitter (0)\n");
        printf("╞═══════════════════════════════════════════════════════════════════════════════════════════════════╡\n");
        printf("\t* Choisisez votre option : ");
        scanf("%d", &n);
        getc(stdin);
        switch (n)
        {
            case 1 :
            {
                printf("\t* Nom du fichier : ");
                scanf("%s", nom);
                tab = fileToChain(tab, nom);
                printf("\t* Le tableau de liste a été crée.\n\n");
            } break ;

            case 2 :
            {
                if (!mots)
                    fprintf(stderr, "\t Attention le tableau est vide !\n");
                tab = tabToChain(tab, mots, i);
                printf("\t* Le tableau de liste a été crée.\n\n");
            } break ;

            case 3 :
            {
                printf("Mot à trouver : ");
                scanf("%s", nom);
                if (searchInChain(tab, nom))
                    printf("\t* Le mot a été trouvé\n\n");
                else
                    printf("\t* Le mot n'a pas été trouvé\n\n");
            } break ;

            case 4 :
            {
                printf("\t* Mot à trouver : ");
                scanf("%s", nom);
                if (searchInTab(mots, nom, i))
                    printf("\t* Le mot a été trouvé\n\n");
                else
                    printf("\t* Le mot n'a pas été trouvé\n\n");
            } break ;

            case 5 :
            {
                printf("\t* Chaîne à trouver : ");
                scanf("%s", nom);
                printf("\t* Les chaînes contenants %s sont :\n", nom);
                affChain(tab, nom);
                printf("\n");
            } break;
            
            case 6 :
            {
                tab = freeTabChain(tab);
                printf("\t* Le tableau de chaîne a été libéré\n\n");
            } break;

            case 0 :
            n = 0;
            break;

            default :
            printf("\t* Mauvaise commande\n\n");
            break;
        }
    }
    printf("\n");
}

void part3()
{
    printf("\n\t* Chaîne construite : \n");
    printf("%s\n", creStr("Bonjour", "le", "monde", "."));
    printf("\n");
}

void menu()
{
    int n;
    int i;
    char **tab;

    tab = NULL;
    n = -1;
    i = 0;
    while (n)
    {
        //╞═══════
        //═══════╡
        printf ("╞═════════════════════════════╡\n");
        printf("\t* Partie 1 (1)\n\t* Partie 2 (2)\n\t* Partie 3 (3)\n\t* Quitter (0)\n");
        printf ("╞═════════════════════════════╡\n");
        printf("\n\t* Choisisez votre partie: ");
        n = -1;
        scanf("%d", &n);
        getc(stdin); // Permet d'empecher un problème si l'on entre un charactère au lieu d'un entier
        switch (n)
        {
            case 1:
            {
                printf("\n");
                tab = part1(&i);
            } break;

            case 2 :
            {
                printf("\n");
                part2(tab, i);
            } break;

            case 3:
            {
                printf("\n");
                part3();
            } break;

            case 0 : break;

            default:
            {
                printf("\t* Mauvaise commande\n\n");
            } break;
        }
    }
}

int main(int argc, char **argv)
{
    char **tab;
    Liste *l;
    int i;
    int misc;

    if (argc == 1)
        menu();
    else if (argc == 8 && atoi(argv[2]) == 1) // WTF
    {
        tab = fileToText(argv[1], &i);
        if (strcmp(argv[3], "."))
            strIntab(tab, argv[3], i);
        addTab(tab, argv[4], atoi(argv[5]), &i);
        triQsort(tab, i, lexicoTri);
        catFile(argv[6], tab, i);
        printf("%d\n", maxScrabbleFile(argv[7], tab, i, &misc));
        tab = freeAll(tab, i);
    }
    else if (argc == 4 && atoi(argv[2]) == 2)
    {
         l = init();
         l= fileToChain(l, argv[1]);
         affChain(l, argv[3]);
         l = freeTabChain(l);
    }
    else
    {
        printf("Commande incorrecte.\n");
    }
    return 0;
}