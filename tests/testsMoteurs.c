#include "..\unity\unity.h"
#include "..\includes\moteurs.h"
#include "..\includes\global.h"


void setUp (void) {



}

// Je test que la table ce créer comme prévu

void testCreationTableMoteurs (void){

    int *exist = malloc(sizeof(int));
    int resultat;

    setUp();

    exist = TableExist("SELECT 1 FROM moteurs LIMIT 1");

    if (*exist == 1){
        initConnexion();
        executerCommandeSQL ("DROP TABLE moteurs");
        closeConnexion();
    }

    resultat = creationTableMoteurs();

    
    TEST_ASSERT_EQUAL_INT( 1, resultat);

    free(exist);

}



int main (void){

UNITY_BEGIN();

RUN_TEST(testCreationTableMoteurs);

UNITY_END();

}