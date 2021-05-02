# LEPL1503 - Projet 3 - Groupe H1
Participants :
 - Allegaert Hadrien
 - Beuel Nicolas
 - Gaudin Félix
 - Gwendal Laurent
 - Kuperblum Jeremie
 - Schot Jean
# Description du projet

Le projet a pour but de donner les tous les facteurs premier de nombres présents dans un fichier d'entrée dans un fichier de sortie.
ex :
Fichier d'entrée :

    234
    666
    18446744073709551557
    345678

Fichier de sortie :

    666 2 3 37
    234 2 3 13
    345678 2 3 17 3389
    18446744073709551557

NB : Le fichier de sortie ne garde pas obligatoirement le même ordre que celui d'arrivée.

## Structures

Nous utilisons principalement deux type de structure de liste.

 1. La première est une liste doublement chaînée où la valeur de chaque node est en unsigned int 64 bits. (On utilise principalement cette structure pour stocker des nombres premiers).



    ```c
    typedef struct node{  
	    unsigned  long  long  int value;
	    struct node* next;
    }node;

    typedef  struct list{  
	    int size;
	    node *head;
	    node *tail;
     }list;
 ``
	NB : on utilise la tail de la liste pour ajouter des éléments et donc être en $\theta(1)$
	 pour y ajouter des éléments

 2. La secondes est aussi une liste de node sauf que chaque node contient plus de données. Cette structure est utilisée pour stocker les nombres du fichier d'entré et ses facteurs premiers

    ```c
    typedef  struct divNode{  
	    unsigned  long  long  int value, copy;
	    list *divisors; // the list of prime divisor of the value  struct divNode*
	    next;
    }divNode;

    typedef  struct divList{
	    divNode* root;
	    int size;
	    unsigned  long  long  int max;
     }divList;

## Utilisation

Pour commencer rendez vous dans le fichier contenant le MakeFile (/facto).
Ensuite pour compiler vous devez utiliser la comment `$ make fact` et pour l'exécuter
`$ ./fact inputFile outputFile` à cela vous pouvez ajouter le choix du nombre de threads qui seront utilisés via l'argument `-N` d'un entier.
Vous pouvez build des tests via la commande `$ make build_test`.
Vous pouvez aussi exécuter notre batterie de test via la commande `$ make test`.
Et enfin pour nettoyer les fichiers créés vous pouvez utiliser la commande `$make clean`.
