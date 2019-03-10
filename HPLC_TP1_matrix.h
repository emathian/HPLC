/*--------------------- RESUME ---------------------------------------------------------
Ce programme rassemble les fonctions et les procédures de l'exercice 1 sur les matrices
et celles de l'exercices 2 sur les matrices de lettres.

La mise en parréllélisation de ces dernières a également été partiellement implémentée. 
Ce programme a été réalisé pour faciliter l'implémentation et les tests des fonctions et 
des procédures. 

Dans ce fichier les fonctions et procédures sont triées par ordre alphabétique et succinte-
ment présentées.
---------------------------------------------------------------------------------------*/

#include <map> // UTILE A TESTER ?
using namespace std; // UTILE A TESTER ?

/*--------- FONCTIONS ET PROCEDURES SUR LES MATRICES DE NOMBRES  -----------------------*/

/*--------------------- Procédure : delete_matrix ----------------------------------------
	Cette procédure permet de libérer la mémoire allouée pour construire une matrice de 
	taille nb_row x nb_col.
	Précondition : L'espace mémoire de la matrice Tab doit avoir préalablement allouée.
	Post-condition : La matrice Tab est suprimée.
------------------------------------------------------------------------------------------*/
void delete_matrix( double ** Tab, const int nb_row, const int nb_col);


/*--------------------- Procédure : display-------------------------------------------------
	Cette procédure permet d'afficher le contenu d'une matrice.
	Précondition : L'espace mémoire de la matrice Tab doit avoir préalablement allouée.
------------------------------------------------------------------------------------------*/
void display( double** Tab, const int nb_row, const int nb_col );


/*--------------------- Procédure : fill -------------------------------------------------
	Cette procédure permet de remplir une matrice de taille nb_rox x nb_col par des doubles 
	aléatoires compris entre min et max.
	Précondition : L'espace mémoire de la matrice Tab doit avoir préalablement allouée.
	Post-condition : La matrice contient des doubles générés aléatoirement.
------------------------------------------------------------------------------------------*/
void fill(double** Tab , const int nb_row, const int nb_col, const int min, const int max );


/*--------------------- Fonction : generate_matrix ------------------------------------------
	Cette fonction permet d'allouer l'espace mémoire nécessaire pour une matrice de taille
	nb_rox x nb_col.
--------------------------------------------------------------------------------------------*/
double ** generate_matrix(const int nb_row, const int nb_col);


/*--------------------- Procédure : multi_mat ------------------------------------------------
	Cette procédure permet de multiplier les éléments d'une matrice par un double (a).
	Précondition : L'espace mémoire de la matrice Tab doit avoir préalablement allouée.
--------------------------------------------------------------------------------------------*/
void multi_mat(double ** m , const double  a ,  const int nb_row , const int nb_col );


/*--------------------- Fonction : Random  ---------------------------------------------------
	Cette fonction permet de générer un nombre alétoire compris entre min et max.
	Elle est utilisée par la procédure fill.
--------------------------------------------------------------------------------------------*/
double Random (const double min ,const double max);


/*--------------------- Fonction : sum_mat --------------------------------------------------
	Cette fonction permet de sommer les éléments d'une matrice.
	Précondition : L'espace mémoire de la matrice Tab doit avoir préalablement allouée.
	Post-condition : sum_mat retourne un double égale à la somme des éléments de la matrice m
--------------------------------------------------------------------------------------------*/
double sum_mat( double** m, const int nb_row , const int nb_col);


/*--------------------- Procédure : sum_two-mat -----------------------------------------------
	Cette fonction permet de sommer les éléments de matrice (m1 et m2).
	Précondition : - Les matrices m1, m2 et m3 doivent avoir la même taille,
				   - L'espace mémoire de la matrice de la matrice des résultats doit être allouée,
				   il en est de même pour les matrices m1 et m2 évidemment.
	Post-condition : Les éléments de la matrice m3 sont égaux à la somme des éléments de m1 et m2
------------------------------------------------------------------------------------------------*/
void sum_two_mat(double ** m3 ,  double ** m1 ,  double ** m2 , const int nb_row_m1 , const int nb_col_m1 , const int nb_row_m2 , const int nb_col_m2);


/*--------- FONCTIONS ET PROCEDURES SUR LES MATRICES DE LETTRES  ------------------------------*/

/*--------------------- Procédure : multi_mat ---------------------------------------------------
	Cette procédure permet d'initiliser le dictionnaire des résultats. Le compteur de chaque 
	lettre est mis à zério
	Exemple : A -> 0
	Précondition : Le dictionnaire Alpha doit être initialisé avec en clé un char et en valeur un int.
--------------------------------------------------------------------------------------------*/
void alpha_map(std::map<char,int> &Alpha);


/*--------------------- Procédure : delete_letter_matrix -----------------------------------
	Cette procédure permet de libérer la mémoire allouée pour construire une matrice de char 
	de taille nb_row x nb_col.
	Précondition : L'espace mémoire de la matrice de lettres Tab doit avoir préalablement allouée.
	Post-condition : La matrice Tab est suprimée.
------------------------------------------------------------------------------------------*/
void delete_letter_matrix( char ** Tab, const int nb_row, const int nb_col);


/*--------------------- Procédure : display_map-----------------------------------------------
	Cette procédure permet d'afficher le dictionnaires contennant le résultats du dénombrement.
------------------------------------------------------------------------------------------*/
void display_map (std::map<char,int> &Alpha);


/*--------------------- Fonction : generate_letter_matrix ----------------------------------
	Cette fonction permet d'allouer l'espace mémoire nécessaire pour une matrice de char de 
	taille nb_rox x nb_col.
--------------------------------------------------------------------------------------------*/
char** generate_letter_matrix(const int nb_row, const int nb_col);


/*--------------------- Procédure : letter_fill ---------------------------------------------
	Cette procédure permet de remplir une matrice de taille nb_row x nb_col par des lettres 
	capitales générées aléatoirement.
--------------------------------------------------------------------------------------------*/
void letter_fill(char** Tab , int nb_row, int nb_col);


/*--------------------- Procédure : letter_display ---------------------------------------------
	Cette procédure permet d'afficher les éléments d'une matrice de char.
-----------------------------------------------------------------------------------------------*/
void letter_display(char** Tab, int nb_row, int nb_col );


/*--------------------- Procédure : nb_letters --------------------------------------------------
	Cette procédure permet de dénombrer les lettres contenues dans une matrice de char.
	Précondition : - La matrice de lettres doit être générée et remplie par des lettres capitales,
				   - Le dictionnaire des résultats doit être initialisé (cf : alpha_map)
	Post-condition : - Les valeurs du dictionnaire (Alpha) correspondent au nombre d'occurence des 
					clés dans la matrice de lettres (Tab).	
-----------------------------------------------------------------------------------------------*/
void nb_letters(char**Tab, int nb_row, int nb_col, map<char,int> &Alpha);


