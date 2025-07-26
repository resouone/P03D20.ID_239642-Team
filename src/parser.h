#ifndef PARSER_H
#define PARSER_H

#include "lexer.h"

int to_rpn(const Token *tokens, int token_count, Token *output, int max_output);

#endif
