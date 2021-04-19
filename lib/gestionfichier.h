#include <stdio.h>
#include "vector.h"

// vérifie l'existence des fichiers nécéssaire à la bd
// les créer si nécessaire
void check();

// fonction lisant le fichier file
// met les données dans un vecteur
vector lecture_client(const char * file);

// prend une chaine de caractères "%s;%s;..."
// sépare la chaine en morceau
// stock les donnée dans le vecteur v
void separateur_chaine(vector* v, char * chaine);

// fonction lisant le fichier file
// met les données dans un vecteur
vector lecture_restaurant(const char * file);

// fonction lisant le fichier file
// met les données dans un vecteu
vector lecture_livreur(const char * file);

// fonction lisant le fichier file
// met les données dans un vecteu
vector lecture_menu(const char * file);