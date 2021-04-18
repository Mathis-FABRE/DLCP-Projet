#include <stdio.h>
#include "vector.h"

// vérifie l'existence des fichiers nécéssaire à la bd
// les créer si nécessaire
void check();

// fonction lisant le fichier db_clients.csv
// met les données dans un vecteur
vector lecture_client();

// prend une chaine de caractères "%s;%s;..."
// sépare la chaine en morceau
// stock les donnée dans le vecteur v
void separateur_chaine(vector* v, char * chaine);

// fonction lisant le fichier db_restaunts.csv
// met les données dans un vecteur
vector lecture_restaurant();

// fonction lisant le fichier db_livreurs.csv
// met les données dans un vecteu
vector lecture_livreur();

// fonction lisant le fichier db_menus.csv
// met les données dans un vecteu
vector lecture_menu();