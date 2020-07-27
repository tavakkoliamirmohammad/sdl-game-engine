#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#include "token2.h"
#include "file_handling.h"
#include "linked_list.h"

#define KEYSZIE 100
#define TOKEN_NUM 18

char keywords[TOKEN_NUM][KEYSZIE] = {"solidblock", "deathblock", "moveblock", "rpoint", "wall", "up", "down", "right",
                                     "left", "character", "time", "target", "object", "opp", "attack", "put",
                                     "raindb", "Exit"};

int parameters_count[TOKEN_NUM] = {1,1,1,3,1,1,1,1,1,1,1,1,1,1,1,3,1,1};

#include <string.h>
#include <stdio.h>


struct TokenVector *get_line_info(char *line) {
    ignore_spaces(line);
    struct TokenVector *token_vector = (struct TokenVector *) malloc(sizeof(struct TokenVector));
    char *item;
    item = strtok(line, "=");
    // check if item is item is present in token array;
    token_vector->type = get_token_type(item);
    token_vector->info = NULL;
    while (item != NULL) {
        item = strtok(NULL, ",");
        if (item != NULL) {
            token_vector->info = add_last_LL(token_vector->info, item, (strlen(item) + 1) * sizeof(char));
        }
    }
    return token_vector;
}

int extract_num(char *input, int index) {
    int res;
    res = 0;
    while (isdigit(input[index])) {
        res = res * 10 + (input[index] - '0');
        ++index;
    }
    return res;
}

int get_token_type(char *keyword) {
    int i;
    for (i = 0; i < TOKEN_NUM; ++i) {
        if (strcmp(keyword, keywords[i]) == 0) {
            return i;
        }
    }
    return -1;
}


void print_token_vector(struct TokenVector *token_vector) {
    int index, str_index;
    printf("token type: %s ", keywords[token_vector->type]);
    int vector_len;
    vector_len = len(token_vector->info);
    for (index = 0; index < vector_len; ++index) {
        printf("%s ", (char *) get_data(token_vector->info, index));
    }
    printf(" len: %d\n", vector_len);

}

struct TokenVector *init_vector_pointer(void) {
    struct TokenVector *vector_pointer = (struct TokenVector *) malloc(sizeof(struct TokenVector));
    return vector_pointer;
}


int getmin(int a, int b) {
    return a < b ? a : b;
}

int get_keyword_parameters(char *keyword){
    int index;
    for (index = 0;index < TOKEN_NUM;++index){
        if (strcmp(keyword,keywords[index]) == 0){
            return parameters_count[index];
        }
    }
    return -1;

};