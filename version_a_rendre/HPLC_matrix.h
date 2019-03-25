/*--------------------- RESUME ---------------------------------------------------------
Ce programme rassemble les fonctions et les procédures de l'exercice 1 sur les matrices
de nombres.
La mise en parréllélisation de ces dernières a  été implémentée. Ce programme a 
été réalisé pour évaluer la performance de la parallélisation pour les passages à l'échelle 
forte et faible.  
Dans ce fichier les fonctions et procédures sont triées par ordre alphabétique et succinte-
ment présentées.
---------------------------------------------------------------------------------------*/

/*---------------------CONSIGNES DE COMPLATION --------------------------------------------
Pour compiler ce fichier merci d'indiquer l'option -fopenmp
Exemple : g++ -std=c++11 -fopenmp HPLC_matrix.cpp -o HPLC_matrix
--------------------------------------------------------------------------------------*/

/*---------------------CONSIGNES D'EXECUTION ----- --------------------------------------
Pour l'éxution du programme merci d'indiquer en premier argument le type d'échelle, avec 0
pour l'échelle forte et 1 pour l'échelle faible. Le nombre de runs doit également être spécifié
Exemple : ./HPLC_matrix 0 10
--------------------------------------------------------------------------------------*/

/*--------------------- Procédure : delete_matrix ----------------------------------------
	Cette procédure permet de libérer la mémoire allouée pour la construction d'une matrice de 
	taille nb_row x nb_col.
	Précondition : L'espace mémoire de la matrice Tab doit avoir été préalablement allouée.
	Post-condition : La matrice Tab est suprimée.
------------------------------------------------------------------------------------------*/
void delete_matrix( double ** Tab,int nb_row, int nb_col);


/*--------------------- Procédure : display-------------------------------------------------
	Cette procédure permet d'afficher le contenu d'une matrice.
	Précondition : L'espace mémoire de la matrice Tab doit avoir préalablement allouée.
------------------------------------------------------------------------------------------*/
void display( double** Tab, int nb_row, int nb_col );

/*--------------------- Procédure : fill -------------------------------------------------
	Cette procédure permet de remplir une matrice de taille nb_rox x nb_col par des doubles 
	aléatoires compris entre min et max.
	Précondition : L'espace mémoire de la matrice Tab doit avoir préalablement allouée.
	Post-condition : La matrice contient des doubles générés aléatoirement.
------------------------------------------------------------------------------------------*/
void fill(double** Tab , int nb_row, int nb_col,int min, int max );

/*--------------------- Fonction : generate_matrix ------------------------------------------
	Cette fonction permet d'allouer l'espace mémoire nécessaire pour une matrice de taille
	nb_rox x nb_col.
--------------------------------------------------------------------------------------------*/
double ** generate_matrix( int nb_row, int nb_col);

/*--------------------- Procédure : main_func ------------------------------------------------
	Cette procédure organise l'éxécution de l'ensemble des fonctions et des procédures du programme
	associé au matrices de nombres. Les résultats de l'éxécution seront stockés dans un fichier,
	dont le nom est spécifié par l'utilisateur (file_name). Ces derniers seront organisés en cinq
	colonnes tel que:

	Nombre de tread | Nb lignes |Nb cols | Durée : somme de deux vecteurs | Durée : Somme des 
	éléments d'un vecteur | Durée : Multiplication d'un vecteur par une constante

	La procédure réalise les étapes suivantes :
		- 1) Création de trois matrices  de double et allocation mémoire, 
		- 2) Remplissage de deux matrices (cf: procédure fill et random),
		- 3) Calcul de la somme de deux matrices (cf : sum_two_mat ), et mémorisation de la durée,
		- 4) Calcul de la somme des éléments d'une matrice (cf : sum_mat ), et mémorisation de la durée,
		- 5) Multiplication d'une matrice par un double (cf : multi_mat) et mémorisation de la durée.
	
	Préconditions : - Le fichier de résultats doit avoir été  crée.
				   - Les options d'exécution (nombre de coeurs de calcul et taille des vecteurs) doivent être 
				     passéees en arguement. 

	Postcondition : - À chaque appel de la procédure une ligne de résultat est écrite.
------------------------------------------------------------------------------------------*/
void main_func(const int nb_thread, const int  nb_row, const int  nb_col, const char* file_name, const double A);


/*--------------------- Procédure : multi_mat ------------------------------------------------
	Cette procédure permet de multiplier les éléments d'une matrice par un double (a).
--------------------------------------------------------------------------------------------*/
void multi_mat(double ** m , const double  a ,  const int nb_row , const int nb_col );


/*--------------------- Fonction : Random  ---------------------------------------------------
	Cette fonction permet de générer un nombre alétoire compris entre min et max.
	Elle est utilisée par la procédure fill.
--------------------------------------------------------------------------------------------*/
double Random (double min , double max);


/*--------------------- Fonction : sum_mat --------------------------------------------------
	Cette fonction permet de sommer les éléments d'une matrice.
	Post-condition : sum_mat retourne un double égale à la somme des éléments de la matrice m
--------------------------------------------------------------------------------------------*/
double sum_mat( double** m, const int nb_row , const int nb_col);


/*--------------------- Procédure : sum_two-mat -----------------------------------------------
	Cette fonction permet de sommer les éléments de matrice (m1 et m2).
	Précondition : - Les matrices m1, m2 et m3 doivent avoir la même taille,
	
	Post-condition : Les éléments de la matrice m3 sont égaux à la somme des éléments de m1 et m2
------------------------------------------------------------------------------------------------*/
void sum_two_mat(double ** m3 ,  double ** m1 ,  double ** m2 , const int nb_row_m1 , const int nb_col_m1 , const int nb_row_m2 , const int nb_col_m2);

