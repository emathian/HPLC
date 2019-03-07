void delete_matrix( double ** Tab,int nb_row, int nb_col);
void display( double** Tab, int nb_row, int nb_col );
void fill(double** Tab , int nb_row, int nb_col,int min, int max );
double ** generate_matrix( int nb_row, int nb_col);
void multi_mat(double ** m , const double  a ,  const int nb_row , const int nb_col );
double Random (double min , double max);
double sum_mat( double** m, const int nb_row , const int nb_col);
void sum_two_mat(double ** m3 ,  double ** m1 ,  double ** m2 , const int nb_row_m1 , const int nb_col_m1 , const int nb_row_m2 , const int nb_col_m2);


//######### Code matrice lettre a tester #########
std::map<char,int> alpha_map (void);
char** generate_letter_matrix( int nb_row, int nb_col);
void delete_letter_matrix( char ** Tab,int nb_row, int nb_col);
void letter_fill(char** Tab , int nb_row, int nb_col);
void letter_display(char** Tab, int nb_row, int nb_col );
void nb_letters(char** Tab, int nb_row, int nb_col);


//################################################
