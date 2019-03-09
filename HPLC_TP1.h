/*--------------------- RESUME ---------------------------------------------------------
Ce programme rassemble les fonctions et les procédures de l'exercice 1 sur les vecteurs.
La mise en parréllélisation de ces dernières a également été implémentée. Ce programme a 
été réalisé pour faciliter l'implémentation et les tests des fonctions et des procédures. 

Dans ce fichier les fonctions et procédures sont triées par ordre alphabétique et succinte-
ment présentées.
---------------------------------------------------------------------------------------*/

/*--------------------- Procédure : display  ------------------------------------------------
	Cette procédure permet l'affichage d'un vecteur de taille définit.
	Précondition : Le vecteur (Tab) doit être instancié, et la mémoire nécessaire allouée.
--------------------------------------------------------------------------------------------*/
void display(const double* Tab, const int Taille_tab);


/*--------------------- Procédure : fill --------------------------------------------------
	Cette procédure permet le remplissage d'un vecteur, de taille défini, par des doubles
	générés aléatoirement compris entre min et max. La parallélisation de cette opératon est
	assurée.
	Précondition : Le vecteur (Tab) doit être instancié, et la mémoire nécessaire allouée.
	Post-condition : La valeur des éléments du vecteur correspondent à un nombre aléatoire.
------------------------------------------------------------------------------------------*/
void fill(double* Tab , const int Taille_tab, const int min, const int max );


/*--------------------- Fonction : Random  -------------------------------------------------
	Cette fonction retourne un double généré alétoirement entre les bornes définies par min
	er max. La fonction Random est appélé par la procédure fill.
------------------------------------------------------------------------------------------*/
double Random (const double min , const double max);


/*--------------------- Procédure : multi_vector (Multiplication du vecteur par un double) --
	Cette procédure permet de multiplier les éléments d'un vecteur par une constante (a).
	Précondition:  - Le vecteur doit être instancié, et la mémoire nécessaire allouée.
--------------------------------------------------------------------------------------------*/
void multi_vector(double * v , const double  a ,  const int taille_v );


/*--------------------- Procédure : sum_two_vector (Somme de deux vecteurs)  ----------------
	Cette procédure permet de sommer deux vecteurs et retourne les résultats dans un vecteur v3.
	Préconditions: - Les vecteurs doivent être instanciés, et la mémoire nécessaire allouée.
				   - La taille des vecteurs à sommer (v1 et v2) doit être égale.
	Postcondition: - Les éléments du vecteur v3 sont équivalents à la somme des éléments de v1
					 et V2. 
--------------------------------------------------------------------------------------------*/
void sum_two_vector(double* v3 , const double * v1 , const double * v2 , const int taille_v1 , const int taille_v2 );


/*--------------------- Fonction : sum_vector (Somme des éléments d'un vecteur)  ----------------
	Cette fonction permet de sommer les éléments d'un vecteur et retourne le résultat (double).
	Précondition:  - Le vecteur doit être instancié, et la mémoire nécessaire allouée.
--------------------------------------------------------------------------------------------*/
double sum_vector(const double Tab[], const int Taille_tab);


