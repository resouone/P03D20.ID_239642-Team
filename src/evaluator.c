#include <math.h>
#include <string.h>

#include "lexer.h"

double evaluate_rpn(const Token *rpn, int len, double x)
{
    double stack[256];
    int sp = 0;

    for (int i = 0; i < len; ++i)
    {
        Token t = rpn[i];

        if (t.type == T_NUMBER)
        {
            stack[sp++] = t.value;
        }
        else if (t.type == T_VARIABLE)
        {
            stack[sp++] = x;
        }
        else if (t.type == T_OPERATOR)
        {
            if (sp < 2)
                return NAN;
            double b = stack[--sp];
            double a = stack[--sp];

            if (strcmp(t.str, "+") == 0)
            {
                stack[sp++] = a + b;
            }
            else if (strcmp(t.str, "-") == 0)
            {
                stack[sp++] = a - b;
            }
            else if (strcmp(t.str, "*") == 0)
            {
                stack[sp++] = a * b;
            }
            else if (strcmp(t.str, "/") == 0)
            {
                if (b == 0.0)
                    return NAN;
                stack[sp++] = a / b;
            }
            else
            {
                return NAN; // неизвестный оператор
            }
        }
        else if (t.type == T_FUNCTION)
        {
            if (sp < 1)
                return NAN;
            double arg = stack[--sp];

            if (strcmp(t.str, "sin") == 0)
            {
                stack[sp++] = sin(arg);
            }
            else if (strcmp(t.str, "cos") == 0)
            {
                stack[sp++] = cos(arg);
            }
            else if (strcmp(t.str, "tan") == 0)
            {
                stack[sp++] = tan(arg);
            }
            else if (strcmp(t.str, "ctg") == 0)
            {
                if (tan(arg) == 0.0)
                    return NAN;
                stack[sp++] = 1.0 / tan(arg);
            }
            else if (strcmp(t.str, "sqrt") == 0)
            {
                if (arg < 0.0)
                    return NAN;
                stack[sp++] = sqrt(arg);
            }
            else if (strcmp(t.str, "ln") == 0)
            {
                if (arg <= 0.0)
                    return NAN;
                stack[sp++] = log(arg);
            }
            else
            {
                return NAN; // неизвестная функция
            }
        }
        else
        {
            return NAN; // некорректный токен
        }
    }

    if (sp != 1)
        return NAN;
    return stack[0];
}
