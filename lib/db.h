#pragma once

#include "vector_api.h"
#include "vector_types.h"

#include <stdbool.h>
#include <stdio.h>

#define TAILLE_CHAMP_NOM 36
#define TAILLE_CHAMP_TEL 14

enum specialite_t
{
    RESTAURANT,
    MENU,
    LIVREUR,
    CLIENT,
};

typedef struct restaurant
{
    size_t id; // Clé primaire.
    char nom[TAILLE_CHAMP_NOM];
    int code_postal;
    char telephone[TAILLE_CHAMP_TEL];
    char type[TAILLE_CHAMP_NOM];
    vector menu;
    float solde;
} restaurant;

typedef struct menu
{
    size_t id; // Clé primaire.
    char nom[TAILLE_CHAMP_NOM];
    vector ingredients;
    float prix;
} menu;

typedef struct livreur
{
    size_t id; // Clé primaire.
    char nom[TAILLE_CHAMP_NOM];
    char telephone[TAILLE_CHAMP_TEL];
    vector deplacements; // Liste de code_postal
    size_t restaurant;
    float solde;
} livreur;

typedef struct client
{
    size_t id; // Clé primaire.
    char nom[TAILLE_CHAMP_NOM];
    int code_postal;
    char telephone[TAILLE_CHAMP_TEL];
    float solde;
}

vector lecture_table(
    FILE *fichier);

void ecriture_table(
    FILE *fichier,
    vector const *db);

// Renvoie 'vrai' si le docteur compte 'MEDECINE_GENERALE' parmi ses spécialités.
bool est_generaliste(
    void const *d);
