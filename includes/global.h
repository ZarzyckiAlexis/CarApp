#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <mysql.h>
#include <stdbool.h>
#define DB_NAME "projet" // Le nom de la base de données

int erreurFichier(FILE *monFichier);
void initConnexion();
void closeConnexion();
MYSQL_RES *SqlSelect(char *query);