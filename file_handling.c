#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "file_handling.h"
#include "utils.h"
#include "token2.h"
#define FILESIZE 100


void ignore_spaces(char *input) {
    int index;
    for (index = 0; index < strlen(input); ++index) {
        if (isspace(input[index])) {
            shift_string(input, index + 1);
            --index;
        }
    }

}

void shift_string(char *input, int index) {
    int i;
    for (i = index; i <= strlen(input); ++i) {
        input[i - 1] = input[i];
    }
}

int search_keyword(char *input, char *keyword) {
    int input_index, keyword_index, copy_index;
    input_index = keyword_index = copy_index = 0;
    if (strlen(input) < strlen(keyword)) {
        return -1;
    }
    for (input_index = 0; input_index <= strlen(input) - strlen(keyword); ++input_index) {
        copy_index = input_index;
        while (input[input_index] == keyword[keyword_index]) {
            ++keyword_index;
            ++input_index;
        }
        if (keyword_index >= strlen(keyword)) {
            return input_index - 1;
        }
        else {
            input_index = copy_index;
            keyword_index = 0;
        }
    }
    return -1;
}

struct FileData *read_file(char *file_name) { // copying contents of a file into an array
    //file_content = (char *)malloc(sizeof(char) * FILESIZE);
    FILE *fp = NULL;
    fp = fopen(file_name,"r");
    if(fp ==  NULL){
        return NULL;
    }

    struct FileData *file_data = (struct FileData *)malloc(sizeof(struct FileData));
    int content, index, new_size;
    index = 0;
    file_data -> file_position = 0;
    new_size = FILESIZE;
    file_data -> file_content = (char *) malloc(sizeof(char) * new_size);
    while ((content = getc(fp)) != EOF) {
        if (index == new_size) {
            file_data -> file_content = (char *) my_realloc(file_data -> file_content, (new_size + 1000) * sizeof(char));
            new_size += 1000;
        }
        (file_data -> file_content)[index] = content;
        ++index;
    }
    (file_data -> file_content)[index] = '\0';
    fclose(fp);
    return file_data;
}

char *read_line(struct FileData *file_data) {
    int size;
    size = 1;
    char *line = NULL;
    if (file_data -> file_position >= strlen(file_data -> file_content)) {
        return NULL;
    }
    line = (char *) malloc(sizeof(char));
    while ((file_data -> file_content)[file_data -> file_position] != '\n' && (file_data -> file_content)[file_data -> file_position] != '\0') {
        line = (char *) my_realloc(line, size * sizeof(char));
        line[size - 1] = (file_data -> file_content)[file_data -> file_position];
        ++size;
        ++(file_data -> file_position);
    }
    ++(file_data -> file_position);
    if (line != NULL) {
        line = (char *) my_realloc(line, size * sizeof(char));
        line[size - 1] = '\0';
    }
    return line;
}

struct LinkedList *get_file_info(struct FileData *file) {
    int size;
    size = 1;
    char *line;
    struct LinkedList *file_data = NULL;
    int index;
    index = 0;
    for (index = 0; (line = read_line(file)); ++index) {
        struct TokenVector *token_vector;
        token_vector = get_line_info(line);
        file_data = add_last_LL(file_data, token_vector, sizeof(struct TokenVector));
    }
    return file_data;
}