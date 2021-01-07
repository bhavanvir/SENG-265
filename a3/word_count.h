#include <assert.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef struct histogram_t{
    char *word;
    int freq;
    int len;
    struct histogram_t *next;
} histogram_t;

void alloc_fail(void){
    fprintf(stderr, "Unable to allocate memory");
    exit(3);
}

void free_list(histogram_t *list){
    histogram_t *tmp;

    while(list != NULL){
        tmp = list;
        list = list->next;
        free(tmp);
    }
}

char ** tokenize_str(char *buffer, int *num_words){
    size_t init_size = 50;
    char *t;
    t = strtok(buffer, " .,;()\n\t");

    char **word_arr = (char **)malloc(init_size * sizeof(char *));
    if(word_arr == NULL) alloc_fail();

    int i = 0;
    while(t != NULL){
        if(i >= init_size){
            init_size *= 2;
            char** tmp = (char **)realloc(word_arr, init_size * sizeof(char *));
            if(tmp == NULL) alloc_fail();
            word_arr = tmp;
        }

        word_arr[i] = t;
    
        i++;
        *num_words += 1;
        t = strtok(NULL, " .,;()\n\t");
        
    } 
    word_arr[i] = '\0';
    
    return word_arr;
}

int by_len(const void *a, const void *b){
    const char **ai = (const char **) a;
    const char **bi = (const char **) b;
    
    if(strlen(*ai) >= strlen(*bi))
        return 1;
    else
        return -1;
}

histogram_t *new_node(char *new_val, int len, int freq){
    assert(new_val != NULL);

    histogram_t *tmp = (histogram_t *)malloc(sizeof(histogram_t));
    if(tmp == NULL) alloc_fail();

    tmp->word = new_val;
    tmp->len = len;
    tmp->freq = freq;
    tmp->next = NULL;
    return tmp;
}

histogram_t *add_end(histogram_t *list, histogram_t *new_val){
    histogram_t *curr;

    if(list == NULL){
        new_val->next = NULL;
        return new_val;
    }
    
    for(curr = list; curr->next != NULL; curr = curr->next);
    curr->next = new_val;
    new_val->next = NULL;
    return list;
}

histogram_t *add_inorder(histogram_t *list, histogram_t *new_val, int sort_flag){
    histogram_t *prev = NULL;
    histogram_t *curr = NULL;

    if(list == NULL)
        return new_val;

    for(curr = list; curr != NULL; curr = curr->next){
        if(strcmp(new_val->word, curr->word) > 0 && sort_flag == 0)
            prev = curr;
        else if(strcmp(new_val->word, curr->word) < 0 && sort_flag == 1)
            prev = curr;
        else
            break;
    }
    
    new_val->next = curr;
    if(prev == NULL)
        return new_val;
    else{
        prev->next = new_val;
        return list;
    }    
}

void remove_duplicates(histogram_t *list){
    histogram_t *curr = list;
    histogram_t *next_next;

    if(curr == NULL)
        return;

    while(curr->next != NULL){
        if(strcmp(curr->word, curr->next->word) == 0){
            next_next = curr->next->next;
            free(curr->next);
            curr->next = next_next;
        }else
            curr = curr->next;
    }
}

void print_histo(histogram_t *new_list, int length, int num_occur){
    histogram_t *curr = new_list;
    int count = 0;
    for(curr = new_list; curr != NULL; curr = curr->next){
        if(strlen(curr->word) == length){
            if(num_occur == 1){
                printf(" (words: \"%s\")\n", curr->word);
            }else{
                if(num_occur - count == num_occur){
                    printf(" (words: \"%s\"", curr->word);
                    count++;
                }else if(num_occur - count == 1){
                    printf(" and \"%s\")\n", curr->word);
                    count++;
                }else{
                    printf(", \"%s\"", curr->word);
                    count++;
                }
            }
        }if(count == num_occur)
            return;
    }

}

int search_for(histogram_t *new_list, int length){
    histogram_t *curr = new_list;
    int count = 0;

    while(curr != NULL){
        if(strlen(curr->word) == length)
            count++;
        curr = curr->next;
    }
    return count;
}

int largest_word(histogram_t *list){
    histogram_t *curr = list;
    int max = strlen(curr->word);

    while(curr != NULL){
        if(max < strlen(curr->word))
            max = strlen(curr->word);
        curr = curr->next;
    }
    return max;
}
