#include "moteurs.h"

int creationTableMoteurs(void)
{

    // Déclaration des variables
    char *requeteSQL = malloc(250);

    int *resultat = malloc(sizeof(int));

    
    //Vérification que la table n'existe pas 
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