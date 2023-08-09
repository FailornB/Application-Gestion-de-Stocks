#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>
#define ID "CP2"
#define MDP "gestionstock"
#define ENTER 13
#define BACKSPACE 8
#define SPACE 32
#define TAB 9

// Nous choisissons des fichiers DAT pour stocker des informations



//définition de la structure du produit
struct article //définition de la structure du produit
{
	char nomproduit[40],fournisseur[40],c;
	int idproduit;
	int prix_unitaire;
	int quantite;
}produit ;

//définition de la stucture du client
struct client
{
    char nomclient[40],c;
    int idclient;
    int numproduitclient;
}client ;

//déplacer curseur
void gotoxy(short x, short y)
{
    COORD pos ={x,y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

// fonction principale
void main()
{
    //mdp();
    menu();
}









//Fonction affichant les 3 produits qui ont été le plus vendu.
void top_vente(){

    //Declaration des variables
    FILE *top = fopen("Top_vente.dat","r");
    char nom_produit[40];
    int quantite_vendue;
    int qnt_la_plus_grande = 0;
    int qnt_la_plus_grande_sauv1;
    int qnt_la_plus_grande_sauv2;
    int nombre_ligne=0;
    int nb_pr=0;

    //Si le fichier est vide
    if(fgetc(top) == EOF){
        printf("Il n'y a pas encore eu de ventes pour le moment\n");
        return;
    }



    // On determine la quantite vendue la plus grande sauvegardée dans le fichier
    rewind(top);
    while(fscanf(top,"%s %i", nom_produit, &quantite_vendue)==2){
        if(quantite_vendue>qnt_la_plus_grande){
            qnt_la_plus_grande = quantite_vendue;
        }
        nombre_ligne++;
    }
    // On affiche le nom du produit correspondant à cette valeur
    rewind(top);
    while(fscanf(top,"%s %i", nom_produit, &quantite_vendue)==2){
        if(quantite_vendue==qnt_la_plus_grande && nb_pr ==0){
            printf("Le produit qui a ete le plus vendu est %s avec %i kg de ventes!\n", nom_produit, qnt_la_plus_grande);
            nb_pr = 1;
        }
    }



    // On sauvegarde la quantite du produit le plus vendu pour eviter de réafficher le top 1
    qnt_la_plus_grande_sauv1 = qnt_la_plus_grande;
    qnt_la_plus_grande = 0;
    nb_pr =0;



    // Meme procédure pour le second produit le plus vendu.
    // On determine la seconde quantite vendue la plus grande dans le fichier
    rewind(top);
    while(fscanf(top,"%s %i", nom_produit, &quantite_vendue)==2){
        if(nombre_ligne<2){
            printf("il n'y a qu'un seul produit pour le moment\n");
            return;
        }
        if (quantite_vendue == qnt_la_plus_grande_sauv1){
            continue;
        }
        if(quantite_vendue>qnt_la_plus_grande){
            qnt_la_plus_grande = quantite_vendue;
        }
    }
    // On affiche le nom du produit correspondant à cette valeur
    rewind(top);
    while(fscanf(top,"%s %i", nom_produit, &quantite_vendue)==2){
        if(nombre_ligne<2){
            return;
        }
        if(quantite_vendue==qnt_la_plus_grande && nb_pr ==0){
            printf("Le second produit qui a ete le plus vendu est %s avec %i kg de ventes!\n", nom_produit, qnt_la_plus_grande);
            nb_pr =1;
        }
    }



    // On sauvegarde la seconde quantite du produit le plus vendu pour eviter de réafficher le top 2
    qnt_la_plus_grande_sauv2 = qnt_la_plus_grande;
    qnt_la_plus_grande = 0;
    nb_pr =0;

    // Meme procédure pour la troisieme plus grande quantite vendue
    // On determine la troisieme quantite vendue la plus grande dans le fichier
    rewind(top);
    while(fscanf(top,"%s %i", nom_produit, &quantite_vendue)==2){
        if(nombre_ligne<3){
            printf("Il n'y a que deux produits pour le moment\n");
            return;
        }
        if (quantite_vendue == qnt_la_plus_grande_sauv2 || quantite_vendue == qnt_la_plus_grande_sauv1 ){
            continue;
        }
        if(quantite_vendue>qnt_la_plus_grande){
            qnt_la_plus_grande = quantite_vendue;
        }
    }
    // On affiche le nom du produit correspondant à cette valeur
    rewind(top);
    while(fscanf(top,"%s %i", nom_produit, &quantite_vendue)==2){
        if(quantite_vendue==qnt_la_plus_grande && nb_pr ==0){
            printf("Le troisieme produit qui a ete le plus vendu est %s avec %i kg de ventes!\n", nom_produit, qnt_la_plus_grande);
            nb_pr =1;
        }
    }

    fclose(top);
    return;
}
















// Fonction permettant la vente des produits en stock
void vendre()
{
    // déclaration des variables de type fichier et necessaires à l'affichage des produits
	FILE *f, *file, *t,*h, *top, *top2, *cli,*cli2;

	produit;
	int i, q;
	time_t mnt;
	time(&mnt);
	char nom_client[40];

	//vérification si fichier catalogue est Nul
	if((f=fopen("Catalogue.dat","r"))==NULL)
	{

		gotoxy(10,3);
		printf("AUCUN PRODUIT");
		printf("\n\t\t Pressez une touche pour revenir au menu ");
		getch();
		menu();
	}

	//Affichage de la liste des produits
	else
	{
		gotoxy(0,5);
			for(i=0;i<100;i++)
		{
			printf("-");
		}

		gotoxy(5,6);
		printf("Nom Produit");
		gotoxy(25,6);
		printf("ID Produit");
		gotoxy(40,6);
		printf("Fournisseur");
		gotoxy(60,6);
		printf("Prix unitaire (eur)");
		gotoxy(80,6);
		printf("Quantite (kg)\n");

		for(i=0;i<100;i++)
		{
			printf("-");
		}
		q=8;
		while(fscanf(f,"%s %s %i %i %i\n", produit.nomproduit,produit.fournisseur, &produit.prix_unitaire, &produit.idproduit,&produit.quantite)!=EOF)
		{
			gotoxy(5,q);
			printf("%s",produit.nomproduit);
			gotoxy(25,q);
			printf("%i",produit.idproduit);
			gotoxy(40,q);
			printf("%s",produit.fournisseur);
			gotoxy(60,q);
			printf("%i",produit.prix_unitaire);
			gotoxy(80,q);
			printf("%i",produit.quantite);

			q++;
		}
		printf("\n");
		for(i=0;i<100;i++){
			printf("-");
		}
	}
	fclose(f);
    gotoxy(40,14);


    // Declaration des variables
    char recherche[40];
    char texte[256];
    char nom_produit[40];
    int quantite_vendue;
	int trouver=0;
	int trouver2 = 0;
	int qnt;
	int nb_ligne = 0;
	int num_facture ;
	int nb_achats_client;
	char nom_client_fic[40];
	int choix;
	int id_fic;

	// Ouverture des fichiers
	file=fopen("Catalogue.dat","r+");
	t =fopen("CatalogueTemp.dat","w+");
	h = fopen("Historique.dat","a");
	f = fopen("Facture.dat","r+");
	top = fopen("Top_vente.dat","r+");
	top2 = fopen("Top_vente_temp.dat","w+");
	cli = fopen("Clients.dat","r+");
	cli2 = fopen("ClientsTemp.dat","a+");

	//Commencement de la vente
	printf("\nQuel client etes vous (nom): ");
	fflush(stdin);
	gets(nom_client);
	nom_client[0]=toupper(nom_client[0]);
	// On verifie si le client existe dans le fichier Client, si non, on  propose de l'enregistrer.
	while(fscanf(cli,"%s %i %i", &nom_client_fic, &id_fic, &nb_achats_client)==3 && trouver2==0){

        if(strcmp(nom_client,nom_client_fic)==0){

            trouver2 = 1;
        }
	}
	if(trouver2!=1){
        printf("Ce client n'a pas encore ete sauvegarde dans notre base de donnees, tapez 1 pour ajouter un client, sinon tapez 2 pour retournez au menu produit\n");
        printf("Votre choix :");
        fflush(stdin);
        scanf("%i", &choix);
        switch(choix){
            case 1:
                enregistrclient();
                break;
            case 2:
                menuproduit();
                break;
            default:
                printf("Choix non valide\n");
                getch();
                menuproduit();
            }
	}

	printf("\nEntrez un nom de produit a acheter : ");
    fflush(stdin);
	gets(recherche);
	recherche[0]=toupper(recherche[0]);

	//vérification si le nom de la recherche est le même que l'un des produits
	while (!feof(file) && trouver==0)
	{
		fscanf(file,"%s %s %i %i %i", produit.nomproduit, produit.fournisseur, &produit.prix_unitaire, &produit.idproduit,&produit.quantite);
		nb_ligne ++;
		if(strcmp(recherche, produit.nomproduit)==0)
		{
			trouver=1;
		}
	}

	// La vente se poursuit si le produit est trouvé
    if(trouver)
    {
        printf("\n Quelle quantite, voulez vous acheter ? ");
        scanf("%d",&qnt);

        rewind(file); //réinitialise le flux en placant la tête de lecture en début de fichier
        for(int i =0; i<nb_ligne; i++)
            fscanf(file,"%s %s %i %i %i", produit.nomproduit, produit.fournisseur, &produit.prix_unitaire, &produit.idproduit,&produit.quantite);

        // Si demande une quantite indisponible
        if(qnt>produit.quantite)
        {
            printf("Valeur superieur a la quantite disponible");
            printf("\n\n=======================================================");
            printf("\nAppuyez sur une touche pour revenir au menu produit ");
            printf("\n=======================================================");
            while((produit.c = getch()) =='\r');
            fclose(file);
            fclose(t);
            fclose(h);
            fclose(top);
            fclose(top2);
            menuproduit();
        }


        //Si quantité demandée est égale à la quantité disponible
        if(qnt==produit.quantite)
        {
            //On complète l'historique
            fprintf(h,"%s a achete %i kg de %s le %s", nom_client, qnt, recherche, ctime(&mnt));

            // On crée la facture
            fseek(h,0,SEEK_END);
            num_facture = ftell(h)/44; // compte le nombre d'éléments


            fseek(f,0,SEEK_END);
            fputs("                                                  ---------\n",f);
            fputs("                                                  |FACTURE|\n",f);
            fputs("                                                  ---------\n",f);
            fputs("                                                   \n\n",f);
            fprintf(f,"Facture du client %s                                         Facture n°%d \n", nom_client,num_facture);
            fprintf(f,"                                                            Date:%s \n", ctime(&mnt));
            fputs("Quantité                     Produit                       Prix unité                    Montant \n",f);
            fprintf(f,"%i                            %s                             %i                             %i \n\n", qnt,produit.nomproduit,produit.prix_unitaire,qnt*produit.prix_unitaire);
            fprintf(f,"                                                                                   TOTAL:%i \n\n",qnt*produit.prix_unitaire);
            fputs("Merci d'avoir choisi notre entreprise!\n", f);
            // fin de la facture

            // affichage d'informations pour l'acheteur
            printf("Vous avez achete %i kg de %s\n", produit.quantite, produit.nomproduit);
            printf("La quantite du produit en stock est maintenant nulle.");

            // On modifie les quantités en stock suite à l'achat
            rewind(file);
            while(fscanf(file,"%s %s %i %i %i", produit.nomproduit, produit.fournisseur, &produit.prix_unitaire, &produit.idproduit,&produit.quantite)==5){
                if(strcmp(produit.nomproduit,recherche)!=0){
                    fprintf(t,"%s %s %i %i %i\n",produit.nomproduit,produit.fournisseur,produit.prix_unitaire,produit.idproduit,produit.quantite);
                }
            }

            // On ajoute la quantité vendue dans le fichier sauvegardant le nombre total de vente pour un produit(utile pour le top 3 des ventes)
            rewind(top);
            while(fscanf(top,"%s %d", &nom_produit, &quantite_vendue)==2){
                if (strcmp(nom_produit,produit.nomproduit)!=0){
                    fprintf(top2,"%s %d\n", nom_produit, quantite_vendue);
                }
            }

            rewind(top);
            while(fscanf(top,"%s %d", &nom_produit, &quantite_vendue)==2){
                if (strcmp(nom_produit,produit.nomproduit)==0){
                    quantite_vendue = quantite_vendue+qnt;
                    fprintf(top2,"%s %d\n", nom_produit, quantite_vendue);
                }
            }


            // On itere un a la valeur de nombre d'achat effectues par le client en question
            rewind(cli);
            while(fscanf(cli,"%s %i %i", &nom_client_fic, &id_fic, &nb_achats_client)==3){
                if(strcmp(nom_client,nom_client_fic)!=0){
                    fprintf(cli2,"%s %i %i \n", nom_client_fic, id_fic ,nb_achats_client);
                }
            }
            rewind(cli);
            while(fscanf(cli,"%s %i %i", &nom_client_fic, &id_fic,&nb_achats_client)==3){
                if(strcmp(nom_client,nom_client_fic)==0){
                    nb_achats_client++;
                    fprintf(cli2,"%s %i %i\n", nom_client_fic, id_fic,nb_achats_client);
                }
            }

            // fermeture des fichiers
            fclose(file);
            fclose(t);
            fclose(h);
            fclose(f);
            fclose(top);
            fclose(top2);
            fclose(cli);
            fclose(cli2);

            remove("Top_vente.dat"); //supprime le fichier pas à jour
            rename("Top_vente_temp.dat","Top_vente.dat");//renommer le fichier Temp par le fichier définitif
            remove("Catalogue.dat");// De même pour le fichier Catalogue
            rename("CatalogueTemp.dat","Catalogue.dat");
            remove("Client.dat"); //De même pour le fichier Client
            rename("ClientTemp.dat","Client.dat");
        }

        //Si quantité inférieure à la quantité disponible
        if(qnt<produit.quantite)
        {
            //On complète l'historique
            fprintf(h,"%s a achete %i kg de %s le %s", nom_client, qnt, recherche, ctime(&mnt));

            // On crée la facture
            fseek(h,0,SEEK_END);
            num_facture = ftell(h)/44;

            fseek(f,0,SEEK_END);
            fputs("                                                  ---------\n",f);
            fputs("                                                  |FACTURE|\n",f);
            fputs("                                                  ---------\n",f);
            fputs("                                                   \n\n",f);
            fprintf(f,"Facture du client %s                                         Facture n°%d \n", nom_client,num_facture);
            fprintf(f,"                                                            Date:%s \n", ctime(&mnt));
            fputs("Quantité                     Produit                       Prix unité                    Montant \n",f);
            fprintf(f,"%i                            %s                             %i                             %i \n\n", qnt,produit.nomproduit,produit.prix_unitaire,qnt*produit.prix_unitaire);
            fprintf(f,"                                                                                   TOTAL:%i \n\n",qnt*produit.prix_unitaire);
            fputs("Merci d'avoir choisi notre entreprise!\n", f);
            // fin de la facture

            // Information pour l'acheteur
            printf("Vous avez achete %i kg de %s\n", qnt, produit.nomproduit);


            // On modifie les quantités en stock suite à l'achat
            rewind(file);
            while(fscanf(file,"%s %s %i %i %i", produit.nomproduit, produit.fournisseur, &produit.prix_unitaire, &produit.idproduit,&produit.quantite)==5){
                if(strcmp(produit.nomproduit,recherche)!=0){
                    fprintf(t,"%s %s %i %i %i\n",produit.nomproduit,produit.fournisseur,produit.prix_unitaire,produit.idproduit,produit.quantite);
                }
            }
            rewind(file);
            while(fscanf(file,"%s %s %i %i %i", produit.nomproduit, produit.fournisseur, &produit.prix_unitaire, &produit.idproduit,&produit.quantite)==5){
                if(strcmp(produit.nomproduit,recherche)==0){
                    fprintf(t,"%s %s %i %i %i\n",produit.nomproduit,produit.fournisseur,produit.prix_unitaire,produit.idproduit,produit.quantite-qnt);
                    // Seuil d'alerte
                    if(produit.quantite-qnt <200)
                        printf("ALERTE! : LE PRODUIT DOIT ETRE REAPPROVISIONNE, La quantite en stock est descendue sous la barre des 200 kg");
                }
            }

            // On ajoute la quantité vendue dans le fichier sauvegardant le nombre total de ventes pour chaque produit(utile pour le top 3 des ventes).
            rewind(top);
            while(fscanf(top,"%s %d", nom_produit, &quantite_vendue)==2){
                if (strcmp(nom_produit,recherche)!=0){
                    fprintf(top2,"%s %d\n", nom_produit, quantite_vendue);
                }
            }

            rewind(top);
            while(fscanf(top,"%s %d", nom_produit, &quantite_vendue)==2){
                if (strcmp(nom_produit,recherche)==0){
                    quantite_vendue = quantite_vendue+qnt;
                    fprintf(top2,"%s %d\n", nom_produit, quantite_vendue);
                }
            }

            // On itere un a la valeur de nombre d'achat effectues par le client en question
            rewind(cli);
            while(fscanf(cli,"%s %i %i", nom_client_fic, &id_fic, &nb_achats_client)==3){
                if(strcmp(nom_client,nom_client_fic)!=0){
                    fprintf(cli2,"%s %i %i\n", nom_client_fic, id_fic ,nb_achats_client);
                }
            }
            rewind(cli);
            while(fscanf(cli,"%s %i %i", nom_client_fic, &id_fic, &nb_achats_client)==3){
                if(strcmp(nom_client,nom_client_fic)==0){
                    nb_achats_client++;
                    fprintf(cli2,"%s %i %i\n", nom_client_fic, id_fic,nb_achats_client);
                }
            }

            // Fermeture des fichiers
            fclose(file);
            fclose(t);
            fclose(h);
            fclose(f);
            fclose(top);
            fclose(top2);
            fclose(cli);
            fclose(cli2);

            remove("Top_vente.dat"); //supprime le fichier pas à jour
            rename("Top_vente_temp.dat","Top_vente.dat");//renommer le fichier Temp par le fichier définitif
            remove("Catalogue.dat"); //De même pour le fichier catalogue
            rename("CatalogueTemp.dat","Catalogue.dat");
            remove("Clients.dat"); //De même pour le fichier Client
            rename("ClientsTemp.dat","Clients.dat");

        }
    }

    //Si le produit n'est pas trouvé
    else
    {
        printf("Aucun produit nomme %s existe", recherche);
        fclose(file);
        fclose(t);
        fclose(h);
        fclose(f);
        fclose(top);
        fclose(top2);
    }
    printf("\n Pressez une touche pour revenir au menu");
    while((produit.c = getch()) =='\r');
    menu();

}









// Fonction damandant le mot de passe
void mdp(){

    char c,id[20],mdp[20],chainemdp[20];
    int nb,i;
    do
    {

        system("CLS"); // efface tout ce qu'il y a à l'écran
        printf("Nom  d'utilisateur : ");
        scanf("%s",id);
        if(strcmp(id,ID)!=0)
        {
            printf("Nom d'utilisateur invalide !");
            getch();
        }
    }while(strcmp(id,ID)!=0);
    do
    {
        printf("Mot de passe : ");
        nb=0;
        while((c=getch())!=ENTER)
        {
            if(c!=BACKSPACE && nb<20)
            {
                chainemdp[nb]=c;
                nb++;
                printf("*"); //Remplace les lettres par des * pour le mot de passe
            }
            else
            {
                if(nb>0)
                {
                    //Pour gérer l'effacement
                    nb--;
                   chainemdp[nb]='\0';
                }
            }
        }
        //On copie tous les caractères contenu dans la chaine
        for(i=0;i<nb;i++)
        {
            mdp[i]=chainemdp[i];
        }
        mdp[i]='\0'; //On indique le caractère de fin de ligne
        if(strcmp(mdp,MDP)!=0)
        {
            printf("\nMot de passe invalide \a\n");
        }
    }while(strcmp(mdp,MDP)!=0);
	system("cls");
}












// Fonction menu Produit
void menuproduit()
{
    //Declaration variables
    int choix;
    int choix2;
	system("cls");
	time_t t;
	time(&t);
	FILE *h = fopen("Historique.dat","r");
	char texte[70];

	printf("                                                                                                         \n");
	printf("-----------------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\t\t\t\t%s",ctime(&t));
	printf("-----------------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n");
	printf("|---------------------------------------------------- Menu -----------------------------------------------------|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t <1> Ajouter un produit\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t <2> Supprimer un produit\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t <3> Rechercher un produit\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t <4> Consulter la liste des produits\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t <5> Modifier un produit\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t <6> Vendre un produit\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t <7> Consulter l'historique des ventes\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t <8> Consulter les 3 produits au top des ventes\t\t\t|\n");
	printf("|\t\t\t\t\t\t <9> Quitter\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|---------------------------------------------------------------------------------------------------------------|\n");
	printf("\n\n\t\tVotre choix ? ");
	scanf("%i", &choix);

	system("cls");

    //On lance la fonction correspondant au choix de l'utilisateur
	switch(choix)
	{
		case 1:
			ajouter();
			break;
		case 2:
			supprimer();
			break;
		case 3:
		    printf("\t\tRechercher avec ? :\n");
		    printf("\n\t\t <1> LE NOM \n");
		    printf("\t\t <2> LE FOURNISSEUR\n");
		    printf("\t\t <3> LE CODE\n");
		    scanf("%i", &choix2);
		    switch(choix2)
		    {
                case 1:
                    rechercherparnom();
                    break;
                case 2:
                    rechercherparfournisseur();
                    break;
                case 3:
                    rechercherparid();
                    break;
                default:
                    printf("Choix non valide");
                    getch();
                    menuproduit();
		    }
		case 4:
            afficher_liste();
			break;
		case 5:
			printf("\t\tModifier avec ? :\n");
		    printf("\n\t\t <1> LE CODE \n");
		    printf("\t\t <2> LE NOM\n");
		    scanf("%i", &choix2);
		    switch(choix2)
		    {
                case 1:
                    modifier();
                    break;
                case 2:
                    modifierparnom();
                    break;
                default:
                    printf("Choix non valide");
                    getch();
                    menuproduit();
		    }
        case 6:
            vendre();
            break;
        case 7:
            if(h == NULL)
                printf("Pas encore de ventes effectuees");
            while(fgets(texte,70,h)!=NULL)
                printf("%s\n",texte);
            printf("\n\n=======================================================");
            printf("\nAppuyez sur une touche pour revenir au menu produit ");
            printf("\n=======================================================");
            while((produit.c = getch()) =='\r');
            menuproduit();
			break;
        case 8:
            top_vente();
            printf("\n\n=======================================================");
            printf("\nAppuyez sur une touche pour revenir au menu produit ");
            printf("\n=======================================================");
            while((produit.c = getch()) =='\r');
            menuproduit();
			break;
		case 9:
            printf("Fin d'application");
            exit(0);
            break;
        default:
            printf("Choix non valide\n");
            getch();
			menu();
	}
    fclose(h);
}












//Fonction menu client
void menuclient()
{
    //Declaration variables
    int choix;
    int choix2;
	system("cls");
	time_t t;
	time(&t);
	FILE *h=fopen("Historique.dat","r");
	char texte[70];

	printf("                                                                                                         \n");
	printf("-----------------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\t\t\t\t%s",ctime(&t));
	printf("-----------------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n");
	printf("|---------------------------------------------------- Menu -----------------------------------------------------|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t <1> Ajouter un client\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t <2> Supprimer un client\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t <3> Rechercher un client\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t <4> Consulter la liste des clients\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t <5> Modifier un client\t\t\t\t\t\t|\n");
	//printf("|\t\t\t\t\t\t <6> Consulter l'historique des achats\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t <6> Quitter\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|---------------------------------------------------------------------------------------------------------------|\n");
	printf("\n\n\t\tVotre choix ? ");
	scanf("%i", &choix);
    system("cls");

    //On lance la fonction correspondant au choix de l'utilisateur
    switch(choix)
	{
		case 1:
			enregistrclient();
			break;
		case 2:
			supprimerclient();
			break;
		case 3:
		    printf("\t\tRechercher avec ? :\n");
		    printf("\n\t\t <1> LE NOM \n");
		    printf("\t\t <2> LE CODE\n");
		    scanf("%i", &choix2);
		    switch(choix2)
		    {
                case 1:
                    rechercherclientparnom();
                    break;
                case 2:
                    rechercherclientparid();
                    break;
                default:
                    printf("Choix non valide");
                    getch();
                    menuproduit();
		    }
		case 4:
            afficher_client();
			break;
		case 5:
		    printf("\t\tModifier avec ? :\n");
		    printf("\n\t\t <1> LE CODE \n");
		    printf("\t\t <2> LE NOM\n");
		    scanf("%i", &choix2);
		    switch(choix2)
		    {
                case 1:
                    modifierclient();
                    break;
                case 2:
                    modifierclientparnom();
                    break;
                default:
                    printf("Choix non valide");
                    getch();
                    menuclient();
		    }
		case 6:
            printf("Fin d'application");
            exit(0);
            break;


		default:
            printf("Choix non valide\n");
            getch();
			menu();
	}
    fclose(h);
}











//Fonction du menu principal de l'application
void menu()
{
    //Declaration variables
	int choix;
	FILE *aide = NULL; //déclaration d'une variable aide de type fichier
	char ecrire;
	time_t t;
	time(&t);


	system("cls");
	printf("                                                                                                         \n");
	printf("-----------------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\t\t\t\t%s",ctime(&t));
	printf("-----------------------------------------------------------------------------------------------------------------\n");
	printf("\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\n");
	printf("|---------------------------------------------------- Menu -----------------------------------------------------|\n");
    printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t <1> Menu produit\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t <2> Menu client\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t <3> Aide\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t <4> Quitter\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|\t\t\t\t\t\t\t\t\t\t\t\t\t\t|\n");
	printf("|---------------------------------------------------------------------------------------------------------------|\n");
	printf("\n\n\t\tVotre choix ? ");
	scanf("%i", &choix);

	system("cls");

	//On lance la fonction correspondant au choix de l'utilisateur
	switch(choix)
	{
		case 1:
			menuproduit();
			break;
		case 2:
			menuclient();
			break;
		case 3:
		    //affiche l aide
            printf("\n\n");
            aide = fopen("aide.txt", "r");
            while ((ecrire =fgetc(aide))!=EOF){
                    printf("%c",ecrire);
            }
            printf("\n\n=======================================================");
            printf("\nAppuyez sur une touche pour revenir au menu principal ");
            printf("\n=======================================================");
            while((produit.c = getch()) =='\r');
            menu();
			break;

		case 4:
            printf("Fin d'application");
            exit(0);
            break;


		default:
            printf("Choix non valide\n");
            getch();
			menu();
	}

}
















// Fonction ajoutant un produit au stock
void ajouter()
{
    //Declaration variables
	produit;
	int index, valid;
	char c;
	int a=0;
	FILE *fp;
    FILE *top;

	do
	{
		system("cls");
		printf("============ Entrez les details du produit ============");
		int testID; //variable pour savoir si le code est deja assigné

		//ouverture et création du fichier
		fp = fopen("Catalogue.dat","a+");

        // Demande ID du produit
		if((fp = fopen("Catalogue.dat","a+"))!=NULL) // vérification si fichier est NULL
		{
			I:
			printf("\nCode du produit\t :");
			scanf("%i",&testID);
			while(fscanf(fp,"%s %s %i %i %i", produit.nomproduit, produit.fournisseur, &produit.prix_unitaire, &produit.idproduit,&produit.quantite)!=EOF)
			{

				if(testID == produit.idproduit)
				{
					printf("\n\tLe code du produit est deja assigne.\n");
					goto I; //permet de se repositionner sur la saisie du code car déjà assigné
				}
			}
			produit.idproduit = testID;
		}
		else
		{
			printf("\nCode du produit\t :");
			scanf("%i",&produit.idproduit);
		}

        //Demande nom du produit
		do
		{

			fflush(stdin);
			printf("\nNom du produit\t :");
			gets(produit.nomproduit); // obtenir chaine d'entrée
			produit.nomproduit[0]=toupper(produit.nomproduit[0]);
			// itération pour chaque caractère de la chaîne
			for (index=0; index<strlen(produit.nomproduit); ++index)
			{	// vérification caractères (lettres)
				if(isalpha(produit.nomproduit[index]))
					valid = 1;
				else
				{
					valid = 0;
					break;
				}
			}
			if (!valid)
			{
				printf("\n Ce nom contient des caracteres invalides. Entrez les details a nouveau");
				getch(); //lit un caractère au clavier


			}
		}while(!valid);


        //Demande fournisseur du produit
        do
		{
			char fournisseur[40];
			fflush(stdin);
			printf("\nFournisseur du produit\t :");
			gets(produit.fournisseur);
			produit.fournisseur[0]=toupper(produit.fournisseur[0]);

			for (index=0; index<strlen(produit.fournisseur); ++index)
			{
				if(isalpha(produit.fournisseur[index]))
					valid = 1;
				else
				{
					valid = 0;
					break;
				}
			}
			if (!valid)
			{
				printf("\n Ce nom contient des caracteres invalides. Entrez les details a nouveau");
				getch();


			}
		}while(!valid);

        //Demande prix unitaire du produit
        printf("\nPrix unitaire du produit\t :");
        scanf("%i", &produit.prix_unitaire);

        //Demande quantite du produit
        printf("\nQuantite :");
        scanf("%i",&produit.quantite);

        // On ecrit toutes les infos dans le fichier catalogue et on ecrit le nom du produit suivi du nombre de ventes dans le fichier top_vente.
		fp=fopen("Catalogue.dat","a");
		top = fopen("Top_vente.dat","a");
		fprintf(fp,"\n%s %s %i %i %i\n", produit.nomproduit, produit.fournisseur,produit.prix_unitaire, produit.idproduit,produit.quantite);
		fprintf(top,"%s %i", produit.nomproduit, 0);

		// Seuil d'alerte
		if(produit.quantite<200)
                    printf("ALERTE! : LE PRODUIT DEVRAIT ETRE REAPPROVISIONNER, La quantite du produit en stock est sous la barre des 200 kg");
        //Fermeture des fichiers
		fclose(fp);
		fclose(top);

		printf("\n 'Entree' pour ajouter d'autres produits ou une autre touche pour revenir au menu");

	}
	while((c = getch()) =='\r');
	menu(); //Retour au menu principal
}














// Fonction ajoutant les clients
void enregistrclient()
{
    //Declaration variables
	client;
	int index, valid;
	char c;
	int a=0;
	FILE *fp;

    do
	{
		system("cls");
		printf("============ Entrez les details du client ============");
		int testID;
		fp = fopen("Clients.dat","a+");

        //Demande ID du client
		if((fp = fopen("Clients.dat","a+"))!=NULL)
		{
			I:
			printf("\nCode du client\t :");
			scanf("%i",&testID);
			while(fscanf(fp,"%s %i %i", client.nomclient, &client.idclient, &client.numproduitclient)!=EOF)
			{
				if(testID == client.idclient)
				{
					printf("\n\tLe code du client est deja assigne.\n");
					goto I;
				}
			}
			client.idclient = testID;
		}
		else
		{
			printf("\nCode du client\t :");
			scanf("%i",&client.idclient);
		}

	    //Demande nom du client
		do
		{
			fflush(stdin);
			printf("\nNom du client\t :");
			gets(client.nomclient);
			client.nomclient[0]=toupper(client.nomclient[0]);
			for (index=0; index<strlen(client.nomclient); ++index)
			{
				if(isalpha(client.nomclient[index]))
					valid = 1;
				else
				{
					valid = 0;
					break;
				}
			}
			if (!valid)
			{
				printf("\n Ce nom contient des caracteres invalides. Entrez les details a nouveau");
				getch();


			}
		}while(!valid);


        printf("\nNombre de fois que le client a achete dans l'entreprise:");
        scanf("%i",&client.numproduitclient);

        //On ecrit les infos dans le fichier Clients.
		fp=fopen("Clients.dat","a");
		fprintf(fp,"%s %i %i\n", client.nomclient, client.idclient,client.numproduitclient);
		fclose(fp);

		printf("\n 'Entree' pour ajouter d'autres produits ou une autre touche pour revenir au menu");

	}
	while((c = getch()) =='\r');
	menu();
}












//Fonction recherchant le client par le nom
void rechercherclientparnom()
{
    //Declaration variables
	char recherche[40];
	client;
	int trouver=0;
	FILE *sfile;

	sfile=fopen("Clients.dat","r");
	printf("\nEntrez un nom de client :");
	fflush(stdin); //effacer le tampon de sortie et déplace les données mises en tampon
	gets(recherche);
	recherche[0]=toupper(recherche[0]);

	//On cherche le nom dans le fichier
	while (!feof(sfile) && trouver==0)
	{
		fscanf(sfile,"%s %i %i", client.nomclient, &client.idclient,&client.numproduitclient);
		if(strcmp(recherche, client.nomclient)==0)
		{
			trouver=1;
		}
	}

    //On affiche le client et ses caracteristiques si on le trouve
	if(trouver)
	{
		printf("\n Client trouve");
		printf("\nNom du client\t\t:%s  \nID du client\t\t:%i \nNombre d'achats\t\t\t:%i", client.nomclient, client.idclient,client.numproduitclient);

	}
	else
		printf("Aucun client nomme %s existe", recherche);

    fclose(sfile);
    printf("\n Pressez une touche pour revenir au menu");
    while((client.c = getch()) =='\r');
    menu();

}












//Focntion recherchant le client par l'id
void rechercherclientparid()
{
    //Declaration variables
	int recherche;
	client;
	int trouver=0;
	FILE *sfile;

	sfile=fopen("Clients.dat","r");
	printf("Entrez le code du client :");
	scanf("%i", &recherche);
    fflush(stdin);

    //On cherche l'ID dans le fichier
    while (!feof(sfile) && trouver==0)
	{
		fscanf(sfile,"%s %i %i", client.nomclient, &client.idclient, &client.numproduitclient);
		if(recherche==client.idclient)
		{
			trouver=1;
		}
	}

	//On affiche le client et ses caracteristiques si on le trouve
	if(trouver)
	{
		printf("\n Client trouve\n");
		printf("\nNom du client\t\t:%s  \nID du client\t\t:%i \nNombre d'achats\t\t\t:%i", client.nomclient, client.idclient,client.numproduitclient);

	}
	else{
		printf("Aucun client avec l ID %i existe", recherche);

		fclose(sfile);
		printf("\n Pressez une touche pour revenir au menu");
		while((client.c = getch()) =='\r');
		menu();
	}
	while((client.c = getch()) =='\r');
    menu();


}












//Fonction recherchant le produit par le nom
void rechercherparnom()
{
    //Declaration variables
	char recherche[40];
	produit;
	int trouver=0;
	FILE *sfile;

	sfile=fopen("Catalogue.dat","r");
	printf("\nEntrez un nom de produit :");
	fflush(stdin);
	gets(recherche);
	recherche[0]=toupper(recherche[0]);

	//On cherche le nom du produit dans le fichier
	while (!feof(sfile) && trouver==0)
	{
		fscanf(sfile,"%s %s %i %i %i", produit.nomproduit, produit.fournisseur, &produit.prix_unitaire, &produit.idproduit,&produit.quantite);
		if(strcmp(recherche, produit.nomproduit)==0)
		{
			trouver=1;
		}
	}
    //On affiche le produit et ses caracteristiques si on le trouve
	if(trouver)
	{
		printf("\n Produit trouve");
		printf("\nNom du produit\t\t:%s  \nPays de provenance du produit\t\t:%s \nPrix unitaire du produit\t\t:%i \nID du produit\t\t:%i \nQuantite\t:%i", produit.nomproduit, produit.fournisseur, produit.prix_unitaire, produit.idproduit, produit.quantite);

	}
	else
		printf("Aucun produit nomme %s existe", recherche);

		fclose(sfile);
    printf("\n Pressez une touche pour revenir au menu");
    while((produit.c = getch()) =='\r');
    menu();

}















//Fonction recherchant le produit par le fournisseur
void rechercherparfournisseur()
{
    //Declaration variables
	char recherche[40];
	produit;
	int trouver=0;
	FILE *sfile;

	sfile=fopen("Catalogue.dat","r");
	printf("\nEntrez le fournisseur de produit :");
	fflush(stdin);
	gets(recherche);
	recherche[0]=toupper(recherche[0]);

	//On cherche le fournisseur dans le fichier
	while (!feof(sfile) && trouver==0)
	{
		fscanf(sfile,"%s %s %i %i %i", produit.nomproduit, produit.fournisseur, &produit.prix_unitaire, &produit.idproduit,&produit.quantite);
		if(strcmp(recherche, produit.fournisseur)==0)
		{
			trouver=1;
		}
	}
    //On affiche le produit correspondant au fournisseur et ses caracteristiques si on le trouve
	if(trouver)
	{
		printf("\n Produit trouve");
		printf("\nNom du produit\t\t:%s  \nFournisseur\t\t:%s \nPrix unitaire du produit\t\t:%i \nID du produit\t\t:%i \nQuantite\t:%i", produit.nomproduit, produit.fournisseur, produit.prix_unitaire, produit.idproduit, produit.quantite);

	}
	else
		printf("Aucun produit provenant de %s existe", recherche);

    fclose(sfile);
    printf("\n Pressez une touche pour revenir au menu");
    while((produit.c = getch()) =='\r');
    menu();

}










//Fonction recherchant le produit par l'id
void rechercherparid()
{
    //Declaration variables
	int recherche;
	produit;
	int trouver=0;
	FILE *sfile;

	sfile=fopen("Catalogue.dat","r");
	printf("Entrez le code du produit :");
	scanf("%i", &recherche);
    fflush(stdin);

    //On cherche L'ID dan sle fichier
    while (!feof(sfile) && trouver==0)
	{
		fscanf(sfile,"%s %s %i %i %i", produit.nomproduit, produit.fournisseur, &produit.prix_unitaire, &produit.idproduit,&produit.quantite);
		if(recherche==produit.idproduit)
		{
			trouver=1;
		}
	}
    //On affiche le produit correspondant à l'ID et ses caractéristiques si on le trouve
	if(trouver)
	{
		printf("\n Produit trouve");
		printf("\nNom du produit\t\t:%s  \nPays de provenance du produit\t\t:%s \nPrix unitaire du produit\t\t:%i \nID du produit\t\t:%i \nQuantite\t:%i", produit.nomproduit, produit.fournisseur, produit.prix_unitaire, produit.idproduit, produit.quantite);

	}
	else
		printf("Aucun produit provenant de %s existe", recherche);

    fclose(sfile);
    printf("\n Pressez une touche pour revenir au menu");
    while((produit.c = getch()) =='\r');
    menu();

}













// Fonction supprimant un produit
void supprimer(void)
{
    //Declaration variables
	char recherche[40];
	produit;
	int trouver=0;
	FILE *sfile, *tfile;
	//Ouverture des fichiers
	sfile=fopen("Catalogue.dat","r");
	tfile=fopen("CatalogueTemp.dat","w+"); //utilisation d'un fichier temporaire pour sauvegarder les modifications du produit

	printf("\n Entrez le nom du produit : ");
	fflush(stdin);
	scanf("%s",recherche);
	recherche[0]=toupper(recherche[0]);

	//On cherche le nom du produit dans le fichier et si il est trouvé, on ne l'écrit pas dans le fichier temp comme les autres
	while (fscanf(sfile,"%s %s %i %i %i\n",produit.nomproduit,produit.fournisseur, &produit.prix_unitaire,&produit.idproduit,&produit.quantite)!=EOF)
	{
		if(strcmp(recherche,produit.nomproduit)==0)
		{
			trouver=1;
		}
		else
		{
			fprintf(tfile,"%s %s %i %i %i\n", produit.nomproduit,produit.fournisseur, produit.prix_unitaire,produit.idproduit,produit.quantite);
		}
	}
            //On informe l'utilisateur si le produit a ete supprimé
			if(!trouver)
			{
				printf("\n Ce produit n'existe pas ");
				getch();
				menu();
			}

			else
			{
				printf("\n Produit supprime\n");
				printf("La quantite du produit en stock est maintenant nulle.");
			}
			//Fermeture des fichiers
			fclose(sfile);
			fclose(tfile);
			// On remplace l'ancien fichier par le nouveau.
			remove("Catalogue.dat");
			rename("CatalogueTemp.dat","Catalogue.dat");



			printf("\n Pressez une touche pour revenir au menu ");
    while((produit.c = getch()) =='\r');
    menu();
}












//Fonction supprimant un client
void supprimerclient(void)
{
    //Declaration variables
	char recherche[40];
	client;
	int trouver=0;
	FILE *sfile, *tfile;
	//Ouverture fichiers
	sfile=fopen("Clients.dat","r");
	tfile=fopen("ClientsTemp.dat","w+");

	printf("\n Entrez le nom du client : ");
	fflush(stdin);
	scanf("%s",recherche);
	recherche[0]=toupper(recherche[0]);

	//De meme, on cherche le nom du client dans le fichier et si il est trouvé, on ne l'écrit pas dans le fichier temp comme les autres
	while (fscanf(sfile,"%s %i %i\n",client.nomclient, &client.idclient, &client.numproduitclient)!=EOF)
	{
		if(strcmp(recherche,client.nomclient)==0)
		{
			trouver=1;
		}
		else
		{
			fprintf(tfile,"%s %i %i\n", client.nomclient, client.idclient, client.numproduitclient);
		}
	}
            //On informe l'utilisateur si le produit a ete supprimé
			if(!trouver)
			{
				printf("\n Ce client n'existe pas ");
				getch();
				menu();
			}
			else
			{
				printf("\n Client supprime");
			}

			//Fermeture des fichiers
			fclose(sfile);
			fclose(tfile);
			// On remplace l'ancien fichier par le nouveau.
			remove("Clients.dat");
			rename("ClientsTemp.dat","Clients.dat");

			printf("\n Pressez une touche pour revenir au menu ");
    while((client.c = getch()) =='\r');
    menu();
}














//Fonction affichant tous les produits en stock
void afficher_liste()
{
    //Declaration des variables
	FILE *f;
	produit;
	int i, q;

	//On verifie s il y a des produits en stocks
	if((f=fopen("Catalogue.dat","r"))==NULL)
	{

		gotoxy(10,3);
		printf("AUCUN PRODUIT");
		printf("\n\t\t Pressez une touche pour revenir au menu ");
		getch();
		menu();


	}

	//Si il y a des produits dans le fichier, on les affiche avec leurs caractéristiques.
	else
	{

		gotoxy(0,5);
			for(i=0;i<100;i++)
		{
			printf("-");
		}
        // En-tête du tableau
		gotoxy(5,6);
		printf("Nom Produit");
		gotoxy(25,6);
		printf("ID Produit");
		gotoxy(40,6);
		printf("Fournisseur");
		gotoxy(60,6);
		printf("Prix unitaire (eur)");
		gotoxy(80,6);
		printf("Quantite (kg)\n");

		for(i=0;i<100;i++)
		{
			printf("-");
		}
		q=8;
		while(fscanf(f,"%s %s %i %i %i\n", produit.nomproduit,produit.fournisseur, &produit.prix_unitaire, &produit.idproduit,&produit.quantite)!=EOF)
		{
		    // Affichage des caractéristiques des produits
			gotoxy(5,q);
			printf("%s",produit.nomproduit);
			gotoxy(25,q);
			printf("%i",produit.idproduit);
			gotoxy(40,q);
			printf("%s",produit.fournisseur);
			gotoxy(60,q);
			printf("%i",produit.prix_unitaire);
			gotoxy(80,q);
			printf("%i",produit.quantite);

			q++;
		}
		printf("\n");
		for(i=0;i<100;i++){
			printf("-");
		}
	}

	fclose(f);

    gotoxy(40,14);
	printf("\n Pressez une touche pour revenir au menu ");
    getch();
    menu();
}














//Fonction affichant tous les clients
void afficher_client()
{
    //Declaration variables
	FILE *f=fopen("Clients.dat","r");
	client;
	int i, q;
	rewind(f);
	//On verifie s'il y a des clients dans le fichier
	if(fgetc(f)==EOF)
	{

		gotoxy(10,3);
		printf("AUCUN CLIENT");
		printf("\n\t\t Pressez une touche pour revenir au menu ");
		getch();
		menu();


	}
	//S'il y en a, on les affiche avec leurs caracteristiques
	else
	{

		gotoxy(0,5);
			for(i=0;i<70;i++)
		{
			printf("-");
		}

		gotoxy(5,6);
		printf("Nom Client");
		gotoxy(25,6);
		printf("ID Client");
		gotoxy(40,6);
		printf("Nombre d'achats");
        gotoxy(0,7);
		for(i=0;i<70;i++)
		{
			printf("-");
		}
		q=8;
		rewind(f);
		while(fscanf(f,"%s %i %i\n", client.nomclient,&client.idclient,&client.numproduitclient)!=EOF)
		{
			gotoxy(5,q);
			printf("%s",client.nomclient);
			gotoxy(25,q);
			printf("%i",client.idclient);
			gotoxy(40,q);
			printf("%i",client.numproduitclient);

			q++;
		}
		printf("\n");
		for(i=0;i<70;i++){
			printf("-");
		}
	}
	fclose(f);

    gotoxy(40,14);
	printf("\n Pressez une touche pour revenir au menu ");
    getch();
    menu();
}















//Fonction modifiant les informations du produit via l'ID
void modifier()
{
    //Declaration variables
	int index, valid;
	produit;
	FILE *fp, *rp, *an;
	int a=0;
	char ancien_nom[40];
	char ancien_fournisseur[40];
	int ancien_prix;
	int ancien_id;
	int ancienne_qnt;
	int id;
	char edit;
	long int size=sizeof(a);
	//On verifie s'il y a des produits dans le fichier
	if((fp=fopen("Catalogue.dat","r+"))==NULL)
	{
		printf("AUCUN PRODUIT ");
		menu();
	}
	//S'il y en a, on demande l ID du produit a modifier
	else
	{
		rp = fopen("CatalogueTemp.dat","a");
		system("cls");
		printf("Entrez le code du produit a modifier :");
		scanf("%i",&id);
		fflush(stdin);
		while(fscanf(fp,"%s %s %i %i %i\n", produit.nomproduit,produit.fournisseur, &produit.prix_unitaire, &produit.idproduit,&produit.quantite)!=EOF)
		{
		    //On affiche les caracteristiques du produit si trouvé et on demande les nouvelles
			if(id==produit.idproduit)
			{
                for(int j=0;j<strlen(produit.nomproduit);j++){
                    ancien_nom[j] = produit.nomproduit[j];
                    ancien_fournisseur[j] = produit.fournisseur[j];
                }
                ancien_prix = produit.prix_unitaire;
                ancien_id = produit.idproduit;
                ancienne_qnt = produit.quantite;

				a=1;
				printf("\n\t*****  Produit trouve *****");
				printf("\nNom du produit\t\t: %s",produit.nomproduit);
				printf("\nFournisseur\t\t: %s",produit.fournisseur);
				printf("\nPrix unitaire\t\t\t: %i",produit.prix_unitaire);
				printf("\nID Produit\t\t: %i",produit.idproduit);
				printf("\nQuantite\t:%i",produit.quantite);

				printf("\n\n\t*** Nouvel enregistrement ***");
			do
				{
                    // Nouveau nom du produit
					fflush(stdin);
					printf("\nNouveau nom du produit\t\t: ");
					gets(produit.nomproduit);
					produit.nomproduit[0]=toupper(produit.nomproduit[0]);
					for (index=0; index<strlen(produit.nomproduit); ++index)
					{
						if(isalpha(produit.nomproduit[index]))
							valid = 1;
						else
						{
							valid = 0;
							break;
						}
					}
					if (!valid)
					{
						printf("\n Ce nom contient des caracteres invalides. Entrez les details a nouveau ");
						getch();


					}
				}while(!valid);

				do
				{
				    //Nouveau fournisseur du produit
					char fournisseur[40];
					fflush(stdin);
					printf("\nNouveau fournisseur du produit\t\t:");
					gets(produit.fournisseur);
					produit.fournisseur[0]=toupper(produit.fournisseur[0]);
					for (index=0; index<strlen(produit.fournisseur); ++index)
					{
						if(isalpha(produit.fournisseur[index]))
							valid = 1;
						else
						{
							valid = 0;
							break;
						}
					}
					if (!valid)
					{
						printf("\n Ce nom contient des caracteres invalides. Entrez les details a nouveau ");
						getch();


					}
				}while(!valid);

				// Nouveau prix, ID et quantité
				printf("\nNouveau prix :");
				scanf("%i",&produit.prix_unitaire);
				printf("\nNouveau ID du produit\t\t:");
				scanf("%i",&produit.idproduit);
				printf("\nNouvelle quantite\t:");
				scanf("%i",&produit.quantite);

				printf(" 'C' pour confirmer les changements ou une autre touche pour annuler ");
				edit=getche();
				if(edit=='c' || edit=='C')
				{
					fprintf(rp,"%s %s %i %i %i\n", produit.nomproduit, produit.fournisseur, produit.prix_unitaire, produit.idproduit,produit.quantite);
					fflush(stdin);
					printf("\n\n\t\tLes modifications ont ete enregistrees\n ");
					// Seuil d'alerte
                    if(produit.quantite<200)
                        printf("ALERTE! : LE PRODUIT DOIT ETRE REAPPROVISIONNE, La quantite en stock est descendue sous la barre des 200 kg");
				}
				else{
                    printf("\nModification annulee");
                    fprintf(rp,"%s %s %i %i %i\n", ancien_nom, ancien_fournisseur, ancien_prix, ancien_id,ancienne_qnt);
				}
			}
			else
			{
				fprintf(rp,"%s %s %i %i %i\n", produit.nomproduit, produit.fournisseur, produit.prix_unitaire, produit.idproduit,produit.quantite);
				fflush(stdin);
			}

		}
		if(!a)
		{
			printf("\n\nLe produit n'existe pas !");
		}
		//Fermeture des fichiers
		fclose(rp);
		fclose(fp);
		//On remplace l ancien fichier par le nouveau
		remove("Catalogue.dat");
		rename("CatalogueTemp.dat","Catalogue.dat");
		getch();
	}
	menu();
}












// Fonction modifiant les informations du client via l'ID
void modifierclient()
{
    //Declaration variables
	int index, valid;
	client;
	FILE *fp, *rp;
	int a=0;
	int id;
	char edit;
	char ancien_nom[40];
	int ancien_id;
	int ancien_nb;
	long int size=sizeof(a);
	//On verifie s'il y a des clients dans le fichier
	if((fp=fopen("Clients.dat","r+"))==NULL)
	{
		printf("AUCUN CLIENT ");
		menu();
	}
	//S'il y en a, on demande l ID du client a modifier
	else
	{
		rp = fopen("ClientsTemp.dat","w+");
		system("cls");
		printf("Entrez le code du client a modifier :");
		scanf("%i",&id);
		fflush(stdin);
		while(fscanf(fp,"%s %i %i\n", client.nomclient,&client.idclient,&client.numproduitclient)!=EOF)
		{
		    //On affiche les caracteristiques du client si trouvé et on demande les nouvelles
			if(id==client.idclient)
			{

                for(int j=0;j<strlen(client.nomclient);j++){
                    ancien_nom[j] = client.nomclient[j];
                }
                ancien_id = client.idclient;
                ancien_nb = client.numproduitclient;

				a=1;
				printf("\n\t*****  Client trouve *****");
				printf("\nNom du client\t\t: %s",client.nomclient);
				printf("\nID du client\t\t: %i",client.idclient);
				printf("\nNombre d'achats dans l'entreprise\t\t\t: %i",client.numproduitclient);

				printf("\n\n\t*** Nouvel enregistrement ***");
			do
				{

					fflush(stdin);
					printf("\nNouveau nom du client\t\t\t: ");
					gets(client.nomclient);
					client.nomclient[0]=toupper(client.nomclient[0]);
					for (index=0; index<strlen(client.nomclient); ++index)
					{
						if(isalpha(client.nomclient[index]))
							valid = 1;
						else
						{
							valid = 0;
							break;
						}
					}
					if (!valid)
					{
						printf("\n Ce nom contient des caracteres invalides. Entrez les details a nouveau ");
						getch();


					}
				}while(!valid);

				printf("\nNouveau code du client\t\t\t:");
				scanf("%i",&client.idclient);
				printf("\nNouveau nombre d'achats dans l'entreprise\t:");
				scanf("%i",&client.numproduitclient);

				printf(" 'C' pour confirmer les changements ou une autre touche pour annuler ");
				edit=getche();
				if(edit=='c' || edit=='C')
				{
					fprintf(rp,"%s %i %i\n", client.nomclient, client.idclient, client.numproduitclient);
					fflush(stdin);
					printf("\n\n\t\tLes modifications ont ete enregistrees ");
				}
				else{
                    printf("\nModification annulee");
                    fprintf(rp,"%s %i %i\n", ancien_nom, ancien_id, ancien_nb);

				}
			}
			else
			{
				fprintf(rp,"%s %i %i\n", client.nomclient, client.idclient, client.numproduitclient);
				fflush(stdin);
			}

		}
		if(!a)
		{
			printf("\n\nLe client n'existe pas !");
		}
		//Fermeture des fichiers
		fclose(rp);
		fclose(fp);
		//On remplace l ancien fichier par le nouveau
		remove("Clients.dat");
		rename("ClientsTemp.dat","Clients.dat");
		getch();
	}
	menu();
}













// Fonction modifiant les informations du client via le nom
void modifierclientparnom()
{
    //Declaration variables
	int index, valid;
	client;
	//char recherche[40];
	FILE *fp, *rp;
	int a=0;
	char chgt[40];
	char ancien_nom[40];
	int ancien_id;
	int ancien_nb;
	char edit;
	long int size=sizeof(a);
	//On verifie s'il y a des clients dans le fichier
	if((fp=fopen("Clients.dat","r+"))==NULL)
	{
		printf("AUCUN CLIENT ");
		menu();
	}
	//S'il y en a, on demande le nom du client a modifier
	else
	{
		rp = fopen("ClientsTemp.dat","a");
		system("cls");
		printf("Entrez le nom du client a modifier :");
		scanf("%s",&chgt);
		fflush(stdin);
		while(fscanf(fp,"%s %i %i\n", client.nomclient,&client.idclient,&client.numproduitclient)!=EOF)
		{
		    //On affiche les caracteristiques du client si trouvé et on demande les nouvelles
			if(strcmp(chgt, client.nomclient) ==0)
			{
                for(int j=0;j<strlen(client.nomclient);j++){
                    ancien_nom[j] = client.nomclient[j];
                }
                ancien_id = client.idclient;
                ancien_nb = client.numproduitclient;

				a=1;
				printf("\n\t*****  Client trouve *****");
				printf("\nNom du client\t\t: %s",client.nomclient);
				printf("\nID du client\t\t: %i",client.idclient);
				printf("\nNombre d'achats dans l'entreprise\t\t\t: %i",client.numproduitclient);

				printf("\n\n\t*** Nouvel enregistrement ***");
			do
				{

					fflush(stdin);
					//Nouveau nom
					printf("\nNouveau nom du client\t\t\t: ");
					gets(client.nomclient); // get input aring
					client.nomclient[0]=toupper(client.nomclient[0]);
					//pour tous les caracteres
					for (index=0; index<strlen(client.nomclient); ++index)
					{	//vérifie si le caractere est valide ou non
						if(isalpha(client.nomclient[index]))
							valid = 1;
						else
						{
							valid = 0;
							break;
						}
					}
					if (!valid)
					{
						printf("\n Ce nom contient des caracteres invalides. Entrez les details a nouveau ");
						getch();


					}
				}while(!valid);
                //Nouvel ID
				printf("\nNouveau code du client\t\t\t:");
				scanf("%i",&client.idclient);
				printf("\nNouveau nombre d'achats dans l'entreprise\t:");
				scanf("%i",&client.numproduitclient);

				printf(" 'C' pour confirmer les changements ou une autre touche pour annuler ");
				edit=getche();
				if(edit=='c' || edit=='C')
				{
					fprintf(rp,"%s %i %i\n", client.nomclient, client.idclient, client.numproduitclient);
					fflush(stdin);
					printf("\n\n\t\tLes modifications ont ete enregistrees ");
				}
				else{
                    printf("\Modification annulee");
                    fprintf(rp,"%s %i %i\n", ancien_nom, ancien_id, ancien_nb);


				}
			}
			else
			{
				fprintf(rp,"%s %i %i\n", client.nomclient, client.idclient, client.numproduitclient);
				fflush(stdin);
			}

		}
		if(!a)
		{
			printf("\n\nLe client n'existe pas !");
		}
		//Fermeture des fichiers
		fclose(rp);
		fclose(fp);
		//On remplace l ancien fichier par le nouveau
		remove("Clients.dat");
		rename("ClientsTemp.dat","Clients.dat");

		getch();
	}
	menu();
}














// Fonction modifiant les informations du produit via le nom
void modifierparnom()
{
    ////Declaration variables
	int index, valid;
	produit;
	char ancien_nom[40];
	char ancien_fournisseur[40];
	int ancien_prix;
	int ancien_id;
	int ancienne_qnt;
	//char recherche[40];
	FILE *fp, *rp;
	int a=0;
	char chgt[40];
	char edit;
	long int size=sizeof(a);
	//On verifie s'il y a des produits dans le fichier
	if((fp=fopen("Catalogue.dat","r+"))==NULL)
	{
		printf("AUCUN PRODUIT ");
		menu();
	}
	//S'il y en a, on demande le nom du produit a modifier
	else
	{
		rp = fopen("CatalogueTemp.dat","a");
		system("cls");
		printf("Entrez le nom du produit a modifier :");
		scanf("%s",&chgt);
		fflush(stdin);
		while(fscanf(fp,"%s %s %i %i %i\n", produit.nomproduit,produit.fournisseur, &produit.prix_unitaire, &produit.idproduit,&produit.quantite)!=EOF)
		{
		    ////On affiche les caracteristiques du produit si trouvé et on demande les nouvelles
			if(strcmp(chgt, produit.nomproduit) ==0)
			{

                for(int j=0;j<strlen(produit.nomproduit);j++){
                    ancien_nom[j] = produit.nomproduit[j];
                    ancien_fournisseur[j] = produit.fournisseur[j];
                }
                ancien_prix = produit.prix_unitaire;
                ancien_id = produit.idproduit;
                ancienne_qnt = produit.quantite;

				a=1;
				printf("\n\t*****  Produit trouve *****");
				printf("\nNom du produit\t\t: %s",produit.nomproduit);
				printf("\nFournisseur\t\t: %s",produit.fournisseur);
				printf("\nPrix unitaire\t\t\t: %i",produit.prix_unitaire);
				printf("\nID Produit\t\t: %i",produit.idproduit);
				printf("\nQuantite\t:%i",produit.quantite);

				printf("\n\n\t*** Nouvel enregistrement ***");
			do
				{

					fflush(stdin);
					//Nouveau nom
					printf("\nNouveau nom du produit\t\t: ");
					gets(produit.nomproduit);
					produit.nomproduit[0]=toupper(produit.nomproduit[0]);
					//pour tous les caracteres
					for (index=0; index<strlen(produit.nomproduit); ++index)
					{	//vérifie si le caractere est valide ou non
						if(isalpha(produit.nomproduit[index]))
							valid = 1;
						else
						{
							valid = 0;
							break;
						}
					}
					if (!valid)
					{
						printf("\n Ce nom contient des caracteres invalides. Entrez les details a nouveau ");
						getch();


					}
				}while(!valid);

				do
				{
					char fournisseur[40];
					fflush(stdin);
					//Nouveau fournisseur
					printf("\nNouveau fournisseur du produit\t\t:");
					gets(produit.fournisseur); // get input aring
					produit.fournisseur[0]=toupper(produit.fournisseur[0]);
					//pour tous les caracteres
					for (index=0; index<strlen(produit.fournisseur); ++index)
					{	//vérifie si le caractere est valide ou non
						if(isalpha(produit.fournisseur[index]))
							valid = 1;
						else
						{
							valid = 0;
							break;
						}
					}
					if (!valid)
					{
						printf("\n Ce nom contient des caracteres invalides. Entrez les details a nouveau ");
						getch();


					}
				}while(!valid);
                //Nouveau prix,ID, et quantite
				printf("\nNouveau prix :");
				scanf("%i",&produit.prix_unitaire);
				printf("\nNouveau ID du produit\t\t:");
				scanf("%i",&produit.idproduit);
				printf("\nNouvelle quantite\t:");
				scanf("%i",&produit.quantite);

				printf(" 'C' pour confirmer les changements ou une autre touche pour annuler ");
				edit=getche();
				if(edit=='c' || edit=='C')
				{
					fprintf(rp,"%s %s %i %i %i\n", produit.nomproduit, produit.fournisseur, produit.prix_unitaire, produit.idproduit,produit.quantite);
					fflush(stdin);
					printf("\n\n\t\tLes modifications ont ete enregistrees\n ");
					// Seuil d'alerte
                    if(produit.quantite<200)
                        printf("ALERTE! : LE PRODUIT DOIT ETRE REAPPROVISIONNE, La quantite en stock est descendue sous la barre des 200 kg");
				}
				else{
                    printf("\Modification annulee");
                    fprintf(rp,"%s %s %i %i %i\n", ancien_nom, ancien_fournisseur, ancien_prix, ancien_id,ancienne_qnt);

				}
			}
			else
			{
				fprintf(rp,"%s %s %i %i %i\n", produit.nomproduit, produit.fournisseur, produit.prix_unitaire, produit.idproduit,produit.quantite);
				fflush(stdin);
			}

		}
		if(!a)
		{
			printf("\n\nLe produit n'existe pas !");
		}
		//Fermeture des fichiers
		fclose(rp);
		fclose(fp);
		//On remplace l'ancien fichier par le nouveau
		remove("Catalogue.dat");
		rename("CatalogueTemp.dat","Catalogue.dat");
		getch();
	}
	menu();
}

