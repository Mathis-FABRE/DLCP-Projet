#include "menu.h"

#include <stdio.h>
#include <stdlib.h>

void connexion_client(vector * clients, vector * restos, vector * menus, vector * livreurs)
{
    system("clear");
    printf("#######################################\n");
    printf("         kiki's delivery sevice        \n");
    printf("#######################################\n");
    printf("\n");
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
        if(id > 0)
        {
            Client comp;
            comp.id=id;
            search = id_search(begin(clients), end(clients), &comp, idclient_compare);
            if(search)
                menu_client(at(clients, search-1), restos, menus, livreurs);
            else
                printf("id n'existe pas veuillez réessayer: ");
        }
    }while(id>0 && !search);

    if(id<=0)
    {
        printf("Entrer votre nom: ");
        // char * name;
        // scanf(" %s", name);
    }
}

void menu_client(iterator client, vector * restos, vector * menus, vector * livreurs)
{
    system("clear");
    printf("#######################################\n");
    printf("         kiki's delivery sevice        \n");
    printf("#######################################\n");
    printf("\n");
    printf("#######################################\n");
    printf("              Menu Client              \n");
    printf("#######################################\n");
    printf("\n");

    printf("info :\n");
    Client * compte = (Client*)client.element;
    printf("id: %ld\n", compte->id);
    printf("nom: %s\n", compte->nom);
    printf("code postal: %d\n", compte->code_postal);
    printf("\n");

    printf("Vous voulez ?\n");
    printf("1/ Consulter votre solde\n");
    printf("2/ Modifier votre profil\n");
    printf("3/ Voir la liste des restaurants\n");
    printf("4/ Passer une commande\n");
    printf("5/ supprimer compte\n");
    printf("\n");
    printf("Votre choix (r pour retour): ");
    char choice;
    do{
        scanf(" %c", &choice);
        if(choice!='1' && choice!='2' && choice!='3' && choice!='4' && choice!='5' && choice!='r')
            printf("choix invalide veuillez réessayer: ");
    }while(choice!='1' && choice!='2' && choice!='3' && choice!='4' && choice!='5' && choice!='r');

    switch (choice)
    {
    case '1':
        menu_client_solde(client, restos, menus, livreurs);
        break;

    case '2':
        menu_modifier_client(client, restos, menus, livreurs);
        break;

    case '3':
        menu_client(client, restos, menus, livreurs);
        break;

    case '4':
        menu_client(client, restos, menus, livreurs);
        break;

    case '5':
        menu_supprimer_client(client, restos, menus, livreurs);
        break;

    case 'r':
        // menu_principal();
        break;
    }

}

void menu_client_solde(iterator client, vector * restos, vector * menus, vector * livreurs)
{
    system("clear");
    printf("#######################################\n");
    printf("         kiki's delivery sevice        \n");
    printf("#######################################\n");
    printf("\n");
    printf("#######################################\n");
    printf("              Solde Client             \n");
    printf("#######################################\n");
    printf("\n");
    printf("Votre Solde : %.2f€", ((Client*)client.element)->solde);
    printf("\n");
    printf("Voulez vous créditer votre solde ?\n");
    printf("(y pour oui, n pour non)\n");
    char choice;
    do{
        scanf(" %c", &choice);
        if(choice!='y' && choice!='n')
            printf("réponse invalide veuillez réessayer: ");
    }while(choice!='y' && choice!='n');
    switch(choice)
    {
    case 'y':
        menu_credit_client(client, restos, menus, livreurs);
        break;
    
    case 'n':
        menu_client(client, restos, menus, livreurs);
        break;
    }
}

void menu_credit_client(iterator client, vector * restos, vector * menus, vector * livreurs)
{
    system("clear");
    printf("#######################################\n");
    printf("         kiki's delivery sevice        \n");
    printf("#######################################\n");
    printf("\n");
    printf("#######################################\n");
    printf("            Creditage Client           \n");
    printf("#######################################\n");
    printf("\n");
    printf("Entrez la somme que vous souhaitez\n");
    printf("créditer a votre solde: ");
    float choice;
    do{
        scanf(" %f", &choice);
        if(choice < 0)
            printf("somme invalide veuillez réessayer: ");
    }while(choice < 0);
    menu_client(client, restos, menus, livreurs);
}

void menu_modifier_client(iterator client, vector * restos, vector * menus, vector * livreurs)
{
    system("clear");
    printf("#######################################\n");
    printf("         kiki's delivery sevice        \n");
    printf("#######################################\n");
    printf("\n");
    printf("#######################################\n");
    printf("          Modification Client          \n");
    printf("#######################################\n");
    printf("\n");
    printf("Vous voulez modifiez ?\n");
    printf("1/ Code postal\n");
    printf("2/ Téléphone\n");
    printf("\n");
    printf("Votre choix (q pour quitter, r pour retour): ");
    char choice;
    do{
        scanf(" %c", &choice);
        if(choice!='1' && choice!='2' && choice!='q' && choice!='r')
            printf("choix invalide veuillez réessayer: ");
    }while(choice!='1' && choice!='2' && choice!='q' && choice!='r');

    switch (choice)
    {
    case '1':
        // menu_livreur_solde();
        break;

    case '2':
        // menu_modifier_livreur();
        break;

    case 'r':
        menu_client(client, restos, menus, livreurs);
        break;
    
    default:
        break;
    }
}

void menu_supprimer_client(iterator client, vector * restos, vector * menus, vector * livreurs)
{
    system("clear");
    printf("#######################################\n");
    printf("         kiki's delivery sevice        \n");
    printf("#######################################\n");
    printf("\n");
    printf("#######################################\n");
    printf("           Suppression Compte          \n");
    printf("#######################################\n");
    printf("\n");
    printf("Etes vous sûr de vouloir supprimer votre compte ?");
    printf("(y pour oui, n pour non)\n");
    char choice;
    do{
        scanf(" %c", &choice);
        if(choice!='y' && choice!='n')
            printf("réponse invalide veuillez réessayer: ");
    }while(choice!='y' && choice!='n');
    switch(choice)
    {
    case 'y':
        // menu_principal();
        break;
    
    case 'n':
        menu_client(client, restos, menus, livreurs);
        break;
    }
}

void connexion_resto(vector * restos, vector * menus)
{
    system("clear");
    printf("#######################################\n");
    printf("         kiki's delivery sevice        \n");
    printf("#######################################\n");
    printf("\n");
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
        if(id > 0)
        {
            Restaurant comp;
            comp.id = id;
            search = id_search(begin(restos), end(restos), &comp, idresto_compare);
            if(search)
                menu_resto(at(restos, search - 1), menus);
            else
                printf("id n'existe pas veuillez réessayer: ");
        }
    }while(id>0 && !search);

    if(id<=0)
    {
        printf("Entrer votre nom: ");
        // char * name;
        // scanf(" %s", name);
    }
}

void menu_resto(iterator resto, vector * menus)
{
    system("clear");
    printf("#######################################\n");
    printf("         kiki's delivery sevice        \n");
    printf("#######################################\n");
    printf("\n");
    printf("#######################################\n");
    printf("            Menu Restaurant            \n");
    printf("#######################################\n");
    printf("\n");

    printf("info :\n");
    Restaurant * compte = (Restaurant*)resto.element;
    printf("id: %ld\n", compte->id);
    printf("nom: %s\n", compte->nom);
    printf("code postal: %d\n", compte->code_postal);
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
    char choice;
    do{
        scanf(" %c", &choice);
        if(choice!='1' && choice!='2' && choice!='3' && choice!='r')
            printf("choix invalide veuillez réessayer: ");
    }while(choice!='1' && choice!='2' && choice!='3' && choice!='r');

    switch (choice)
    {
    case '1':
        menu_resto_solde(resto, menus);
        break;

    case '2':
        menu_modifier_resto(resto, menus);
        break;

    case '3':
        menu_supprimer_resto(resto, menus);
        break;

    case 'r':
        // menu_principal();
        break;
    }

}

void menu_resto_solde(iterator resto, vector * menus)
{
    system("clear");
    printf("#######################################\n");
    printf("         kiki's delivery sevice        \n");
    printf("#######################################\n");
    printf("\n");
    printf("#######################################\n");
    printf("            Solde Restaurant           \n");
    printf("#######################################\n");
    printf("\n");
    printf("Votre Solde : %.2f€", ((Restaurant*)(resto.element))->solde);
    printf("\n");
    printf("Entrer n'importe quoi pour retourner: ");
    char choice;
    scanf(" %c", &choice);
    menu_resto(resto, menus);
}

void menu_modifier_resto(iterator resto, vector * menus)
{
    system("clear");
    printf("#######################################\n");
    printf("         kiki's delivery sevice        \n");
    printf("#######################################\n");
    printf("\n");
    printf("#######################################\n");
    printf("           Modification Menu           \n");
    printf("#######################################\n");
    printf("\n");
    printf("Vous voulez ?\n");
    printf("1/ Ajouter un item\n");
    printf("2/ supprimer un item\n");
    printf("\n");
    printf("Votre choix (r pour retour): ");
    char choice;
    do{
        scanf(" %c", &choice);
        if(choice!='1' && choice!='2' && choice!='r')
            printf("choix invalide veuillez réessayer: ");
    }while(choice!='1' && choice!='2' && choice!='r');

    switch (choice)
    {
    case '1':
        modif_additem(resto, menus);
        break;

    case '2':
        // menu_modifier_livreur();
        break;

    case 'r':
        menu_resto(resto, menus);
        break;
    
    default:
        break;
    }
}

void modif_additem(iterator resto, vector * menus)
{
    system("clear");
    printf("#######################################\n");
    printf("         kiki's delivery sevice        \n");
    printf("#######################################\n");
    printf("\n");
    printf("#######################################\n");
    printf("           Modification Menu           \n");
    printf("#######################################\n");
    printf("\n");
    printf("Menus disponible : \n");
    for(iterator b=begin(menus), e=end(menus); compare(b,e); increment(&b,1))
    {
        Menu * menu=(Menu*)(b.element);
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
        if(choice != 0)
        {
            test = add_menu(choice, (Restaurant*)resto.element, *menus);
            if(test<0)
            {
                printf("id invalide : ");
                if(test==-1)
                    printf("id inexistant\n");
                else if(test==-2)
                    printf("item déjà dans menu\n");
                printf("Veuillez réessayer: ");
            }
        }
    } while (choice !=0 && test<0);
    
    if(choice == 0)
    {
        printf("Entrez les infos de l'item (nom,ingredient1;ingredient2;...,prix): ");
        do
        {
            char * nom, * ingredients;
            nom=malloc(50);
            ingredients=malloc(100);
            float prix;
            if(scanf(" %50[^,],%100[^,],%f", nom, ingredients, &prix)==3)
            {
                test = ajout_menu(nom, ingredients, prix, menus);
                if (test<0)
                {
                    printf("Erreur : ");
                    if(test == -1)
                        printf("nom trop long\n");
                    else if(test == -2)
                        printf("ingredients invalides");
                    else if(test == -3)
                        printf("prix invalide\n");
                    printf("Veuillez réessayer: ");
                }
                else
                    add_menu(test, (Restaurant*)resto.element, *menus);
            }

            else
            {
                printf("Nombre de valeur incorrecte veuillez réessayer: ");
                test=-1;
            }
        } while (test<0);
        
    }
}

void menu_supprimer_resto(iterator resto, vector * menus)
{
    system("clear");
    printf("#######################################\n");
    printf("         kiki's delivery sevice        \n");
    printf("#######################################\n");
    printf("\n");
    printf("#######################################\n");
    printf("           Suppression Compte          \n");
    printf("#######################################\n");
    printf("\n");
    printf("Etes vous sûr de vouloir supprimer votre compte ?");
    printf("(y pour oui, n pour non)\n");
    char choice;
    do{
        scanf(" %c", &choice);
        if(choice!='y' && choice!='n')
            printf("réponse invalide veuillez réessayer: ");
    }while(choice!='y' && choice!='n');
    switch(choice)
    {
    case 'y':
        // menu_principal();
        break;
    
    case 'n':
        menu_resto(resto, menus);
        break;
    }
}

void connexion_livreur(vector * livreurs, vector * restos)
{
    system("clear");
    printf("#######################################\n");
    printf("         kiki's delivery sevice        \n");
    printf("#######################################\n");
    printf("\n");
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
        if(id > 0)
        {
            Livreur comp;
            comp.id = id;
            search = id_search(begin(livreurs), end(livreurs), &comp, idlivreur_compare);
            if(search)
                menu_livreur(at(livreurs, search - 1), restos);
            else
                printf("id n'existe pas veuillez réessayer: ");
        }
    }while(id>0 && !search);

    if(id<=0)
    {
        printf("Entrer votre nom: ");
        // char * name;
        // scanf(" %s", name);
    }
}

void menu_livreur(iterator livreur, vector * restos)
{
    system("clear");
    printf("#######################################\n");
    printf("         kiki's delivery sevice        \n");
    printf("#######################################\n");
    printf("\n");
    printf("#######################################\n");
    printf("              Menu Livreur             \n");
    printf("#######################################\n");
    printf("\n");

    printf("info :\n");
    Livreur * compte = (Livreur*)livreur.element;
    printf("id: %ld\n", compte->id);
    printf("nom: %s\n", compte->nom);
    printf("exclu resto: %ld\n", compte->restaurant);
    printf("\n");

    printf("Vous voulez ?\n");
    printf("1/ Voir votre solde\n");
    printf("2/ Modifier profil\n");
    printf("3/ Supprimer compte\n");
    printf("\n");
    printf("Votre choix (r pour retour): ");
    char choice;
    do{
        scanf(" %c", &choice);
        if(choice!='1' && choice!='2' && choice!='3' && choice!='r')
            printf("choix invalide veuillez réessayer: ");
    }while(choice!='1' && choice!='2' && choice!='3' && choice!='r');

    switch (choice)
    {
    case '1':
        menu_livreur_solde(livreur, restos);
        break;

    case '2':
        menu_modifier_livreur(livreur, restos);
        break;

    case '3':
        menu_supprimer_livreur(livreur, restos);
        break;

    case 'r':
        // menu_principal();
        break;
    
    default:
        break;
    }
}

void menu_livreur_solde(iterator livreur, vector * restos)
{
    system("clear");
    printf("#######################################\n");
    printf("         kiki's delivery sevice        \n");
    printf("#######################################\n");
    printf("\n");
    printf("#######################################\n");
    printf("             Solde Livreur             \n");
    printf("#######################################\n");
    printf("\n");
    printf("Votre Solde : %.2f€", ((Livreur*)livreur.element)->solde);
    printf("\n");
    printf("Entrer n'importe quoi pour retourner: ");
    char choice;
    scanf(" %c", &choice);
    menu_livreur(livreur, restos);
}

void menu_modifier_livreur(iterator livreur, vector * restos)
{
    printf("#######################################\n");
    printf("         kiki's delivery sevice        \n");
    printf("#######################################\n");
    printf("\n");
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
    char choice;
    do{
        scanf(" %c", &choice);
        if(choice!='1' && choice!='2' && choice!='3' && choice!='r')
            printf("choix invalide veuillez réessayer: ");
    }while(choice!='1' && choice!='2' && choice!='3' && choice!='r');

    switch (choice)
    {
    case '1':
        // menu_livreur_solde();
        break;

    case '2':
        // menu_modifier_livreur();
        break;

    case '3':
        // menu_supprimer_livreur();
        break;

    case 'r':
        menu_livreur(livreur, restos);
        break;
    }
}

void menu_supprimer_livreur(iterator livreur, vector * restos)
{
    system("clear");
    printf("#######################################\n");
    printf("         kiki's delivery sevice        \n");
    printf("#######################################\n");
    printf("\n");
    printf("#######################################\n");
    printf("           Suppression Compte          \n");
    printf("#######################################\n");
    printf("\n");
    printf("Etes vous sûr de vouloir supprimer votre compte ?");
    printf("(y pour oui, n pour non)\n");
    char choice;
    do{
        scanf(" %c", &choice);
        if(choice!='y' && choice!='n')
            printf("réponse invalide veuillez réessayer: ");
    }while(choice!='y' && choice!='n');
    switch(choice)
    {
    case 'y':
        // menu_principal();
        break;
    
    case 'n':
        menu_livreur(livreur, restos);
        break;
    }
}

void affiche_liste(iterator first, iterator last)
{
    if(compare(first,last) == 0)
    {
        printf("vide");
        return;
    }

    iterator e = last;
    decrement(&e, 1);
    if(first.element_size == sizeof(size_t))
    {
        for (iterator b = first; compare(b,e); increment(&b, 1))
        {
            printf("%ld,", *((size_t*)b.element));
        }
        
        printf("%ld", *((size_t*)e.element));
    }
    else
    {
        for(iterator b=first; compare(b,e); increment(&b,1))
        {
            printf("%s;", (char*)(b.element));
        }
        printf("%s", (char*)(e.element));
    }

    return;
}