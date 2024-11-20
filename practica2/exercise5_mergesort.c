/***********************************************************/
/* Program: exercise5                  Date:               */
/* Authors:                                                */
/*                                                         */
/* Program that writes in a file                           */
/* the average times of the MergeSort algorithm            */
/*                                                         */
/* Input: Command Line                                     */
/* -num_min: lowest number of table elements               */
/* -num_max: highest number of table elements              */
/* -incr: increment                                        */
/* -numP: number of permutations to average                */
/* -outputFile: Output file name                           */
/* Output: 0 in case of success                            */
/* -1 otherwise                                            */
/***********************************************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "sorting.h"
#include "times.h"

int main(int argc, char** argv) {
    int i, num_min, num_max, incr, n_perms;
    char nombre[256];
    short ret;

    srand(time(NULL));

    if (argc != 11) {
        fprintf(stderr, "Error in input parameters:\n\n");
        fprintf(stderr, "%s -num_min <int> -num_max <int> -incr <int>\n", argv[0]);
        fprintf(stderr, "\t\t -numP <int> -outputFile <string> \n");
        fprintf(stderr, "Where:\n");
        fprintf(stderr, "-num_min: lowest number of table elements\n");
        fprintf(stderr, "-num_max: highest number of table elements\n");
        fprintf(stderr, "-incr: increment\n");
        fprintf(stderr, "-numP: number of permutations to average\n");
        fprintf(stderr, "-outputFile: Output file name\n");
        exit(-1);
    }

    printf("Practice number 1, section 5\n");
    printf("Done by: your names\n");
    printf("Group: Your group\n");
    
    /* Check command line */
    for (i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-num_min") == 0) {
            num_min = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-num_max") == 0) {
            num_max = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-incr") == 0) {
            incr = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-numP") == 0) {
            n_perms = atoi(argv[++i]);
        } else if (strcmp(argv[i], "-outputFile") == 0) {
            strcpy(nombre, argv[++i]);
        } else {
            fprintf(stderr, "Wrong parameter %s\n", argv[i]);
            exit(-1);
        }
    }

    /* Compute times for MergeSort */
    ret = generate_sorting_times(MergeSortFlag, nombre, num_min, num_max, incr, n_perms);
    if (ret == ERR) {
        printf("Error in function generate_sorting_times\n");
        exit(-1);
    }

    printf("Correct output. Results written to %s\n", nombre);

    return 0;
}