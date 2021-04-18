#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "db.h"

void check()
{
    FILE* out;

    // tente d'ouvrir le fichier en lecture
    out=fopen("db_clients.csv", "r");
    if(!out)
    {
        // s'il n'existe pas
        out=fopen("db_clients.csv", "w");
        fprintf(out, "%s", "id,nom,code postal,telephone,solde\n");
    }
    fclose(out);

    // tente d'ouvrir le fichier en lecture
    out=fopen("db_livreurs.csv", "r");
    if(!out)
    {
        // s'il n'existe pas
        out=fopen("db_livreurs.csv", "w");
        fprintf(out, "%s", "id,nom,telephone,deplacements,restaurant,solde\n");
    }
    fclose(out);

    // tente d'ouvrir le fichier en lecture
    out=fopen("db_menus.csv", "r");
    if(!out)
    {
        // s'il n'existe pas
        out=fopen("db_menus.csv", "w");
        fprintf(out, "%s", "id,nom,ingredients,prix\n");
    }
    fclose(out);

    // tente d'ouvrir le fichier en lecture
    out=fopen("db_restaurants.csv", "r");
    if(!out)
    {
        // s'il n'existe pas
        out=fopen("db_restaurants.csv", "w");
        fprintf(out, "%s", "id,nom,code postal,telephone,type,menu,solde\n");
    }
    fclose(out);
}

void lecture_client(vector * clients)
{
    FILE* db_clients=fopen("db_clients.csv", "r");

    Client client;

    while (fscanf(db_clients, "%zu,%36[^,],%d,%14[^,],%f", &client.id, client.nom, &client.code_postal, client.telephone, &client.solde)==5)
    {
        push_back(clients, &client);
    }

    fclose(db_clients);

    return;    
}