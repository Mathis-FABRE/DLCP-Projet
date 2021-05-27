#pragma once

#include "vector_api.h"
#include "vector_types.h"

#include <stdbool.h>
#include <stdio.h>

#define TAILLE_CHAMP_NOM 39
#define TAILLE_CHAMP_TEL 14

typedef enum categorie
{
    RESTAURANT,
    MENU,
    LIVREUR,
    CLIENT,
} CATEGORIE;


typedef struct restaurant
{
    size_t id; // Clé primaire.
    char nom[TAILLE_CHAMP_NOM+1];
    int code_postal;
    char telephone[TAILLE_CHAMP_TEL+1];
    char type[TAILLE_CHAMP_NOM+1];
    vector menu;
    float solde;
} Restaurant;

typedef struct menu
{
    size_t id; // Clé primaire.
    char nom[TAILLE_CHAMP_NOM+1];
    vector ingredients;
    float prix;
} Menu;

typedef struct livreur
{
    size_t id; // Clé primaire.
    char nom[TAILLE_CHAMP_NOM+1];
    char telephone[TAILLE_CHAMP_TEL+1];
    vector deplacements; // Liste de code_postal
    size_t restaurant;
    float solde;
} Livreur;

typedef struct client
{
    size_t id; // Clé primaire.
    char nom[TAILLE_CHAMP_NOM+1];
    int code_postal;
    char telephone[TAILLE_CHAMP_TEL+1];
    float solde;
} Client;

vector lecture_table(
    FILE *fichier);

void ecriture_table(
    FILE *fichier,
    vector const *db);

// Renvoie 'vrai' si le docteur compte 'MEDECINE_GENERALE' parmi ses spécialités.
bool est_generaliste(
    void const *d);

// fonction ajoutant un resto dans le vecteur resto
// le vecteur est supposé trié en entrant et sortant
// si la fonction marche correctement return > 0
// return == id nouvel item
// sinon return < 0
// -1 : nom resto au dessus 39 char
// -2 : tel invalide
// -3 : type invalide
int ajout_resto(char * nom, int code, char * telephone, char * type, vector * restos);

// fonction ajoutant des ingredients dans un menu
// ingredients sous forme
// ingredient1;ingredient2;ingredien3=t3;...
// renvoie 1 si fonction executer correctement
// renvoie 0 si erreur
int ajout_ingredients(char * ingredients, vector * v);

// fonction ajoutant un menu dans le vecteur menu
// le vecteur est supposé trié en entrant et sortant
// si la fonction marche correctement return > 0
// return == id nouvel item
// sinon return < 0
// -1 : nom menu au dessus 39 char
// -2 : ingredients invalides
// -3 : prix < 0
int ajout_menu(char * nom, char * ingredients, float prix, vector * menus);

// fonction ajoutant le menu avec id dans un resto
// si la fonction marche correctement return > 0
// 1 : menu existe et rajouter correctement
// -1 : id menu inexistant
// -2 : menu déjà dans resto
// menu trié en entré et sortie
int add_menu(size_t id, Restaurant * resto, vector const menus);

// supprime un item du menu de l'iterateur
// supposer contenir un Restaurant
// id est l'id de l'item à retirer
// renvoie
// 1 : marche correctement
// 0 : item non présent dans le menu
int del_menu(iterator restaurant, size_t id);

// supprime l'iterateur restaurant de restos
// restaurant contient un Restaurant
// livreurs contient des Livreur
// les references à restaurant dans livreurs
// sont remplacées par 0
void del_resto(vector * restos, iterator restaurant, vector * livreurs);

// ajoute les code postaux dans ajout_livreur
// prend "code1;code2;..." et le vecteur à changer
// renvoie 1 si la fonction marche
// sinon 0
int ajout_code(char * deplacements, vector * v);

// fonction ajoutant un livreur dans le vecteur livreurs
// le vecteur est supposé trié en entrant et sortant
// si la fonction marche correctement return > 0
// return == id nouvel item
// sinon return < 0
// -1 : nom invalide
// -2 : telephone invalide
// -3 : déplacements invalides
// -4 : resto n'existe pas
// -5 : peut se déplacer dans le resto exclusif
int ajout_livreur(char * nom, char * tel, char * deplacement, size_t resto, vector restos, vector * livreurs);

// Fontion ajoutant un client dans le vecteur clients
// le vecteur est supposé trié en entrant et sortant
// si la fonction marche correctement return > 0
// return l'id du nouvel item
// sinon return < 0
// -1 : nom invalide
// -2 : code postal invalide
// -3 : telephone invalide
int ajout_client(char * nom, char* code, char * telephone, float solde, vector * clients);

// fonction supprimant un certain iterateur de livreurs
// considère que l'itérateur est un Livreur
void del_livreur(vector * livreurs, iterator livreur);

// fonction modifiant le restaurant exclusif d'un livreur
// l'itarateur d'un livreur à modifier
// renvoie 1 si marche correctement
// sinon renvoie < 0
// -1 : resto invalide
// -2 : livreur peut pas se déplacer sur resto
int modif_livreur_resto(iterator livreur, size_t resto, vector restos);

// fonction retirant un deplacement possible d'un livreur
// l'itarateur d'un livreur à modifier
// renvoie 1 si marche correctement
// sinon renvoie < 0
// -1 : pos invalide
// -2 : cause conflit avec restaurant exclusif
int modif_livreur_delcode(iterator livreur, size_t pos, vector restos);

// fonction ajoutant un deplacement possible d'un livreur
// l'itarateur d'un livreur à modifier
// renvoie 1 si marche correctement
// sinon renvoie < 0
// -1 : code invalide
// -2 : peut déjà se déplacer là
int modif_livreur_addcode(iterator livreur, int code);

// fonction modifiant le telephone d'un livreur
// l'itarateur d'un livreur à modifier
// renvoie 1 si marche correctement
// sinon renvoie < 0
// -1 : tel invalide
int modif_livreur_tel(iterator livreur, char * tel);

// Fonction qui créé un vector de restaurants
// elle prend en paramètres le code_postal et le type de cuisine 
// si l'utilisateur souhaite filtrer aux restaurants qui le livrent
// ou aux restaurants d'un certain type
vector liste_resto(int code_postal, vector *restos, vector *livreurs, char *type_cuisine, char *nom_restaurant);

// Fonction qui créé un vector de menus
// elle prend en paramètres le code_postal, 
// le type de cuisine un nom de restaurant et un solde
// si l'utilisateur souhaite filtrer aux restaurants qui le livrent
// ou aux restaurants d'un certain type
vector liste_items(int code_postal, vector *restos, vector *livreurs, vector *menus, char *type_cuisine, char *nom_restaurant, float solde);
// fonction supprimant un certain iterateur de clients
// considère que l'itérateur est un Client
void del_client(vector *clients, iterator client);

// fonction modifiant le code postal d'un client
// l'itarateur d'un client à modifier
// renvoie 1 si marche correctement
// sinon renvoie < 0
// -1 : tel invalide
int modif_client_code(iterator client, char * code);

// fonction modifiant le # de tel d'un client
// l'itarateur d'un client à modifier
// renvoie 1 si marche correctement
// sinon renvoie < 0
// -1 : tel invalide
int modif_client_tel(iterator client, char * tel);

// fonction permettant de créditer un solde
// l'itarateur d'un client à modifier
// renvoie 1 si marche correctement
// sinon renvoie < 0
// -1 : ammount invalide
int client_credit_solde(iterator client, float amount);
