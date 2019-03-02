#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include "HPLC_TP1_matrix.h"
#include <ctime> // Pour initialier la graine de rand
# include <time.h>
#include <iostream>
#include <fstream>

using namespace std;
//#include <omp.h>

int main(int argc, char** argv) {

	srand((int) time(0));
	int nb_thread = atoi(argv[3]);
	//omp_set_num_threads(nb_thread); 
	
	
	int nb_row = atoi(argv[1]); // Atoi Ascii to integer
	int nb_col = atoi(argv[2]);
	
	double** Tab1 = generate_matrix(nb_row,nb_col);
	double** Tab2 = generate_matrix(nb_row,nb_col);
	double** Tab_sum = generate_matrix(nb_row,nb_col);


	double min = 0; 
	double max = 10; //RAND_MAX;


	fill (Tab1, nb_row, nb_col, min , max);
	//fill (Tab2, nb_row, nb_col, min , max);

	display(Tab1, nb_row, nb_col);
	//display(Tab2, nb_row, nb_col);
	
/*
	int before = (clock() *1000 / CLOCKS_PER_SEC);


	sum_two_vector(Tab_sum , Tab1 , Tab2 ,Taille_tab  , Taille_tab );
	//display(Tab_sum, Taille_tab);

	double s  = sum_vector(Tab1 , Taille_tab);
	printf("Somme du vecteur 1   :  %f \n" , s);
	
	multi_vector(Tab_sum , 2 ,  Taille_tab );

	int after=  (clock() *1000 / CLOCKS_PER_SEC);
	int diff = after - before;
	printf("Durée  :  %d \n", diff );

  	ofstream myfile;
  	myfile.open ("somme_deux_vexct_result.txt", fstream::app);
  	myfile <<  nb_thread <<"\t"<< Taille_tab <<"\t"  << diff <<"\t" <<  "\n";
  	myfile.close();
  
	
	delete [] Tab1;
	delete [] Tab2;
	delete [] Tab_sum;
*/	
	delete_matrix(Tab1 , nb_row, nb_col);
	delete_matrix(Tab2 , nb_row, nb_col);
	delete_matrix(Tab_sum , nb_row, nb_col);
	
	/*for (int i = 0; i < nb_row; ++i)
	{
    	
    	delete [] Tab2[i];
    	delete [] Tab_sum[i];
    }
	
		delete [] Tab2;
		delete [] Tab_sum;
*/
	return 0;
}

double** generate_matrix( int nb_row, int nb_col){
	double** Tab = new double*[nb_row];

	for (int i = 0; i < nb_row; ++i){
		Tab[i] = new double[nb_col];
		
	}
	return Tab;
}


void delete_matrix( double ** Tab,int nb_row, int nb_col){
	for (int i = 0; i < nb_row; ++i)
	{
    	delete [] Tab[i];
    }
		delete [] Tab;
		
}

void fill(double** Tab , int nb_row, int nb_col, int min, int max )
{
	
	# pragma omp parallel for

	for (int i =0 ; i< nb_row ; i++)
	{
		for (int j =0 ; j< nb_col ; j++)
		{
			Tab[i][j] = Random(min, max);
		}
	}

}


void display(double** Tab, int nb_row, int nb_col )
{
  
	
  for (int i = 0; i < nb_row; i++)
  {
  	 printf("[");
  	for(int j = 0; j < nb_col; j++)
  	{
    	
    	printf("%f", Tab[i][j]);
    	/* We add a comma, except for the last element */
    	if (j < nb_row-1) 
    	{
      	printf(", ");
    	}
  	}
  	printf("]\n");
   } 
}

double Random (double min , double max) 
{	
	double f = (double)rand () / RAND_MAX;
	return min + f * (max-min+1); 
} 

void sum_two_vector(double * v3 , const double * v1 , const double * v2 , const int taille_v1 , const int taille_v2   )

{	
	if (taille_v1 != taille_v2 )
	{
		printf("Les vecteurs ont des longueurs diffférentes" );
	}
	else
	{
		
        # pragma omp parallel for 
	  	//{
 		for (int i =0 ; i< taille_v1  ; i++  ) 
 			{
 			
 			v3[i] = v1[i] + v2[i];
 			}
	 //	}
   	}

}

double sum_vector(const double Tab[], int Taille_tab)
{
  int s = 0;
  int i;
  # pragma omp parallel for reduction (+:s)
  //{
  for (i = 0; i < Taille_tab; i++)
  	{
    s = s + Tab[i];
  	}
  //}
  return s;
 
}

void multi_vector(double * v , const double  a ,  const int taille_v    )

{	

	{
		# pragma omp parallel
        # pragma omp for 
	  	//{
 		for (int i =0 ; i< taille_v  ; i++  ) 
 			{
 			
 			v[i] = v[i] * a;
 			}
	 //	}
   	}

}

