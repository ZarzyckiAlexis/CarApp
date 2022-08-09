/*
Auteur : Noah Verly
But :   Fichier contenant tout les #includes,#define
        et déclaration des fonctions
*/

// INCLUDE
#include <locale.h>  //Ceci permet de changer l'encodage
#include <stdio.h>   //Ouput,input/ tout les fonction par rapport aux fichiers
#include <stdlib.h>  //exit
#include <conio.h>   //clrscr
#include <string.h>  // Pour les chaines de carat�eres
#include <windows.h> // Sleep

// DEFINE
#define DIM 60
#define NAME_FICHIER "users.txt"
#define LIBRE_VIDE 0 
#define SIMPLE 1
#define ADMIN 2

/*FOCNTION*/
// fonction pour lister les utilisateur
void lister_uti();
// fonction pour l'ajout
void menu_ajouter(char *rang);
unsigned ajouter(FILE *fichier,char *log, char *mdp, int dim, char *rang);
// fonction pour la suppression
unsigned menu_supprimer();
unsigned supprimer(FILE *fichier, char *log, int dim);
// fonction commune
unsigned check_existe(char *log, int dim, FILE *fichier);
void chiffrement(char *log, char *mdp, int dim);