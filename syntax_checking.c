#include "syntax_checking.h"
#include "file_handling.h"
#include "map_handling.h"
#include "token2.h"
#include <string.h>
#include <ctype.h>

int check_syntax(struct FileData *file_data){
    char *curr_line,*keyword;
    while ((curr_line = read_line(file_data)) != NULL){
        ignore_spaces(curr_line);
        if (strchr(curr_line,'=') == NULL){
            return 0;
        }
        keyword = strtok(curr_line,"=");
        if (get_token_type(keyword) == -1){
            return 0;
        }
    }
    return 1;
}
