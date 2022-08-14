#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mysql.h>
#include <stdbool.h>
#define DB_NAME "projet" // Le nom de la base de données

int erreurFichier(FILE *monFichier, int showText);
// Fonction qui permet la connexion à la base de données
void initConnexion();
// Fonction qui permet la déconnexion à la base de données
void closeConnexion();
// Fonction qui permet de vérifier si une table existe
// [ 1 = EXISTE ; 0 = N'EXISTE PAS ]
int *TableExist(char *query);
// Fonction qui permet d'éxécuté une requête SQL et qui renvois  le résultat
MYSQL_RES *SqlSelect(char *query);
// Fonction qui permet d'éxécuté une requête SQL et ne renvois pas le résultat
void executerCommandeSQL(char *instructionSQL);
// Fonction qui permet de supprimer toutes les tables de la BDD
void destroyAllTable();
// Fonction qui permet de voir si une données est présent dans la table
int *isDataPresent(char *query);
// Fonction qui permet de généré toutes les tables
void createAllTable();

