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

vector lecture_client()
{
    vector clients=make_vector(sizeof(Client), 0, 2.);

    FILE* db_clients=fopen("db_clients.csv", "r");

    Client client;

    while (fscanf(db_clients, "%zu,%39[^,],%d,%14[^,],%f", &client.id, client.nom, &client.code_postal, client.telephone, &client.solde)==5)
    {
        push_back(&clients, &client);
    }

    fclose(db_clients);

    return clients;    
}

void separateur_chaine(vector* v, char * chaine)
{
    char buffer[100];
    size_t id;

    if(sscanf(chaine, "%zu;%s", &id, buffer)==2)
    {
        push_back(v,&id);
        while(sscanf(buffer, "%zu;%s", &id, buffer)==2)
        {
            push_back(v,&id);
        }
        sscanf(buffer, "%zu", &id);
        push_back(v,&id);
    }

    else
    {
        sscanf(chaine, "%zu", &id);
        push_back(v,&id);
    }

    return;
}

vector lecture_restaurant()
{
    vector restos=make_vector(sizeof(Restaurant), 0, 2.);

    FILE* db_resto=fopen("db_restaurants.csv", "r");

    Restaurant resto;

    char menus[50];

    while(fscanf(db_resto, "%zu,%39[^,],%d,%14[^,],%39[^,],%[^,],%f", &resto.id, resto.nom, &resto.code_postal, resto.telephone, resto.type, menus, &resto.solde)==7)
    {
        resto.menu=make_vector(sizeof(size_t),0,2.);
        separateur_chaine(&resto.menu, menus);
        push_back(&restos, &resto);
    }

    fclose(db_resto);

    return restos;
}