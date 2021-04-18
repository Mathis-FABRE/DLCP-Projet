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
    }
    fclose(out);

    // tente d'ouvrir le fichier en lecture
    out=fopen("db_livreurs.csv", "r");
    if(!out)
    {
        // s'il n'existe pas
        out=fopen("db_livreurs.csv", "w");
    }
    fclose(out);

    // tente d'ouvrir le fichier en lecture
    out=fopen("db_menus.csv", "r");
    if(!out)
    {
        // s'il n'existe pas
        out=fopen("db_menus.csv", "w");
    }
    fclose(out);

    // tente d'ouvrir le fichier en lecture
    out=fopen("db_restaurants.csv", "r");
    if(!out)
    {
        // s'il n'existe pas
        out=fopen("db_restaurants.csv", "w");
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
    
    switch (v->element_size)
    {
    case sizeof(size_t): ;
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
        break;
    
    case sizeof(int): ;
        int code;

        if(sscanf(chaine, "%d;%s", &code, buffer)==2)
        {
            push_back(v,&code);
            while(sscanf(buffer, "%d;%s", &code, buffer)==2)
            {
                push_back(v,&code);
            }
            sscanf(buffer, "%d", &code);
            push_back(v,&code);
        }

        else
        {
            sscanf(chaine, "%d", &code);
            push_back(v,&code);
        }
        break;

    case 40: ;
        char ingredient[40];

        if(sscanf(chaine, "%39[^;];%s", ingredient, buffer)==2)
        {
            push_back(v,ingredient);
            while(sscanf(buffer, "%39[^;];%s", ingredient, buffer)==2)
            {
                push_back(v,ingredient);
            }
            sscanf(buffer, "%39[^;]", ingredient);
            push_back(v,ingredient);
        }

        else
        {
            sscanf(chaine, "%39[^;]", ingredient);
            push_back(v,ingredient);
        }
        break;
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

vector lecture_livreur()
{
    vector livreurs=make_vector(sizeof(Livreur),0,2.);

    FILE* db_livreur=fopen("db_livreurs.csv", "r");

    Livreur livreur;

    char restos[100];

    while(fscanf(db_livreur, "%zu,%39[^,],%14[^,],%[^,],%zu,%f", &livreur.id, livreur.nom, livreur.telephone, restos, &livreur.restaurant, &livreur.solde)==6)
    {
        livreur.deplacements=make_vector(sizeof(int), 0, 2.);
        separateur_chaine(&livreur.deplacements, restos);
        push_back(&livreurs, &livreur);
    }

    fclose(db_livreur);

    return livreurs;
}

vector lecture_menu()
{
    vector menus=make_vector(sizeof(Menu), 0, 2.);

    FILE* db_menu=fopen("db_menus.csv","r");

    Menu menu;

    char ingredients[136];

    while(fscanf(db_menu, "%zu,%39[^,],%[^,],%f", &menu.id, menu.nom, ingredients, &menu.prix)==4)
    {
        menu.ingredients=make_vector(sizeof(menu.nom), 0, 2.);
        separateur_chaine(&menu.ingredients, ingredients);
        push_back(&menus, &menu);
    }

    fclose(db_menu);

    return menus;
}