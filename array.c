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
	int i,j;
	float **tab = malloc (sizeof (float *) * nb_row);

	for (i=0; i < nb_row; i++)
	{
		tab [i] = malloc (sizeof (float) * row_len);

		for (j=0; j < row_len; j++)
			tab [i][j] = 0;
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
	int i = 0, nb_char = 0;
	char c;

	while ( (c = fgetc (file)) != EOF )
	{
		if (nb_char < max_len_per_row)
		{
			tab [i][nb_char] = c;
		}

		nb_char ++;

		if (c == '\n')
		{
			if (nb_char > max_len_per_row)
			{
				printf ("ERROR : tweet too long, line :%d\n", i);
				tab[i][max_len_per_row-1] = '\n';
			}

			i++;
			nb_char = 0;
		}
	}

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

void tab_floatx1_to_file (char * file_name, float **tab, int tabLen, int nbr_tweet, int nbr_data, int nb_output, char *result)
{
	int i, j;

	FILE *file = fopen (file_name, "w+");

	fprintf (file, "%d %d %d\n", nbr_data, tabLen, nb_output);
	
		for (i=0; i < nbr_tweet; i++)
		{
			if (tab [i] != NULL)
			{
				for (j=0; j < tabLen ; j++)
					fprintf (file, "%f ", tab[i][j]);
		
				fprintf (file, "%s\n", result);
			}
		}
	fclose(file);
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

void tab_floatx4_to_file (char * file_name, float **tab1, int tab1Len, float **tab2, int tab2Len, float **tab3, int tab3Len, float** tab4, int tab4Len, int nbr_tweet, int nbr_data,  char *result)
{
	int i, j;

	FILE *file = fopen (file_name, "w+");

	fprintf (file, "%d %d 7\n", nbr_data, tab1Len + tab2Len + tab3Len + tab4Len);
	
		for (i=0; i < nbr_tweet; i++)
		{
			if (tab1 [i] != NULL)
			{
				for (j=0; j <  tab1Len ; j++)
					fprintf (file, "%f ", tab1[i][j]);
		
				for (j=0; j < tab2Len; j++)
					fprintf (file, "%f ", tab2[i][j]);

				for (j=0; j < tab3Len; j++)
					fprintf (file, "%f ", tab3[i][j]);

				for (j=0; j < tab4Len; j++)
					fprintf (file, "%f ", tab4[i][j]);
		
			fprintf (file, "%s\n", result);
			}
		}
	fclose(file);
}

void tab_floatx5_to_file (char * file_name, float **tab1, int tab1Len, float **tab2, int tab2Len, float **tab3, int tab3Len, float** tab4, int tab4Len, float **tab5, int tab5Len, int nbr_tweet, int nbr_data, char *result)
{
	int i, j;

	FILE *file = fopen (file_name, "w+");

	fprintf (file, "%d %d 7\n", nbr_data, tab1Len + tab2Len + tab3Len + tab4Len + tab5Len);
	
		for (i=0; i < nbr_tweet; i++)
		{
			if (tab1 [i] != NULL)
			{
				for (j=0; j < tab1Len ; j++)
					fprintf (file, "%f ", tab1[i][j]);
		
				for (j=0; j < tab2Len; j++)
					fprintf (file, "%f ", tab2[i][j]);

				for (j=0; j < tab3Len; j++)
					fprintf (file, "%f ", tab3[i][j]);

				for (j=0; j < tab4Len; j++)
					fprintf (file, "%f ", tab4[i][j]);

				for (j=0; j < tab5Len; j++)
					fprintf (file, "%f ", tab5[i][j]);
		
			fprintf (file, "%s\n", result);
			}
		}
	fclose(file);
}

void tab_floatx1_to_file_withNULL (char * file_name, float **tab, int tabLen, int nbr_tweet, int nbr_data, int nb_output, char *result)
{
	int i, j;

	FILE *file = fopen (file_name, "w+");

	fprintf (file, "%d %d %d\n", nbr_data, tabLen, nb_output);
	
		for (i=0; i < nbr_tweet; i++)
		{
			if (tab [i] != NULL)
			{
				for (j=0; j < tabLen ; j++)
					fprintf (file, "%f ", tab[i][j]);
		
				fprintf (file, "%s\n", result);
			}
			else
			{
				for (j=0; j < tabLen ; j++)
					fprintf (file, "0 ");

				fprintf (file, "%s\n", result);
			}
		}
	fclose(file);
}

void tab_floatx5_to_file_withNULL (char * file_name, float **tab1, int tab1Len, float **tab2, int tab2Len, float **tab3, int tab3Len, float** tab4, int tab4Len, float **tab5, int tab5Len, int nbr_tweet, int nbr_data, int nb_output, char *result)
{
	int i, j, nb_inputs = tab1Len + tab2Len + tab3Len + tab4Len + tab5Len;

	FILE *file = fopen (file_name, "w+");

	fprintf (file, "%d %d %d\n", nbr_data, nb_inputs, nb_output);
	
		for (i=0; i < nbr_tweet; i++)
		{
			if (tab1 [i] != NULL)
			{
				for (j=0; j < tab1Len ; j++)
					fprintf (file, "%f ", tab1[i][j]);
		
				for (j=0; j < tab2Len; j++)
					fprintf (file, "%f ", tab2[i][j]);

				for (j=0; j < tab3Len; j++)
					fprintf (file, "%f ", tab3[i][j]);

				for (j=0; j < tab4Len; j++)
					fprintf (file, "%f ", tab4[i][j]);

				for (j=0; j < tab5Len; j++)
					fprintf (file, "%f ", tab5[i][j]);
		
				fprintf (file, "%s\n", result);
			}
			else
			{
				for (j=0; j < nb_inputs ; j++)
					fprintf (file, "0 ");

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
