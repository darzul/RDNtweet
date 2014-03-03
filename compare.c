#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int getIdByLang (char *lang);

int main (int argc, char *argv[])
{
	if (argc != 3)
	{
		printf ("./exe predictFile.txt resultFile.txt out.txt");
		return 0;
	}

	FILE *predictFile = fopen (argv[1], "r");
	FILE *resultFile = fopen (argv[2], "r");
	
	char *result = malloc (sizeof (char)*10);
	char *predict = malloc (sizeof (char)*10);

	while ( fgets (result, 3, resultFile) != NULL && fgets (predict, 3, predictFile) != NULL )
	{
//printf ("%s %s\n", predict, result);
		if (getIdByLang (result) > 0)
			printf ("P %d R %d\n", getIdByLang (predict), getIdByLang (result));
	}

	free (predict);
	free (result);
	fclose (predictFile);
	fclose (resultFile);

	return 0;
}

int getIdByLang (char *lang)
{
	if (strcmp (lang, "fr") == 0)
	{
		return 0;
	}
	else if (strcmp (lang, "en") == 0)
	{
		return 1;
	}
	else if (strcmp (lang, "de") == 0)
	{
		return 2;
	}
	else if (strcmp (lang, "es") == 0)
	{
		return 3;
	}
	else if (strcmp (lang, "pt") == 0)
	{
		return 4;
	}
	else if (strcmp (lang, "it") == 0)
	{
		return 5;
	}
	else if (strcmp (lang, "tr") == 0)
	{
		return 6;
	}
	else
	{
		return -1;
	}

}
