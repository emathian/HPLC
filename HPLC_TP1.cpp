/*--------------------- RESUME ---------------------------------------------------------
Ce programme rassemble les fonctions et les procédures de l'exercice 1 sur les vecteurs.
La mise en parréllélisation de ces dernières a également été implémentée. Ce programme a 
été réalisé pour faciliter l'implémentation et les tests des fonctions et des procédures. 
---------------------------------------------------------------------------------------*/

/*---------------------IMPORATION DES LIBRAIRIES --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include "HPLC_TP1.h"
#include <ctime> // Pour initialier la graine de rand
# include <time.h>
#include <iostream>
#include <fstream>

using namespace std;

/* ################### PARALLELISATION ################# */
#include <omp.h>
/* ##################################################### */


/*---------------------CONSIGNES D'EXECUTION ----- --------------------------------------
Pour l'éxution du progrmma merci d'indiquer en premier argument le nombre de core utilisé,
et en second argument le nombre de runs 
Exemple : ./HPLC_TP1 2 2000000
--------------------------------------------------------------------------------------*/


/*---------------------PRROGRAMME PRINCIPAL-------------------------------------------*/
int main(int argc, char** argv) {

	srand((int) time(0)); // Générateur de nombre alétoire

	/*-------------- PARALLELISATION ET OPTIONS D'ÉXÉCUTION --------------------------*/
	int nb_thread = atoi(argv[2]);  // Définition du nombre de core
	omp_set_num_threads(nb_thread); 
	int Taille_tab = atoi(argv[1]); // Taille des vecteurs
	/*--------------------------------------------------------------------------------*/
	
	
	/*------------------- INTIALISATION DES VECTEURS ---------------------------------*/
	double* Tab1;
	double* Tab2;
	double* Tab_sum;

	// Borne de générteur de nombre aléatoire 
	double min = 0; 
	double max = 10; //RAND_MAX;

	// Allocation mémoire
	Tab1 = new double[Taille_tab];
	Tab2 = new double[Taille_tab]; 
	Tab_sum = new double[Taille_tab] ;
	/*--------------------------------------------------------------------------------*/


	/*------------------- TESTS DES FONTIONS ET PROCEDURE ----------------------------*/
	int before = (clock() *1000 / CLOCKS_PER_SEC); // Initialisation du chronomètre

	// Remplissage des vecteurs de taille = Taille_tab par des nombre aléatoires compris 
	// entre min et max :
	fill (Tab1, Taille_tab, min , max);
	fill (Tab2, Taille_tab, min , max);

	// Affichage des vecteurs :
	printf("Affichage vecteur 1   :   \n" );
	display(Tab1, Taille_tab);
	printf("Affichage vecteur 2   :   \n" );
	display(Tab2,  Taille_tab);

	// Somme de deux vecteurs :
	sum_two_vector(Tab_sum , Tab1 , Tab2 ,Taille_tab  , Taille_tab );
	printf("Affichage du vecteur résultant (3) de la somme du vecteur 1 et 2  :  \n" );
	display(Tab_sum,  Taille_tab);

	// Somme des éléments d'un vecteur :
	double s  = sum_vector(Tab1 , Taille_tab);
	printf("Somme des éléments du vecteur 1   :  %f \n" , s);
	
	// Multiplication du vecteur par un double
	multi_vector(Tab_sum , 2 ,  Taille_tab );
	printf("Affichage du vecteur 3 * 2   :  %f \n" , s);
	display(Tab_sum,  Taille_tab);

	int after=  (clock() *1000 / CLOCKS_PER_SEC); // Arrêt du chronomètre
	int diff = after - before; // Calcul de la durée d'éxécution
	printf("Durée d'éxécution :  %d \n", diff ); // Affichage de la durée d'éxécution

	// Mémorisation du temps d'éxécution en fonction du nombre de core et de la taille des
	// vecterus.
  	ofstream myfile;
  	myfile.open ("Resultats_Vecteurs_Tests.txt", fstream::app);
  	myfile <<  nb_thread <<"\t"<< Taille_tab <<"\t"  << diff <<"\t" <<  "\n";
  	myfile.close();
  
	// Désallocation de la mémoire :	
	delete [] Tab1;
	delete [] Tab2;
	delete [] Tab_sum;

	return 0;
}


/*--------------------- Procédure : display  ------------------------------------------------
	Cette procédure permet l'affichage d'un vecteur de taille définit.
--------------------------------------------------------------------------------------------*/
void display(const double* Tab, const int Taille_tab)
{
  printf("["); // Marque le début d'un vecteur	
  for (int i = 0; i < Taille_tab; i++) 
  {
    printf("%f", Tab[i]);
    // Séparation des éléments par une virgule (exception pour le denier élément)
    if (i < Taille_tab-1) 
    {
      printf(", ");
    }
  }
  printf("]\n"); // Marque la fin d'un vecteur.
}


/*--------------------- Procédure : fill --------------------------------------------------
	Cette procédure permet le remplissage d'un vecteur, de taille défini, par des doubles
	générés aléatoirement compris entre min et max. La parallélisation de cette opératon est
	assurée.
------------------------------------------------------------------------------------------*/
void fill(double* Tab , const int Taille_tab, const int min, const int max )
{
	/* ################### PARALLELISATION ################# */
	# pragma omp parallel for
	/* ##################################################### */
	
	for (int i =0 ; i< Taille_tab +1 ; i++ ) // Pour i chaque élément du vecteur : 
		{
		Tab[i] = Random(min, max); // Appel du générateur de nombre aléatoire
		}
}


/*--------------------- Fonction : Random  -------------------------------------------------
	Cette fonction retourne un double généré alétoirement entre les bornes définies par min
	er max. La fonction Random est appélé par la procédure fill.
------------------------------------------------------------------------------------------*/
double Random (const double min , const double max) 
{	
	double f = (double)rand () / RAND_MAX;
	return min + f * (max-min+1); 
} 


/*--------------------- Procédure : multi_vector (Multiplication du vecteur par un double) --
	Cette procédure permet de multiplier les éléments d'un vecteur par une constante (a).
	Cette opération est parallélisée.
--------------------------------------------------------------------------------------------*/
void multi_vector(double * v , const double  a ,  const int taille_v )

{	
	/* ################### PARALLELISATION ################# */
	# pragma omp parallel for
	/* ##################################################### */
 		for (int i =0 ; i< taille_v  ; i++  ) 
 		{
 			v[i] = v[i] * a;
 		}   	
}



/*--------------------- Procédure : sum_two_vector (Somme de deux vecteurs)  ----------------
	Cette procédure permet de sommer deux vecteurs et retourne les résultats dans un vecteur v3.
	Cette opération est parallélisée.
--------------------------------------------------------------------------------------------*/
void sum_two_vector(double * v3 , const double * v1 , const double * v2 , const int taille_v1 , const int taille_v2   )
{	
	// Condition sur la taille des vecteurs v1 et v2 
	if (taille_v1 != taille_v2 )
	{
		printf("Les vecteurs ont des longueurs diffférentes" );
	}

	else
	{
		
    	/* ################### PARALLELISATION ################# */
		# pragma omp parallel for
		/* ##################################################### */
	  
 		for (int i =0 ; i< taille_v1  ; i++  ) 
 		{
 			v3[i] = v1[i] + v2[i]; // Somme des éléments des vecteurs v1 et v2
 		}
   	}
}


/*--------------------- Fonction : sum_vector (Somme des éléments d'un vecteur)  ----------------
	Cette fonction permet de sommer les éléments d'un vecteur et retourne le résultat (double).
	La parallélisation de cette opération de sommation est assurée par réduction. Ainsi chaque thread
	calcule un résultat partiel, puis le résultat final est calculé par sommation des résultats 
	intermédiaires. 
--------------------------------------------------------------------------------------------*/
double sum_vector(const double Tab[], const int Taille_tab)
{
  int s = 0; // Initialisation de la somme

  /* ################### PARALLELISATION ################# */
  # pragma omp parallel for reduction (+:s)
  /* ##################################################### */
  for (int i = 0; i < Taille_tab; i++)
  {
    s = s + Tab[i];
  }

  return s; 
}

