/*
Auteur : Noah Verly
But :   Fichier avec le code des fonctions
*/
#include "users.h"


/*FONCTION LISTER LES UTILISATEUR ET LEUR GRADE*/
void lister_uti()
{
    // DECLARATION DES VARIABLES
    FILE *fichier;
    char buff[DIM];
    // TRAITEMENT
    fichier = fopen(NAME_FICHIER, "r"); // Ouverture du fichier
    rewind(fichier);
    printf("\t\tListe des utilisateurs :\n");
    printf("\t\t=======================\n\n");

    while (fscanf(fichier, "%s", buff) != EOF) // On boucle jusque la fin du fichier pour recuperer le nom
    {
        // On affiche le pseudo et status
        printf("%s\n", buff);
        // On passe le mdp en le fscanf
        fscanf(fichier, "%s", buff);
    }
    if (fclose(fichier)==0)
        {
            printf("\nAppuyer sur une touche pour continuer !");
            getch();
        }
}

/*FONCTION D'AJOUT*/
void menu_ajouter(char *rang)
{
    // DECLARATION DES VARIABLES
    FILE *fichier;
    char log[DIM]; // 55 car on doit garder un caratere en plus pour le caratere de fin et le =log
    char mdp[DIM]; // 55 car on doit garder un caratere en plus pour le caratere de fin et le =mdp
    int returned;
    // TRAITEMENT

    printf("\t\tAJOUTER UN UTILISATEUR\n");
    printf("\t=====================================");
    fichier = fopen(NAME_FICHIER, "a+"); // Ouverture du fichier
    rewind(fichier);

    // Pour le log
    printf("\nQuel est le nom de l'utilisateur :\t");
    fflush(stdin);
    scanf("%s", &log);
    // Pour le mot de passe
    printf("\nQuel est le mot de passe :\t\t");
    fflush(stdin);
    scanf("%s", &mdp);
    // Fonction d'ajout
    if (ajouter(fichier, log, mdp, DIM, rang) == 0)
    {
        printf("\nL'utilisateur n'a pas ete ajoute(e)");
    } else{
        printf("\nL'utilisateur a ete ajoute(e)\n");
        if (fclose(fichier) == 0)
        {
            printf("\n\nAppuyer sur une touche pour continuer !");
            getch();
        }
    }
    // On ferme le fichier
}

/*FONCTION D'AJOUT*/
unsigned ajouter(FILE *fichier, char *log, char *mdp, int dim, char *rang)
{
    // DECLARATIONS DES VARIABLES
    char log_insert[dim];
    char mdp_insert[dim];
    char rang_insert[dim];
    char verif[1] = {"0"};
    unsigned short returned;
    // TRAITEMENT
    strcpy(log_insert, log);
    strcpy(mdp_insert, mdp);
    // On verifie le log et mdp s'il est dispo et ok
    if (strcmp(verif, log_insert) == 0 || strcmp(verif, mdp_insert) == 0)
    {
        printf("Vous avez annule(e) le processus");
        if(fclose(fichier)==0){
                return 0;
            }
    }
    returned = check_existe(log, DIM, fichier);
    if (returned >= SIMPLE) //On regarde si le pseudo est utilisé par un simple (1) ou un admin (2)
    {
        printf("Ce nom d'utilisateur est PAS disponible !");
        if(fclose(fichier)==0){
                return 0;
            }
    }
    if (strlen(log) > 50)
    {
        printf("Votre nom d'uitlisateur doit faire 50 caracteres ou moins");
        if(fclose(fichier)==0){
                return 0;
            }
    }
    if (strlen(mdp) > 50)
    {
        printf("Votre mot de passe doit faire 50 caracteres ou moins");
        if(fclose(fichier)==0){
                return 0;
            }
    }
    else
    {
        //On copie les log et mdp dans des varaibles 
        strcpy(rang_insert, rang);
        strcpy(log_insert, log);
        //On concatenne le log et le rang 
        strcat(log_insert, rang_insert);
        strcpy(mdp_insert, mdp);
        // On ajoute dans le .txt
        fprintf(fichier, "%s\n", &log_insert);
        // Appel de la fonction de chiffrement
        chiffrement(log_insert, mdp_insert, DIM);
        // On ajoute dans le .txt
        strcat(mdp_insert, "=MDP");
        fprintf(fichier, "%s\n", &mdp_insert);
        return 1;
    }
}
/*FONCTION DE CHECK DE DOUBLON*/
unsigned check_existe(char *log, int dim, FILE *fichier)
{
    // DECLARATION DES VARIABLES
    char buff[dim];
    char log_uti[dim];
    char log_admin[dim];
    // TRAITEMENT
    rewind(fichier); // Revenir en haut du fichier
    strcpy(log_uti, log);
    strcpy(log_admin, log);
    strcat(log_uti, "=Log");        // Permet de concatenner deux chaines de caracteres
    strcat(log_admin, "=LogAdmin"); // Permet de concatenner deux chaines de caracteres

    while (fscanf(fichier, "%s", buff) != EOF) // On boucle jusque la fin du fichier
    {
        if (strcmp(buff, log_uti) == 0)
        {             // Non disponible
            return SIMPLE; // On return 1 pour pas rester dans la boucle donc eviter l'erreur et perdre du temps
        }
        if (strcmp(buff, log_admin) == 0)
        {             // Non disponible
            return ADMIN; // On return 2 pour pas rester dans la boucle donc eviter l'erreur et perdre du temps
        }
    }
    // Disponible
    //  printf("Ce nom d'utilisateur est disponible !");
    return LIBRE_VIDE; // On return 0 pour dire qu'il est dispo
}

/*FONCTION DE CHIFFREMENT*/
void chiffrement(char *log, char *mdp, int dim)
{
    // DECLARATION DES VARIABLES
    unsigned short cpt, longmdp = strlen(mdp), longlog = strlen(log);
    // TRAITEMENT
    for (cpt = 0; cpt < longmdp; cpt++)
    {
        mdp[cpt] = ~mdp[cpt];     // On inverse le bit
        mdp[cpt] = mdp[cpt] << 3; // On deplace trois vers la droite
        
    }
}
/*FONCTION DE SUPRESSION*/
unsigned menu_supprimer()
{
    // DECLARATION DES VARIABLES
    FILE *fichier;
    char rep;
    char log[DIM]; // 55 car on doit garder un caractere en plus pour le caractere de fin et le =log
    char mdp[DIM]; // 55 car on doit garder un caractere en plus pour le caractere de fin et le =mdp
    int returned = 0;

    // TRAITEMENT

    printf("\t\tSUPPRIMER UN UTILISATEUR\n");
    printf("\t=====================================");

    // Verifie si le log existe
    printf("\n\nQuel est le nom de l'utilisateur a supprimer :\t");
    fflush(stdin);
    scanf("%s", &log);
    // Demande a l'utilsateur s'il est sur de supprimer
    do
    {
        printf("Voulez-vous supprimer l'utilisateur\t(Y=yes\tor\tN=no) :\t");
        fflush(stdin);
        scanf("%c", &rep);
        fichier = fopen(NAME_FICHIER, "r"); // Ouverture du fichier
        rewind(fichier);
        returned=check_existe(log,DIM, fichier);
        //Si la reponse est Y et que l'utilisateur est un simple on supprime
        if ((toupper(rep)) == 'Y' && (returned==LIBRE_VIDE || returned ==SIMPLE))
        {
            if (!supprimer(fichier, log, DIM))
            {
                printf("\nL'utilisateur n'a pas pu etre supprimer !");
            }else{
                printf("\nL'utilisateur a ete supprime(e) !");
            }
            printf("\nAppuyer sur une touche pour continuer !");
            getch();
        }//Sinon on fait rien
        else if ((toupper(rep)) == 'N')
        {
            printf("\nVous avez decider de ne pas supprimer l'utilisateur !");
            printf("\nAppuyer sur une touche pour continuer !");
            getch();
            if(fclose(fichier)==0){
                return 0;
            }
        }
        else //Sinon c'est que c'est un admin et on ne peut pas le supprimer
        {
            printf("Vous ne pouvez pas supprimer un administateur !");
            if(fclose(fichier)==0){
                return 0;
            }
        }
    } while (toupper(rep) != 'Y' && toupper(rep) != 'N');
}

unsigned supprimer(FILE *fichier, char *log, int dim)
{
    // DECLARATION DES VARIABLES
    char buff[dim];
    FILE *newfichier;
    char log_uti[dim];
    char log_admin[dim];
    char verif[1] = {"0"};
    unsigned short returned;
    // TRAITEMENT
    strcpy(log_uti, log);
    strcpy(log_admin, log);
    //On verifie que l'utilisateur ne veut pas annuler
    if (strcmp(verif, log_uti) == 0)
    {
        printf("Vous avez annule(e) le processus");
        if(fclose(fichier)==0){
            return 0;
        }
    }
    //On regarde si l'utilisateur existe
    returned = check_existe(log, DIM, fichier);
    if (returned == LIBRE_VIDE)
    {
        printf("\nCe nom d'utilisateur N'existe PAS.\n\n");
        if(fclose(fichier)==0){
            return 0;
        }
    }
    //On regarde si le log fait moins de 51 caracteres
    if (strlen(log) > 50)
    {
        printf("\nVotre nom d'utilisateur doit faire 50 caracteres ou moins");
        if(fclose(fichier)==0){
            return 0;
        }
    }
    else
    {
        strcat(log_uti, "=Log");        // Permet de concat?nner deux cha?nes de caract?res
        strcat(log_admin, "=LogAdmin"); // Permet de concat?nner deux cha?nes de caract?res
        //On va cree un nouveau fichier
        newfichier = fopen("users2.txt", "w");
        //on remonte en haut des deux fichier au cas ou
        rewind(fichier);
        rewind(newfichier);
        // Boucle pour faire tout le fichier
        while (fscanf(fichier, "%s", buff) != EOF) 
        {
            //On compare le buff qui contient la ligne actuel avec le log dans ses deux versions si oui on fscanf pour eviter le log
            if (strcmp(buff, log_uti) == 0 || strcmp(buff, log_admin) == 0)
            {
                fscanf(fichier, "%s", buff);
            }
            else
            {
                fprintf(newfichier, "%s\n", buff);
            }
        }
        // Fermeture des fichier pour les modifier
        if (fclose(fichier) == 0 && fclose(newfichier) == 0)
        {
            if (remove(NAME_FICHIER)==0)
            {
                if (rename("users2.txt", NAME_FICHIER)==0)
                {
                    return 1;
                }
            }
        }
    }
}
/*FONCTION DE MODIFICATION*/
unsigned menu_modifier()
{
    // DECLARATION DES VARIABLES
    FILE *fichier;
    char log_actu[DIM]; // 61 car on doit garder un caractere en plus pour le caractere de fin et le =Log ou =LogAdmin
    char log[DIM];      // 61 car on doit garder un caractere en plus pour le caractere de fin et le =Log ou =LogAdmin
    char mdp[DIM];      // 61 car on doit garder un caractere en plus pour le caractere de fin et le =MPD
    char verif[1] = {"0"};
    int returned;
    // TRAITEMENT
    printf("\t\tMODIFIER UN UTILISATEUR\n");
    printf("\t\t======================");
    // On demande le nom de l'utilisateur
    printf("\n\nQuel est le nom de l'utilisateur a modifier :\t");
    fflush(stdin);
    scanf("%s", &log_actu);
    if (strcmp(verif, log_actu) == 0)
    {
        printf("Vous avez annule(e) le processus");
        return 0;
    }
    if (strlen(log_actu) > 50)
    {
        printf("\nVotre nom d'utilisateur doit faire 50 caracteres ou moins");
        return 0;
    }
    fichier = fopen(NAME_FICHIER, "a+"); // Ouverture du fichier
    rewind(fichier);
    returned = check_existe(log_actu, DIM, fichier);
    if (returned == LIBRE_VIDE)
    {
        printf("\nCe nom d'utilisateur N'existe PAS.\n\n");
        fclose(fichier);
        if (fclose(fichier)==0)
        {
            return 0;
        }
    }
    // Si on voit qu'il est admin on lui demande de "se connecter" pour voir si c'est bien lui
    // Choix du nouveau nom d'utilsateur
    printf("\nQuel est le nouveau nom d'utilisateur :\t");
    fflush(stdin);
    scanf("%s", &log);
    // Choix du nouveau mdp
    printf("\nQuel est le nouveau mot de passe :\t");
    fflush(stdin);
    scanf("%s", &mdp);
    // Appel de la fonction de modification
    if (modifier(fichier, log_actu, log, mdp, DIM) == 0)
    {
        printf("\nAucune information n'a ete modifier");
    }
}
/*FONCTION POUR MODOFIER*/
unsigned modifier(FILE *fichier, char *log_actu, char *log, char *mdp, int dim)
{
    // DECLARATIONS DES VARIABLES
    char log_change[dim];
    char mdp_change[dim];
    char cpy_log_actu[dim];
    char verif[1] = {"0"};
    unsigned short returned;
    // TRAITEMENT
    strcpy(cpy_log_actu, log_actu);
    strcpy(log_change, log);
    strcpy(mdp_change, mdp);
    // On regarde si le compte de l'utilisateur est ok
    if (strcmp(verif, log_change) == 0 || strcmp(verif, mdp_change) == 0)
    {
        printf("Vous avez annule(e) de le processus !");
        if (fclose(fichier)==0)
        {
            return 0;
        }
    }
    returned = check_existe(log_change, DIM, fichier);
    if (returned >= SIMPLE)
    {
        printf("Ce nom d'utilisateur N'est PAS disponible.");
        if (fclose(fichier)==0)
        {
            return 0;
        }
    }
    if (strlen(log_change) > 50)
    {
        printf("Votre nom d'utilisateur doit faire 50 caracteres ou moins");
        if (fclose(fichier)==0)
        {
            return 0;
        }
    }
    if (strlen(mdp_change) > 50)
    {
        printf("Votre mot de passe doit faire 50 caracteres ou moins");
        if (fclose(fichier)==0)
        {
            return 0;
        }
    }
    returned = check_existe(cpy_log_actu, dim, fichier);
    if (returned == ADMIN)
    {
        supprimer(fichier, cpy_log_actu, dim);
        fichier = fopen(NAME_FICHIER, "a+"); // Ouverture du fichier
        rewind(fichier);
        ajouter(fichier, log_change, mdp_change, dim, "=LogAdmin");
        if (fclose(fichier) == 0)
        {
            printf("Vos informations ont ete changees\n");
            return 1;
        }
    }
    else if (returned == SIMPLE)
    {
        supprimer(fichier, cpy_log_actu, dim);
        fichier = fopen(NAME_FICHIER, "a+"); // Ouverture du fichier
        rewind(fichier);
        ajouter(fichier, log_change, mdp_change, dim, "=Log");
        if (fclose(fichier) == 0)
        {
            printf("Les informations ont ete changees");
            return 1;
        }
    }
}
/*FONCTION DE CONNEXION*/
unsigned menu_connexion()
{
    // DECLARATION DES VARIABLES
    char log[DIM];
    char mdp[DIM];
    int cpt = 0;
    int rank;
    // TRAITEMENT
    setlocale(LC_ALL, "ISO 8859-1");
    do
    {
        printf("\t\tConnectez-vous :\n");
        printf("\t\t================\n\n");
        //On rentre le log
        printf("Quel est votre nom d'utilisateur : ");
        fflush(stdin);
        scanf("%s", &log);
        //on rentre le mdp
        printf("\nQuel est votre mot de passe : ");
        fflush(stdin);
        scanf("%s", &mdp);
        //On appelle la fonction d'identification qui va renvoyer s'il est admin ou pas
        rank = identification(log, mdp, DIM);
        if (rank == LIBRE_VIDE)
        {
            printf("\nLe nom d'utilisateur et/ou le mot de passe est incorrect\n\n");
        }
    } while (!rank);
    printf("\nVous etes connecte(e) !\n\n");
    printf("Appuyer sur une touche pour continuer");
    getch();
    return rank;
}
/*FONCTION D'IDENTIFICATION*/
unsigned identification(char *log, char *mdp, int dim)
{
    // DECLARATION DES VARIABLES
    FILE *fichier;
    char buff[dim];
    // TRAITEMENT
    fichier = fopen(NAME_FICHIER, "a+"); // Ouverture du fichier
    rewind(fichier);
    // On regarde si le log existe et s'il est admin ou simple
    if (check_existe(log, dim, fichier) == SIMPLE)
    {
        // On recupere le mdp de l'utilisateur
        fscanf(fichier, "%s", buff);
        strcat(log, "=Log");
        // On chiffre le mpd
        chiffrement(log, mdp, dim);
        // On concatene le mdp chiffrer avec le =MDP
        strcat(mdp, "=MDP");
        if (strcmp(buff, mdp) != 0)
        {
            return 0;
        }
        if (fclose(fichier) == 0)
        {
            return 1;
        }
    }
    else if (check_existe(log, dim, fichier) == ADMIN)
    {
        // On recupere le mdp de l'utilisateur
        fscanf(fichier, "%s", buff);
        strcat(log, "=LogAdmin");
        // On chiffre le mpd
        chiffrement(log, mdp, dim);
        // On concatene le mdp chiffrer avec le =MDP
        strcat(mdp, "=MDP");
        if (strcmp(buff, mdp) != 0)
        {
            return 0;
        }
        if (fclose(fichier) == 0)
        {
            return 2;
        }
    }
    else
        return 0;
}
