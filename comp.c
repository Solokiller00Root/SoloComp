#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_END,
    TOKEN_UNKNOWN
} TOKEN_TYPE;

typedef struct {
    TOKEN_TYPE type;
    int value;  // Used only for TOKEN_NUMBER
} TOKEN;

TOKEN currentToken;

TOKEN_TYPE lex(unsigned char **_src, TOKEN *num) {
    unsigned char *src = *_src;
    int i;
    while (1) {
        switch (*src) {
            case 0:
            case ';':
                *_src = src;
                return TOKEN_END;
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                src++;
                break;
            case '0' ... '9':
                i = 0;
                do {
                    i = i * 10 + *src - '0';
                    src++;
                } while ('0' <= *src && *src <= '9');
                num->type = TOKEN_NUMBER;
                num->value = i;
                *_src = src;
                return TOKEN_NUMBER;
            case '*':
                num->type = TOKEN_MULTIPLY;
                *_src = src + 1;
                return TOKEN_MULTIPLY;
            case '/':
                num->type = TOKEN_DIVIDE;
                *_src = src + 1;
                return TOKEN_DIVIDE;
            case '+':
                num->type = TOKEN_PLUS;
                *_src = src + 1;
                return TOKEN_PLUS;
            case '-':
                num->type = TOKEN_MINUS;
                *_src = src + 1;
                return TOKEN_MINUS;
            case '(':
                num->type = TOKEN_LPAREN;
                *_src = src + 1;
                return TOKEN_LPAREN;
            case ')':
                num->type = TOKEN_RPAREN;
                *_src = src + 1;
                return TOKEN_RPAREN;
            default:
                num->type = TOKEN_UNKNOWN;
                return TOKEN_UNKNOWN;
        }
    }
}





int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <equation>\n", argv[0]);
        return 1;
    }

    return 0;
}

