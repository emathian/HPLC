/*--------------------- RESUME ---------------------------------------------------------
Ce programme rassemble les fonctions et les procédures de l'exercice 2 sur les matrices
de lettres.

La mise en parréllélisation de ces dernières a également été implémentée. Ce programme a 
été réalisé pour évaluer la performance de la parallélisation par passage à l'échelle 
forte et faible.  
Les fonctions sont présentées dans l'ordre alphabétique.
---------------------------------------------------------------------------------------*/

#include <map> // ?
using namespace std; // ?


/*---------------------CONSIGNES DE COMPLATION ------------------------------------------
Pour compiler ce fichier merci d'indiquer l'option -fopenmp
Exemple : g++ -fopenmp HPLC_matrix_letters.cpp -o HPLC_matrix_letters
--------------------------------------------------------------------------------------*/

/*---------------------CONSIGNES D'EXECUTION ----- --------------------------------------
Pour l'éxution du programme merci d'indiquer en premier argument le type de force, avec 0
pour la force forte et 1 pour la force faible. Le nombre de runs doit également être spécifié
Exemple : ./HPLC_matrix_letters 0 10
--------------------------------------------------------------------------------------*/


/*--------------------- Procédure : delete_letter_matrix -----------------------------------
	Cette procédure est utilisée par nb_letter_v2, elle permet d'ajouter deux dictionnaires
	contenant le nombre d'occurences de chaque de lettres.
	Précondition : -Les deux dictionnaires ont été préalablement initialisés (cf : init_map)
	Post condition : - A la fin de la pocédure les valeurs du dictionnaire nommé Alpha ont été
						mises à jour
------------------------------------------------------------------------------------------*/
void ajout_map(std::map<char,int> &Alpha, std::map<char,int> &Alpha_inter)


/*--------------------- Procédure : delete_letter_matrix -----------------------------------
	Cette procédure permet de libérer la mémoire allouée pour la construction d'une matrice de 
	taille nb_row x nb_col.
	
	Post-condition : La matrice Tab est suprimée.
------------------------------------------------------------------------------------------*/
void delete_letter_matrix( char ** Tab,int nb_row, int nb_col);


/*--------------------- Procédure : display_map ----------------------------------------------
	Cette procédure permet d'afficher le contenu des résultats de nb_letters et nb_letters_v2.
------------------------------------------------------------------------------------------*/
void display_map (std::map<char,int> &Alpha);


/*--------------------- Fonction : generate_letter_matrix ----------------------------------
	Cette fonction permet d'allouer l'espace mémoire nécessaire pour une matrice de char de 
	taille nb_rox x nb_col.
--------------------------------------------------------------------------------------------*/
char** generate_letter_matrix( int nb_row, int nb_col);


/*--------------------- Procédure : init_mat ---------------------------------------------------
	Cette procédure permet d'initiliser le dictionnaire des résultats. Le compteur de chaque 
	lettre est mis à zério
	Exemple : A -> 0
	Précondition : Le dictionnaire Alpha doit être initialisé avec en clé un char et en valeur un int.
--------------------------------------------------------------------------------------------*/
void init_map(std::map<char,int> &Alpha);


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
	Cette procédure permet de dénombrer les lettres contenues dans une matrice de char. Elle prend
	en argument un dictionnaire dont la clé est la lettre et la valeur est le nombre d'occurences
	à la fin du calcul. Cette fonction est parallélisé sur le problème complet (Q2.4).
	Précondition : - La matrice de lettres doit être générée et remplie par des lettres capitales,
				   - Le dictionnaire des résultats doit être initialisé (cf : alpha_map)
	Post-condition : - Les valeurs du dictionnaire (Alpha) correspondent au nombre d'occurence des 
					clés dans la matrice de lettres (Tab).	
-----------------------------------------------------------------------------------------------*/
void nb_letters(char**Tab, int nb_row, int nb_col, map<char,int> &Alpha);


/*--------------------- Procédure : nb_letters_v2 --------------------------------------------------
	Cette procédure permet de dénombrer les lettres contenues dans une matrice de char. Elle prend
	en argument un dictionnaire, chaque  clé représente une lettre, la valeur associé correspond au
	nombre d'occurences trouvées dans la matrice. Cette fonction est parallélisé sur le problème
	découpé (Q2.5 à Q2.7). Ainsi elle crée des dictionnaires intermédiaires permettant le dénombrement
	des lettres par ligne parcourue, les résultats de chaque ligne sont ensuite ajoutés au dictionnaire
	global via l'appel à  ajout_map.
	Précondition : - La matrice de lettres doit avoir été générée et remplie par des lettres capitales,
				   - Le dictionnaire des résultats doit être initialisé (cf : alpha_map)
	Post-condition : - Les valeurs du dictionnaire (Alpha) correspondent au nombre d'occurence des 
					clés dans la matrice de lettres (Tab).	
-----------------------------------------------------------------------------------------------*/
void nb_letters_v2(char**Tab, int nb_row, int nb_col, map<char,int> &Alpha);

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
		
	Préconditions : - Le fichier de résultats doit être crée.

	Postcondition : - À chaque appel de la procédure une ligne de résultat est écrite.
------------------------------------------------------------------------------------------*/
void main_func(const int nb_thread, const int  nb_row, const int  nb_col, const char* file_name );


