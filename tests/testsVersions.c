#include "..\includes\versions.h"
#include "..\unity\unity.h"

void setup(){
}

// test de l'existence de la table versions
void testExistTableVersions(){
    int resultat;
    resultat = existTableVersions(); // Existe -> retourne 1
    TEST_ASSERT_EQUAL(1, resultat); // Elle existe
}

void testNotExistTableVersions(){
    int resultat;
    executerCommandeSQL("DROP TABLE versions"); // On supprime la table
    resultat = existTableVersions(); // Existe pas -> retourne 0
    TEST_ASSERT_EQUAL(0, resultat); // Elle n'existe pas
}

// test sur la création de la table version
void testCreateTableVersions(){
    int resultat;
    resultat = createTableVersions(); // Création réussie ?
    TEST_ASSERT_EQUAL(1, resultat); // Oui, elle retourne 1
}

// test sur les données présente dans la table
void testTableEmpty(){
    int resultat;
    executerCommandeSQL("DELETE FROM versions"); // On supprime le contenu de la table
    resultat = isTableEmptyVersions(); // La table est-elle vide ?
    TEST_ASSERT_EQUAL(1, resultat); // Oui, elle retourne 1
    // On recrée la base à son origine
    executerCommandeSQL("DROP TABLE versions"); // On supprime la table
    // On la regénère
    createTableVersions();
}

// test sur les données présente dans la table
void testTableNotEmpty(){
    int resultat;
    resultat = isTableEmptyVersions(); // La table est-elle vide ?
    TEST_ASSERT_EQUAL(0, resultat); // Non, elle retourne 0
}

// test sur le garnissage du tableau des versions

void testTableVersions(){
    char *nomVersions = (char *)malloc(50); // On alloue en mémoire le nom de la version souhaitée
    char versions[100][100]; // On initialise le tableau
    int *nbElements = (int *)malloc(sizeof(int)); // On alloue en mémoire le nombre d'éléments dans le tableau
    int result = 0; // On affecte le résultat à 0 par défaut, on part sur une base "non trouvée"
    strcpy(nomVersions, "1.1 essence"); // On rentre le nom de la version codée en dur
    getVersions(versions, nbElements); // On récupère les versions dans la DB
    for(int i=0; i<*nbElements; i++){ // On boucle jusqu'au dernier éléments du tableau
        if(strcmp(versions[i], nomVersions) == 0){ // On vérifie si l'élément en cours est égal à celui souhaité
            result = 1; // On à trouvé, on retourne 1
        }
    }
    TEST_ASSERT_EQUAL(1, result); // C'est bon
    free(nomVersions); // On s'occupe de désalloué l'emplacement mémoire après l'éxécution du programme de test
    free(nbElements);
}



int main(void){
    UNITY_BEGIN();
    RUN_TEST(testNotExistTableVersions);
    RUN_TEST(testCreateTableVersions);
    RUN_TEST(testExistTableVersions);
    RUN_TEST(testTableNotEmpty);
    RUN_TEST(testTableEmpty);
    RUN_TEST(testTableVersions);
    UNITY_END();
    return 0;
}
