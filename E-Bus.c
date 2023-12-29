#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    int jr,mois,an;
}date;
typedef struct {
    int h,min,s;
}heure;
typedef struct Bus {
    int IdBus,nbre_place_dispo;
    int place_dispo[100];

    char destina[50];
    date datedep;
    heure hrdep;
    int nbserv;
    char services[20][101];
    struct Bus *suiv;
}Bus  ;
 typedef struct  Reservation {
    int Idrres,IdBus,num_place;
    char nompassa[50];
    struct Reservation *suiv;
}Reservation;
 typedef struct Passager {
    int idpassager, numtel;
    char nompass[50],email[50];
    struct Passager *suiv;
} Passager;
int buscpmtr = 0;
int rescpmtr = 0;
int passcpmtr = 0;
Passager *passgr=NULL;
Reservation *reser=NULL;
Bus *b=NULL;
void ajoutpassager(Passager *nvpassager) {
    if (passgr == NULL) {
        passgr = nvpassager;
        passgr->suiv =NULL;
    } else {
        Passager* p = passgr;
        while (p->suiv != NULL)
           p= p->suiv;

        p->suiv = nvpassager;
        p->suiv->suiv=NULL;
    }
}
void ajoutbus(Bus *nvbus) {
    if (b == NULL) {
        b = nvbus;
        b->suiv =NULL;
    } else {
        Bus* p = b;
        while (p->suiv != NULL)
           p= p->suiv;

        p->suiv = nvbus;
        p->suiv->suiv=NULL;
    }
}
void ajoutres(Reservation *nvreser) {
    if (reser == NULL) {
        reser = nvreser;
        reser->suiv =NULL;
    } else {
        Reservation* p = reser;
        while (p->suiv != NULL)
           p= p->suiv;

        p->suiv = nvreser;
        p->suiv->suiv=NULL;
    }
}
void creer_nv_cpt() {
    Passager *poi = (Passager *)malloc(sizeof(Passager));
    printf("Veuillez entrer votre nom : \n");
    scanf("%s",&poi->nompass);
    printf("Veuillez entrer votre email  : \n");
    scanf("%s", &poi->email);
    printf("Veuillez entrer votre numero de telephone :\n ");
    scanf("%d",  &poi->numtel);
    poi->idpassager =passcpmtr+1;
    poi->suiv = NULL;
    printf("Compte cree avec succes.\n");
       if (passgr == NULL){
        ajoutpassager(poi);
        passgr = poi;
        passgr->suiv =NULL;
    } else {
        Passager* poi = poi;
        while (poi->suiv != NULL)
           poi= poi->suiv;

        poi->suiv = poi;
        poi->suiv->suiv=NULL;
    }

}
void creerbus() {
    Bus *p = (Bus *)malloc(sizeof(Bus));
    printf("Entrez l'identifiant du bus :\n ");
    scanf("%d",  &p->IdBus);
    printf("Entrez le nombre de places disponibles dans le bus :\n ");
    scanf("%d",  &p->nbre_place_dispo);
   printf("Entrez la destination du bus :\n ");
   for (int i = 0; i < p->nbre_place_dispo; i++)p->place_dispo[i]=0;
    scanf("%s",  &p->destina);
     printf("Entrez la date de depart du bus dans la format jj/mm/aaaa :\n ");
    scanf("%d/%d/%d",  &p->datedep.jr,&p->datedep.mois,&p->datedep.an);
    printf("Entrez l'heure' de depart du bus  dans la format hh:mm:ss :\n ");
    scanf("%s",  &p->hrdep.h,&p->hrdep.min,&p->hrdep.s);
    printf("Entrez le nombre des services valables dans le bus :\n ");
    scanf("%d",  &p->nbserv);
    
    printf("Entrez les services valables dans le bus :\n ");
    for (int i = 0; i < p->nbserv; i++)
    scanf("%s",  &p->services[i]);
    ajoutbus(p);
    if (b == NULL) {
        b = p;
        b->suiv =NULL;
    } else {
        Bus* p = b;
        while (p->suiv != NULL)
           p= p->suiv;

        p->suiv = p;
        p->suiv->suiv=NULL;
    }
    printf("bus ajoute avec succees \n ");
}
void details_bus() {
    Bus *q=b;
    while(q != NULL) {
         printf("Idantifiant : %d\n Destination : %s\n nombre de places disponibles : %d\n les numeros des places disponibles dans le bus:",
               q->IdBus, q->destina,q->nbre_place_dispo);
        for (int i = 0; i < q->nbre_place_dispo; i++)
         if(q->place_dispo[i]==0)
          printf("%d,",i);
          printf("\n");
         printf("date de depart: %d/%d/%d à  %d:%d:%d\n  servises valables: \n", q->datedep.jr, q->datedep.mois,q->datedep.an,q->hrdep.h,q->hrdep.min,q->hrdep.s);
         for (int i = 0; i < q->nbserv; i++)
          printf("-%s,",q->services[i]);} 
           printf("\n");
       
        q = q->suiv;
    }


void creer_res() {

    Reservation *p = (Reservation *)malloc(sizeof(Reservation));
    printf("Entrez le nom du voyageur: ");
    scanf("%s", &p->nompassa);
    printf("les bus disponibles sont :\n");
    details_bus(b);
    int nb=0;Bus *l=b;
    while(nb==0){
    nb=0;l=b;
    printf("Entrez l'identifiant du bus choisi : ");
    scanf("%d\n", &p->IdBus);
    
     while (nb==0 & l!=NULL){
        if(l->place_dispo[p->num_place]==0&& l->IdBus==p->IdBus)
        nb++;
         l=l->suiv;
    }
        if(nb==0)printf("Bus complet!");
    }
    int nbre=1;Bus *h=b;
    while(nbre==1){
     h=b;   
    nbre=0;
    printf("Veuillez entrer le numero de la place choisi : ");
    scanf("%d\n", &p->num_place);
    while (nbre==0 & h!=NULL){
        if(h->place_dispo[p->num_place]==1&& h->IdBus==p->IdBus)
        nbre++;
        h=h->suiv;
    }
    if(nbre==1)
    printf("place deja reservee.\n");}
    printf("reservation faite avec succees\n");
    ajoutres(p);
}



// Fonction pour afficher les détails d'une réservation
void afficherReservation(Reservation *head) {
    Reservation *current = head;

    if (current == NULL) {
        printf("La liste des réservations est vide.\n");
        return;
    }

    printf("Détails des réservations :\n");

    while (current != NULL) {
        printf("ID de la réservation : %d\n", current->Idrres);
        printf("Nom du passager : %s\n", current->nompassa);
        printf("ID du bus : %d\n", current->IdBus);
        printf("Numéro de la place : %d\n", current->num_place);
      }}                                                                                                                                                                                                                      // Fonction pour modifier les détails d'une réservation
void modifierReservation(int idrreservation, char nouveauNom[50], int nouveaunum_place, int nouveauIdB) {
    Reservation *current = reser;

    while (current != NULL) {
        if (current->Idrres == idrreservation) {
            // La réservation a été trouvée, effectuez les modifications
            current->num_place = nouveaunum_place;
            current->IdBus = nouveauIdB;
            printf("Modification de la réservation effectuée avec succès.\n");
            return; // Sortez de la fonction après la modification
        }
        current = current->suiv;
    }

    // Si la réservation n'a pas été trouvée
    printf("Réservation non trouvée. Aucune modification effectuée.\n");
}
int main() {
    int m=0;
    int x,y=0;
    char nouveauNom[50];
    int nouveaunum_place;
    int nouveauIdres;
    int nouveauIdB;
    int Idrreservation;
   do{
    printf("bienvenus!\n s'il vous plait choisis votre status comme utulisateur:\n 1-voyageur\n 2-employe\n");
         scanf("%d", &x);
          
    }while(x!=1&&x!=2);
    
    if(x==2){
        while(!y){
         printf("1- Ajouter un bus a la base de donnee \n");
         printf("2- Afficher les details des bus. \n");
          printf("0- Sortir de l'application \n \n");
        scanf("%d",&y);}
         switch (y)
         {
          case 0:
              break;
          case 1:
              creerbus();
              break;
          case 2:
              details_bus();
              break;

          break;}}
    else{
        while(!y){
            printf("1- Ajouter un nouveau compte. \n");
            printf("2- Creer une nouvelle resevetion. \n");
            printf("3- Afficher les details des bus. \n");
            printf("4- afficher les details d'une reservation. \n");
            printf("5- Modifier les details d'une reservation. \n");
            printf("0- Sortir de l'application \n \n");
        }
         switch (y)
         {
          case 0:
              break;
          case 1:
               creer_nv_cpt();
           case 2:
              creer_res();
           case 3:
              details_bus();
           case 5:
              printf("Que voulez vous modifier \n");
              printf("entrez le numero de reservation \n");
              scanf("%d",&Idrreservation);
            printf("1- Le numero du bus.\n");
            scanf("%d", &nouveauIdB);
            printf("2- Le numero du place.\n");
            scanf("%d", &nouveaunum_place);
            printf("3- Le nom de voyageur.\n");
            scanf("%s", &nouveauNom);
            modifierReservation(Idrreservation, nouveauNom, nouveaunum_place, nouveauIdB);
            break;
         }  
      }
}