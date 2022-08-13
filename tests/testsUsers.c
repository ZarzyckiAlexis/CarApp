#include "..\includes\users.h"
#include "..\unity\unity.h"

#define DIM 60

static char login[DIM];
FILE * fichier;

void setup(){

}
//POUR VERIFIER SI LE PSEUDO EXISTE
void log_pris_admin()
{       
        char login[DIM]="Admin";
        fichier=fopen("test.txt","r" );
        TEST_ASSERT_EQUAL_UINT(2,check_existe(login,DIM,fichier));
        fclose(fichier);
}
void log_pris_simple()
{       
        char login[DIM]="Simple";
        fichier=fopen("test.txt","r" );
        TEST_ASSERT_EQUAL_UINT(1,check_existe(login,DIM,fichier));
        fclose(fichier);
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
        fclose(fichier);
}
void ajouter_ko_log(){
        char log[DIM]="Admin";
        char mdp[DIM]="1205";
        fichier=fopen("test.txt","r" );
        TEST_ASSERT_EQUAL_UINT(0,ajouter(fichier,log,mdp,DIM,"=LogAdmin"));
}
void ajouter_ko_uti_0(){
        char log[DIM]="0";
        char mdp[DIM]="1205";
        fichier=fopen("test.txt","r" );
        TEST_ASSERT_EQUAL_UINT(0,ajouter(fichier,log,mdp,DIM,"=LogAdmin"));
        fclose(fichier);
}
void ajouter_ko_mdp_0(){
        char log[DIM]="Admin3";
        char mdp[DIM]="0";
        fichier=fopen("test.txt","r" );
        TEST_ASSERT_EQUAL_UINT(0,ajouter(fichier,log,mdp,DIM,"=LogAdmin"));
        fclose(fichier);
}
void ajouter_ko_uti_long(){
        char log[DIM]="sssssssssssssssssssssssssssssssssssssssssssssssssss";
        char mdp[DIM]="Free";
        fichier=fopen("test.txt","r" );
        TEST_ASSERT_EQUAL_UINT(0,ajouter(fichier,log,mdp,DIM,"=LogAdmin"));
        fclose(fichier);
}
void ajouter_ko_mdp_long(){
        char log[DIM]="Admin3";
        char mdp[DIM]="sssssssssssssssssssssssssssssssssssssssssssssssssss";
        fichier=fopen("test.txt","r" );
        TEST_ASSERT_EQUAL_UINT(0,ajouter(fichier,log,mdp,DIM,"=LogAdmin"));
        fclose(fichier);
}
//POUR MODIFIER
void modifier_ok_admin(){
        char log_actu[DIM]="Admin";
        char log[DIM]="Admin3";
        char mdp[DIM]="Admin3";
        fichier=fopen("test.txt","r" );
        TEST_ASSERT_EQUAL_UINT(1,modifier(fichier,log_actu,log,mdp,DIM));
        fclose(fichier);
}
void modifier_ok_uti(){
        char log_actu[DIM]="Simple";
        char log[DIM]="Simple2";
        char mdp[DIM]="Simple2";
        fichier=fopen("test.txt","r" );
        TEST_ASSERT_EQUAL_UINT(1,modifier(fichier,log_actu,log,mdp,DIM));
        fclose(fichier);
}
void modifier_ko_log_0(){
        char log_actu[DIM]="Simple";
        char log[DIM]="0";
        char mdp[DIM]="1205";
        fichier=fopen("test.txt","r" );
        TEST_ASSERT_EQUAL_UINT(0,modifier(fichier,log_actu,log,mdp,DIM));
        fclose(fichier);
}
void modifier_ko_mdp_0(){
        char log_actu[DIM]="Simple";
        char log[DIM]="Simple2";
        char mdp[DIM]="0";
        fichier=fopen("test.txt","r" );
        TEST_ASSERT_EQUAL_UINT(0,modifier(fichier,log_actu,log,mdp,DIM));
        fclose(fichier);
}
void modifier_ko_log_pris(){
        char log_actu[DIM]="Simple";
        char log[DIM]="Admin";
        char mdp[DIM]="1205";
        fichier=fopen("test.txt","r" );
        TEST_ASSERT_EQUAL_UINT(0,modifier(fichier,log_actu,log,mdp,DIM));
        fclose(fichier);
}
void modifier_ko_log_long(){
        char log_actu[DIM]="Simple";
        char log[DIM]="sssssssssssssssssssssssssssssssssssssssssssssssssss";
        char mdp[DIM]="1205";
        fichier=fopen("test.txt","r" );
        TEST_ASSERT_EQUAL_UINT(0,modifier(fichier,log_actu,log,mdp,DIM));
        fclose(fichier);
}
void modifier_ko_mdp_long(){
        char log_actu[DIM]="Simple";
        char log[DIM]={"Simple3"};
        char mdp[DIM]={"sssssssssssssssssssssssssssssssssssssssssssssssssss"};
        fichier=fopen("test.txt","r" );
        TEST_ASSERT_EQUAL_UINT(0,modifier(fichier,log_actu,log,mdp,DIM));
        fclose(fichier);
}
//POUR SUPPRIMER
void supprimer_ok(){
        char log[DIM]="Simple";
        fichier=fopen("test.txt","r" );
        TEST_ASSERT_EQUAL_UINT(1,supprimer(fichier,log,DIM));
        fclose(fichier);
}
void supprimer_ko_log(){
        char log[DIM]="x";
        fichier=fopen("test.txt","r" );
        TEST_ASSERT_EQUAL_UINT(0,supprimer(fichier,log,DIM));
        fclose(fichier);
}
void supprimer_ko_log_0(){
        char log[DIM]="0";
        fichier=fopen("test.txt","r" );
        TEST_ASSERT_EQUAL_UINT(0,supprimer(fichier,log,DIM));
        fclose(fichier);
}
void supprimer_ko_log_long(){
        char log[DIM]="sssssssssssssssssssssssssssssssssssssssssssssssssss";
        fichier=fopen("test.txt","r" );
        TEST_ASSERT_EQUAL_UINT(0,supprimer(fichier,log,DIM));
        fclose(fichier);
}
//TEST
int main(void)
{
    UNITY_BEGIN();
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
