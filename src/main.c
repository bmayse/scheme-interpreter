#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "reader.h"

int run_repl();
void fetch_next_line_into_buffer(buffer* input);
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
    buffer input_buffer;
    input_buffer.size = SIZE_MAX;
    input_buffer.data = malloc(SIZE_MAX);
    fetch_next_line_into_buffer(&input_buffer);
    while(should_continue(input_buffer.data)) {
        printf("Processing line: %s\n", input_buffer.data);
        fetch_next_line_into_buffer(&input_buffer);
    }
    
    free(input_buffer.data);
    return 0; 
}

void fetch_next_line_into_buffer(buffer* input) {
    getline((char**)&input->data, &input->size, stdin);
    char* data = input->data;
    data[strcspn(data, "\n")] = 0;
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
