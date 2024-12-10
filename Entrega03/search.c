/**
 *
 * Description: Implementation of functions for search
 *
 * File: search.c
 * Author: Carlos Aguirre and Javier Sanz-Cruzado
 * Version: 1.0
 * Date: 14-11-2016
 *
 */

#include "search.h"

#include <stdlib.h>
#include <math.h>

/**
 *  Key generation functions
 *
 *  Description: Receives the number of keys to generate in the n_keys
 *               parameter. The generated keys go from 1 to max. The
 * 				 keys are returned in the keys parameter which must be 
 *				 allocated externally to the function.
 */
  
/**
 *  Function: uniform_key_generator
 *               This function generates all keys from 1 to max in a sequential
 *               manner. If n_keys == max, each key will just be generated once.
 */
void uniform_key_generator(int *keys, int n_keys, int max)
{
  int i;
  for(i = 0; i < n_keys; i++)
    keys[i] = 1 + (i % max);
  return;
}

/**
 *  Function: potential_key_generator
 *               This function generates keys following an approximately
 *               potential distribution. The smaller values are much more 
 *               likely than the bigger ones. Value 1 has a 50%
 *               probability, value 2 a 17%, value 3 the 9%, etc.
 */
void potential_key_generator(int *keys, int n_keys, int max)
{
  int i;
  for(i = 0; i < n_keys; i++) 
    keys[i] = .5+max/(1 + max*((double)rand()/(RAND_MAX)));
  return;
}

PDICT init_dictionary (int size, char order)
{
	/* Verificar si los parámetros son válidos*/
  if (size <= 0 || (order != SORTED && order != NOT_SORTED))
    return NULL;

  /* Asignar memoria para el diccionario*/
  PDICT dict = (PDICT)malloc(sizeof(DICT));
  if (!dict)
    return NULL;

  /* Inicializar campos del diccionario*/
  dict->size = size;
  dict->n_data = 0;  /* Al principio no hay datos en la tabla*/
  dict->order = order;

  /* Asignar memoria para la tabla de datos*/
  dict->table = (int *)malloc(size * sizeof(int));
  if (!dict->table) {
    free(dict);
    return NULL;
  }
  
  return dict;
}

void free_dictionary(PDICT pdict)
{
	/* your code */
}

int insert_dictionary(PDICT pdict, int key)
{
	/* Verificar si el diccionario y la tabla son válidos*/
  if (!pdict || !pdict->table)
    return ERR;

  /* Verificar si hay espacio disponible en el diccionario*/
  if (pdict->n_data >= pdict->size) 
    return ERR;

  /* Caso 1: Diccionario NO ORDENADO*/
  if (pdict->order == NOT_SORTED)
      pdict->table[pdict->n_data] = key; /* Insertar al final*/
    
    /* Caso 2: Diccionario ORDENADO*/
    else if (pdict->order == SORTED) {
      int j;
      /* Insertar al final temporalmente*/
      pdict->table[pdict->n_data] = key;

      /* Ordenar por inserción*/
      int A = pdict->table[pdict->n_data]; /* Elemento insertado*/
      j = pdict->n_data - 1;

      /* Desplazar elementos hacia la derecha para insertar en la posición correcta*/
      while (j >= 0 && pdict->table[j] > A) {
        pdict->table[j + 1] = pdict->table[j];
        j--;
      }
      pdict->table[j + 1] = A; /* Colocar el elemento en la posición correcta*/
    } else
        return ERR; /*Return Error*/

    /* Incrementar el número de datos en el diccionario*/
    pdict->n_data++;
    return OK; /* Éxito*/
}

int massive_insertion_dictionary (PDICT pdict,int *keys, int n_keys)
{
	/* Verificar si el diccionario y el array de claves son válidos*/
  if (!pdict || !keys)
    return ERR;
  int i;
  /* Insertar cada clave usando la función insert_dictionary*/
  for (i = 0; i < n_keys; i++)
    if (insert_dictionary(pdict, keys[i]) == ERR)
      return ERR;
  return OK; /* Éxito*/
}

int search_dictionary(PDICT pdict, int key, int *ppos, pfunc_search method)
{
	/* Verificar si los parámetros son válidos*/
  if (!pdict || !pdict->table || !ppos || !method) 
    return ERR; /* Error
  
  /* Llamar al método de búsqueda proporcionado*/
  int result = method(pdict->table, pdict->size, pdict->n_data, key, ppos);

  if (result == OK)
    return OK; /* Clave encontrada*/
  else 
    return ERR; /* Clave no encontrada*/
  
}


/* Search functions of the Dictionary ADT */
int bin_search(int *table,int F,int L,int key, int *ppos)
{
	int left = 0, right = F - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (table[mid] == key) {
            *ppos = mid; /* Clave encontrada*/
            return mid; /* Retorna la posición*/
        } else if (table[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    *ppos = NOT_FOUND; /* Clave no encontrada*/
    return NOT_FOUND;
}

int lin_search(int *table,int F,int L,int key, int *ppos)
{
  int i;
	for (i = 0; i < F; i++) {
        if (table[i] == key) {
            *ppos = i; /* Clave encontrada*/
            return i; /* Retorna la posición*/
        }
    }

    *ppos = NOT_FOUND; /* Clave no encontrada*/
    return NOT_FOUND;
}

int lin_auto_search(int *table,int F,int L,int key, int *ppos)
{
  int i;
	for (i = 0; i < F; i++) {
        if (table[i] == key) {
            *ppos = i; /* Clave encontrada*/

            /* Intercambiar con la posición anterior si no es la primera posición*/
            if (i > 0) {
                int temp = table[i];
                table[i] = table[i - 1];
                table[i - 1] = temp;
                *ppos = i - 1; /* Actualizar la posición después del intercambio*/
            }

            return *ppos; /* Retorna la nueva posición*/
        }
    }

    *ppos = NOT_FOUND; /* Clave no encontrada*/
    return NOT_FOUND;
}


