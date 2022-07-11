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



int main(void){
    UNITY_BEGIN();
    RUN_TEST(testNotExistTableVersions);
    RUN_TEST(testCreateTableVersions);
    RUN_TEST(testExistTableVersions);
    RUN_TEST(testTableNotEmpty);
    RUN_TEST(testTableEmpty);
    UNITY_END();
    return 0;
}
