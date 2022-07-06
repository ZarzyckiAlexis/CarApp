#include "global.h"

void initConnexion(MYSQL *sqlConnexion){

  sqlConnexion = mysql_init(NULL);
  if (sqlConnexion == NULL){
    fprintf(stderr, "%s\n", mysql_error(sqlConnexion));
    exit(EXIT_FAILURE);
  }

  // On se connecte et regarde si on à eu d'erreur
  if (!mysql_real_connect(sqlConnexion, "localhost", "root",
                          NULL, DB_NAME, 3306, NULL, 0)){
    fprintf(stderr, "%s\n", mysql_error(sqlConnexion));
    exit(EXIT_FAILURE);
  }

}

void closeConnexion(MYSQL *sqlConnexion){
  if (sqlConnexion != NULL){ // Si nous somme connecter
    mysql_close(sqlConnexion); // On ferme la connexion
  }
}

MYSQL_RES *SqlSelect(char *query){

  MYSQL *con = NULL;
  // Executer la requête
  initConnexion(con);
  if (mysql_query(con, query)){ // Si une erreur est présente
    fprintf(stderr, "%s\n", mysql_error(con)); // Affichage de l'erreur
    mysql_close(con); // On ferme la connexion
    exit(EXIT_FAILURE); // On quitte en erreur
  }
  // Stocker le resultat de la requête
  MYSQL_RES *sqlResult = mysql_store_result(con); // On store le resultat de la requete
  if (sqlResult == NULL){ // Si il est null
    fprintf(stderr, "%s\n", mysql_error(con)); // Affichage de l'erreur
    mysql_close(con); // On ferme la connexion
    exit(EXIT_FAILURE); // On quitte en erreur
  }
  // Tout c'est bien passer
  closeConnexion(con); // On ferme la connexion à la BDD
  return sqlResult; // On renvois le résultat
}