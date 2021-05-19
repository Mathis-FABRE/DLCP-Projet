#include "menu.h"

#include <stdio.h>
#include <stdlib.h>

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
}