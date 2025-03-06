#include "stdlib.h"
#include "reader.h"

static void free_token(struct Token** tok);

int calculate_result(struct Reader *reader) {
    struct Token *head = NULL;
    // create a linkedlist based stack of tokens.
    // pop when a operator is encountered and add the result to the stack
    while (reader->token != NULL) {
        reader->token->next = head;
        head = reader->token;
        if (head->tok_type != TOK_NUM) {
            // this is an operation:
            struct Token *op = head;
            struct Token *val_a = head->next;
            if (!val_a) {
                reader->had_error = true;
                return -1;
            }
            struct Token *val_b = head->next->next;
            if (!val_b) {
                reader->had_error = true;
                return -1;
            }
            int new_val = 0;
            switch (op->tok_type) {
                case TOK_ADD:
                    new_val = val_a->val + val_b->val;
                    break;
                case TOK_DIV:
                    if (val_a->val != 0)
                        new_val = val_b->val / val_a->val;
                    else {
                        reader->had_error = true;
                        return -1;
                    }
                    break;
                case TOK_MULT:
                    new_val = val_a->val * val_b->val;
                    break;
                case TOK_SUB:
                    new_val = val_b->val - val_a->val;
                    break;
                default:
                    return -1;
            }
            free_token(&val_b);
            free_token(&val_a);
            free_token(&op);
            struct Token *new_token = malloc(sizeof(struct Token));
            new_token->next = val_b->next;
            new_token->tok_type = TOK_NUM;
            new_token->val = new_val;

            head = new_token;
        }
        advance(reader);
    }
    if (head != NULL && !head->next) {
        return head->val;
    } else {
        reader->had_error = true;
        return -1;
    }
}

void free_token(struct Token** tok) {
    free(*tok);
    *tok = NULL;
}