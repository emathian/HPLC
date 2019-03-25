/*--------------------- RESUME ---------------------------------------------------------
Ce programme rassemble les fonctions et les procédures de l'exercice 2 sur les matrices
de lettres.

La mise en parréllélisation de ces dernières a également été implémentée. Ce programme a 
été réalisé pour évaluer la performance de la parallélisation par passage à l'échelle 
forte et faible.  
---------------------------------------------------------------------------------------*/

/*---------------------IMPORATION DES LIBRAIRIES --------------------------------------*/
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include "HPLC_matrix_letters.h"
#include <ctime> // Pour initialier la graine de rand
# include <time.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>

/* ################### PARALLELISATION ################# */
#include <omp.h>
/* ##################################################### */

using namespace std;
#define SIZE 256// Max size of file_name

/*---------------------CONSIGNES DE COMPLATION ------------------------------------------
Pour compiler ce fichier merci d'indiquer l'option -fopenmp
Exemple : g++ -fopenmp HPLC_matrix_letters.cpp -o HPLC_matrix_letters
--------------------------------------------------------------------------------------*/

/*---------------------CONSIGNES D'EXECUTION ----- --------------------------------------
Pour l'éxution du programme merci d'indiquer en premier argument le type de force, avec 0
pour la force forte et 1 pour la force faible. Le nombre de runs doit également être spécifié
Exemple : ./HPLC_matrix_letters 0 10
--------------------------------------------------------------------------------------*/

/*---------------------PRROGRAMME PRINCIPAL-------------------------------------------*/
int main(int argc, char** argv) {
	srand((int) time(0)); // Générateur de nombre alétoire

	/*-------------- OPTIONS D'ÉXECUTION ----------------------------------------------*/
	// Initialisation du fichier des résultats
	char file_name[SIZE];
	cout << "Entrer le nom du fichier de sortie : ";
	cin>> file_name;
	ofstream myfile;
  	myfile.open ( file_name, fstream::app);
	myfile <<  "nb_thread \t nb_rows\t nb_cols \ttemps_comptage \ttemps_comptage_v2 \n";	
	myfile.close();

	// Type de passage à l'échelle et nombre de runs
	int force_forte_faible = atoi(argv[1]); // force forte = 0 ; force faible =1
	int nb_runs = atoi(argv[2]); // nombre de repetitions

	/*-------------- PROGRAMME POUR LE PASSAGE A L'ÉCHELLE FORTE --------------------------*/
	if (force_forte_faible ==0)
	{
		int V_nb_thread[] = {1,2,4}; // Vecteurs définissant le nombre de coeurs
		int V_nb_rows[] = {1000, 2000, 3000, 5000, 7000};// Vecteur définissant le nombre de lignes dans les matrices
		int V_nb_cols[] = {1000, 2000, 3000,5000, 7000}; // Vecteur définissant le nombre de colonnes dans les matrices
	

		for (int z=0; z<nb_runs ; z++) //  Pour le nombre de runs défini par l'utilisateur 
		{ 
			for (int i=0 ; i<3 ; i++) // Pour chaque nombre de coeurs défini dans V_nb_thread
			{
				for (int j=0 ; j<4 ; j++) // Pour chaque taille de matrice dans V_nb_rows et V_nb_cols	
				{

					int nb_row =V_nb_rows[j] ; // Nombre de lignes courantes
					int nb_col =V_nb_cols[j] ; // Nombre de colonnes courantes
					int nb_thread = V_nb_thread[i];  // Nombre de coeurs courant
					/* ################### PARALLELISATION ################# */
					omp_set_num_threads(nb_thread); 
					/* ##################################################### */
					main_func( nb_thread, nb_row, nb_col, file_name); // Appel à la procedure principale écrivant une ligne de résultats à chaque itération
	
				} // end de i
	  		} // end de j
  		 }// end de z
	} // End if

	/*-------------- PROGRAMME POUR LE PASSAGE A L'ÉCHELLE FAIBLE --------------------------*/
	else
	{
		map <int, vector<int>  > cond_force_faible; // Instanciation d'un dectionnaire associant le nombre de threads et la taille des matices

		cond_force_faible [1]=vector<int>(1000,1000);
  		cond_force_faible [2]=vector<int>(2000,2000);
  		cond_force_faible [3]=vector<int>(3000,3000);
 		cond_force_faible [4]=vector<int>(4000,4000);


		for (int z=0; z<nb_runs ; z++)//  Pour le nombre de runs défini par l'utilisateur 
		{ 
			for (map<int, vector<int> >::iterator it=cond_force_faible.begin() ; it!=cond_force_faible.end(); ++it ) // Pour chaque condition d'éxécution définie dans map <int,int> cond_force_faible, 
			{

			// Taille des matrices
			int nb_thread = it->first;	
			vector<int>  values = it->second;
			int nb_row = values[0] ; // Nombre de lignes courantes
			int nb_col = values[1]; // Nombre de colonnes courantes

			/* ################### PARALLELISATION ################# */
			omp_set_num_threads(nb_thread); 
			/* ##################################################### */
			main_func( nb_thread, nb_row, nb_col, file_name); // Appel à la procedure principale écrivant une ligne de résultats à chaque itération

			} // end it map
	  	} // end z
	} // end else
	return 0;
}


/*--------------------- Procédure : delete_letter_matrix -----------------------------------
	Cette procédure est utilisée par nb_letter_v2, elle permet d'ajouter deux dictionnaires
	contenant le nombre d'occurences de chaque de lettres.
------------------------------------------------------------------------------------------*/
void ajout_map(std::map<char,int> &Alpha, std::map<char,int> &Alpha_inter)
{
  for (int i =65; i<91; i++)
	{
		Alpha[char(i)]+=Alpha_inter[char(i)];
	}
}

/*--------------------- Procédure : delete_letter_matrix -----------------------------------
	Cette procédure permet de libérer la mémoire allouée pour construire une matrice de 
	taille nb_row x nb_col.
------------------------------------------------------------------------------------------*/
void delete_letter_matrix( char ** Tab,int nb_row, int nb_col)
{
	for (int i = 0; i < nb_row; ++i)
	{
    	delete [] Tab[i];
	   }
		delete [] Tab;		
}


/*--------------------- Procédure : display_map ----------------------------------------------
	Cette procédure permet d'afficher le contenu des résultats de nb_letters et nb_letters_v2.
------------------------------------------------------------------------------------------*/
void display_map (std::map<char,int> &Alpha)
{
	for (map<char, int >::iterator it=Alpha.begin() ; it!=Alpha.end(); ++it )
	{
		cout << it->first << '\t' << it->second  << endl;
	}
}


/*--------------------- Fonction : generate_letter_matrix ----------------------------------
	Cette fonction permet d'allouer l'espace mémoire nécessaire pour une matrice de char de 
	taille nb_rox x nb_col.
--------------------------------------------------------------------------------------------*/
char** generate_letter_matrix( int nb_row, int nb_col)
{
	char** Tab = new char*[nb_row];
	for (int i = 0; i < nb_row; ++i)
	{
		Tab[i] = new char[nb_col];
		
	}
	return Tab;
}


/*--------------------- Procédure : init_mat ---------------------------------------------------
	Cette procédure permet d'initiliser le dictionnaire des résultats. Le compteur de chaque 
	lettre est mis à zéro
	Exemple : A -> 0
--------------------------------------------------------------------------------------------*/
void init_map(std::map<char,int> &Alpha)
{
	for (int i =65; i<91; i++)
	{
		Alpha[char(i)]=0;
	}
}


/*--------------------- Procédure : letter_fill ---------------------------------------------
	Cette procédure permet de remplir une matrice de taille nb_row x nb_col par des lettres 
	capitales générées aléatoirement.
--------------------------------------------------------------------------------------------*/
void letter_fill(char** Tab , int nb_row, int nb_col)
{
	/* ################### PARALLELISATION ################# */
	//# pragma omp parallel for // Parallélisation possible
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
}



/*--------------------- Procédure : nb_letters --------------------------------------------------
	Cette procédure permet de calculer les occurences de chaque lettre contenue dans une matrice
	de char. Elle prend en argument un dictionnaire dont la clé est la lettre et la valeur est le 
	nombre d'occurences de chaque lettre à la fin du parcours de la matricce. Cette fonction est 
	parallélisé sur le problème complet (Q2.4).
-----------------------------------------------------------------------------------------------*/
void nb_letters(char**Tab, int nb_row, int nb_col, std::map<char,int> &Alpha)
{
	/* ################### PARALLELISATION ################# */
	# pragma omp parallel for
	/* ##################################################### */
	for (int i =0 ; i< nb_row ; i++)
	{
		for (int j =0 ; j< nb_col ; j++)
		{
			Alpha[Tab[i][j]] +=1;			
		}
	}
	
} 


/*--------------------- Procédure : nb_letters_v2 --------------------------------------------------
	Cette procédure permet de calculer les occurences de chaque lettre contenue dans une matrice de char.
	 Elle prend en argument un dictionnaire, chaque  clé représente une lettre, la valeur associé correspond au
	nombre d'occurences de celle-ci dans la matrice. Cette fonction est parallélisé sur le problème
	découpé (Q2.5 à Q2.7). Ainsi elle crée des dictionnaires intermédiaires permettant le dénombrement
	des lettres par ligne parcourue, les résultats de chaque ligne sont ensuite ajoutés au dictionnaire
	des résultats finaux via l'appel à  ajout_map.
-----------------------------------------------------------------------------------------------*/
void nb_letters_v2(char**Tab, int nb_row, int nb_col, std::map<char,int> &Alpha)
{
	/* ################### PARALLELISATION ################# */
	# pragma omp parallel for
	/* ##################################################### */

	for (int i =0 ; i< nb_row ; i++) // Pour chaque ligne
	{
		map<char, int> Alpha_inter; // Création d'un dictionnaires des occurences initialisé à zéro
		init_map(Alpha_inter);

	  /* ################### PARALLELISATION ################# */
	 	# pragma omp parallel for
	  /* ##################################################### */

		for (int j =0 ; j< nb_col ; j++) // Parcours de chaque case contenu dans une ligne
		{
			Alpha_inter[Tab[i][j]] +=1; // Ajuot des occurences dans le dictionnaire intermédiaire
		}
		ajout_map(Alpha, Alpha_inter); // A la fin du parcours d'une ligne ajout des résultats intermédiaires au dictionnaire final
	}
}


/*--------------------- Procédure : main_func ------------------------------------------------
	Cette procédure organise l'éxécution de l'ensemble des fonctions et procédures du programme
	associé aux matrices de lettres. Les résultats de l'éxécution seront stockés dans un fichier,
	dont le nom est spécifié par l'utilisateur (file_name). Ces derniers seront organisés en quatre
	colonnes tel que:

	Nombre de tread | Nb lignes |Nb cols | Durée : parallélisation V1 | Durée : parallélisation V2 
	 
	La procédure réalise les étapes suivantes :
		- 1) Création d'une  de la matrice de lettres 
		- 2) Remplissage de la matrice de lettres (cf: procédure fill_letter),
		- 3) Initialisation du dictionnaire des résultats
		- 4) Calcul du nombre d'occurence de chaque lettres grâce à la première version de parallélisation, 
			(nb_letters) et mémorisation de la durée,
		- 5) Initialisation d'un second dictinnaire global de résultats pour les résultats de la seconde
			 version de parallélisation
		- 6) Calcul des fréquences de chaque lettre grâce à la deuxième version de parallélisation, 
			(nb_letters_v2) et mémorisation de la durée,
		- 7) Ecriture d'une ligne de résultats
------------------------------------------------------------------------------------------*/
void main_func(const int nb_thread, const int  nb_row, const int  nb_col, const char* file_name )
{
	// Ouverture du fichier des résultats 
	ofstream myfile;
	myfile.open ( file_name, fstream::app);

	// Construction de la matrice de lettres
	char** tab_l1 = generate_letter_matrix(nb_row, nb_col);
	letter_fill(tab_l1 ,  nb_row,  nb_col);
	
	// Calcul de la performance sur le problème complet
	map <char,int> alpha_res1;
	init_map(alpha_res1 ); // Initialisation du dictionnaire
	int before1 = (clock() *1000 / CLOCKS_PER_SEC);
	nb_letters(tab_l1, nb_row, nb_col , alpha_res1);
	int after1=  (clock() *1000 / CLOCKS_PER_SEC);
	int diff1 = after1 - before1;
	
	// Calcul de la performance sur le problème découpé en sous problème
 	map <char,int> alpha_glob ;
	init_map(alpha_glob); // Initialisation du dictionnaire final
	int before2 = (clock() *1000 / CLOCKS_PER_SEC);
	nb_letters_v2(tab_l1, nb_row, nb_col , alpha_glob );
	int after2=  (clock() *1000 / CLOCKS_PER_SEC);
	int diff2 = after2 - before2;

	// Ecriture des résultats
	myfile <<  nb_thread <<"\t"<< nb_row << "\t" << nb_col <<"\t"  << diff1 << "\t"  << diff2 <<  "\n";
 	myfile.close();

 	// Libération de l'espace mémoire alloué
	delete_letter_matrix(tab_l1 , nb_row, nb_col);
}



