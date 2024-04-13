#include <stdio.h>

// enum for the types of the tokens
typedef enum{
    TOKEN_NUMBER,
    TOKEN_PLUS,
    TOKEN_MINUS,
    TOKEN_MULTIPLY,
    TOKEN_DIVIDE,
    TOKEN_LPAREN,
    TOKEN_RPAREN,
    TOKEN_SPACE,
    TOKEN_END,
    TOKEN_UNKNOWN
}TOKEN_TYPE;


//struct for the TOKEN

typedef struct{
    TOKEN_TYPE type;
    int value;  // value of the numbers !!! USED ONLY FOR TOKEN_NUMBER
}TOKEN;

TOKEN_TYPE currentTOKEN;

TOKEN_TYPE next(unsigned char **_src, TOKEN *num);

TOKEN_TYPE next(unsigned char **_src, TOKEN *num) {
    unsigned char *src = *_src;
    long i;
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
            case '0' ... '9':   // range between 0 and 9 not sure if its going to work without gcc compiler;
                i = 0;
                do {
                    i = i * 10 + *src - '0';
                    src++;
                } while ('0' <= *src && *src <= '9'); // equation to shift the characters in order to get their numbers, example: '1234' = 1234;
                num->value = i;
                *_src = src;
                return TOKEN_NUMBER;
            case '*':
                num->type = TOKEN_MULTIPLY;
                *_src=src+1;
                return TOKEN_MULTIPLY;
            case '/':
                num->type = TOKEN_DIVIDE;
                *_src=src+1;
                return TOKEN_DIVIDE;
            case '+':
                num->type = TOKEN_PLUS;
                *_src=src+1;
                return TOKEN_PLUS;
            case '-':
                num->type = TOKEN_MINUS;
                *_src=src+1;
                return TOKEN_MINUS; 
            case '(':
                num->type = TOKEN_LPAREN;
                *_src=src+1;
                return TOKEN_LPAREN;
            case ')':
                num->type = TOKEN_RPAREN;
                *_src=src+1;
                return TOKEN_RPAREN;
            default:
                src++;
                break;
        }
    }
}





int main(int argc, char *argv[]){

    if(argc < 2){
        printf("Usage: %s <equation>\n", argv[0]);
        return 1;
    }


    return 0;
}
    
   





