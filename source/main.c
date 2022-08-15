/*
Auteur : Noah Verly
But :   Menu de l'application de gestion des utilsateurs,
        vous pouvez choisir entre ajouter, modifier et supprimer
        des utilsateurs
*/

// INCLUDE
#include "../includes\users.c"
#include "../includes\versions.c"
#include "../includes\moteurs.c"
#include "../includes\versionsMoteurs.c"
// MAIN
int main(void)
{
// DECLARATIONS DES VARIABLES
    unsigned short choix,choix_uti,rank;
    long lfile;
    // TRAITEMENT
    setlocale(LC_ALL, "ISO 8859-1");
    //PARTIE : Choix entre s'enregristrer ou se connecter
    printf("Bienvenue\n");
    printf("=========");
    do
    {

        printf("\n\nQue voulez-vous faire ?\n\n");
        printf("\t- Vous enregistrez \t(1)\n");
        printf("\t- Vous connectez \t(2)\n");
        printf("\t- Quitter le programme \t(3)");

    do{
        printf("\n\nQuel est votre choix : \t"); fflush(stdin); scanf("%u", &choix);
    } while (choix!=1 && choix!=2 && choix!=3);
    //PARTIE : Pour s'inscrire
    system("cls");
    if (choix==1)
    {
        //On regarde si le fichier est vide pour savoir s'il est le premier pour le mettre admin
        FILE * fichier=fopen("users.txt","r" );
        if (erreurDeFichier(fichier))
        {
            return 0;
        }
        fseek(fichier,0,SEEK_END);  
        long lfile=ftell(fichier);   //longueur du fichier 
        fclose(fichier); 
        if(lfile==LIBRE_VIDE){
            menu_ajouter("=LogAdmin");
        }else{
            menu_ajouter("=Log");
        }
    } 
    //PARTIE : Pour se connecter et utiliser l'application
    else if (choix==2)
    {
        rank = menu_connexion();
        if(existTableVersions() == 0){
            createTableVersions();
        }
        int *resultat = TableExist("SELECT 1 FROM moteurs LIMIT 1");
        if(*resultat == 0){
            creationTableMoteurs();
       }
        resultat = TableExist("SELECT 1 FROM versions_moteurs LIMIT 1");
        if (*resultat == 0){
            creationTableVersionsMoteurs();
       }
        printf("Magazine\n");
        printf("========");
        //Do while du menu de selection
        do
        {
            system("cls");
            printf("\n\nQue voulez-vous faire ?\n\n");
            printf("\t-Lister les différente voiture et moteurs (1)");
            printf("\t-Chercher un moteur \t\t(2)\n");
        //Menu de l'administrateur
        if (rank==2)
        {
            printf("\t-Ajouter une nouvelle version \t(3)");
            printf("\t-Lister les utilisateur \t(4)\n");
            printf("\t-Ajouter une utilisateur \t(5)");
            printf("\t-Supprimer un utilisateur \t(6)\n");
            printf("\t-Modifier un utilisateur \t(7)");
            printf("\t-Quitter le programme \t\t(8)\n");
            printf("\n\t-Information importante :");
            printf("\n\t   Pour le choix 5 et 7, si vous voulez annuler un processus, tapez 0");
        }else{//Menu unique pour le simple utilisateur
            printf("\t-Quitter le programme \t(3)");
            
        }
        //Do while de sélection de choix
        do{
            printf("\n\nQuel est votre choix : \t"); fflush(stdin); scanf("%u", &choix_uti);
        } while (choix_uti!= 1 && choix_uti!= 2 && choix_uti!= 3 && choix_uti!= 4 && choix_uti!= 5 && choix_uti!= 6 && choix_uti!=7 && choix_uti!=8);
        char versions[100][100];
        int *count = (int *)malloc(sizeof(int));
        int idMoteur = 0, nbVersions = 0;
        int nbMoteur = 0;
        nbMoteur = combienDeMoteurs();
        char tableauDesMoteurs[nbMoteur*5][21];
        char modele[100];
        char version[100];
        char idmotor[100];
        //Choix commun
            switch (choix_uti)
            {
            // Lister les voitures
            case 1:
            getVersions(versions, count);
            system("cls");
            printf("======= Moteurs =======\n\n");
            recuperationDesInfosMoteurs(tableauDesMoteurs);
            for(int i=0; i<nbMoteur; i++){
            printf("IdMoteur : %s Cylindree: %s nombreCylindres: %s Puissance: %s Carburant: %s \n", tableauDesMoteurs[i*5], tableauDesMoteurs[i*5+1], tableauDesMoteurs[i*5+2], tableauDesMoteurs[i*5+3], tableauDesMoteurs[i*5+4]);
            }
            printf("\n");
            printf("======= Versions =======\n\n");
            for(int i=0; i<*count/3; i++){
            printf("Versions : %s Modele: %s Marque: %s \n", versions[i*3], versions[i*3+1], versions[i*3+2]);
            }
            printf("\n");
            printf("Appuyez sur une touche de votre clavier pour continuer\n");
            getch();
            break;
            // Rechercher une voiture
            case 2:
                system("cls");
                printf("Entre l'id du moteur : ");
                scanf("%d", &idMoteur);
                
                MYSQL_RES *res = NULL;
                // Récupération des ids des différentes versions en DB
                // Si après le passage nbVersions = -1 alors le moteur n'existe pas
                // Si après le passage nbVersions = 0 alors le moteur n'a pas de modèle
                res = recuperationDesVersions(idMoteur, &nbVersions);
                // Si il y a 0 version cela veut dire que se moteur ne contient pas de version
                if (nbVersions > 1)
                { // Tableau contenant tout les ids des versions contenant le moteur choisi
                    int tableauIdVersions[nbVersions];
                    // Tableau qui contiendra les infos récupérer pour chaque version
                    char tableauInfosVersions[nbVersions * 4][51];
                    // Utilisation des résultats pour récupérer les ids dans un tableau
                    recuperationDuResultat(tableauIdVersions, res);
                    // Récupération des infos de chaque version contenant le moteur choisi
                    recuperationDesInfosVersions(tableauInfosVersions, tableauIdVersions, nbVersions);
                    int cpt = 0;
                    for(int i=0; i<nbVersions; i++){
                        printf("\nNom version: %s Modele: %s Marque: %s ID: %s\n", tableauInfosVersions[cpt*4],tableauInfosVersions[cpt*4+1], tableauInfosVersions[cpt*4+2], tableauInfosVersions[cpt*4+3]);
                        cpt++;
                    }
                }
                switch(nbVersions){
                    case 0:
                        printf("Aucune version pour ce moteur\n");
                        break;
                    case -1:
                        printf("Aucun moteur ne possede cette identifiant\n");
                        break;
                }
                printf("Appuyez sur une touche de votre clavier pour continuer\n");
                getch();
            }
        //Choix unique pour l'administrateur
        if (rank==ADMIN)
        {
            switch (choix_uti)
            {
            //Ajouter une nouvelle version
            case 3:
                system("cls");
                printf("Veuillez entrer le nom de la version : ");
                scanf("%s", version);
                fflush(stdin);
                printf("Veuillez entrer le modele : ");
                scanf("%s", modele);
                fflush(stdin);
                printf("Veuillez entrer l'id moteur: ");
                scanf("%s", idmotor);
                char *errors = (char *)malloc(1000); // on réserve un emplacement mémoire pour la gestion des erreurs
                strcpy(errors, "\n"); // On initialise le contenu de la liste d'erreurs
                addVersions(version, modele, idmotor, errors);
                printf("%s", errors);
                printf("Appuyez sur une touche de votre clavier pour continuer\n");
                getch();
                break;
            // Lister les utilisateur
            case 4:
                system("cls");
                lister_uti();
                break;
            // Ajouter un utilisateur
            case 5:
                system("cls");
                menu_ajouter("=Log");
                break;
            // Supprimer un utilisateur 
            case 6: 
                system("cls");
                menu_supprimer();
                break;
            // Modifier un utilisateur 
            case 7:
                system("cls");
                menu_modifier();
                break;
            }
        }
    
        } while (!(rank==SIMPLE && choix_uti==3) && !(rank==ADMIN && choix_uti==8));
    }
    } while (choix !=3);
    system("cls");
    printf("Merci d'avoir utilise(e) l'application !");
    // Stop pendant 5 secondes
    Sleep(500);
    exit(EXIT_SUCCESS);
}
