#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include "HPLC_TP1_matrix.h"
#include <ctime> // Pour initialier la graine de rand
# include <time.h>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;
//#include <omp.h>


/* POUR L'EXECUTION
Le premier argument se refere au nombre de thread
Le second au nombre de colonnes
Le troisième au nombre de ligne
Exemple : ./HPLC_TP1_matrix 1 30000 40000
*/

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
	fill (Tab2, nb_row, nb_col, min , max);

	//display(Tab1, nb_row, nb_col);
	//display(Tab2, nb_row, nb_col);
	

	int before = (clock() *1000 / CLOCKS_PER_SEC);


	sum_two_mat(Tab_sum, Tab1 , Tab2 , nb_row ,  nb_col , nb_row , nb_col);
	//display(Tab_sum, nb_row, nb_col);

	double s= sum_mat( Tab1, nb_row ,  nb_col);
	//printf("%f\n", s);

	double A = 3;
	multi_mat( Tab1 , A ,  nb_row ,  nb_col );
	//display(Tab1, nb_row, nb_col);

	delete_matrix(Tab1 , nb_row, nb_col);
	delete_matrix(Tab2 , nb_row, nb_col);
	delete_matrix(Tab_sum , nb_row, nb_col);
	
	// CODE LOUISE

	char** tab_l1 = generate_letter_matrix(nb_row, nb_col);
	letter_fill(tab_l1 ,  nb_row,  nb_col);
	letter_display(tab_l1 ,  nb_row,  nb_col);
	map <char,int> alpha_test ;
	alpha_map(alpha_test );
	nb_letters(tab_l1, nb_row, nb_col , alpha_test);
	display_map(alpha_test);
	delete_letter_matrix(tab_l1 , nb_row, nb_col);

	return 0;
}


void delete_matrix( double ** Tab,int nb_row, int nb_col)
{
	for (int i = 0; i < nb_row; ++i)
	{
    	delete [] Tab[i];
    }
		delete [] Tab;		
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
   printf("\n");
   printf("\n");
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



double** generate_matrix( int nb_row, int nb_col)
{
	double** Tab = new double*[nb_row];
	for (int i = 0; i < nb_row; ++i)
	{
		Tab[i] = new double[nb_col];
		
	}
	return Tab;
}


//######### Code matrice lettre a tester #########

char** generate_letter_matrix( int nb_row, int nb_col)
{
	char** Tab = new char*[nb_row];
	for (int i = 0; i < nb_row; ++i)
	{
		Tab[i] = new char[nb_col];
		
	}
	return Tab;
}


void delete_letter_matrix( char ** Tab,int nb_row, int nb_col)
{
	for (int i = 0; i < nb_row; ++i)
	{
    	delete [] Tab[i];
    }
		delete [] Tab;		
}


void letter_fill(char** Tab , int nb_row, int nb_col)
{
	
	//# pragma omp parallel for

	for (int i =0 ; i< nb_row ; i++)
	{
		for (int j =0 ; j< nb_col ; j++)
		{
			Tab[i][j] = rand() % ('Z' - 'A' + 1) + 'A';
						
	
		}
	}
}



void letter_display(char** Tab, int nb_row, int nb_col )
{
  for (int i = 0; i < nb_row; i++)
  {
  	printf("[");
  	for(int j = 0; j < nb_col; j++)
  	{
    	printf("%c", Tab[i][j]);
    	/* We add a comma, except for the last element */
    	if (j < nb_row-1) 
    	{
      		printf(", ");
    	}
  	}
    printf("]\n");
   } 
   printf("\n");
   printf("\n");
}

void  alpha_map(std::map<char,int> &Alpha)
{
	for (int i =65; i<91; i++)
	{
		Alpha[char(i)]=0;
	
		
	}

}


void nb_letters(char**Tab, int nb_row, int nb_col, std::map<char,int> &Alpha)
{
	
	for (int i =0 ; i< nb_row ; i++)
	{
		for (int j =0 ; j< nb_col ; j++)
		{
			//permet de parcourir les colonnes du tableau resultat
			
			Alpha[Tab[i][j]] +=1;
			
		}
	}
	
}


void display_map (std::map<char,int> &Alpha)
{
	
	for (map<char, int >::iterator it=Alpha.begin() ; it!=Alpha.end(); ++it )
	{
		cout << it->first << '\t' << it->second  << endl;
	}
			
	
	
}

//################################################


void multi_mat(double ** m , const double  a ,  const int nb_row , const int nb_col    )
{	
	# pragma omp parallel
    # pragma omp for 
	  	//{

	for (int i = 0; i < nb_row; i++)
  	{
  		for (int j = 0; j < nb_col; j++)
  		{
   			m[i][j] = a*  m[i][j];
  		}
  	} 	
	 //	}   	
}





double Random (double min , double max) 
{	
	double f = (double)rand () / RAND_MAX;
	return min + f * (max-min+1); 
} 



double sum_mat( double** m, const int nb_row , const int nb_col)
{
  int s = 0;

  # pragma omp parallel for reduction (+:s)
  //{
  for (int i = 0; i < nb_row; i++)
  {
  		for (int j = 0; j < nb_col; j++)
  		{
   			s = s + m[i][j];
  		}
  }
  //}
  return s;
}

void sum_two_mat(double ** m3 ,  double ** m1 ,  double ** m2 , const int nb_row_m1 , const int nb_col_m1 , const int nb_row_m2 , const int nb_col_m2)
{	
	if (nb_col_m1!=nb_col_m2 and nb_row_m1!=nb_row_m2 )
	{
		printf("Les matrices n'ont pas la même taille. \n " );
	}
	else
	{
        # pragma omp parallel for 
	  	//{
 		for (int i =0 ; i< nb_col_m1  ; i++  ) 
 		{
 			for(int j = 0; j < nb_col_m1; j++)
 			{
 				m3[i][j] = m1[i][j] + m2[i][j];
 			}
 		}
	 //	}
   	}

}
