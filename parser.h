#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"

#define CHAR_MAX_PER_TWEET 200
#define NB_INPUT 256
#define NB_OUTPUT 7

float ** create_frq_tab (char **tweets, int nb_tweet);
float * count_frq_char_normalized (char *string);

int count_tweets_from_file (char *file_name);
int count_tweets_from_tab (char **tweets, int nb_tweet);

void removeDouble (char ** tweetTable, int size);
void removeURL(char ** tweetTable, int size);
int str_remove_word (char *text, char *word);

char * lang_to_result (char *lang);
void data_to_file (char *file_name, float **frq_tab, int nb_tweet, int nb_data, int nb_input, int nb_output, char *result);
