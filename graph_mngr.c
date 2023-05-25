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
    (graph->adjList)[graph->vertices-1].list = NULL;
    return RES_OK;
}

int delete_vertex(Graph* const graph, char* const name){
    int* res = find_vertices(graph, (const char**)&name, 1);
    if (!res){
        printf("Error in delete_vertex()\n");
        return RES_ERR;
    }

    if (res[0] == RES_FIND_ERR){
        printf("Person with this name doesn't exists\n");
        free(res);
        return RES_OK;
    }

    Node* cur = (graph->adjList + res[0])->list;
    Node* tmp = NULL;
    int delete_res = 0;
    while (cur){
        tmp = cur->next;
        delete_res = delete_edge(graph, (graph->adjList + res[0])->name,
                                 (graph->adjList + cur->ind)->name);
        if (delete_res == RES_ERR){
            printf("Error in delete_vertex()\n");
            return RES_ERR;
        }
        cur = tmp;
    }

    free((graph->adjList + res[0])->name);
    (graph->adjList + res[0])->name = NULL;
    free(res);
    return RES_OK;
}

/*
void move_elems(Graph* const graph, int a){
    for (int i = a; i < graph->vertices - 1; ++i) {
        (graph->adjList)[i] = (graph->adjList)[i+1];
    }
    --(graph->vertices);
    graph->adjList = (Vertex*) realloc(graph->adjList, (graph->vertices)*sizeof(Vertex));
    if (!(graph->adjList) && graph->vertices){
        printf("Error in move_elems()\n");
    }
}
 */

int add_edge(Graph* const graph, char* const name1, char* const name2, const int weight){
    int* res = valid_vertices(graph, name1, name2);
    if (!res){ return RES_OK; }

    if (find_edge(graph, res, NULL)){
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

int delete_edge(Graph* const graph, char* const name1, char* const name2){
    int* res = valid_vertices(graph, name1, name2);
    if (!res){ return RES_OK; }

    Node* prev1 = NULL;
    Node* prev2 = NULL;
    Node* cur1 = find_edge(graph, res, &prev1);
    if (!cur1){
        printf("Edge between \"%s\" and \"%s\" doesn't exist\n", name1, name2);
        free(res);
        return RES_OK;
    }
    int tmp = res[0];
    res[0] = res[1];
    res[1] = tmp;
    Node* cur2 = find_edge(graph, res, &prev2);
    if (!cur2){
        printf("Error in delete_edge()\n");
        return RES_ERR;
    }

    if (prev1){ prev1->next = cur1->next; }
    else { (graph->adjList + res[1])->list = cur1->next; }
    if (prev2){ prev2->next = cur2->next; }
    else { (graph->adjList + res[0])->list = cur2->next; }
    free(cur1);
    free(cur2);

    free(res);
    return RES_OK;
}

int* valid_vertices(Graph* const graph, char* const name1, char* const name2){
    char** arr = (char**) malloc(2 * sizeof(char*));
    if (!arr){
        printf("Error in add_edge()\n");
        return NULL;
    }
    arr[0] = name1;
    arr[1] = name2;

    int* res = find_vertices(graph, (const char**)arr, 2);
    if (!res){
        printf("Error in add_edge()\n");
        return NULL;
    }
    free(arr);

    if ((res[0] == RES_FIND_ERR) || (res[1] == RES_FIND_ERR)){
        if (res[0] == RES_FIND_ERR){ printf("Person with name %s doesn't exist\n", name1); }
        else { printf("Person with name \"%s\" doesn't exist\n", name2); }
        free(res);
        return NULL;
    }
    return res;
}

void show(Graph* const graph){
    Vertex* cur_vertex = NULL;
    Node* cur_node = NULL;
    for (int i = 0; i < graph->vertices; ++i) {
        cur_vertex = graph->adjList + i;
        if (!(cur_vertex->name)){ continue; }
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
            if (!((graph->adjList)[i].name)){ continue; }
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

Node* find_edge(Graph* const graph, const int* const arr, Node** prev){
    Node* cur = (graph->adjList)[arr[0]].list;
    Node* pr = NULL;
    while (cur && (cur->ind != arr[1])){
        pr = cur;
        cur = cur->next;
    }
    if (prev){ *prev = pr; }
    return cur;
}
