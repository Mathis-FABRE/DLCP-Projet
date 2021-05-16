#include "algorithm.h"
#include "db.h"

#include "vector_api.h"
#include "vector_types.h"

#include <stdbool.h>
#include <stddef.h>
#include <string.h>


bool all_of(
    iterator first,
    iterator last,
    bool (*predicate)(void const *data))
{
    iterator current = first;
    bool test = true;
    while (current.element != last.element && test == true)
    {
        test = predicate(current.element);
        increment(&current, 1);
    }

    return test;
}

bool any_of(
    iterator first,
    iterator last,
    bool (*predicate)(void const *data))
{
    iterator current = first;
    bool test = false;
    while (current.element != last.element && test == false)
    {
        test = predicate(current.element);
        increment(&current, 1);
    }

    return test;
}

bool none_of(
    iterator first,
    iterator last,
    bool (*predicate)(void const *data))
{
    iterator current = first;
    bool test = false;
    while (current.element != last.element && test == false)
    {
        test = predicate(current.element);
        increment(&current, 1);
    }

    if (test == false)
        return true;
    else
        return false;
}

void for_each(
    iterator first,
    iterator last,
    void (*unary_operation)(void *data))
{
    for (iterator i = first, e = last; compare(i, e) != 0; increment(&i, 1))
    {
        unary_operation(i.element);
    }
}

size_t count_if(
    iterator first,
    iterator last,
    bool (*unary_operation)(void const *data))
{
    // On utilise un compteur qui compte le nombre de tests réussis
    size_t counter = 0;
    for (iterator i = first, e = last; compare(i, e) != 0; increment(&i, 1))
    {
        if (unary_operation(i.element))
            counter++;
    }

    return counter;
}

iterator find_if(
    iterator first,
    iterator last,
    bool (*predicate)(void const *data))
{

    for (iterator i = first, e = last; compare(i, e) != 0; increment(&i, 1))
    {
        // on renvoie le premier qui correspond
        if (predicate(i.element))
            return i;
    }
    // si on ne l'a pas trouvé
    return last;
}

iterator copy(
    iterator first,
    iterator last,
    iterator destination)
{
    for (iterator i = first, e = last; compare(i, e) != 0; increment(&i, 1))
    {
        // on copie
        memmove(destination.element, i.element, i.element_size);
        increment(&destination, 1);
    }

    return destination;
}

iterator copy_if(
    iterator first,
    iterator last,
    iterator destination,
    bool (*predicate)(void const *data))
{
    for (iterator i = first, e = last; compare(i, e) != 0; increment(&i, 1))
    {
        if (predicate(i.element))
        {
            // on copie
            memmove(destination.element, i.element, i.element_size);
            increment(&destination, 1);
        }
    }

    return destination;
}

void fill(
    iterator first,
    iterator last,
    void const *data)
{
    for (iterator i = first, e = last; compare(i, e) != 0; increment(&i, 1))
    {
        // on renvoie le premier qui correspond
        memmove(i.element, data, i.element_size);
    }
}

iterator transform(
    iterator first,
    iterator last,
    iterator destination,
    void (*unary_operation)(void *data))
{

    for (iterator i = first, e = last; compare(i, e) != 0; increment(&i, 1))
    {

        // on copie l'élément
        memmove(destination.element, i.element, i.element_size);
        // on modifie l'élément
        unary_operation(destination.element);
        increment(&destination, 1);
    }

    return destination;
}

void generate(
    iterator first,
    iterator last,
    void *(*generator)())
{
    for (iterator i = first, e = last; compare(i, e) != 0; increment(&i, 1))
    {
        // on renvoie le premier qui correspond
        memmove(i.element, generator(), i.element_size);
    }
}

iterator rotate(
    iterator first,
    iterator n_first,
    iterator last)
{
    int count = 0;
    for (iterator i = first; compare(i, n_first) != 0; increment(&i, 1))
    {
        // on décale l'iterator de i.element_size
        count++;
    }

    for (size_t t = 0; t < count; t++)
    {

        // on décale d'abord le premier pour ne pas l'écraser
        void *temp = malloc(first.element_size);
        memmove(temp, first.element, first.element_size);

        iterator i = first, e = last;
        for (; compare(i, e) != 0; increment(&i, 1))
        {
            // on décale l'iterator de i.element_size
            memmove(i.element, i.element + i.element_size, i.element_size);
        }
        // on décrémente à partir de la fin pour obtenir le dernier (après la rotation)
        decrement(&i, 1);
        // on y place le premier qu'on avait sauvegardé dans temp
        memmove(i.element, temp, first.element_size);
        free(temp);
    }

    // on veut le dernier élément traité
    decrement(&last, 1);

    return last;
}

void reverse(
    iterator first,
    iterator last)
{
int count = 0;
    for (iterator i = first, e = last; compare(i, e) != 0; increment(&i, 1))
    {
        // on compte combien d'éléments on a entre first et last
        count++;
    }
    
    iterator i = first;
    for (size_t t = 0; t < count / 2; t++)
    {
        // Pas besoin d'incrémenter i la première fois, on est bien placé
        if (t) increment(&i, 1);
        // on décale d'abord le premier pour ne pas l'écraser
        void *temp = malloc(i.element_size);
        memmove(temp, i.element, i.element_size);
        
        // on décale l'iterator de i.element_size
        memmove(i.element, i.element + (count - 1 - 2*t) * i.element_size, i.element_size);
        
        // on décrémente à partir de la fin pour obtenir le dernier (après la rotation)
        decrement(&i, 1);
        // on y place le premier qu'on avait sauvegardé dans temp
        memmove(i.element + (count - 2*t) * i.element_size, temp, first.element_size);
        
        free(temp);

        increment(&i, 1);
    }
}

int compare_int(
    const void *a,
    const void *b)
{
    return *(int *)a - *(int *)b;
}

void sort(
    iterator first,
    iterator last)
{
    // algorithme de tri bulle

    // teste si vecteur taille 1
    iterator test=first;
    increment(&test,1);
    if(compare(test, last)>=0)
        return; // si oui quitte fonct : déjà trie
    
    // sinon on trie

    iterator j=first;
    int trie;
    do
    {
        // on considère le vecteur comme trie
        trie=1;
        
        // k à T[n-1]
        iterator k=last;
        decrement(&k, 1);
        // pour touts les elements de T[n-1] à T[sorted+1](jusqu'où les éléments sont triés)
        for (iterator sorted=j; compare(k, sorted) > 0; decrement(&k, 1))
        {
            // prendre l'élément en dessous
            test=k;
            decrement(&test, 1);
            // les comparer
            if(compare_int(k.element, test.element)<0) // si compare_int < 0 element de k < element de j
            {
                // echanger les elements
                iterator swaplast=k; // limite du swap
                increment(&swaplast, 1);
                reverse(test, swaplast);
                
                trie=0; // tableau non trie
                j=test; // on considere que les éléments sont triés jusqu'à j
            }
        }
        
    } while (trie==0); 
}

void sort_by(
    iterator first,
    iterator last,
    int (*comparator)(void const *a, void const *b))
{
    // algorithme de tri bulle

    // teste si vecteur taille 1
    iterator test=first;
    increment(&test,1);
    if(compare(test, last)>=0)
        return; // si oui quitte fonct : déjà trie
    
    // sinon on trie

    iterator j=first;
    int trie;
    do
    {
        // on considère le vecteur comme trie
        trie=1;
        
        // k à T[n-1]
        iterator k=last;
        decrement(&k, 1);
        // pour touts les elements de T[n-1] à T[sorted+1](jusqu'où les éléments sont triés)
        for (iterator sorted=j; compare(k, sorted) > 0; decrement(&k, 1))
        {
            // prendre l'élément en dessous
            test=k;
            decrement(&test, 1);
            // les comparer
            if(comparator(k.element, test.element)<0) // si compare_int < 0 element de k < element de j
            {
                // echanger les elements
                iterator swaplast=k; // limite du swap
                increment(&swaplast, 1);
                reverse(test, swaplast);
                
                trie=0; // tableau non trie
                j=test; // on considere que les éléments sont triés jusqu'à j
            }
        }
        
    } while (trie==0); 
}

iterator unique(
    iterator first,
    iterator last,
    int (*comparator)(void const *a, void const *b))
{

    if (compare(first, last) == 0) return last;
    
    // iterateur qui récupère le premier élément déplacé
    iterator ret;
    int count = 0;
    iterator result = first;
    increment(&first, 1);
    for (; compare(first, last) != 0; increment(&first, 1))
    {
        // les comparer
        if (comparator(first.element, result.element) == 0)
        {
            
            // on sauvegarde l'élément à déplacer
            increment(&result, 1);
            memmove(result.element, first.element, first.element_size);
            if (count == 0) ret = result;
            count++;
        }
        else
        {
            // j'enregistre l'élément pointé par ret
            void *temp = malloc(first.element_size);
            memmove(temp, ret.element, ret.element_size);

            // j'y place l'élément de result (différent)
            memmove(ret.element, ret.element + count * ret.element_size, result.element_size);

            // je mets l'élément de ret à la place de result
            memmove(ret.element + count * ret.element_size, temp, result.element_size);
            free(temp);

            increment(&ret, 1);
        }
    }
        
    return ret;
}

bool binary_search(
    iterator first,
    iterator last,
    void const *value,
    int (*comparator)(void const *a, void const *b))
{
    iterator test;

    for(iterator b=first, e=last; compare(b,e); test.element = (b.element+e.element)/2)
    {
        int res=comparator(test.element, value);
        if(res == 0)
            return true;
        else if(res > 0)
            e = test;
        else
            b = test;
    }

    return false;
}

int id_search(
    iterator first,
    iterator last,
    void const *value,
    int (*id_comp)(void const *a, void const *b))
{
    // iterateur de test
    iterator test=first;

    int place=1;
    // pour tous les el de l'intervalle
    while (compare(test, last)<0)
    {
        // si egal à value
        if(id_comp(test.element, value)==0)
            // renvoie vrai
            return place;
        increment(&test, 1);
        place++;
    }
    
    // sinon faux
    return 0;
}

iterator_interval equal_range(
    iterator first,
    iterator last,
    void const *value, int (*comparator)(void const *a, void const *b))
{
    // initialise begin à la fin
    void * begin=last.element;

    // iterateur de test
    iterator test=first;

    // comparer tous les el. de l'intervalle avec value
    while (compare(test, last)<0 && begin==last.element)
    {
        // si un el est égal à val
        if(comparator(test.element, value)==0)
            // mettre begin à cette el
            begin=test.element;
        increment(&test, 1);
    }

    // initialise end au debut
    void * end=first.element;
    // si begin
    if(begin!=last.element)
    {
        // comparer tous les el. de l'intervalle avec value
        while(compare(test,last)<=0 && end==first.element)
        {
            // si un el est different 
            if(comparator(test.element, value)!=0)
                // end pointe cet el
                end=test.element;
            increment(&test, 1);
        }
    }

    // retourne l'intervalle
    return (iterator_interval){
        .begin = (iterator){.element = begin},
        .end = (iterator){.element = end}};
}

iterator set_difference(
    iterator first1,
    iterator last1,
    iterator first2,
    iterator last2,
    iterator destination,
    int (*comparator)(void const *a, void const *b))
{
    // iterateur courant
    iterator curr=first1;

    // pour tous les el. de l'intervalle 1
    while (compare(curr, last1)<0)
    {
        // iterateur de test
        iterator test=first2;
        int presence=0; // indique la presence d'un el. similaire dans 2

        // les comparer aux el. de 2 tant qu'il sont inférieur et non present
        while (comparator(test.element, curr.element)<=0 && presence==0 && compare(test, last2)<0)
        {
            // el1 égale à el2
            if(comparator(test.element, curr.element)==0)
                presence=1; // el present dans 2
            increment(&test, 1);
        }
        
        // si el non present dans 2
        if(presence==0)
        {
            // le mettre dans destination
            set(destination, curr.element);
            increment(&destination, 1); //incrementer destination
        }
        
        increment(&curr, 1);
    }
    
    return destination; // renvoyé destination
}

iterator set_intersection(
    iterator first1,
    iterator last1,
    iterator first2,
    iterator last2,
    iterator destination,
    int (*comparator)(void const *a, void const *b))
{
    // iterateur courant
    iterator curr=first1;

    // pour tous les el. de l'intervalle 1
    while (compare(curr, last1)<0)
    {
        // iterateur de test
        iterator test=first2;
        int presence=0; // indique la presence d'un el. similaire dans 2

        // les comparer aux el. de 2 tant qu'il sont inférieur et non present
        while (comparator(test.element, curr.element)<=0 && presence==0 && compare(test, last2)<0)
        {
            // el1 égale à el2
            if(comparator(test.element, curr.element)==0)
                presence=1; // el present dans 2
            increment(&test, 1);
        }
        
        // si el present dans 2
        if(presence==1)
        {
            // le mettre dans destination
            set(destination, curr.element);
            increment(&destination, 1); //incrementer destination
        }
        
        increment(&curr, 1);
    }
    
    return destination; // renvoyé destination
}

int get_first_id(iterator first, iterator last)
{
    // on rajoute le client au premier id disponible
    iterator i = first, e = last;
    
    int id = 0;
    if(i.element_size==sizeof(Client))
    {
        Client *user = (Client*)(i.element);
        while(compare(i, e) && user->id == id + 1)
        {
            increment(&i, 1);
            user = (Client*)(i.element);
            id++;
        }
    }

    else if(i.element_size==sizeof(Restaurant))
    {
        Restaurant *user = (Restaurant*)(i.element);
        while(compare(i, e) && user->id == id + 1)
        {
            increment(&i, 1);
            user = (Restaurant*)(i.element);
            id++;
        }
    }

    else if(i.element_size==sizeof(Menu))
    {
        Menu *user = (Menu*)(i.element);
        while(compare(i, e) && user->id == id + 1)
        {
            increment(&i, 1);
            user = (Menu*)(i.element);
            id++;
        }
    }

    else if(i.element_size==sizeof(Livreur))
    {
        Livreur *user = (Livreur*)(i.element);
        while(compare(i, e) && user->id == id + 1)
        {
            increment(&i, 1);
            user = (Livreur*)(i.element);
            id++;
        }
    }

    return id + 1;
}
 