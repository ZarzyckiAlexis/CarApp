#include "global.h"

MYSQL *con = NULL;
// Permet de se connecter à la base de données
void initConnexion(){
  con = mysql_init(NULL);
  if (con == NULL){
    fprintf(stderr, "%s\n", mysql_error(con));
    exit(EXIT_FAILURE);
  }

  // On se connecte et regarde si on à eu d'erreur
  if (!mysql_real_connect(con, "localhost", "root",
                          NULL, DB_NAME, 3306, NULL, 0)){
    fprintf(stderr, "%s\n", mysql_error(con));
    exit(EXIT_FAILURE);
  }

}

// Permet de se déconnecter de la base de données
void closeConnexion(){
  if (con != NULL){ // Si nous somme connecter
    mysql_close(con); // On ferme la connexion
  }
}

// Permet d'effectuer les requêtes dans la base de données
MYSQL_RES *SqlSelect(char *query){
  // Executer la requête
  initConnexion(con);
  if (mysql_query(con, query)){ // Si une erreur est présente
    printf("%d", mysql_errno(con));
    fprintf(stderr, "%s\n", mysql_error(con)); // Affichage de l'erreur
    mysql_close(con); // On ferme la connexion
    exit(EXIT_FAILURE); // On quitte en erreur
  }
  // Stocker le resultat de la requête
  MYSQL_RES *sqlResult = mysql_store_result(con); // On store le resultat de la requete
  if (sqlResult == NULL){ // Si il est null
    fprintf(stderr, "%s\n", mysql_error(con)); // Affichage de l'erreur
    printf("%d", mysql_errno(con));
    mysql_close(con); // On ferme la connexion
    exit(EXIT_FAILURE); // On quitte en erreur
  }
  // Tout c'est bien passer
  closeConnexion(con); // On ferme la connexion à la BDD
  return sqlResult; // On renvois le résultat
}

int *TableExist(char *query){
  // Executer la requête
  initConnexion(con);
  int *result = malloc(sizeof(int));
  *result = 0;
  if (mysql_query(con, query)){ // Si une erreur est présente
    if(mysql_errno(con) == 1146){ // Code d'erreur table n'existe pas
        return result;
    }
    fprintf(stderr, "%s\n", mysql_error(con)); // Affichage de l'erreur
    mysql_close(con); // On ferme la connexion
    exit(EXIT_FAILURE); // On quitte en erreur
  }
  // Stocker le resultat de la requête
  MYSQL_RES *sqlResult = mysql_store_result(con); // On store le resultat de la requete
  if (sqlResult == NULL){ // Si il est null
    if(mysql_errno(con) == 1146){ // Code d'erreur table n'existe pas
        return result;
    }
    fprintf(stderr, "%s\n", mysql_error(con)); // Affichage de l'erreur
    printf("%d", mysql_errno(con));
    mysql_close(con); // On ferme la connexion
    exit(EXIT_FAILURE); // On quitte en erreur
  }
  // Tout c'est bien passer
  closeConnexion(con); // On ferme la connexion à la BDD
  *result = 1;
  return result; // On renvois le résultat
}

int erreurFichier(FILE *monFichier)
{
    if (monFichier == NULL)
    {
        int erreur = errno;
        printf("Erreur d'ouverture %d.\n", erreur);
        perror("Erreur détaillée: ");
        return true;
    }
    return false;
}