#include "global.h"


// Création de la table pour les moteurs
int creationTableMoteurs (void);
// En utilisant le tableau contenant les id des versions qui possède le moteur demander on va rechercher les infos qu'il nous faut
void recuperationDesInfosVersions(char tableauInfosVersions[][51], int tableauIdVersions[], int nbVersions);
// Fonction pour récupérer les versions d'un moteur demander
void creationListePourMoteurs(int idMoteur, int *nbVersions);
//Récupération id des versions contenant le moteur demander en les stockants dans un tableau d'integer
// La variable res est garnie dans la fonction recuperationDesVersions
void recuperationDuResultat(int tableauIdVersions[], MYSQL_RES *res);
// Récupération des versions équipées de ce moteurs
MYSQL_RES *recuperationDesVersions(int idMoteur, int *nbVersions);






/* EXEMPLE NOTER POUR L UTILISATION DANS LE MAIN
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
        break;
    }
}
*/