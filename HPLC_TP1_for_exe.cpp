#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include "HPLC_TP1_for_exe.h"
#include <ctime> // Pour initialier la graine de rand
#include <time.h>
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <fstream> //


using namespace std; 
#define SIZE 200 // Max size of file_name

//#include <omp.h>

int main(int argc, char** argv) {
	srand((int) time(0));

	char file_name[SIZE];
	cout << "Entrer le nom du fichier de sortie : ";
	cin>> file_name
	int force_forte_faible = atoi(argv[1]); // force forte = 0 ; force faible =1
	int nb_runs = atoi(argv[2]); // nombre de repetitions
	string file_name =  "test_main_func.txt"; // Nom du fichier de sortie

	ofstream myfile;
  	myfile.open ( file_name, fstream::app);
	myfile <<  "nb_thread \t Taille_tab\tdiff1 somme deux vect\tdiff2 somme vect\tdiff3 multi vect\n";	
	myfile.close();

	if (force_forte_faible ==0){
	
	int V_nb_thread[] = {1,2,4};
	int V_Taille_tab[] = {1000000,5000000,10000000, 20000000, 30000000}; 

	int i;
	int j;

	for (int z=0; z<nb_runs ; z++){ // nb runs
	for (i=0 ; i<3 ; i++){
	for (j=0 ; j<4 ; j++){

		int Taille_tab =V_Taille_tab[j] ;
		int nb_thread = V_nb_thread[i];
		//omp_set_num_threads(nb_thread); 
		main_func(nb_thread,  Taille_tab );
	
		} // end de i
	  } // end de j
   }// end de z
	
} // End if


	else {
		
		map <int,int> cond_force_faible;

		cond_force_faible [1]=10000000;
  		cond_force_faible [2]=20000000;
  		cond_force_faible [3]=30000000;
 		cond_force_faible [4]=40000000;


		for (int z=0; z<nb_runs ; z++){ // nb runs
		for (map<int,int>::iterator it=cond_force_faible.begin() ; it!=cond_force_faible.end(); ++it ){
			int nb_thread = it->first;			
			int Taille_tab = it->second ;
			//omp_set_num_threads(nb_thread); 
			main_func(nb_thread,  Taille_tab);
		} // end it map
	  } // end z
	 //  myfile.close();
   } // end else
	
	return 0;
}

void fill(double* Tab , int Taille_tab, int min, int max )
{
	
	# pragma omp parallel for
  	//{
	for (int i =0 ; i< Taille_tab +1 ; i++  ) 
		{
		Tab[i] = Random(min, max);
		}
  	//}
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


void main_func(const int nb_thread, const int  Taille_tab){
	ofstream myfile;
	myfile.open ( "test_main_func.txt", fstream::app);

	double* Tab1;
	double* Tab2;
	double* Tab_sum;


	double min = 0; 
	double max = 10; //RAND_MAX;


	Tab1 = new double[Taille_tab];
	Tab2 = new double[Taille_tab]; 
	Tab_sum = new double[Taille_tab] ;

	fill (Tab1, Taille_tab, min , max);
	fill (Tab2, Taille_tab, min , max);

	int before1 = (clock() *1000 / CLOCKS_PER_SEC);
	sum_two_vector(Tab_sum , Tab1 , Tab2 ,Taille_tab  , Taille_tab );
	int after1=  (clock() *1000 / CLOCKS_PER_SEC);
	int diff1 = after1 - before1;


	
	int before2 = (clock() *1000 / CLOCKS_PER_SEC);
	double s  = sum_vector(Tab1 , Taille_tab);
	int after2=  (clock() *1000 / CLOCKS_PER_SEC);
	int diff2 = after2 - before2;
	
	int before3 = (clock() *1000 / CLOCKS_PER_SEC);
	multi_vector(Tab_sum , 2 ,  Taille_tab );
	int after3=  (clock() *1000 / CLOCKS_PER_SEC);
	int diff3 = after3 - before3;
	myfile <<  nb_thread <<"\t"<< Taille_tab <<"\t"  << diff1 <<"\t" << diff2 <<"\t" << diff3 <<   "\n";
  	myfile.close();
  
	
	delete [] Tab1;
	delete [] Tab2;
	delete [] Tab_sum;


}

