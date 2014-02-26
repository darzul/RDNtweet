#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "array.h"

#define SIZE_MAX_CHARSET 100
#define CHAR_MAX_PER_TWEET 200
#define NB_OUTPUT 7

static int ASCII_SIZE = 256;
static int HOG_SIZE = 128;//only mutiple of 2 and <= 256 more it is better it is

int *getCharset (char *fileName);

float * normalize (float * tab, int size);
float **  create_hog (char **tweets, int nb_tweet);
void print_hog (float * hog);
float *  normalize_hog (float * hog);
float * calcul_hog_tweet_normalized (char *string);

float ** create_frq_tab (char **tweets, int nb_tweet);
float * count_frq_char_normalized (char *string);

float ** calculFrqFirstCharWord (char **tweets, int nb_tweet);
float *getFrqFirstCharWordPerLine (char *line);
float ** calculFrqLastCharWord (char **tweets, int nb_tweet);
float *getFrqLastCharWordPerLine (char *line);

float ** createIntFrqTab (int **tweets, int nb_tweet, int* charset, int charsetLen);
float * countFrqInt (int *string, int* charset, int charsetLen);
void charsetFilter (int **tab, int size, int *charset, int charsetLen);
int getCharsetId (int *charset, int charsetLen, int letter);

int count_tweets_from_file (char *file_name);
int count_tweets_from_tab (char **tweets, int nb_tweet);

void removeDouble (char ** tweetTable, int size);
void removeURL(char ** tweetTable, int size);
void removeHashTag(char ** tweetTable, int size);
void removePseudo (char ** tweetTable, int size);
int str_remove_word (char *text, char *word);
void tweetsToLower (char **tweets, int line);
int **translateCharToInt (char **tweets, int nb_tweet);

char * lang_to_result (char *lang);
void data_to_file (char *file_name, float **frq_tab, int nb_tweet, int nb_data, int nb_input, int nb_output, char *result, int lineLen);
