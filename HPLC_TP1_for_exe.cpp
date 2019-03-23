/*--------------------- RESUME ---------------------------------------------------------
Ce programme rassemble les fonctions et les procédures de l'exercice 1 sur les vecteurs.
La mise en parréllélisation de ces dernières a également été implémentée. Ce programme a 
été réalisé pour évaluer la performance de la parallélisation par passage à l'échelle 
forte et faible.  

Ce programma est quasi équivalent à celle de HPLC_TP1.cpp, mais introduit le main
nécéssaire à l'évauation des passages à l'échelle.
---------------------------------------------------------------------------------------*/

/*---------------------IMPORATION DES LIBRAIRIES --------------------------------------*/
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
#define SIZE 256// Taille du buffer pour le nom du fichier des résultats.

/* ################### PARALLELISATION ################# */
#include <omp.h>
/* ##################################################### */


/*---------------------CONSIGNES DE COMPLATION --------------------------------------------
Pour compiler ce fichier merci d'indiquer l'option -fopenmp
Exemple : g++ -fopenmp HPLC_TP1_for_exe.cpp -o HPLC_TP1_for_exe
--------------------------------------------------------------------------------------*/

/*---------------------CONSIGNES D'EXECUTION ----- --------------------------------------
Pour l'éxution du programme merci d'indiquer en premier argument le type de force, avec 0
pour la force forte et 1 pour la force faible. Le nombre de runs doit également être spécifié
Exemple : ./HPLC_TP1_for_exe 0 10
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
	myfile <<  "nb_thread \t Taille_tab\tdiff1 somme deux vect\tdiff2 somme vect\tdiff3 multi vect\n";	
	myfile.close();


	// Type de passage à l'échelle et nombre de runs
	int force_forte_faible = atoi(argv[1]); // force forte = 0 ; force faible =1
	int nb_runs = atoi(argv[2]); // nombre de repetitions
	

	/*-------------- PROGRAMME POUR LE PASSAGE A L'ÉCHELLE FORTE --------------------------*/
	if (force_forte_faible ==0)
	{
		int V_nb_thread[] = {1,2,4}; // Vecteur définissant le nombre de core qui seront successivement utilisés
		int V_Taille_tab[] = {1000000,5000000,10000000, 20000000, 30000000}; // Vecteur définissant la taille des vecteurs successivement générés

		for (int z=0; z<nb_runs ; z++)// Pour le nombre de runs défini par l'utilisateur  
		{ 
			for (int i=0 ; i<3 ; i++)// Pour chaque nombre de coeurs défini dans V_nb_thread
			{ 
				for (int j=0 ; j<5 ; j++) // Pour chaque taille de vecteur de core défini dans V_Taille_tab		
				{
					int Taille_tab =V_Taille_tab[j] ; // Taille courante des vecteurs
					int nb_thread = V_nb_thread[i]; // Nombre de coeurs courant
					
					/* ################### PARALLELISATION ################# */
					omp_set_num_threads(nb_thread); 
					/* ##################################################### */
					
					main_func(nb_thread,  Taille_tab, file_name ); // Appel à la procedure principale écrivant une ligne de résultat à chaque itération
				} // end de j
	  		} // end de i
   		}// end de z
	} // End if


	/*-------------- PROGRAMME POUR LE PASSAGE A L'ÉCHELLE FAIBLE --------------------------*/
	else 
	{

		map <int,int> cond_force_faible; // Instanciation d'un dectionnaire associant le nombre de threads et la taille des vecteurs

		// Définition des différentes conditions d'éxécution (Clé : Nombre de thread - Valeur : Taille des vecteurs)
		cond_force_faible [1]=10000000;
  		cond_force_faible [2]=20000000;
  		cond_force_faible [3]=30000000;
 		cond_force_faible [4]=40000000;


		for (int z=0; z<nb_runs ; z++)// Pour le nombre de runs défini par l'utilisateur  
		{ 
			for (map<int,int>::iterator it=cond_force_faible.begin() ; it!=cond_force_faible.end(); ++it ) // Pour chaque condition d'éxécution définie dans map <int,int> cond_force_faible, 
			{
				int nb_thread = it->first;	// Nombre de threads courant		
				int Taille_tab = it->second ; // Taille courante des vecteurs
				/* ################### PARALLELISATION ################# */
				omp_set_num_threads(nb_thread); 
				/* ##################################################### */
				
				main_func(nb_thread,  Taille_tab, file_name); // Appel à la procedure principale écrivant une ligne de résultat à chaque itération
			} // end for 
	  	} // end z
	} // end else
	
	//myfile.close();
	return 0;
}


/*--------------------- Procédure : display  ------------------------------------------------
	Cette procédure permet l'affichage d'un vecteur de taille définit.
	Précondition : Le vecteur (Tab) doit être instancié, et la mémoire nécessaire allouée.
--------------------------------------------------------------------------------------------*/
void display(const double* Tab, const int Taille_tab)
{
  printf("[");// Marque le début d'un vecteur	
  for (int i = 0; i < Taille_tab; i++)
  {
    printf("%f", Tab[i]);
	// Séparation des éléments par une virgule (exception pour le denier élément)
    if (int i < Taille_tab-1) 
    {
      printf(", ");
    }
  }
  printf("]\n");// Marque la fin d'un vecteur.
}


/*--------------------- Procédure : fill --------------------------------------------------
	Cette procédure permet le remplissage d'un vecteur, de taille défini, par des doubles
	générés aléatoirement compris entre min et max. La parallélisation de cette opératon est
	assurée.
------------------------------------------------------------------------------------------*/
void fill(double* Tab , int Taille_tab, int min, int max )
{	
	/* ################### PARALLELISATION ################# */
	# pragma omp parallel for
	/* ##################################################### */

	for (int i =0 ; i< Taille_tab +1 ; i++  ) 
		{
		Tab[i] = Random(min, max);
		}
}

/*--------------------- Procédure : main_func ------------------------------------------------
	Cette procédure organise l'éxécution de l'ensemble des fonctions et procédures du programme.
	Les résultats de l'éxécution seront stockés dans un fichier, dont le nom est spécifié par 
	l'utilisateur (file_name). Ces derniers seront organisés en quatres colonnes telles que:

	Nombre de tread | Taille des vecteurs | Durée : somme de deux vecteurs | Durée : Somme des 
	éléments d'un vecteur | Durée : Multiplication d'un vecteur par une constante

	La procédure réalise les étapes suivantes :
		- 1) Création de trois vecteurs  de double et allocation mémoire, 
		- 2) Remplissage de deux vecteur (cf: procédure fill et random),
		- 3) Calcul de la somme de deux vecteurs (cf : sum_two_vector ), et mémorisation de la durée,
		- 4) Calcul de la somme des éléments d'un vecteur (cf : sum_vector ), et mémorisation de la durée,
		- 5) Multiplication d'un vecteur par un double (cf : multi_vector) et mémorisation de la durée.
-------------------------------------------------------------------------*/
void main_func(const int nb_thread, const int  Taille_tab, const char* file_name){
	
	// Ouverture du fichier des résultats 
	ofstream myfile;
	myfile.open ( file_name, fstream::app);

	// Instanciation des vecteurs
	double* Tab1;
	double* Tab2;
	double* Tab_sum;

	// Allocation mémoire
	Tab1 = new double[Taille_tab];
	Tab2 = new double[Taille_tab]; 
	Tab_sum = new double[Taille_tab] ;

	// Bornes de générteur de nombres aléatoires 
	double min = 0; 
	double max = 10; 

	// Remplissage des vecteurs de taille = Taille_tab par des nombre aléatoires compris 
	// entre min et max :
	fill (Tab1, Taille_tab, min , max);
	fill (Tab2, Taille_tab, min , max);

	// Tâche N°1  : Spmme de deux vecteurs
	int before1 = (clock() *1000 / CLOCKS_PER_SEC); // Initialisation du chronomètre
	sum_two_vector(Tab_sum , Tab1 , Tab2 ,Taille_tab  , Taille_tab ); // Somme de Tab1 et Tab2 pour le remplissage de Tab_sum
	int after1=  (clock() *1000 / CLOCKS_PER_SEC); // Arrêt du chronmètre
	int diff1 = after1 - before1; // Durée de la tâche N°1 

	// Tâche N°2  : Spmme des éléments d'un vecteur
	int before2 = (clock() *1000 / CLOCKS_PER_SEC);// Initialisation du chronomètre
	double s  = sum_vector(Tab1 , Taille_tab); // Calcul de la somme des éléments de Tab1
	int after2=  (clock() *1000 / CLOCKS_PER_SEC); // Arrêt du chronmètre
	int diff2 = after2 - before2;// Durée de la tâche N°2
	
	// Tâche N°3  : Multiplication des éléments d'un vecteur par une constante
	int before3 = (clock() *1000 / CLOCKS_PER_SEC);// Initialisation du chronomètre
	multi_vector(Tab_sum , 2 ,  Taille_tab ); // Multiplication des éléments du vecteur Tab_sum par 2
	int after3=  (clock() *1000 / CLOCKS_PER_SEC);// Arrêt du chronmètre
	int diff3 = after3 - before3;// Durée de la tâche N°3
	
	// Ecriture de la durée des différentes tâches en fonction du nombre de cores et de la taille des vecteurs
	myfile <<  nb_thread <<"\t"<< Taille_tab <<"\t"  << diff1 <<"\t" << diff2 <<"\t" << diff3 <<   "\n";
  	myfile.close();
  
	// Libération de la mémoire
	delete [] Tab1;
	delete [] Tab2;
	delete [] Tab_sum;

}


/*--------------------- Procédure : multi_vector (Multiplication du vecteur par un double) --
	Cette procédure permet de multiplier les éléments d'un vecteur par une constante (a).
	Cette opération est parallélisée.
--------------------------------------------------------------------------------------------*/
void multi_vector(double * v , const double  a ,  const int taille_v    )
{	

	/* ################### PARALLELISATION ################# */
	# pragma omp parallel for
	/* ##################################################### */
 		for (int i =0 ; i< taille_v  ; i++  ) 
 			{
 			
 			v[i] = v[i] * a;
 			}
}


/*--------------------- Fonction : Random  -------------------------------------------------
	Cette fonction retourne un double généré alétoirement entre les bornes définies par min
	et max. La fonction Random est appélé par la procédure fill.
------------------------------------------------------------------------------------------*/
double Random (double min , double max) 
{	
	double f = (double)rand () / RAND_MAX;
	return min + f * (max-min+1); 
} 


/*--------------------- Procédure : sum_two_vector (Somme de deux vecteurs)  ----------------
	Cette procédure permet de sommer deux vecteurs et retourne les résultats dans un vecteur v3.
	Cette opération est parallélisée.
--------------------------------------------------------------------------------------------*/
void sum_two_vector(double * v3 , const double * v1 , const double * v2 , const int taille_v1 , const int taille_v2   )

{	
	if (taille_v1 != taille_v2 )
	{
		printf("Les vecteurs ont des longueurs diffférentes. " );
	}

	else
	{
        /* ################### PARALLELISATION ################# */
		# pragma omp parallel for
		/* ##################################################### */
 		for (int i =0 ; i< taille_v1  ; i++  ) 
 		{
 			v3[i] = v1[i] + v2[i];
 		}
 	}
}

/*--------------------- Fonction : sum_vector (Somme des éléments d'un vecteur)  ----------------
	Cette fonction permet de sommer les éléments d'un vecteur et retourne le résultat (double).
	La parallélisation de cette opération de sommation est assurée par réduction. Ainsi chaque thread
	calcule un résultat partiel, puis le résultat final est calculé par sommation des résultats 
	intermédiaires. 
--------------------------------------------------------------------------------------------*/
double sum_vector(const double Tab[], int Taille_tab)
{
  int s = 0;
 
  /* ################### PARALLELISATION ################# */
  # pragma omp parallel for reduction (+:s)
  /* ##################################################### */
  for (int i = 0; i < Taille_tab; i++)
  {
    s = s + Tab[i];
  }
  return s;
}




