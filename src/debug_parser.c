#include <stdio.h>

#include "lexer.h"
#include "parser.h"

void print_token(const Token *t)
{
    switch (t->type)
    {
    case T_NUMBER:
        printf("NUMBER(%g)", t->value);
        break;
    case T_OPERATOR:
        printf("OPERATOR(%s)", t->str);
        break;
    case T_LPAREN:
        printf("LPAREN");
        break;
    case T_RPAREN:
        printf("RPAREN");
        break;
    case T_VARIABLE:
        printf("VARIABLE(%s)", t->str);
        break;
    case T_FUNCTION:
        printf("FUNCTION(%s)", t->str);
        break;
    default:
        printf("UNKNOWN");
    }
}

int main(void)
{
    char expr[256];
    printf("Введите выражение: ");
    if (!fgets(expr, sizeof(expr), stdin))
    {
        return 1;
    }

    Token toks[256], rpn[256];
    int n = tokenize(expr, toks, 256);
    if (n < 0)
    {
        printf("Лексическая ошибка\n");
        return 1;
    }

    int rpn_len = to_rpn(toks, n, rpn, 256);
    if (rpn_len < 0)
    {
        printf("Ошибка преобразования в RPN\n");
        return 1;
    }

    printf("RPN: ");
    for (int i = 0; i < rpn_len; ++i)
    {
        printf("%s ", rpn[i].str);
    }
    printf("\n");

    return 0;
}
