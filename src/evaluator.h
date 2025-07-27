#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "lexer.h"

// Вычисляет выражение в ОПЗ (RPN) при заданном x
// Возвращает результат или NAN при ошибке
double evaluate_rpn(const Token *rpn, int len, double x);

#endif