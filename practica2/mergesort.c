#include <stdio.h>
#include <stdlib.h>

// Define an error code
#define ERR -1

// Merge function: Combines two sorted subarrays into one sorted array
int merge(int* tabla, int ip, int iu, int imedio) {
    int basic_operations = 0;

    // Sizes of the two subarrays
    int n1 = imedio - ip + 1;
    int n2 = iu - imedio;

    // Temporary arrays for the two subarrays
    int* left = (int*)malloc(n1 * sizeof(int));
    int* right = (int*)malloc(n2 * sizeof(int));

    if (!left || !right) {
        // Memory allocation failed
        return ERR;
    }

    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++) {
        left[i] = tabla[ip + i];
        basic_operations++;
    }
    for (int i = 0; i < n2; i++) {
        right[i] = tabla[imedio + 1 + i];
        basic_operations++;
    }

    // Merge the two temporary arrays back into `tabla`
    int i = 0, j = 0, k = ip;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            tabla[k++] = left[i++];
        } else {
            tabla[k++] = right[j++];
        }
        basic_operations++;
    }

    // Copy any remaining elements of `left`
    while (i < n1) {
        tabla[k++] = left[i++];
        basic_operations++;
    }

    // Copy any remaining elements of `right`
    while (j < n2) {
        tabla[k++] = right[j++];
        basic_operations++;
    }

    // Free temporary arrays
    free(left);
    free(right);

    return basic_operations;
}

// MergeSort function: Recursively sorts an array
int mergesort(int* tabla, int ip, int iu) {
    int basic_operations = 0;

    if (ip < iu) {
        int imedio = ip + (iu - ip) / 2;

        // Sort the first half
        int left_operations = mergesort(tabla, ip, imedio);
        if (left_operations == ERR) {
            return ERR;
        }
        basic_operations += left_operations;

        // Sort the second half
        int right_operations = mergesort(tabla, imedio + 1, iu);
        if (right_operations == ERR) {
            return ERR;
        }
        basic_operations += right_operations;

        // Merge the two halves
        int merge_operations = merge(tabla, ip, iu, imedio);
        if (merge_operations == ERR) {
            return ERR;
        }
        basic_operations += merge_operations;
    }

    return basic_operations;
}

int main() {

    int tabla[] = {38, 27, 43, 3, 9, 82, 10};
    int n = sizeof(tabla) / sizeof(tabla[0]);

    printf("Original array:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", tabla[i]);
    }
    printf("\n");

    int result = mergesort(tabla, 0, n - 1);

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
