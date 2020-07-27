#include <stdio.h>

#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

struct FileData {
    char *file_content;
    int file_position;
};

void ignore_spaces(char *input);

void shift_string(char *input, int index);

int search_keyword(char *input, char *keyword);

char *read_line(struct FileData *file_Data);


struct FileData *read_file(char *file_name);

struct LinkedList *get_file_info(struct FileData *file);

#endif