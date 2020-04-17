#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
/****************************Valeurs**************************/

char valeurs[]={'A','K','Q','J','T','9','8','7','6','5','4','3','2'};
char figures[]={'C','D','H','S'}; //C=Trèfle H=Coeur D=Carreau  S=Pique

/******************************Structures*********************************/
typedef struct carte
{
    char valeur;
    char figure;
}carte;


typedef struct main
{
    carte cartes[5];
}mainjoueur;


typedef struct score {
    char type[255];
    int score;
}score;


typedef struct joueur {
    int numero;
    score scorejoueur;
    mainjoueur main;
    bool gagnant;
}joueur;


typedef struct joueurs {
    joueur joueur[2];
}joueurs;

/*********************************Prototypes*********************************/
mainjoueur generatehand();
void affichermain(mainjoueur);
char generatefigure();

char generatevalue ();

bool is_same_figure(carte*carte1, carte*carte2);

bool is_same_figure(carte*carte1, carte*carte2);
/*************************************Choix figures et valeurs******************************/
char generatevalue() {
    sleep(1);
    int nb1= rand() %13;

    return valeurs[nb1];
}

char generatefigure() {
    sleep(1);
    int nb2 = rand() %4;

    return figures[nb2];
}


/*********************************Génération carte***************************************/
mainjoueur generatehand() {

    for (int i = 0; i <=4; i++) { //Génération d'une carte

        carte carte ;

        carte.figure=generatefigure();
        carte.valeur=generatevalue();
        printf("carte : %c%c\n",carte.valeur,carte.figure);

    carte.figure=generatefigure();
    carte.valeur=generatevalue();

        mainjoueur main ;



//printf("Carte : %c%c \n",carte.valeur, carte.figure);

    }


    mainjoueur result;
    return result;


}
/************************************bool**************************/

bool is_same_figure(carte*carte1, carte*carte2)
{

    return carte1->figure == carte2->figure;            //retourne true ou false après avoir comparé les figues des cartes

}

bool is_same_value (carte * carte1, carte * carte2)
{

    return carte1->valeur == carte2->valeur;            //retourne true ou false après avoir comparé les valeurs des cartes

}





int main() {
    srand(time(NULL)); //commande random
    generatehand();

    printf("Test");

    return 0;
}