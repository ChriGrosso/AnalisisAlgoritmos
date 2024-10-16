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

#include "times.h"
#include "sorting.h"
#include "permutations.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

/*struct timeval {
    time_t tv_sec;  // secondi dall'Epoch
    suseconds_t tv_usec;  // microsecondi
};*/

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
  if(n_perms <= 0 || N <= 0 || ptime == NULL)return ERR; //Parameters check
  int i,j;
  double t1,t2,contT=0;
  int contOB=0,averageOB=0,minOB=2147483647,maxOB=0;
  int**permArray=generate_permutations(n_perms, N);
  if(permArray == NULL) return ERR; //Malloc check
  struct timeval tv1,tv2;
  gettimeofday(&tv1,NULL);
  for(i=0;i<n_perms;i++){
    j=metodo(permArray[i],0,N-1);
    if(j==ERR) return ERR; //return Check
    //OB Operations
    if(j<minOB) minOB=j;
    if(j>maxOB) maxOB=j;
    contOB+=j;
  }
  gettimeofday(&tv2,NULL);
  t1 = tv1.tv_sec*1000 + (tv1.tv_usec / 1000.0); //in ms
  t2 = (tv2.tv_sec*1000 + (tv2.tv_usec / 1000.0) - t1); //in ms
  contT=t2/n_perms;
  averageOB=contOB/n_perms;

  //saving data in struct
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
  int n_times = (num_max - num_min) / incr + 1; //num min included
  int ret,N;
    PTIME_AA time_aa = (PTIME_AA) malloc(n_times * sizeof(TIME_AA));
    if (time_aa == NULL) return ERR;
    for (int i = 0; i < n_times; i++) {
        N=num_min+(incr*i);
        ret=average_sorting_time(method, n_perms, N, &time_aa[i]);
        if(ret == ERR){ //Return check
          free(time_aa); //free memory
          return ERR; 
        } 
    }
    if(save_time_table(file,time_aa,n_times)==ERR) return ERR; //Return Check
    
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
    if (!f) return ERR; //File Check

    
    fprintf(f, "Size\tTime\t\tAvg OB\tMax OB\tMin OB\n");

    // Writing Data
    for(int i = 0; i<n_times;i++){
      fprintf(f, "%d\t%.6f\t%.2f\t%d\t%d\n", ptime[i].N, ptime[i].time, 
          ptime[i].average_ob, ptime[i].max_ob, ptime[i].min_ob);
      //fprintf(f, "%d\t%f\n", ptime[i].N, ptime[i].average_ob);
      }
    fclose(f);
    return OK;
}


