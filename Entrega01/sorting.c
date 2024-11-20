/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */


#include "sorting.h"
#define NULL ((void *)0)

/***************************************************/
/* Function: BubbleSort                            */
/* Rutina de ordinacion BubbleSort                 */
/* Input:                                          */
/* int* array puntero a array de ordenar           */
/* int ip primera posicion del array               */
/* int iu ultima posicion del array                */
/***************************************************/
int BubbleSort(int* array, int ip, int iu){
    if (array == NULL || ip < 0 || iu < ip) return ERR; //Parameters check
    int count = 0;
    int temp,a;
    for (int i = ip; i < iu; i++) {
        a = iu - (i - ip);
        for (int j = ip; j < a; j++) {
            count++;  
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    return count;
}

/***************************************************/
/* Function: BubbleSort                            */
/* Rutina de ordinacion BubbleSort con flag        */
/* Input:                                          */
/* int* array puntero a array de ordenar           */
/* int ip primera posicion del array               */
/* int iu ultima posicion del array                */
/***************************************************/
int BubbleSortFlag(int* array, int ip, int iu)
{
    if (array == NULL || ip < 0 || iu < ip) return ERR; //Paramethers Check
    int swapped; //Flag
    int i, j;
    int cont = 0;
    for (i = iu; i > ip; i--) {
        swapped = 0;
        for (j = ip; j < i; j++) {
            cont++;
            if (array[j] > array[j+1]) {
                int temp = array[j];
                array[j] = array[j+1];
                array[j+1] = temp;
                swapped = 1; //Flag update
            }
        }
        if (!swapped) return cont;
    }
    return cont;
}



