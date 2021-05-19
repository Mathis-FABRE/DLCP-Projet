#include "menu.h"

#include <stdio.h>
#include <stdlib.h>

void menu_principal()
{
    system("clear");
    printf("#######################################\n");
    printf("         kiki's delivery sevice        \n");
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
    char choice;
    do{
        scanf(" %c", &choice);
        if(choice!='1' && choice!='2' && choice!='3' && choice!='q')
            printf("choix invalide veuillez réessayer: ");
    }while(choice!='1' && choice!='2' && choice!='3' && choice!='q');

    switch (choice)
    {
    case '1':
        menu_resto();
        break;

    case '2':
        menu_livreur();
        break;

    case '3':
        menu_client();
        break;
    
    default:
        break;
    }
}

void menu_client()
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
    printf("vous voulez ?\n");
    printf("1/ Consulter votre solde\n");
    printf("2/ Modifier votre profil\n");
    printf("3/ Voir la liste des restaurants\n");
    printf("4/ Passer une commande\n");
    printf("\n");
    printf("Votre choix (q pour quitter, r pour retour): ");
    char choice;
    do{
        scanf(" %c", &choice);
        if(choice!='1' && choice!='2' && choice!='3' && choice!='4' && choice!='q' && choice!='r')
            printf("choix invalide veuillez réessayer: ");
    }while(choice!='1' && choice!='2' && choice!='3' && choice!='4' && choice!='q' && choice!='r');

    switch (choice)
    {
    case '1':
        menu_resto();
        break;

    case '2':
        menu_livreur();
        break;

    case '3':
        menu_client();
        break;

    case 'r':
        menu_principal();
        break;
    
    default:
        break;
    }

}

void menu_resto()
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
    printf("vous voulez ?\n");
    printf("1/ Voir votre solde\n");
    printf("2/ Modifier le menu\n");
    printf("3/ Supprimer compte\n");
    printf("\n");
    printf("Votre choix (q pour quitter, r pour retour): ");
    char choice;
    do{
        scanf(" %c", &choice);
        if(choice!='1' && choice!='2' && choice!='3' && choice!='q' && choice!='r')
            printf("choix invalide veuillez réessayer: ");
    }while(choice!='1' && choice!='2' && choice!='3' && choice!='q' && choice!='r');

    switch (choice)
    {
    case '1':
        menu_resto();
        break;

    case '2':
        menu_livreur();
        break;

    case '3':
        menu_client();
        break;

    case 'r':
        menu_principal();
        break;
    
    default:
        break;
    }

}

void menu_livreur()
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
    printf("vous voulez ?\n");
    printf("1/ Voir votre solde\n");
    printf("2/ Modifier profil\n");
    printf("3/ Supprimer compte\n");
    printf("\n");
    printf("Votre choix (q pour quitter, r pour retour): ");
    char choice;
    do{
        scanf(" %c", &choice);
        if(choice!='1' && choice!='2' && choice!='3' && choice!='q' && choice!='r')
            printf("choix invalide veuillez réessayer: ");
    }while(choice!='1' && choice!='2' && choice!='3' && choice!='q' && choice!='r');

    switch (choice)
    {
    case '1':
        menu_resto();
        break;

    case '2':
        menu_livreur();
        break;

    case '3':
        menu_client();
        break;

    case 'r':
        menu_principal();
        break;
    
    default:
        break;
    }

}