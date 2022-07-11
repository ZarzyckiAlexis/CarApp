#include "..\unity\unity.h"
#include "..\includes\moteurs.h"
#include "..\includes\global.h"


void setUp (void) {



}

// Je test que la table ce créer comme prévu

void testCreationTableMoteurs (void){

    int *resultat = malloc(sizeof(int));

    setUp();

    creationTableMoteurs();

    resultat = TableExist("SELECT 1 FROM moteurs LIMIT 1");
    
    TEST_ASSERT_EQUAL_INT( 1, *resultat);

}



int main (void){

UNITY_BEGIN();

RUN_TEST(testCreationTableMoteurs);

UNITY_END();

}