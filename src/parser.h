#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

// Переводит инфикс в ОПЗ (RPN)
// Возвращает количество выходных токенов или -1 при ошибке
int to_rpn(const Token *in, int n, Token *out, int cap);

#endif
