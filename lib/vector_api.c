#include "vector_api.h"

#include "vector_types.h"

#include <stdlib.h>
#include <string.h>

vector make_vector(
    size_t const element_size,
    size_t const num_elements,
    float const growth_factor)
{
    void *data = NULL;
    if (num_elements) data = malloc(element_size * num_elements);

    return (vector){
            .element_size = element_size,
            .size=num_elements,
            .capacity=num_elements, 
            .data = data,
            .growth_factor=growth_factor
            };
}

void destroy(
    vector* v)
{
    if (v->data) free(v->data);
}

size_t size(
    vector const v)
{
    return v.size;
}

size_t capacity(
    vector const v)
{
    return v.capacity;
}

void push_back(
    vector* v,
    void const* data)
{
    // si vecteur vide
    if(v->capacity==0)
    {
        // realloue memoire
        destroy(v);
        v->data=malloc(v->element_size);
        // change capacité
        v->capacity=1;
    }

    // sinon si capacité limite vect atteint
    else if(v->size==v->capacity)
    {
        // alloue nouvelle memoire selon growth factor
        v->capacity=v->capacity*v->growth_factor;
        v->data=realloc(v->data, v->element_size*v->capacity);
    }

    memmove((v->data)+(v->element_size*v->size), data, v->element_size);
    v->size++;
}

void* pop_back(
    vector* v)
{
    // décremente taille vect
    v->size=v->size-1;
    return (v->data)+(v->element_size*v->size);
}

void insert(
    vector* v,
    iterator const i,
    void const* data)
{
    if (v->capacity == 0 || compare(i, end(v)) == 0)
    {
        push_back(v, data);
    }
    else
    {
        // si capacité limite vect atteint
        if (v->size == v->capacity)
        {
            // alloue nouvelle memoire selon growth factor
            v->capacity = v->capacity * v->growth_factor;
            v->data = realloc(v->data, v->element_size * v->capacity);
        }

        // réserve l'espace pour insérer l'élément
        iterator it = end(v);
        // increment(&it, 1);
        while (compare(i, it))
        {
            decrement(&it, 1);
            memmove(it.element+v->element_size, it.element, v->element_size);
        }

        //insérer l'élément
        memmove(i.element, data, i.element_size);
        v->size++;
    }
}

void erase(
    vector* v,
    iterator const i)
{
    if (v)
    {
        // on reduit la taille du vector
        v->size--;
        // on déplace les éléments suivants d'un "cran" vers la gauche en mémoire
        int nb_elem = 0; // nombre d'éléments à décaler
        iterator it = i;
        // increment(&it, 1);
        while (compare(it, end(v)))
        {
            increment(&it, 1);
            nb_elem++;
        }
        memmove(i.element, i.element + v->element_size, v->element_size * nb_elem);
    }
}

void assign(
    vector* v,
    iterator first,
    iterator last)
{
    // On copie chaque élément à l'aide de push_back
    iterator i = first, e = last;
    for (; compare(i, e) != 0; increment(&i, 1))
    {
        push_back(v, i.element);
    }
}

void clear(
    vector* v)
{
    // on libère la mémoire
    for (iterator i = begin(v), e = end(v); compare(i, e) != 0; increment(&i, 1))
        pop_back(v);
}

void swap(
    vector* a,
    vector* b)
{
    // on créé un vector temporaire pour la copie
    vector temp = (vector){
        .element_size = a->element_size,
        .size = a->size,
        .capacity = a->capacity,
        .data = a->data,
        .growth_factor = a->growth_factor};

    // on échange les pointeurs de donnée et les tailles
    a->size = b->size;
    a->data = b->data;

    b->size = temp.size;
    b->data = temp.data;
}

void reserve(
    vector* v,
    size_t const num_elements)
{
    // si capacité trop petite
    if(v->capacity<num_elements)
    {
        // realloer memoire
        v->data=realloc(v->data, v->element_size*num_elements);
        v->capacity=num_elements;
    }
    //sinon rien faire
}

void resize(
    vector* v,
    size_t const num_elements)
{
    // reserve capacite si trop petite
    reserve(v, num_elements);
    // ajuste nb_el non def
    v->size=num_elements;
}

void shrink_to_fit(
    vector* v)
{
    if(v->capacity>v->size)
    {
        v->data=realloc(v->data, v->element_size*v->size);
        v->capacity=v->size;
    }
}


iterator begin(
    vector const* v)
{
    return (iterator){
            .element = v->data,
            .element_size=v->element_size
            };
}

iterator end(
    vector const* v)
{
    return (iterator){
            .element = (v->data)+(v->element_size*v->size),
            .element_size=v->element_size
            };
}

iterator at(
    vector const* v,
    size_t const index)
{
    return (iterator){
            .element = (v->data)+(v->element_size*index),
            .element_size=v->element_size
            };
}

int compare(
    iterator const a,
    iterator const b)
{
    if(a.element<b.element)
        return -1;
    
    else if(a.element==b.element)
        return 0;

    else
        return 1;
}

void increment(
    iterator* i,
    size_t const num_elements)
{
    i->element=(i->element)+(i->element_size*num_elements);
}

void decrement(
    iterator* i,
    size_t const num_elements)
{
    i->element=(i->element)-(i->element_size*num_elements);
}

void* value(
    iterator const i)
{
    return i.element;
}

void set(
    iterator i,
    void const* data)
{
    memmove(i.element, data, i.element_size);
}
