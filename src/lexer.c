#include "lexer.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int tokenize(const char *expression, Token *tokens, int max_tokens) {
    int i = 0; // позиция в строке
    int count = 0;

    while (expression[i] != '\0') {
        if (isspace(expression[i])) {
            i++;
            continue;
        }

        if (count >= max_tokens) return -1;

        // Число
        if (isdigit(expression[i]) || (expression[i] == '.' && isdigit(expression[i + 1]))) {
            char *end;
            tokens[count].value = strtod(&expression[i], &end);
            tokens[count].type = T_NUMBER;
            int len = end - &expression[i];
            strncpy(tokens[count].str, &expression[i], len);
            tokens[count].str[len] = '\0';
            i += len;
            count++;
            continue;
        }

        // Буквы — может быть x или функция
        if (isalpha(expression[i])) {
            char ident[16] = {0};
            int j = 0;

            while (isalpha(expression[i]) && j < 15) {
                ident[j++] = expression[i++];
            }
            ident[j] = '\0';

            if (strcmp(ident, "x") == 0) {
                tokens[count].type = T_VARIABLE;
            } else if (
                strcmp(ident, "sin") == 0 || strcmp(ident, "cos") == 0 ||
                strcmp(ident, "tan") == 0 || strcmp(ident, "ctg") == 0 ||
                strcmp(ident, "sqrt") == 0 || strcmp(ident, "ln") == 0
            ) {
                tokens[count].type = T_FUNCTION;
            } else {
                return -1;  // неизвестная функция/переменная
            }

            strcpy(tokens[count].str, ident);
            count++;
            continue;
        }

        // Скобки
        if (expression[i] == '(') {
            tokens[count].type = T_LPAREN;
            strcpy(tokens[count].str, "(");
            count++;
            i++;
            continue;
        }

        if (expression[i] == ')') {
            tokens[count].type = T_RPAREN;
            strcpy(tokens[count].str, ")");
            count++;
            i++;
            continue;
        }

        // Операторы
        if (strchr("+-*/", expression[i])) {
            tokens[count].type = T_OPERATOR;
            tokens[count].str[0] = expression[i];
            tokens[count].str[1] = '\0';
            count++;
            i++;
            continue;
        }

        // Неизвестный символ
        return -1;
    }

    return count;
}

