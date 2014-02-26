#include "parser.h"


int main (int argc, char *argv[]) 
{
	if (argc != 5 || strlen (argv [3]) != 2)
	{
		printf ("Please enter correct args\n./parser.exe input_file output_file language charset.txt\n");
		return 0;
	}

	char *result = NULL;

	if ( ( result = lang_to_result (argv [3]) ) == NULL )
	{
		printf ("Wrong language\nPossibilities are : fr, en, es, tr, de, pt, it\n");
		return 0;
	}

	int * charset = getCharset (argv [4]);
	if (charset == NULL)
	{
		printf ("Error in charset.txt\n");
		return 0;
	}
	int i=0;
	while (charset[i] != -1)
		i++;

	int charsetLen = i;


	int nb_tweet = count_tweets_from_file (argv [1]);
	char **tweets = init_2d_char_tab (nb_tweet, CHAR_MAX_PER_TWEET);

	
	file_to_tab (argv[1], tweets, nb_tweet, CHAR_MAX_PER_TWEET);

	removeDouble (tweets, nb_tweet);
	removeURL (tweets, nb_tweet);
	//removeHashTag (tweets, nb_tweet);
	removePseudo (tweets, nb_tweet);
	tweetsToLower (tweets, nb_tweet);	

	//float **frq_tab = create_frq_tab (tweets, nb_tweet);
	int **intTweets = translateCharToInt (tweets, nb_tweet);

	float **frqFirstCharWord = calculFrqFirstCharWord (tweets, nb_tweet);
	float **frqLastCharWord = calculFrqLastCharWord (tweets, nb_tweet);
	float **frq_tab = createIntFrqTab (intTweets, nb_tweet, charset, charsetLen);
	float **hog_tab = create_hog(tweets, nb_tweet);

	//print_2d_string_tab (tweets, nb_tweet);

	int nb_data = count_tweets_from_tab (tweets, nb_tweet);


	tab_floatx3_to_file (argv [2], frq_tab, charsetLen, frqLastCharWord, 26, frqFirstCharWord, 26, nb_tweet, nb_data, result);
	//tab_floatx2_to_file (argv [2], frq_tab, charsetLen, frqLastCharWord, 26, nb_tweet, nb_data, result);
	//tab_floatx2_to_file (argv [2], frq_tab, charsetLen, hog_tab, HOG_SIZE, nb_tweet, nb_data, result);
	//data_to_file (argv [2], frq_tab, nb_tweet, nb_data, charsetLen, NB_OUTPUT, result, charsetLen);
	

	free (charset);
	free (result);
	free_2d_tab ( (void **) tweets, nb_tweet);
	free_2d_tab ( (void **) frq_tab, nb_tweet);
	free_2d_tab ( (void **) hog_tab, nb_tweet);

	return 0;
}

int *getCharset (char *fileName)
{
	FILE *file = fopen (fileName, "r");
	char str [SIZE_MAX_CHARSET];
	unsigned char letter;
	int nb_char, i;

	if (fgets (str, SIZE_MAX_CHARSET, file) == NULL)
		return NULL;

	int strLen = strlen (str);

// When you have an octect between 194 and 197 it's a special char which take 2 octets
	for (i=0, nb_char=0; i < strLen; i++)
	{
		letter = (unsigned char) str [i];
		if ( letter >= 194 && letter <= 197 )
			i++;

		nb_char ++;
	}

	int *charset = malloc (sizeof (int)*(nb_char+1));
	charset [nb_char] = -1;

	for (i=0, nb_char=0; i < strLen; i++, nb_char ++)
	{
		letter = (unsigned char) str [i];
		if ( letter >= 194 && letter <= 197 )
		{
			charset [nb_char] = letter*256 + (unsigned char) str [i+1];
			i++;
		}
		else
		{
			charset [nb_char] = letter;
		}
	}

	return charset;
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

float **  create_hog (char **tweets, int nb_tweet)
{
	float **frq_tab = init_2d_float_tab (nb_tweet, HOG_SIZE);
	int i;

	for (i=0; i<nb_tweet; i++)
	{
		if (tweets [i] != NULL)
		{
			frq_tab [i] = calcul_hog_tweet_normalized (tweets [i]);
		}
		else
		{
			free (frq_tab [i]);
			frq_tab [i] = NULL;
		}
	}

	return frq_tab;
}

float ** calculFrqFirstCharWord (char **tweets, int nb_tweet)
{
	float **frq_tab = init_2d_float_tab (nb_tweet, 26);
	int i;

	for (i=0; i<nb_tweet; i++)
	{
		if (tweets [i] != NULL)
		{
			frq_tab [i] = getFrqFirstCharWordPerLine (tweets [i]);

		}
		else
		{
			free (frq_tab [i]);
			frq_tab [i] = NULL;
		}
	}

	return frq_tab;
}

float *getFrqFirstCharWordPerLine (char *line)
{
	// Just a-z letter
	float *frq = malloc (sizeof (int)*26);
	int i;
	char c, next;

	for (i=0; i < 26; i++)
	{
		frq [i] = 0;
	}

	for (i=0; i < CHAR_MAX_PER_TWEET; i++)
	{
		c = line [i];

		if (c == '\0')
			break;

		if (c == ' ')
		{
			next = line[i+1];
			if (next >= 97 && next <= 122)
				frq [ next-97 ] ++;
		}
	}

	return frq;
}

float ** calculFrqLastCharWord (char **tweets, int nb_tweet)
{
	float **frq_tab = init_2d_float_tab (nb_tweet, 26);
	int i;

	for (i=0; i<nb_tweet; i++)
	{
		if (tweets [i] != NULL)
		{
			frq_tab [i] = getFrqLastCharWordPerLine (tweets [i]);

		}
		else
		{
			free (frq_tab [i]);
			frq_tab [i] = NULL;
		}
	}

	return frq_tab;
}

float *getFrqLastCharWordPerLine (char *line)
{
	// Just a-z letter
	float *frq = malloc (sizeof (int)*26);
	int i;
	char c, prev;

	for (i=0; i < 26; i++)
	{
		frq [i] = 0;
	}

	// The first char doesn't interest us
	for (i=1; i < CHAR_MAX_PER_TWEET; i++)
	{
		c = line [i];

		if (c == '\0')
		{
			prev = line[i-1];
			if (prev >= 97 && prev <= 122)
				frq [ prev-97 ] ++;

			break;
		}

		if (c == ' ')
		{
			prev = line[i-1];
			if (prev >= 97 && prev <= 122)
				frq [ prev-97 ] ++;
		}
	}

	return frq;
}

float ** createIntFrqTab (int **tweets, int nb_tweet, int* charset, int charsetLen)
{
	float **frq_tab = init_2d_float_tab (nb_tweet, charsetLen);
	int i;

	for (i=0; i<nb_tweet; i++)
	{
		if (tweets [i] != NULL)
		{
			frq_tab [i] = countFrqInt (tweets [i], charset, charsetLen);

		}
		else
		{
			free (frq_tab [i]);
			frq_tab [i] = NULL;
		}
	}

	return frq_tab;
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


float * calcul_hog_tweet_normalized (char *string) {

	float * hog = malloc (sizeof (int)*HOG_SIZE);
	int i;

	for (i=0; i<HOG_SIZE; i++)
	{
		hog [i] = 0;
	}
	int diviseur = 256/(HOG_SIZE);
	int diff;
	//float modulo;
	int entiere;
	for (i=0; i<CHAR_MAX_PER_TWEET && string[i] != '\0' ; i++)
	{
		diff = ((unsigned char) string[i+1] )- ((unsigned char) string[i]);
		if (diff < 0 ){
			diff = -diff;
		}
		/*
		Plz choose between 1 or 2 
		*/
		
		/*** 1 ***/
		entiere = diff/diviseur;
		hog[entiere] ++;
		//printf("%d ",entiere);
		
		/**** 2 ***/
		/*
		entiere = diff/diviseur;
		modulo = diff%diviseur - diviseur/2 + 0.5; // valeur between [-3.5 ; 3.5]
		if (modulo < 0 ){
			modulo = -modulo; //value between [0 ;3.5]
		}
		hog[entiere] +=(float) 1 - (float)modulo/(diviseur/2);
		*/
		
		
		//print_hog (hog);
	}

	hog = normalize_hog (hog);
	//hog = centrage(hog, HOG_SIZE);
	return hog;
	

}
float * centrage (float * tab, int size){


	int i;
	float max;
	for (i=0, max = 0; i< size; i++ ){
		if (tab[i] > max ){
			max = tab[i];
		}
	}
	for (i=0; i< size; i++ ){
		tab[i]=((tab[i]/max)*2)-1;
	
	}
	return tab;
}


float *  normalize_hog (float * hog){
	double carre = 0 ; 
	int i;
	for (i=0; i < HOG_SIZE ;i ++ ){
		carre += pow(hog[i], 2);
	}
	carre = sqrt (carre);
	
	for (i=0; i < HOG_SIZE ;i ++ ){
		hog[i] = hog[i]/carre;
	}


	return hog;
}

void print_hog (float * hog){

int i;

for (i=0; i< HOG_SIZE ; i++){

	printf ("%f ",hog[i]);


}
printf ("\n");

}

int getCharsetId (int *charset, int charsetLen, int letter)
{
	int i;

	for (i=0; i<charsetLen; i++)
	{
		if (letter == charset[i])
			return i;
	}

	return -1;
}

float * countFrqInt (int *string, int* charset, int charsetLen)
{

	float *frq_char = malloc (sizeof (int)*charsetLen);
	int i, id;

	for (i=0; i<charsetLen; i++)
	{
		frq_char [i] = 0;
	}

	for (i=0; i<CHAR_MAX_PER_TWEET; i++)
	{
		if ( string [i] == 0)
			break;

		id = getCharsetId (charset, charsetLen, string [i]);

		if (id >= 0)
			frq_char [id]++;
	}

	int nb_char = i;
	
	for (i=0; i < charsetLen; i++)
	{
		frq_char [i] /= nb_char;
		//frq_char [i] = (frq_char [i] * 2) - 1;

	}

	//frq_char = centrage (frq_char,256);
	return frq_char;
}

float * count_frq_char_normalized (char *string)
{

	float *frq_char = malloc (sizeof (int)*256);
	int i;

	for (i=0; i<256; i++)
	{
		frq_char [i] = 0;
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
		//frq_char [i] = (frq_char [i] * 2) - 1;

	}
	//frq_char = centrage (frq_char,256);
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
			while (str_remove_word (tweetTable[i], "http"))
			{
			}
		}
	}
}

void removeHashTag(char ** tweetTable, int size)
{
	int i;

	for (i =0; i < size; i++){

		if (tweetTable[i] != NULL)
		{
			while (str_remove_word (tweetTable[i], "#"))
			{
			}
		}
	}
}

void removePseudo (char ** tweetTable, int size)
{
	int i;

	for (i =0; i < size; i++){

		if (tweetTable[i] != NULL)
		{
			while (str_remove_word (tweetTable[i], "@"))
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

void tweetsToLower (char **tweets, int line)
{
	int i, j;

	for (i=0; i < line; i++)
	{

		if (tweets[i] == NULL)
			continue;

		for (j=0; j < ASCII_SIZE; j++)
		{

			if (tweets [i][j] == '\0')
				break;

			tweets [i][j] = tolower (tweets [i][j]);
		}
	}
}

void data_to_file (char *file_name, float **frq_tab, int nb_tweet, int nb_data, int nb_input, int nb_output, char *result, int lineLen)
{
	FILE *file = fopen (file_name, "w+");

	fprintf (file, "%d %d %d\n", nb_data, nb_input, nb_output);

	tab_float_to_file (file, frq_tab, nb_tweet, lineLen, result);
	

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

int **translateCharToInt (char **tweets, int nb_tweet) {

	int ** tab = init_2d_int_tab (nb_tweet, CHAR_MAX_PER_TWEET);
	int i, j;
	unsigned char letter;

	for (i=0; i < nb_tweet; i++)
	{
		if (tweets [i] == NULL)
		{
			tab [i] = NULL;
			continue;
		}

		for (j=0; j < CHAR_MAX_PER_TWEET; j++)
		{

			if (tweets [i][j] == '\0')
				break;

			letter = (unsigned char)tweets [i][j];

			/*
				First octet is always between 194 and 197 for special char in charset.txt
			*/
			if (letter >= 194 && letter <= 197)
			{
				tab [i][j] = letter*256 + (unsigned char)tweets [i][j+1];
				tab [i][j+1] = -1;
				j++;
			}
			else
			{
				tab [i][j] = letter;
			}
		}
	}

	return tab;
}
