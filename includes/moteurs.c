#include "moteurs.h"

int creationTableMoteurs(void)
{

    // Déclaration des variables
    char *requeteSQL = malloc(250);

    int *resultat = malloc(sizeof(int));

    // Vérification que la table n'existe pas
    resultat = TableExist("SELECT 1 FROM moteurs LIMIT 1");

    if (*resultat != 1)

    {
        initConnexion();

        // Création de la rêquete
        sprintf(requeteSQL, "CREATE TABLE moteurs(idMoteur INT, cylindree INT, nombreCylindres INT, puissance INT, typeCarburant VARCHAR(20), PRIMARY KEY(idMoteur) );");

        // Exécution de la rêquete
        executerCommandeSQL(requeteSQL);

        // Déconnexion de la DB
        closeConnexion();

        free(requeteSQL);
        free(resultat);
        return 1; // La table est créer
    }
    else
        // Si resultat n'est pas = à 1 c'est que la table existe déjà
        printf("La table moteurs est déjà existante. Si vous voulez la régénerer supprimer la au préalable");

    free(requeteSQL);
    free(resultat);
    return 0; // La table n'est pas créer
}

// Récupération des versions équipées de ce moteurs
MYSQL_RES *recuperationDesVersions(int idMoteur, int *nbVersions)
{

    // Déclarations des variables
    MYSQL_RES *res = NULL;
    char *requeteSQL = malloc(250);

    // Vérification que le moteur existe avant de faire d'autre procédure
    //  Création de la requeteSQL en y insérant l'id du moteur entrez par l'utilisateur

    sprintf(requeteSQL, "SELECT idMoteur FROM moteurs WHERE idMoteur = %d", idMoteur);

    // Exécution de la requete créer
    res = SqlSelect(requeteSQL);

    if (res->row_count == 0)
    {
        *nbVersions = -1;
    }
    else
    {
        mysql_free_result(res);
        // Création de la requeteSQL en y insérant l'id du moteur entrez par l'utilisateur
        sprintf(requeteSQL, "SELECT idVersion FROM versions_moteurs WHERE idMoteur = %d", idMoteur);

        // Exécution de la requete créer
        res = SqlSelect(requeteSQL);

        // Récupération du nombre de version trouver le row
        *nbVersions = res->row_count;
    }

    free(requeteSQL);
    return res;
}

// Récupération id des versions contenant le moteur demander en les stockants dans un tableau d'integer
//  La variable res est garnie dans la fonction recuperationDesVersions
void recuperationDuResultat(int tableauIdVersions[], MYSQL_RES *res)
{

    MYSQL_ROW ligne = NULL;
    int i = 0;

    // Insertion du résultat dans un tableau
    while ((ligne = mysql_fetch_row(res)))
    {
        tableauIdVersions[i] = atoi(*ligne);
        i++;
    }

    // Free du pointeur de résultat
    mysql_free_result(res);
}

// En utilisant le tableau contenant les id des versions qui possède le moteur demander on va rechercher les infos qu'il nous faut
void recuperationDesInfosVersions(char tableauInfosVersions[][51], int tableauIdVersions[], int nbVersions)
{
    MYSQL_RES *res = NULL;
    MYSQL_ROW ligne = NULL;
    char *requeteSQL = malloc(250);
    int k = 0;
    for (int i = 0; i != nbVersions; i++)
    {

        sprintf(requeteSQL, "SELECT nomVersion, nomModele, nomMarque, idVersion FROM versions WHERE idVersion =%d", tableauIdVersions[i]);
        res = SqlSelect(requeteSQL);
        ligne = mysql_fetch_row(res);

        for (int j = 0; j != 4; j++, k++)
        {

            strcpy(&tableauInfosVersions[k][0], ligne[j]);
        }
    }
}

int main(void)
{
    int idMoteur = 0, nbVersions = 0;
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
    }

    switch (nbVersions)
    {
    case 0:
        printf("Aucune version pour ce moteur");
        break;
    case -1:
        printf("Aucun moteur ne possède cette identifiant");
        break;
    default:
        printf("Des versions ont été trouvés");
        printf("%d",nbVersions);
        break;
    }
}