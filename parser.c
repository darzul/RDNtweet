#include "parser.h"

int main (int argc, char *argv[]) 
{
	if (argc != 2)
	{
		printf ("Please indicate the input file");
	}

	int nb_tweet = count_tweets (argv [1]);
	char **tweets = init_2d_char_tab (nb_tweet, CHAR_MAX_PER_TWEET);

	file_to_tab (argv[1], tweets, nb_tweet, CHAR_MAX_PER_TWEET);

	//removeDouble (tweets, nb_tweet);
	removeURL (tweets, nb_tweet);
printf ("LOL\n");
	print_2d_string_tab (tweets, nb_tweet);

	return 0;
}

int count_tweets (char *file_name)
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

int * count_frq_char (char *phrase)
{
	printf ("%s", phrase);

	int *frq_char = malloc (sizeof (int)*256);
	int i;

	for (i=0; i<256; i++)
	{
		frq_char [i] = '\0';
	}

	for (i=0; i<CHAR_MAX_PER_TWEET; i++)
	{
		if ( phrase [i] == '\0')
			break;

		printf ("%d\t=>\t%c\n", (unsigned char) phrase [i], phrase [i]);

		frq_char [ (unsigned char) phrase [i] ]++;
	}

	printf ("Length:\t%d\n", i-1);


	return frq_char;
}
