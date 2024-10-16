/***********************************************************/
/* Program: exercise5                  Date:               */
/* Authors:                                                */
/*                                                         */
/* Programa that writes in a file                          */
/* the average times of the algorithm                      */
/* of sorting by insertion                                 */
/*                                                         */
/* Input: Command Line                                     */
/* -num_min: lowest number of table elements               */
/* -num_max: highest number of table elements              */
/* -incr: increment\n                                      */
/* -numP: number of permutations to average                */
/* -outputFile: Output file name                           */
/* Output: 0 in case of error                              */
/* -1 otherwise                                            */
/***********************************************************/


#define ERR -1
#define OK (!(ERR))

typedef int (* pfunc_sort)(int*, int, int);

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

/* type definitions */
typedef struct time_aa {
  int N;           /* size of each element */
  int n_elems;     /* number of elements to average */
  double time;   /* average clock time */
  double average_ob; /* average number of times that the OB is executed */
  int min_ob;      /* minimum of executions of the OB */
  int max_ob;      /* maximum of executions of the OB */
} TIME_AA, *PTIME_AA;


/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */


/***************************************************/
/* Function: average_sorting_time Date:            */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, 
                              int n_perms,
                              int N, 
                              PTIME_AA ptime)
{
  int i,j;
  double t1,t2,contT;
  int contOB=0,averageOB=0,minOB=0,maxOB=0;
  t1=(double)time(NULL);
  int**permArray=generate_permutations(n_perms, N);
  for(i=0;i<n_perms;i++){
    t1=(double)time(NULL);
    j=metodo(permArray[i],permArray[i][0],permArray[i][N]);
    if(j=ERR)
      return ERR;
    t2=(double)time(NULL)-t1;
    if(j<minOB)
      minOB=j;
    if(j>maxOB)
      maxOB=j;
    contOB+=j;
    contT+=t2;
  }
  contT=contT/n_perms;
  averageOB=contOB/n_perms;
  ptime->n_elems=n_perms;
  ptime->N=N;
  ptime->time=contT;
  ptime->average_ob=averageOB;
  ptime->max_ob=maxOB;
  ptime->min_ob=minOB;
  return OK;

}

/***************************************************/
/* Function: generate_sorting_times Date:          */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, 
                                int num_min, int num_max, 
                                int incr, int n_perms)
{
  int n_times = (num_max - num_min) / incr + 1;
  int ret,N;
    PTIME_AA *time_aa = (PTIME_AA*) malloc(n_times * sizeof(TIME_AA*));
    if (!time_aa) return ERR;
    for (int i = 0; i < n_times; i++) {
        N=num_min+(incr*i);
        ret=average_sorting_time(method, n_perms, N, time_aa[i]);
        if(save_time_table(file, time_aa[i],n_times)==ERR) return ERR;
    }
    
    return OK;
}

/***************************************************/
/* Function: save_time_table Date:                 */
/*                                                 */
/* Your documentation                              */
/***************************************************/
short save_time_table(char* file, PTIME_AA ptime, int n_times)
{
  FILE *f = fopen(file, "w");
    if (!f) return ERR;

    // Imprimir encabezado
    fprintf(f, "Size\tTime\tAvg OB\tMax OB\tMin OB\n");

    // Escribir cada fila de la tabla
    for (int i = 0; i < n_times; i++) {
        fprintf(f, "%d\t%.6f\t%.2f\t%d\t%d\n", ptime->n_elems, ptime->time, 
                ptime->average_ob, ptime->max_ob, ptime->min_ob);
    }
    fclose(f);
    return OK;
}


/***************************************************/
/* Function: SelectSort    Date:                   */
/* Your comment                                    */
/***************************************************/
int BubbleSort(int* array, int ip, int iu){
  if (array == NULL || ip < 0 || iu < ip) {
        return ERR; /* Errore negli input*/
    }
    int count = 0; /* Numero di confronti*/
    int temp;
    for (int i = ip; i < iu; i++) {
        for (int j = ip; j < iu - (i - ip); j++) {
            count++;  /*Incrementa il contatore delle operazioni base (confronti)*/
            if (array[j] > array[j + 1]) {
                /* Scambia gli elementi se non sono in ordine*/
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    return count; /* Restituisce il numero di confronti*/
}

int BubbleSortFlag(int* array, int ip, int iu)
{
  /* your code */
}

int random_num(int inf, int sup)
{
  int c= sup-inf;
  int rd_num;
  rd_num = inf+(int)((float)c*rand()/(RAND_MAX+1.0)); 
  return rd_num;
}

/***************************************************/
/* Function: generate_perm Date:                   */
/* Authors:                                        */
/*                                                 */
/* Rutine that generates a random permutation      */
/*                                                 */
/* Input:                                          */
/* int n: number of elements in the permutation    */
/* Output:                                         */
/* int *: pointer to integer array                 */
/* that contains the permitation                   */
/* or NULL in case of error                        */
/***************************************************/
int* generate_perm(int N)
{
  int i, t, r;
  int*perm=(int*)malloc(sizeof(int)*N);
  for(i=0;i<N;i++){
    perm[i]=i+1;
  }
  for(i=0;i<N;i++){
    t=perm[i];
    r=random_num(0,N-1);
    perm[i]=perm[r];
    perm[r]=t;
  }
  return perm;
}

/***************************************************/
/* Function: generate_permutations Date:           */
/* Authors:                                        */
/*                                                 */
/* Function that generates n_perms random          */
/* permutations with N elements                    */
/*                                                 */
/* Input:                                          */
/* int n_perms: Number of permutations             */
/* int N: Number of elements in each permutation   */
/* Output:                                         */
/* int**: Array of pointers to integer that point  */
/* to each of the permutations                     */
/* NULL en case of error                           */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{
  int**permArray=(int**)malloc(sizeof(int*)*n_perms);
  int i;
  for(i=0;i<n_perms;i++){
    permArray[i]=generate_perm(N);
  }
  return permArray;
}

int main(int argc, char** argv)
{
  int i, num_min, num_max, incr, n_perms;
  char nombre[256];
  short ret;

  srand(time(NULL));

  if (argc != 11) {
    fprintf(stderr, "Error in input parameters:\n\n");
    fprintf(stderr, "%s -num_min <int> -num_max <int> -incr <int>\n", argv[0]);
    fprintf(stderr, "\t\t -numP <int> -outputFile <string> \n");
    fprintf(stderr, "Donde:\n");
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
  
  /* check command line */
  for(i = 1; i < argc ; i++) {
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
      fprintf(stderr, "Wrong paramenter %s\n", argv[i]);
    }
  }

  /* compute times */
  ret = generate_sorting_times(BubbleSort, nombre,num_min, num_max,incr, n_perms);
  if (ret == ERR) { /* ERR_TIME should be a negative number */
    printf("Error in function generate_sorting_times\n");
    exit(-1);
  }
  printf("Correct output \n");

  return 0;
}