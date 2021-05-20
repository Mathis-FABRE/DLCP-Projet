#include "db.h"

#include "vector_api.h"
#include "vector_types.h"
#include "algorithm.h"
#include "functions.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int ajout_resto(char *nom, int code, char *telephone, char *type, vector *restos)
{
    int id = get_first_id(begin(restos), end(restos));

    Restaurant new;
    new.id = id;

    if (isunder39(nom))
        strcpy(new.nom, nom);
    else
        return -1;

    new.code_postal = code;

    if (istel(telephone))
        strcpy(new.telephone, telephone);
    else
        return -2;

    if (isnom(type))
        strcpy(new.type, type);
    else
        return -3;

    new.menu = make_vector(sizeof(size_t), 0, 2.);
    new.solde = 0.;

    push_back(restos, &new);

    sort_by(begin(restos), end(restos), idresto_compare);

    return id;
}

int ajout_ingredients(char *ingredients, vector *v)
{
    char buffer[256];

    char ingredient[40];

    if (sscanf(ingredients, "%39[^;];%[^,]", ingredient, buffer) == 2)
    {
        if (isnom(ingredient))
            push_back(v, ingredient);
        else
            return 0;

        while (sscanf(buffer, "%39[^;];%[^,]", ingredient, buffer) == 2)
        {
            if (isnom(ingredient))
                push_back(v, ingredient);
            else
                return 0;
        }
        sscanf(buffer, "%39[^;]", ingredient);
        if (isnom(ingredient))
            push_back(v, ingredient);
        else
            return 0;
    }

    else if (sscanf(ingredients, "%39[^;]", ingredient) == 1)
    {
        if (isnom(ingredient))
            push_back(v, ingredient);
        else
            return 0;
    }

    else
        return 0;

    return 1;
}

int ajout_menu(char *nom, char *ingredients, float prix, vector *menus)
{
    int id = get_first_id(begin(menus), end(menus));

    Menu new;

    new.id = id;

    if (isunder39(nom))
        strcpy(new.nom, nom);
    else
        return -1;

    new.ingredients = make_vector(40, 0, 2.);
    if (!ajout_ingredients(ingredients, &new.ingredients))
        return -2;

    if (prix >= 0.)
        new.prix = prix;
    else
        return -3;

    push_back(menus, &new);

    sort_by(begin(menus), end(menus), idmenu_compare);

    return id;
}

int add_menu(size_t id, Restaurant *resto, vector const menus)

{
    Menu compare;
    compare.id = id;

    if (binary_search(begin(&menus), end(&menus), &compare, idmenu_compare))
    {
        if (binary_search(begin(&resto->menu), end(&resto->menu), &id, numerical_compare))
            return -2;
        push_back(&resto->menu, &id);
        sort_by(begin(&resto->menu), end(&resto->menu), numerical_compare);
        return 1;
    }

    else
        return -1;
}

int del_menu(iterator restaurant, size_t id)
{
    Restaurant *modif = (Restaurant *)(restaurant.element);

    int search = 0;
    for (iterator b = begin(&modif->menu), e = end(&modif->menu); compare(b, e) && search <= 0; increment(&b, 1))
    {
        search = *(int *)(b.element) - id;
        if (search == 0)
        {
            erase(&modif->menu, b);
            return 1;
        }
    }

    return 0;
}

void del_resto(vector *restos, iterator restaurant, vector *livreurs)
{
    Restaurant *suppr = (Restaurant *)(restaurant.element);
    destroy(&suppr->menu);

    for (iterator b = begin(livreurs), e = end(livreurs); compare(b, e); increment(&b, 1))
    {
        Livreur *test = (Livreur *)(b.element);

        if (suppr->id == test->restaurant)
            modif_livreur_resto(b, 0, *restos);
    }

    erase(restos, restaurant);
}

int ajout_code(char *deplacements, vector *v)
{
    char buffer[256];

    int code;

    if (sscanf(deplacements, "%d;%s", &code, buffer) == 2)
    {
        if (code > 0)
            push_back(v, &code);
        else
            return 0;

        while (sscanf(buffer, "%d;%s", &code, buffer) == 2)
        {
            if (code > 0)
                push_back(v, &code);
            else
                return 0;
        }

        if (sscanf(buffer, "%d", &code) == 1)
        {
            if (code > 0)
                push_back(v, &code);
            else
                return 0;
        }
        else
            return 0;
    }

    else if (sscanf(deplacements, "%d", &code) == 1)
    {
        if (code > 0)
            push_back(v, &code);
        else
            return 0;
    }

    else
        return 0;

    return 1;
}

int ajout_livreur(char *nom, char *tel, char *deplacement, size_t resto, vector restos, vector *livreurs)
{
    int id = get_first_id(begin(livreurs), end(livreurs));

    Livreur new;

    new.id = id;

    if (isnom(nom))
        strcpy(new.nom, nom);
    else
        return -1;

    if (istel(tel))
        strcpy(new.telephone, tel);
    else
        return -2;

    new.deplacements = make_vector(sizeof(int), 0, 2.);
    if (!ajout_code(deplacement, &new.deplacements))
        return -3;

    Restaurant comp1;
    comp1.id = resto;
    int presence = id_search(begin(&restos), end(&restos), &comp1, idresto_compare);
    if (resto == 0 || presence)
        new.restaurant = resto;
    else
        return -4;

    if (resto != 0)
    {
        int test = 0;
        Restaurant const *comp = (Restaurant *)(at(&restos, presence - 1).element);
        for (iterator b = begin(&new.deplacements), e = end(&new.deplacements); compare(b, e) && !test; increment(&b, 1))
        {
            if (*(int *)(b.element) == comp->code_postal)
                test = 1;
        }

        if (!test)
            return -5;
    }

    new.solde = 0.;

    push_back(livreurs, &new);

    sort_by(begin(livreurs), end(livreurs), idlivreur_compare);

    return id;
}

void del_livreur(vector *livreurs, iterator livreur)
{
    Livreur *suppr = (Livreur *)(livreur.element);

    destroy(&suppr->deplacements);

    erase(livreurs, livreur);
}

int ajout_client(char *nom, char *code, char *telephone, float solde, vector *clients)
{
    int id = get_first_id(begin(clients), end(clients));

    Client new;
    new.id = id;

    if (isnom(nom))
        strcpy(new.nom, nom);
    else
        return -1;

    if (iscode(code))
    {
        int int_code;
        sscanf(code, "%d", &int_code);
        new.code_postal = int_code;
    }
    else
        return -2;

    if (istel(telephone))
        strcpy(new.telephone, telephone);
    else
        return -3;

    new.solde = solde;

    push_back(clients, &new);

    sort_by(begin(clients), end(clients), idclient_compare);

    return id;
}

int modif_livreur_resto(iterator livreur, size_t resto, vector restos)
{
    Livreur *modif = (Livreur *)(livreur.element);

    if (resto != 0)
    {
        Restaurant comp;
        comp.id = resto;
        int posresto = id_search(begin(&restos), end(&restos), &comp, idresto_compare);
        if (!posresto)
            return -1;

        int test = 0;
        Restaurant const *compd = (Restaurant *)(at(&restos, posresto - 1).element);
        for (iterator b = begin(&modif->deplacements), e = end(&modif->deplacements); compare(b, e) && !test; increment(&b, 1))
        {
            if (*(int *)(b.element) == compd->code_postal)
                test = 1;
        }

        if (!test)
            return -2;
    }

    modif->restaurant = resto;

    return 1;
}

int modif_livreur_delcode(iterator livreur, size_t pos, vector restos)
{
    Livreur *modif = (Livreur *)(livreur.element);

    int taille = size(modif->deplacements);
    if (pos > taille || pos <= 0)
        return -1;

    if (modif->restaurant != 0)
    {
        int *code = (int *)(at(&modif->deplacements, pos - 1).element);
        Restaurant comp;
        comp.id = modif->restaurant;
        Restaurant *exclu = (Restaurant *)(at(&restos, id_search(begin(&restos), end(&restos), &comp, idresto_compare) - 1).element);
        if (*code == exclu->code_postal)
            return -2;
    }

    erase(&modif->deplacements, at(&modif->deplacements, pos - 1));

    return 1;
}

int modif_livreur_addcode(iterator livreur, int code)
{
    Livreur *modif = (Livreur *)(livreur.element);

    if (code < 9999 || code > 99999)
        return -1;

    for (iterator b = begin(&modif->deplacements), e = end(&modif->deplacements); compare(b, e); increment(&b, 1))
    {
        int *comp = (int *)(b.element);
        if (*comp == code)
            return -2;
    }

    push_back(&modif->deplacements, &code);

    return 1;
}

int modif_livreur_tel(iterator livreur, char *tel)
{
    Livreur *modif = (Livreur *)(livreur.element);

    if (!istel(tel))
        return -1;

    strcpy(modif->telephone, tel);

    return 1;
}

vector liste_resto(int code_postal, vector *restos, vector *livreurs, char *type_cuisine)
{
    vector liste = make_vector(sizeof(Restaurant), 0, 2.);
    vector restaurants = make_vector(sizeof(Restaurant), size(*restos), 2.);
    copy(begin(restos), end(restos), begin(&restaurants));
    

    // Un restau peut livrer le client si son id est dans les livreurs qui ont le code postal du client
    // ou si son code postal est le même que celui du client et d'un livreur "libre"

    if (code_postal)
    {
        for (iterator first = begin(livreurs), end_i = end(livreurs); compare(first, end_i) < 0; increment(&first, 1))
        {

            Livreur *livreur = (Livreur *)(first.element);
            vector codes = livreur->deplacements;

            for (iterator f = begin(&codes), e = end(&codes); compare(f, e) < 0; increment(&f, 1))
            {
                int code = *(int *)(f.element);
                if (code == code_postal)
                {
                    if (livreur->restaurant != 0)
                    {
                        Restaurant *resto = (Restaurant *)at(&restaurants, livreur->restaurant - 1).element;
                        push_back(&liste, resto);
                        // on supprime le restaurant pour ne pas retomber dessus par la suite et accélérer les opérations
                        erase(&restaurants, at(&restaurants, livreur->restaurant - 1));

                        break;
                    }
                    else
                    {
                        for (iterator d = begin(&restaurants), fin = end(&restaurants); compare(d, fin) < 0; increment(&d, 1))
                        {
                            Restaurant *resto = (Restaurant *)d.element;
                            if (resto->code_postal == code_postal)
                            {
                                push_back(&liste, resto);
                                // on supprime le restaurant pour ne pas retomber dessus par la suite et accélérer les opérations
                                erase(&restaurants, at(&restaurants, id_search(begin(&restaurants), end(&restaurants), resto, idresto_compare) - 1));

                                // on décrémente pour ne pas sauter l'élément suivant celui supprimé
                                decrement(&d, 1);

                                // mise à jour de fin
                                fin = end(&restaurants);
                            }
                        }
                    }
                }
            }
        }
    }

    // Restriction à un type de cuisine
    if (type_cuisine)
    {
        if (code_postal)
        {
            for (iterator d = begin(&liste), fin = end(&liste); compare(d, fin) < 0; increment(&d, 1))
            {
                Restaurant *resto = (Restaurant *)(d.element);
                if (strcmp(resto->type, type_cuisine) != 0)
                {
                    
                    erase(&liste, at(&liste, id_search(begin(&liste), end(&liste), resto, idresto_compare) - 1));

                    // on décrémente pour ne pas sauter l'élément suivant celui supprimé
                    decrement(&d, 1);

                    // mise à jour de fin
                    fin = end(&liste);
                }
            }
        }
        else 
        {
            for (iterator d = begin(&restaurants), fin = end(&restaurants); compare(d, fin) < 0; increment(&d, 1))
        {
            Restaurant *resto = (Restaurant *)(d.element);
            if (strcmp(resto->type, type_cuisine) == 0)
            {
                push_back(&liste, resto);
                erase(&restaurants, at(&restaurants, id_search(begin(&restaurants), end(&restaurants), resto, idresto_compare) - 1));

                // on décrémente pour ne pas sauter l'élément suivant celui supprimé
                decrement(&d, 1);

                // mise à jour de fin
                fin = end(&restaurants);
            }
        }
        }
        
    }

    destroy(&restaurants);

    return liste;
}