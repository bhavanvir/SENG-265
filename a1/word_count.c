#include "word_count.h" 

int
real_main(int argc, char *argv[]) {
    //TODO
    
    //variable declarations    
    char buffer[MAX_FILESIZE + 1] = {0}; 
    size_t bytes = 0;
    word_t count[MAX_WORD_LEN] = {0};
    initialize(count);
    word_t input_line = {0}; 
   
    //parsing stdin to see how many arguments are entered 
    if(argc < 3){
        printf("program: missing '--infile <filename> [--sort] [--print-words]'\n");
        return 0;
    }else if(argc == 3){
        //read the file at the 3rd index of stdin
        bytes = read_file(argv[2], buffer);
        
        //tokenize the file
        input_line.num_words = tokenize_string(buffer, bytes, &input_line);

        //increment the num_words counter at the index that corresponds to the strlen of input_line, for count
        int i = 0;
        while(*input_line.histogram[i] != '\0'){
            count[strlen(input_line.histogram[i])].num_words++;
            i++;
        }
        
        //print the frequency
        print_histogram(count, 0);
    }else if(argc == 4){
        int sort_flag = 0;
   
        //looping through the arguments to see if --sort is included, and at which index <filename> is
        for(int i = 0; i < argc; i++){
            //if the current index is not 0, and is not any of the below flags, it must be the <filename>
            if(strcmp(argv[i], "--infile") != 0 && strcmp(argv[i], "--sort") != 0 && i != 0)
                bytes = read_file(argv[i], buffer);
            //if --sort has been found, then set the corresponding flag to be true
            else if(strcmp(argv[i], "--sort") == 0)
                sort_flag = 1;
        }        

        input_line.num_words = tokenize_string(buffer, bytes, &input_line);

        int i = 0;
        while(*input_line.histogram[i] != '\0'){
            count[strlen(input_line.histogram[i])].num_words++;
            i++;
        }
        
        //if the sort flag is true, and the <filename> actually exists, then calculate the median and print the sorted frequency
        if(sort_flag == 1 && bytes != -1){
            double median = print_median(count, 0);       
        
            qsort(count, MAX_WORD_LEN, sizeof(word_t), by_freq);
        
            print_histogram(count, 0);
       
            printf("Median word length: %.1f\n", median);
        }
    }else if(argc == 5){
       //looping through the arguments to see if --sort and --print-words are included, at at which index <filename> is
       for(int i = 0; i < argc; i++){
           if(strcmp(argv[i], "--infile") != 0 && strcmp(argv[i], "--sort") != 0 && strcmp(argv[i], "--print-words") != 0 && i != 0)
               bytes = read_file(argv[i], buffer); 
       } 
    }else if(argc > 5){
        printf("program: missing '--infile <filename> [--sort] [--print-words]'\n");
        return 0;
    }

    return 0;
}



#ifndef TEST
int
main(int argc, char *argv[]) {
    return real_main(argc, argv);
}
#endif
