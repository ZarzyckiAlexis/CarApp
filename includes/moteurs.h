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
//Fonction appeller dans le main qui fait le travail complete de recherche en utilisant les fonction si dessus
// Selon la valeur de nbVersions après l'appelle de celle ci on pourra determiner si le moteur existe si il possède des versions VOIR EXEMPLE SI DESSOUS
void creationListePourMoteurs(int idMoteur, int *nbVersions);







/* EXEMPLE NOTER
int main(void)
{
    int idMoteur = 0, nbVersions = 0;
    printf("Entre l'id du moteur : ");
    scanf("%d", &idMoteur);
    creationListePourMoteurs(idMoteur, &nbVersions);


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