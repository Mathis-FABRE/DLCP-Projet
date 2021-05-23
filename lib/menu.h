#include "vector.h"
#include "db.h"
#include "algorithm.h"
#include "functions.h"

#pragma once

// void menu_principal(vector * clients, vector * restos, vector * menus, vector * livreurs);
void connexion_client(vector * clients, vector * restos, vector * menus, vector * livreurs);
void menu_client(iterator client, vector * restos, vector * menus, vector * livreurs);
void menu_client_solde(iterator client, vector * restos, vector * menus, vector * livreurs);
void menu_credit_client(iterator client, vector * restos, vector * menus, vector * livreurs);
void menu_modifier_client(iterator client, vector * restos, vector * menus, vector * livreurs);
void menu_supprimer_client(iterator client, vector * restos, vector * menus, vector * livreurs);
void connexion_resto(vector * restos, vector * menus);
void menu_resto(iterator resto, vector * menus);
void menu_resto_solde(iterator resto, vector * menus);
void menu_modifier_resto(iterator resto, vector * menus);
void menu_supprimer_resto(iterator resto, vector * menus);
void connexion_livreur(vector * livreurs, vector * restos);
void menu_livreur(iterator livreur, vector * restos);
void menu_livreur_solde(iterator livreur, vector * restos);
void menu_modifier_livreur(iterator livreur, vector * restos);
void menu_supprimer_livreur(iterator livreur, vector * restos);