/**
* \page Général 
* 
* \author Elouan Cadalen
* \version 3.0
* \date 28 novembre 2021
*
* Ce programme est une reproduction du jeu du yams
* en c où deux joueurs peuvent jouer l'un contre l'autre
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

/**
* \def N_DES
* \brief Nombre de dés.
*
* Nombre de dés à lancer pour jouer.
*/
#define N_DES 5

/**
* \def NB_JOUEUR
* \brief Nombre de joueur.
*
* Nombre de joueur qui peuvent jouer au jeu.
*/
#define NB_JOUEUR 2

/**
* \def NB_CASE
* \brief Nombre de case dans le tableau des score.
*
* Nombre de case qui apparaissent dans le tableau des scores.
*/
#define NB_CASE 17

/**
* \def TAILLE_PSEUDO
* \brief nombre de caractères max pour le pseudo.
*
* Nombre de caractère max autorisé pour le pseudo
*/
#define TAILLE_PSEUDO 21

/**
* \typedef t_des
* \brief tableau de dé.
*
* définition du type de tableau qui va contenir les dés.
*/
typedef int t_des[N_DES];

/**
* \typedef t_score
* \brief tableau de score avec NB_JOUEUR lignes et NB_CASE colonnes.
*
* définition du tableau en 2D qui va contenir les scores des deux joueurs.
*/
typedef int t_score[NB_JOUEUR][NB_CASE];

/**
* \typedef chaine20
* \brief chaine de 20 caractères.
*
* définition d'une chaine de 20 caractères.
*/
typedef char chaine20[21];

/**
* \typedef t_chaine
* \brief tableau de NB_CASE de chaine20.
*
* définition d'un tableau contenant les différentes lignes de textes présente dans le tableau des scores.
*/
typedef chaine20 t_chaine[NB_CASE];

/**
* \typedef pseudo20
* \brief chaine de 20 caractères.
*
* Le type chaine permet de déclarer des chaines de caractères en tant que liste chaînée.
*/
typedef char pseudo20[21];

/**
* \def chaine
* \brief constante pour les différentes chaines de caractères présente dans le tableau des scores.
*
*/
const t_chaine chaine={"1 total de 1","2 total de 2","3 total de 3","4 total de 4","5 total de 5","6 total de 6","Bonus si >62 [35]"," Total superieur",
"Brelan    [total]","Carre     [total]","Full house   [25]","Petite suite [30]","Grande suite [40]","Yams         [50]","Chance      [total]","Total inferieur","Total"};

/**
* \def des
* \brief constante pour les différentes représentations graphique des dés.
*
*/
const chaine20 des[6][5]={{"╔═══╗","║   ║","║ ▪ ║","║   ║","╚═══╝"},{"╔═══╗","║▪  ║","║   ║","║  ▪║","╚═══╝"},{"╔═══╗","║▪  ║","║ ▪ ║","║  ▪║","╚═══╝"},
{"╔═══╗","║▪ ▪║","║   ║","║▪ ▪║","╚═══╝"},{"╔═══╗","║▪ ▪║","║ ▪ ║","║▪ ▪║","╚═══╝"},{"╔═══╗","║▪ ▪║","║▪ ▪║","║▪ ▪║","╚═══╝"}};

/**
* \def ARRET
* \brief constante pour la valeur d'arret.
*
*/
const int ARRET=-1;

/**
* \fn void donner_pseudo(pseudo20 pseudores)
* \brief Procédure qui demande un pseudo au joueur.
* \param pseudores : paramètre de sortie qui représente le pseudo de l'utilisateur.
*
* Demande le pseudo à l'utilisateur et vérifie s'il fait bien 20 caractères ou moins.
*/
void donner_pseudo(pseudo20 pseudores) {
    char pseudo[50];
    do
    {
        printf("\nDonnez votre pseudo(20 caractères max) : ");
        scanf("%s",pseudo);
        if (strlen(pseudo)>20 || strlen(pseudo)==0) {
            printf("taille de pseudo incorrecte\n");
        }
    } while (strlen(pseudo)>20 || strlen(pseudo)==0);
    strcpy(pseudores,pseudo);
}

/**
* \fn void echange(int *i,int *j)
* \brief Procédure qui échange deux valeurs.
* \param i : paramètre d'entrée/sortie qui représente une valeur
* \param j : paramètre d'entrée/sortie qui représente une autre valeur
*
* échange deux valeurs placées en paramètre
*/
void echange(int *i,int *j) {
    int tmp;
    tmp=*i;
    *i=*j;
    *j=tmp;
}

/**
* \fn void tri_des(t_des tab)
* \brief Procédure qui tri les dés.
* \param tab : paramètre d'entrée/sortie qui représente le tableau contenant les valeurs des 5 dés
*
* tri le tableau de dés avec un tri à bulle
*/
void tri_des(t_des tab) {
    int max,imaxtmp;
    bool permutation=true;
    max=N_DES-1;
    while (permutation && max>0) {
        permutation=false;
        imaxtmp=max-1;
        for (int i=0;i<max;i++) {
            if (tab[i]>tab[i+1]) {
                echange(&tab[i],&tab[i+1]);
                permutation=true;
                imaxtmp=i+1;
            }
        }
        max=imaxtmp;
    }
}

/**
* \fn rangement_facile(t_des tab,int val)
* \brief Fonction qui calcule le score pour le cases du tableau supérieur.
* \param tab : paramètre d'entrée/sortie qui représente tableau des dés triés.
* \param val : paramètre d'entrée qui représente la valeur du dé recherchée.
* \return le score à ranger dans le tableau.
*/
int rangement_facile(t_des tab,int val) {
    int res=0;
    for (int i=0;i<N_DES;i++) {
        if (tab[i]==val) {
            res=res+val;
        }
    }
    return res;
}

/**
* \fn rangement_yams(t_des tab)
* \brief Fonction qui calcule le score pour la case yams.
* \param tab : paramètre d'entrée/sortie qui représente tableau des dés triés.
* \return le score à ranger dans la case yams du tableau.
*/
int rangement_yams(t_des tab) {
    bool res;
    int val=tab[0],score;
    res=true;
    for (int i=1;i<N_DES;i++) {
        if (tab[i]!=val) {
            res=false;
        }
    }
    if (res) {
        score=50;
    }
    else {
        score=0;
    }
    return score;
}

/**
* \fn rangement_chance(t_des tab)
* \brief Fonction qui calcule le score pour la case chance.
* \param tab : paramètre d'entrée/sortie qui représente tableau des dés triés.
* \return le score à ranger dans la case chance du tableau.
*/
int rangement_chance(t_des tab) {
    int res=0;
    for (int i=0;i<N_DES;i++) {
        res=res+tab[i];
    }
    return res;
}

/**
* \fn suite_des(t_des tab)
* \brief Fonction calcule le nombre de chiffre qu'il y a de dé qui ont des valeurs qui se suivent.
* \param tab : paramètre d'entrée/sortie qui représente tableau des dés triés.
* \return le nombre de dé qui ont des valeurs qui se suivent.
*/
int suite_des(t_des tab) {
    int max,suite;
    max=0;
    suite=1;
    for (int i=1;i<N_DES;i++) {
        if (tab[i]==tab[i-1]+1) {
            suite++;
        }
        else {
            suite=1;
        }
        if (max<suite) {
            max=suite;
        }
    }
    return max;
}

/**
* \fn void occu_des(t_des tab,int *max,int *valmax)
* \brief Procédure qui compte le nombre d'occurence qu'il y a dans le tableau des dés.
* \param tab : paramètre d'entrée/sortie qui représente le tableau contenant les valeurs des 5 dés triés.
* \param max : paramètre de sortie qui représente le nombre d'occurence max qu'il y a dans le tableau des dés.
* \param valmax : paramètre de sortie qui représente la valeur du dé qui est représenté le plus de fois dans le tableau des dés.
*/
void occu_des(t_des tab,int *max,int *valmax) {
    int occurence,val;;
    *max=0;
    val=tab[0];
    occurence=1;
    for (int i=1;i<N_DES;i++) {
        if (tab[i]==val) {
            occurence++;
        }
        else {
            occurence=1;
            val=tab[i];
        }
        if (*max<occurence) {
            *valmax=val;
            *max=occurence;
        }
    }
}

/**
* \fn rangement_brelan(t_des tab)
* \brief Fonction qui calcule le score pour la case brelan.
* \param tab : paramètre d'entrée/sortie qui représente tableau des dés triés.
* \return le score à ranger dans la case brelan du tableau.
*/
int rangement_brelan(t_des tab) {
    int res,occu,val;
    occu_des(tab,&occu,&val);
    if (occu>=3) {
        res=3*val;
    }
    return res;
}

/**
* \fn rangement_carre(t_des tab)
* \brief Fonction qui calcule le score pour la case carre.
* \param tab : paramètre d'entrée/sortie qui représente tableau des dés triés.
* \return le score à ranger dans la case carré du tableau.
*/
int rangement_carre(t_des tab) {
    int res,occu,val;
    occu_des(tab,&occu,&val);
    if (occu>=4) {
        res=4*val;
    }
    return res;
}

/**
* \fn rangement_full_house(t_des tab)
* \brief Fonction qui calcule le score pour la case full house.
* \param tab : paramètre d'entrée/sortie qui représente tableau des dés triés.
* \return le score à ranger dans la case full house du tableau.
*/
int rangement_full_house(t_des tab) {  // d'après les règles officielles du yams le full house donne 25 points 
    int val1,val2,occu1,occu2,res;     //si il y a 2 dés identiques d'une valeur et 3 dés identiques d'une autre valeur
    val1=tab[0];
    val2=tab[N_DES-1];
    occu1=1;
    occu2=1;
    for (int i=1;i<N_DES-2;i++) {
        if (tab[i]==val1) {
            occu1++;
        }
        else if (tab[i]==val2) {
            occu2++;
        }
    }
    if ((occu1==3 && occu2==2) || (occu2=3 && occu1==2)){
        res=25;
    }
    else {
        res=0;
    }
    return res;
}

/**
* \fn void maj_totaux(t_score tab,int joueur)
* \brief Procédure qui calcule le total supérieur, inférieur et le total des deux.
* \param tab : paramètre d'entrée/sortie qui représente le tableau des scores.
* \param joueur : paramètre d'entrée qui représente le joueur en train de jouer (0 pour le premier et 1 pour le deuxième).
*/
void maj_totaux(t_score tab,int joueur) {
    int totsup,totinf;
    totsup=0;
    totinf=0;
    for (int i=0;i<7;i++) {
        if (tab[joueur][i]!=-1) {
            totsup=totsup+tab[joueur][i];
        }
    }
    for (int i=8;i<15;i++) {
        if (tab[joueur][i]!=-1) {
            totinf=totinf+tab[joueur][i];
        }
    }
    tab[joueur][7]=totsup;
    tab[joueur][15]=totinf;
    tab[joueur][16]=totsup+totinf;
}

/**
* \fn void calcul_bonus(t_score tab,int joueur)
* \brief Procédure qui calcule bonus présent dans le tableau supérieur
* \param tab : paramètre d'entrée/sortie qui représente le tableau des scores.
* \param joueur : paramètre d'entrée qui représente le joueur en train de jouer (0 pour le premier et 1 pour le deuxième).
*/
void calcul_bonus(t_score tab,int joueur) {
    int score=0;
    for (int i=0;i<6;i++) {
        if (tab[joueur][i]!=-1) {
            score=score+tab[joueur][i];
        }
    }
    if (score>62) {
        tab[joueur][6]=35;
    }
}

/**
* \fn void init_tableau(t_score tab)
* \brief Procédure qui initialise toutes les valeurs du tableau à ARRET
* \param tab : paramètre d'entrée/sortie qui représente le tableau des scores.
*/
void init_tableau(t_score tab) {
    for (int i=0;i<2;i++) {
        for (int j=0 ;j<17;j++) {
            tab[i][j]=ARRET;
        }
    }
}

/**
* \fn void tableau_score(int tour,t_score tab,pseudo20 pseudo)
* \brief Procédure qui affiche le tableau du joueur en train de jouer
* \param tour : paramètre d'entrée qui représente le tour.
* \param tab : paramètre d'entrée qui représente le tableau des scores.
* \param pseudo : paramètre d'entrée qui représente le pseudo du joueur en train de jouer.
*/
void tableau_score(int tour,t_score tab,pseudo20 pseudo) {
    int i;
    char space[8]="        ";
    i=tour % 2;
    system("clear");
    printf("Jeu du Yams\n");
    printf("╔═══════════════════════╦════════╗\n");
    printf("║%23s║ score  ║\n",pseudo);
    for (int j=0;j<8;j++) {
        printf("║%2d ║",j);
        printf("%19s║",chaine[j]);
        if (tab[i][j]!=-1) {
            printf("%8d║\n",tab[i][j]);
        }
        else {
            printf("%s║\n",space);
        }
    }
    printf("╚═══════════════════════╩════════╝\n\n");
    printf("╔═══════════════════════╦════════╗\n");
    printf("║%23s║ score  ║\n",pseudo);
    for (int j=8;j<16;j++) {
        printf("║%2d ║",j);
        printf("%19s║",chaine[j]);
        if (tab[i][j]!=-1) {
            printf("%8d║\n",tab[i][j]);
        }
        else {
            printf("%s║\n",space);
        }
    }
    printf("╚═══════════════════════╩════════╝\n");
    printf("╔═══════════════════════╦════════╗\n");
    printf("║%23s║",chaine[16]);
    if (tab[i][16]!=-1) {
            printf("%8d║\n",tab[i][16]);
        }
        else {
            printf("%s║\n",space);
        }
    printf("╚═══════════════════════╩════════╝\n\n");
}




/**
* \fn void lance_des(t_des tab)
* \brief Procédure qui génère une valeur entre 1 et 6 pour chacun des 5 dés
* \param tab : paramètre d'entrée qui représente le tableau des scores.
*/
void lance_des(t_des tab) {
    for (int i=0;i<5;i++) {
        tab[i]=(rand() % 6) +1;
    }
    tri_des(tab);
}

/**
* \fn  void relance_des(t_des tab)
* \brief Procédure qui relance les dés qui sont donnés par le joueur
* \param tab : paramètre d'entrée qui représente le tableau des scores.
*/
void relance_des(t_des tab) {
    int choixde;
    do
    {
        do
        {
            printf("Quel dé voulez-vous relancer ? (numéro de dé, valeur d'arrêt:%d) :",ARRET);
            scanf("%d",&choixde);
            if ((choixde<1 || choixde>5) && choixde!=ARRET) {
                printf("Numéro de dé érroné\n");
            }
        } while ((choixde<1 || choixde>5) && choixde!=ARRET);
        tab[choixde-1]=(rand() % 6) + 1;
    } while (choixde!=ARRET);
  tri_des(tab);
}

/**
* \fn pause()
* \brief Procédure qui mets en pause le jeu et qui atttends qu'un caractère est rentré puis entrée
*/
void pause() {
    chaine20 tmp;
    printf("Appuyez sur un caractère puis ENTREE pour continuer...");
    scanf("%s",tmp);
}

/**
* \fn void affichergagnant(t_score tab,pseudo20 pseudo1,pseudo20 pseudo2)
* \brief Procédure qui affiche le gagnant de la partie ainsi que les scores finaux des deux
* \param tab : paramètre d'entrée qui représente le tableau des scores.
* \param pseudo1 : paramètre d'entrée qui représente le pseudo du joueur numéro 1.
* \param pseudo2 : paramètre d'entrée qui représente le pseudo du joueur numéro 2.
*/
void affichergagnant(t_score tab,pseudo20 pseudo1,pseudo20 pseudo2) {
    if (tab[1][16]>tab[2][16]) {
        printf("Bravo %s, vous avez gagné la partie avec %d point, %s vous avez eu %d points, il y a donc %d point d'écart",pseudo1,tab[1][16],pseudo2,tab[2][16],tab[1][16]-tab[2][16]);
    }
    else if (tab[1][16]>tab[2][16]) {
        printf("Bravo %s, vous avez gagné la partie avec %d point, %s vous avez eu %d points, il y a donc %d point d'écart",pseudo2,tab[2][16],pseudo1,tab[1][16],tab[2][16]-tab[1][16]);
    }
    else {
        printf("Vous avez tous les deux un score de %d, il n'y a donc pas de gagnant",tab[1][16]);
    }
}

/**
* \fn void rangement_score(int tour,t_score tab_score,t_des tab_des)
* \brief Procédure qui demande l'emplacement dans lequel le joueur veut ranger son score.
* \param tour : paramètre d'entrée qui représente le tour.
* \param tab_score : paramètre d'entrée/sortie qui représente le tableau des scores.
* \param tab_des : paramètre d'entrée qui représente le tableau des dés.
*/
void rangement_score(int tour,t_score tab_score,t_des tab_des) {
    int rangement,i,calc;
    i=tour % 2;
    do
    {
        printf("A quel endroit voulez-vous ranger votre score : ");
        scanf("%d",&rangement);
        if (tab_score[i][rangement]!=ARRET) {
            printf("Valeur déjà attribuée ou impossible\n");
        }
    } while (((rangement<0 || rangement>5) && (rangement<8 || rangement>14)) || (tab_score[i][rangement]!=ARRET)); // quand la valeur>=0 et <=5 ou quand la valeur >=8 et la valeur <=14 ou quand la valeur est différente de la valeur d'arrêt
    if (rangement<6) {
        tab_score[i][rangement]=rangement_facile(tab_des,rangement+1);
    }
    switch (rangement)
    {
        case 8:
            tab_score[i][rangement]=rangement_brelan(tab_des);
            break;
        case 9:
            tab_score[i][rangement]=rangement_carre(tab_des);
            break;
        case 10:
            tab_score[i][rangement]=rangement_full_house(tab_des);
            break;
        case 11:
            if (suite_des(tab_des)>=4) {
                calc=30;
            }
            else {
                calc=0;
            }
            tab_score[i][rangement]=calc;
            break;
        case 12:
            if (suite_des(tab_des)==5) {
                calc=40;
            }
            else {
                calc=0;
            }
            tab_score[i][rangement]=calc;
            break;
        case 13:
            tab_score[i][rangement]=rangement_yams(tab_des);
            break;
        case 14:
            tab_score[i][rangement]=rangement_chance(tab_des);
            break;
    }
    maj_totaux(tab_score,i);
    calcul_bonus(tab_score,i);
}

/**
* \fn void afficher_des(t_des tab)
* \brief Procédure qui affiche les 5 dés
* \param tab : paramètre d'entrée qui représente le tableau des dés.
*/
void afficher_des(t_des tab) {
    printf("\n");
    printf("Numéro des dés :");
    printf("\n");
    for (int i=1;i<=N_DES;i++) {
        printf(" %d    ",i);
    }
    printf("\n");
    for (int i=0;i<5;i++) {
        for (int j=0;j<N_DES;j++) {
            printf("%s ",des[tab[j]-1][i]);
        }
        printf("\n");
    }
    printf("\n");
}

/**
* \fn int main()
* \brief Programme principal.
* \return Code de sortie du programme (0 : sortie normale).
* 
* Le programme principale gère le lancement des différentes procédures et fonctions
* il va boucler 26 fois, représentant les 13 tours pour les deux joueurs
*/
int main() {
    srand(time(NULL));
    t_score tab_score;
    t_des tab_des;
    int choix,relance;
    pseudo20 pseudo1,pseudo2,pseudotour;
    donner_pseudo(pseudo1);
    printf("pseudo valide\n");
    do {
        donner_pseudo(pseudo2);
        if (strcmp(pseudo1,pseudo2)==0) {
            printf("Erreur Pseudo identique\n");
        }
    } while (strcmp(pseudo1,pseudo2)==0);
    printf("pseudo valide\n");
    init_tableau(tab_score);
    for (int tour=0;tour<26;tour++) {
        relance=3;
        lance_des(tab_des);
        if (tour%2==0) {
            strcpy(pseudotour,pseudo1);
        }
        else {
            strcpy(pseudotour,pseudo2);
        }
        do {
            tableau_score(tour,tab_score,pseudotour);
            afficher_des(tab_des);
            do
            {
                printf(" Que voulez-vous faire (relance restante : %d) :1 relancer certains dés, 2 relancer tous les dés ,3 terminer tour: ",relance);
                scanf("%d",&choix);
                if (choix<1 || choix>3) {
                    printf("Valeur incorrecte\n");
                }
            } while (choix<1 || choix>3);
            switch (choix)
            {
            case 1:
                relance_des(tab_des);
                relance=relance-1;
                break;
            case 2:
                lance_des(tab_des);
                relance=relance-1;
                break;
            case 3:
                rangement_score(tour,tab_score,tab_des);
                tableau_score(tour,tab_score,pseudotour);
                pause();
                break;
            }
        } while (relance>0 && choix!=3);
        if (relance==0) {
            tableau_score(tour,tab_score,pseudotour);
            afficher_des(tab_des);
            rangement_score(tour,tab_score,tab_des);
            tableau_score(tour,tab_score,pseudotour);
            pause();
        }
    }
    affichergagnant(tab_score,pseudo1,pseudo2);
    return EXIT_SUCCESS;
}