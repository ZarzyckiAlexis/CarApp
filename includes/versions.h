// Gestion des dépendances
#include "global.h"

// Gestion des headers

// Fonction qui permet la vérification de l'existence de la table version 
// [ 1 = EXISTE ; 0 = N'EXISTE PAS ]
int existTableVersions();

// Fonction qui permet la création de la table version 
// [ -1 = EXISTE DÉJÀ ; 1 = REUSSI ; 0 = RATÉ CRÉATION TABLE ; 2 = RATÉ AJOUT DONNÉES ]
int createTableVersions();

// Fonction qui permet de vérifier si la table est vide
// [ -1 = TABLE EXISTE PAS ; 0 = PAS VIDE ; 1 = VIDE ]
int isTableEmptyVersions();

// Fonction qui permet de garnir un tableau des données présente dans la base de données
void getVersions(char versions[][100], int *count);