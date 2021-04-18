#include "gestionfichier.h"
#include "db.h"

#include "test_harness/test_harness.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Valeurs pour le harnais de test spécifiques à ce programme.
// augmenter cette val à chaque test créer
int const tests_total = 21;

int const test_column_width = 80;

int main()
{
    float const growth_factor=2.;

    check();

    vector clients=lecture_client();

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

    destroy(&clients);

    vector menus=make_vector(sizeof(size_t),0,growth_factor);

    separateur_chaine(&menus, "1;2;3");

    TEST(size(menus)==3);

    for (size_t i = 0; i < 3; i++)
    {
        size_t const* id=(size_t*)(at(&menus, i).element);
        TEST(*id==i+1);
    }

    destroy(&menus);
    
    vector restos=lecture_restaurant();

    TEST(size(restos)==3);

    Restaurant const* c=(Restaurant*)(at(&restos, 2).element);

    TEST(c->id==3);
    TEST(strcmp(c->nom, "Joe's International House of Pancakes")==0);
    TEST(c->code_postal==13010);
    TEST(strcmp(c->telephone, "04 22 33 44 55")==0);
    TEST(strcmp(c->type, "Americain")==0);
    TEST(size(c->menu)==2);
    TEST(c->solde==44.);

    destroy(&restos);

    return tests_executed - tests_successful;
}