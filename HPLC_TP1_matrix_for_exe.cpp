/*--------------------- RESUME ---------------------------------------------------------
Ce programme rassemble les fonctions et les procédures de l'exercice 1 sur les matrices
de nombre.

La mise en parréllélisation de ces dernières a également été implémentée. Ce programme a 
été réalisé pour évaluer la performance de la parallélisation par passage à l'échelle 
forte et faible, pour les matrices de NOMBRES.  

Aisi cette entête est quasi équivalente à celle de HPLC_TP1_matrix.h, mais introduit 
la procédure  main.func contanant les principales directives pour l'évaluation de la performance. 

Dans ce fichier les fonctions et procédures sont triées par ordre alphabétique et succinte-
ment présentées.
---------------------------------------------------------------------------------------*/

/*---------------------IMPORATION DES LIBRAIRIES --------------------------------------*/
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

/* ################### PARALLELISATION ################# */
#include <omp.h>
/* ##################################################### */


using namespace std;
#define SIZE 256// Max size of file_name


/*---------------------CONSIGNES DE COMPLATION --------------------------------------------
Pour compiler ce fichier merci d'indiquer l'option -fopenmp
Exemple : g++ -fopenmp HPLC_TP1_matrix_for_exe.cpp -o HPLC_TP1_for_matrix_for_exe
--------------------------------------------------------------------------------------*/

/*---------------------CONSIGNES D'EXECUTION ----- --------------------------------------
Pour l'éxution du programme merci d'indiquer en premier argument le type de force, avec 0
pour la force forte et 1 pour la force faible. Le nombre de runs doit également être spécifié
Exemple : ./HPLC_TP1_matrix_for_exe 0 10
--------------------------------------------------------------------------------------*/

/*---------------------PRROGRAMME PRINCIPAL-------------------------------------------*/
int main(int argc, char** argv) {
	srand((int) time(0));// Générateur de nombre alétoire

	/*-------------- OPTIONS D'ÉXECUTION ----------------------------------------------*/
	// Initialisation du fichier des résultats
	char file_name[SIZE];
	cout << "Entrer le nom du fichier de sortie : ";
	cin>> file_name;
	ofstream myfile;
  	myfile.open ( file_name, fstream::app);
	myfile <<  "nb_thread \t nb_rows\t nb_cols \tdiff1 somme deux vect\tdiff2 somme vect\tdiff3 multi vect\n";	
	myfile.close();

	// Type de passage à l'échelle et nombre de runs
	int force_forte_faible = atoi(argv[1]); // force forte = 0 ; force faible =1
	int nb_runs = atoi(argv[2]); // nombre de repetitions
	
	/*-------------- PROGRAMME POUR LE PASSAGE A L'ÉCHELLE FORTE --------------------------*/
	if (force_forte_faible ==0)
	{
		int V_nb_thread[] = {1,2,4};
		int V_nb_rows[] = {1000,2000,3000, 4000, 5000}; // Vecteur définissant le nombre de core qui seront successivement utilisés
		int V_nb_cols[] = {1000,2000,3000, 4000, 5000};// Vecteur définissant la taille des vecteurs successivement générés

		for (int z=0; z<nb_runs ; z++)//  Pour le nombre de runs défini par l'utilisateur  
		{ 
			for (int i=0 ; i<3 ; i++)// Pour chaque nombre de coeurs défini dans V_nb_thread
			{ 
				for (int j=0 ; j<4 ; j++)// Pour chaque taille de matrice de core défini dans V_nb_rows et V_nb_cols		
				{ 

				int nb_row =V_nb_rows[j] ; // Nombre de lignes courantes
				int nb_col =V_nb_cols[j] ; // Nombre de colonnes courantes 
				int nb_thread = V_nb_thread[i]; // Nombre de coeurs courant
			
				/* ################### PARALLELISATION ################# */
				omp_set_num_threads(nb_thread); 
				/* ##################################################### */
		
				double A = 2; // Definition du double multiplicatif
				main_func( nb_thread, nb_row, nb_col, file_name, A);  // Appel à la procedure principale écrivant une ligne de résultats à chaque itération
		
				} // end de i
		  	} // end de j
	   	}// end de z	
	} // End if

	/*-------------- PROGRAMME POUR LE PASSAGE A L'ÉCHELLE FAIBLE --------------------------*/
	else 
	{
		
		map <int, vector<int>  > cond_force_faible; // Instanciation d'un dectionnaire associant le nombre de threads et la taille des matices

		// Définition des différentes conditions d'éxécution (Clé : Nombre de thread - Valeur : vecteurs <nb_rows,nb_cols)
		cond_force_faible [1]=vector<int>(1000,1000);
  		cond_force_faible [2]=vector<int>(2000,2000);
  		cond_force_faible [3]=vector<int>(3000,3000);
 		cond_force_faible [4]=vector<int>(4000,4000);


		for (int z=0; z<nb_runs ; z++) //  Pour le nombre de runs défini par l'utilisateur 
		{ 
			for (map<int, vector<int> >::iterator it=cond_force_faible.begin() ; it!=cond_force_faible.end(); ++it ) // Pour chaque condition d'éxécution définie dans map <int,int> cond_force_faible, 
			{
				int nb_thread = it->first;	// Nombre de coeurs courant
				
				// Taille des matrices
				vector<int>  values = it->second; 
				int nb_row = values[0] ; // Nombre de lignes courantes
				int nb_col = values[1]; // Nombre de colonnes courantes 

				/* ################### PARALLELISATION ################# */
				omp_set_num_threads(nb_thread); 
				/* ##################################################### */

				double A = 2;  // Definition du double multiplicatif
				main_func( nb_thread, nb_row, nb_col, file_name, A); // Appel à la procedure principale écrivant une ligne de résultats à chaque itération

			} // end it map
	  	} // end z
	
   	} // end else
	
	myfile.close();
	return 0;
}

/*--------------------- Procédure : delete_matrix ----------------------------------------
	Cette procédure permet de libérer la mémoire allouée pour construire une matrice de 
	taille nb_row x nb_col.
------------------------------------------------------------------------------------------*/
void delete_matrix( double ** Tab,int nb_row, int nb_col)
{
	for (int i = 0; i < nb_row; ++i)
	{
    	delete [] Tab[i];
    }
		delete [] Tab;		
}

/*--------------------- Procédure : display-------------------------------------------------
	Cette procédure permet d'afficher le contenu d'une matrice.
------------------------------------------------------------------------------------------*/
void display(double** Tab, int nb_row, int nb_col )
{
  for (int i = 0; i < nb_row; i++) // Pour chaque ligne
  {
  	printf("["); 
  	for(int j = 0; j < nb_col; j++) // Pour chaque colonne
  	{
    	printf("%f", Tab[i][j]);
    	// Séparation des éléments par une virgule (exception pour le denier élément)
    	if (j < nb_row-1) 
    	{
      		printf(", ");
    	}
  	}
    printf("]\n");
   } 
   printf("\n");
}

/*--------------------- Procédure : fill -------------------------------------------------
	Cette procédure permet de remplir une matrice de taille nb_rox x nb_col par des doubles 
	aléatoires compris entre min et max.
	Cette fonction est parallélisée.
------------------------------------------------------------------------------------------*/
void fill(double** Tab , int nb_row, int nb_col, int min, int max )
{
	/* ################### PARALLELISATION ################# */	
	# pragma omp parallel for
	/* ##################################################### */
	for (int i =0 ; i< nb_row ; i++)
	{
		for (int j =0 ; j< nb_col ; j++)
		{
			Tab[i][j] = Random(min, max); // Appel à Random pour le tirage d'un double aléatoire 
		}
	}
}



/*--------------------- Fonction : generate_matrix ------------------------------------------
	Cette fonction permet d'allouer l'espace mémoire nécessaire pour une matrice de taille
	nb_rox x nb_col.
--------------------------------------------------------------------------------------------*/
double** generate_matrix( int nb_row, int nb_col)
{
	double** Tab = new double*[nb_row]; 
	for (int i = 0; i < nb_row; ++i)
	{
		Tab[i] = new double[nb_col];
	}
	return Tab;
}

/*--------------------- Procédure : main_func ------------------------------------------------
	Cette procédure organise l'éxécution de l'ensemble des fonctions et procédures du programme
	associé au matrices de nombres. Les résultats de l'éxécution seront stockés dans un fichier,
	dont le nom est spécifié par l'utilisateur (file_name). Ces derniers seront organisés en cinq
	colonnes telles que:

	Nombre de tread | Nb lignes |Nb cols | Durée : somme de deux vecteurs | Durée : Somme des 
	éléments d'un vecteur | Durée : Multiplication d'un vecteur par une constante

	La procédure réalise les étapes suivantes :
		- 1) Création de trois vecteurs  de double et allocation mémoire, 
		- 2) Remplissage de deux vecteur (cf: procédure fill et random),
		- 3) Calcul de la somme de deux vecteurs (cf : sum_two_vector ), et mémorisation de la durée,
		- 4) Calcul de la somme des éléments d'un vecteur (cf : sum_vector ), et mémorisation de la durée,
		- 5) Multiplication d'un vecteur par un double (cf : multi_vector) et mémorisation de la durée.
------------------------------------------------------------------------------------------*/
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


/*--------------------- Procédure : multi_mat ------------------------------------------------
	Cette procédure permet de multiplier les éléments d'une matrice par un double (a).
	Cette fonction est parallélisée.
--------------------------------------------------------------------------------------------*/
void multi_mat(double ** m , const double  a ,  const int nb_row , const int nb_col    )
{	
	/* ################### PARALLELISATION ################# */	
	# pragma omp parallel for
	/* ##################################################### */

	for (int i = 0; i < nb_row; i++)
  	{
  		for (int j = 0; j < nb_col; j++)
  		{
   			m[i][j] = a*  m[i][j];
  		}
  	} 	  	
}


/*--------------------- Fonction : Random  ---------------------------------------------------
	Cette fonction permet de générer un nombre alétoire compris entre min et max.
	Elle est utilisée par la procédure fill.
--------------------------------------------------------------------------------------------*/
double Random (double min , double max) 
{	
	double f = (double)rand () / RAND_MAX;
	return min + f * (max-min+1); 
} 

/*--------------------- Fonction : sum_mat --------------------------------------------------
	Cette fonction permet de sommer les éléments d'une matrice.
	La parallélisation de cette opération de sommation est assurée par réduction. Ainsi chaque thread
	calcule un résultat partiel, puis le résultat final est calculé par sommation des résultats 
	intermédiaires. 
--------------------------------------------------------------------------------------------*/
double sum_mat( double** m, const int nb_row , const int nb_col)
{
  	int s = 0;
 	/* ################### PARALLELISATION ################# */
  	# pragma omp parallel for reduction (+:s)
  	/* ##################################################### */
	for (int i = 0; i < nb_row; i++)
  	{
  		for (int j = 0; j < nb_col; j++)
  		{
   			s = s + m[i][j];
  		}
  	}
  return s;
}

/*--------------------- Procédure : sum_two-mat -----------------------------------------------
	Cette fonction permet de sommer les éléments de matrice (m1 et m2).
	Cette fonction est parallélisée.
------------------------------------------------------------------------------------------------*/
void sum_two_mat(double ** m3 ,  double ** m1 ,  double ** m2 , const int nb_row_m1 , const int nb_col_m1 , const int nb_row_m2 , const int nb_col_m2)
{	
	if (nb_col_m1!=nb_col_m2 and nb_row_m1!=nb_row_m2 )
	{
		printf("Les matrices n'ont pas la même taille. \n " );
	}
	else
	{
    	/* ################### PARALLELISATION ################# */	
		# pragma omp parallel for
		/* ##################################################### */
 		for (int i =0 ; i< nb_col_m1  ; i++  ) 
 		{
 			for(int j = 0; j < nb_col_m1; j++)
 			{
 				m3[i][j] = m1[i][j] + m2[i][j];
 			}
 		}
   	}
}

