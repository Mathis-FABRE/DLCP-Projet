#include <stdio.h>
#include "vector.h"

// vérifie l'existence des fichiers nécéssaire à la bd
// les créer si nécessaire
void check();

vector lecture_client();

void separateur_chaine(vector* v, char * chaine);

vector lecture_restaurant();

vector lecture_livreur();

vector lecture_menu();