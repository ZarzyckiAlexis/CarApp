#include "..\unity\unity.h"
#include "..\includes\moteurs.h"
#include "..\includes\global.h"

static int idMoteur;
static int nbVersions;
static MYSQL_RES *res;
static int tableauIdVersions[3];

void setUp(void)
{

    idMoteur = 0;
    nbVersions = 0;
    res = NULL;
}

// Je test que la table ce créer comme prévu

void testCreationTableMoteurs(void)
{

    int *exist = malloc(sizeof(int));
    int resultat;

    setUp();

    exist = TableExist("SELECT 1 FROM moteurs LIMIT 1");

    resultat = creationTableMoteurs();

    TEST_ASSERT_EQUAL_INT(1, resultat);

    free(exist);
}


// Des moteurs et versions de test doivent être créer dans la DB pour ces tests

// Test dans le cas ou le moteur demander n'existe pas
void testMoteurInexistant(void)
{

    setUp();
    idMoteur = 3;
    creationListePourMoteurs(idMoteur, &nbVersions);

    TEST_ASSERT_EQUAL_INT(-1, nbVersions);
}

// Test dans le cas ou le moteur demander ne possède pas de versions
void testMoteurSansVersions(void)
{

    setUp();
    idMoteur = 2;
    creationListePourMoteurs(idMoteur, &nbVersions);

    TEST_ASSERT_EQUAL_INT(0, nbVersions);
}

// Test dans le cas ou le moteur à des versions et tout ce passe bien
void testMoteurExistantEtVersions(void)
{

    setUp();
    idMoteur = 1;
    creationListePourMoteurs(idMoteur, &nbVersions);

    TEST_ASSERT_EQUAL_INT(3, nbVersions);
}

// Test que la fonction recuperationDesVersions récupère bien les versions on utilise un moteur dans lequel on sais qu'il y a 3 versions
void testRecupVersions(void)
{

    setUp();
    idMoteur = 1;

    res = recuperationDesVersions(idMoteur, &nbVersions);

    TEST_ASSERT_EQUAL_INT(3, nbVersions);
}

// Test que le tableau d'id des versions possèdant le moteur demander ce remplis correctement pour cela on sais que l'id dans la case 1 du tableau sera 2
void testRecupIdVersions(void)
{

    setUp();
    idMoteur = 1;

    res = recuperationDesVersions(idMoteur, &nbVersions);

    recuperationDuResultat(tableauIdVersions, res);

    TEST_ASSERT_EQUAL_INT(2, tableauIdVersions[1]);
}

// Test on sais que l'information récupérer dans ligne 0 de la matrice sera le nomVersion qui est GTI si tout ce passe bien ou devrait retrouver cette chaine
void testRecupInfos(void)
{

    char tableauInfosVersions[12][51];
    setUp();
    idMoteur = 1;

    res = recuperationDesVersions(idMoteur, &nbVersions);

    recuperationDuResultat(tableauIdVersions, res);
    recuperationDesInfosVersions(tableauInfosVersions, tableauIdVersions, nbVersions);

    TEST_ASSERT_EQUAL_STRING("GTI", &tableauInfosVersions[0][0]);
}

int main(void)
{

    UNITY_BEGIN();

    RUN_TEST(testCreationTableMoteurs);
    RUN_TEST(testMoteurInexistant);
    RUN_TEST(testMoteurSansVersions);
    RUN_TEST(testMoteurExistantEtVersions);
    RUN_TEST(testRecupVersions);
    RUN_TEST(testRecupIdVersions);
    RUN_TEST(testRecupInfos);

    UNITY_END();
}