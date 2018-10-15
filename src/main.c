#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "reader.h"

int run_repl();
char* read_line();
int should_continue(char* given_value);
int run_on_file(char* file_name);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        run_repl();
        return 1;
    }
    return run_on_file(argv[1]);
}

int run_repl() {
    char* line = read_line();
    while(should_continue(line)) {
        printf("Processing line: %s\n", line);
        free(line);
        line = read_line();
    }
  
    free(line);
    return 0; 
}

char* read_line() {
    char* line = NULL;
    size_t max = 0;
    size_t size = getline(&line, &max, stdin);
    line[strcspn(line, "\n")] = 0;
    return line;
 
}

int should_continue(char* given_value) {
    return strcmp("exit", given_value);
}

int run_on_file(char* file_name) {
    FILE* file = fopen(file_name, "r");
    if (!file) {
        printf("File not found.");
        return -1;
    }
    
    buffer file_buffer = read_file(file);
    printf("%s", file_buffer.data);
    free(file_buffer.data);
    return 0;
}
