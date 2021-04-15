#include "db.h"

#include "vector_api.h"
#include "vector_types.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>


/* vector lecture_table(
    FILE* file)
{
    vector vect = make_vector(sizeof(client), 0, 2.);
    // buffer et séparateurs pour split la chaine
    char string[1024], del[] = ",";
    while(fgets(string, 1024, file))
    {
        // on coupe la chaine au premier délimiteur rencontré avec strtok
        char *index_s = strtok(string, del);

        // on transforme la chaine obtenue en size_t 
        size_t index;
        sscanf(index_s, "%zu" ,&index);

        // on split au prochain del
        // note: on part de NULL car strtok place un NULL après chaque délimiteur lorsqu'il coupe la chaine
        char * temp = strtok(NULL, del);

        // on coupe puis on sauvegarde en tant qu'entier
        char *spe_s = strtok(NULL, del);
        int spe;
        sscanf(spe_s, "%d" ,&spe);

        // on coupe puis on sauvegarde en tant que size_t
        char *index_hopital_s= strtok(NULL, del);
        size_t index_hopital;
        sscanf(index_hopital_s, "%zu" ,&index_hopital);
        
        // création du docteur
        docteur doct = (docteur){
            .index = index,
            .specialites = spe,
            .index_hopital = index_hopital
        };
        strcpy(doct.nom, temp);

        // on le range dans le vecteur
        push_back(&vect, &doct);
    }

    return vect;
}

void ecriture_table(
    FILE* file,
    vector const* db)
{
     for (iterator i = begin(db), e = end(db); compare(i, e) != 0; increment(&i, 1))
    {
        docteur *doc = i.element;
        fprintf(file, "%zu,%s,%d,%zu\n", doc->index, doc->nom, doc->specialites, doc->index_hopital);
    }
}

bool est_generaliste(
    void const* d)
{
    docteur *doc = (docteur *) d;
    // Lien utile pour le test : https://www.oreilly.com/library/view/c-cookbook/0596003390/ch04s06.html
    enum specialite_t specialite = doc->specialites;
    if ((specialite & MEDECINE_GENERALE) == MEDECINE_GENERALE)    
        return true;

    return false;
} */