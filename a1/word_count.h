/* Bhavanvir Rai
 * V00938954
 */

#ifndef A1_H
#define A1_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define FILE_NOT_FOUND  1
#define BAD_ARGS        2
#define MAX_FILESIZE    5000
#define MAX_WORD_CNT    750
#define MAX_WORD_LEN    35 //Supercalifragilisticexpialidocious
#define TRUE 1
#define FALSE 0

/* 
 * Debugging print function that can has the same 
 * format as `printf`.  If `-D DEBUG` is passed to
 * the compiler then the print code is compiled, 
 * otherwise, it's an empty function.
 *
 */
void debug(const char* format, ... );
void debug(const char* format, ... ) {
#ifdef DEBUG 
	va_list args;
	
	fprintf(stdout, "  -->  ");
	va_start(args, format);
	vfprintf(stdout, format, args);
	va_end(args);

	fprintf(stdout, "\n");
	fflush(stdout);
#endif	
}

typedef struct word_t
{
    //TODO
    int num_words;
    int length;
    char histogram[MAX_WORD_CNT][MAX_WORD_LEN];
    
} word_t;

size_t read_file(char* filepath, char* buffer);
int tokenize_string(char* buffer, size_t bytes, word_t* freq);
void print_histogram(word_t* buckets, int print_words);
double print_median(word_t* bucket, int number_of_buckets);
void initialize(word_t* bucket);

int by_freq( const void* a, const void* b);
int by_len( const void* a, const void* b);
int by_alphanum( const void* a, const void* b);

int
tokenize_string(char *buffer, size_t bytes, word_t* bucket) {
    /* char* buffer: Input string to tokenize
     * size_t bytes: size of buffer in bytes
     * word_t* bucket: pointer to struct word array that holds the word histogram
     *
     * Function tokenizes the buffer and update the appropriate word_t buckets 
     *
     * Returns: number of buckets 
     */
    int num_words = 0;
    char delimiters[] = " .,;()\n\t";
    char *t;
    t = strtok(buffer, delimiters);
    
    while(t && num_words < MAX_WORD_CNT){
        strncpy(bucket->histogram[num_words], t, MAX_WORD_LEN);
        num_words++;
        t = strtok(NULL, delimiters);
    }
    
    return num_words;
}

void
print_histogram(word_t* bucket,  int print_words)
{
    /* word_t* bucket: pointer to struct word array that holds the word histogram
     * print_words: flag to print words (Part C) or not
     *
     * Function prints out the word histogram 
     */
    while(print_words < MAX_WORD_LEN){
        if(bucket[print_words].num_words != 0)
            printf("Count[%.2d]=%.2d;\n", bucket[print_words].length, bucket[print_words].num_words);
        print_words++;
    }
}

double
print_median(word_t* bucket, int number_of_buckets){
    /* word_t* bucket: pointer to struct word array that holds the word histogram
     * int number_of_buckets: Number of buckets (unique word lengths) 
     *
     * Function prints out the word length median value 
     */
    int buffer[MAX_WORD_LEN];
    for(int i = 0; i < MAX_WORD_LEN; i++){
        if(bucket[i].num_words != 0){
            buffer[number_of_buckets] = bucket[i].length;
            number_of_buckets++;
        }
    }
    
    if(number_of_buckets == 1)
        return buffer[number_of_buckets - 1];
    else if(number_of_buckets % 2 != 0)
        return buffer[number_of_buckets / 2];
    
    int left_middle = buffer[number_of_buckets / 2];
    int right_middle = buffer[(number_of_buckets / 2) - 1];

    double sum = (double)(left_middle + right_middle) / 2;
    return sum;
}


void 
initialize(word_t* bucket){
    /* Initialize the number of words in the bucket to 0, and the length
     * of each word to be dependent on the current index value 'i'
     */ 
    for(int i = 0; i < MAX_WORD_LEN; i++){
        bucket[i].num_words = 0;
        bucket[i].length = i;
    }
}

size_t
read_file(char* filepath, char* buffer) {
    /* char* filepath: path to the input word file (i.e. t01.txt) 
     * char* buffer: buffer to save the contents of the file to 
     *
     * Function that reads the contents of a file into the array buffer
     *
     * Returns: the size of the array in bytes 
     */
    FILE *fp = fopen(filepath, "r");
    
    if(fp == NULL){
        printf("unable to open '%s' for reading\n", filepath);
        return -1;
    }    

    int i = 0;
    for(int ch = fgetc(fp); ch != EOF; ch = fgetc(fp)){
        buffer[i++] = ch;
    }    
    buffer[i] = '\0';
    fclose(fp);

    return sizeof(buffer);
}

/* Functions to be used by `qsort`
 *
 * These functions should sort by these rules:
 *      a left of b   return positive value
 *      a equals b    return 0
 *      b right of a  return negative value
 *
 * In you function, you need to cast your pointer
 * to the correct pointer type:
 *     
 *     const char *ai = (const char*) a;  
 */

int by_freq( const void* a, const void* b)
{
    //Sort by word count/frequency (--sort flag)
    //In the case of a tie, sort by word length
    const word_t* ai = a;
    const word_t* bi = b;

    if(ai->num_words < bi->num_words)
        return 1;
    else if(bi->num_words < ai->num_words)
        return -1;
    return by_len(a, b);
}

int by_len( const void* a, const void* b)
{
    //Sort by word length
    const word_t* ai = a;
    const word_t* bi = b;

    if(ai->num_words < bi->num_words)
        return -1;
    else if(bi->num_words < ai->num_words)
        return 1;
    return 0;
}

int by_alphanum( const void* a, const void* b)
{
    //Sort alphaphetically
    //Remember that upper should come before lowercase
    return 0;
}


#endif
