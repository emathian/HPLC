/*--------------------- RESUME ---------------------------------------------------------
Ce programme rassemble les fonctions et les procédures de l'exercice 1 sur les matrices
et celles de l'exercices 2 sur les matrices de lettres.

La mise en parréllélisation de ces dernières a également été partiellement implémentée. 
Ce programme a été réalisé pour faciliter l'implémentation et les tests des fonctions et 
des procédures. 
---------------------------------------------------------------------------------------*/

/*---------------------IMPORATION DES LIBRAIRIES --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include "HPLC_TP1_matrix.h"
#include <ctime> 
#include <time.h>
#include <iostream>
#include <fstream>
#include <map>

using namespace std;

/* ################### PARALLELISATION ################# */
#include <omp.h>
/* ##################################################### */

/*---------------------CONSIGNES DE COMPLATION --------------------------------------------
Pour compiler ce fichier merci d'indiquer l'option -fopenmp
Exemple : g++ -fopenmp HPLC_TP1_matrix.cpp -o HPLC_TP1_matrix
--------------------------------------------------------------------------------------*/

/*---------------------CONSIGNES D'EXECUTION ----- --------------------------------------
Pour l'éxution du programme merci d'indiquer en premier argument le nombre de lignes, en
second le nombre de colonnes et en troisième argument le nombre de coeurs.
Exemple : ./HPLC_TP1_matrix 20 20 2000000
--------------------------------------------------------------------------------------*/

/*---------------------PRROGRAMME PRINCIPAL-------------------------------------------*/
int main(int argc, char** argv) {

	srand((int) time(0));// Générateur de nombre alétoire

	/*-------------- PARALLELISATION ET OPTIONS D'ÉXÉCUTION --------------------------*/
	int nb_thread = atoi(argv[3]);  // Définition du nombre de coeurs
	omp_set_num_threads(nb_thread); 
	int nb_row = atoi(argv[1]); // Nombre de lignes
	int nb_col = atoi(argv[2]); // Nombre de colonnes
	/*--------------------------------------------------------------------------------*/

	/*------------------- TESTS DES FONTIONS ET PROCEDURE SUR LES MATRICES------------*/

	//  INTIALISATION DES MATRICES : 

	// Génération des matrices et allocation mémoire
	double** Tab1 = generate_matrix(nb_row,nb_col);
	double** Tab2 = generate_matrix(nb_row,nb_col);
	double** Tab_sum = generate_matrix(nb_row,nb_col);

	// Bornes de générteur de nombres aléatoires
	double min = 0; 
	double max = 10; //RAND_MAX;

	// Remplissage des matirces
	fill (Tab1, nb_row, nb_col, min , max);
	fill (Tab2, nb_row, nb_col, min , max);

	// Affichage des matrices
	printf("Affichage de la matrice  1   :   \n" );
	display(Tab1, nb_row, nb_col);
	printf("Affichage de la matrice  2   :   \n" );
	display(Tab2, nb_row, nb_col);
	

	// Somme de deux matrices
	sum_two_mat(Tab_sum, Tab1 , Tab2 , nb_row ,  nb_col , nb_row , nb_col);
	printf("Affichage de la matrice  résultantes de la somme des matrices 1 et 2  :   \n" );
	display(Tab_sum, nb_row, nb_col);

	// Somme des éléments d'une matrice
	double s= sum_mat( Tab1, nb_row ,  nb_col);
	printf(" Affichage de la somme des éléments de la matrice 1  :  %f\n", s);

	// Multiplication des éléments d'une matrice par un double (A)
	double A = 3;
	multi_mat( Tab1 , A ,  nb_row ,  nb_col );
	printf(" Affichage des éléments de la matrice 1 après multiplication des éléments par  %f\n :", A );
	display(Tab1, nb_row, nb_col);
	
	// LIBERATION DE L'ESPACE MEMOIRE :
	delete_matrix(Tab1 , nb_row, nb_col);
	delete_matrix(Tab2 , nb_row, nb_col);
	delete_matrix(Tab_sum , nb_row, nb_col);
	/*--------------------------------------------------------------------------------*/

	/*--- TESTS DES FONTIONS ET PROCEDURE SUR LES MATRICES DE LETTRE -----------------*/

	// Generation de la matrice
	char** tab_l1 = generate_letter_matrix(nb_row, nb_col);

	// Remplissage de la matrice
	letter_fill(tab_l1 ,  nb_row,  nb_col);

	// Affichage de la matrice
	printf(" Affichage de la matrice de lettre :  %f\n", s);
	letter_display(tab_l1 ,  nb_row,  nb_col);

	// DICTIONNAIRES DE COMPTAGE

	// Initialisation du dictionnaire
	map <char,int> alpha_test ; 
	alpha_map(alpha_test ); 

	// Denombrement
	nb_letters(tab_l1, nb_row, nb_col , alpha_test);

	// Affichage des résultats
	printf(" Affichage des résultats du dénombrement :  %f\n", s);
	display_map(alpha_test);

	// Liberation de l'espace mémoire
	delete_letter_matrix(tab_l1 , nb_row, nb_col);
	/*--------------------------------------------------------------------------------*/

	return 0;
}

/*--------- FONCTIONS ET PROCEDURES SUR LES MATRICES DE NOMBRES  -----------------------*/

/*--------------------- Procédure : delete_matrix ----------------------------------------
	Cette procédure permet de libérer la mémoire allouée pour construire une matrice de 
	taille nb_row x nb_col.
------------------------------------------------------------------------------------------*/
void delete_matrix( double ** Tab, const int nb_row, const int nb_col)
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
void display(double** Tab, const int nb_row, const int nb_col )
{
  for (int i = 0; i < nb_row; i++)
  {
  	printf("["); 
  	for(int j = 0; j < nb_col; j++)
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
  printf("\n");
}

/*--------------------- Procédure : fill -------------------------------------------------
	Cette procédure permet de remplir une matrice de taille nb_rox x nb_col par des doubles 
	aléatoires compris entre min et max.
	Cette fonction est parallélisée.
------------------------------------------------------------------------------------------*/
void fill(double** Tab , const int nb_row, const int nb_col, const int min, const int max )
{
	/* ################### PARALLELISATION ################# */
	# pragma omp parallel for
	/* ##################################################### */

	for (int i =0 ; i< nb_row ; i++)
	{
		for (int j =0 ; j< nb_col ; j++)
		{
			Tab[i][j] = Random(min, max); // Appel du générateur de nombre aléatoire
		}
	}
}


/*--------------------- Fonction : generate_matrix ------------------------------------------
	Cette fonction permet d'allouer l'espace mémoire nécessaire pour une matrice de taille
	nb_rox x nb_col.
--------------------------------------------------------------------------------------------*/
double** generate_matrix( const int nb_row, const int nb_col)
{
	// Rappel une matrice est un pointeur de pointeur
	double** Tab = new double*[nb_row]; 
	for (int i = 0; i < nb_row; ++i)
	{
		Tab[i] = new double[nb_col];	
	}
	return Tab;
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
   			m[i][j] = a*  m[i][j]; // Multiplication des éléments de la matrice m par a
  		}
  	} 		  	
}


/*--------------------- Fonction : Random  ---------------------------------------------------
	Cette fonction permet de générer un nombre alétoire compris entre min et max.
	Elle est utilisée par la procédure fill.
--------------------------------------------------------------------------------------------*/
double Random (const double min , const  double max) 
{	
	double f = (double)rand ()/ RAND_MAX;
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
 				m3[i][j] = m1[i][j] + m2[i][j]; // Addition des éléments des matrices 1 et 2 pour compléter la matrice 3
 			}
 		}
   	}
}


/*--------- FONCTIONS ET PROCEDURES SUR LES MATRICES DE LETTRES  ------------------------------*/

/*--------------------- Procédure : multi_mat ---------------------------------------------------
	Cette procédure permet d'initiliser le dictionnaire des résultats. Le compteur de chaque 
	lettre est mis à zéro.
--------------------------------------------------------------------------------------------*/
void  alpha_map(std::map<char,int> &Alpha)
{
	for (int i =65; i<91; i++)
	{
		Alpha[char(i)]=0;	
	}
}


/*--------------------- Procédure : delete_letter_matrix -----------------------------------
	Cette procédure permet de libérer la mémoire allouée pour construire une matrice de char 
	de taille nb_row x nb_col.
	Cette procédure est parallélisée.
------------------------------------------------------------------------------------------*/
void delete_letter_matrix( char ** Tab, const int nb_row, const int nb_col)
{
	/* ################### PARALLELISATION ################# */
  	# pragma omp parallel for 
  	/* ##################################################### */
	for (int i = 0; i < nb_row; ++i)
	{
    	delete [] Tab[i];
    }
	delete [] Tab;		
}


/*--------------------- Procédure : display_map-----------------------------------------------
	Cette procédure permet d'afficher le dictionnaires contennant le résultats du dénombrement.
------------------------------------------------------------------------------------------*/
void display_map (std::map<char,int> &Alpha)
{
	for (map<char, int >::iterator it=Alpha.begin() ; it!=Alpha.end(); ++it )
	{
		cout << it->first << '\t' << it->second  << endl; // Affichage des résultats
	}	
}



/*--------------------- Fonction : generate_letter_matrix ----------------------------------
	Cette fonction permet d'allouer l'espace mémoire nécessaire pour une matrice de char de 
	taille nb_rox x nb_col.
	Cette fonction est parallélisée.
--------------------------------------------------------------------------------------------*/
char** generate_letter_matrix(const int nb_row, const int nb_col)
{
	/* ################### PARALLELISATION ################# */
  	# pragma omp parallel for 
  	/* ##################################################### */
	char** Tab = new char*[nb_row];
	for (int i = 0; i < nb_row; ++i)
	{
		Tab[i] = new char[nb_col];
	}
	return Tab;
}


/*--------------------- Procédure : letter_fill ---------------------------------------------
	Cette procédure permet de remplir une matrice de taille nb_row x nb_col par des lettres 
	capitales générées aléatoirement.
	Cette procédure est parallélisée.
--------------------------------------------------------------------------------------------*/
void letter_fill(char** Tab , int nb_row, int nb_col)
{
	/* ################### PARALLELISATION ################# */
  	# pragma omp parallel for 
  	/* ##################################################### */
	for (int i =0 ; i< nb_row ; i++)
	{
		for (int j =0 ; j< nb_col ; j++)
		{
			Tab[i][j] = rand() % ('Z' - 'A' + 1) + 'A';
		}
	}
}


/*--------------------- Procédure : letter_display ---------------------------------------------
	Cette procédure permet d'afficher les éléments d'une matrice de char.
-----------------------------------------------------------------------------------------------*/
void letter_display(char** Tab, int nb_row, int nb_col )
{
  for (int i = 0; i < nb_row; i++)
  {
  	printf("[");
  	for(int j = 0; j < nb_col; j++)
  	{
    	printf("%c", Tab[i][j]);
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


/*--------------------- Procédure : nb_letters --------------------------------------------------
	Cette procédure permet de dénombrer les lettres contenues dans une matrice de char.
	PARALLELISATION À REALISER
-----------------------------------------------------------------------------------------------*/
void nb_letters(char**Tab, int nb_row, int nb_col, std::map<char,int> &Alpha)
{
	for (int i =0 ; i< nb_row ; i++) //permet de parcourir les lignes de la matrices de lettres
	{
		for (int j =0 ; j< nb_col ; j++) //permet de parcourir les colonnes de la matrices de lettres
		{
			Alpha[Tab[i][j]] +=1; // Incrémentation du dictionnaire des résultats		
		}
	}
}




