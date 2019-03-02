void delete_matrix( double ** Tab,int nb_row, int nb_col);
void display( double** Tab, int nb_row, int nb_col );
void fill(double** Tab , int nb_row, int nb_col,int min, int max );
double ** generate_matrix( int nb_row, int nb_col);
void main_func(const int nb_thread, const int  nb_row, const int  nb_col, const char* file_name, const double A);
void multi_mat(double ** m , const double  a ,  const int nb_row , const int nb_col );
double Random (double min , double max);
double sum_mat( double** m, const int nb_row , const int nb_col);
void sum_two_mat(double ** m3 ,  double ** m1 ,  double ** m2 , const int nb_row_m1 , const int nb_col_m1 , const int nb_row_m2 , const int nb_col_m2);