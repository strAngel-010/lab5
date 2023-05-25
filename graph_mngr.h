//
// Created by vlad on 25.05.23.
//

#ifndef LAB5_GRAPH_MNGR_H
#define LAB5_GRAPH_MNGR_H

#include "../aux_funcs/aux_funcs.h"
#include "structs.h"

int add_vertex(Graph* const graph, char* const name);
int add_edge(Graph* const graph, char* const name1, char* const name2, const int weight);
int* find_vertices(Graph* const graph, const char** const arr, const int size);
Node* find_edge(Graph* const graph, const int* const arr);
void show(Graph* const graph);
void erase(Graph* const graph);

#endif //LAB5_GRAPH_MNGR_H
