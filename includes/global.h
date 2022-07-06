#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mysql.h>
#define DB_NAME "projet" // Le nom de la base de données

int erreurFichier(FILE *monFichier);
void initConnexion(MYSQL *sqlConnexion);
void closeConnexion(MYSQL *sqlConnexion);
MYSQL_RES *SqlSelect(char *query);