#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <gmpxx.h>

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
score resultat;

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

int getrang(carte cartes);

score is_straight_flush(mainjoueur *); // suite combinée à une couleur, sans l'As comme plus haute carte (si 2 straight flush, le joueur qui a la carte la plus haute de la suite wins), score : 150
score is_four_of_king(mainjoueur *); // quatre cartes d'un même valeur - score : 120
score is_full_house(mainjoueur *); // brelan + paire - score : 100
score is_flush(mainjoueur *); // cinq cartes de même figure (mais /!\ a ce que ce soit du même sigle) --> 5 trefle OU 5 coeur OU etc.. - score : 90
score is_straight(mainjoueur *); // cinq cartes consécutives (qui se suivent numériquement) - score : 70
score is_three_of_kind(mainjoueur *); // trois cartes de la même valeur (brelan) - score : 50
score is_two_pair(mainjoueur*); // deux paires - score : 40
score is_pair(mainjoueur *); // une seule paire - score : 20
score is_highcard(mainjoueur *); // carte la plus haute - score : 10

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


/*********************************Génération carte et mains***************************************/
mainjoueur generatehand() {
    mainjoueur tiragecarte ;

    for (int i = 0; i <=4; i++) { //Génération d'une carte

        carte cartes;

        cartes.figure = generatefigure();
        cartes.valeur = generatevalue();

        tiragecarte.cartes[i]=cartes;


    }
    return tiragecarte;

}

void affichermain(mainjoueur tiragecarte) {
        printf("La main du joueur est : ");
        for (int i = 0; i < 5; i++) {
            printf("%c%c ", tiragecarte.cartes[i].valeur, tiragecarte.cartes[i].figure);
        }
}

/************************************bool**************************/

bool is_same_figure(carte*carte1, carte*carte2)
{

    return carte1->figure == carte2->figure;            //retourne true ou false après avoir comparé les figures des cartes

}


bool is_same_value (carte * carte1, carte * carte2)
{

    return carte1->valeur == carte2->valeur;            //retourne true ou false après avoir comparé les valeurs des cartes

}
/****************************rang carte************************/

int getrang(carte cartes) {

    int valeur_carte;                               //création variable on l'on rentre la valeur de la carte

    for (int i = 0; i < 13; i++)                          //création d'une boucle for pour scanner les 14 élements présent dans le tableau
    {

        if (cartes.valeur ==
            valeurs[i])                    //si le pointeur de la carte est associer à sa bonne valeur dans le tableau
            valeur_carte = i;                             //la variable valeur_carte prend alors la valeur de la case i du tableau

    }

    return valeur_carte;  //on retourne la variable valeur_carte de type entier


}



/**************************Combinaisons*********************/
score is_pair(mainjoueur *tiragecarte) {

    score paire;
    for (int i = 0; i <5 ; i++) {
        for (int j = 0; j <5 ; j++) {
            if (tiragecarte->cartes[i].valeur == tiragecarte->cartes[j+1].valeur){
                strcpy(resultat.score, "UNE PAIRE");
                printf("une paire");
                resultat.score = 20 ;
            }
        }
    }


    return resultat;
}

score is_two_pair(mainjoueur *tiragecarte) {

    score twopair;
    for (int i=0; i <5 ; i++) {
        for (int j=0; j <5 ; j++) {
            for (int k=0; k <5; k++) {
                if (tiragecarte->cartes[i].valeur == tiragecarte->cartes[j+1].valeur && tiragecarte->cartes[k].valeur == tiragecarte->cartes[k+1].valeur) {
                    strcpy(resultat.score, "DEUX PAIRE");
                    printf("deux paire");
                    resultat.score=40;
                }
            }

        }

    }

}

score is_highcard(mainjoueur *tiragecarte) {
    score highcard;
    carte cartes;
    for (int i=0; i<5; i++){

        printf("La carte la plus fort est :", tiragecarte.cartes[i] == carte.valeur[1]);
    }





}


int main() {
    srand(time(NULL)); //commande random
    affichermain(generatehand());
    score pair;
    score is_pair;


    return 0;
}

