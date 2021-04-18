#include "gestionfichier.h"
#include "db.h"

#include "test_harness/test_harness.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Valeurs pour le harnais de test spécifiques à ce programme.
// augmenter cette val à chaque test créer
int const tests_total = 9;

int const test_column_width = 80;

int main()
{
    // float const growth_factor=2.;

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

    return tests_executed - tests_successful;
}