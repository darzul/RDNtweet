#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int * count_chars (char *string);

int main (int argc, char *argv[]) 
{
	if (argc != 2)
	{
		printf ("Please indicate input file");
	}

	FILE *in_file = fopen (argv[1], "r+");

	char *phrase = malloc (sizeof (char)*141);

	while ( fgets (phrase, 141, in_file) != NULL )
	{
		count_chars (phrase);
	}

	return 0;
}

int * count_chars (char *phrase)
{
	printf ("%s", phrase);

	int *frq_char = malloc (sizeof (int)*257);
	int i;

	for (i=0; i<256; i++)
	{
		frq_char [i] = '\0';
	}

	for (i=0; i<141; i++)
	{
		if ( phrase [i] == '\0')
			break;

		printf ("%d\t=>\t%c\n", (unsigned char) phrase [i], phrase [i]);

		frq_char [ (unsigned char) phrase [i] ]++;
	}

	printf ("Length:\t%d\n", i-1);


	return frq_char;
}
