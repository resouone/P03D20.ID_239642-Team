#include "lexer.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_digit(char c) { return c >= '0' && c <= '9'; }

static int is_letter(char c) { return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'); }

static int is_space(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r'; }

static int is_func(const char *s) {
    return strcmp(s, "sin") == 0 || strcmp(s, "cos") == 0 || strcmp(s, "tan") == 0 || strcmp(s, "ctg") == 0 ||
           strcmp(s, "sqrt") == 0 || strcmp(s, "ln") == 0;
}

int tokenize(const char *expr, Token *out, int cap) {
    int i = 0;      // индекс в expr
    int count = 0;  // сколько токенов уже записано

    while (expr[i] != '\0') {
        char c = expr[i];

        if (is_space(c)) {
            i++;
            continue;
        }

        if (count >= cap) return -1;

        // Число: 3.14 или .5
        if (is_digit(c) || (c == '.' && is_digit(expr[i + 1]))) {
            char buf[32] = {0};
            int j = 0;

            while ((is_digit(expr[i]) || expr[i] == '.') && j < 31) {
                buf[j++] = expr[i++];
            }
            buf[j] = '\0';

            out[count].type = T_NUMBER;
            out[count].value = strtod(buf, NULL);
            strncpy(out[count].str, buf, sizeof(out[count].str));
            count++;
            continue;
        }

        // Идентификатор: функция или переменная
        if (is_letter(c)) {
            char buf[16] = {0};
            int j = 0;

            while (is_letter(expr[i]) && j < 15) {
                buf[j++] = expr[i++];
            }
            buf[j] = '\0';

            if (strcmp(buf, "x") == 0) {
                out[count].type = T_VARIABLE;
            } else if (is_func(buf)) {
                out[count].type = T_FUNCTION;
            } else {
                return -1;
            }

            strncpy(out[count].str, buf, sizeof(out[count].str));
            count++;
            continue;
        }

        // Скобки
        if (c == '(' || c == ')') {
            out[count].type = (c == '(') ? T_LPAREN : T_RPAREN;
            out[count].str[0] = c;
            out[count].str[1] = '\0';
            count++;
            i++;
            continue;
        }

        // Операторы
        if (c == '+' || c == '-' || c == '*' || c == '/') {
            out[count].type = T_OPERATOR;
            out[count].str[0] = c;
            out[count].str[1] = '\0';
            count++;
            i++;
            continue;
        }

        // Ошибка: неизвестный символ
        return -1;
    }

    return count;
}
