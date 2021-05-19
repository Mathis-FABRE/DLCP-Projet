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
    printf("Vous voulez ?\n");
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
        menu_client_solde();
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

void menu_client_solde()
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
    printf("Votre Solde : ");
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
        menu_credit_client();
        break;
    
    case 'n':
        menu_client();
        break;
    }
}

void menu_credit_client()
{
    system("clear");
    printf("#######################################\n");
    printf("         kiki's delivery sevice        \n");
    printf("#######################################\n");
    printf("\n");
    printf("#######################################\n");
    printf("            Creditage Client           \n")
    printf("#######################################\n");
    printf("\n");
    printf("Entrez la somme que vous souhaitez\n");
    printf("créditer a votre solde: ");

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
    printf("Vous voulez ?\n");
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
        menu_resto_solde();
        break;

    case '2':
        menu_modifier_resto();
        break;

    case '3':
        menu_supprimer_resto();
        break;

    case 'r':
        menu_principal();
        break;
    
    default:
        break;
    }

}

void menu_resto_solde()
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
    printf("Votre Solde : ");
    printf("\n");
    printf("Entrer n'importe quoi pour retourner: ");
    char choice;
    scanf(" %c", &choice);
    menu_resto();
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
    printf("Vous voulez ?\n");
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
        menu_livreur_solde();
        break;

    case '2':
        menu_modifier_livreur();
        break;

    case '3':
        menu_supprimer_livreur();
        break;

    case 'r':
        menu_principal();
        break;
    
    default:
        break;
    }

}

void menu_livreur_solde()
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
    printf("Votre Solde : ");
    printf("\n");
    printf("Entrer n'importe quoi pour retourner: ");
    char choice;
    scanf(" %c", &choice);
    menu_livreur();
}