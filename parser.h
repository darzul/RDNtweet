#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#include "array.h"

#define CHAR_MAX_PER_TWEET 200
#define NB_OUTPUT 7

static int ASCII_SIZE = 256;
static int HOG_SIZE = 64;


float * centrage (float * tab, int size);
float **  create_hog (char **tweets, int nb_tweet);
void print_hog (float * hog);
float *  normalize_hog (float * hog);
float * calcul_hog_tweet_normalized (char *string);

float ** create_frq_tab (char **tweets, int nb_tweet);
float * count_frq_char_normalized (char *string);

int count_tweets_from_file (char *file_name);
int count_tweets_from_tab (char **tweets, int nb_tweet);

void removeDouble (char ** tweetTable, int size);
void removeURL(char ** tweetTable, int size);
void removeHashTag(char ** tweetTable, int size);
void removePseudo (char ** tweetTable, int size);
int str_remove_word (char *text, char *word);
void tweetsToLower (char **tweets, int line);

char * lang_to_result (char *lang);
void data_to_file (char *file_name, float **frq_tab, int nb_tweet, int nb_data, int nb_input, int nb_output, char *result);
