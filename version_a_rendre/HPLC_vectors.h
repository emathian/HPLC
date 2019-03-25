/*--------------------- RESUME ---------------------------------------------------------
Ce programme rassemble les fonctions et les procédures de l'exercice 1 sur les vecteurs.
La mise en parréllélisation de ces dernières a également été implémentée. Ce programme a 
été réalisé pour évaluer la performance de la parallélisation par passage à l'échelle 
forte et faible.  
Dans ce fichier les fonctions et procédures sont triées par ordre alphabétique et succinte-
ment présentées.
---------------------------------------------------------------------------------------*/

/*---------------------CONSIGNES DE COMPLATION --------------------------------------------
Pour compiler ce fichier merci d'indiquer l'option -fopenmp
Exemple : g++ -fopenmp HPLC_vectors.cpp -o HPLC_vectors
--------------------------------------------------------------------------------------*/

/*---------------------CONSIGNES D'EXECUTION ----- --------------------------------------
Pour l'éxution du programme merci d'indiquer en premier argument le type de force, avec 0
pour la force forte et 1 pour la force faible. Le nombre de runs doit également être spécifié
Exemple : ./HPLC_vectors 0 10
--------------------------------------------------------------------------------------*/


/*--------------------- Procédure : display  ------------------------------------------------
	Cette procédure permet l'affichage d'un vecteur de taille défini.
	Précondition : Le vecteur (Tab) doit être instancié, et la mémoire nécessaire allouée.
--------------------------------------------------------------------------------------------*/
void display(const double* Tab, const int Taille_tab);


/*--------------------- Procédure : fill --------------------------------------------------
	Cette procédure permet le remplissage d'un vecteur, de taille défini, par des doubles
	générés aléatoirement compris entre min et max. La parallélisation de cette opératon est
	assurée.
	Précondition : Le vecteur (Tab) doit être instancié, et la mémoire nécessaire allouée.
	Post-condition : Les valeurs des éléments du vecteur correspondent à un double aléatoire.
------------------------------------------------------------------------------------------*/
void fill(double* Tab , int Taille_tab, int min, int max );


/*--------------------- Procédure : main_func ------------------------------------------------
	Cette procédure organise l'éxécution de l'ensemble des fonctions et des procédures du programme.
	Les résultats de l'éxécution seront stockés dans un fichier, dont le nom est spécifié par 
	l'utilisateur (file_name). Ils seront organisés en quatres colonnes tel que:

	Nombre de tread | Taille des vecteurs | Durée : somme de deux vecteurs | Durée : Somme des 
	éléments d'un vecteur | Durée : Multiplication d'un vecteur par une constante

	La procédure réalise les étapes suivantes :
		- 1) Création de trois vecteurs de double et allocation mémoire, 
		- 2) Remplissage de deux vecteurs (cf: procédure fill et random),
		- 3) Calcul de la somme de deux vecteurs (cf : sum_two_vecr ), les résultats sont stockés dans
		le troisième vecteur. La durée du calcul est mémorisée,
		- 4) Calcul de la somme des éléments d'un vecteur (cf : sum_vect), et mémorisation de la durée,
		- 5) Multiplication des éléments d'un vecteur par un double (cf : multi_vector) 
		et mémorisation de la durée.
	
	Préconditions : - Le fichier de résultats doit être crée.
		
	Postcondition : - À chaque appel de la procédure une ligne de résultat est écrite.
------------------------------------------------------------------------------------------*/
void main_func(const int nb_thread, const int  Taille_tab, const char* file_name);


/*--------------------- Procédure : multi_vector (Multiplication du vecteur par un double) --
	Cette procédure permet de multiplier les éléments d'un vecteur par une constante (a).
	Précondition:  - Le vecteur doit être instancié, et la mémoire nécessaire allouée.
--------------------------------------------------------------------------------------------*/
void multi_vector(double * v , const double  a ,  const int taille_v );


/*--------------------- Fonction : Random  -------------------------------------------------
	Cette fonction retourne un double généré alétoirement entre les bornes définies par min
	er max. La fonction Random est appélé par la procédure fill.
------------------------------------------------------------------------------------------*/
double Random (double min , double max);


/*--------------------- Procédure : sum_two_vector (Somme de deux vecteurs)  ----------------
	Cette procédure permet de sommer deux vecteurs et retourne les résultats dans un vecteur v3.
	Préconditions: - Les vecteurs doivent être instanciés, et la mémoire nécessaire allouée.
				   - Les tailles des vecteurs à sommer (v1 et v2) doivent être égales.
	Postcondition: - Les éléments du vecteur v3 sont équivalents à la somme des éléments de v1
					 et v2. 
--------------------------------------------------------------------------------------------*/
void sum_two_vector(double* v3 , const double * v1 , const double * v2 , const int taille_v1 , const int taille_v2  );


/*--------------------- Fonction : sum_vector (Somme des éléments d'un vecteur)  ----------------
	Cette fonction permet de sommer les éléments d'un vecteur et retourne le résultat (double).
	Précondition:  - Le vecteur doit être instancié, et la mémoire nécessaire allouée.
--------------------------------------------------------------------------------------------*/
double sum_vector(const double Tab[], int Taille_tab);



