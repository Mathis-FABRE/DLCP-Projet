#include "db.h"

#include "vector_api.h"
#include "vector_types.h"
#include "algorithm.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

//     char nom[TAILLE_CHAMP_NOM+1];
//     int code_postal;
//     char telephone[TAILLE_CHAMP_TEL+1];
//     char type[TAILLE_CHAMP_NOM+1];
//     vector menu;
//     float solde;

int ajout_resto(char * nom, int code, char * telephone, char * type, vector * restos)
{
    int id=get_first_id(begin(restos), end(restos));

    Restaurant new;
    new.id = id;
    strcpy(new.nom, nom);
    new.code_postal = code;
    strcpy(new.telephone, telephone);
    strcpy(new.type, type);
    new.menu = make_vector(sizeof(size_t), 0, 2.);
    new.solde = 0.;


    push_back(restos, &new);

    return id;
}