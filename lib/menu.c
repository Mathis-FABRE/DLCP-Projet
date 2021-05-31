#include "menu.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_INPUT 50

void menu_header()
{
    system("clear");
    printf("#######################################\n");
    printf("         Kiki's Delivery Sevice        \n");
    printf("#######################################\n");
    printf("\n");
}

int menu_connexion()
{
    menu_header();

    printf("#######################################\n");
    printf("               Connexion               \n");
    printf("#######################################\n");
    printf("\n");

    printf("Vous voulez ?\n");
    printf("1/ vous connecter\n");
    printf("2/ creer un nouveau compte\n");
    printf("\n");
    printf("Votre choix (r pour retour): ");


    char str[NB_INPUT];

    char choice;
    do
    {
        scanf(" %50[^\n]", str);
        choice = str[0];
        if (choice != '1' && choice != '2' && choice != 'r')
            printf("Choix invalide veuillez réessayer: ");
    } while (choice != '1' && choice != '2' && choice != 'r');

    switch (choice)
    {
    case '1':
        return 1;
        break;

    case '2':
        return 2;
        break;

    case 'r':
        return 0;
        break;
    }

    return 0;
}

void creer_client(vector *clients, vector *restos, vector *menus, vector *livreurs)
{
    menu_header();

    printf("#######################################\n");
    printf("            Création Client            \n");
    printf("#######################################\n");
    printf("\n");
    printf("Entrez votre nom: ");
    char *name = malloc(40);
    scanf(" %39[^\n]", name);

    printf("Entrez votre telephone (XX XX XX XX XX): ");
    char *tel = malloc(15);
    scanf(" %14[^\n]", tel);

    printf("Entrez votre code postal: ");
    char *code = malloc(6);
    scanf(" %s", code);

    printf("Entrez la solde de base: ");
    float solde;

    do
    {
        scanf(" %f", &solde);
        if (solde < 0)
        {
            printf("Solde impossible réessayer: ");
        }
    } while (solde < 0);

    int test;
    do
    {
        test = ajout_client(name, code, tel, solde, clients);
        if (test < 0)
        {
            printf("Erreur : ");
            if (test == -1)
            {
                printf("nom invalide\n");
                printf("Veuillez réessayer (nom): ");
                scanf(" %39[^\n]", name);
            }
            else if (test == -2)
            {
                printf("code postale invalide\n");
                printf("Veuillez réessayer (code postal): ");
                scanf(" %s", code);
            }
            else if (test == -3)
            {
                printf("téléphone invalide\n");
                printf("Veuillez réessayer (téléphone): ");
                scanf(" %14[^\n]", tel);
            }
        }
    } while (test < 0);

    free(name);
    free(tel);
    free(code);

    printf("votre id est %d\n\n", test);
    printf("Entrez n'importe quoi pour continuer: ");
    char c;
    scanf(" %c", &c);

    Client comp;
    comp.id = test;
    menu_client(at(clients, id_search(begin(clients), end(clients), &comp, idclient_compare) - 1), clients, restos, menus, livreurs);
}

void connexion_client(vector *clients, vector *restos, vector *menus, vector *livreurs)
{
    menu_header();

    printf("#######################################\n");
    printf("            Connexion Client           \n");
    printf("#######################################\n");
    printf("\n");
    printf("Entrer votre id (<= 0 si vous ne le connaissez pas): ");
    int id;
    int search;
    do
    {
        scanf(" %d", &id);
        if (id > 0)
        {
            Client comp;
            comp.id = id;
            search = id_search(begin(clients), end(clients), &comp, idclient_compare);
            if (search)
                menu_client(at(clients, search - 1), clients, restos, menus, livreurs);
            else
                printf("id n'existe pas veuillez réessayer: ");
        }
    } while (id > 0 && !search);

    if (id <= 0)
    {
        printf("Entrer votre nom: ");
        char *name = malloc(40);
        scanf(" %40[^\n]", name);
        vector select = select_name(begin(clients), end(clients), name, nameclient);

        free(name);
        if (size(select) == 1)
            menu_client(at(clients, id_search(begin(clients), end(clients), at(&select, 0).element, idclient_compare) - 1), clients, restos, menus, livreurs);

        else if (size(select) == 0)
        {
            printf("Erreur : nom non présent dans db");

            printf("Entrez n'importe quoi pour retourner: ");
            char choice;
            scanf(" %c", &choice);
        }
        else
        {
            printf("\n");
            for (iterator b = begin(&select), e = end(&select); compare(b, e) != 0; increment(&b, 1))
            {
                Client *client = (Client *)(b.element);
                printf("%zu,%s,%s,%14s,%.2f\n", client->id, client->nom, client->code_postal, client->telephone, client->solde);
            }

            printf("Entrer votre id (<= 0 pour retour): ");
            do
            {
                scanf(" %d", &id);
                if (id > 0)
                {
                    Client comp;
                    comp.id = id;
                    search = id_search(begin(clients), end(clients), &comp, idclient_compare);
                    if (search)
                        menu_client(at(clients, search - 1), clients, restos, menus, livreurs);
                    else
                        printf("id n'existe pas veuillez réessayer: ");
                }
            } while (id > 0 && !search);
        }
    }
}

void menu_client(iterator client, vector *clients, vector *restos, vector *menus, vector *livreurs)
{
    char choice;
    do
    {
        menu_header();

        printf("#######################################\n");
        printf("              Menu Client              \n");
        printf("#######################################\n");
        printf("\n");

        printf("info :\n");
        Client *compte = (Client *)client.element;
        printf("id: %ld\n", compte->id);
        printf("nom: %s\n", compte->nom);
        printf("code postal: %s\n", compte->code_postal);
        printf("numéro de téléphone: %s\n", compte->telephone);

        printf("\n");

        printf("Vous voulez ?\n");
        printf("1/ Consulter votre solde\n");
        printf("2/ Modifier votre profil\n");
        printf("3/ Voir la liste des restaurants\n");
        printf("4/ Passer une commande\n");
        printf("5/ Supprimer compte\n");
        printf("\n");
        printf("Votre choix (r pour retour): ");


        char str[NB_INPUT];
        int res;

        do
        {
            scanf(" %50[^\n]", str);
            choice = str[0];
            if (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != 'r')
                printf("Choix invalide veuillez réessayer: ");
        } while (choice != '1' && choice != '2' && choice != '3' && choice != '4' && choice != '5' && choice != 'r');

        switch (choice)
        {
        case '1':
            menu_client_solde(client);
            break;

        case '2':
            menu_modifier_client(client, restos, menus, livreurs);
            break;

        case '3':
            menu_afficher_restos(client, clients, restos, menus, livreurs);
            break;

        case '4':
            menu_commande(client, restos, livreurs, menus, NULL);
            break;

        case '5':
            res = menu_supprimer_client(client, clients);
            if (res == 1)
                choice = 'r';
            break;

        case 'r':
            break;
        }

    } while (choice != 'r');
}

void menu_client_solde(iterator client)
{
    menu_header();

    printf("#######################################\n");
    printf("              Solde Client             \n");
    printf("#######################################\n");
    printf("\n");
    printf("Votre Solde : %.2f€", ((Client *)client.element)->solde);
    printf("\n");
    printf("Voulez vous créditer votre solde ?\n");
    printf("(y pour oui, n pour non)\n");


    char str[NB_INPUT];
    char choice;

    do
    {
        scanf(" %50[^\n]", str);
        choice = str[0];
        if (choice != 'y' && choice != 'n')
            printf("réponse invalide veuillez réessayer: ");
    } while (choice != 'y' && choice != 'n');


    switch(choice)
    {
    case 'y':
        menu_credit_client(client);
        break;

    case 'n':
        break;
    }
}

void menu_credit_client(iterator client)
{
    menu_header();

    printf("#######################################\n");
    printf("            Creditage Client           \n");
    printf("#######################################\n");
    printf("\n");
    printf("Entrez la somme que vous souhaitez\n");
    printf("créditer a votre solde: ");
    float choice;
    do
    {
        scanf(" %f", &choice);
        if (choice < 0)
            printf("somme invalide veuillez réessayer: ");
    } while (choice < 0);

    client_credit_solde(client, choice);
}

void menu_modifier_client(iterator client, vector *restos, vector *menus, vector *livreurs)
{
    char choice;

    menu_header();

    printf("#######################################\n");
    printf("          Modification Client          \n");
    printf("#######################################\n");
    printf("\n");
    printf("Vous voulez modifier ?\n");
    printf("1/ Code postal\n");
    printf("2/ Téléphone\n");
    printf("\n");
    printf("Votre choix (q pour quitter, r pour retour): ");

    char str[NB_INPUT];

    do
    {
        scanf(" %50[^\n]", str);
        choice = str[0];
        if (choice != '1' && choice != '2' && choice != 'q' && choice != 'r')
            printf("Choix invalide veuillez réessayer: ");
    } while (choice != '1' && choice != '2' && choice != 'q' && choice != 'r');

    switch (choice)
    {
    case '1':
        menu_modif_client_code(client);
        break;

    case '2':
        menu_modif_client_tel(client);
        break;

    case 'r':
        break;

    default:
        break;
    }
}

int menu_modif_client_code(iterator client)
{
    menu_header();

    printf("#######################################\n");
    printf("    Modification code postal client    \n");
    printf("#######################################\n");
    printf("\n");
    printf("Votre code postal actuel est %s\n", ((Client *)(client.element))->code_postal);
    printf("\n");
    printf("Entrez votre nouveau code postal (r pour retour):\n");

    char str[6];
    char choice;
    do
    {
        scanf(" %50[^\n]", str);
        choice = str[0];
        if (choice != 'r' && modif_client_code(client, str) != 1)
            printf("Choix invalide, veuillez réessayer: ");
    } while (choice != 'r' && modif_client_code(client, str) != 1);

    return 1;
}

int menu_modif_client_tel(iterator client)
{
    menu_header();

    printf("###############################################\n");
    printf("    Modification numéro de téléphone client    \n");
    printf("###############################################\n");
    printf("\n");
    printf("Votre numéro de téléphone actuel est : %s\n", ((Client *)(client.element))->telephone);
    printf("\n");
    printf("Entrez votre nouveau numéro de téléphone (r pour retour):\n");

    char str[15];
    char choice;
    do
    {
        scanf(" %15[^\n]", str);
        choice = str[0];
        if (choice != 'r' && modif_client_tel(client, str) != 1)
            printf("Choix invalide, veuillez réessayer: ");
    } while (choice != 'r' && modif_client_tel(client, str) != 1);

    return 1;
}

int menu_afficher_restos(iterator client, vector *clients, vector *restos, vector *menus, vector *livreurs)
{
    menu_header();

    printf("#######################################\n");
    printf("       Affichage des restaurants       \n");
    printf("#######################################\n");
    printf("\n");

    printf("Voulez-vous limiter la recherche :\n");
    char str[NB_INPUT];
    printf("Aux restaurants pouvant vous livrer ? (y pour oui, n pour non) : ");
    char choice;
    do
    {
        scanf(" %40[^\n]", str);
        choice = str[0];
        if (choice != 'y' && choice != 'n')
            printf("Choix invalide, veuillez réessayer: ");
    } while (choice != 'y' && choice != 'n');
    char type[TAILLE_CHAMP_NOM + 1];
    printf("A un type de cuisine ? (n pour non) : ");

    scanf(" %40[^\n]", type);

    char code[6];
    if (choice == 'n')
        code[0] = 0;
    else
    {
        Client *cl = (Client *)(client.element);
        strcpy(code, cl->code_postal);
    }

    vector liste = liste_resto(code, restos, livreurs, type, NULL);

    affichage_restos(client, restos, livreurs, menus, &liste);

    return 1;
}

int affichage_restos(iterator client, vector *restos, vector *livreurs, vector *menus, vector *liste)
{

    menu_header();

    printf("#######################################\n");
    printf("       Affichage des restaurants       \n");
    printf("#######################################\n");
    printf("\n");

    printf("ID | Nom | Code Postal | Téléphone : Menu, Type de restaurant\n");
    printf("-------------------------------------------------------------\n");
    printf("\n");

    int id = 1;
    for (iterator f = begin(liste), e = end(liste); compare(f, e) < 0; increment(&f, 1))
    {
        Restaurant *resto = (Restaurant *)(f.element);
        printf("%d | %s | %s | %s : ", id++, resto->nom, resto->code_postal, resto->telephone);
        if (size(resto->menu) == 0)
            printf("(pas de menu), ");
        for (iterator first = begin(&resto->menu), last = end(&resto->menu); compare(first, last) < 0; increment(&first, 1))
        {
            size_t id = *(size_t *)(first.element);
            Menu *menu = (Menu *)at(menus, id - 1).element;
            printf("%s, ", menu->nom);
        }
        printf("%s\n", resto->type);
    }

    char str[NB_INPUT];
    printf("\n");
    printf("Nombre de résultats : %ld\n", size(*liste));
    printf("\n");

    if (size(*liste) > 0)
    {
        printf("Souahitez-vous faire une commande à partir de cette liste ? (y / n) : ");
        char choice;
        do
        {
            scanf(" %40[^\n]", str);
            choice = str[0];
            if (choice != 'y' && choice != 'n')
                printf("Choix invalide, veuillez réessayer1: ");
        } while (choice != 'y' && choice != 'n');

        switch (choice)
        {
        case 'y':
            menu_commande(client, restos, livreurs, menus, liste);
            break;

        default:
            break;
        }
    }
    else
    {
        printf("Appuyez sur une touche pour continuer : ");
        scanf(" %10[^\n]", str);
    }

    return 1;
}

int menu_commande(iterator client, vector *restos, vector *livreurs, vector *menus, vector *liste)
{
    menu_header();

    printf("#######################################\n");
    printf("              Menu commande            \n");
    printf("#######################################\n");
    printf("\n");
    printf("\n");

    char code[6];

    float solde = -1;
    char choice_code, choice_solde;
    Client *cl = (Client *)(client.element);
    char str[10], str_type[TAILLE_CHAMP_NOM + 1], nom[TAILLE_CHAMP_NOM + 1];
    printf("Souhaitez-vous limiter la liste des menus\n");
    if (!liste)
    {
        //  À qui peut me livrer

        printf("A qui peut vous livrer ? (y pour oui, n pour non) : ");
        do
        {
            scanf(" %40[^\n]", str);
            choice_code = str[0];
            if (choice_code != 'y' && choice_code != 'n')
                printf("Choix invalide, veuillez réessayer: ");
        } while (choice_code != 'y' && choice_code != 'n');
        if (choice_code == 'y')
        {
            strcpy(code, cl->code_postal);
        }
        if (choice_code == 'n')
            code = NULL;
        //  À un type de cuisine

        printf("A un type de cuisine particulier ? (n pour non) : ");
        scanf(" %40[^\n]", str_type);
        //  À un seul restaurant

        printf("A un seul restaurant ? (n pour non) : ");
        scanf(" %40[^\n]", nom);
    }
    else
    {
        nom[0] = 0;
    }

    //  Aux items moins chers que mon solde disponible
    printf("Aux menus dont le prix est inferieur à votre solde ? (y pour oui, n pour non) : ");
    do
    {
        scanf(" %40[^\n]", str);
        choice_solde = str[0];
        if (choice_solde != 'y' && choice_solde != 'n')
            printf("Choix invalide, veuillez réessayer: ");
    } while (choice_solde != 'y' && choice_solde != 'n');
    if (choice_solde == 'y')
    {
        solde = cl->solde;
    }

    vector items;
    if (liste)
        items = liste_items_bis(menus, liste, solde);
    else
    {
        vector new_liste = liste_resto(code, restos, livreurs, str_type, nom);
        items = liste_items_bis(menus, &new_liste, solde);
    }

    free(code);

    menu_afficher_items(&items, client, restos, livreurs, menus, nom);

    return 1;
}

int menu_afficher_items(vector *liste, iterator client, vector *restos, vector *livreurs, vector *menus, char *nom)
{
    menu_header();

    printf("#######################################\n");
    printf("         Affichage des menus         \n");
    printf("#######################################\n");
    printf("\n");

    int id = 1;
    printf("ID | Nom | Ingredients | Prix\n");
    printf("-----------------------------\n");
    printf("\n");

    for (iterator f = begin(liste), e = end(liste); compare(f, e) < 0; increment(&f, 1))
    {
        Menu *menu = (Menu *)(f.element);
        printf("%d | %s | ", id++, menu->nom);
        if (size(menu->ingredients) == 0)
            printf("(pas de d'ingredients), ");
        for (iterator first = begin(&menu->ingredients), last = end(&menu->ingredients); compare(first, last) < 0; increment(&first, 1))
        {
            char *ingredient = (char *)(first.element);
            printf("%s, ", ingredient);
        }
        printf("%.2f €\n", menu->prix);
    }

    char str[NB_INPUT];
    printf("\n");
    printf("Nombre de résultats : %ld\n", size(*liste));
    char choice;
    char choice_item;
    if (size(*liste) > 0)
    {
        printf("\n");
        printf("Souahitez-vous\n");
        printf("1/ Continuer avec tous ces menus\n");
        printf("2/ Ajouter seulement certains menus (un à un)\n");
        printf("Entrez une option : ");
        do
        {
            scanf(" %10[^\n]", str);
            choice = str[0];
            if (choice != '1' && choice != '2')
                printf("Choix invalide, veuillez réessayer: ");
        } while (choice != '1' && choice != '2');
        switch (choice)
        {
        case '1':;
            menu_recap_commande(client, liste, restos, livreurs, nom);
            break;
        case '2':;

            vector new_liste = make_vector(sizeof(Menu), 0, 2.);
            do
            {
                printf("Entrez l'id du menu à ajouter à votre commande (s pour aller à la commande) : ");
                size_t id;
                do
                {

                    scanf(" %10[^\n]", str);
                    choice_item = str[0];
                    sscanf(str, " %zu\n", &id);
                    if (choice_item != 's' && (id <= 0 || id > size(*liste)))
                        printf("Choix invalide, veuillez réessayer : ");
                } while (choice_item != 's' && (id <= 0 || id > size(*liste)));
                if (choice_item == 's')
                    menu_recap_commande(client, &new_liste, restos, livreurs, nom);
                else
                {
                    Menu *item = (Menu *)(at(liste, id - 1).element);
                    push_back(&new_liste, item);
                }
            } while (choice_item != 's');
            break;

        default:
            break;
        }
    }
    else
    {
        printf("Aucun résultat\n");
        printf("Appuyez sur une touche pour continuer : ");
        scanf(" %10[^\n]", str);
    }

    return 1;
}

int menu_recap_commande(iterator client, vector *liste, vector *restos, vector *livreurs, char *nom_resto)
{
    menu_header();

    printf("#######################################\n");
    printf("      Récapitulatif de la commande     \n");
    printf("#######################################\n");
    printf("\n");

    int id = 1;
    printf("ID | Nom | Ingredients | Prix\n");
    printf("-----------------------------\n");
    printf("\n");

    for (iterator f = begin(liste), e = end(liste); compare(f, e) < 0; increment(&f, 1))
    {
        Menu *menu = (Menu *)(f.element);
        printf("%d | %s | ", id++, menu->nom);
        if (size(menu->ingredients) == 0)
            printf("(pas de d'ingredients), ");
        for (iterator first = begin(&menu->ingredients), last = end(&menu->ingredients); compare(first, last) < 0; increment(&first, 1))
        {
            char *ingredient = (char *)(first.element);
            printf("%s, ", ingredient);
        }
        printf("%.2f €\n", menu->prix);
    }

    // restaurants à payer
    vector restaurants = make_vector(sizeof(Restaurant), 0, 2.);
    vector paiements = make_vector(sizeof(float), 0, 2.);
    vector liv = make_vector(sizeof(Livreur), 0, 2.);

    Client *cl = (Client *)(client.element);

    char str[NB_INPUT];
    printf("\n");
    float total = commande(liste, restos, livreurs, cl->code_postal, nom_resto, &restaurants, &paiements, &liv);
    printf("Prix total : %.2f €\n", total);
    char choice;
    printf("\n");
    printf("Souhaitez-vous :\n");
    printf("1/ Confirmer la commande\n");
    printf("2/ Retirer un menu de la commande\n");
    printf("3/ Annuler la commande\n");
    printf("\n");
    printf("Entrez votre choix (r pour retour) : ");
    do
    {
        scanf(" %50[^\n]", str);
        choice = str[0];
        if (choice != '1' && choice != '2' && choice != '3' && choice != 'r')
            printf("Choix invalide veuillez réessayer: ");
    } while (choice != '1' && choice != '2' && choice != '3' && choice != 'r');

    int test = -1;
    switch (choice)
    {
    case '1':;
        test = make_payment(client, restos, livreurs, &restaurants, &paiements, &liv, total);

        if (test != 1)
        {
            printf("Le paiement n'a pas pu être réalisé car vous n'avez pas assez d'argent\n");

            printf("\n");
            do
            {
                size_t id;
                printf("Entrez l'id du menu à supprimer : ");
                scanf(" %zu\n", &id);
                test = del_commande(liste, id);
                if (test == -1)
                    printf("Choix invalide, veuillez réessayer : ");
            } while (test == -1);

            destroy(&restaurants);
            destroy(&paiements);
            destroy(&liv);

            menu_recap_commande(client, liste, restos, livreurs, nom_resto);
        }
        break;

    case '2':;
        printf("\n");

        do
        {
            size_t id;
            printf("Entrez l'id du menu à supprimer : ");
            scanf(" %zu", &id);
            test = del_commande(liste, id);
            if (test == -1)
                printf("Choix invalide, veuillez réessayer : ");
        } while (test == -1);

        destroy(&restaurants);
        destroy(&paiements);
        destroy(&liv);

        menu_recap_commande(client, liste, restos, livreurs, nom_resto);

    default:
        destroy(&restaurants);
        destroy(&paiements);
        destroy(&liv);
        break;
    }

    return 1;
}

int menu_supprimer_client(iterator client, vector *clients)
{
    menu_header();

    printf("#######################################\n");
    printf("           Suppression Compte          \n");
    printf("#######################################\n");
    printf("\n");
    printf("Etes vous sûr de vouloir supprimer votre compte ? ");
    printf("(y pour oui, n pour non)\n");

    char str[NB_INPUT];
    char choice;
    do
    {
        scanf(" %50[^\n]", str);
        choice = str[0];
        if (choice != 'y' && choice != 'n')
            printf("réponse invalide veuillez réessayer: ");
    } while (choice != 'y' && choice != 'n');

    switch(choice)
    {
    case 'y':
        del_client(clients, client);
        return 1;
        break;

    case 'n':
        return 0;
        break;
    }

    return 0;
}

void creer_resto(vector *restos, vector *menus, vector *livreurs)
{
    menu_header();

    printf("#######################################\n");
    printf("          Création Restaurant          \n");
    printf("#######################################\n");
    printf("\n");
    printf("Entrez votre nom: ");
    char *name = malloc(40);
    scanf(" %39[^\n]", name);

    printf("Entrez votre telephone (XX XX XX XX XX): ");
    char *tel = malloc(15);
    scanf(" %14[^\n]", tel);

    printf("Entrez votre code postal: ");
    char code[10];
    scanf(" %10[^\n]", code);

    printf("Entrez le type de votre restaurant: ");
    char *type = malloc(40);
    scanf(" %39[^\n]", type);

    int test;
    do
    {
        test = ajout_resto(name, code, tel, type, restos);
        if (test < 0)
        {
            printf("Erreur : ");
            if (test == -1)
            {
                printf("nom invalide\n");
                printf("Veuillez réessayer (nom): ");
                scanf(" %39[^\n]", name);
            }
            else if (test == -2)
            {
                printf("téléphone invalide\n");
                printf("Veuillez réessayer (téléphone): ");
                scanf(" %14[^\n]", tel);
            }
            else if (test == -3)
            {
                printf("type invalide\n");
                printf("Veuillez réessayer (type): ");
                scanf(" %14[^\n]", tel);
            }
            else if(test == -3)
            {
                printf("code postal invalide\n");
                printf("Veuillez réessayer (code): ");
                scanf(" %10[^\n]", code);
            }
        }
    } while (test < 0);

    free(name);
    free(tel);
    free(type);

    printf("votre id est %d\n\n", test);
    printf("Entrez n'importe quoi pour continuer: ");
    char c;
    scanf(" %c", &c);

    Restaurant comp;
    comp.id = test;
    menu_resto(at(restos, id_search(begin(restos), end(restos), &comp, idresto_compare) - 1), restos, menus, livreurs);
}

void connexion_resto(vector *restos, vector *menus, vector *livreurs)
{
    menu_header();

    printf("#######################################\n");
    printf("          Connexion Restaurant         \n");
    printf("#######################################\n");
    printf("\n");
    printf("Entrer votre id (<= 0 si vous ne le connaissez pas): ");
    int id;
    int search;
    do
    {
        scanf(" %d", &id);
        if (id > 0)
        {
            Restaurant comp;
            comp.id = id;
            search = id_search(begin(restos), end(restos), &comp, idresto_compare);
            if (search)
                menu_resto(at(restos, search - 1), restos, menus, livreurs);
            else
                printf("id n'existe pas veuillez réessayer: ");
        }
    } while (id > 0 && !search);

    if (id <= 0)
    {
        printf("Entrer votre nom: ");
        char *name = malloc(40);
        scanf(" %40[^\n]", name);
        vector select = select_name(begin(restos), end(restos), name, nameresto);

        free(name);
        if (size(select) == 1)
            menu_resto(at(restos, id_search(begin(restos), end(restos), at(&select, 0).element, idresto_compare) - 1), restos, menus, livreurs);

        else if (size(select) == 0)
        {
            printf("Erreur : nom non présent dans db");

            printf("Entrez n'importe quoi pour retourner: ");
            char choice;
            scanf(" %c", &choice);
        }
        else
        {
            printf("\n");
            for (iterator b = begin(&select), e = end(&select); compare(b, e) != 0; increment(&b, 1))
            {

                Restaurant *resto = (Restaurant *)(b.element);
                printf("%zu,%s,%s,%14s,%s,", resto->id, resto->nom, resto->code_postal, resto->telephone, resto->type);
              
                affiche_liste(begin(&resto->menu), end(&resto->menu));
                printf(",%.2f\n", resto->solde);
            }

            printf("Entrer votre id (<= 0 pour retour): ");
            do
            {
                scanf(" %d", &id);
                if (id > 0)
                {
                    Client comp;
                    comp.id = id;
                    search = id_search(begin(restos), end(restos), &comp, idresto_compare);
                    if (search)
                        menu_resto(at(restos, search - 1), restos, menus, livreurs);
                    else
                        printf("id n'existe pas veuillez réessayer: ");
                }
            } while (id > 0 && !search);
        }
    }
}

void menu_resto(iterator resto, vector *restos, vector *menus, vector *livreurs)
{
    char choice;
    do
    {
        menu_header();

        printf("#######################################\n");
        printf("            Menu Restaurant            \n");
        printf("#######################################\n");
        printf("\n");

        printf("info :\n");
        Restaurant *compte = (Restaurant *)resto.element;
        printf("id: %ld\n", compte->id);
        printf("nom: %s\n", compte->nom);
        printf("code postal: %s\n", compte->code_postal);
        printf("telephone: %s\n", compte->telephone);
        printf("menu: ");
        affiche_liste(begin(&compte->menu), end(&compte->menu));
        printf("\n\n");

        printf("Vous voulez ?\n");
        printf("1/ Voir votre solde\n");
        printf("2/ Modifier le menu\n");
        printf("3/ Supprimer compte\n");
        printf("\n");
        printf("Votre choix (r pour retour): ");

        int res;
        char str[NB_INPUT];
      
        do
        {
            scanf(" %50[^\n]", str);
            choice = str[0];
            if (choice != '1' && choice != '2' && choice != '3' && choice != 'r')
                printf("Choix invalide veuillez réessayer: ");
        } while (choice != '1' && choice != '2' && choice != '3' && choice != 'r');

        switch (choice)
        {
        case '1':
            menu_resto_solde(resto);
            break;

        case '2':
            menu_modifier_resto(resto, menus);
            break;

        case '3':
            res = menu_supprimer_resto(resto, restos, livreurs);
            if (res == 1)
                choice = 'r';
            break;

        case 'r':
            break;
        }

    } while (choice != 'r');
}

void menu_resto_solde(iterator resto)
{
    menu_header();

    printf("#######################################\n");
    printf("            Solde Restaurant           \n");
    printf("#######################################\n");
    printf("\n");
    printf("Votre Solde : %.2f€", ((Restaurant *)(resto.element))->solde);
    printf("\n");
    printf("Entrez n'importe quoi pour retourner: ");
    char choice;
    scanf(" %c", &choice);
}

void menu_modifier_resto(iterator resto, vector *menus)
{
    menu_header();

    printf("#######################################\n");
    printf("           Modification Menu           \n");
    printf("#######################################\n");
    printf("\n");
    printf("Vous voulez ?\n");
    printf("1/ Ajouter un item\n");
    printf("2/ supprimer un item\n");
    printf("\n");
    printf("Votre choix (r pour retour): ");

    char str[NB_INPUT];
    char choice;
    do
    {
        scanf(" %50[^\n]", str);
        choice = str[0];
        if (choice != '1' && choice != '2' && choice != 'r')
            printf("Choix invalide veuillez réessayer: ");
    } while (choice != '1' && choice != '2' && choice != 'r');

    switch (choice)
    {
    case '1':
        modif_additem(resto, menus);
        break;

    case '2':
        modif_suppritem(resto, menus);
        break;

    case 'r':
        break;
    }
}

void modif_additem(iterator resto, vector *menus)
{
    menu_header();

    printf("#######################################\n");
    printf("           Modification Menu           \n");
    printf("#######################################\n");
    printf("\n");
    printf("Menus disponible : \n");
    for (iterator b = begin(menus), e = end(menus); compare(b, e); increment(&b, 1))
    {
        Menu *menu = (Menu *)(b.element);
        printf("%zu,%s,", menu->id, menu->nom);
        affiche_liste(begin(&menu->ingredients), end(&menu->ingredients));
        printf(",%.2f\n", menu->prix);
    }
    printf("\n");
    printf("Entrez l'id de l'item que vous souhaitez ajouter (0 pour creer un nouvel item): ");
    int choice, test;
    do
    {
        scanf(" %d", &choice);
        if (choice != 0)
        {
            test = add_menu(choice, (Restaurant *)resto.element, *menus);
            if (test < 0)
            {
                printf("id invalide : ");
                if (test == -1)
                    printf("id inexistant\n");
                else if (test == -2)
                    printf("item déjà dans menu\n");
                printf("Veuillez réessayer: ");
            }
        }
    } while (choice != 0 && test < 0);

    if (choice == 0)
    {
        printf("Entrez les infos de l'item (nom,ingredient1;ingredient2;...,prix): ");
        do
        {
            char nom[50], ingredients[100];
            float prix;
            if (scanf(" %50[^,],%100[^,],%f", nom, ingredients, &prix) == 3)
            {
                test = ajout_menu(nom, ingredients, prix, menus);
                if (test < 0)
                {
                    printf("Erreur : ");
                    if (test == -1)
                        printf("nom trop long\n");

                    else if(test == -2)
                        printf("ingredients invalides\n");
                    else if(test == -3)

                        printf("prix invalide\n");
                    printf("Veuillez réessayer: ");
                }
                else
                    add_menu(test, (Restaurant *)resto.element, *menus);
            }

            else
            {
                printf("Nombre de valeur incorrecte veuillez réessayer: ");
                test = -1;
            }

        } while (test < 0);
    }
}

void modif_suppritem(iterator resto, vector *menus)
{
    menu_header();

    printf("#######################################\n");
    printf("           Modification Menu           \n");
    printf("#######################################\n");
    printf("\n");
    printf("Vos items :\n");
    Restaurant *compte = (Restaurant *)resto.element;
    for (iterator b = begin(&compte->menu), e = end(&compte->menu); compare(b, e); increment(&b, 1))
    {
        int *id = (int *)b.element;
        Menu *menu = (Menu *)at(menus, (*id) - 1).element;
        printf("%zu,%s,", menu->id, menu->nom);
        affiche_liste(begin(&menu->ingredients), end(&menu->ingredients));
        printf(",%.2f\n", menu->prix);
    }
    printf("\n");
    printf("Quel item souhaitez vous retirer: ");
    int choice;
    do
    {
        scanf(" %d", &choice);
        choice = del_menu(resto, choice);
        if (choice == 0)
            printf("id invalide veuillez réessayer: ");
    } while (choice == 0);
}

int menu_supprimer_resto(iterator resto, vector *restos, vector *livreurs)
{
    menu_header();

    printf("#######################################\n");
    printf("           Suppression Compte          \n");
    printf("#######################################\n");
    printf("\n");
    printf("Etes vous sûr de vouloir supprimer votre compte ? ");
    printf("(y pour oui, n pour non)\n");

    char str[NB_INPUT];
    char choice;
    do
    {
        scanf(" %50[^\n]", str);
        choice = str[0];
        if (choice != 'y' && choice != 'n')
            printf("réponse invalide veuillez réessayer: ");
    } while (choice != 'y' && choice != 'n');


    switch(choice)
    {
    case 'y':
        del_resto(restos, resto, livreurs);
        return 1;
        break;

    case 'n':
        return 0;
        break;
    }

    return 0;
}

void creer_livreur(vector *livreurs, vector *restos)
{
    menu_header();

    printf("#######################################\n");
    printf("            Création Livreur           \n");
    printf("#######################################\n");
    printf("\n");
    printf("Entrez votre nom: ");
    char name[40];
    scanf(" %39[^\n]", name);

    printf("Entrez votre telephone (XX XX XX XX XX): ");
    char tel[15];
    scanf(" %14[^\n]", tel);

    printf("Entrez vos déplacements possibles (code1;code2;...): ");
    char deplacements[100];
    scanf(" %100[^\n]", deplacements);

    printf("Entrez votre restaurant exclusif (0 si aucun): ");
    int resto;
    scanf(" %d", &resto);

    int test;
    do
    {
        test = ajout_livreur(name, tel, deplacements, resto, *restos, livreurs);
        if (test < 0)
        {
            printf("Erreur : ");
            if (test == -1)
            {
                printf("nom invalide\n");
                printf("Veuillez réessayer (nom): ");
                scanf(" %39[^\n]", name);
            }
            else if (test == -2)
            {
                printf("téléphone invalide\n");
                printf("Veuillez réessayer (téléphone): ");
                scanf(" %14[^\n]", tel);
            }
            else if (test == -3)
            {
                printf("déplacements invalide\n");
                printf("Veuillez réessayer (déplacements): ");
                scanf(" %100[^\n]", deplacements);
            }
            else if (test == -4)
            {
                printf("restaurants inexistant\n");
                printf("Veuillez réessayer (restaurant): ");
                scanf(" %d", &resto);
            }
            else if (test == -5)
            {
                printf("peut pas se déplacer au restaurant exclusif\n");
                printf("Veuillez réessayer (restaurant): ");
                scanf(" %d", &resto);
            }
        }
    } while (test < 0);

    printf("votre id est %d\n\n", test);
    printf("Entrez n'importe quoi pour continuer: ");
    char c;
    scanf(" %c", &c);

    Livreur comp;
    comp.id = test;
    menu_livreur(at(livreurs, id_search(begin(livreurs), end(livreurs), &comp, idresto_compare) - 1), livreurs, restos);
}

void connexion_livreur(vector *livreurs, vector *restos)
{
    menu_header();

    printf("#######################################\n");
    printf("           Connexion Livreur           \n");
    printf("#######################################\n");
    printf("\n");
    printf("Entrer votre id (<= 0 si vous ne le connaissez pas): ");
    int id;
    int search;
    do
    {
        scanf(" %d", &id);
        if (id > 0)
        {
            Livreur comp;
            comp.id = id;
            search = id_search(begin(livreurs), end(livreurs), &comp, idlivreur_compare);
            if (search)
                menu_livreur(at(livreurs, search - 1), livreurs, restos);
            else
                printf("id n'existe pas veuillez réessayer: ");
        }
    } while (id > 0 && !search);

    if (id <= 0)
    {
        printf("Entrer votre nom: ");
        char name[40];
        scanf(" %40[^\n]", name);
        vector select = select_name(begin(livreurs), end(livreurs), name, namelivreur);

        if (size(select) == 1)
            menu_livreur(at(livreurs, id_search(begin(livreurs), end(livreurs), at(&select, 0).element, idlivreur_compare) - 1), livreurs, restos);

        else if (size(select) == 0)
        {
            printf("Erreur : nom non présent dans db\n");

            printf("Entrez n'importe quoi pour retourner: ");
            char choice;
            scanf(" %c", &choice);
        }
        else
        {
            printf("\n");
            for (iterator b = begin(&select), e = end(&select); compare(b, e) != 0; increment(&b, 1))
            {
                Livreur *livreur = (Livreur *)(b.element);
                printf("%zu,%s,%14s,", livreur->id, livreur->nom, livreur->telephone);
                affiche_liste(begin(&livreur->deplacements), end(&livreur->deplacements));
                printf(",%zu,%.0f\n", livreur->restaurant, livreur->solde);
            }

            printf("Entrer votre id (<= 0 pour retour): ");
            do
            {
                scanf(" %d", &id);
                if (id > 0)
                {
                    Client comp;
                    comp.id = id;
                    search = id_search(begin(livreurs), end(livreurs), &comp, idlivreur_compare);
                    if (search)
                        menu_livreur(at(livreurs, search - 1), livreurs, restos);
                    else
                        printf("id n'existe pas veuillez réessayer: ");
                }
            } while (id > 0 && !search);
        }
    }
}

void menu_livreur(iterator livreur, vector *livreurs, vector *restos)
{
    char choice;
    do
    {
        menu_header();

        printf("#######################################\n");
        printf("              Menu Livreur             \n");
        printf("#######################################\n");
        printf("\n");

        printf("Info :\n");
        Livreur *compte = (Livreur *)livreur.element;
        printf("id: %ld\n", compte->id);
        printf("nom: %s\n", compte->nom);
        printf("téléphone: %s\n", compte->telephone);
        printf("déplacements: ");
        affiche_liste(begin(&compte->deplacements), end(&compte->deplacements));
        printf("\nexclu resto: %ld\n", compte->restaurant);
        printf("\n");

        printf("Vous voulez ?\n");
        printf("1/ Voir votre solde\n");
        printf("2/ Modifier profil\n");
        printf("3/ Supprimer compte\n");
        printf("\n");
        printf("Votre choix (r pour retour): ");

        char str[NB_INPUT];
        int res;

        do
        {
            scanf(" %50[^\n]", str);
            choice = str[0];
            if (choice != '1' && choice != '2' && choice != '3' && choice != 'r')
                printf("Choix invalide veuillez réessayer: ");
        } while (choice != '1' && choice != '2' && choice != '3' && choice != 'r');

        switch (choice)
        {
        case '1':
            menu_livreur_solde(livreur);
            break;

        case '2':
            menu_modifier_livreur(livreur, restos);
            break;

        case '3':
            res = menu_supprimer_livreur(livreur, restos);
            if (res == 1)
                choice = 'r';
            break;

        case 'r':
            break;
        }

    } while (choice != 'r');
}

void menu_livreur_solde(iterator livreur)
{
    menu_header();

    printf("#######################################\n");
    printf("             Solde Livreur             \n");
    printf("#######################################\n");
    printf("\n");
    printf("Votre Solde : %.2f€", ((Livreur *)livreur.element)->solde);
    printf("\n");
    printf("Entrez n'importe quoi pour retourner: ");
    char choice;
    scanf(" %c", &choice);
}

void menu_modifier_livreur(iterator livreur, vector *restos)
{
    menu_header();

    printf("#######################################\n");
    printf("          Modification Livreur         \n");
    printf("#######################################\n");
    printf("\n");
    printf("Vous voulez modifiez ?\n");
    printf("1/ Déplacements possibles\n");
    printf("2/ Téléphone\n");
    printf("3/ Exclusivité restaurateur\n");
    printf("\n");
    printf("Votre choix (r pour retour): ");

    char str[NB_INPUT];
    char choice;
    do
    {
        scanf(" %50[^\n]", str);
        choice = str[0];
        if (choice != '1' && choice != '2' && choice != '3' && choice != 'r')
            printf("Choix invalide veuillez réessayer: ");
    } while (choice != '1' && choice != '2' && choice != '3' && choice != 'r');

    switch (choice)
    {
    case '1':
        menu_deplacement(livreur, restos);
        break;

    case '2':
        modif_tellivreur(livreur);
        break;

    case '3':
        modif_restolivreur(livreur, restos);
        break;

    case 'r':
        break;
    }
}

void menu_deplacement(iterator livreur, vector *restos)
{
    menu_header();

    printf("#######################################\n");
    printf("          Modification Livreur         \n");
    printf("#######################################\n");
    printf("\n");
    printf("Vous voulez ?\n");
    printf("1/ Ajouter un déplacement\n");
    printf("2/ Retirer un déplacement\n");
    printf("\n");
    printf("Votre choix (r pour retour): ");

    char str[NB_INPUT];

    char choice;
    do
    {
        scanf(" %50[^\n]", str);
        choice = str[0];
        if (choice != '1' && choice != '2' && choice != 'r')
            printf("Choix invalide veuillez réessayer: ");
    } while (choice != '1' && choice != '2' && choice != 'r');

    switch (choice)
    {
    case '1':
        modif_addcode(livreur);
        break;

    case '2':
        modif_delcode(livreur, restos);
        break;

    case 'r':
        menu_modifier_livreur(livreur, restos);
        break;
    }
}

void modif_addcode(iterator livreur)
{
    menu_header();

    printf("#######################################\n");
    printf("          Modification Livreur         \n");
    printf("#######################################\n");
    printf("\n");
    printf("Entrez le nouveau code postale: ");

    int test;
    do
    {
        char code[10];
        scanf(" %10[^\n]", code);
        test = modif_livreur_addcode(livreur, code);
        if (test < 0)
        {
            printf("Erreur : ");
            if (test == -1)
                printf("code invalide\n");
            else if (test == -2)
                printf("code déjà présent\n");
            printf("Veuillez réessayer: ");
        }
    } while (test < 0);
}

void modif_delcode(iterator livreur, vector *restos)
{
    menu_header();

    printf("#######################################\n");
    printf("          Modification Livreur         \n");
    printf("#######################################\n");
    printf("\n");
    printf("Déplacements possibles :\n");

    Livreur *compte = (Livreur *)livreur.element;
    int i = 1;
    for (iterator b = begin(&compte->deplacements), e = end(&compte->deplacements); compare(b, e); increment(&b, 1))
    {
        printf("%d/ %d\n", i, *((int *)b.element));
        i++;
    }

    printf("Entrez le numéro du déplacement à retirer: ");

    int test;
    do
    {
        int choice;
        scanf(" %d", &choice);
        test = modif_livreur_delcode(livreur, choice, *restos);
        if (test < 0)
        {
            printf("Erreur : ");
            if (test == -1)
                printf("numéro invalide\n");
            else if (test == -2)
                printf("cause conflit avec restaurant exclusif");
            printf("Veuillez réessayer: ");
        }
    } while (test < 0);
}

void modif_tellivreur(iterator livreur)
{
    menu_header();

    printf("#######################################\n");
    printf("          Modification Livreur         \n");
    printf("#######################################\n");
    printf("\n");
    printf("Entrez votre nouveaux téléphone (XX XX XX XX XX): ");

    int test;
    do
    {
        char *tel = malloc(20);
        scanf(" %20[^\n]", tel);
        test = modif_livreur_tel(livreur, tel);
        if (test < 0)
        {
            printf("Erreur : tel invalide\n");
            printf("Veuillez réessayer: ");
        }
        free(tel);
    } while (test < 0);
}

void modif_restolivreur(iterator livreur, vector *restos)
{
    menu_header();

    printf("#######################################\n");
    printf("          Modification Livreur         \n");
    printf("#######################################\n");
    printf("\n");
    printf("Entrez votre nouveaux restaurant exclusif (0 si aucun): ");
    int test;
    do
    {
        int choice;
        scanf(" %d", &choice);
        test = modif_livreur_resto(livreur, choice, *restos);
        if (test < 0)
        {
            printf("Erreur : ");
            if (test == -1)
                printf("id invalide\n");
            else if (test == -2)
                printf("incapable de se déplacer là\n");
            printf("Veuillez réessayer: ");
        }
    } while (test < 0);
}

int menu_supprimer_livreur(iterator livreur, vector *livreurs)
{
    menu_header();

    printf("#######################################\n");
    printf("           Suppression Compte          \n");
    printf("#######################################\n");
    printf("\n");
    printf("Etes vous sûr de vouloir supprimer votre compte ? ");
    printf("(y pour oui, n pour non)\n");


    char str[NB_INPUT];
    char choice;
    do{
        scanf(" %50[^\n]", str);
        choice = str[0];
        if(choice!='y' && choice!='n')
            printf("réponse invalide veuillez réessayer: ");
    } while (choice != 'y' && choice != 'n');

    switch(choice)
    {
    case 'y':
        del_livreur(livreurs, livreur);
        return 1;
        break;

    case 'n':
        return 0;
        break;
    }

    return 0;
}

void affiche_liste(iterator first, iterator last)
{
    if (compare(first, last) == 0)
    {
        printf("vide");
        return;
    }

    iterator e = last;
    decrement(&e, 1);
    if (first.element_size == sizeof(size_t))
    {
        for (iterator b = first; compare(b, e); increment(&b, 1))
        {
            printf("%ld,", *((size_t *)b.element));
        }

        printf("%ld", *((size_t *)e.element));
    }

    else if (first.element_size == sizeof(int))
    {
        for (iterator b = first; compare(b, e); increment(&b, 1))
        {
            printf("%d,", *((int *)b.element));
        }

        printf("%d", *((int *)e.element));
    }

    else
    {
        for (iterator b = first; compare(b, e); increment(&b, 1))
        {
            printf("%s;", (char *)(b.element));
        }
        printf("%s", (char *)(e.element));
    }

    return;
}