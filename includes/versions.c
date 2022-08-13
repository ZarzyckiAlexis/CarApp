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
            char *SqlReq = "INSERT INTO `versions` (`idVersion`, `nomVersion`, `nomModele`, `nomMarque`) VALUES ('0', '1990 T18', 'celica', 'toyota');"; // On prépare notre requête SQL
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
                executerCommandeSQL("INSERT INTO `versions` (`idVersion`, `nomVersion`, `nomModele`, `nomMarque`) VALUES ('998', '2.0 gti', '206', 'peugeot');");
                executerCommandeSQL("INSERT INTO `versions` (`idVersion`, `nomVersion`, `nomModele`, `nomMarque`) VALUES ('999', '1.6 sti', 'wrx', 'subaru');");
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
        MYSQL_RES *sqlResult = SqlSelect("select COUNT(*) from `versions`"); // On effectue la requête
        MYSQL_ROW sqlRow;
        int result = 1; // On définit la valeur de base à 1
        while (sqlRow = mysql_fetch_row(sqlResult)){
            int row = atoi(sqlRow[0]); // On récupère le nombre de lignes 
            if(row >= 1){ // On regarde si il y'a 0 lignes
                return 0; // Table vide
            }
        }
        return result;
    }
    else{
        return -1; // On renvois -1 => la table n'existe pas.
    }
}

void getVersions(char versions[][100], int *count){
    if(existTableVersions() == 1){ // La table existe!
        // Lecture de la table
        MYSQL_RES *sqlResult = SqlSelect("SELECT * FROM versions ORDER BY nomMarque, nomModele");
        int nombreMax = 100;
        int nombreCurrent = 0;
        char *versionsTable = (char *) malloc(nombreMax);
        MYSQL_ROW sqlRow;
        while (sqlRow = mysql_fetch_row(sqlResult))
        {
            // Lecture du contenu ligne par ligne et conversion dans les types
            char *nomVersion = (char *)malloc(strlen(sqlRow[1] + 1));
            char *nomModele = (char *)malloc(strlen(sqlRow[2] + 1));
            char *nomMarque = (char *)malloc(strlen(sqlRow[3] + 1));
            strcpy(nomVersion, sqlRow[1]);
            strcpy(nomModele, sqlRow[2]);
            strcpy(nomMarque, sqlRow[3]);
            // Extension de la table si necessaire
            if (nombreCurrent >= nombreMax){
                nombreMax += 10;
                versionsTable = realloc(versionsTable, nombreMax);
            }
            // Ajout dans la table
            strcpy(versionsTable, nomVersion);
            for(int x=0;x<100; x++){
                versions[nombreCurrent][x] = versionsTable[x];   
            }
            nombreCurrent++;
            strcpy(versionsTable, nomModele);
            for(int x=0;x<100; x++){
                versions[nombreCurrent][x] = versionsTable[x];   
            }
            nombreCurrent++;
            strcpy(versionsTable, nomMarque);
            for(int x=0;x<100; x++){
                versions[nombreCurrent][x] = versionsTable[x];   
            }
            nombreCurrent++;
        }
        // Libération memoire du resultat SQL
        mysql_free_result(sqlResult);
        *count = nombreCurrent;
        free(versionsTable);
    }
}

void addVersions(char *nameVersion, char *nameModele, char *idMoteur, char *errors){
    FILE* idFile = NULL;
    idFile = fopen("../source/idVersions.txt", "r");
    char *originalNameVersion = (char *)malloc(1000);
    char *originalNameModele = (char *)malloc(1000);
    char *originalIdMoteur = (char *)malloc(1000);
    strcpy(originalNameVersion, nameVersion);
    strcpy(originalNameModele, nameModele);
    strcpy(originalIdMoteur, idMoteur);
    if(erreurFichier(idFile, 0) == 0){  // On essaye de lire le fichier --> Il existe, on continue ; Si pas, on le crée.
        printf("\nOuverture du fichier idVersions...\n"); // On affiche l'ouverture réussie du fichier
        char *id = (char *)malloc(sizeof(int) * 100);
        fgets(id, 100, idFile);
        if(existTableVersions() == 1){ // La table existe!
            // Lecture de la table
            // Début de la Vérification de l'existence du nom du modèle + récupération du nom de la marque
            // Création de la requête SQL
            char *query = (char *)malloc(100);
            strcpy(query, "SELECT nomMarque FROM versions WHERE nomModele=");
            //char query[100] = "SELECT nomMarque FROM versions WHERE nomModele="; // base de la requête
            char *stroke = (char *)malloc(100);
            strcpy(stroke, "'");
            //char stroke[10] = "'"; // caractère autour du modèle
            strcat(query, stroke); // On met le caractère après l'égal
            strcat(query, nameModele); // on met le nom du modèle
            strcat(query, stroke); // on met le caractère après le modèle
            // On s'occupe du résultat
            MYSQL_RES *sqlResult = SqlSelect(query);
            char *nameMarquesTable = (char *) malloc(100);
            char *nameMarques = (char *)malloc(100);
            strcpy(nameMarques, "null"); // On met la valeur par défaut à "null"
            MYSQL_ROW sqlRow;
            while (sqlRow = mysql_fetch_row(sqlResult))
            {
                // Lecture du contenu ligne par ligne et conversion dans les types
                char *currentResult = (char *)malloc(strlen(sqlRow[0] + 1));
                strcpy(currentResult, sqlRow[0]);
                // Ajout dans la table
                strcpy(nameMarquesTable, currentResult);
                for(int x=0;x<100; x++){
                    nameMarques[x] = nameMarquesTable[x]; // On met le nom de la marque dans le nameVersions
                }
            }
            free(nameMarquesTable);
            if(strcmp(nameMarques, "null") == 0){ // Le nom est toujours null => Erreur on quitte, le modèle ne trouve pas de marque => n'existe pas
                strcpy(errors, "Ce modele ne correponds a aucune marque!\n");
                //printf("marques");
            }
            else{
                //printf("\n%s", nameMarques); // On affiche le nom de la marques
                // Fin de la Vérification de l'existence du nom du modèle + récupération du nom de la marque
                // Début de la vérification de l'existence de l'idMoteur
                // Création de la requête SQL
                strcpy(query, "SELECT idMoteur FROM moteurs WHERE idMoteur=");
                strcat(query, stroke); // On met le caractère après l'égal
                strcat(query, idMoteur); // on met l'id
                strcat(query, stroke); // on met le caractère après l'id
                // On s'occupe du résultat
                MYSQL_RES *sqlResult = SqlSelect(query);
                char *idMoteursTable = (char *) malloc(100);
                char *idMoteurs = (char *)malloc(100);
                strcpy(idMoteurs, "null"); // On met la valeur par défaut à "null"
                MYSQL_ROW sqlRow;
                while (sqlRow = mysql_fetch_row(sqlResult))
                {
                    // Lecture du contenu ligne par ligne et conversion dans les types
                    char *currentResult = (char *)malloc(strlen(sqlRow[0] + 1));
                    strcpy(currentResult, sqlRow[0]);
                    // Ajout dans la table
                    strcpy(idMoteursTable, currentResult);
                    for(int x=0;x<100; x++){
                        idMoteurs[x] = idMoteursTable[x]; // On met l'id dans l'idMoteurs
                    }
                }
                free(idMoteursTable);
                if(strcmp(idMoteurs, "null") == 0){ // L'id est toujours null => Erreur on quitte, l'id n'existe pas
                    strcpy(errors, "Cette id n'existe pas!\n");
                    //printf("id");
                }
                else{
                    free(idMoteurs);
                    // Fin de la Vérification de l'existence de l'id moteur
                    // Début de la vérification de la non existence du nomVersion
                    // Création de la requête SQL
                    strcpy(query, "select 1 from `versions` WHERE nomVersion=");
                    strcat(query, stroke); // On met le caractère après l'égal
                    strcat(query, nameVersion); // on met le nom de la version
                    strcat(query, stroke); // on met le caractère après le nom de la version
                    strcat(query, " LIMIT 1");
                    int *sqlResult = isDataPresent(query);
                    if(*sqlResult == 1){
                        strcpy(errors, "Cette version existe deja!\n");
                    }
                    else{
                        //printf("\n%s", nameVersion); // On affiche le nom de la version
                        printf("\nAjout reussi ! \n\t - Marque: %s \n\t - Modele: %s \n\t Version: \n\t\t - Id: %s \n\t\t - Nom: %s \n\t - Moteur: \n\t\t - Id: %s \n", nameMarques, originalNameModele, id, originalNameVersion, originalIdMoteur);
                        // Fin de la Vérification de la non existence du nomVersion
                        // On ajoute dans la BDD
                        char *req = "INSERT INTO versions (idVersion, nomVersion, nomModele, nomMarque) VALUES ('%s','%s','%s','%s')";
                        char *insert = malloc(10000);
                        sprintf(insert, req, id, originalNameVersion, originalNameModele, nameMarques);
                        executerCommandeSQL(insert);
                        char *req2 = "INSERT INTO `versions_moteurs`(`idMoteur`, `idVersion`) VALUES ('%s','%s')";
                        char *insert2 = malloc(10000);
                        sprintf(insert2, req2, idMoteur, id);
                        executerCommandeSQL(insert2);
                        fclose(idFile);
                        idFile = fopen("../source/idVersions.txt", "w"); // On créer un fichier et on l'ouvre en écriture
                        if(erreurFichier(idFile, 0) == 0){ // Il n'existe pas, on va le créer
                           // printf("%d", ancientId); 
                            int lengthstr = strlen(id);
                            int pos = lengthstr - 1; // Last char
                            int prevpos = pos-1; // Prev last char
                            int nextpos = pos+1; // Blank after last char
                            if(id[pos] == '9'){ // Caractère 9
                                if(prevpos < 0){
                                    int counternext = nextpos;
                                    int counterpos = pos;
                                    int counterprev = prevpos;
                                    for(;counterprev!=0; counterprev++){
                                        id[counternext] = id[counterpos];
                                        id[counterpos] = '0';
                                        counternext++;
                                        counterpos++;
                                    }
                                    id[pos] = id[pos] + 1;
                                    id[counterpos] = '0';
                                    id[counternext] = '\0'; // on met le caractère de fin

                                }
                                else{
                                    id[prevpos] = id[prevpos] + 1;
                                    id[pos] = '0';
                                }
                            }
                            else{ // Sinon on ajoute 1
                                id[pos] = id[pos] + 1;
                            }
                            char idToPut[100];
                            strcpy(idToPut, id);
                            fputs(idToPut, idFile);
                            free(nameMarques);
                            free(insert);
                            free(insert2);
                        }
                    }
                }
                // Libération memoire du resultat SQL
                mysql_free_result(sqlResult);
                }
            // Libération memoire du resultat SQL
            free(query);
            mysql_free_result(sqlResult);
        }
        strcat(errors, "\0");
        free(originalNameVersion);
        free(originalIdMoteur);
        free(originalNameModele);
        free(id);
        fclose(idFile); // On ferme le fichier
    }
    else{
        fclose(idFile);
        idFile = fopen("../source/idVersions.txt", "w"); // On créer un fichier et on l'ouvre en écriture
        if(erreurFichier(idFile, 0) == 0){ // Il n'existe pas, on va le créer
            printf("Generation du fichier idVersions..."); 
            char id[] = "1"; // On défini l'ID à 0
            fputc(id[0], idFile); // On insert l'ID dans l fichier
        }
    }
}

