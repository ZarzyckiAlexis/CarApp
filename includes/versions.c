#include "versions.h"
#include "global.c"

int existTableVersions(){
  // Lecture de la table
  int *sqlResult = TableExist("select 1 from `versions` LIMIT 1");
  if(*sqlResult == 1){
    return 1;
  }else{
    return 0;
  }
}

int createTableVersions(){
    if(existTableVersions() == 0){ // La table n'existe pas
        // On se connecte à la base de données
        initConnexion();
        // Alors, on crée la table
        char *SqlReq = "CREATE TABLE versions( idVersion INT, nomVersion VARCHAR(50), nomModele VARCHAR(50), nomMarque VARCHAR(50), PRIMARY KEY(idVersion) );"; // On prépare notre requête SQL
        char *allocatedSqlReq = (char *)malloc(strlen(SqlReq)+ 1); // On alloue en mémoire la requete
        sprintf(allocatedSqlReq, SqlReq); // On met la requête dans allocatedSqlReq
        if (allocatedSqlReq != NULL){
            // On execute la requête et on vérifie les potentiels erreurs
            if (mysql_query(con, allocatedSqlReq)){ // Une erreur à été détecté
                closeConnexion(); // On ferme la connexion
                free(allocatedSqlReq); // On désalloue la mémoire allouée
                return 0; // On retourne en erreur de création de table
            }
            // Pas d'erreur, on continue
            // On ajoute une donnée à titre d'exemple
            free(allocatedSqlReq);
            char *SqlReq = "INSERT INTO `versions` (`idVersion`, `nomVersion`, `nomModele`, `nomMarque`) VALUES ('1', '1.1 essence', 'celica', 'toyota');"; // On prépare notre requête SQL
            char *allocatedSqlReq = (char *)malloc(strlen(SqlReq)+ 1); // On alloue en mémoire la requete
            sprintf(allocatedSqlReq, SqlReq); // On met la requête dans allocatedSqlReq
            if (allocatedSqlReq != NULL){
                // On execute la requête et on vérifie les potentiels erreurs
                if (mysql_query(con, allocatedSqlReq)){ // Une erreur à été détecté
                    closeConnexion(); // On ferme la connexion
                    free(allocatedSqlReq); // On désalloue la mémoire allouée
                    return 2; // On retourne en erreur d'ajout des données
                }
                free(allocatedSqlReq); // On désalloue la mémoire allouée
                return 1;
            }
            free(allocatedSqlReq); // On désalloue la mémoire allouée
            return 2; // Erreur ajout des données, requête null
        }
        free(allocatedSqlReq); // On désalloue la mémoire allouée
        return 0; // Erreur, création de table requête null
    }
    else{
        return -1;
    }
}

int isTableEmptyVersions(){
    if(existTableVersions() == 1){ // La table existe
        MYSQL_RES *sqlResult = SqlSelect("select * from `versions`"); // On effectue la requête
        MYSQL_ROW sqlRow;
        int result = 1; // On définit la valeur de base à 1
        while (sqlRow = mysql_fetch_row(sqlResult)){
            int row = atoi(sqlRow[0]); // On récupère le nombre de lignes 
            if(row >= 1){ // On regarde si il y'a 0 lignes
                result = 0; // Table vide
            }
        }
        return result;
    }
    else{
        return -1; // On renvois -1 => la table n'existe pas.
    }
}