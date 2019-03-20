#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include "HPLC_TP1_exo2_for_exe.h"
#include <ctime> // Pour initialier la graine de rand
# include <time.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

using namespace std;
#include <omp.h>
#define SIZE 256// Max size of file_name

/* POUR L'EXECUTION
Le premier argument se refere au nombre de thread
Le second au nombre de colonnes
Le troisième au nombre de ligne
Exemple : ./HPLC_TP1_matrix 1 30000 40000
g++ -std=c++11 -fopenmp HPLC_TP1_exo2_for_exe.cpp -o HPLC_TP1_exo2_for_exe

*/

int main(int argc, char** argv) {

	srand((int) time(0));

	char file_name[SIZE];
	cout << "Entrer le nom du fichier de sortie : ";
	cin>> file_name;
	int force_forte_faible = atoi(argv[1]); // force forte = 0 ; force faible =1
	int nb_runs = atoi(argv[2]); // nombre de repetitions
	
	
	ofstream myfile;
  	myfile.open ( file_name, fstream::app);
	myfile <<  "nb_thread \t nb_rows\t nb_cols \ttemps_comptage";	
	myfile.close();

	if (force_forte_faible ==0){
	
	int V_nb_thread[] = {1,2,4};
	int V_nb_rows[] = {1000, 2000, 3000, 5000, 7000};
	int V_nb_cols[] = {1000, 2000, 3000,5000, 7000};  


	for (int z=0; z<nb_runs ; z++){ // nb runs
	for (int i=0 ; i<3 ; i++){
	for (int j=0 ; j<4 ; j++){

		int nb_row =V_nb_rows[j] ;
		int nb_col =V_nb_cols[j] ;
		int nb_thread = V_nb_thread[i];
		omp_set_num_threads(nb_thread); 
		main_func( nb_thread, nb_row, nb_col, file_name);
	
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
			main_func( nb_thread, nb_row, nb_col, file_name);
		} // end it map
	  } // end z
	 //  myfile.close();
   } // end else
	
	myfile.close();

	myfile.close();
	return 0;
}




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
	# pragma omp parallel for

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



void main_func(const int nb_thread, const int  nb_row, const int  nb_col, const char* file_name )
{
	ofstream myfile;
	myfile.open ( file_name, fstream::app);

	// CODE LOUISE
	char** tab_l1 = generate_letter_matrix(nb_row, nb_col);
	letter_fill(tab_l1 ,  nb_row,  nb_col);
	//letter_display(tab_l1 ,  nb_row,  nb_col);
	map <char,int> alpha_test ;
	alpha_map(alpha_test );

	int before1 = (clock() *1000 / CLOCKS_PER_SEC);
	nb_letters(tab_l1, nb_row, nb_col , alpha_test);
	int after1=  (clock() *1000 / CLOCKS_PER_SEC);
	int diff1 = after1 - before1;

	myfile <<  nb_thread <<"\t"<< nb_row << "\t" << nb_col <<"\t"  << diff1 <<   "\n";
  	myfile.close();

	delete_letter_matrix(tab_l1 , nb_row, nb_col);
}



