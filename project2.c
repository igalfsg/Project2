/* This file contains the source code for ECE 368 Project #2 on sorting

  Written by: Igal Flegmann
  This program takes two parameters, an array of intergers and a number of elements in the array.
  
 
  */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void printArray(int * array, int size){
  
  int i;
  printf("[ ");
  for (i = 0; i < size; i++)
    printf("%d \n", array[i]);
  printf("]\n");
}
 int cmpfunc (const void * a, const void * b)
{
   return (a - b);
}
 
inline void radixSort(int * array, int size){
  int i;
  int semiSorted[size];
  int significantDigit = 1;
  int largestNum = 0;
  int wrongs = 0;
  int negative[size];
  int j = 0;
  int tempo;
  int neglargest = 0;
  for(i = 0; i < size; i++){
    if(i >= 1 && array[i] < array[i - 1])
      wrongs++;
    else if(array[i] > largestNum)
      largestNum = array[i];
  }
  //printf("wrongs %d \n",wrongs);
  if (wrongs > (size - wrongs))
    {
      for( i = 0; i < (size / 2); i++)
	{
	  tempo = array[i];
	  array[i] = array[size - i -1];
	  array[size - i -1] = tempo;
	}
      wrongs = size - wrongs - 1;
    }
  if (wrongs == 0)
      return;
  for(i = 0; i < size; i++){
    if(array[i]< 0){
      negative[j] = (-1) * array[i];
      if (negative[i] > neglargest)
  	neglargest = negative[j];
      array[i] = 0;
      j++;
    }
  }
      while (largestNum / significantDigit > 0){// Loop until we reach the largest significant digit
	
	int bucket[10] = { 0 };
	
	// Counts the number of "keys" or digits that will go into each bucket
	for (i = 0; i < size; i++)
	  bucket[(array[i] / significantDigit) % 10]++;
	
	/**
	 * Add the count of the previous buckets,
	 * Acquires the indexes after the end of each bucket location in the array
	 * Works similar to the count sort algorithm
	 **/
	for (i = 1; i < 10; i++)
	  bucket[i] += bucket[i - 1];
	
	// Use the bucket to fill a "semiSorted" array
	for (i = size - 1; i >= 0; i--)
	  semiSorted[--bucket[(array[i] / significantDigit) % 10]] = array[i];
    
	
	for (i = 0; i < size; i++)
	  array[i] = semiSorted[i];
	
	// Move to next significant digit
	significantDigit *= 10;
	
      }
      significantDigit = 1;
      while (neglargest / significantDigit > 0){// Loop until we reach the largest significant digit
	
	int bucket[10] = { 0 };
	
	// Counts the number of "keys" or digits that will go into each bucket
	for (i = 0; i < size; i++)
	  bucket[(negative[i] / significantDigit) % 10]++;
	
	/**
	 * Add the count of the previous buckets,
	 * Acquires the indexes after the end of each bucket location in the array
	 * Works similar to the count sort algorithm
	 **/
	for (i = 1; i < 10; i++)
	  bucket[i] += bucket[i - 1];
	
	// Use the bucket to fill a "semiSorted" array
	for (i = size - 1; i >= 0; i--)
	  semiSorted[--bucket[(negative[i] / significantDigit) % 10]] = negative[i];
    
	
	for (i = 0; i < size; i++)
	  negative[i] = semiSorted[i];
	
	// Move to next significant digit
	significantDigit *= 10;
	
      }
      for (i=0; i < j; i++)
	array[i]= negative[j-1-i] * (-1);
      //  }
      //else {
  
    //}
}
inline void compy(int * array, int size){
  int i;
  int wrongs = 0;
  int tempo;
  for(i = 0; i < size; i++){
    if(i >= 1 && array[i] < array[i - 1])
      wrongs++;
  }
  if (wrongs > (size - wrongs))
    {
      for( i = 0; i < (size / 2); i++)
	{
	  tempo = array[i];
	  array[i] = array[size - i -1];
	  array[size - i -1] = tempo;
	}
      wrongs = size - wrongs - 1;
    }
  if (wrongs == 0)
      return;
 qsort(array, size, sizeof(int), cmpfunc);
}
 
int main(){
  
  printf("\n\nRunning Radix Sort Example in C!\n");
  printf("----------------------------------\n");
  int size =1000000;
  int list[1000000];
  int check[size];
  int check1[size];
  int i;
  clock_t start, end;
  double cpu_timeu;

  for(i = 0; i< size; i++)
    {
      //      if (i % 2){
      list[i] =( size - i);
      check[i] = list[i];
      check1[i] = check[i];
      // }
      //else
      //{
      //  list[i] =( i - size);
      //  check[i] = list[i];
      //}
      }

  printf("Decending\n");
  /* start = clock(); */
  /* radixSort(&list[0], size); */
  /* end = clock(); */
  /* cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC; */
  /* fprintf(stdout,"readix %f\n ", cpu_timeu); */

  //printArray(&list[0], size);
 
  start = clock();
  qsort(check, size, sizeof(int), cmpfunc);
  end = clock();
  cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stdout,"qsort time = %f \n", cpu_timeu);
  
  start = clock();
  compy(list,size);
  end = clock();
  cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stdout,"merge time = %f \n", cpu_timeu);
  for(i = 0; i< size; i++)
    {
      // if (check[i] != list[i])
	//	fprintf(stdout,"you fucked up son: %d, %d \n", check[i], list[i]);
     
    }

  for(i = 0; i< size; i++)
    {
      //      if (i % 2){
      list[i] = rand() % 2000000;
      check[i] = list[i];
      check1[i] = check[i];
      // }
      //else
      //{
      //  list[i] =( i - size);
      //  check[i] = list[i];
      //}
      }

  printf("Random\n");
  start = clock();
  compy(list, size);
  end = clock();
  cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stdout,"readix %f\n ", cpu_timeu);

 
  start = clock();
  qsort(check, size, sizeof(int), cmpfunc);
  end = clock();
  cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stdout,"qsort time = %f \n", cpu_timeu);
  

for(i = 0; i< size; i++)
    {
      //      if (i % 2){
      list[i] = size % 2;
      check[i] = list[i];
      check1[i] = check[i];
      // }
      //else
      //{
      //  list[i] =( i - size);
      //  check[i] = list[i];
      //}
      }

  /* for (i = 25; i < 200; i++) */
  /*   { */
  /*     list[i] = rand(); */
  /*     check[i] = list[i]; */
  /*   } */
  
  printf("1 0\n");
  start = clock();
  compy(&list[0], size);
  end = clock();
  cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stdout,"readix %f\n ", cpu_timeu);

 
  start = clock();
  qsort(check, size, sizeof(int), cmpfunc);
  end = clock();
  cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stdout,"qsort time = %f \n", cpu_timeu);
 

for(i = 0; i< size; i++)
    {
      list[i] = size - i;
      check[i] = list[i];
      check1[i] = check[i];
      }

  for (i = 25; i < 200; i += 15)
    {
      list[i] = rand();
      check[i] = list[i];
    }
  
  printf("1 0\n");
  start = clock();
  compy(list, size);
  end = clock();
  cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stdout,"readix %f\n ", cpu_timeu);

 
  start = clock();
  qsort(check, size, sizeof(int), cmpfunc);
  end = clock();
  cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stdout,"qsort time = %f \n", cpu_timeu);
  
  return 0;
}
