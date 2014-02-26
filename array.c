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
	int i, j;
	int **tab = malloc (sizeof (int *) * nb_row);

	for (i=0; i < nb_row; i++)
	{
		tab [i] = malloc (sizeof (int) * row_len);

		for (j=0; j < row_len; j++)
		{
			tab[i][j] = 0;
		}
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

void tab_floatx2_to_file (char * file_name, float **tab1, int tab1Len, float **tab2, int tab2Len, int nbr_tweet, int nbr_data,  char *result)
{	
	int i, j;

	FILE *file = fopen (file_name, "w+");

	fprintf (file, "%d %d 7\n", nbr_data, tab1Len + tab2Len);
	
		for (i=0; i < nbr_tweet; i++)
		{
			if (tab1 [i] != NULL)
			{
				for (j=0; j <  tab1Len ; j++)
				{
					fprintf (file, "%f ", tab1[i][j]);
				}
			
		
				for (j=0; j < tab2Len; j++)
				{
			
					fprintf (file, "%f ", tab2[i][j]);

				}
		
			fprintf (file, "%s\n", result);
			}
		}
	fclose(file);
}

void tab_floatx3_to_file (char * file_name, float **tab1, int tab1Len, float **tab2, int tab2Len, float **tab3, int tab3Len, int nbr_tweet, int nbr_data,  char *result)
{
	int i, j;

	FILE *file = fopen (file_name, "w+");

	fprintf (file, "%d %d 7\n", nbr_data, tab1Len + tab2Len + tab3Len);
	
		for (i=0; i < nbr_tweet; i++)
		{
			if (tab1 [i] != NULL)
			{
				for (j=0; j <  tab1Len ; j++)
				{
					fprintf (file, "%f ", tab1[i][j]);
				}
			
		
				for (j=0; j < tab2Len; j++)
				{
			
					fprintf (file, "%f ", tab2[i][j]);

				}

				for (j=0; j < tab3Len; j++)
				{
			
					fprintf (file, "%f ", tab3[i][j]);

				}
		
			fprintf (file, "%s\n", result);
			}
		}
	fclose(file);
}

void tab_float_to_file (FILE *file, float **tab, int tab_len, int lineLen, char *result)
{
	int i, j;

	for (i=0; i < tab_len; i++)
	{
		if (tab [i] != NULL)
		{
			for (j=0; j < lineLen; j++)
			{	
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
