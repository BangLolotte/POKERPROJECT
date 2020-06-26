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


void comparermain(joueurs *);

score testcombinaisons(mainjoueur*);



/*************************************Choix figures et valeurs******************************/
char generatevalue() {
    int nb1= rand() %13;      //génération d'un chiffre entre 0 et 13

    return valeurs[nb1];
}

char generatefigure() {
    int nb2 = rand() %4;     //génération d'un chiffre entre 0 et 4

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
bool testdoublons(carte*cartes, mainjoueur*tiragecarte) {    //permet de tester si une carte est identique à une autre dans la main


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
        printf("%c%c ", tiragecarte.cartes[i].valeur, tiragecarte.cartes[i].figure); //appel des cartes générées dans une fonction précédente
    }
}


/****************************rang de la carte************************/

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



/***********************************************Combinaisons************************************************/

score is_pair(mainjoueur *tiragecarte) {
    int cpt=0;

    score paire;
    paire.score=0;

    for (int i = 0; i <5 ; i++) {
        if (cpt ==1){

            strcpy(paire.type, "PAIRE");
            paire.score = 20 ;
            break; //on casse la boucle
        }

        for (int j = i+1; j <5 ; j++) {       //analyse la main triée
            if (is_same_value(&tiragecarte->cartes[i],&tiragecarte->cartes[j])){ //si la valeur de la carte est identique à celle d'après
                cpt++;


            }
        }
    }

    return paire;
}

score is_two_pair(mainjoueur *tiragecarte) {

    score deuxpaires;
    deuxpaires.score=0;
    for (int i = 0; i < 4 ; ++i) {
        if (is_same_value(&tiragecarte->cartes[i], &tiragecarte->cartes[i + 1]) &&       //si la valeur de la 1ere carte et la 2e carte = valeur de la 3e et la 4e
            is_same_value(&tiragecarte->cartes[i + 3], &tiragecarte->cartes[i + 4]))
        {
            strcpy(deuxpaires.type, "DOUBLE PAIRE");
            deuxpaires.score = 40;
        }

    }


    return deuxpaires;
}


score is_three_of_kind(mainjoueur *tiragecarte) {

    score brelan;
    brelan.score=0;
    for (int i = 0; i < 2; ++i) {
        if (tiragecarte->cartes[i].valeur == tiragecarte->cartes[i + 1].valeur &&    //si valeur de la première = valeur de la 2e,
            tiragecarte->cartes[i].valeur == tiragecarte->cartes[i + 2].valeur) {    //et valeur de la 1e = valeur de la 3e

            strcpy(brelan.type, "BRELAN");
            brelan.score = 50;
        }
        return brelan;
    }
}


score is_straight(mainjoueur *tiragecarte) {

    score suite;
    suite.score = 0;
    for (int i = 0; i < 4; ++i) {
        if (getrang(tiragecarte->cartes[i + 4]) == 1 + getrang(tiragecarte->cartes[i + 3]) &&    //si le rang de la dernière carte  = celle de la 4e + 1
            getrang(tiragecarte->cartes[i + 3]) == 1 + getrang(tiragecarte->cartes[i + 2]) &&    // et rang de la 4e = celle de la 3e + 1
            getrang(tiragecarte->cartes[i + 2]) == 1 + getrang(tiragecarte->cartes[i + 1]) &&    // et rang de la 3e = celle de la 2e +1... Ainsi de suite
            getrang(tiragecarte->cartes[i + 1]) == 1 + getrang(tiragecarte->cartes[i])) {
            strcpy(suite.type, "UNE SUITE");
            suite.score = 70;
        }

        return suite;

    }
}

score is_flush(mainjoueur *tiragecarte) {


    score flush;
    flush.score = 0;
    for (int i=0; i<5 ; i++) {
        for (int j=0; j<5 ; j++) {
            if (tiragecarte->cartes[i].figure == tiragecarte->cartes[j+1].figure == tiragecarte->cartes[j+2].figure
                == tiragecarte->cartes[j+3].figure == tiragecarte->cartes[j+4].figure){
                strcpy(flush.type, "FLUSH");
                flush.score = 80;
            }


        }

    }

    return flush;
}

score is_full_house(mainjoueur *tiragecarte) { //resultat du brelan et de la double paire

    score fullhouse;
    fullhouse.score =0;

    if (fullhouse.type=="BRELAN"&&fullhouse.type=="DOUBLE PAIRE"){

        strcpy(fullhouse.type, "FULL HOUSE");
        fullhouse.score = 90;
    }


    return fullhouse;
}


score is_four_of_king(mainjoueur *tiragecarte) {

    score carre;
    carre.score=0;

    for (int i = 0; i < 2 ; ++i) {
        if (tiragecarte->cartes[i].valeur == tiragecarte->cartes[i + 1].valeur && // si valeur de la 1e = valeur de la 2e
            tiragecarte->cartes[i].valeur == tiragecarte->cartes[i + 2].valeur && // et valeur de la 1e = valeur de la 3e
            tiragecarte->cartes[i].valeur == tiragecarte->cartes[i + 3].valeur) { // et valeur de la 1e = valeur de la 4e


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
        if (tiragecarte->cartes[i].figure == tiragecarte->cartes[i+1].figure &&   //si figure de la 1e = figure de la 2e
            tiragecarte->cartes[i].figure == tiragecarte->cartes[i+2].figure &&   // si figure de la 1e = figure de la 3e
            tiragecarte->cartes[i].figure == tiragecarte->cartes[i+3].figure &&   // si figure la 1e = figure de la 4e
            tiragecarte->cartes[i].figure == tiragecarte->cartes[i+4].figure) {  // si figure de la 1e = figure de la 5e
            strcpy(straight_flush.type, "STRAIGHT FLUSH");
            straight_flush.score = 200;
        }
    }
    return straight_flush;
}


/*****************************Appel de toutes les combinaisons**********************************/

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
    if (resultat.score == 0) {
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
   // if (resultat.score==0){
   //    resultat = is_highcard(tiragecarte);
   //}

    printf("%i", resultat.score);  // pour vérifications
}


/********************************Comparaison des 2 mains générées********************************/

void comparermain(joueurs *js) {
    joueur premier;  //appel d'une instance pour joueur 1
    joueur deuxieme; //appel d'une instance pour joueur 2

    printf("score joueur 0 (premier) %d", js->joueur[0].scorejoueur.score);   //pour vérifications
    printf("score joueur 1 (deuxieme) %d", js->joueur[1].scorejoueur.score);  //pour vérifications

    if (js->joueur[0].scorejoueur.score > js->joueur[1].scorejoueur.score){
        premier.gagnant = true;
        deuxieme.gagnant=false;
        printf("\nLe joueur 1 gagne. %s est plus fort que %s", premier.scorejoueur.type, deuxieme.scorejoueur.type);
    }
    if (js->joueur[0].scorejoueur.score == js ->joueur[1].scorejoueur.score){
        premier.gagnant=true;
        deuxieme.gagnant=true;
        printf("\nEgalité");
    }
    if (js->joueur[0].scorejoueur.score < js ->joueur[1].scorejoueur.score){
        deuxieme.gagnant=true;
        premier.gagnant=false;
        printf("\nLe joueur 2 gagne. %s est plus fort que %s", deuxieme.scorejoueur.type, premier.scorejoueur.type);

    }
    if (premier.gagnant ==false && deuxieme.gagnant==false){
        printf("\nErreur...");
    }
}

/*********************************Main**********************************/

int main() {
    unsigned long seed = clock()+time(NULL)+getpid();
    srand(seed); //commande random

    joueurs joueurs;
    joueur premier;

    joueurs.joueur[0] = premier;  //le joueur[0] devient "premier"

    joueur deuxieme;
    joueurs.joueur[1]=deuxieme;  //le joueur[1] devient "deuxième"

    mainjoueur mainjoueur1 = tri((generatehand()));

    joueurs.joueur[0].main=mainjoueur1;  //la première main devient la main du joueur premier
    printf("\nla main du joueur 1 est : ");
    affichermain(mainjoueur1);
    testcombinaisons(&mainjoueur1); //appel des combinaisons pour la mainjoueur1

    mainjoueur mainjoueur2 = tri((generatehand()));

    joueurs.joueur[1].main=mainjoueur2;  //même principe que la première
    printf("\nla main du joueur 2 est : ");
    affichermain(mainjoueur2);
    testcombinaisons(&mainjoueur2);


    comparermain(&joueurs); //comparaison des mains + détermination du résultat





    return 0;
}