#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

int random_num(int inf, int sup);

void main(){
    srand(time(NULL));
    int array[11];
    int n;
    for(int i = 0; i<=10;i++){
        array[i]=0;
    }
    for(int i=0;i<50000;i++){
        n=random_num2(1,10);
        array[n]++;
    }
    for(int i = 0; i<=10;i++){
        printf("%d\t%d\n",i, array[i]);
    }
}

int random_num(int inf, int sup)
{
  int c= sup-inf+1;
  int rd_num;
  rd_num = inf+(int)((float)c*rand()/(RAND_MAX+1.0)); 
  return rd_num;
}

int random_num2(int inf, int sup)
{
  int rd_num;
  rd_num = (rand() % (sup - inf + 1)) + inf; 
  return rd_num;
}