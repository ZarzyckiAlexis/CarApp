#include "versionsMoteurs.h"

int creationTableVersionsMoteurs(void)
{

   // Déclaration des variables
   char *requeteSQL = malloc(250);

   int *resultat = malloc(sizeof(int));

   // Vérification que la table n'existe pas
   resultat = TableExist("SELECT 1 FROM versions_moteurs LIMIT 1");

   if (*resultat != 1)

   {

      // Création de la rêquete
      sprintf(requeteSQL,"CREATE TABLE versions_moteurs(idMoteur INT, idVersion INT, PRIMARY KEY(idMoteur, idVersion), FOREIGN KEY(idMoteur) REFERENCES moteurs(idMoteur), FOREIGN KEY(idVersion) REFERENCES versions(idVersion));");

          // Exécution de la rêquete
          executerCommandeSQL(requeteSQL);
          executerCommandeSQL("INSERT INTO `versions_moteurs` (`idMoteur`, `idVersion`) VALUES ('0', '0');");
          executerCommandeSQL("INSERT INTO `versions_moteurs` (`idMoteur`, `idVersion`) VALUES ('0', '998');");
          executerCommandeSQL("INSERT INTO `versions_moteurs` (`idMoteur`, `idVersion`) VALUES ('0', '999');");

      free(requeteSQL);
      free(resultat);
      return 1; // La table est créer
   }
   else
      // Si resultat n'est pas = à 1 c'est que la table existe déjà 
      printf("La table versions_moteurs est déjà existante. Si vous voulez la régénerer supprimer la au préalable");

   free(requeteSQL);
   free(resultat);
   return 0; // La table n'est pas créer
}