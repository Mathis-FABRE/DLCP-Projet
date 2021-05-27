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

int const tests_total = 352;

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

            // Test code erreur : -1
            TEST(ajout_client("Bob L'Eponge", "13050", "04 10 20 30 40",-10, &clients) == -1);
            TEST(ajout_client("Bob Le  Bricoleur", "13050", "04 10 20 30 40",-10, &clients) == -1);
            TEST(ajout_client("Le meilleur restaurant au monde que vous n'avez jamais vu", "13050", "04 10 20 30 40",-10, &clients) == -1);

            // // Test code erreur : -2
            TEST(ajout_client("Chez Brian", "1305X", "04 10 20 30 40",-10, &clients) == -2);
            TEST(ajout_client("Chez Brian", "130500", "04 10 20 30 40",-10, &clients) == -2);
            TEST(ajout_client("Chez Brian", "1305", "04 10 20 30 40",-10, &clients) == -2);

            // // Test code erreur : -3
            TEST(ajout_client("Chez Brian", "13050", "04 10 20 30 4X",-10, &clients) == -3);
            TEST(ajout_client("Chez Brian", "13050", "04 10 20 30",-10, &clients) == -3);
            TEST(ajout_client("Chez Brian", "13050", "+334 10 20 30 41",-10, &clients) == -3);

            TEST(ajout_client("Brian May","13009","06 66 35 45 25",-10, &clients) == 4);

            TEST(size(clients) == 4);

            sauvegarde_clients(begin(&clients), end(&clients));

            TEST_FILE("db_clients.csv","test/db_clients_final.csv")

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
            TEST(ajout_livreur("Johnny Hardbook", "07 08 86 14 89", "82517;83560", 4, restos, &livreurs)==5);
            TEST(ajout_livreur("Charlie", "07 06 05 04 03", "80456", 6, restos, &livreurs)==-4);
            TEST(ajout_livreur("Charlie", "07 06 05 04 03", "80456", -1, restos, &livreurs)==-4);
            TEST(ajout_livreur("Aribiek@ zarbie", "07 39 18 20 48", "89470", 3, restos, &livreurs)==-1);
            TEST(ajout_livreur("Juju", "06 72 9a 74 95", "98107;18206;17820;39504", 0, restos, &livreurs)==-2);
            TEST(ajout_livreur("Mr Nowhere", "05 40 93 04 59", "", 0, restos, &livreurs)==-3);
            TEST(ajout_livreur("Mr Worldwide", "17 28 39 46 05", "theworld", 0, restos, &livreurs)==-3);
            TEST(ajout_livreur("Mr Worldwide", "17 28 39 46 05", "83740;theworld", 0, restos, &livreurs)==-3);
            TEST(ajout_livreur("ajin", "93 64 28 57 01", "18257", 3, restos, &livreurs)==-5);

            sauvegarde_livreurs(begin(&livreurs), end(&livreurs));
            TEST_FILE("db_livreurs.csv", "test/db_livreur_final.csv");

            destroy(&livreurs);
        }

            // Tests liste_resto et liste_items
        {
            
            vector livreurs = lecture_livreur("test/db_livreurs.csv");
            vector menus = lecture_menu("test/db_menus.csv");
            vector restos = lecture_restaurant("test/db_restaurants.csv");

            vector liste = liste_resto(0, &restos, &livreurs, NULL, NULL);
            
            TEST(size(liste) == 4);
            // tests "peut me livrer"
            
            liste = liste_resto(13001, &restos, &livreurs, NULL, NULL);

            Restaurant *restaurant = (Restaurant *)(begin(&liste).element);
            TEST(strcmp(restaurant->nom, "Chez Michel") == 0);

            TEST(size(liste) == 1);

            TEST( ajout_resto("Reste Tôt", 13009, "06 51 12 69 57", "Fast Food", &restos) == 4);

            restaurant = (Restaurant *)at(&restos, 3).element;
            TEST(add_menu(2, restaurant, menus) == 1);
            TEST(add_menu(8, restaurant, menus) == 1);
            TEST(strcmp(restaurant->nom, "Reste Tôt") == 0)
            TEST(size(restaurant->menu) == 2);

            TEST( ajout_resto("Dindo Marrons", 13009, "06 23 72 89 75", "Francais", &restos) == 6);

            restaurant = (Restaurant *)at(&restos, 5).element;
            TEST(strcmp(restaurant->nom, "Dindo Marrons") == 0)
            TEST(add_menu(7, restaurant, menus) == 1);
            TEST(size(restaurant->menu) == 1);

            liste = liste_resto(13009, &restos, &livreurs, NULL, NULL);
            TEST(size(liste) == 2);

            // tests "type de cuisine"

            liste = liste_resto(0, &restos, &livreurs, "Fast Food", NULL);
            TEST(size(liste) == 2);

            liste = liste_resto(0, &restos, &livreurs, "Americain", NULL);
            TEST(size(liste) == 1);

            liste = liste_resto(0, &restos, &livreurs, "Francais", NULL);
            TEST(size(liste) == 1);

            liste = liste_resto(0, &restos, &livreurs, "Vegetarien", NULL);
            TEST(size(liste) == 1);

            // tests "peut me livrer" + "type de cuisine"

            liste = liste_resto(13009, &restos, &livreurs, "Fast Food", NULL);
            restaurant = (Restaurant *)(begin(&liste).element);
            TEST(strcmp(restaurant->nom, "Reste Tôt") == 0);
            TEST(size(liste) == 1);

            liste = liste_resto(13003, &restos, &livreurs, "Provencal", NULL);
            restaurant = (Restaurant *)(begin(&liste).element);
            TEST(strcmp(restaurant->nom, "Chez Michel") == 0);
            TEST(size(liste) == 1);

            liste = liste_resto(0, &restos, &livreurs, NULL, "Chez Michel");
            restaurant = (Restaurant *)(begin(&liste).element);
            TEST(strcmp(restaurant->nom, "Chez Michel") == 0);
            TEST(size(liste) == 1);

            liste = liste_resto(0, &restos, &livreurs, "Provencal", "Chez Michel");
            restaurant = (Restaurant *)(begin(&liste).element);
            TEST(strcmp(restaurant->nom, "Chez Michel") == 0);
            TEST(size(liste) == 1);

            destroy(&liste);

            // tests liste_items

            // tous les menus
            liste = liste_items(0, &restos, &livreurs, &menus, NULL, NULL, 0);
            TEST(size(liste) == 8);

            // tous les menus moins chers que 20€
            liste = liste_items(0, &restos, &livreurs, &menus, NULL, NULL, 20);
            TEST(size(liste) == 7);

            // tous les menus moins chers que 10€ ou à 10€
            liste = liste_items(0, &restos, &livreurs, &menus, NULL, NULL, 10);
            TEST(size(liste) == 5);

            // tous les menus de Chez Michel
            liste = liste_items(0, &restos, &livreurs, &menus, NULL, "Chez Michel", 0);
            TEST(size(liste) == 3);

            // tous les menus de Chez Michel
            liste = liste_items(0, &restos, &livreurs, &menus, NULL, "Five Guys", 0);
            TEST(size(liste) == 1);

            // tous les menus disponibles en 13009
            liste = liste_items(13009, &restos, &livreurs, &menus, NULL, NULL, 0);
            TEST(size(liste) == 3);

            // tous les menus disponibles en 13009 chez Reste Tôt
            liste = liste_items(13009, &restos, &livreurs, &menus, NULL, "Reste Tôt", 0);
            TEST(size(liste) == 2);

            // tous les menus disponibles en 13009 chez Reste Tôt à moins de 5 euros
            liste = liste_items(13009, &restos, &livreurs, &menus, NULL, "Reste Tôt", 5);
            TEST(size(liste) == 1);

            destroy(&liste);
            destroy(&restos);
            destroy(&menus);
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

        TEST(iscode("")      == 0);
        TEST(iscode("1")     == 0);
        TEST(iscode("11")    == 0);
        TEST(iscode("111")   == 0);
        TEST(iscode("1111")  == 0);
        TEST(iscode("X1111") == 0);
        TEST(iscode("XXXXX") == 0);
        TEST(iscode("1111X") == 0);
        TEST(iscode("0x110") == 0);
        TEST(iscode("Marseille") == 0);
        TEST(iscode("Paris") == 0)
        TEST(iscode("11111") == 1);
        TEST(iscode("13009") == 1);
    }

    // test relation add_menu del_menu
    {
        vector restos=lecture_restaurant("db_restaurants.csv");
        vector menus=lecture_menu("db_menus.csv");

        TEST(add_menu(9, (Restaurant*)(at(&restos, 3).element), menus) == 1);
        TEST(add_menu(8, (Restaurant*)(at(&restos, 3).element), menus) == 1);
        TEST(add_menu(13, (Restaurant*)(at(&restos, 3).element), menus) == -1);
        TEST(add_menu(36, (Restaurant*)(at(&restos, 3).element), menus) == -1);
        TEST(add_menu(-1, (Restaurant*)(at(&restos, 3).element), menus) == -1);
        TEST(add_menu(9, (Restaurant*)(at(&restos, 3).element), menus) == -2);
        TEST(add_menu(8, (Restaurant*)(at(&restos, 3).element), menus) == -2);
        TEST(add_menu(7, (Restaurant*)(at(&restos, 2).element), menus) == -2);

        Restaurant * resto =(Restaurant*)(at(&restos, 3).element);
        TEST(resto->id==4);
        TEST(size(resto->menu)==2);
      
        TEST(*((size_t*)(at(&(resto->menu), 0).element))==8);
        TEST(*((size_t*)(at(&(resto->menu), 1).element))==9);

        resto =(Restaurant*)(at(&restos, 2).element);
        TEST(resto->id==3);
        TEST(size(resto->menu)==2);

        TEST(*((size_t*)(at(&(resto->menu), 0).element))==6);
        TEST(*((size_t*)(at(&(resto->menu), 1).element))==7);

        TEST(del_menu(at(&restos, 3), 8) == 1);

        resto =(Restaurant*)(at(&restos, 3).element);

        TEST(resto->id == 4);
        TEST(size(resto->menu)==1);
        TEST(*((size_t*)(at(&resto->menu, 0).element)) == 9);

        TEST(del_menu(at(&restos, 3), 9) == 1);

        TEST(size(resto->menu)==0);

        TEST(del_menu(at(&restos, 2), 7) == 1);

        resto =(Restaurant*)(at(&restos, 2).element);

        TEST(resto->id == 3);
        TEST(size(resto->menu)==1);
        TEST(*((size_t*)(at(&resto->menu, 0).element)) == 6);

        TEST(del_menu(at(&restos, 2), -6) == 0);
        TEST(del_menu(at(&restos, 2), 0) == 0);
        TEST(del_menu(at(&restos, 2), 9) == 0);
        TEST(del_menu(at(&restos, 2), 1) == 0);

        TEST(size(resto->menu) == 1);

        TEST(del_menu(at(&restos, 3), 0) == 0);
        TEST(del_menu(at(&restos, 3), -9) == 0);
        TEST(del_menu(at(&restos, 3), 1) == 0);
        TEST(del_menu(at(&restos, 3), 8) == 0);
        TEST(del_menu(at(&restos, 3), 9) == 0);

        resto =(Restaurant*)(at(&restos, 3).element);

        TEST(size(resto->menu) == 0);

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


    // test del_livreur
    {
        vector livreurs = lecture_livreur("db_livreurs.csv");

        Livreur comp_livreur;
        comp_livreur.id=1;
        del_livreur(&livreurs, at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare)-1));
        TEST(size(livreurs) == 4);
        TEST(get_first_id(begin(&livreurs), end(&livreurs)) == 1);

        Livreur * test = (Livreur*)(at(&livreurs, 2).element);
        TEST(test->id == 4);

        comp_livreur.id=4;
        del_livreur(&livreurs, at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare)-1));
        TEST(size(livreurs) == 3);
        TEST(id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) == 0);

        test = (Livreur*)(at(&livreurs, 2).element);
        TEST(test->id == 5);

        comp_livreur.id=5;
        del_livreur(&livreurs, at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare)-1));
        TEST(size(livreurs) == 2);
        TEST(id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) == 0);

        test = (Livreur*)(at(&livreurs, 1).element);
        TEST(test->id == 3);
        test = (Livreur*)(at(&livreurs, 0).element);
        TEST(test->id == 2);
    }

    // test modif_livreur
    {
        vector livreurs = lecture_livreur("db_livreurs.csv");
        vector restos = lecture_restaurant("db_restaurants.csv");

        Livreur comp_livreur;

        // modif_livreur_resto
        comp_livreur.id = 2;
        TEST(modif_livreur_resto(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 3, restos) == 1);
        Livreur * test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 2);
        TEST(test->restaurant == 3);

        TEST(ajout_resto("la nouvelle cuisine", 13011, "08 07 05 04 03", "Gastronomique", &restos) == 6);
        TEST(size(restos) == 6);
        Restaurant comp_resto;
        comp_resto.id = 6;
        TEST(id_search(begin(&restos), end(&restos), &comp_resto, idresto_compare) == 5+1);

        comp_livreur.id = 3;
        TEST(modif_livreur_resto(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 6, restos) == 1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 3);
        TEST(test->restaurant == 6);

        comp_livreur.id = 1;
        TEST(modif_livreur_resto(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 5, restos) == -2);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 1);
        TEST(test->restaurant == 1);

        comp_livreur.id = 2;
        TEST(modif_livreur_resto(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 9, restos) == -1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 2);
        TEST(test->restaurant == 3);

        comp_livreur.id = 3;
        TEST(modif_livreur_resto(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), -1, restos) == -1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 3);
        TEST(test->restaurant == 6);

        comp_livreur.id = 3;
        TEST(modif_livreur_resto(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 3, restos) == 1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 3);
        TEST(test->restaurant == 3);

        comp_livreur.id = 3;
        TEST(modif_livreur_resto(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 6, restos) == 1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 3);
        TEST(test->restaurant == 6);

        comp_livreur.id = 5;
        TEST(modif_livreur_resto(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 0, restos) == 1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 5);
        TEST(test->restaurant == 0);

        comp_livreur.id = 5;
        TEST(modif_livreur_resto(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 0, restos) == 1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 5);
        TEST(test->restaurant == 0);

        comp_livreur.id = 5;
        TEST(modif_livreur_resto(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 4, restos) == 1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 5);
        TEST(test->restaurant == 4);

        // modif_livreur_delcode
        comp_livreur.id = 2;
        TEST(modif_livreur_delcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 1, restos) == 1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 2);
        TEST(size(test->deplacements) == 5);
        TEST(*(int*)(at(&test->deplacements, 0).element) == 13004);

        comp_livreur.id = 2;
        TEST(modif_livreur_delcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 3, restos) == 1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 2);
        TEST(size(test->deplacements) == 4);
        TEST(*(int*)(at(&test->deplacements, 2).element) == 13009);

        comp_livreur.id = 4;
        TEST(modif_livreur_delcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 3, restos) == 1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 4);
        TEST(size(test->deplacements) == 2);
        TEST(*(int*)(at(&test->deplacements, 2 - 1).element) == 12300);

        comp_livreur.id = 3;
        TEST(modif_livreur_delcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 0, restos) == -1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 3);
        TEST(size(test->deplacements) == 4);

        comp_livreur.id = 3;
        TEST(modif_livreur_delcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), -1, restos) == -1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 3);
        TEST(size(test->deplacements) == 4);

        comp_livreur.id = 3;
        TEST(modif_livreur_delcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 10, restos) == -1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 3);
        TEST(size(test->deplacements) == 4);

        comp_livreur.id = 3;
        TEST(modif_livreur_delcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 5, restos) == -1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 3);
        TEST(size(test->deplacements) == 4);

        comp_livreur.id = 2;
        TEST(modif_livreur_delcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 4, restos) == -2);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 2);
        TEST(size(test->deplacements) == 4);

        comp_livreur.id = 2;
        TEST(modif_livreur_delcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 4, restos) == -2);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 2);
        TEST(size(test->deplacements) == 4);

        comp_livreur.id = 3;
        TEST(modif_livreur_delcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 4, restos) == -2);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 3);
        TEST(size(test->deplacements) == 4);

        comp_livreur.id = 5;
        TEST(modif_livreur_delcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 1, restos) == -2);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 5);
        TEST(size(test->deplacements) == 2);

        // modif_livreur_addcode
        comp_livreur.id = 1;
        TEST(modif_livreur_addcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 13009) == 1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 1);
        TEST(size(test->deplacements) == 4);
        TEST(*(int*)(at(&test->deplacements, 4-1).element) == 13009);

        comp_livreur.id = 4;
        TEST(modif_livreur_addcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 13007) == 1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 4);
        TEST(size(test->deplacements) == 3);
        TEST(*(int*)(at(&test->deplacements, 3-1).element) == 13007);

        comp_livreur.id = 3;
        TEST(modif_livreur_addcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 13006) == 1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 3);
        TEST(size(test->deplacements) == 5);
        TEST(*(int*)(at(&test->deplacements, 5-1).element) == 13006);

        comp_livreur.id = 3;
        TEST(modif_livreur_addcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 13004) == 1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 3);
        TEST(size(test->deplacements) == 6);
        TEST(*(int*)(at(&test->deplacements, 6-1).element) == 13004);

        comp_livreur.id = 5;
        TEST(modif_livreur_addcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 130069) == -1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 5);
        TEST(size(test->deplacements) == 2);

        comp_livreur.id = 5;
        TEST(modif_livreur_addcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), -130069) == -1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 5);
        TEST(size(test->deplacements) == 2);

        comp_livreur.id = 1;
        TEST(modif_livreur_addcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), -13006) == -1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 1);
        TEST(size(test->deplacements) == 4);

        comp_livreur.id = 1;
        TEST(modif_livreur_addcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 01) == -1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 1);
        TEST(size(test->deplacements) == 4);

        comp_livreur.id = 2;
        TEST(modif_livreur_addcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 13010) == -2);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 2);
        TEST(size(test->deplacements) == 4);

        comp_livreur.id = 3;
        TEST(modif_livreur_addcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 13011) == -2);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 3);
        TEST(size(test->deplacements) == 6);

        comp_livreur.id = 4;
        TEST(modif_livreur_resto(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 5, restos) == 1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 4);
        TEST(test->restaurant == 5);

        // modif_livreur_tel
        comp_livreur.id = 5;
        TEST(modif_livreur_tel(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), "07 09 63 85 49") == 1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 5);
        TEST(strcmp(test->telephone, "07 09 63 85 49") == 0);

        comp_livreur.id = 1;
        TEST(modif_livreur_tel(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), "07 08 74 62 10") == 1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 1);
        TEST(strcmp(test->telephone, "07 08 74 62 10") == 0);

        comp_livreur.id = 2;
        TEST(modif_livreur_tel(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), "07 08 74 62 1") == -1);
        test = (Livreur*)(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1).element);
        TEST(test->id == 2);
        TEST(strcmp(test->telephone, "06 01 02 03 04") == 0);
    }

    // test del_resto
    {
        vector livreurs = lecture_livreur("db_livreurs.csv");
        vector restos = lecture_restaurant("db_restaurants.csv");

        Livreur comp_livreur;
        comp_livreur.id = 3;
        modif_livreur_addcode(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 13001);
        modif_livreur_resto(at(&livreurs, id_search(begin(&livreurs), end(&livreurs), &comp_livreur, idlivreur_compare) - 1), 1, restos);

        del_resto(&restos, at(&restos, 0), &livreurs);
        TEST(size(restos) == 4);
        TEST(size(livreurs) == 5);

        TEST(get_first_id(begin(&restos), end(&restos)) == 1);

        TEST(((Livreur*)(at(&livreurs, 0).element))->restaurant == 0);
        TEST(((Livreur*)(at(&livreurs, 2).element))->restaurant == 0);

        del_resto(&restos, at(&restos, 2), &livreurs);

        TEST(((Restaurant*)(at(&restos, 2).element))->id == 5);

        TEST(size(restos) == 3);
        TEST(size(livreurs) == 5);

        TEST(((Livreur*)(at(&livreurs, 0).element))->restaurant == 0);
        TEST(((Livreur*)(at(&livreurs, 2).element))->restaurant == 0);
        TEST(((Livreur*)(at(&livreurs, 4).element))->restaurant == 0);

        modif_livreur_resto(at(&livreurs, 1), 2, restos);
        
        del_resto(&restos, at(&restos, 2), &livreurs);

        TEST(size(restos) == 2);
        TEST(size(livreurs) == 5);

        TEST(((Livreur*)(at(&livreurs, 0).element))->restaurant == 0);
        TEST(((Livreur*)(at(&livreurs, 1).element))->restaurant == 2);
        TEST(((Livreur*)(at(&livreurs, 2).element))->restaurant == 0);
        TEST(((Livreur*)(at(&livreurs, 4).element))->restaurant == 0);
    }

    // test binary_search
    {
        vector numbers = make_vector(sizeof(int), 0, 2.);

        int n = 1;
        push_back(&numbers, &n);
        push_back(&numbers, &n);
        push_back(&numbers, &n);
        n = 22;
        push_back(&numbers, &n);
        push_back(&numbers, &n);
        n = 99;
        push_back(&numbers, &n);

        iterator const b = begin(&numbers), e = end(&numbers);
        n = 1;
        TEST(binary_search(b, e, &n, numerical_compare) == true);
        n = 22;
        TEST(binary_search(b, e, &n, numerical_compare) == true);
        n = 99;
        TEST(binary_search(b, e, &n, numerical_compare) == true);
        n = 0;
        TEST(binary_search(b, e, &n, numerical_compare) == false);
        n = 100;
        TEST(binary_search(b, e, &n, numerical_compare) == false);

        iterator fourth = at(&numbers, 3);
        n = 1;
        TEST(binary_search(fourth, e, &n, numerical_compare) == false);
        n = 22;
        TEST(binary_search(b, fourth, &n, numerical_compare) == false);
    }

    return tests_executed - tests_successful;
}