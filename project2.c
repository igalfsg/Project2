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
    printf("%d ", array[i]);
  printf("]\n");
}
 
 
inline void radixSort(int * array, int size){
  
  printf("\n\nRunning Radix Sort on Unsorted List!\n\n");
 
  // Base 10 is used
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
    if(array[i] < array[i - 1])
      wrongs++;
    else if(array[i] > largestNum)
      largestNum = array[i];
  }
  if (wrongs > (size - wrongs))
    {
      for( i = 0; i < size; i++)
	{
	  tempo = array[i];
	  array[i] = array[size - i -1];
	  array[size - i -1] = tempo;
	}
      wrongs = size - wrongs;
    }
  if (wrongs > 100)  
    {
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
    }
  else {
    if (wrongs == 0)
      return;
    for (i = 1 ; i <= size - 1; i++) {
    j = i;
 
    while ( j > 0 && array[j] < array[j-1]) {
      tempo          = array[j];
      array[j]   = array[j-1];
      array[j-1] = tempo;
 
      j--;
    }
  }
  }
}
 
int main(){
  
  printf("\n\nRunning Radix Sort Example in C!\n");
  printf("----------------------------------\n");
  int size =10;
  int list[10]={0, -2, 4, 5, 3, -4, 5, 6, 3, 2};
  int i;
  clock_t start, end;
  double cpu_timeu;

  /* for(i = 0; i< size; i++) */
  /*   { */
  /*     list[i] = rand(); */
  /*   } */
  
  printf("\nUnsorted List: ");
  printArray(&list[0], size);
  start = clock();
  radixSort(&list[0], size);
  end = clock();
  cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stdout,"%f ", cpu_timeu);
  printArray(&list[0], size);
  printf("\n");
  
  return 0;
}
