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

    if(isunder39(nom))
        strcpy(new.nom, nom);
    else
        return -1;
    
    new.code_postal = code;

    if(istel(telephone))
        strcpy(new.telephone, telephone);
    else
        return -2;
    
    if(isnom(type))
        strcpy(new.type, type);
    else
        return -3;    

    new.menu = make_vector(sizeof(size_t), 0, 2.);
    new.solde = 0.;

    push_back(restos, &new);

    sort_by(begin(restos), end(restos), idresto_compare);

    return id;
}