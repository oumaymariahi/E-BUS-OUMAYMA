#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>


struct Voyageur {
    char nom[15];
    char prenom[15];
    char email[15];
    char motDePasse[15];
    int CIN; 
};

struct Reservation{
    int id;
    char nomV[15]; //nom du voyageur
    char date[10];
    int numBus;
    char desti[20]; //destination 
    
    
};

struct Bus{
    int numBus ;
    int capacite; 
    char destination[20];
    char etat[20]; //l'etat d'un Bus (en panne ou fonctionnel) 
    
};

typedef struct Voyageur Voyageur;
typedef struct Reservation Reservation;
typedef struct Bus Bus;


int NOMBRE_DES_LIGNES(char nom_fichier[15]){
    //fonction qui retourne le nombre des lignes d'un fichier
    FILE *fichier;
    char ch[256];
    int i=0;
    fichier = fopen(nom_fichier,"r");

    while ((fgets (ch,256,fichier)) != NULL){
        i++;
    }
    fclose(fichier);
    return i;
}


int recherche_indice(Voyageur *tab, int n , int x) /*l'entr�e x est le CIN du Voyageur*/
{   //fonction qui renvoie l'indice du voyageur dans le tableau grace à son num de CIN
    for (int i = 0; i <= n ; i++)
    {
        if (tab[i].CIN == x)
        {
            return i;
        }
    }
    return -1;
}


int RECHERCHER( Voyageur *tab,int n ,int x ){
    //chercher si le produit existe deja ou non
    int indice ;
    indice=recherche_indice(tab,n,x);


    if (indice != -1 ) {
        printf("voyageur existant \n");
        return indice;
        
       
    }
    else{
        printf("voyageur inexistant \n");
        return -1;
        
    }

}

int creerCompteVoyageur(char nomfichier[20] , Voyageur *tab, int n){

    // Fonction pour créer un compte de voyageur et stocker les informations dans un fichier
    int x;
    printf("Entrez votre CIN:");
    scanf("%d",&x);

    int indice ;
    indice=recherche_indice(tab,n,x);
    
    if (indice == -1 ) {
        tab[n].CIN=x;

        printf("Entrez votre nom :");
        scanf("%s",&tab[n].nom);

        printf("Entrez votre prenom :");
        scanf("%s",&tab[n].prenom);

        printf("Entrez votre adresse e-mail :");
        scanf("%s",&tab[n].email);

        printf("Entrez votre mot de passe :");
        scanf("%s",&tab[n].motDePasse); 


        FILE *fp ;
        fp = fopen(nomfichier, "a");


        fprintf(fp, "%s | %s | %d | %s | %s\n ", (tab[n].nom) ,(tab[n].prenom),(tab[n].CIN),tab[n].email, tab[n].motDePasse); 
        fclose(fp);


        printf("votre compte a ete cree avec succes\n");
        return n+1;
   
    } else {
         printf("voyageur deja existant \n");
         return n;

    }
    
    
}

int SeConnecterVoyageur(Voyageur *tab , int n , int x){
    char code[20];
    char email[20];

    printf("donner votre email\n");
    scanf("%s",&email);
    printf("donner votre Mot de passe\n");
    scanf("%s",&code);

    int indice;
    indice=recherche_indice(tab,n,x);

    if (tab[indice].motDePasse==code){
        printf("Bienvenue dans E-BUS");

    }else{
        printf("Mot De passe incorrecte.REESSAYER\n");

    }

    return 0;
   
}



int AfficherHistorique(Reservation *res, int n){
   
    for(int i=0; i<n; i++){
        printf("%d | %s | %s | %s | %d ", res[i].id, res[i].nomV, res[i].desti, res[i].date, res[i].numBus);
    }
}

int RechercheIndiceR(Reservation *tab, int n , int x) /*l'entree x est l'ID du reservation*/
{   //fonction qui renvoie l'indice du reservation dans le tableau grace à son ID
    for (int i = 0; i < n ; i++)
    {
        if (tab[i].id == x)
        {
            return i;
        }
    }
    return -1;
}



void StockReservations ( Reservation  Res, char state, char filename[20] ) { //Historique des reservations
    FILE *f ;
    f = fopen(filename,"a");
    fprintf(f,"%s  %s  %s  %d  %s  %d  %d ", state , Res.date, Res.desti , Res.id , Res.nomV, Res.numBus ); 
    fclose(f); //le parametre state indique l'etat de la reservation (annulée ou confirmée)
}



int AnnulerReservation( Reservation * tab , int n ){
    //Cette fonction permet d'annuler une reservation 
    int x;
    printf("Donner votre id");
    scanf("%d",&x);
    int indice = RechercheIndiceR(tab ,n, x);
    if (indice ==-1){
        printf("id introuvable");
        return n;
    }else {
        StockReservations ( tab[indice],"Annulee", "Reservation.txt" );
        for (int i=indice; i<n-1; i++){
            tab[i]=tab[i+1];
        }
        printf("Votre Réservation a ete annulee avec succes\n");
        return n-1;
        
    }

}


int ModifierDate( Reservation *tab, int n){ 
    // Modifier la date d'une reservation
    int x;
    printf("Donner votre id");
    scanf("%d",&x);

    int indice = RechercheIndiceR(tab ,n,x);    
    if (indice==-1){
        printf("id introuvable\n");
    }else{
        
        AnnulerReservation(tab,n);

        printf("Donner la nouvelle date ");
        scanf("%s",&tab[indice].date);

        
        StockReservations(tab[indice],"confirmee","Rservation.txt");
    }
    return 0;
}





int creerReservation( Reservation *tab, int n) { 
    //creer une reservation
    int x;
    printf("donner votre id de reservation\n");
    scanf("%d", &x);

    int i = RechercheIndiceR(tab, n, x);

    if (i != -1) {
        printf("vous avez deja rserve.\n");
    } else {
        i = n;

        printf("Entrez votre nom ");
        scanf("%s", &tab[i].nomV);

        printf("Donnez la date de reservation ");
        scanf("%s", &tab[i].date);

        printf("Quelle est votre destination ? ");
        scanf("%s", &tab[i].desti);

        printf("Donner le numero du Bus. ");
        scanf("%d", &tab[i].numBus); 

        

    
        StockReservations(tab[i], "confirmee", "Reservations.txt"); 
        printf("  **  Votre reservation a ete bien enregistree  **   \n");
    }
    return 0;
}



int RechercheIndiceB(Bus * tab, int n , int x) /*l'entr�e x est le num du Bus*/
{   //fonction qui renvoie l'indice du bus dans le tableau grace à son numBUS

    for (int i = 0; i < n ; i++)
    {
        if (tab[i].numBus== x)
        {
            return i;
        }
    }
    return -1;
}

void AJOUTER_AU_FICHIER_DES_BUS(char nom_fichier[15],Bus x){
    //ajouter toutes les informations d'un bus dans fichier

    FILE * fichier;
    fichier=fopen(nom_fichier,"a");
    fprintf(fichier,"%d %d %s %s \n", x.numBus, x.capacite, x.destination, x.etat);
    fclose(fichier);
}

int AjouterBus(Bus * tab,int  n){
    //fonction qui ajoute un Bus 

    int i,x;
    printf("Donner le numero du bus a ajouter :");
    scanf("%d",&(x));
    i=RechercheIndiceB(tab,n,x);
    if (i!= -1 ) {
        printf("Produit existant. \n");
        return n;
    }
    else{
        i=n;
        tab[i].numBus=x;
        printf("Donner l'etat du bus a ajouter : ");
        scanf("%s",&tab[i].etat);
        printf("Donner la capacite du bus a ajouter : ");
        scanf("%d",&tab[i].capacite);
        printf("Donner la destination du bus a ajouter : ");
        scanf("%s",&tab[i].destination);

        AJOUTER_AU_FICHIER_DES_BUS("Bus.txt",tab[i]);

        printf("\nAjout effectuee avec succes. \n");
        return n+1;
        }
}


void AFFICHER_LA_DESCRIPTION_BUS(Bus * tab, int n){
    // Afficher la description d'un bus
    int i,x;
    printf("Donner le numero du Bus : ");
    scanf("%d",&x);
    i=RechercheIndiceB(tab,n,x);
    if(i!=-1){
        printf("Le nombre des places occupees dans le Bus est %d .\n",tab[i].capacite);
        printf("Sa destination est %s .\n",tab[i].destination);
        printf("Le Bus est %s. \n",tab[i].etat);
    }else{
        printf("Numero invalide. \n");
    }

}


void Parametres(){
        char choix[5],choix2[5];

    printf("(1) Changer le couleur du texte au blanc \n");
    printf("(2) Changer le couleur du texte au bleu \n");
    printf("(3) Changer le couleur du texte au rouge \n");
    printf("(4) Changer le couleur du texte au vert \n");
    printf("(5) Changer le couleur du texte au noir \n");
    printf("Votre Choix :");
    scanf("%s",&choix);

    printf("\n(1) Changer le couleur de l'arriere-plan au blanc \n");
    printf("(2) Changer le couleur de l'arriere-plan au bleu \n");
    printf("(3) Changer le couleur de l'arriere-plan au rouge \n");
    printf("(4) Changer le couleur de l'arriere-plan au vert \n");
    printf("(5) Changer le couleur de l'arriere-plan au noir \n");
    printf("Votre Choix :");
    scanf("%s",&choix2);

    switch(atoi(choix)){
    case 1 :
        {
            switch(atoi(choix2)){
            case 2 :
            {
                system("COLOR 97");
                break;
            }
            case 3 :
            {
                system("COLOR 47");
                break;
            }
            case 4 :
            {
                system("COLOR 27");
                break;
            }
            case 5 :
            {
                system("COLOR 07");
                break;
            }
            }
            break;
        }
    case 2 :
        {
            switch(atoi(choix2)){
            case 1 :
            {
                system("COLOR 79");
                break;
            }
            case 3 :
            {
                system("COLOR 49");
                break;
            }
            case 4 :
            {
                system("COLOR 29");
                break;
            }
            case 5 :
            {
                system("COLOR 09");
                break;
            }
            }
            break;
        }
    case 3 :
        {
            switch(atoi(choix2)){
            case 1 :
            {
                system("COLOR 74");
                break;
            }
            case 2 :
            {
                system("COLOR 94");
                break;
            }
            case 4 :
            {
                system("COLOR 24");
                break;
            }
            case 5 :
            {
                system("COLOR 04");
                break;
            }
            }
            break;
        }
    case 4 :
        {
            switch(atoi(choix2)){
            case 1 :
            {
                system("COLOR 72");
                break;
            }
            case 2 :
            {
                system("COLOR 92");
                break;
            }
            case 3 :
            {
                system("COLOR 42");
                break;
            }
            case 5 :
            {
                system("COLOR 02");
                break;
            }
            }
            break;
        }
    case 5 :
        {
            switch(atoi(choix2)){
            case 1 :
            {
                system("COLOR 70");
                break;
            }
            case 2 :
            {
                system("COLOR 90");
                break;
            }
            case 3 :
            {
                system("COLOR 40");
                break;
            }
            case 4 :
            {
                system("COLOR 20");
                break;
            }

            }
            break;
        }
    }
}


int REMPLIRE_LE_TABLEAU_V(char nom_fichier[15], Voyageur * tab){           
     //fonction qui remplie le tableau des voyageurs en cours et retourne sa taille

    FILE * fichier;
    int n;

    fichier=fopen(nom_fichier,"a");
    fclose(fichier);

    n=NOMBRE_DES_LIGNES(nom_fichier);

    fichier=fopen(nom_fichier,"r");
    if (fichier != NULL){
        for(int i=0;i<n;i++){
            fscanf(fichier,"%s %s %s %s %d\n",&(tab[i].nom),&(tab[i].prenom),&(tab[i].email),&(tab[i].motDePasse) ,&(tab[i].CIN));
        }
        fclose(fichier);
    }
    return n;
}

int REMPLIRE_LE_TABLEAU_R(char nom_fichier[15], Reservation * tab){            
    //fonction qui remplie le tableau des reservation en cours et retourne sa taille

    FILE * fichier;
    int n,i;

    fichier=fopen(nom_fichier,"a");
    fclose(fichier);

    n=NOMBRE_DES_LIGNES(nom_fichier);

    fichier=fopen(nom_fichier,"r");
    if (fichier != NULL){
        for(i=0;i<n;i++){
            fscanf(fichier,"%s %s %d %s %d %d  \n",&(tab[i].date),&(tab[i].desti),&(tab[i].id),&(tab[i].nomV) ,&(tab[i].numBus) );
        }
        fclose(fichier);
    }
    return n;
}

int REMPLIRE_LE_TABLEAU_B( FILE *nomf ,Bus *tab){            
    //fonction qui remplit le tableau des Bus  et retourne sa taille
    FILE * fichier;
    int n,i;
    fichier=fopen(nomf,"a");
    fclose(fichier);

    n=NOMBRE_DES_LIGNES(nomf);

    fichier=fopen(nomf,"r");
    if (fichier != NULL){
        for(i=0;i<n;i++){
            fscanf(fichier,"%d %d %s %s\n",&(tab[i].numBus),&(tab[i].capacite),&(tab[i].etat),&(tab[i].destination) );
        }
        fclose(fichier);
    }
    return n;
}


int main()
{
char choix[5];
Voyageur V[20];
Reservation R[20];
Bus B[20];
int n,m,l;
char a[10];

n=REMPLIRE_LE_TABLEAU_V("Voyageur.txt",V);
m=REMPLIRE_LE_TABLEAU_R("Rservation.txt",R);
l=REMPLIRE_LE_TABLEAU_B("Bus.txt",B);




while(atoi(choix)!=10){                 //atoi() convertir un  string en un integer

    printf("\n   - RESERVATION DE BUS - \n\n");
    printf("(1) Acceder a votre compte Voyageur \n(2) Creer un compte Voyageur \n");
    printf("(3) Faire une Reservation \n(4) Annuler une Reservation \n");
    printf("(5) Modifier la date d'une reservation \n(6) Ajouter un bus \n(7) Afficher la description d'un Bus \n");
    printf("(8) Afficher les historiques \n(9) Parametres \n");
    printf("(10) Quitter le programme \n\n");
    printf("Votre choix: ");
    scanf("%s",&choix);

    while(atoi(choix)<1 || atoi(choix)>10){
        system("cls");              //clear console screen

         printf("\n   - RESERVATION DE BUS -\n\n");
    printf("(1) Acceder à votre compte Voyageur \n(2) Creer un compte Voyageur \n");
    printf("(3) Faire une Reservation \n(4)  Annuler une Reservation \n");
    printf("(5) Modifier la date d'une reservation \n(6)  Ajouter un bus \n(7) Afficher la description d'un Bus \n");
    printf("(7) Afficher les historiques \n(8) Parametres \n");
    printf("(9) Quitter le programme \n\n");
    printf("Votre choix: ");
    scanf("%s",&choix);
    }

    switch(atoi(choix)){

      case 1 :
      {
          system("cls");
          int CIN;
          printf("Donner votre CIN\n");
          scanf("%d",&CIN); 

          int indice = RECHERCHER(V,n,CIN);

          if (indice !=-1){
            SeConnecterVoyageur(V,n,CIN); 

          }


          printf("\n(0)  Retour au menu principale\n");
          scanf("%s",&a);
          break;
      }
      case 2 :
      {
          system("cls");

          n=creerCompteVoyageur("voyageur.txt",V,n);
          

          printf("\n(0)  Retour au menu principale\n");
          scanf("%s",&a);
          break;
      }
      case 3 :
      {
          system("cls");

          m=creerReservation(R,n);

          printf("\n(0)  Retour au menu principale\n");
          scanf("%s",&a);
          break;
      }
      case 4 :
      {
          system("cls");

          m=AnnulerReservation(R,n);

          printf("\n(0)  Retour au menu principale\n");
          scanf("%s",&a);
          break;
      }
      case 5 :
      {
          system("cls");

          ModifierDate(R,n);

          printf("\n(0)  Retour au menu principale\n");
          scanf("%s",&a);
          break;
      }
      case 6 :
      {
          system("cls");

          l=AjouterBus(B,l);

          printf("\n(0)  Retour au menu principale\n");
          scanf("%s",&a);
          break;
      }
      case 7 :
      {
          system("cls");

          AFFICHER_LA_DESCRIPTION_BUS(B,l);

          printf("\n(0)  Retour au menu principale\n");
          scanf("%s",&a);
          break;
      }
      case 8 :
      {
          system("cls");

         
          AfficherHistorique(R,m);

          printf("\n(0)  Retour au menu principale\n");
          scanf("%s",&a);
          break;
      }
      case 9 :
      {
          system("cls");

          Parametres();

          printf("\n(0)  Retour au menu principale\n");
          scanf("%s",&a);
          break;
      }
    }
    system("cls");
}
printf("Vous avez quitte l'application. ");

}






