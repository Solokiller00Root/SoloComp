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

struct _ASPTree {
    TOKEN_TYPE type;
    int value;
    struct _ASPTree *left;
    struct _ASPTree *right;
};

TOKEN_TYPE lex(unsigned char **_src, TOKEN *num);
struct _ASPTree *parseFactor(unsigned char **_src);

struct _ASPTree *newNode(int value) {
    struct _ASPTree* node = (struct _ASPTree*)malloc(sizeof(struct _ASPTree));
    node->type = TOKEN_NUMBER;
    node->value = value;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct _ASPTree *parseTerm(unsigned char **_src) {
    TOKEN token;
    TOKEN_TYPE type = lex(_src, &token);
    printf("PARSE TERM: %d\n", type);
    struct _ASPTree *exp;

    switch (type) {
        case TOKEN_NUMBER:
            printf("Parsed NUMBER: %d\n", token.value);
            return newNode(token.value);
        case TOKEN_LPAREN:
            printf("Parsed LPAREN\n");
            exp = parseFactor(_src); 
            if (lex(_src, &token) != TOKEN_RPAREN) {
                printf("Missing closing parentheses");
                free(exp);
                return NULL;
            }
            return exp;
        default:
            printf("Error: Unexpected token\n");
            return NULL;
    }
}
struct _ASPTree *parseFactor(unsigned char **_src) {
    struct _ASPTree *left = parseTerm(_src);
    
    if (!left) {
        printf("Error: Failed to parse left term\n");
        return NULL;
    }

    TOKEN token;
    TOKEN_TYPE type = lex(_src, &token);
    printf("PARSE FACTOR: %d\n", type);

    switch (type) {
        case TOKEN_PLUS:
        case TOKEN_MINUS:
        case TOKEN_DIVIDE:
        case TOKEN_MULTIPLY:
            printf("Parsed operator\n");
            {
                struct _ASPTree *right = parseFactor(_src);
 
                if (!right) {
                    printf("Error: Failed to parse right factor\n");
                    free(left);
                    return NULL;
                }

                struct _ASPTree *exp = newNode(0); // Placeholder node
                exp->type = type;
                exp->left = left;
                exp->right = right;
                return exp;
            }
        case TOKEN_END:
            printf("Parsed end of input\n");
            return left;
        case TOKEN_RPAREN:
            printf("Parsed RPAREN\n");
            return left; 
        default:
            printf("Error: Unexpected token in parseFactor\n"); 
            free(left);
            return NULL;
    }
}

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

int parse(struct _ASPTree *node){
    if(node == NULL){
        printf("Error: Node = NULL\n");
        return 1;
    }

    switch(node->type){
        case TOKEN_NUMBER:
            return node->value;
        case TOKEN_PLUS:
            return parse(node->left) + parse(node->right);
        case TOKEN_MINUS:
            return parse(node->left) - parse(node->right);
        case TOKEN_MULTIPLY:
            return parse(node->left) * parse(node->right);
        case TOKEN_DIVIDE:
            return parse(node->left) / parse(node->right);
        default:
            printf("Error: Unexpected token PARSE\n");
            return 0;    
    }
}

void testLex(const char* input) {
    unsigned char* src = (unsigned char*) input;
    TOKEN token;

    printf("Input expression: %s\n", input);

    while (1) {
        TOKEN_TYPE type = lex(&src, &token);

        switch (type) {
            case TOKEN_END:
                printf("End of input\n");
                return;
            case TOKEN_NUMBER:
                printf("Token: NUMBER, Value: %d\n", token.value);
                break;
            case TOKEN_PLUS:
                printf("Token: PLUS\n");
                break;
            case TOKEN_MINUS:
                printf("Token: MINUS\n");
                break;
            case TOKEN_MULTIPLY:
                printf("Token: MULTIPLY\n");
                break;
            case TOKEN_DIVIDE:
                printf("Token: DIVIDE\n");
                break;
            case TOKEN_LPAREN:
                printf("Token: LPAREN\n");
                break;
            case TOKEN_RPAREN:
                printf("Token: RPAREN\n");
                break;
            case TOKEN_UNKNOWN:
                printf("Unknown token\n");
                break;
        }
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <equation>\n", argv[0]);
        return 1;
    }

    unsigned char *input = argv[1];
    struct _ASPTree *root = parseFactor(&input);
    //testLex(input);
  

    int result = parse(root);
    printf("Result: %d\n", result);

    free(root);
    return 0;
}

