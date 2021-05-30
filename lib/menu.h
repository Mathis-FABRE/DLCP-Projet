#include "vector.h"
#include "db.h"
#include "algorithm.h"
#include "functions.h"

#pragma once

void menu_header();
int menu_connexion();

void creer_client(vector * clients, vector * restos, vector * menus, vector * livreurs);
void connexion_client(vector * clients, vector * restos, vector * menus, vector * livreurs);
void menu_client(iterator client, vector * clients, vector * restos, vector * menus, vector * livreurs);
void menu_client_solde(iterator client);
void menu_credit_client(iterator client);
void menu_modifier_client(iterator client, vector * restos, vector * menus, vector * livreurs);
int menu_modif_client_code(iterator client);
int menu_modif_client_tel(iterator client);
int menu_afficher_restos(iterator client, vector *clients, vector *restos, vector *menus, vector *livreurs);
int affichage_restos(vector *liste, vector *menus);
int menu_supprimer_client(iterator client, vector * clients);

void creer_resto(vector * restos, vector * menus, vector * livreurs);
void connexion_resto(vector * restos, vector * menus, vector * livreurs);
void menu_resto(iterator resto, vector * restos, vector * menus, vector * livreurs);
void menu_resto_solde(iterator resto);
void menu_modifier_resto(iterator resto, vector * menus);
void modif_additem(iterator resto, vector * menus);
void modif_suppritem(iterator resto, vector * menus);
int menu_supprimer_resto(iterator resto, vector * restos, vector * livreurs);

void creer_livreur(vector * livreurs, vector * restos);
void connexion_livreur(vector * livreurs, vector * restos);
void menu_livreur(iterator livreur, vector * livreurs, vector * restos);
void menu_livreur_solde(iterator livreur);
void menu_modifier_livreur(iterator livreur, vector * restos);
void menu_deplacement(iterator livreur, vector * restos);
void modif_addcode(iterator livreur);
void modif_delcode(iterator livreur, vector * restos);
void modif_tellivreur(iterator livreur);
void modif_restolivreur(iterator livreur, vector * restos);
int menu_supprimer_livreur(iterator livreur, vector * livreurs);

void affiche_liste(iterator first, iterator last);