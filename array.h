#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/*
	Alloc/Desalloc
*/
char ** init_2d_char_tab (int nb_row, int row_len);
void free_2d_tab (void **tab, int tab_len);

/*
	Data manipulation
*/
void file_to_tab (char *file_name, char ** tab, int tab_len, int max_len_per_row);

/*
	Display data
*/
void print_2d_string_tab (char **tab, int tab_len);
