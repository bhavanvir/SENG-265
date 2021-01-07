#include "word_count.h"

int
main(int argc, char *argv[]) {    
    if(argc < 3 || argc > 4){
       fprintf(stderr, "program: missing '--infile <filename> [--sort]'\n");
       exit(1);
    }
   
    int sort_flag = 0;   
    char *filename = "";
    for(int i = 0; i < argc; i++){
      if(strcmp(argv[i], "--infile") != 0 && strcmp(argv[i], "--sort") != 0 && i != 0)
          filename = argv[i];
      else if(strcmp(argv[i], "--sort") == 0)
          sort_flag = 1;
    }
    
    FILE *fp = fopen(filename, "r");
   
    if(fp == NULL){ 
        fprintf(stderr, "Unable to open --infile <%s>", filename);
        exit(2);
    }
        
    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    if(size == 0) return 0;

    rewind(fp);

    char *buffer = (char *)malloc(size);
    if(buffer == NULL) alloc_fail();

    if(fread(buffer, sizeof(char), size, fp) != size){
        fprintf(stderr, "Unable to open --infile <%s>", filename);
        exit(2);
    }
    buffer[size-1] = '\0';
    fclose(fp);

    if(argc == 3 || sort_flag == 1){
        int num_words = 0;
        char **tokenized = tokenize_str(buffer, &num_words);
        if(num_words == 0) return 0;        

        qsort(tokenized, num_words, sizeof(char *), by_len);
          
        histogram_t *list = NULL;
        histogram_t *list_cpy = NULL;
        histogram_t *list_rm = NULL;
        for(int i = 0; i < num_words; i++){
            list = add_end(list, new_node(tokenized[i], 0, 0));
            list_rm = add_inorder(list_rm, new_node(tokenized[i], 0, 0), sort_flag);
            list_cpy = list;
        }
        remove_duplicates(list_rm);

        int largest = largest_word(list) + 1;

        int *count = (int *)calloc(largest, sizeof(int));
        if(count == NULL) alloc_fail();
        while(list != NULL){
            count[strlen(list->word)]++;
            list = list->next;
        }
        list = list_cpy;
        
        for(int i = 0; i < largest; i++){
            if(count[i] != 0){
                list->freq = count[i];
                list->len = i;
                list = list->next;
            }
        }
        list = list_cpy;
        
        while(list != NULL){
            if(list->len != 0 && list->freq != 0){
                printf("Count[%.2d]=%.2d;", list->len, list->freq);
                print_histo(list_rm, list->len, search_for(list_rm, list->len));
            }
            list = list->next;
        }
           
        free_list(list);
        free_list(list_rm);
        free_list(list_cpy);
        free(buffer);
        free(count);
        free(tokenized);  
        
    }    
    return 0;    
}


