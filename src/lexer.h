#ifndef LEXER_H
#define LEXER_H

typedef enum
{
    T_NUMBER,
    T_OPERATOR,
    T_LPAREN,
    T_RPAREN,
    T_VARIABLE,
    T_FUNCTION
} TokenType;

typedef struct
{
    TokenType type;
    char str[16];
    double value;
} Token;

//// Возвращает количество токенов или -1 (при ошибке)
int tokenize(const char *expr, Token *out, int cap);

#endif