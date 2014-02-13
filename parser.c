#include "parser.h"

int main (int argc, char *argv[]) 
{
	if (argc != 4 || strlen (argv [3]) != 2)
	{
		printf ("Please enter correct args\n./parser.exe input_file output_file language");
		return 0;
	}

	char *result = NULL;

	if ( ( result = lang_to_result (argv [3]) ) == NULL )
	{
		printf ("Wrong language\nPossibilities are : fr, en, es, tr, de, pt, it\n");
		return 0;
	}

	int nb_tweet = count_tweets_from_file (argv [1]);
	char **tweets = init_2d_char_tab (nb_tweet, CHAR_MAX_PER_TWEET);

	file_to_tab (argv[1], tweets, nb_tweet, CHAR_MAX_PER_TWEET);

	removeDouble (tweets, nb_tweet);
	removeURL (tweets, nb_tweet);

	float **frq_tab = create_frq_tab (tweets, nb_tweet);
	//print_2d_string_tab (tweets, nb_tweet);

	int nb_data = count_tweets_from_tab (tweets, nb_tweet);

	data_to_file (argv [2], frq_tab, nb_tweet, nb_data, NB_INPUT, NB_OUTPUT, result);

	free (result);
	free_2d_tab ( (void **) tweets, nb_tweet);
	free_2d_tab ( (void **) frq_tab, nb_tweet);

	return 0;
}

int count_tweets_from_file (char *file_name)
{
	FILE *file = fopen (file_name, "r+");
	int nb_tweet = 0;
	char *tweet = malloc (sizeof (char)*CHAR_MAX_PER_TWEET);

	while ( fgets (tweet, CHAR_MAX_PER_TWEET, file) != NULL )
	{
		nb_tweet++;
	}

	free (tweet);
	fclose (file);

	return nb_tweet;
}

int count_tweets_from_tab (char **tweets, int nb_tweet)
{
	int i, nb_data=0;

	for (i=0; i<nb_tweet; i++)
	{
		if (tweets[i] != NULL)
			nb_data++;
	}

	return nb_data;
}

float ** create_frq_tab (char **tweets, int nb_tweet)
{
	float **frq_tab = init_2d_float_tab (nb_tweet, 256);
	int i;

	for (i=0; i<nb_tweet; i++)
	{
		if (tweets [i] != NULL)
		{
			frq_tab [i] = count_frq_char_normalized (tweets [i]);
		}
		else
		{
			free (frq_tab [i]);
			frq_tab [i] = NULL;
		}
	}

	return frq_tab;
}

float * count_frq_char_normalized (char *string)
{

	float *frq_char = malloc (sizeof (int)*256);
	int i;

	for (i=0; i<256; i++)
	{
		frq_char [i] = '\0';
	}

	for (i=0; i<CHAR_MAX_PER_TWEET; i++)
	{
		if ( string [i] == '\0')
			break;

		frq_char [ (unsigned char) string [i] ]++;
	}

	int nb_char = i;

	for (i=0; i < 256; i++)
	{
		frq_char [i] /= nb_char;
	}

	return frq_char;
}

void removeDouble (char ** tweetTable, int size)
{
	int i, j;
	for (i=0; i < size; i++){

		if (tweetTable [i] == NULL)
			continue;

		for (j=i+1; j < size ;j++){

			if (tweetTable [j] == NULL)
				continue;

			if ( strcmp(tweetTable[i],tweetTable[j]) == 0 )
			{
				free (tweetTable[j]);
				tweetTable[j] = NULL;
			}
		}
	}
}


void removeURL(char ** tweetTable, int size)
{
	int i;

	for (i =0; i < size; i++){

		if (tweetTable[i] != NULL)
		{
			while (str_remove_word (tweetTable[i], "http://"))
			{
			}
		}
	}
}

int str_remove_word (char *text, char *word) 
{
	int id_char=0, i=0;
	char *word_ptr = strstr (text, word);

	if (word_ptr == NULL)
		return 0;

	while (&text [id_char] != word_ptr)
	{
		id_char++;
	}

	while (word_ptr [i] != ' ' && word_ptr [i] != '\0' && word_ptr [i] != '\n')
	{
		i++;
	}

	if (word_ptr [i] == ' ')
	{
		i++;
	}

	while (word_ptr [i] != '\0')
	{	
		text [id_char] = word_ptr [i];

		id_char++;
		i++;
	}

	while (id_char < CHAR_MAX_PER_TWEET)
	{
		text [id_char] = '\0';
		id_char++;
	}

	return 1;
}

void data_to_file (char *file_name, float **frq_tab, int nb_tweet, int nb_data, int nb_input, int nb_output, char *result)
{
	FILE *file = fopen (file_name, "w+");

	fprintf (file, "%d %d %d\n", nb_data, nb_input, nb_output);
	tab_float_to_file (file, frq_tab, nb_tweet, nb_input, result);

	fclose (file);
}

char * lang_to_result (char *lang)
{

	char *result = malloc (sizeof (char)*14);

	if (strcmp (lang, "fr") == 0)
	{
		strcpy (result, "1 0 0 0 0 0 0");
	}
	else if (strcmp (lang, "en") == 0)
	{
		strcpy (result, "0 1 0 0 0 0 0");
	}
	else if (strcmp (lang, "de") == 0)
	{
		strcpy (result, "0 0 1 0 0 0 0");
	}
	else if (strcmp (lang, "es") == 0)
	{
		strcpy (result, "0 0 0 1 0 0 0");
	}
	else if (strcmp (lang, "pt") == 0)
	{
		strcpy (result, "0 0 0 0 1 0 0");
	}
	else if (strcmp (lang, "it") == 0)
	{
		strcpy (result, "0 0 0 0 0 1 0");
	}
	else if (strcmp (lang, "tr") == 0)
	{
		strcpy (result, "0 0 0 0 0 0 1");
	}
	else
	{
		return NULL;
	}

	return result;
}