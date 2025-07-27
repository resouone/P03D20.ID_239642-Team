#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "evaluator.h"
#include "lexer.h"
#include "parser.h"

int main(void) {
    char expr[256];
    double x;

    printf("Введите выражение: ");
    if (!fgets(expr, sizeof(expr), stdin)) {
        printf("n/a\n");
        return 1;
    }

    expr[strcspn(expr, "\n")] = '\0';

    printf("Введите значение x: ");
    if (scanf("%lf", &x) != 1) {
        printf("n/a\n");
        return 1;
    }

    Token toks[256];
    int n = tokenize(expr, toks, 256);
    if (n < 0) {
        printf("Ошибка лексера: n/a\n");
        return 1;
    }

    Token rpn[256];
    int len = to_rpn(toks, n, rpn, 256);
    if (len < 0) {
        printf("Ошибка парсера: n/a\n");
        return 1;
    }

    double result = evaluate_rpn(rpn, len, x);
    if (isnan(result)) {
        printf("Ошибка вычисления: n/a\n");
        return 1;
    }

    printf("f(%.5f) = %.8f\n", x, result);
    return 0;
}
