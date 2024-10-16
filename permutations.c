/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */


#include "permutations.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

#define ERR -1
/************************************************************************/
/* Function: random_num                                                 */
/* Rutine that generates a random number between two given numbers      */
/*                                                                      */
/* Input:                                                               */
/* int inf: lower limit                                                 */
/* int sup: upper limit                                                 */
/* Output:                                                              */
/* int: random number                                                   */
/************************************************************************/
int random_num(int inf, int sup)
{
  if(inf < 0  || sup < 0 || sup < inf) return ERR; //Parameters Check

  int c=sup-inf;
  int rd_num;
  rd_num = inf+(int)((float)c*rand()/(RAND_MAX+1.0)); //Inclusive
  
  return rd_num;
}

/******************************************************************************************/
/* Function: generate_perm Date:                                                          */
/* Rutine that generates a random permutation                                             */
/* Input:                                                                                 */
/* int n: number of elements in the permutation                                           */
/* Output:                                                                                */
/* int *: pointer to integer array that contains the permutation or NULL in case of error */
/******************************************************************************************/
int* generate_perm(int N)
{
  if(N <= 0) return NULL;//Parameters Check
  int i, t, r;
  int*perm=(int*)malloc(sizeof(int)*N);
  if(perm == NULL) return NULL;//Malloc check
  for(i=0;i<N;i++) 
    perm[i]=i+1;
  for(i=0;i<N;i++){
    t=perm[i];
    r=random_num(i,N-1);
    if (r == ERR){ //Random Number Check
      free(perm); //Free memory
      return NULL; 
    }
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
  if(n_perms<1 || N<1) return ERR; //Parameters check

  int**permArray=(int**)malloc(sizeof(int*)*n_perms); 
  
  if(permArray == NULL) return ERR; //Malloc Check

  int i;
  for(i=0;i<n_perms;i++){
    permArray[i]=generate_perm(N);
    if (permArray[i]==ERR){ //Gen Perm Check
      free(permArray); //Free memory
      return ERR;
    }
  }
  return permArray;
}