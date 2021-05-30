#include "gestionfichier.h"
#include "db.h"
#include "algorithm.h"
#include "functions.h"
#include "menu.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    system("clear");
    printf("chargement");
    check(0);

    vector restos = lecture_restaurant("db_restaurants.csv");
    shrink_to_fit(&restos);
    printf(".");
    vector menus = lecture_menu("db_menus.csv");
    shrink_to_fit(&menus);
    printf(".");
    vector livreurs = lecture_livreur("db_livreurs.csv");
    shrink_to_fit(&livreurs);
    printf(".");
    vector clients = lecture_client("db_clients.csv");
    shrink_to_fit(&clients);
    printf(".");

    printf("\n\n");

    char choice;

    do
    {
        system("clear");
        printf("#######################################\n");
        printf(" Bienvenue sur Kiki's Delivery Service \n");
        printf("#######################################\n");
        printf("\n");
        printf("#######################################\n");
        printf("             Menu Principal            \n");
        printf("#######################################\n");
        printf("\n");
        printf("Vous êtes ?\n");
        printf("1/ Un.e Restaurateur.tice\n");
        printf("2/ Un.e Livreur.se\n");
        printf("3/ Un.e Client.e\n");
        printf("\n");
        printf("Votre choix (q pour quitter): ");

        char * str = malloc(50);
        
        do{
            if(scanf(" %50[^\n]", str) == 1)
            {
                choice = str[0];
                if(choice!='1' && choice!='2' && choice!='3' && choice!='q')
                    printf("Choix invalide veuillez réessayer: ");
            }
            else
                printf("Choix invalide veuillez réessayer: ");
        }while(choice!='1' && choice!='2' && choice!='3' && choice!='q');

        free(str);
        
        int co;
        switch (choice)
        {
        case '1':
            co = menu_connexion();
            if(co == 1)
                connexion_resto(&restos, &menus, &livreurs);
            else if(co == 2)
                creer_resto(&restos, &menus, &livreurs);
            break;

        case '2':
            co = menu_connexion();
            if(co == 1)
                connexion_livreur(&livreurs, &restos);
            else if(co == 2)
                creer_livreur(&livreurs, &restos);
            break;

        case '3':
            co = menu_connexion();
            if(co == 1)
                connexion_client(&clients, &restos, &menus, &livreurs);
            else if(co == 2)
                creer_client(&clients, &restos, &menus, &livreurs);
            break;
        }
    }while (choice != 'q');    

    sauvegarde_clients(begin(&clients), end(&clients));
    destroy(&clients);

    sauvegarde_resto(begin(&restos), end(&restos));
    destroy(&restos);

    sauvegarde_menus(begin(&menus), end(&menus));
    destroy(&menus);

    sauvegarde_livreurs(begin(&livreurs), end(&livreurs));
    destroy(&livreurs);

    return 0;
}