// These test macros and functions have been collected in this header file to 
// keep 'main.c' as free as possible from distractions beyond tests content.
// It is expected that this header file is only included from 'main.c' otherwise 
// symbols will be duplicated.

#pragma once

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nombre total de tests.
extern int const tests_total;

// Nombre total de tests exécutés. 
int tests_executed = 0;

// Pour chaque test qui réussi, cette variable sera incrémentée de 1.
// Le but est de la garder égale à test_executes.
int tests_successful = 0;

// Largeur de la colonne d'affichage de test.
extern int const test_column_width;

// Incrémente le nombre de test exécutés de 1.
// Si le test réussi, incrémente le nombre de tests réussis de 1.
#define TEST(x) printf("%s:%d:0 %*s : ", __FILE__, __LINE__, __LINE__ < 100 ? -test_column_width - 1 : -test_column_width, #x); \
                tests_executed += 1;        \
                if(x)                       \
                {                           \
                    tests_successful += 1;  \
                    printf("[SUCCES]\n");   \
                }                           \
                else                        \
                {                           \
                    printf("[ECHEC]\n");    \
                }

// Incrémente le nombre de test exécutés de 1.
// Compare le contenu de deux fichiers aux chemins a et b avec la commande diff.
// Si les fichiers sont pareils, incrémente le nombre de tests réussis de 1.
#define TEST_FILE(a, b) printf("%s:%d:0 %s %s %s : ", __FILE__, __LINE__, "diff --text --strip-trailing-cr", a, b);   \
                        tests_executed += 1;            \
                        {                               \
                            int const r = system("diff --text --strip-trailing-cr " a " " b " > /dev/null");    \
                            if(!WEXITSTATUS(r))         \
                            {                           \
                                tests_successful += 1;  \
                                printf("[SUCCES]\n");   \
                            }                           \
                            else                        \
                            {                           \
                                printf("[ECHEC]\n");    \
                            }                           \
                        }

// Affiche le sommaire des résultats des tests.
void __attribute__((destructor)) print_summary()
{
    printf("---\nNombre de tests\t:%3d\nTests executes\t:%3d\nTests reussis\t:%3d\n", tests_total, tests_executed, tests_successful);
}

// Fonction à executer lors d'un signal.
// Affiche le code du signal et arrête immédiatement le programme.
void signal_handler(int signal)
{
    printf("[FATAL(%d)]\n", signal);
    exit(tests_total - tests_successful);
}

// Mise en place de la fonction à exécuter lors de signaux (de détresse).
void __attribute__((constructor)) install_signal_handler()
{
    struct sigaction sa;
    memset(&sa, 0, sizeof(struct sigaction));
    sigemptyset(&sa.sa_mask);
    sa.sa_handler = signal_handler;
    for(int signals[] = {SIGABRT, SIGBUS, SIGFPE, SIGILL, SIGINT, SIGSEGV}, i = 0; i != sizeof(signals) / sizeof(int); ++i)
    {
        sigaction(signals[i], &sa, NULL);
    }
}
