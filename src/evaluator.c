#include "evaluator.h"
#include <math.h>

double evaluate_rpn(const Token *rpn, int rpn_length, double x_value) {
    (void)rpn;
    (void)rpn_length;

    return sin(x_value);  // пока игнорируем всё, кроме x
}
