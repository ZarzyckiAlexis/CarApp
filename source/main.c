/*
Auteur : Noah Verly
But :   Menu de l'application de gestion des utilsateurs,
        vous pouvez choisir entre ajouter, modifier et supprimer
        des utilsateurs
*/

// INCLUDE
#include "../includes\users.c"
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
    if (choix==1)
    {
        //On regarde si le fichier est vide pour savoir s'il est le premier pour le mettre admin
        FILE * fichier=fopen("users.txt","r" );
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
        printf("Magazine\n");
        printf("========");
        //Do while du menu de selection
        do
        {
            printf("\n\nQue voulez-vous faire ?\n\n");
            printf("\t-Lister les différente voiture  (1)");
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
        //Choix commun
            switch (choix_uti)
            {
            // Lister les voitures
            case 1:

                break;
            // Rechercher une voiture
            case 2:
            
                break;
            }
        //Choix unique pour l'administrateur
        if (rank==ADMIN)
        {
            switch (choix_uti)
            {
            //Ajouter une nouvelle version
            case 3:

                break;
            // Lister les utilisateur
            case 4:
                lister_uti();
                break;
            // Ajouter un utilisateur
            case 5:
                menu_ajouter("=Log");
                break;
            // Supprimer un utilisateur 
            case 6: 
                menu_supprimer();
                break;
            // Modifier un utilisateur 
            case 7:
                menu_modifier();
                break;
            }
        }
    
        } while (!(rank==SIMPLE && choix_uti==3) && !(rank==ADMIN && choix_uti==8));
    }
    } while (choix !=3);
    printf("Merci d'avoir utilise(e) l'application !");
    // Stop pendant 5 secondes
    Sleep(500);
    exit(EXIT_SUCCESS);
}
