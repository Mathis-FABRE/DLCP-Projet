#include "gestionfichier.h"
#include "db.h"
#include "algorithm.h"
#include "functions.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    system("clear");
    printf("#######################################\n");
    printf(" Bienvenue sur kiki's delivery service \n");
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
        scanf("%c", &choice);
        if(choice!='1' && choice!='2' && choice!='3' && choice!='q')
            printf("choix invalide veuillez réessayer: ");
    }while(choice!='1' && choice!='2' && choice!='3' && choice!='q');

    printf("\n");

    return 0;
}