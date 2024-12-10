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
#include <stdlib.h>
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
    if (array == NULL || ip < 0 || iu < ip) return ERR; /*Parameters check*/
    int count = 0;
    int temp,a,i,j;
    for (i = ip; i < iu; i++) {
        a = iu - (i - ip);
        for (j = ip; j < a; j++) {
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
    if (array == NULL || ip < 0 || iu < ip) return ERR; /*Paramethers Check*/
    int swapped; /*Flag*/
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
                swapped = 1; /*Flag update*/
            }
        }
        if (!swapped) return cont;
    }
    return cont;
}

/* Merge function: Combines two sorted subarrays into one sorted array*/
int merge(int* tabla, int ip, int iu, int imedio) {
    int basic_operations = 0;
    int i;
    /* Sizes of the two subarrays*/
    int n1 = imedio - ip + 1;
    int n2 = iu - imedio;
    /* Temporary arrays for the two subarrays*/
    int* left = (int*)malloc(n1 * sizeof(int));
    int* right = (int*)malloc(n2 * sizeof(int));
    if (!left || !right) {
        /* Memory allocation failed*/
        return ERR;
    }
    /* Copy data to temporary arrays*/
    for (i = 0; i < n1; i++) {
        left[i] = tabla[ip + i];
        basic_operations++;
    }
    for (i = 0; i < n2; i++) {
        right[i] = tabla[imedio + 1 + i];
        basic_operations++;
    }
    /* Merge the two temporary arrays back into `tabla`*/
    int j = 0, k = ip;
    i=0;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            tabla[k++] = left[i++];
        } else {
            tabla[k++] = right[j++];
        }
        basic_operations++;
    }
    /* Copy any remaining elements of `left`*/
    while (i < n1) {
        tabla[k++] = left[i++];
        basic_operations++;
    }
    /* Copy any remaining elements of `right`*/
    while (j < n2) {
        tabla[k++] = right[j++];
        basic_operations++;
    }
    /* Free temporary arrays*/
    free(left);
    free(right);
    return basic_operations;
}

/* MergeSort function: Recursively sorts an array*/
int mergesort(int* tabla, int ip, int iu) {
    int basic_operations = 0;
    if (ip < iu) {
        int imedio = ip + (iu - ip) / 2;

        /* Sort the first half*/
        int left_operations = mergesort(tabla, ip, imedio);
        if (left_operations == ERR) {
            return ERR;
        }
        basic_operations += left_operations;

        /* Sort the second half*/
        int right_operations = mergesort(tabla, imedio + 1, iu);
        if (right_operations == ERR) {
            return ERR;
        }
        basic_operations += right_operations;

        /* Merge the two halves*/
        int merge_operations = merge(tabla, ip, iu, imedio);
        if (merge_operations == ERR) {
            return ERR;
        }
        basic_operations += merge_operations;
    }

    return basic_operations;
}

int Heapify(int* tabla, int n, int i) {
    int basic_operations = 0;

    int largest = i;           /* Initialize largest as root*/
    int left = 2 * i + 1;      /* Left child*/
    int right = 2 * i + 2;     /* Right child*/

    /* Check if left child exists and is greater than root*/
    if (left < n && tabla[left] > tabla[largest]) {
        largest = left;
    }
    basic_operations++;

    /* Check if right child exists and is greater than largest so far*/
    if (right < n && tabla[right] > tabla[largest]) {
        largest = right;
    }
    basic_operations++;

    /* If largest is not root, swap and continue heapifying*/
    if (largest != i) {
        int temp = tabla[i];
        tabla[i] = tabla[largest];
        tabla[largest] = temp;
        basic_operations++;

        /* Recursively heapify the affected subtree*/
        int sub_operations = Heapify(tabla, n, largest);
        if (sub_operations == ERR) {
            return ERR;
        }
        basic_operations += sub_operations;
    }

    return basic_operations;
}

/***************************************************/
/* Function: CrearHeap                             */
/* Description: Builds a max heap from the array   */
/***************************************************/
int CrearHeap(int* tabla, int n) {
    int basic_operations = 0;
    int i;
    /* Start from the last non-leaf node and heapify each node*/
    for (i = n / 2 - 1; i >= 0; i--) {
        int operations = Heapify(tabla, n, i);
        if (operations == ERR) {
            return ERR;
        }
        basic_operations += operations;
    }

    return basic_operations;
}

/***************************************************/
/* Function: OrdenarHeap                           */
/* Description: Performs heap sort                 */
/***************************************************/
int OrdenarHeap(int* tabla, int n) {
    int basic_operations = 0;
    int i;

    /* Create a heap from the array*/
    int heap_operations = CrearHeap(tabla, n);
    if (heap_operations == ERR) {
        return ERR;
    }
    basic_operations += heap_operations;

    /* Extract elements one by one from the heap*/
    for (i = n - 1; i > 0; i--) {
        /* Move the root (largest element) to the end*/
        int temp = tabla[0];
        tabla[0] = tabla[i];
        tabla[i] = temp;
        basic_operations++;

        /* Call Heapify on the reduced heap*/
        int operations = Heapify(tabla, i, 0);
        if (operations == ERR) {
            return ERR;
        }
        basic_operations += operations;
    }

    return basic_operations;
}

/***************************************************/
/* Function: heapsort                              */
/* Description: Combines the above routines into   */
/*              a single sorting function          */
/***************************************************/
int heapsort(int* tabla, int ip, int iu) {
    if (ip >= iu) {
        return 0;  /* No sorting needed for a single element*/
    }

    /* Calculate the size of the array*/
    int n = iu - ip + 1;
    int i;

    /* Allocate a temporary array for the range ip to iu*/
    int* temp = (int*)malloc(n * sizeof(int));
    if (!temp) {
        return ERR;
    }

    /* Copy the relevant range to the temporary array*/
    for (i = 0; i < n; i++) {
        temp[i] = tabla[ip + i];
    }

    /* Perform heap sort on the temporary array*/
    int basic_operations = OrdenarHeap(temp, n);
    if (basic_operations == ERR) {
        free(temp);
        return ERR;
    }

    /* Copy the sorted array back to the original array*/
    for (i = 0; i < n; i++) {
        tabla[ip + i] = temp[i];
    }

    free(temp);
    return basic_operations;
}



