#include "versions.c"

void main(){
    char name[100] = "celica";
    char *errors = (char *)malloc(1000); // on réserve un emplacement mémoire pour la gestion des erreurs
    char *messages = (char *)malloc(1000);
    strcpy(errors, "\n"); // On initialise le contenu de la liste d'erreurs
    addVersions("1990 T18", name, "0", errors);
    printf("%s", errors);
}