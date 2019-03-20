#include <map>
using namespace std;


void  init_map(std::map<char,int> &Alpha);
char** generate_letter_matrix( int nb_row, int nb_col);
void delete_letter_matrix( char ** Tab,int nb_row, int nb_col);
void display_map (std::map<char,int> &Alpha);
void letter_fill(char** Tab , int nb_row, int nb_col);
void letter_display(char** Tab, int nb_row, int nb_col );
void nb_letters(char**Tab, int nb_row, int nb_col, map<char,int> &Alpha);
void nb_letters_v2(char**Tab, int nb_row, int nb_col, map<char,int> &Alpha, map<char,int> &Alpha_inter)
void main_func(const int nb_thread, const int  nb_row, const int  nb_col, const char* file_name );

