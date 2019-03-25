/*--------------------- RESUME ---------------------------------------------------------
Ce programme rassemble les fonctions et les procédures de l'exercice 2 sur les matrices
de lettres.

La mise en parréllélisation de ces dernières a également été implémentée. Ce programme a 
été réalisé pour évaluer la performance de la parallélisation par passage à l'échelle 
forte et faible, pour les matrices de LETTRES.  

Aisi cette entête  introduit la procédure  main.func contanant les principales directives 
pour l'évaluation de la performance. 
---------------------------------------------------------------------------------------*/

#include <map> // ?
using namespace std; // ?


/*--------------------- Procédure : delete_letter_matrix -----------------------------------
	Cette procédure est utilisée par nb_letter_v2, elle permet d'ajouter deux dictionnaires
	contenant les fréquences de lettres.
	Précondition : -Les deux dictionnaires ont été préalablement initialisés (cf : init_map)
	Post condition : - A la fin de la pocédure les valeurs du dictionnaire nommé Alpha ont été
						mises à jour
------------------------------------------------------------------------------------------*/
void ajout_map(std::map<char,int> &Alpha, std::map<char,int> &Alpha_inter)

/*--------------------- Procédure : delete_letter_matrix -----------------------------------
	Cette procédure permet de libérer la mémoire allouée pour construire une matrice de 
	taille nb_row x nb_col.
	Précondition : L'espace mémoire de la matrice Tab doit avoir préalablement allouée.
	Post-condition : La matrice Tab est suprimée.
------------------------------------------------------------------------------------------*/
void delete_letter_matrix( char ** Tab,int nb_row, int nb_col);


/*--------------------- Procédure : display_map ----------------------------------------------
	Cette procédure permet d'afficher le contenu des résultats de nb_letters et nb_letters_v2.
	Précondition : L'espace mémoire de la matrice Tab doit avoir préalablement allouée.
------------------------------------------------------------------------------------------*/
void display_map (std::map<char,int> &Alpha);


/*--------------------- Fonction : generate_letter_matrix ----------------------------------
	Cette fonction permet d'allouer l'espace mémoire nécessaire pour une matrice de char de 
	taille nb_rox x nb_col.
--------------------------------------------------------------------------------------------*/
char** generate_letter_matrix( int nb_row, int nb_col);


/*--------------------- Procédure : multi_mat ---------------------------------------------------
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
	des résultats finaux via l'appel à  ajout_map.
	Précondition : - La matrice de lettres doit être générée et remplie par des lettres capitales,
				   - Le dictionnaire des résultats doit être initialisé (cf : alpha_map)
	Post-condition : - Les valeurs du dictionnaire (Alpha) correspondent au nombre d'occurence des 
					clés dans la matrice de lettres (Tab).	
-----------------------------------------------------------------------------------------------*/
void nb_letters_v2(char**Tab, int nb_row, int nb_col, map<char,int> &Alpha);

/*--------------------- Procédure : main_func ------------------------------------------------
	Cette procédure organise l'éxécution de l'ensemble des fonctions et procédures du programme
	associé au matrices de lettres. Les résultats de l'éxécution seront stockés dans un fichier,
	dont le nom est spécifié par l'utilisateur (file_name). Ces derniers seront organisés en cinq
	colonnes telles que:

	Nombre de tread | Nb lignes |Nb cols | Durée : parallélisation V1 | Durée : parallélisation V2 
	éléments d'un vecteur | Durée : Multiplication d'un vecteur par une constante

	La procédure réalise les étapes suivantes :
		- 1) Création d'une atruce de la matrice de lettres   et allocation mémoire, 
		- 2) Remplissage de la matrice de lettres (cf: procédure fill_letter),
		- 3) Initialisation du dictionnaire des résultats
		- 4) Calcul des fréquences de lettres grâce à la première version de parallélisation, 
			(nb_letters) et mémorisation de la durée,
		- 5) Initialisation d'un second dictinnaire final de résultats pour la seconde version de parallélisation
		- 6) Calcul des fréquences de lettres grâce à la deuxième version de parallélisation, 
			(nb_letters_v2) et mémorisation de la durée,
		- 7) Ecriture d'une ligne de résultats
		
	Préconditions : - Le fichier de résultats doit être crée.
				   - Les options d'exécution (nombre de coeur et taille des vecteurs) doivent être 
				     passéees en arguement. 

	Postcondition : - À chaque appel de la procédure une ligne de résultat est écrite.
------------------------------------------------------------------------------------------*/
void main_func(const int nb_thread, const int  nb_row, const int  nb_col, const char* file_name );


