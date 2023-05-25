//
// Created by vlad on 25.05.23.
//

#include "graph_mngr.h"

int add_vertex(Graph* const graph, char* const name){
    int* res = find_vertices(graph, (const char**)&name, 1);
    if (!res){
        printf("Error in add_vertex()\n");
        return RES_ERR;
    }

    if (res[0] != RES_FIND_ERR){
        printf("Person with this name already exists\n");
        free(res);
        free(name);
        return RES_OK;
    }
    free(res);

    graph->adjList = (Vertex*) realloc(graph->adjList, (graph->vertices+1)*sizeof(Vertex));
    if (!(graph->adjList)){
        printf("Error in add_vertex()\n");
        return RES_ERR;
    }
    ++(graph->vertices);
    (graph->adjList)[graph->vertices-1].name = name;
    (graph->adjList)[graph->vertices-1].ind = graph->vertices-1;
    (graph->adjList)[graph->vertices-1].list = NULL;
    return RES_OK;
}

int add_edge(Graph* const graph, char* const name1, char* const name2, const int weight){
    char** arr = (char**) malloc(2 * sizeof(char*));
    if (!arr){
        printf("Error in add_edge()\n");
        return RES_ERR;
    }
    arr[0] = name1;
    arr[1] = name2;

    int* res = find_vertices(graph, (const char**)arr, 2);
    if (!res){
        printf("Error in add_edge()\n");
        return RES_ERR;
    }
    free(arr);

    if ((res[0] == RES_FIND_ERR) || (res[1] == RES_FIND_ERR)){
        if (res[0] == RES_FIND_ERR){ printf("Person with name %s doesn't exist\n", name1); }
        else { printf("Person with name \"%s\" doesn't exist\n", name2); }
        free(res);
        return RES_OK;
    }

    if (find_edge(graph, res)){
        printf("Edge between %s and \"%s\" already exists\n", name1, name2);
        free(res);
        return RES_OK;
    }

    Node* node1 = (Node*) malloc(sizeof(Node));
    Node* node2 = (Node*) malloc(sizeof(Node));
    if (!node1 || !node2){
        printf("Error in add_edge()\n");
        return RES_ERR;
    }
    node1->next = (graph->adjList)[res[0]].list;
    (graph->adjList)[res[0]].list = node1;
    node1->ind = res[1];
    node1->weight = weight;

    node2->next = (graph->adjList)[res[1]].list;
    (graph->adjList)[res[1]].list = node2;
    node2->ind = res[0];
    node2->weight = weight;

    free(res);
    return RES_OK;
}

void show(Graph* const graph){
    Vertex* cur_vertex = NULL;
    Node* cur_node = NULL;
    for (int i = 0; i < graph->vertices; ++i) {
        cur_vertex = graph->adjList + i;
        printf("%s: ", cur_vertex->name);

        cur_node = cur_vertex->list;
        while (cur_node){
            printf("%s (%d)", (graph->adjList)[cur_node->ind].name, cur_node->weight);
            if (cur_node->next) { printf(" --> "); }
            cur_node = cur_node->next;
        }
        printf("\n");
    }
}

void erase(Graph* const graph){
    Node* prev = NULL;
    Node* cur = NULL;
    for (int i = 0; i < graph->vertices; ++i) {
        cur = (graph->adjList + i)->list;
        while (cur){
            prev = cur;
            cur = cur->next;
            free(prev);
        }

        free((graph->adjList + i)->name);
    }
    if (graph->adjList){ free(graph->adjList); }
}

int* find_vertices(Graph* const graph, const char** const arr, const int size){
    int* res = (int*) malloc(size * sizeof(int));
    if (!res){
        printf("Error in find_vertices()\n");
        return NULL;
    }
    for (int i = 0; i < size; ++i) {
        res[i] = RES_FIND_ERR;
    }

    for (int i = 0; i < graph->vertices; ++i) {
        for (int j = 0; j < size; ++j) {
            if (strcmp((graph->adjList)[i].name, arr[j]) == 0){ res[j] = i; }
        }

        int all_elems_found = 1;
        for (int j = 0; j < size; ++j) {
            if (res[j] == RES_FIND_ERR){
                all_elems_found = 0;
                break;
            }
        }
        if (all_elems_found){ return res; }
    }
    return res;
}

Node* find_edge(Graph* const graph, const int* const arr){
    Node* cur = (graph->adjList)[arr[0]].list;
    while (cur && (cur->ind != arr[1])){ cur = cur->next; }
    return cur;
}
