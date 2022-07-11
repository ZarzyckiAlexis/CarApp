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


int main(void){
    UNITY_BEGIN();
    RUN_TEST(testNotExistTableVersions);
    RUN_TEST(testCreateTableVersions);
    RUN_TEST(testExistTableVersions);
    UNITY_END();
    return 0;
}
