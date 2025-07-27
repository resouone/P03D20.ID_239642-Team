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

    int row = round((Y_MAX - y) / (Y_MAX - Y_MIN) * (HEIGHT - 1));
    if (row >= 0 && row < HEIGHT && col >= 0 && col < WIDTH) {
        canvas[row][col] = '*';
    }
}

static void draw_canvas(const char canvas[HEIGHT][WIDTH]) {
    for (int y = 0; y < HEIGHT; ++y) {
        for (int x = 0; x < WIDTH; ++x) {
            putchar(canvas[y][x]);
        }
        putchar('\n');
    }
}

static void draw_graph(const Token *rpn, int rpn_len) {
    char canvas[HEIGHT][WIDTH];
    clear_canvas(canvas);

    for (int col = 0; col < WIDTH; ++col) {
        double x = X_MIN + (X_MAX - X_MIN) * col / (WIDTH - 1);
        double y = evaluate_rpn(rpn, rpn_len, x);
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

    draw_graph(rpn, nrpn);
    return 0;
}
