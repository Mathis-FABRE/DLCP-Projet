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

int ajout_ingredients(char * ingredients, vector * v)
{
    char buffer[256];

    char ingredient[40];

    if(sscanf(ingredients, "%39[^;];%[^,]", ingredient, buffer)==2)
    {
        if(isnom(ingredient))
            push_back(v,ingredient);
        else
            return 0;
        
        while(sscanf(buffer, "%39[^;];%[^,]", ingredient, buffer)==2)
        {
            if(isnom(ingredient))
                push_back(v,ingredient);
            else
                return 0;
        }
        sscanf(buffer, "%39[^;]", ingredient);
        if(isnom(ingredient))
            push_back(v,ingredient);
        else
            return 0;
    }

    else if(sscanf(ingredients, "%39[^;]", ingredient)==1)
    {
        if(isnom(ingredient))
            push_back(v,ingredient);
        else
            return 0;
    }

    else
        return 0;

    return 1;
}

int ajout_menu(char * nom, char * ingredients, float prix, vector * menus)
{
    int id = get_first_id(begin(menus), end(menus));

    Menu new;

    new.id=id;

    if(isunder39(nom))
        strcpy(new.nom, nom);
    else
        return -1;

    new.ingredients=make_vector(40, 0, 2.);
    if(!ajout_ingredients(ingredients, &new.ingredients))
        return -2;

    if(prix>=0.)
        new.prix=prix;
    else
        return -3;

    push_back(menus, &new);

    sort_by(begin(menus), end(menus), idmenu_compare);

    return id;
}

int menu_resto(size_t id, Restaurant * resto, vector const menus)
{
    Menu compare;
    compare.id=id;

    if(binary_search(begin(&menus), end(&menus), &compare, idmenu_compare))
    {
        push_back(&resto->menu, &id);
        return 1;
    }

    else
        return 0;    
}

int ajout_code(char * deplacements, vector * v)
{
    char buffer[256];

    int code;

    if(sscanf(deplacements, "%d;%s", &code, buffer)==2)
    {
        if(code>0)
            push_back(v,&code);
        else
            return 0;
        
        while(sscanf(buffer, "%d;%s", &code, buffer)==2)
        {
            if(code>0)
                push_back(v,&code);
            else
                return 0;
        }

        if(sscanf(buffer, "%d", &code)==1)
        {
            if(code>0)
                push_back(v,&code);
            else
                return 0;
        }
        else
            return 0;
    }

    else if(sscanf(deplacements, "%d", &code)==1)
    {
        if(code>0)
            push_back(v,&code);
        else
            return 0;
    }

    else
        return 0;
    
    return 1;
}

int ajout_livreur(char * nom, char * tel, char * deplacement, size_t resto, vector restos, vector * livreurs)
{
    int id = get_first_id(begin(livreurs), end(livreurs));

    Livreur new;

    new.id = id;

    if(isnom(nom))
        strcpy(new.nom, nom);
    else
        return -1;
    
    if(istel(tel))
        strcpy(new.telephone, tel);
    else
        return -2;

    new.deplacements=make_vector(sizeof(int), 0, 2.);
    if(!ajout_code(deplacement, &new.deplacements))
        return -3;

    Restaurant comp1;
    comp1.id = resto;
    int presence=id_search(begin(&restos), end(&restos), &comp1, idresto_compare);
    if(resto==0 || presence)
        new.restaurant=resto;
    else
        return -4;

    if(resto!=0)
    {
        int test=0;
        Restaurant const* comp=(Restaurant*)(at(&restos, presence-1).element);
        for(iterator b=begin(&new.deplacements), e=end(&new.deplacements); compare(b,e) && !test; increment(&b, 1))
        {
            if(*(int*)(b.element)==comp->code_postal)
                test=1;
        }

        if(!test)
            return -5;
    }

    new.solde=0.;

    push_back(livreurs, &new);

    sort_by(begin(livreurs), end(livreurs), idlivreur_compare);

    return id;
}

int modif_livreur_resto(iterator livreur, size_t resto, vector restos)
{
    Livreur * modif=(Livreur*)(livreur.element);

    if(resto!=0)
    {
        Restaurant comp;
        comp.id=resto;
        int posresto=id_search(begin(&restos), end(&restos), &comp, idresto_compare);
        if(!posresto)
            return -1;

        int test=0;
            Restaurant const* compd=(Restaurant*)(at(&restos, posresto-1).element);
            for(iterator b=begin(&modif->deplacements), e=end(&modif->deplacements); compare(b,e) && !test; increment(&b, 1))
            {
                if(*(int*)(b.element)==compd->code_postal)
                    test=1;
            }

            if(!test)
                return -2;
    }

    modif->restaurant=resto;
    
    return 1;
}