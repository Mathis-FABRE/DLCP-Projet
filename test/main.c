#include "gestionfichier.h"
#include "db.h"
#include "algorithm.h"

#include "test_harness/test_harness.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Valeurs pour le harnais de test spécifiques à ce programme.
// augmenter cette val à chaque test créer
int const tests_total = 42;

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

            TEST(get_first_id(&clients) == 4);

            sauvegarde_clients(begin(&clients), end(&clients));

            TEST_FILE("db_clients.csv","test/db_clients.csv")

            destroy(&clients);
        }

        // test de separateur_chaine()
        {
            vector menus=make_vector(sizeof(size_t),0,growth_factor);

            separateur_chaine(&menus, "1;2;3");

            TEST(size(menus)==3);

            for (size_t i = 0; i < 3; i++)
            {
                size_t const* id=(size_t*)(at(&menus, i).element);
                TEST(*id==i+1);
            }

            destroy(&menus);
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

            TEST(get_first_id(&restos) == 4);

            sauvegarde_resto(begin(&restos), end(&restos));

            TEST_FILE("db_restaurants.csv", "test/db_restaurants.csv");

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

            sauvegarde_livreurs(begin(&livreurs), end(&livreurs));
            TEST_FILE("db_livreurs.csv", "test/db_livreurs.csv");

            destroy(&livreurs);
        }

        // test lecture_menu() + sauvegarde_menus()
        {
            vector dbmenus=lecture_menu("test/db_menus.csv");

            TEST(size(dbmenus)==8);

            Menu const* item=(Menu*)(begin(&dbmenus).element);

            TEST(item->id==1);
            TEST(strcmp(item->nom, "bouillabaise")==0);
            TEST(size(item->ingredients)==2);
            TEST(item->prix==25.);

            sauvegarde_menus(begin(&dbmenus), end(&dbmenus));
            TEST_FILE("db_menus.csv", "test/db_menus.csv");

            destroy(&dbmenus);
        }
    }

    return tests_executed - tests_successful;
}