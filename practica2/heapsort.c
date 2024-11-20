#include <stdio.h>
#include <stdlib.h>

// Define an error code
#define ERR -1

/***************************************************/
/* Function: Heapify                               */
/* Description: Ensures the max-heap property for  */
/*              a subtree rooted at index i       */
/***************************************************/
int Heapify(int* tabla, int n, int i) {
    int basic_operations = 0;

    int largest = i;           // Initialize largest as root
    int left = 2 * i + 1;      // Left child
    int right = 2 * i + 2;     // Right child

    // Check if left child exists and is greater than root
    if (left < n && tabla[left] > tabla[largest]) {
        largest = left;
    }
    basic_operations++;

    // Check if right child exists and is greater than largest so far
    if (right < n && tabla[right] > tabla[largest]) {
        largest = right;
    }
    basic_operations++;

    // If largest is not root, swap and continue heapifying
    if (largest != i) {
        int temp = tabla[i];
        tabla[i] = tabla[largest];
        tabla[largest] = temp;
        basic_operations++;

        // Recursively heapify the affected subtree
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

    // Start from the last non-leaf node and heapify each node
    for (int i = n / 2 - 1; i >= 0; i--) {
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

    // Create a heap from the array
    int heap_operations = CrearHeap(tabla, n);
    if (heap_operations == ERR) {
        return ERR;
    }
    basic_operations += heap_operations;

    // Extract elements one by one from the heap
    for (int i = n - 1; i > 0; i--) {
        // Move the root (largest element) to the end
        int temp = tabla[0];
        tabla[0] = tabla[i];
        tabla[i] = temp;
        basic_operations++;

        // Call Heapify on the reduced heap
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
        return 0;  // No sorting needed for a single element
    }

    // Calculate the size of the array
    int n = iu - ip + 1;

    // Allocate a temporary array for the range ip to iu
    int* temp = (int*)malloc(n * sizeof(int));
    if (!temp) {
        return ERR;
    }

    // Copy the relevant range to the temporary array
    for (int i = 0; i < n; i++) {
        temp[i] = tabla[ip + i];
    }

    // Perform heap sort on the temporary array
    int basic_operations = OrdenarHeap(temp, n);
    if (basic_operations == ERR) {
        free(temp);
        return ERR;
    }

    // Copy the sorted array back to the original array
    for (int i = 0; i < n; i++) {
        tabla[ip + i] = temp[i];
    }

    free(temp);
    return basic_operations;
}

/***************************************************/
/* Main Function: Testing the heapsort algorithm   */
/***************************************************/
int main() {
    int tabla[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(tabla) / sizeof(tabla[0]);

    printf("Original array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", tabla[i]);
    }
    printf("\n");

    int result = heapsort(tabla, 0, n - 1);

    if (result == ERR) {
        printf("An error occurred during sorting.\n");
        return 1;
    }

    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", tabla[i]);
    }
    printf("\n");

    printf("Total basic operations: %d\n", result);

    return 0;
}
