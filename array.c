#include "array.h"

/*
	Alloc/Desalloc
*/
char ** init_2d_char_tab (int nb_row, int row_len)
{
	int i;
	char **tab = malloc (sizeof (char *) * nb_row);

	for (i=0; i < nb_row; i++)
	{
		tab [i] = malloc (sizeof (char) * row_len);
	}

	return tab;
}

void free_2d_tab (void **tab, int tab_len)
{
	int i;

	for (i=0; i < tab_len; i++)
	{
		free (tab [i]);
	}
	free (tab);

	return;
}

/*
	Data manipulation
*/
void file_to_tab (char *file_name, char ** tab, int tab_len, int max_len_per_row)
{
	FILE *file = fopen (file_name, "r+");
	int i;
	char *phrase = malloc (sizeof (char)*max_len_per_row);

	for (i=0; i < tab_len; i++)
	{
		fgets (phrase, max_len_per_row, file);
		strcpy (tab [i], phrase);
	}

	free (phrase);
	fclose (file);
}

/*
	Display data
*/
void print_2d_string_tab (char **tab, int tab_len)
{
	int i;

	for (i=0; i < tab_len; i++)
	{
		if (tab [i] != NULL)
			printf ("%s\n", tab [i]);
		else
			printf ("NULL\n");
	}
}
