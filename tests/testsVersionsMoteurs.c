#include "..\unity\unity.h"
#include "..\includes\versionsMoteurs.h"
#include "..\includes\global.h"


void setUp (void) {



}

// Je test que la table ce créer comme prévu

void testCreationTableVersionsMoteurs (void){

    int *exist = malloc(sizeof(int));
    int resultat;

    setUp();

    exist = TableExist("SELECT 1 FROM versions_moteurs LIMIT 1");

    if (*exist == 1){
        initConnexion();
        executerCommandeSQL ("DROP TABLE versions_moteurs");
        closeConnexion();
    }

    resultat = creationTableVersionsMoteurs();

    
    TEST_ASSERT_EQUAL_INT( 1, resultat);

    free(exist);

}



int main (void){

UNITY_BEGIN();

RUN_TEST(testCreationTableVersionsMoteurs);

UNITY_END();

}