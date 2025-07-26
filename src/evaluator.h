#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "lexer.h"

double evaluate_rpn(const Token *rpn, int rpn_length, double x_value);

#endif
