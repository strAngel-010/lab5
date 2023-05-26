//
// Created by vlad on 25.05.23.
//

#ifndef LAB5_GRAPH_MNGR_H
#define LAB5_GRAPH_MNGR_H

#include "../aux_funcs/aux_funcs.h"
#include "structs.h"

enum DFS_VARIABLES{
    WHITE = 0,
    GREY = 1,
    BLACK = 2,
    NULL_PREDECESSOR = -1
};

int add_vertex(Graph* const graph, char* const name);
int edit_vertex(Graph* const graph, char* const name1, char* const name2);
int delete_vertex(Graph* const graph, char* const name);
int add_edge(Graph* const graph, char* const name1, char* const name2, const int weight);
int edit_edge(Graph* const graph, char* const name1, char* const name2, const int weight);
int delete_edge(Graph* const graph, char* const name1, char* const name2);
int strongly_connected_components(Graph* const graph);
void dfs_visit(Graph* const graph, int vertex_ind, int* const color, int* const pred);
int* valid_vertices(Graph* const graph, char* const name1, char* const name2);
int* find_vertices(Graph* const graph, const char** const arr, const int size);
Node* find_edge(Graph* const graph, const int* const arr, Node** prev);
void show(Graph* const graph);
void erase(Graph* const graph);

#endif //LAB5_GRAPH_MNGR_H
