#include "db.h"

#include "vector_api.h"
#include "vector_types.h"
#include "algorithm.h"
#include "functions.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

int ajout_resto(char *nom, char *code, char *telephone, char *type, vector *restos)
{
    int id = get_first_id(begin(restos), end(restos));

    Restaurant new;
    new.id = id;

    if (isunder39(nom))
        strcpy(new.nom, nom);
    else
        return -1;

    if (istel(telephone))
        strcpy(new.telephone, telephone);
    else
        return -2;

    if (isnom(type))
        strcpy(new.type, type);
    else
        return -3;

    if (iscode(code))
        strcpy(new.code_postal, code);
    else
        return -4;

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
        {
            if (binary_search(begin(v), end(v), ingredient, lexicographical_compare))
                return 0;
            push_back(v, ingredient);
        }
        else
            return 0;

        while (sscanf(buffer, "%39[^;];%[^,]", ingredient, buffer) == 2)
        {
            if (isnom(ingredient))
            {
                if (binary_search(begin(v), end(v), ingredient, lexicographical_compare))
                    return 0;
                push_back(v, ingredient);
            }
            else
                return 0;
        }
        sscanf(buffer, "%39[^;]", ingredient);
        if (isnom(ingredient))
        {
            if (binary_search(begin(v), end(v), ingredient, lexicographical_compare))
                return 0;
            push_back(v, ingredient);
        }
        else
            return 0;
    }

    else if (sscanf(ingredients, "%39[^;]", ingredient) == 1)
    {
        if (isnom(ingredient))
        {
            if (binary_search(begin(v), end(v), ingredient, lexicographical_compare))
                return 0;
            push_back(v, ingredient);
        }
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

    char code[6];

    if (sscanf(deplacements, "%6[^;];%s", code, buffer) == 2)
    {
        if (iscode(code))
        {
            if (binary_search(begin(v), end(v), code, lexicographical_compare))
                return 0;
            push_back(v, code);
        }
        else
            return 0;

        while (sscanf(buffer, "%6[^;];%s", code, buffer) == 2)
        {
            if (iscode(code))
            {
                if (binary_search(begin(v), end(v), code, lexicographical_compare))
                    return 0;
                push_back(v, code);
            }
            else
                return 0;
        }

        if (sscanf(buffer, "%6[^;]", code) == 1)
        {
            if (iscode(code))
            {
                if (binary_search(begin(v), end(v), code, lexicographical_compare))
                    return 0;
                push_back(v, code);
            }
            else
                return 0;
        }
        else
            return 0;
    }

    else if (sscanf(deplacements, "%6[^;]", code) == 1)
    {
        if (iscode(code))
        {
            if (binary_search(begin(v), end(v), code, lexicographical_compare))
                return 0;
            push_back(v, code);
        }
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

    new.deplacements = make_vector(6, 0, 2.);
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
        Restaurant const *comp = (Restaurant *)(at(&restos, presence - 1).element);
        if (!binary_search(begin(&new.deplacements), end(&new.deplacements), &comp->code_postal, lexicographical_compare))
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
        strcpy(new.code_postal, code);
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

        Restaurant const *compd = (Restaurant *)(at(&restos, posresto - 1).element);
        if (!binary_search(begin(&modif->deplacements), end(&modif->deplacements), &compd->code_postal, lexicographical_compare))
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
        char *code = (char *)(at(&modif->deplacements, pos - 1).element);
        Restaurant comp;
        comp.id = modif->restaurant;
        Restaurant *exclu = (Restaurant *)(at(&restos, id_search(begin(&restos), end(&restos), &comp, idresto_compare) - 1).element);
        if (strcmp(code, exclu->code_postal) == 0)
            return -2;
    }

    erase(&modif->deplacements, at(&modif->deplacements, pos - 1));

    return 1;
}

int modif_livreur_addcode(iterator livreur, char *code)
{
    Livreur *modif = (Livreur *)(livreur.element);

    if (!iscode(code))
        return -1;

    if (binary_search(begin(&modif->deplacements), end(&modif->deplacements), code, lexicographical_compare))
        return -2;

    push_back(&modif->deplacements, code);

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

vector liste_resto(char *code_postal, vector *restos, vector *livreurs, char *type_cuisine, char *nom_restaurant)
{
    vector liste = make_vector(sizeof(Restaurant), 0, 2.);
    vector restaurants = make_vector(sizeof(Restaurant), size(*restos), 2.);
    copy(begin(restos), end(restos), begin(&restaurants));

    // Un restau peut livrer le client si son id est dans les livreurs qui ont le code postal du client
    // ou si son code postal est le même que celui du client et d'un livreur "libre"

    if ((code_postal && strlen(code_postal) > 2))
    {
        for (iterator first = begin(livreurs), end_i = end(livreurs); compare(first, end_i) < 0; increment(&first, 1))
        {

            Livreur *livreur = (Livreur *)(first.element);
            

            for (iterator f = begin(&livreur->deplacements), e = end(&livreur->deplacements); compare(f, e) < 0; increment(&f, 1))
            {
                char *code = (char *)(f.element);
                if (strcmp(code, code_postal) == 0)
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
                            for (iterator f_i = begin(&livreur->deplacements), e_i = end(&livreur->deplacements); compare(f_i, e_i) < 0; increment(&f_i, 1))
                            {
                                char *code_l = (char *)(f_i.element);
                                if (strcmp(resto->code_postal, code_l) == 0)
                                {
                                    push_back(&liste, resto);
                                    // on supprime le restaurant pour ne pas retomber dessus par la suite et accélérer les opérations
                                    erase(&restaurants, at(&restaurants, id_search(begin(&restaurants), end(&restaurants), resto, idresto_compare) - 1));

                                    // on décrémente pour ne pas sauter l'élément suivant celui supprimé
                                    decrement(&d, 1);

                                    // mise à jour de fin
                                    fin = end(&restaurants);
                                    break;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    // Restriction à un type de cuisine
    if (type_cuisine && strlen(type_cuisine) > 2)
    {
        if ((code_postal && strlen(code_postal) > 2))
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
    if (nom_restaurant && strlen(nom_restaurant) > 1)
    {
        if ((code_postal && strlen(code_postal) > 2) || (type_cuisine && strlen(type_cuisine) > 2))
        {
            for (iterator d = begin(&liste), fin = end(&liste); compare(d, fin) < 0; increment(&d, 1))
            {
                Restaurant *resto = (Restaurant *)(d.element);
                if (strcmp(resto->nom, nom_restaurant) != 0)
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
                if (strcmp(resto->nom, nom_restaurant) == 0)
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
    if ((!code_postal || strlen(code_postal) <= 2) && (!type_cuisine || strlen(type_cuisine) <= 2) && (!nom_restaurant || strlen(nom_restaurant) <= 2))
    {
        return restaurants;
    }

    destroy(&restaurants);

    return liste;
}

vector liste_items(char *code_postal, vector *restos, vector *livreurs, vector *liste_menus, char *type_cuisine, char *nom_restaurant, float solde)
{
    // items à traiter
    vector menus = make_vector(sizeof(Menu), size(*liste_menus), 2.);
    copy(begin(liste_menus), end(liste_menus), begin(&menus));

    // liste d'items à renvoyer
    vector liste_items = make_vector(sizeof(Menu), 0, 2.);

    // recup les items à partir de la liste de restos

    // enlever les items trop chers

    vector new_liste = liste_resto(code_postal, restos, livreurs, type_cuisine, nom_restaurant);
    for (iterator d = begin(&new_liste), fin = end(&new_liste); compare(d, fin) < 0; increment(&d, 1))
    {
        Restaurant *resto = (Restaurant *)(d.element);

        for (iterator first = begin(&resto->menu), end_i = end(&resto->menu); compare(first, end_i) < 0; increment(&first, 1))
        {
            size_t id = *(size_t *)(first.element);
            Menu search;
            search.id = id;
            int it_id = id_search(begin(&menus), end(&menus), &search, idmenu_compare);
            if (it_id)
            {
                Menu *menu = (Menu *)(at(&menus, it_id - 1).element);
                float prix = menu->prix;
                if (prix <= solde || solde < 0)
                {

                    // chercher l'item dans la liste de tous les items
                    if (id_search(begin(liste_menus), end(liste_menus), menu, idmenu_compare))
                    {
                        // ajouter l'item au vect des items à renvoyer
                        push_back(&liste_items, menu);
                        // retirer l'item du vect de tous les items
                        erase(&menus, at(&menus, id_search(begin(&menus), end(&menus), menu, idmenu_compare) - 1));
                    }
                }
            }
        }
    }

    destroy(&new_liste);
    destroy(&menus);

    return liste_items;
}

vector liste_items_bis(vector *liste_menus, vector *liste, float solde)
{
    // liste d'items à renvoyer
    vector liste_items = make_vector(sizeof(Menu), 0, 2.);

    // items à traiter
    vector menus = make_vector(sizeof(Menu), size(*liste_menus), 2.);
    copy(begin(liste_menus), end(liste_menus), begin(&menus));

    for (iterator d = begin(liste), fin = end(liste); compare(d, fin) < 0; increment(&d, 1))
    {
        Restaurant *resto = (Restaurant *)(d.element);

        for (iterator first = begin(&resto->menu), end_i = end(&resto->menu); compare(first, end_i) < 0; increment(&first, 1))
        {
            size_t id = *(size_t *)(first.element);
            Menu search;
            search.id = id;
            int it_id = id_search(begin(&menus), end(&menus), &search, idmenu_compare);
            if (it_id)
            {
                Menu *menu = (Menu *)(at(&menus, it_id - 1).element);
                float prix = menu->prix;
                if (prix <= solde || solde < 0)
                {

                    // chercher l'item dans la liste de tous les items
                    if (id_search(begin(liste_menus), end(liste_menus), menu, idmenu_compare))
                    {
                        // ajouter l'item au vect des items à renvoyer
                        push_back(&liste_items, menu);
                        // retirer l'item du vect de tous les items
                        erase(&menus, at(&menus, id_search(begin(&menus), end(&menus), menu, idmenu_compare) - 1));
                    }
                }
            }
        }
    }
    destroy(liste);

    destroy(&menus);

    return liste_items;
}

void del_client(vector *clients, iterator client)
{
    erase(clients, client);
}

int modif_client_code(iterator client, char *code)
{
    Client *modif = (Client *)(client.element);

    if (!iscode(code))
        return -1;

    strcpy(modif->code_postal, code);

    return 1;
}

int modif_client_tel(iterator client, char *tel)
{
    Client *modif = (Client *)(client.element);

    if (!istel(tel))
        return -1;

    strcpy(modif->telephone, tel);

    return 1;
}

int client_credit_solde(iterator client, float amount)
{
    Client *modif = (Client *)(client.element);

    if (amount <= 0)
        return -1;

    modif->solde += amount;

    return 1;
}

float commande(vector *commande, vector *restos, vector *livreurs, char *code_client, char *nom_resto, vector *restaurants, vector *paiements, vector *liv)
{

    float prix_commande = 0;

    for (iterator start = begin(commande), end_i = end(commande); compare(start, end_i) < 0; increment(&start, 1))
    {
        Menu *item = (Menu *)(start.element);
        // size_t id = item->id;
        int found = 0;
        for (iterator d = begin(restaurants), fin = end(restaurants); compare(d, fin) < 0 && !found; increment(&d, 1))
        {
            Restaurant *resto = (Restaurant *)(d.element);
            if (nom_resto && strlen(nom_resto) > 2)
            {
                if (binary_search(begin(&resto->menu), end(&resto->menu), &item->id, equals_id) && strcmp(resto->nom, nom_resto) == 0)
                {
                    // le resto propose l'item
                    int where = id_search(begin(restaurants), end(restaurants), resto, idresto_compare);
                    if (where)
                    {
                        float *paiement = (float *)at(paiements, where - 1).element;
                        *paiement = *paiement + item->prix;
                        found = 1;
                    }
                    else
                    {
                        push_back(restaurants, resto);
                        push_back(paiements, &(item->prix));
                        found = 1;
                    }

                    prix_commande += item->prix;
                    break;
                }
            }
            else
            {
                if (binary_search(begin(&resto->menu), end(&resto->menu), &item->id, equals_id))
                {
                    // le resto propose l'item
                    int where = id_search(begin(restaurants), end(restaurants), resto, idresto_compare);
                    if (where)
                    {
                        float *paiement = (float *)at(paiements, where - 1).element;
                        *paiement = *paiement + item->prix;
                        found = 1;
                    }
                    else
                    {
                        push_back(restaurants, resto);
                        push_back(paiements, &(item->prix));
                        found = 1;
                    }

                    prix_commande += item->prix;
                    break;
                }
            }
        }
        if (!found)
        {
            for (iterator d = begin(restos), fin = end(restos); compare(d, fin) < 0 && !found; increment(&d, 1))
            {
                Restaurant *resto = (Restaurant *)(d.element);
                if (nom_resto && strlen(nom_resto) > 2)
                {
                    if (binary_search(begin(&resto->menu), end(&resto->menu), &item->id, equals_id) && strcmp(resto->nom, nom_resto) == 0)
                    {
                        // le resto propose l'item
                        int where = id_search(begin(restaurants), end(restaurants), resto, idresto_compare);
                        if (where)
                        {
                            float *paiement = (float *)at(paiements, where - 1).element;
                            *paiement = *paiement + item->prix;
                            // found = 1;
                        }
                        else
                        {
                            push_back(restaurants, resto);
                            push_back(paiements, &(item->prix));
                            // found = 1;
                        }

                        prix_commande += item->prix;
                        break;
                    }
                }
                else
                {
                    if (binary_search(begin(&resto->menu), end(&resto->menu), &item->id, equals_id))
                    {
                        // le resto propose l'item
                        int where = id_search(begin(restaurants), end(restaurants), resto, idresto_compare);
                        if (where)
                        {
                            float *paiement = (float *)at(paiements, where - 1).element;
                            *paiement = *paiement + item->prix;
                            // found = 1;
                        }
                        else
                        {
                            push_back(restaurants, resto);
                            push_back(paiements, &(item->prix));
                            // found = 1;
                        }

                        prix_commande += item->prix;
                        break;
                    }
                }
            }
        }
    }
    // trouver les livreurs
    for (iterator start = begin(restaurants), end_i = end(restaurants); compare(start, end_i) < 0; increment(&start, 1))
    {
        Restaurant *resto = (Restaurant *)(start.element);
        int found = 0;

        for (iterator d = begin(liv), fin = end(liv); compare(d, fin) < 0; increment(&d, 1))
        {
            int liv_ok = 0;
            Livreur *livreur = (Livreur *)(d.element);
            if (livreur->restaurant == resto->id)
            {
                push_back(liv, livreur);
                liv_ok = 1;
                break;
            }
            else
            {
                int cclient = 0, cresto = 0;
                for (iterator first = begin(&livreur->deplacements), e = end(&livreur->deplacements); compare(first, e) < 0; increment(&first, 1))
                {
                    char *code = (char *)(first.element);
                    if (strcmp(code, resto->code_postal) == 0)
                        cresto = 1;
                    if (code_client)
                    {
                        if (strcmp(code, code_client) == 0)
                            cclient = 1;
                    }

                    if (((code_client && cclient && cresto) || cresto) && id_search(begin(liv), end(liv), livreur, idlivreur_compare) == 0)
                    {
                        push_back(liv, livreur);
                        prix_commande += 2;
                        found = 1;
                        liv_ok = 1;
                        break;
                    }
                }
                if (liv_ok)
                    break;
            }
        }

        if (!found)
        {
            for (iterator d = begin(livreurs), fin = end(livreurs); compare(d, fin) < 0; increment(&d, 1))
            {
                Livreur *livreur = (Livreur *)(d.element);
                int liv_ok = 0;
                if (livreur->restaurant == resto->id)
                {
                    push_back(liv, livreur);
                    liv_ok = 1;
                    break;
                }
                else
                {
                    int cclient = 0, cresto = 0;
                    for (iterator first = begin(&livreur->deplacements), e = end(&livreur->deplacements); compare(first, e) < 0; increment(&first, 1))
                    {
                        char *code = (char *)(first.element);
                        if (strcmp(code, resto->code_postal) == 0)
                            cresto = 1;
                        if (code_client)
                        {
                            if (strcmp(code, code_client) == 0)
                                cclient = 1;
                        }

                        if (((code_client && cclient && cresto) || cresto) && id_search(begin(liv), end(liv), livreur, idlivreur_compare) == 0)
                        {
                            push_back(liv, livreur);
                            prix_commande += 2;
                            liv_ok = 1;
                            break;
                        }
                    }
                }
                if (liv_ok)
                    break;
            }
        }
    }

    return prix_commande;
}

int add_commande(vector *liste, vector *commande, size_t id)
{
    if (id <= 0 || id > size(*liste))
    {
        return -1;
    }
    else
    {
        Menu *item = (Menu *)(at(liste, id - 1).element);
        push_back(commande, item);
    }

    return 1;
}

int del_commande(vector *commande, size_t id)
{
    if (id <= 0 || id > size(*commande))
    {
        return -1;
    }
    else
    {
        erase(commande, at(commande, id - 1));
    }

    return 1;
}

int make_payment(iterator client, vector *restos, vector *livreurs, vector *restaurants, vector *paiements, vector *livs, float total)
{
    Client *cl = (Client *)(client.element);
    if (cl->solde >= total)
        cl->solde -= total;
    else
        return -1;

    iterator f_payment = begin(paiements);
    for (iterator f = begin(restaurants), e = end(restaurants); compare(f, e) < 0; increment(&f, 1))
    {
        Restaurant *resto = (Restaurant *)(at(restos, id_search(begin(restos), end(restos), (f.element), idresto_compare) - 1).element);
        float paiement = *(float *)(f_payment.element);
        resto->solde += paiement;
        increment(&f_payment, 1);
    }

    for (iterator f = begin(livs), e = end(livs); compare(f, e) < 0; increment(&f, 1))
    {
        Livreur *liv = (Livreur *)(at(livreurs, id_search(begin(livreurs), end(livreurs), (f.element), idlivreur_compare) - 1).element);
        liv->solde += 2;
    }

    return 1;
}