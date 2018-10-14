#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"
#include "reader.h"

buffer read_file(FILE* file) {
    fseek(file, 0, SEEK_END);
    size_t size = (size_t)ftell(file);
    fseek(file, 0, SEEK_SET);

    void* contents = malloc(size);
    fread(contents, size, 1, file);
    fclose(file);

    buffer file_buffer = {size, contents};

    return file_buffer;
}
