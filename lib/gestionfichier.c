#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vector.h"
#include "db.h"

void check(int choix)
{
    FILE* out;

    if(choix==0)
    {
        // tente d'ouvrir le fichier en lecture
        out=fopen("db_clients.csv", "r");
        if(!out)
        {
            // s'il n'existe pas
            out=fopen("db_clients.csv", "w");
            fprintf(out, "id,nom,code postal,telephone,solde\n");
        }
        fclose(out);

        // tente d'ouvrir le fichier en lecture
        out=fopen("db_livreurs.csv", "r");
        if(!out)
        {
            // s'il n'existe pas
            out=fopen("db_livreurs.csv", "w");
            fprintf(out, "id,nom,telephone,deplacements,restaurant,solde\n");
        }
        fclose(out);

        // tente d'ouvrir le fichier en lecture
        out=fopen("db_menus.csv", "r");
        if(!out)
        {
            // s'il n'existe pas
            out=fopen("db_menus.csv", "w");
            fprintf(out, "id,nom,ingredients,prix\n");
        }
        fclose(out);

        // tente d'ouvrir le fichier en lecture
        out=fopen("db_restaurants.csv", "r");
        if(!out)
        {
            // s'il n'existe pas
            out=fopen("db_restaurants.csv", "w");
            fprintf(out, "id,nom,code postal,telephone,type,menu,solde\n");
        }
        fclose(out);
    }

    else
    {
        // tente d'ouvrir le fichier en lecture
        out=fopen("test/db_clients.csv", "r");
        if(!out)
        {
            // s'il n'existe pas
            out=fopen("test/db_clients.csv", "w");
            fprintf(out, "id,nom,code postal,telephone,solde\n");
        }
        fclose(out);

        // tente d'ouvrir le fichier en lecture
        out=fopen("test/db_livreurs.csv", "r");
        if(!out)
        {
            // s'il n'existe pas
            out=fopen("test/db_livreurs.csv", "w");
            fprintf(out, "id,nom,telephone,deplacements,restaurant,solde\n");
        }
        fclose(out);

        // tente d'ouvrir le fichier en lecture
        out=fopen("test/db_menus.csv", "r");
        if(!out)
        {
            // s'il n'existe pas
            out=fopen("test/db_menus.csv", "w");
            fprintf(out, "id,nom,ingredients,prix\n");
        }
        fclose(out);

        // tente d'ouvrir le fichier en lecture
        out=fopen("test/db_restaurants.csv", "r");
        if(!out)
        {
            // s'il n'existe pas
            out=fopen("test/db_restaurants.csv", "w");
            fprintf(out, "id,nom,code postal,telephone,type,menu,solde\n");
        }
        fclose(out);
    }
}

vector lecture_client(const char * file)
{
    vector clients=make_vector(sizeof(Client), 0, 2.);

    FILE* db_clients=fopen(file, "r");

    // ignore première ligne
    char ignore[100];
    fgets(ignore,100,db_clients);

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

        if(sscanf(chaine, "%39[^;];%[^,]", ingredient, buffer)==2)
        {
            push_back(v,ingredient);
            while(sscanf(buffer, "%39[^;];%[^,]", ingredient, buffer)==2)
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

vector lecture_restaurant(const char * file)
{
    vector restos=make_vector(sizeof(Restaurant), 0, 2.);

    FILE* db_resto=fopen(file, "r");

    // ignore première ligne
    char ignore[100];
    fgets(ignore,100,db_resto);

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

vector lecture_livreur(const char * file)
{
    vector livreurs=make_vector(sizeof(Livreur),0,2.);

    FILE* db_livreur=fopen(file, "r");

    // ignore première ligne
    char ignore[100];
    fgets(ignore,100,db_livreur);

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

vector lecture_menu(const char * file)
{
    vector menus=make_vector(sizeof(Menu), 0, 2.);

    FILE* db_menu=fopen(file,"r");

    // ignore première ligne
    char ignore[100];
    fgets(ignore,100,db_menu);

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

void sauvegarde_clients(iterator first, iterator last)
{
    FILE* db_client=fopen("db_clients.csv", "w");

    fprintf(db_client, "id,nom,code postal,telephone,solde\n");

    for(iterator b=first, e=last; compare(b,e)!=0; increment(&b,1))
    {
        Client * client=(Client*)(b.element);
        fprintf(db_client, "%zu,%s,%d,%14s,%.0f\n", client->id, client->nom, client->code_postal, client->telephone, client->solde);
    }

    fclose(db_client);

    return;
}

void sauvegarde_liste(FILE* file, iterator first, iterator last)
{
    if(first.element_size==sizeof(size_t))
    {
        iterator e=last;
        decrement(&e,1);
        for(iterator b=first; compare(b,e)!=0; increment(&b,1))
        {
            size_t * id=(size_t*)(b.element);
            fprintf(file, "%zu;", *id);
        }
        size_t * id=(size_t*)(e.element);
        fprintf(file, "%zu", *id);
    }

    else if(first.element_size==sizeof(int))
    {
        iterator e=last;
        decrement(&e,1);
        for(iterator b=first; compare(b,e)!=0; increment(&b,1))
        {
            int * id=(int*)(b.element);
            fprintf(file, "%d;", *id);
        }
        int * id=(int*)(e.element);
        fprintf(file, "%d", *id);
    }

    else
    {
        iterator e=last;
        decrement(&e,1);
        for(iterator b=first; compare(b,e)!=0; increment(&b,1))
        {
            char * nom=(char*)(b.element);
            fprintf(file, "%s;", nom);
        }
        char * nom=(char*)(e.element);
        fprintf(file, "%s", nom);
    }
}

void sauvegarde_resto(iterator first, iterator last)
{
    FILE* db_resto=fopen("db_restaurants.csv", "w");

    fprintf(db_resto, "id,nom,code postal,telephone,type,menu,solde\n");

    for(iterator b=first, e=last; compare(b,e)!=0; increment(&b,1))
    {
        Restaurant * resto=(Restaurant*)(b.element);
        fprintf(db_resto, "%zu,%s,%d,%14s,%s,", resto->id, resto->nom, resto->code_postal, resto->telephone, resto->type);
        sauvegarde_liste(db_resto, begin(&resto->menu), end(&resto->menu));
        fprintf(db_resto, ",%.0f\n", resto->solde);
    }

    fclose(db_resto);

    return;
}

void sauvegarde_livreurs(iterator first, iterator last)
{
    FILE* db_livreur=fopen("db_livreurs.csv", "w");

    fprintf(db_livreur, "id,nom,telephone,deplacements,restaurant,solde\n");

    for(iterator b=first, e=last; compare(b,e)!=0; increment(&b,1))
    {
        Livreur * livreur=(Livreur*)(b.element);
        fprintf(db_livreur, "%zu,%s,%14s,", livreur->id, livreur->nom, livreur->telephone);
        sauvegarde_liste(db_livreur, begin(&livreur->deplacements), end(&livreur->deplacements));
        fprintf(db_livreur, ",%zu,%.0f\n", livreur->restaurant, livreur->solde);
    }

    fclose(db_livreur);

    return;
}

void sauvegarde_menus(iterator first, iterator last)
{
    FILE* db_menu=fopen("db_menus.csv", "w");

    fprintf(db_menu, "id,nom,ingredients,prix\n");

    for(iterator b=first, e=last; compare(b,e)!=0; increment(&b,1))
    {
        Menu * menu=(Menu*)(b.element);
        fprintf(db_menu, "%zu,%s,", menu->id, menu->nom);
        sauvegarde_liste(db_menu, begin(&menu->ingredients), end(&menu->ingredients));
        fprintf(db_menu, ",%0.f\n", menu->prix);
    }

    fclose(db_menu);

    return;
}