#include "graph.h"
#include "evaluator.h"
#include "lexer.h"
#include "parser.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WIDTH 80
#define HEIGHT 25
#define X_MIN 0.0
#define X_MAX (4 * M_PI)
#define Y_MIN -1.0
#define Y_MAX 1.0


//Отрисовка
void draw_graph(const Token *rpn, size_t len) {
    char canvas [HEIGHT][WIDTH];

    for (int y = 0 ; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            canvas[y][x] = '.';
        }
    }

    for (int col = 0; col < WIDTH; col++) {
        double x = X_MIN + (X_MAX - X_MIN) * col / (WIDTH -1);
        double y = evaluate_rpn(rpn, len, x);

        //Проверка вхождения y в допуск
        if (y < Y_MIN || y > Y_MAX || isnan(y)){
            continue;
        }
        
        //Экранные координаты
        int row = round ((Y_MAX - y)/(Y_MAX - Y_MIN) * (HEIGHT -1));

        if (row >= 0 && row < HEIGHT) {
            canvas[row][col] = '*';
        }
    }

    //Построчный вывод
    for (int y = 0; y < HEIGHT; y++) {
        for (int x =0; x < WIDTH; x++) {
            putchar(canvas[y][x]);
        }
        putchar('\n');
    } 
}

//основная функция
int main(void) {
    char expr[256];

    if (!fgets(expr, sizeof(expr), stdin)){
        printf("n/a\n");
        return -1;
    }

    expr[strcspn(expr, "\n")] = 0;

    Token tokens[256];
    int token_count = tokenize(expr, tokens, 256);
    if (token_count < 0) {
        printf("n/a\n");
        return 1;
    }

    Token rpn[256];
    int rpn_len = to_rpn (tokens, token_count, rpn, 256);
    if (rpn_len < 0){
        printf("n/a\n");
        return 1;
    }

    draw_graph(rpn, rpn_len);
    return 0;
}

