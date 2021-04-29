#include "functions.h"
#include "db.h"

#include <stdbool.h>
#include <ctype.h>

bool is_even(
    void const* data)
{
    return *(int*)data % 2 == 0;
}

bool is_odd(
    void const* data)
{
    return  *(int*)data+1 % 2 == 0;
}

bool less_than_five(
    void const* data)
{
    return *(int*)data < 5;
}

bool only_vowels(
    void const* data)
{
    bool test=true;
    int i=0;
    while(((char*)data)[i]!='\0' && test==true)
    {
        char letter=((char*)data)[i];
        if(letter>='A' && letter<='Z')
            letter=letter+32; // passage min;
        
        switch (letter)
        {
        case 'a':
            test=true;
            break;

        case 'e':
            test=true;
            break;

        case 'i':
            test=true;
            break;

        case 'o':
            test=true;
            break;

        case 'u':
            test=true;
            break;

        case 'y':
            test=true;
            break;
        
        default:
            test=false;
            break;
        }
        i++;
    }

    return test;
}

void negate(
    void* data)
{
    // on renvoie le contraire de la valeur pointée par data (en tant que booléen)
    if (data) *(bool*)data = !*(bool*)data;
}

// void flip_case(
//     void* data)
// {
//     if (data)
//     {
//         while (*(char *)data)
//         {
//             // si la lettre est minuscule, alors on la passe en majuscule
//             if (islower(*(char *)data)) *(char *)data = toupper(*(char *)data);
//             // sinon l'inverse
//             else *(char *)data = tolower(*(char *)data);
//             (char *)data++;
//         }
//     }
    
// }

void* counter()
{
    static int c = 0;
    ++c;
    return &c;
}

int numerical_compare(
    void const* a,
    void const* b)
{
    return *(int*)a - *(int*)b;
}

int lexicographical_compare(
    void const* a,
    void const* b)
{
    int i=0;
    int comp=0;
    // tant que a et b sont identiques
    while(((char *)a)[i]!='\0' && ((char *)b)[i]!='\0' && comp==0)
    {
        // les comparer char par char
        comp=((char *)a)[i]-((char *)b)[i];
        i++;
    }

    // si difference
    if(comp!=0)
        return comp;

    // sinon si a et b tous deux finis
    else if(((char *)a)[i]=='\0' && ((char *)b)[i]=='\0')
        return 0;
    
    // sinon si que a est finis
    else if(((char *)a)[i-1]=='\0')
        return -1;

    else
        return 1;
}

int idresto_compare(
    void const* a,
    void const* b)
{
    return ((Restaurant*)a)->id - ((Restaurant*)b)->id;
}