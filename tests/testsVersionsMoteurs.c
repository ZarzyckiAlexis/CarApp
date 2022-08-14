#include "..\unity\unity.h"
#include "..\includes\versionsMoteurs.h"
#include "..\includes\global.h"


void setUp (void) {



}

// Je test que la table ce créer comme prévu

void testCreationTableVersionsMoteurs (void){


    int *exist = malloc(sizeof(int));
    int *resultat = malloc(sizeof(int));

    setUp();
    
    //Suppression de toutes les tables
    destroyAllTable();

    //Ajout des tables rien avoir avec cette batterie de test
    createAllTable();

    resultat = TableExist("SELECT 1 FROM versions_moteurs LIMIT 1");

    TEST_ASSERT_EQUAL_INT(1, *resultat);

    free(exist);

}



int main (void){

UNITY_BEGIN();

RUN_TEST(testCreationTableVersionsMoteurs);

UNITY_END();

}