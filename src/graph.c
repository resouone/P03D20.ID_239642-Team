#include "graph.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "evaluator.h"
#include "lexer.h"
#include "parser.h"

#define WIDTH 80
#define HEIGHT 25
#define X_MIN 0.0
#define X_MAX (4.0 * M_PI)
#define Y_MIN -1.0
#define Y_MAX 1.0

static void clear_canvas(char canvas[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            canvas[y][x] = '.';
        }
    }
}

static void plot_point(char canvas[HEIGHT][WIDTH], int col, double y) {
    if (y < Y_MIN || y > Y_MAX || isnan(y)) return;

    // Ось Y идёт вниз, значит при Y_MIN -> row 0 (верх), при Y_MAX -> row HEIGHT-1 (низ)
    int row = round((y - Y_MIN) / (Y_MAX - Y_MIN) * (HEIGHT - 1));

    if (row >= 0 && row < HEIGHT && col >= 0 && col < WIDTH) {
        canvas[row][col] = '*';
    }
}

static void draw_canvas(const char canvas[HEIGHT][WIDTH]) {
    // Верх экрана — первая строка (0), низ — последняя (HEIGHT - 1)
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            putchar(canvas[y][x]);
        }
        putchar('\n');
    }
}

void draw_graph(const Token *rpn, int rpn_len) {
    char canvas[HEIGHT][WIDTH];
    clear_canvas(canvas);

    for (int col = 0; col < WIDTH; ++col) {
        double x = X_MIN + (X_MAX - X_MIN) * col / (WIDTH - 1);
        double y = evaluate_rpn(rpn, rpn_len, x);
        printf("x = %.6f, y = %.6f\n", x, y);
        plot_point(canvas, col, y);
    }

    draw_canvas(canvas);
}

int main(void) {
    char input[256];
    if (!fgets(input, sizeof(input), stdin)) {
        printf("n/a\n");
        return 1;
    }

    input[strcspn(input, "\n")] = '\0';

    Token tokens[256], rpn[256];
    int ntok = tokenize(input, tokens, 256);
    if (ntok < 0) {
        printf("n/a\n");
        return 1;
    }

    int nrpn = to_rpn(tokens, ntok, rpn, 256);
    if (nrpn < 0) {
        printf("n/a\n");
        return 1;
    }

    printf("RPN: ");
    for (int i = 0; i < nrpn; ++i) {
        printf("%s ", rpn[i].str);
    }
    printf("\n");

    draw_graph(rpn, nrpn);
    return 0;
}
