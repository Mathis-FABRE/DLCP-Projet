#pragma once

#include "vector_api.h"
#include "vector_types.h"

#include <stdbool.h>
#include <stdio.h>

#define TAILLE_CHAMP_NOM 36

// Peut être combiné. P. ex. 0xA = DERMATOLOGIE + MEDECINE_GENERALE.
enum specialite_t
{
    CARDIOLOGIE         = 0x1,
    DERMATOLOGIE        = 0x2,
    ENDOCRINOLOGIE      = 0x4,
    MEDECINE_GENERALE   = 0x8,
    OPHTALMOLOGIE       = 0x10,
    PEDIATRIE           = 0x20,
};

typedef struct docteur
{
    size_t index;   // Clé primaire.
    char nom[TAILLE_CHAMP_NOM];
    int specialites;
    size_t index_hopital;   // Clé secondaire.
} docteur;

vector lecture_table(
    FILE* fichier);

void ecriture_table(
    FILE* fichier,
    vector const* db);

// Renvoie 'vrai' si le docteur compte 'MEDECINE_GENERALE' parmi ses spécialités.
bool est_generaliste(
    void const* d);
