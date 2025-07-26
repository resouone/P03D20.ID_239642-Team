#include "parser.h"

#include <string.h>

#include "lexer.h"

static int precedence(const char *op)
{
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0)
        return 1;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0)
        return 2;
    return 0;
}

static int is_left_associative(const char *op)
{
    return 1; // все операторы у нас левоассоциативные
}

int to_rpn(const Token *in, int n, Token *out, int cap)
{
    Token stack[256];
    int sp = 0;  // стек операндов
    int pos = 0; // позиция в out

    for (int i = 0; i < n; ++i)
    {
        Token tok = in[i];

        if (tok.type == T_NUMBER || tok.type == T_VARIABLE)
        {
            if (pos >= cap)
                return -1;
            out[pos++] = tok;
        }
        else if (tok.type == T_FUNCTION)
        {
            if (sp >= 256)
                return -1;
            stack[sp++] = tok;
        }
        else if (tok.type == T_OPERATOR)
        {
            while (sp > 0 && ((stack[sp - 1].type == T_FUNCTION) ||
                              (stack[sp - 1].type == T_OPERATOR &&
                               ((precedence(stack[sp - 1].str) > precedence(tok.str)) ||
                                (precedence(stack[sp - 1].str) == precedence(tok.str) &&
                                 is_left_associative(tok.str))))))
            {
                if (pos >= cap)
                    return -1;
                out[pos++] = stack[--sp];
            }
            stack[sp++] = tok;
        }
        else if (tok.type == T_LPAREN)
        {
            stack[sp++] = tok;
        }
        else if (tok.type == T_RPAREN)
        {
            int matched = 0;
            while (sp > 0)
            {
                if (stack[sp - 1].type == T_LPAREN)
                {
                    matched = 1;
                    --sp;
                    break;
                }
                if (pos >= cap)
                    return -1;
                out[pos++] = stack[--sp];
            }
            if (!matched)
                return -1; // несбалансированные скобки

            // если после скобки была функция — тоже выгрузим
            if (sp > 0 && stack[sp - 1].type == T_FUNCTION)
            {
                if (pos >= cap)
                    return -1;
                out[pos++] = stack[--sp];
            }
        }
        else
        {
            return -1; // неизвестный токен
        }
    }

    // сброс стека
    while (sp > 0)
    {
        if (stack[sp - 1].type == T_LPAREN || stack[sp - 1].type == T_RPAREN)
            return -1;
        if (pos >= cap)
            return -1;
        out[pos++] = stack[--sp];
    }

    return pos;
}
