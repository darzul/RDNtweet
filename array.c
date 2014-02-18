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

int ** init_2d_int_tab (int nb_row, int row_len)
{
	int i;
	int **tab = malloc (sizeof (int *) * nb_row);

	for (i=0; i < nb_row; i++)
	{
		tab [i] = malloc (sizeof (int) * row_len);
	}

	return tab;
}

float ** init_2d_float_tab (int nb_row, int row_len)
{
	int i;
	float **tab = malloc (sizeof (float *) * nb_row);

	for (i=0; i < nb_row; i++)
	{
		tab [i] = malloc (sizeof (float) * row_len);
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

void tab_string_to_file (FILE *file, char **tab, int tab_len)
{
	int i;

	for (i=0; i < tab_len; i++)
	{
		if (tab [i] != NULL)
		{
			fprintf (file, "%s", tab[i]);
		}
	}
}

void tab_float_to_file (FILE *file, float **tab, int tab_len, int row_len, char *result)
{
	int i, j;

	for (i=0; i < tab_len; i++)
	{
		if (tab [i] != NULL)
		{
			for (j=0; j < row_len; j++)
			{
				// 32 -> espace
				// 97-122 -> a-z
				/*if ( j == 32 || (j >= 97 && j <= 122) )
				{
					fprintf (file, "%f ", tab[i][j]);
				}*/
				
				fprintf (file, "%f ", tab[i][j]);
				
			}
			fprintf (file, "%s\n", result);
		}
	}
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
