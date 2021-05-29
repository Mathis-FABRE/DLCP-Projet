#pragma once

#include <stdbool.h>

// Présume que 'data' contient un 'int'.
// Renvoie 'vrai' is la valeur est paire, sinon 'faux'.
bool is_even(
    void const* data);

// Présume que 'data' contient un 'int'.
// Renvoie 'vrai' is la valeur est impaire, sinon 'faux'.
bool is_odd(
    void const* data);

// Présume que 'data' contient un 'int'.
// Renvoie 'vrai' si la valeur est inférieure à 5, sinon 'faux'.
bool less_than_five(
    void const* data);

// Présume que 'data' contient une chaîne de caractères terminée par '\0'.
// Renvoie 'vrai' si 'data' ne contient que des voyelles minuscules ou majuscules.
bool only_vowels(
    void const* data);

// Présume que 'data' contient un 'bool'.
// Modifie la valeur de 'data' pour son contraire.
void negate(
    void* data);

// Présume que 'data' contient une chaîne de caractères terminée par '\0'.
// Modifie la chaîne donnée avec les minuscules changées pour des majuscules et 
// les majuscules changées pour des minuscules.
void flip_case(
    void* data);

// Renvoie le nombre renvoyé lors d'un précédent appel à 'counter' incrémenté de 1.
// Le premier appel de 'counter' renvoie '1'.
void* counter();

// Présume que 'a' et 'b' contiennent des 'int'.
// Renvoie un nombre négatif si 'a' précède 'b' dans l'ordre numérique.
// Renvoie un nombre positif si 'b' précède 'a' dans l'ordre numérique.
// Renvoie zéro si 'a' et 'b' sont égaux.
int numerical_compare(
    void const* a,
    void const* b);

// Présume que 'a' et 'b' contiennent des chaînes de caractères terminée par '\0'.
// Renvoie un nombre négatif si 'a' précède 'b' dans l'ordre lexicographique.
// Renvoie un nombre positif si 'b' précède 'a' dans l'ordre lexicographique.
// Renvoie zéro si 'a' et 'b' sont identiques.
// P. ex. : 'compare("banane", "bananeraie")' -> négatif.
int lexicographical_compare(
    void const* a,
    void const* b);

// Présume que 'a' et 'b' contiennent des 'Restaurant'.
// Renvoie un nombre négatif si id de 'a' précède id de 'b' dans l'ordre numérique.
// Renvoie un nombre positif si id de 'b' précède id de 'a' dans l'ordre numérique.
// Renvoie zéro si id de 'a' et id de 'b' sont égaux.
int idresto_compare(
    void const* a,
    void const* b);

// Présume que a contient un Restaurant et b une chaine
// Renvoie un nombre négatif si nom de 'a' précède nom de 'b' dans l'ordre numérique.
// Renvoie un nombre positif si nom de 'b' précède nom de 'a' dans l'ordre numérique.
// Renvoie zéro si nom de 'a' et nom de 'b' sont égaux.
int nameresto(
    void const* data,
    void const* name);

// Présume que 'a' et 'b' contiennent des 'Menu'.
// Renvoie un nombre négatif si id de 'a' précède id de 'b' dans l'ordre numérique.
// Renvoie un nombre positif si id de 'b' précède id de 'a' dans l'ordre numérique.
// Renvoie zéro si id de 'a' et id de 'b' sont égaux.
int idmenu_compare(
    void const* a,
    void const* b);

// Présume que 'a' et 'b' contiennent des 'Livreur'.
// Renvoie un nombre négatif si id de 'a' précède id de 'b' dans l'ordre numérique.
// Renvoie un nombre positif si id de 'b' précède id de 'a' dans l'ordre numérique.
// Renvoie zéro si id de 'a' et id de 'b' sont égaux.
int idlivreur_compare(
    void const* a,
    void const* b);

// Présume que a contient un Livreur et b une chaine
// Renvoie un nombre négatif si nom de 'a' précède nom de 'b' dans l'ordre numérique.
// Renvoie un nombre positif si nom de 'b' précède nom de 'a' dans l'ordre numérique.
// Renvoie zéro si nom de 'a' et nom de 'b' sont égaux.
int namelivreur(
    void const* data,
    void const* name);

// Présume que 'a' et 'b' contiennent des 'Client'.
// Renvoie un nombre négatif si id de 'a' précède id de 'b' dans l'ordre numérique.
// Renvoie un nombre positif si id de 'b' précède id de 'a' dans l'ordre numérique.
// Renvoie zéro si id de 'a' et id de 'b' sont égaux.
int idclient_compare(
    void const* a,
    void const* b);

// Présume que a contient un Client et b une chaine
// Renvoie un nombre négatif si nom de 'a' précède nom de 'b' dans l'ordre numérique.
// Renvoie un nombre positif si nom de 'b' précède nom de 'a' dans l'ordre numérique.
// Renvoie zéro si nom de 'a' et nom de 'b' sont égaux.
int nameclient(
    void const* data,
    void const* name);

// regarde si une chaine de caractères
// est en dessous de 39 caractères
// si oui retourne 1
// si non retourne 0
int isunder39(char * string);

// vérifie si l'élément de l'iterator possède un certain id
// renvoie 1 si vrai
// 0 sinon
int equals_id(void const* test, void const *id);

// regarde si une chaine de caractères
// est un téléphone
// si oui retourne 1
// si non retourne 0
int istel(char * string);

// regarde si une chaine de caractères
// est un nom
// si oui retourne 1
// si non retourne 0
int isnom(char * string);

// regarde la chaine passée
// est un code et contient 5 chiffres exactement
// si oui retourne 1
// si non retourne 0
int iscode(char* code);