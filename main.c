#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
/****************************Valeurs**************************/

char valeurs[]={'A','K','Q','J','T','9','8','7','6','5','4','3','2'};
char figures[]={'C','D','H','S'}; //C=Trèfle H=Coeur D=Carreau  S=Pique

int numgagnant ;
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

bool testdoublons(carte*cartes, mainjoueur*tiragecarte);

char generatefigure();

char generatevalue ();

bool is_same_figure(carte*carte1, carte*carte2);

bool is_same_figure(carte*carte1, carte*carte2);

int getrang(carte cartes);

mainjoueur tri(mainjoueur tiragecarte);

score is_straight_flush(mainjoueur *); // suite combinée à une couleur, sans l'As comme plus haute carte (si 2 straight flush, le joueur qui a la carte la plus haute de la suite wins), score : 150
score is_four_of_king(mainjoueur *); // quatre cartes d'un même valeur - score : 120
score is_full_house(mainjoueur *); // brelan + paire - score : 90
score is_flush(mainjoueur *); // cinq cartes de même figure (mais /!\ a ce que ce soit du même sigle) --> 5 trefle OU 5 coeur OU etc.. - score : 80
score is_straight(mainjoueur *); // cinq cartes consécutives (qui se suivent numériquement) - score : 70
score is_three_of_kind(mainjoueur *); // trois cartes de la même valeur (brelan) - score : 50
score is_two_pair(mainjoueur*); // deux paires - score : 40
score is_pair(mainjoueur *); // une seule paire - score : 20
score is_highcard(mainjoueur *); // absence de mains - score : 0


score comparermain(joueurs *);

void testcombinaisons(mainjoueur*);



/*************************************Choix figures et valeurs******************************/
char generatevalue() {
    int nb1= rand() %13;

    return valeurs[nb1];
}

char generatefigure() {
    int nb2 = rand() %4;

    return figures[nb2];
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
bool testdoublons(carte*cartes, mainjoueur*tiragecarte) {


    int cpt=0;

    for (int i = 0; i < 5; i++) {
        if ((is_same_figure(cartes, &tiragecarte->cartes[i])) && (is_same_value(cartes, &tiragecarte->cartes[i]))) {
            cpt ++;
        }
        if (cpt==2) {
            return true;
        }
    }
    return false;
}


/*********************************Génération carte et mains***************************************/
mainjoueur generatehand() {
    mainjoueur tiragecarte ;

    for (int i = 0; i <=4; i++) { //Génération d'une carte

        carte cartes;

        cartes.figure = generatefigure();
        cartes.valeur = generatevalue();

        tiragecarte.cartes[i]=cartes;

        if (testdoublons(&cartes, &tiragecarte)){ // appel de la fonction doublon puis correction sur la main
            i--;
        }

    }

    return tiragecarte;
}


/**************************Tri de la main du joueur************************/

mainjoueur tri(mainjoueur tirage) {
    carte temp1;
    for (int i = 0; i < 5; ++i) {
        for (int k = i+1; k < 5; ++k) {
            if (getrang(tirage.cartes[i]) < getrang(tirage.cartes[k])) {
                temp1 = tirage.cartes[k];
                tirage.cartes[k] = tirage.cartes[i];
                tirage.cartes[i] = temp1;
            }
        }
    }
    return tirage;
}
/****************affichage de la main*****************/

void affichermain(mainjoueur tiragecarte) {

    for (int i = 0; i < 5; i++) {
        printf("%c%c ", tiragecarte.cartes[i].valeur, tiragecarte.cartes[i].figure);
    }
}

/****************************rang carte************************/

int getrang(carte cartes) {

    int valeur_carte;                               //création variable on l'on rentre la valeur de la carte

    for (int i = 0; i < 13; i++)                          //création d'une boucle for pour scanner les 14 élements présent dans le tableau
    {

        if (cartes.valeur ==
            valeurs[i])                    //si le pointeur de la carte est associé à sa bonne valeur dans le tableau
            valeur_carte = i;                             //la variable valeur_carte prend alors la valeur de la case i du tableau

    }

    return valeur_carte;  //on retourne la variable valeur_carte de type entier


}



/**************************Combinaisons*********************/

score is_pair(mainjoueur *tiragecarte) {
    int cpt=0;

    score paire;
    paire.score=0;
    for (int i = 0; i <5 ; i++) {
        if (cpt ==1){
            //printf("cpt 2");
            strcpy(paire.type, "PAIRE");
            paire.score = 20 ;
            break; //on casse la boucle
        }

        for (int j = i+1; j <5 ; j++) {       //analyse la main grâce au tri fait avant
            if (is_same_value(&tiragecarte->cartes[i],&tiragecarte->cartes[j])){ //si la valeur de la carte est identique à celle d'après
                cpt++;
                //printf("%d", cpt);

            }
        }
    }



    return paire;
}

score is_two_pair(mainjoueur *tiragecarte) {

    score deuxpaires;
    deuxpaires.score=0;
    for (int i = 0; i < 4 ; ++i) {
        if (is_same_value(&tiragecarte->cartes[i], &tiragecarte->cartes[i + 1]) &&
            is_same_value(&tiragecarte->cartes[i + 3], &tiragecarte->cartes[i + 4])) {
            strcpy(deuxpaires.type, " DOUBLE PAIRE");
            deuxpaires.score = 40;
        }

    }


    return deuxpaires;
}


score is_three_of_kind(mainjoueur *tiragecarte) {

    score brelan;
    brelan.score=0;
    for (int i = 0; i < 2; ++i) {
        if (tiragecarte->cartes[i].valeur == tiragecarte->cartes[i + 1].valeur &&
            tiragecarte->cartes[i].valeur == tiragecarte->cartes[i + 2].valeur) {

            strcpy(brelan.type, "BRELAN");
            brelan.score = 50;
        }
        return brelan;
    }
}


score is_straight(mainjoueur *tiragecarte) {


    score suite;
    suite.score=0;
    int cpt=0;

    for (int i = 0; i <4 ; i++) {
        if (tiragecarte->cartes[i].valeur == 1+getrang(tiragecarte->cartes[i+1])) //si la carte = 1+ rang de la carte d'après
            cpt++; //cpteur s'incrémente
    }

    printf("cpt= %d",cpt);

    if(cpt==5) {
        strcpy(suite.type, "SUITE");
        suite.score = 70;
    }
    return suite;
}


score is_flush(mainjoueur *tiragecarte) {


    score flush;
    flush.score = 0;
    for (int i=0; i<5 ; i++) {
        for (int j=0; j<5 ; j++) {
            if (tiragecarte->cartes[i].figure == tiragecarte->cartes[j+1].figure == tiragecarte->cartes[j+2].figure
                == tiragecarte->cartes[j+3].figure == tiragecarte->cartes[j+4].figure){
                strcpy(flush.score, "FLUSH");
                flush.score = 80;
            }


        }

    }

    return flush;
}

score is_full_house(mainjoueur *tiragecarte) { //resultat du brelan et de la double paire

    score fullhouse;
    fullhouse.score =0;

    if (fullhouse.score=="BRELAN"&&fullhouse.score=="DOUBLE PAIRE"){

        strcpy(fullhouse.type, "FULL HOUSE");
        fullhouse.score == 90;
    }


    return fullhouse;
}


score is_four_of_king(mainjoueur *tiragecarte) {

    score carre;
    carre.score=0;

    for (int i = 0; i < 2 ; ++i) {
        if (tiragecarte->cartes[i].valeur == tiragecarte->cartes[i + 1].valeur &&
            tiragecarte->cartes[i].valeur == tiragecarte->cartes[i + 2].valeur &&
            tiragecarte->cartes[i].valeur == tiragecarte->cartes[i + 3].valeur) {


            strcpy(carre.type, "CARRE");
            carre.score = 120;
        }
    }
    return carre;

}

score is_straight_flush(mainjoueur *tiragecarte) {

    score straight_flush;
    straight_flush.score=0;
    for (int i=0; i<5; ++i){
        if (tiragecarte->cartes[i].figure == tiragecarte->cartes[i+1].figure &&
            tiragecarte->cartes[i].figure == tiragecarte->cartes[i+2].figure &&
            tiragecarte->cartes[i].figure == tiragecarte->cartes[i+3].figure &&
            tiragecarte->cartes[i].figure == tiragecarte->cartes[i+4].figure) {
            strcpy(straight_flush.type, "STRAIGHT FLUSH");
            straight_flush.score = 200;
        }
    }
    return straight_flush;
}



score testcombinaisons(mainjoueur *tiragecarte) {
score resultat;

    if (resultat.score == 0){
    resultat = is_pair(tiragecarte);
    }
        if (resultat.score==0) {
            resultat = is_two_pair(tiragecarte);
        }
            if (resultat.score==0){
                resultat = is_three_of_kind(tiragecarte);
            }
                if (resultat.score == 0) {
                    resultat = is_four_of_king(tiragecarte);
                }
                    if (resultat.score == 0); {
                        resultat = is_straight(tiragecarte);
                    }
                        if (resultat.score == 0) {
                            resultat = is_flush(tiragecarte);
                        }
                            if (resultat.score == 0) {
                                resultat = is_full_house(tiragecarte);
                            }
                                if (resultat.score==0){
                                    resultat = is_straight_flush(tiragecarte);
                                }
                                    if (resultat.score==0){
                                        resultat = is_highcard(tiragecarte);
                                    }

    printf("%d", resultat);
}

void comparermain(joueurs *js) {


    if (js->joueur[0].scorejoueur.score > js->joueur[1].scorejoueur.score){
        numgagnant =1;
    }
    if (js->joueur[0].scorejoueur.score == js ->joueur[1].scorejoueur.score){
        numgagnant =2;
    }
    if (js->joueur[0].scorejoueur.score < jeu ->joueur[1].scorejoueur.score){
        numgagnant =3;
    }


}



int main() {
    unsigned long seed = clock()+time(NULL)+getpid();
    srand(seed); //commande random

joueurs joueurs;
joueur premier;
joueurs.joueur[0] = premier;

joueur deuxième;
joueurs.joueur[1]=deuxième;

    mainjoueur mainjoueur1 = tri((generatehand()));

    joueurs.joueur[0].main=mainjoueur1;
    printf("\nla main du joueur 1 est : ");
    affichermain(mainjoueur1);
    testcombinaisons(&mainjoueur1);

    mainjoueur mainjoueur2 = tri((generatehand()));

    joueurs.joueur[1].main=mainjoueur2;
    printf("\nla main du joueur 2 est : ");
    affichermain(mainjoueur2);
    testcombinaisons(&mainjoueur2);




    if(numgagnant==1){
        printf("\nLe joueur 1 gagne. %s est plus fort que %s", );
    }

    if (numgagnant == 2) {
        printf("\nEgalité");
    }

    if (numgagnant == 3){
        printf("\nLe joueur 2 gagne. %s est plus fort que %s")
    }




    return 0;
}