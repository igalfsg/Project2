#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <time.h>

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
      list[i] =( size - i);
      check[i] = list[i];
      check1[i] = check[i];
      }

  printf("Decending\n");
  start = clock();
  sort(list, size);
  end = clock();
  cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stdout,"sort %f\n ", cpu_timeu);

 
  /* start = clock(); */
  /* qsort(check, size, sizeof(int), cmpfunc); */
  /* end = clock(); */
  /* cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC; */
  /* fprintf(stdout,"qsort time = %f \n", cpu_timeu); */
  
  start = clock();
  int_tim_sort(check1,size);
  end = clock();
  cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stdout,"tim = %f \n", cpu_timeu);
  for(i = 0; i< size; i++)
    {
      if (list[i] < list[i-1])
	 fprintf(stdout,"you fucked up son: %d, %d \n", list[i],  list[i -1]);
     
    }

  for(i = 0; i< size; i++)
    {
      //      if (i % 2){
      list[i] = rand() % 2000000;
      if(i%2)
	check[i] = -1 * list[i];
      else
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
  sort(list, size);
  end = clock();
  cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stdout,"quick %f\n ", cpu_timeu);

 
  /* start = clock(); */
  /* qsort(check, size, sizeof(int), cmpfunc); */
  /* end = clock(); */
  /* cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC; */
  /* fprintf(stdout,"qsort time = %f \n", cpu_timeu); */
  
  start = clock();
  int_tim_sort(check1,size);
  end = clock();
  cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stdout,"tim = %f \n", cpu_timeu);

for(i = 0; i< size; i++)
  {
    //fprintf(stdout,"%d\n",check[i]);
    //  if (check[i] < check[i-1])
    // fprintf(stdout,"you fucked up son: %d, %d \n", check[i],  check[i -1]);
     
    }
for(i = 0; i< size; i++)
    {
      //      if (i % 2){
      list[i] = (i % 2) * -1;
      check[i] = list[i];
      check1[i] = check[i];
      //fprintf(stdout,"%d\n",list[i]);
      }

   printf("1 0\n");
  start = clock();
  sort(list, size);
  end = clock();
  cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stdout,"quick %f\n ", cpu_timeu);

 
  /* start = clock(); */
  /* qsort(check, size, sizeof(int), cmpfunc); */
  /* end = clock(); */
  /* cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC; */
  /* fprintf(stdout,"qsort time = %f \n", cpu_timeu); */
  
  start = clock();
  int_tim_sort(check1,size);
  end = clock();
  cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stdout,"tim = %f \n", cpu_timeu);
 
for(i = 0; i< size; i++)
    {
      //fprintf(stdout,"%d\n",list[i]);
      /* // if (check1[i] < check1[i-1]) */
      /* // fprintf(stdout,"you fucked up son: %d, %d \n", list[i],  list[i -1]); */
     
    }
for(i = 0; i< size; i++)
    {
      list[i] = size - i;
      check[i] = list[i];
      check1[i] = check[i];
      }

  for (i = 25; i < 200; i += 15)
    {
      list[i] =-1* rand();
      check[i] = list[i];
      check1[i] = check[i];
    }
  check[3]=0;
  printf("almost sorted\n");
  start = clock();
  sort(list, size);
  end = clock();
  cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stdout,"heap %f\n ", cpu_timeu);

 
  /* start = clock(); */
  /* qsort(check, size, sizeof(int), cmpfunc); */
  /* end = clock(); */
  /* cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC; */
  /* fprintf(stdout,"qsort time = %f \n", cpu_timeu); */
  
  start = clock();
  int_tim_sort(check1,size);
  end = clock();
  cpu_timeu = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stdout,"tim = %f \n", cpu_timeu);
  

for(i = 1; i< size; i++)
    {
      // fprintf(stdout, "%d\n", check[i-1]);
      if (list[i] <= list[i-1])
      fprintf(stdout,"you fucked up son: %d, %d \n", list[i],  list[i -1]);
     
    }
return 0;
}
