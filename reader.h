#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

#define MAX_LINE_LENGTH 512

typedef enum {
    TOK_NUM,
    TOK_ADD,
    TOK_MULT,
    TOK_SUB,
    TOK_DIV
} TokenType;

struct Token {
    int val; //undefined if not TOK_NUM.
    TokenType tok_type;
    struct Token* next; //next token on the stack
};

struct Reader {
    struct Token* token; //the current token
    char* save_ptr; //the pointer to the next token to be read
    bool had_error; //set to true if the calculator can not return an answer.
};

char* init_reader(struct Reader* reader, char* filename);
bool advance(struct Reader* reader);
