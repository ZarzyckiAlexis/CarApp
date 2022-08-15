#include "global.h"
#include "versions.h"
#include "moteurs.h"
#include "versionsMoteurs.h"

MYSQL *con = NULL;

// Permet de se connecter à la base de données
void initConnexion()
{
  con = mysql_init(NULL);
  if (con == NULL)
  {
    fprintf(stderr, "%s\n", mysql_error(con));
    exit(EXIT_FAILURE);
  }

  // On se connecte et regarde si on à eu d'erreur
  if (!mysql_real_connect(con, "localhost", "root",
                          NULL, DB_NAME, 3306, NULL, 0))
  {
    fprintf(stderr, "%s\n", mysql_error(con));
    exit(EXIT_FAILURE);
  }
}

// Permet de se déconnecter de la base de données
void closeConnexion()
{
  if (con != NULL)
  {                   // Si nous somme connecter
    mysql_close(con); // On ferme la connexion
  }
}

// Permet d'effectuer les requêtes dans la base de données
MYSQL_RES *SqlSelect(char *query)
{
  // Executer la requête
  initConnexion(con);
  if (mysql_query(con, query))
  { // Si une erreur est présente
    printf("%d", mysql_errno(con));
    fprintf(stderr, "%s\n", mysql_error(con)); // Affichage de l'erreur
    mysql_close(con);                          // On ferme la connexion
    exit(EXIT_FAILURE);                        // On quitte en erreur
  }
  // Stocker le resultat de la requête
  MYSQL_RES *sqlResult = mysql_store_result(con); // On store le resultat de la requete
  if (sqlResult == NULL)
  {                                            // Si il est null
    fprintf(stderr, "%s\n", mysql_error(con)); // Affichage de l'erreur
    printf("%d", mysql_errno(con));
    mysql_close(con);   // On ferme la connexion
    exit(EXIT_FAILURE); // On quitte en erreur
  }
  // Tout c'est bien passer
  closeConnexion(con); // On ferme la connexion à la BDD
  return sqlResult;    // On renvois le résultat
}

// Permet de vérifier si une table existe
int *TableExist(char *query)
{
  // Executer la requête
  initConnexion(con);
  int *result = malloc(sizeof(int));
  *result = 0;
  if (mysql_query(con, query))
  { // Si une erreur est présente
    if (mysql_errno(con) == 1146)
    { // Code d'erreur table n'existe pas
      return result;
    }
    fprintf(stderr, "%s\n", mysql_error(con)); // Affichage de l'erreur
    mysql_close(con);                          // On ferme la connexion
    exit(EXIT_FAILURE);                        // On quitte en erreur
  }
  // Stocker le resultat de la requête
  MYSQL_RES *sqlResult = mysql_store_result(con); // On store le resultat de la requete
  if (sqlResult == NULL)
  { // Si il est null
    if (mysql_errno(con) == 1146)
    { // Code d'erreur table n'existe pas
      return result;
    }
    fprintf(stderr, "%s\n", mysql_error(con)); // Affichage de l'erreur
    printf("%d", mysql_errno(con));
    mysql_close(con);   // On ferme la connexion
    exit(EXIT_FAILURE); // On quitte en erreur
  }
  // Tout c'est bien passer
  closeConnexion(con); // On ferme la connexion à la BDD
  *result = 1;
  return result; // On renvois le résultat
}

// Permet d'exectuer une instruction SQL
void executerCommandeSQL(char *instructionSQL) // Exécution de chaine de commande SQL
{
  initConnexion();
  if (mysql_query(con, instructionSQL))
  {
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(EXIT_FAILURE);
  }
  closeConnexion();
}

// Permet de vérifier si on à pas une erreur au niveau d'un fichier
int erreurFichier(FILE *monFichier, int showText)
{
  if (monFichier == NULL)
  {
    if (showText == 0)
    { // Permet de ne pas afficher les erreurs dans la console
      return true;
    }
    int erreur = errno;
    printf("Erreur d'ouverture %d.\n", erreur);
    perror("Erreur détaillée: ");
    return true;
  }
  return false;
}

int *isDataPresent(char *query)
{
  // Executer la requête
  initConnexion(con);
  int *result = malloc(sizeof(int));
  *result = 0;
  if (mysql_query(con, query))
  {                                            // Si une erreur est présente
    fprintf(stderr, "%s\n", mysql_error(con)); // Affichage de l'erreur
    mysql_close(con);                          // On ferme la connexion
    exit(EXIT_FAILURE);                        // On quitte en erreur
  }
  // Stocker le resultat de la requête
  MYSQL_RES *sqlResult = mysql_store_result(con); // On store le resultat de la requete
  if (sqlResult == NULL)
  {                                            // Si il est null
    fprintf(stderr, "%s\n", mysql_error(con)); // Affichage de l'erreur
    printf("%d", mysql_errno(con));
    mysql_close(con);   // On ferme la connexion
    exit(EXIT_FAILURE); // On quitte en erreur
  }
  MYSQL_ROW sqlRow;
  char res = -1;
  while (sqlRow = mysql_fetch_row(sqlResult))
  {
    res = atoi(sqlRow[0]);
  }
  *result = res;
  // Tout c'est bien passer
  closeConnexion(con); // On ferme la connexion à la BDD
  return result;       // On renvois le résultat
}

void destroyAllTable()
{
  int *resultat = TableExist("SELECT 1 FROM versions_moteurs LIMIT 1");
  if (*resultat == 1)
  {
    executerCommandeSQL("DROP TABLE versions_moteurs");
  }
  if (existTableVersions())
  {
    executerCommandeSQL("DROP TABLE versions");
  }
  resultat = TableExist("SELECT 1 FROM moteurs LIMIT 1");
  if (*resultat == 1)
  {
    executerCommandeSQL("DROP TABLE moteurs");
  }
}

void createAllTable()
{
  createTableVersions();
  creationTableMoteurs();
  creationTableVersionsMoteurs();
}