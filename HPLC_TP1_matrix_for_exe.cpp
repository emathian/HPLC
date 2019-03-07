#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include "HPLC_TP1_matrix_for_exe.h"
#include <ctime> // Pour initialier la graine de rand
# include <time.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string>
#include <fstream> //

using namespace std;
#include <omp.h>
#define SIZE 256// Max size of file_name


/* POUR L'EXECUTION
Le premier argument se refere à la méthode employée force_forte argv[1]=0 ou force_faible argv[1]=1
Le second au nombre de runs
Exemple : HPLC_TP1_matrix_for_exe 0 10
*/

int main(int argc, char** argv) {
	srand((int) time(0));

	char file_name[SIZE];
	cout << "Entrer le nom du fichier de sortie : ";
	cin>> file_name;
	int force_forte_faible = atoi(argv[1]); // force forte = 0 ; force faible =1
	int nb_runs = atoi(argv[2]); // nombre de repetitions
	//string file_name =  "test_main_func.txt"; // Nom du fichier de sortie

	ofstream myfile;
  	myfile.open ( file_name, fstream::app);
	myfile <<  "nb_thread \t nb_rows\t nb_cols \tdiff1 somme deux vect\tdiff2 somme vect\tdiff3 multi vect\n";	
	myfile.close();

	if (force_forte_faible ==0){
	
	int V_nb_thread[] = {1,2,4};
	int V_nb_rows[] = {10,50,100, 2000, 300}; //{1000000,5000000,10000000, 20000000, 30000000};
	int V_nb_cols[] = {10,50,100, 2000, 300};//{1000000,5000000,10000000, 20000000, 30000000};  


	for (int z=0; z<nb_runs ; z++){ // nb runs
	for (int i=0 ; i<3 ; i++){
	for (int j=0 ; j<4 ; j++){

		int nb_row =V_nb_rows[j] ;
		int nb_col =V_nb_cols[j] ;
		int nb_thread = V_nb_thread[i];
		omp_set_num_threads(nb_thread); 
		printf("%d \n", nb_row);
		double A = 2;
		main_func( nb_thread, nb_row, nb_col, file_name, A);
	
		} // end de i
	  } // end de j
   }// end de z
	
} // End if


	else {
		
		map <int, vector<int>  > cond_force_faible;

		cond_force_faible [1]=vector<int>(1000,1000);//(10000000,10000000);
  	cond_force_faible [2]=vector<int>(2000,2000);//(20000000,20000000)
  	cond_force_faible [3]=vector<int>(3000,3000);//(30000000,30000000)
 		cond_force_faible [4]=vector<int>(4000,4000);//(40000000,40000000)


		for (int z=0; z<nb_runs ; z++){ // nb runs
		for (map<int, vector<int> >::iterator it=cond_force_faible.begin() ; it!=cond_force_faible.end(); ++it ){
			int nb_thread = it->first;	
			vector<int>  values = it->second;
			int nb_row = values[0] ;
		//	printf("%d", nb_row);
			int nb_col = values[1];
			omp_set_num_threads(nb_thread); 
			double A = 2;
			main_func( nb_thread, nb_row, nb_col, file_name, A);
		} // end it map
	  } // end z
	 //  myfile.close();
   } // end else
	
	myfile.close();
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


void main_func(const int nb_thread, const int  nb_row, const int  nb_col, const char* file_name , const double A)
{
	ofstream myfile;
	myfile.open ( file_name, fstream::app);

	double** Tab1 = generate_matrix(nb_row,nb_col);
	double** Tab2 = generate_matrix(nb_row,nb_col);
	double** Tab_sum = generate_matrix(nb_row,nb_col);

	double min = 0; 
	double max = 10; //RAND_MAX;

	fill (Tab1, nb_row, nb_col, min , max);
	fill (Tab2, nb_row, nb_col, min , max);

	int before1 = (clock() *1000 / CLOCKS_PER_SEC);
	sum_two_mat(Tab_sum, Tab1 , Tab2 , nb_row ,  nb_col , nb_row , nb_col);
	int after1=  (clock() *1000 / CLOCKS_PER_SEC);
	int diff1 = after1 - before1;


	
	int before2 = (clock() *1000 / CLOCKS_PER_SEC);
	double s= sum_mat( Tab1, nb_row ,  nb_col);
	int after2=  (clock() *1000 / CLOCKS_PER_SEC);
	int diff2 = after2 - before2;
	
	int before3 = (clock() *1000 / CLOCKS_PER_SEC);
	multi_mat( Tab1 , A ,  nb_row ,  nb_col );
	int after3=  (clock() *1000 / CLOCKS_PER_SEC);
	int diff3 = after3 - before3;
	myfile <<  nb_thread <<"\t"<< nb_row << "\t" << nb_col <<"\t"  << diff1 <<"\t" << diff2 <<"\t" << diff3 <<   "\n";
  	myfile.close();

  delete_matrix(Tab1 , nb_row, nb_col);
	delete_matrix(Tab2 , nb_row, nb_col);
	delete_matrix(Tab_sum , nb_row, nb_col);

}



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

