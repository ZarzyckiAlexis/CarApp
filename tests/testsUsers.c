#include "..\includes\users.h"
#include "..\unity\unity.h"

#define DIM 60

static char login[DIM];
FILE*fichier;

void setup(){

}
//POUR LA FONCTION DE CONNEXION
void connexion_nul(){
        char log[DIM]="Noah";
        char mdp[DIM]="s";
        TEST_ASSERT_EQUAL_UINT(0,identification(log,mdp,DIM));
}
void connexion_simple(){
        char log[DIM]="Simple";
        char mdp[DIM]="Simple";
        TEST_ASSERT_EQUAL_UINT(1,identification(log,mdp,DIM));
}

void connexion_admin(){
        char log[DIM]="Admin";
        char mdp[DIM]="Admin";
        TEST_ASSERT_EQUAL_UINT(2,identification(log,mdp,DIM));
}
//POUR VERIFIER SI LE PSEUDO EXISTE
void log_pris_admin()
{       
        char login[DIM]="Admin";
        TEST_ASSERT_EQUAL_UINT(2,check_existe(login,DIM,fichier));
}
void log_pris_simple()
{       
        char login[DIM]="Simple";
        TEST_ASSERT_EQUAL_UINT(1,check_existe(login,DIM,fichier));
}

void log_non_pris()
{
        char login[DIM]="paspris";
        TEST_ASSERT_EQUAL_UINT(0,check_existe(login,DIM,fichier));
}
//POUR AJOUTER
void ajouter_ok_uti(){
        char log[DIM]="Uti";
        char mdp[DIM]="1205";
        TEST_ASSERT_EQUAL_UINT(1,ajouter(fichier,log,mdp,DIM,"=Log"));
}
void ajouter_ok_admin(){
        char log[DIM]="Admin2";
        char mdp[DIM]="1205";
        TEST_ASSERT_EQUAL_UINT(1,ajouter(fichier,log,mdp,DIM,"=LogAdmin"));
}
void ajouter_ko_log(){
        char log[DIM]="Admin";
        char mdp[DIM]="1205";
        TEST_ASSERT_EQUAL_UINT(0,ajouter(fichier,log,mdp,DIM,"=LogAdmin"));
}
void ajouter_ko_uti_0(){
        char log[DIM]="0";
        char mdp[DIM]="Free";
        TEST_ASSERT_EQUAL_UINT(0,ajouter(fichier,log,mdp,DIM,"=LogAdmin"));
}
void ajouter_ko_mdp_0(){
        char log[DIM]="Admin3";
        char mdp[DIM]="0";
        TEST_ASSERT_EQUAL_UINT(0,ajouter(fichier,log,mdp,DIM,"=LogAdmin"));
}
void ajouter_ko_uti_long(){
        char log[DIM]="sssssssssssssssssssssssssssssssssssssssssssssssssss";
        char mdp[DIM]="Free";
        TEST_ASSERT_EQUAL_UINT(0,ajouter(fichier,log,mdp,DIM,"=LogAdmin"));
}
void ajouter_ko_mdp_long(){
        char log[DIM]="Admin3";
        char mdp[DIM]="sssssssssssssssssssssssssssssssssssssssssssssssssss";
        TEST_ASSERT_EQUAL_UINT(0,ajouter(fichier,log,mdp,DIM,"=LogAdmin"));
}
//POUR MODIFIER
void modifier_ok_admin(){
        char log_actu[DIM]="Admin";
        char log[DIM]="Admin3";
        char mdp[DIM]="Admin3";
        TEST_ASSERT_EQUAL_UINT(1,modifier(fichier,log_actu,log,mdp,DIM));
}
void modifier_ok_uti(){
        char log_actu[DIM]="Simple";
        char log[DIM]="Simple2";
        char mdp[DIM]="Simple2";
        TEST_ASSERT_EQUAL_UINT(1,modifier(fichier,log_actu,log,mdp,DIM));
}
void modifier_ko_log_0(){
        char log_actu[DIM]="Simple2";
        char log[DIM]="0";
        char mdp[DIM]="1205";
        TEST_ASSERT_EQUAL_UINT(0,modifier(fichier,log_actu,log,mdp,DIM));
}
void modifier_ko_mdp_0(){
        char log_actu[DIM]="Simple2";
        char log[DIM]="Simple2";
        char mdp[DIM]="0";
        TEST_ASSERT_EQUAL_UINT(1,modifier(fichier,log_actu,log,mdp,DIM));
}
void modifier_ko_log_pris(){
        char log_actu[DIM]="Simple2";
        char log[DIM]="Admin3";
        char mdp[DIM]="1205";
        TEST_ASSERT_EQUAL_UINT(0,modifier(fichier,log_actu,log,mdp,DIM));
}
void modifier_ko_log_long(){
        char log_actu[DIM]="Simple2";
        char log[DIM]="sssssssssssssssssssssssssssssssssssssssssssssssssss";
        char mdp[DIM]="1205";
        TEST_ASSERT_EQUAL_UINT(0,modifier(fichier,log_actu,log,mdp,DIM));
}
void modifier_ko_mdp_long(){
        char log_actu[DIM]="Simple2";
        char log[DIM]={"Simple3"};
        char mdp[DIM]={"sssssssssssssssssssssssssssssssssssssssssssssssssss"};
        TEST_ASSERT_EQUAL_UINT(0,modifier(fichier,log_actu,log,mdp,DIM));
}
//POUR SUPPRIMER
void supprimer_ok(){
        char log[DIM]="Simple2";
        TEST_ASSERT_EQUAL_UINT(1,supprimer(fichier,log,DIM));
}
void supprimer_ko_log(){
        char log[DIM]="x";
        TEST_ASSERT_EQUAL_UINT(0,supprimer(fichier,log,DIM));
}
void supprimer_ko_log_0(){
        char log[DIM]="0";
        TEST_ASSERT_EQUAL_UINT(0,supprimer(fichier,log,DIM));
}
void supprimer_ko_log_long(){
        char log[DIM]="sssssssssssssssssssssssssssssssssssssssssssssssssss";
        TEST_ASSERT_EQUAL_UINT(0,supprimer(fichier,log,DIM));
}
//TEST
int main(void)
{
    UNITY_BEGIN();
    //Test pour la connexion
    RUN_TEST(connexion_nul);
    RUN_TEST(connexion_simple);
    RUN_TEST(connexion_admin);
    //Test pour verifier l"existence d"un log
    RUN_TEST(log_pris_admin);
    RUN_TEST(log_pris_simple);
    RUN_TEST(log_non_pris);
    //Test pour l"ajout
    RUN_TEST(ajouter_ok_uti);
    RUN_TEST(ajouter_ok_admin);
    RUN_TEST(ajouter_ko_log);
    RUN_TEST(ajouter_ko_uti_0);
    RUN_TEST(ajouter_ko_uti_long);
    RUN_TEST(ajouter_ko_mdp_0);
    RUN_TEST(ajouter_ko_mdp_long);
    //Test pour la modification
    RUN_TEST(modifier_ok_uti);
    RUN_TEST(modifier_ok_admin);
    RUN_TEST(modifier_ko_log_0);
    RUN_TEST(modifier_ko_mdp_0);
    RUN_TEST(modifier_ko_log_long);
    RUN_TEST(modifier_ko_mdp_long);
    RUN_TEST(modifier_ko_log_pris);
    //Test pour la suppression
    RUN_TEST(supprimer_ok);
    RUN_TEST(supprimer_ko_log_0);
    RUN_TEST(supprimer_ko_log);
    RUN_TEST(supprimer_ko_log_long);
    UNITY_END();
    return 0;
}
