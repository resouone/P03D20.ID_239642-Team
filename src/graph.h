#ifndef GRAPH_H
#define GRAPH_H
#define M_PI 3.14159265358979323846
#include <stddef.h>

#include "lexer.h"  // для определения Token

void draw_graph(const Token *rpn, size_t len);

#endif
