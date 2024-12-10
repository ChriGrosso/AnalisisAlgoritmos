/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.1
 * Fecha: 16-09-2019
 *
 */

#include "times.h"
#include "sorting.h"
#include "permutations.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

/***************************************************/
/* Function: average_sorting_time                 */
/* Description: Measures the average execution    */
/* time and basic operations of a sorting method  */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, 
                           int n_perms,
                           int N, 
                           PTIME_AA ptime) {
    if (n_perms <= 0 || N <= 0 || ptime == NULL) return ERR; // Parameter validation

    int i, result;
    double t1, t2, total_time = 0;
    int total_ob = 0, min_ob = __INT_MAX__, max_ob = 0;
    int** permArray = generate_permutations(n_perms, N);

    if (permArray == NULL) return ERR; // Memory allocation check

    struct timeval tv1, tv2;

    for (i = 0; i < n_perms; i++) {
        gettimeofday(&tv1, NULL); // Start time
        result = metodo(permArray[i], 0, N - 1); // Sort the permutation
        gettimeofday(&tv2, NULL); // End time

        if (result == ERR) { // Handle error in the sorting method
            for (int j = 0; j < n_perms; j++) free(permArray[j]);
            free(permArray);
            return ERR;
        }

        // Update operation counts
        if (result < min_ob) min_ob = result;
        if (result > max_ob) max_ob = result;
        total_ob += result;

        // Update execution time
        t1 = tv1.tv_sec * 1000.0 + tv1.tv_usec / 1000.0; // Time in milliseconds
        t2 = tv2.tv_sec * 1000.0 + tv2.tv_usec / 1000.0;
        total_time += (t2 - t1);

        free(permArray[i]); // Free the individual permutation
    }

    free(permArray); // Free the array of permutations

    // Calculate averages
    ptime->n_elems = n_perms;
    ptime->N = N;
    ptime->time = total_time / n_perms; // Average execution time
    ptime->average_ob = (double)total_ob / n_perms; // Average operation count
    ptime->min_ob = min_ob;
    ptime->max_ob = max_ob;

    return OK;
}

/***************************************************/
/* Function: generate_sorting_times               */
/* Description: Generates sorting times for       */
/* a range of array sizes                         */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, 
                             int num_min, int num_max, 
                             int incr, int n_perms) {
    if (!method || !file || num_min <= 0 || num_max < num_min || incr <= 0 || n_perms <= 0) {
        return ERR; // Parameter validation
    }

    int n_times = (num_max - num_min) / incr + 1; // Number of sizes to test
    PTIME_AA time_aa = (PTIME_AA)malloc(n_times * sizeof(TIME_AA));
    if (time_aa == NULL) return ERR; // Memory allocation check

    for (int i = 0; i < n_times; i++) {
        int N = num_min + (i * incr);
        if (average_sorting_time(method, n_perms, N, &time_aa[i]) == ERR) {
            free(time_aa); // Free memory on error
            return ERR;
        }
    }

    if (save_time_table(file, time_aa, n_times) == ERR) { // Save results to file
        free(time_aa);
        return ERR;
    }

    free(time_aa); // Free memory after successful execution
    return OK;
}

/***************************************************/
/* Function: save_time_table                      */
/* Description: Saves timing data to a file       */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times) {
    if (!file || !ptime || n_times <= 0) return ERR; // Parameter validation

    FILE* f = fopen(file, "w");
    if (!f) return ERR; // File opening check

    // Write table headers
    fprintf(f, "Size\tAverage Time\tAvg OB\tMin OB\tMax OB\n");

    // Write data for each size
    for (int i = 0; i < n_times; i++) {
        fprintf(f, "%d\t%.6f\t%.2f\t%d\t%d\n", 
                ptime[i].N, 
                ptime[i].time, 
                ptime[i].average_ob, 
                ptime[i].min_ob, 
                ptime[i].max_ob);
    }

    fclose(f); // Close the file
    return OK;
}
