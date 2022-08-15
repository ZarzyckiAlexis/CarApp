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
        // Création de la rêquete
        sprintf(requeteSQL, "CREATE TABLE moteurs(idMoteur INT, cylindree INT, nombreCylindres INT, puissance INT, typeCarburant VARCHAR(20), PRIMARY KEY(idMoteur) );");

        // Exécution de la rêquete
        executerCommandeSQL(requeteSQL);
        executerCommandeSQL("INSERT INTO `moteurs` (`idMoteur`, `cylindree`, `nombreCylindres`, `puissance`, `typeCarburant`) VALUES ('0', '300', '250', '100', 'Diesel');");
        executerCommandeSQL("INSERT INTO `moteurs` (`idMoteur`, `cylindree`, `nombreCylindres`, `puissance`, `typeCarburant`) VALUES ('1', '250', '120', '250', 'Essence');");

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

// Exemple d'utilisation dans le .h
// Retourne le nombre de moteur dans la db
int combienDeMoteurs()
{

    MYSQL_RES *res = NULL;
    int nbMoteurs = 0;

    res = SqlSelect("SELECT cylindree FROM moteurs");

    nbMoteurs = res->row_count;

    return nbMoteurs;
}

// Récupération des informations de tout les moteurs
void recuperationDesInfosMoteurs(char tableauDesMoteurs[][21])
{

    MYSQL_RES *res = NULL;
    MYSQL_ROW ligne = NULL;
    int k = 0;

    res = SqlSelect("SELECT idMoteur, cylindree, nombreCylindres, puissance, typeCarburant FROM moteurs ORDER BY idMoteur");

    // Parcours des lignes pour récupérer les infos moteurs
    while ((ligne = mysql_fetch_row(res)))
    {

        for (int i = 0; i != 5; i++, k++)
        {

            strcpy(&tableauDesMoteurs[k][0], ligne[i]);
        }
    }
}
