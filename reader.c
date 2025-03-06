#include "stdio.h"
#include "stdlib.h"
#include "reader.h"
#include <string.h>

static bool token_from_str(struct Token **token, char *str);

/**
 *
 * @param reader the Reader to be initialized. The first token will be stored in reader and a save pointer
 *              to the next token in the file.
 * @param filename the name of the file to open and read from.
 * @return a pointer to the deep copied line from the file.
 */
char *init_reader(struct Reader *reader, char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("no file\n");
        return NULL;
    }
    char *line = malloc(MAX_LINE_LENGTH);
    fgets(line, MAX_LINE_LENGTH, file);
    fclose(file);
    struct Token *first_token = calloc(1, sizeof(struct Token));
    if (!first_token) {
        return NULL;
    }
    char *token_str = strtok_r(line, " ", &reader->save_ptr);
    if (!token_str) {
        printf("no text\n");
        return NULL;
    }
    token_from_str(&first_token, token_str);
    reader->token = first_token;
    return line;
}

/**
 * Advances the reader to the next token
 * @param reader the reader to be advanced. Reader should have the save pointer of the last strtok_r.
 * @return true if the next token was parsed successfully, false if otherwise.
 */
bool advance(struct Reader *reader) {
    struct Token *token = calloc(1, sizeof(struct Token));
    if (!token) {
        reader->token = NULL;
        return false;
    }
    char *token_str = strtok_r(NULL, " ", &reader->save_ptr);
    if (!token_str) {
        free(token);
        reader->token = NULL;
        return false;
    }
    token_from_str(&token, token_str);
    reader->token = token;
    return true;
}

/**
 * Parses a string into its proper token
 * @param token a pointer to the resultant token
 * @param token_str the string to be transformed
 * @return true if the string could be converted to a token, false if otherwise
 */
static bool token_from_str(struct Token **token, char *token_str) {
    if (strlen(token_str) == 1) {
        switch (token_str[0]) {
            case '+':
                (*token)->tok_type = TOK_ADD;
                break;
            case '-':
                (*token)->tok_type = TOK_SUB;
                break;
            case '*':
                (*token)->tok_type = TOK_MULT;
                break;
            case '/':
                (*token)->tok_type = TOK_DIV;
                break;
            default:
                (*token)->tok_type = TOK_NUM;
                (*token)->val = atoi(token_str);
                break;
        }
    } else {
        (*token)->tok_type = TOK_NUM;
        (*token)->val = atoi(token_str);
    }
    return true;
}