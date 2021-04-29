#include "db.h"

#include "vector_api.h"
#include "vector_types.h"
#include "algorithm.h"
#include "functions.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

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

    sort_by(begin(restos), end(restos), idresto_compare);

    return id;
}