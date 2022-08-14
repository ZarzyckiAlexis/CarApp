#include "..\unity\unity.h"
#include "..\includes\moteurs.h"
#include "..\includes\global.h"

static int idMoteur;
static int nbVersions;
static MYSQL_RES *res;
static MYSQL_ROW ligne;
static int tableauIdVersions[3];
static int nbMoteursA;
static int nbMoteursB;

void setUp(void)
{
    nbMoteursA = 0;
    nbMoteursB = 0;
    idMoteur = 0;
    nbVersions = 0;
    res = NULL;
}

// Je test que la table ce créer comme prévu

void testCreationTableMoteurs(void)
{

    int *exist = malloc(sizeof(int));
    int *resultat = malloc(sizeof(int));

    setUp();

    // Suppression de toutes les tables
    destroyAllTable();

    // Ajout des tables rien avoir avec cette batterie de test
    createAllTable();

    resultat = TableExist("SELECT 1 FROM moteurs LIMIT 1");

    TEST_ASSERT_EQUAL_INT(1, *resultat);

    free(exist);
}

// Des moteurs et versions de test doivent être créer dans la DB pour ces tests

// Test dans le cas ou le moteur demander n'existe pas
void testMoteurInexistant(void)
{

    setUp();
    idMoteur = 3;
    res = recuperationDesVersions(idMoteur, &nbVersions);

    TEST_ASSERT_EQUAL_INT(-1, nbVersions);
}

// Test dans le cas ou le moteur demander ne possède pas de versions
void testMoteurSansVersions(void)
{

    setUp();
    idMoteur = 1;
    res = recuperationDesVersions(idMoteur, &nbVersions);

    TEST_ASSERT_EQUAL_INT(0, nbVersions);
}

// Test dans le cas ou le moteur à des versions et tout ce passe bien
void testMoteurExistantEtVersions(void)
{

    setUp();
    idMoteur = 0;
    res = recuperationDesVersions(idMoteur, &nbVersions);

    TEST_ASSERT_EQUAL_INT(3, nbVersions);
}

// Test que le tableau d'id des versions possèdant le moteur demander ce remplis correctement pour cela on sais que l'id dans la case 1 du tableau sera 2
void testRecupIdVersions(void)
{

    setUp();
    idMoteur = 0;

    res = recuperationDesVersions(idMoteur, &nbVersions);

    recuperationDuResultat(tableauIdVersions, res);

    TEST_ASSERT_EQUAL_INT(998, tableauIdVersions[1]);
}

// Test on sais que l'information récupérer dans ligne 0 de la matrice sera le nomVersion qui est GTI si tout ce passe bien ou devrait retrouver cette chaine
void testRecupInfos(void)
{

    char tableauInfosVersions[12][51];
    setUp();
    idMoteur = 0;

    res = recuperationDesVersions(idMoteur, &nbVersions);

    recuperationDuResultat(tableauIdVersions, res);
    recuperationDesInfosVersions(tableauInfosVersions, tableauIdVersions, nbVersions);

    TEST_ASSERT_EQUAL_STRING("1990 T18", &tableauInfosVersions[0][0]);
}

void testCompterLesMoteurs(void)
{

    setUp();

    res = SqlSelect("SELECT COUNT(cylindree) FROM moteurs");

    ligne = mysql_fetch_row(res);
    nbMoteursA = atoi(*ligne);

    mysql_free_result(res);

    nbMoteursB = combienDeMoteurs();

    TEST_ASSERT_EQUAL_INT(nbMoteursB, nbMoteursA);
}

void testRecupInfosMoteurs(void)
{

    setUp();

    nbMoteursA = combienDeMoteurs();

    // 21 suffira car la seul partie en char est le type de carburant qui est varchar(20)
    char tableauDesMoteurs[nbMoteursA * 5][21];

    recuperationDesInfosMoteurs(tableauDesMoteurs);

    TEST_ASSERT_EQUAL_STRING("0", &tableauDesMoteurs[0][0]);
}

int main(void)
{

    UNITY_BEGIN();

    RUN_TEST(testCreationTableMoteurs);
    RUN_TEST(testMoteurInexistant);
    RUN_TEST(testMoteurSansVersions);
    RUN_TEST(testMoteurExistantEtVersions);
    RUN_TEST(testRecupIdVersions);
    RUN_TEST(testRecupInfos);
    RUN_TEST(testCompterLesMoteurs);
    RUN_TEST(testRecupInfosMoteurs);

    UNITY_END();
}