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
        if (is_space(expr[i])) {
            i++;
            continue;
        }

        if (count >= cap) return -1;

        // Число: 3.14 или .5 или -0.5
        if (is_digit(expr[i]) || (expr[i] == '.' && is_digit(expr[i + 1])) ||
            (expr[i] == '-' &&
             (i == 0 || out[count - 1].type == T_OPERATOR || out[count - 1].type == T_LPAREN) &&
             (is_digit(expr[i + 1]) || expr[i + 1] == '.'))) {
            char buf[32] = {0};
            int j = 0;

            if (expr[i] == '-') {
                buf[j++] = expr[i++];
            }

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

        // Унарный минус перед переменной или функцией → заменяем на "0 - x"
        if (expr[i] == '-' &&
            (i == 0 || out[count - 1].type == T_OPERATOR || out[count - 1].type == T_LPAREN) &&
            is_letter(expr[i + 1])) {
            // Добавим "0"
            out[count].type = T_NUMBER;
            out[count].value = 0.0;
            strcpy(out[count].str, "0");
            count++;

            // Добавим "-"
            out[count].type = T_OPERATOR;
            strcpy(out[count].str, "-");
            count++;

            i++;  // пропускаем '-'

            // Теперь ожидаем переменную или функцию
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

        // Переменная или функция
        if (is_letter(expr[i])) {
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
        if (expr[i] == '(' || expr[i] == ')') {
            out[count].type = (expr[i] == '(') ? T_LPAREN : T_RPAREN;
            out[count].str[0] = expr[i];
            out[count].str[1] = '\0';
            count++;
            i++;
            continue;
        }

        // Операторы + - * /
        if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            out[count].type = T_OPERATOR;
            out[count].str[0] = expr[i];
            out[count].str[1] = '\0';
            count++;
            i++;
            continue;
        }

        // Неизвестный символ
        return -1;
    }

    return count;
}
