#include "gestionfichier.h"
#include "db.h"
#include "algorithm.h"
#include "functions.h"

#include "test_harness/test_harness.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Valeurs pour le harnais de test spécifiques à ce programme.
// augmenter cette val à chaque test créer
int const tests_total = 110;

int const test_column_width = 80;

int main()
{
    float const growth_factor=2.;

    // test gestion_fichier
    {
        check(1);

        // test de lecture_client() + sauvegarde_clients()
        {
            vector clients=lecture_client("test/db_clients.csv");

            TEST(size(clients)==3);

            Client const* a=(Client*)(begin(&clients).element);
            TEST(a->id==1);
            TEST(strcmp(a->nom,"Francoise Perrin")==0);
            TEST(a->code_postal==13005);
            TEST(strcmp(a->telephone,"04 10 20 30 40")==0);
            TEST(a->solde==0.);

            for(int id=1; id<=3; id++)
            {
                Client const* b=(Client*)(at(&clients, id-1).element);
                TEST(b->id==id);
            }

            TEST(get_first_id(begin(&clients), end(&clients)) == 4);

            sauvegarde_clients(begin(&clients), end(&clients));

            TEST_FILE("db_clients.csv","test/db_clients.csv")

            destroy(&clients);
        }

        // test de separateur_chaine()
        {
            vector dbmenus=make_vector(sizeof(size_t),0,growth_factor);

            separateur_chaine(&dbmenus, "1;2;3");

            TEST(size(dbmenus)==3);

            for (size_t i = 0; i < 3; i++)
            {
                size_t const* id=(size_t*)(at(&dbmenus, i).element);
                TEST(*id==i+1);
            }

            destroy(&dbmenus);
        }
        
        // test lecture_restaurant() + sauvegarde_resto()
        {
            vector restos=lecture_restaurant("test/db_restaurants.csv");

            TEST(size(restos)==4);

            Restaurant const* c=(Restaurant*)(at(&restos, 2).element);

            TEST(c->id==3);
            TEST(strcmp(c->nom, "Joe's International House of Pancakes")==0);
            TEST(c->code_postal==13010);
            TEST(strcmp(c->telephone, "04 22 33 44 55")==0);
            TEST(strcmp(c->type, "Americain")==0);
            TEST(size(c->menu)==2);
            TEST(c->solde==44.);

            TEST(get_first_id(begin(&restos), end(&restos)) == 4);

            TEST(ajout_resto("empburger", 82517, "06 53 12 89 75", "Fast Food", &restos) == 4);
            TEST(ajout_resto("ALEXA donne un nom à mon resto jsp n'importe quoi", 83962, "06 89 48 35 36", "Italien", &restos) == -1);
            TEST(ajout_resto("l'erreur du midi", 65471, "07 53 20 45 A6", "Bistro", &restos) == -2);
            TEST(ajout_resto("japan service", 75000, "06 46 21 47 00", "B@r m@aid", &restos) == -3);
            TEST(ajout_resto("suspect", 99254, "06 44 25 01 47 12", "Detective", &restos) == -2);

            TEST(size(restos) == 5);

            sauvegarde_resto(begin(&restos), end(&restos));

            TEST_FILE("db_restaurants.csv", "test/db_resto_final.csv");

            destroy(&restos);
        }

        // test lecture_livreur() + sauvegarde_livreurs()
        {
            vector livreurs=lecture_livreur("test/db_livreurs.csv");

            TEST(size(livreurs)==3);

            Livreur const* d=(Livreur*)(begin(&livreurs).element);

            TEST(d->id==1);
            TEST(strcmp(d->nom,"Francois Pignon")==0);
            TEST(strcmp(d->telephone,"06 00 00 00 00")==0);
            TEST(size(d->deplacements)==3);
            TEST(d->restaurant==1);
            TEST(d->solde==20.);

            int * deplacement=(int*)(at(&d->deplacements,0).element);
            TEST(*deplacement==13001);
            deplacement=(int*)(at(&d->deplacements,1).element);
            TEST(*deplacement==13002);
            deplacement=(int*)(at(&d->deplacements,2).element);
            TEST(*deplacement==13003);

            TEST(get_first_id(begin(&livreurs), end(&livreurs)) == 4);

            vector restos = lecture_restaurant("db_restaurants.csv");

            TEST(ajout_livreur("Jean Frederic", "06 82 26 72 34", "65408;12300;20145", 0, restos, &livreurs)==4);
            TEST(ajout_livreur("Johnny Hardbook", "07 08 86 14 89", "89145;83560", 4, restos, &livreurs)==5);
            TEST(ajout_livreur("Charlie", "07 06 05 04 03", "80456", 6, restos, &livreurs))

            sauvegarde_livreurs(begin(&livreurs), end(&livreurs));
            TEST_FILE("db_livreurs.csv", "test/db_livreurs.csv");

            destroy(&livreurs);
        }

        // test lecture_menu() + sauvegarde_menus()
        {
            vector menus=lecture_menu("test/db_menus.csv");

            TEST(size(menus)==8);

            Menu const* item=(Menu*)(begin(&menus).element);

            TEST(item->id==1);
            TEST(strcmp(item->nom, "bouillabaise")==0);
            TEST(size(item->ingredients)==2);
            TEST(item->prix==25.);

            TEST(get_first_id(begin(&menus), end(&menus)) == 9);

            TEST(ajout_menu("chicken nuggets", "poulet;farine;huile", 2.5, &menus)==9);
            TEST(ajout_menu("salade de fruits", "fruits mixtes", 3.5, &menus)==10);
            TEST(ajout_menu("nothing", "", 100, &menus)==-2);
            TEST(ajout_menu("free stuff", "free;peanut", 0., &menus)==11);
            TEST(ajout_menu("something", "aze;dza", -1., &menus)==-3);
            TEST(ajout_menu("le 13", "leza;le12",-2., &menus)==-2);

            TEST(size(menus)==11);

            sauvegarde_menus(begin(&menus), end(&menus));
            TEST_FILE("db_menus.csv", "test/db_menu_final.csv");

            destroy(&menus);
        }
    }

    // test functions
    {
        TEST(isnom("Bar maid")==1);
        TEST(isnom("")==0);
        TEST(isnom("      ")==0);
        TEST(isnom("AS  S")==0);
        TEST(isnom("A S S")==1);
        TEST(isnom("Sushi")==1);
        TEST(isnom("pIzZA")==1);
        TEST(isnom("poids chiche")==1);
        TEST(isnom("B@r")==0);
        TEST(isnom("P3t1t")==0);
        TEST(isnom("yamana113")==0); // :(
        TEST(isnom("l'entièreté des bouquin d'Harry Potter parcequ'ils sont trop longs")==0);
        TEST(isnom("Joe s International House of Pancakes")==1);

        TEST(isunder39("Joe's International House of Pancakes")==1);
        TEST(isunder39("Jonny's International House of Pancakes")==1);
        TEST(isunder39("Jonnathan's International House of Pancakes")==0);

        TEST(istel("10 02 52 66 45")==1);
        TEST(istel("07 52 14 89 63")==1);
        TEST(istel("28 71 1 78 28 ")==0);
        TEST(istel("18 174 15 01 4")==0);
        TEST(istel("")==0);
        TEST(istel("1")==0);
        TEST(istel("dz ap os ke is")==0);
        TEST(istel("14 55 01 4a 04")==0);
        TEST(istel("@& _è *µ ^¨ çà")==0);
        TEST(istel("14 25 36 87 69 ")==0);
        TEST(istel("01 23 45 67 8")==0);
    }

    // test relation menu_resto
    {
        vector restos=lecture_restaurant("db_restaurants.csv");
        vector menus=lecture_menu("db_menus.csv");

        TEST(menu_resto(8, (Restaurant*)(at(&restos, 3).element), menus)==1);
        TEST(menu_resto(9, (Restaurant*)(at(&restos, 3).element), menus)==1);
        TEST(menu_resto(13, (Restaurant*)(at(&restos, 3).element), menus)==0);
        TEST(menu_resto(36, (Restaurant*)(at(&restos, 3).element), menus)==0);

        Restaurant * resto =(Restaurant*)(at(&restos, 3).element);
        TEST(resto->id==4);
        TEST(size(resto->menu)==2);
      
        TEST(*((size_t*)(at(&(resto->menu), 0).element))==8);
        TEST(*((size_t*)(at(&(resto->menu), 1).element))==9);

        destroy(&restos);
        destroy(&menus);
    }

    //test id_search
    {
        vector restos=lecture_restaurant("test/db_restaurants.csv");

        Restaurant comp_resto;
        comp_resto.id=1;
        TEST(id_search(begin(&restos), end(&restos), &comp_resto, idresto_compare));
        comp_resto.id=2;
        TEST(id_search(begin(&restos), end(&restos), &comp_resto, idresto_compare)==2);
        comp_resto.id=5;
        TEST(id_search(begin(&restos), end(&restos), &comp_resto, idresto_compare)==4);
        comp_resto.id=4;
        TEST(!id_search(begin(&restos), end(&restos), &comp_resto, idresto_compare));

        destroy(&restos);
        
        vector menus=lecture_menu("test/db_menu_final.csv");
        Menu comp_menu;
        comp_menu.id=9;
        TEST(id_search(begin(&menus), end(&menus), &comp_menu, idmenu_compare)==9);
        comp_menu.id=10;
        TEST(id_search(begin(&menus), end(&menus), &comp_menu, idmenu_compare)==10);
        comp_menu.id=11;
        TEST(id_search(begin(&menus), end(&menus), &comp_menu, idmenu_compare)==11);
        comp_menu.id=12;
        TEST(id_search(begin(&menus), end(&menus), &comp_menu, idmenu_compare)==0);
        comp_menu.id=-12;
        TEST(!id_search(begin(&menus), end(&menus), &comp_menu, idmenu_compare));

        destroy(&menus);

        vector livreurs=lecture_livreur("test/db_livreurs.csv");
        Livreur comp_livreur;
        comp_livreur.id=1;
        TEST(id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare)==1);
        comp_livreur.id=2;
        TEST(id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare)==2);
        comp_livreur.id=3;
        TEST(id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare)==3);
        comp_livreur.id=135;
        TEST(id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare)==0);
        comp_livreur.id=0;
        TEST(id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare)==0);
        comp_livreur.id=-1;
        TEST(id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare)==0);

        destroy(&livreurs);
    }

    return tests_executed - tests_successful;
}