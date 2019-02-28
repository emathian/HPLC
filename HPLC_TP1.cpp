#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include "HPLC_TP1.h"
#include <ctime> // Pour initialier la graine de rand
# include <time.h>
using namespace std;
#include <omp.h>

int main(int argc, char** argv) {
	omp_set_num_threads(1);
	srand((int) time(0));
	int Taille_tab = atoi(argv[1]); // Atoi Ascii to integer
	double* Tab1;
	double* Tab2;
	double* Tab_sum;
	
	double min = 0; 
	double max = 10; //RAND_MAX;


	Tab1 = new double[Taille_tab];
	Tab2 = new double[Taille_tab]; 
	Tab_sum = new double[Taille_tab] ;

	int before = (clock() *1000 / CLOCKS_PER_SEC);

	fill (Tab1, Taille_tab, min , max);
	fill (Tab2, Taille_tab, min , max);
	display(Tab1, Taille_tab);
	display(Tab2,  Taille_tab);

	sum_two_vector(Tab_sum , Tab1 , Tab2 ,Taille_tab  , Taille_tab );
	display(Tab_sum, Taille_tab);

	double s  = sum_vector(Tab1 , Taille_tab);
	printf("Somme du vecteur 1   :  %f \n" , s);

	int after=  (clock() *1000 / CLOCKS_PER_SEC);
	int diff = after - before;
	printf("Durée  :  %d \n", diff );
	delete [] Tab1;
	delete [] Tab2;
	delete [] Tab_sum;

	return 0;
}

void fill(double* Tab , int Taille_tab, int min, int max )
{
	for (int i =0 ; i< Taille_tab +1 ; i++  ) 
	{
		Tab[i] = Random(min, max);
	}

}


void display(const double* Tab, int Taille_tab)
{
  int i;
  printf("[");
  for (i = 0; i < Taille_tab; i++)
  {
    printf("%f", Tab[i]);

    /* We add a comma, except for the last element */
    if (i < Taille_tab-1) 
    {
      printf(", ");
    }
  }
  printf("]\n");
}

double Random (double min , double max) 
{	
	double f = (double)rand () / RAND_MAX;
	return min + f * (max-min+1); 
} 

void sum_two_vector(double * v3 , const double * v1 , const double * v2 , const int taille_v1 , const int taille_v2   )

{	
	if (taille_v1 != taille_v2 ){
		printf("Les vecteurs ont des longueurs diffférentes" );
	}
	else{
 		for (int i =0 ; i< taille_v1  ; i++  ) 
 		{
 			
 			v3[i] = v1[i] + v2[i];
 		}

	}

}

double sum_vector(const double Tab[], int Taille_tab)
{
  int s = 0;
  int i;
  for (i = 0; i < Taille_tab; i++)
  {
    s = s + Tab[i];
  }
  return s;
}