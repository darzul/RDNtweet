#include "fonction.h"

void removeDouble (char ** tweetTable, int size)
{
	int i, j;
	for (i=0; i < size; i++){

		if (tweetTable [i] == NULL)
			continue;

		for (j=i+1; j < size ;j++){

			if (tweetTable [j] == NULL)
				continue;

			if ( strcmp(tweetTable[i],tweetTable[j]) == 0 ){
				tweetTable[j] = NULL;
			}
		}
	}
}


void removeURL(char ** tweetTable, int size)
{
	int i, j, length;
	char * pch, *pch2, *save;

	for (i =0; i < size; i++){

		if (tweetTable[i] != NULL)
		{
			pch = strstr (tweetTable[i],"http://");

			if (pch == NULL)
				continue;

			j = 0;
			while (j < 200 && pch [j] != ' ' && pch [j] != '\0' && pch [j] != '\n')
			{
				pch [j] = ' ';
				j++;
			}
		}
	}
}
