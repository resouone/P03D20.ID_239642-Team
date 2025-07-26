#ifndef GRAPH_H
#define GRAPH_H

#include "lexer.h"  // для определения Token
#include <stddef.h>

void draw_graph(const Token *rpn, size_t len);

#endif
