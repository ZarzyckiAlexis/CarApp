#include "moteurs.h"

void creationTableMoteurs (void){

// Déclaration des variables
char *requeteSQL = malloc(250);

//Connexion à la DB
initConnexion();

//Création de la rêquete
sprintf(requeteSQL,"CREATE TABLE moteurs(idMoteur INT, cylindree INT, nombreCylindres INT, puissance INT, typeCarburant VARCHAR(20), PRIMARY KEY(idMoteur) );");

//Exécution de la rêquete
executerCommandeSQL(requeteSQL);

//Déconnexion de la DB
closeConnexion();


}