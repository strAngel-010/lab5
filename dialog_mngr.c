//
// Created by vlad on 25.05.23.
//

#include "dialog_mngr.h"

int D_AddVertex(Graph* const graph){
    char* name = NULL;
    char buf[BUF_SIZE];
    buf[0] = '\0';

    scanf("%*[^\n]");
    getchar();
    printf("Enter name:\n");
    while (!strlen(buf)){
        if (!fgets(buf, BUF_SIZE-1, stdin)) {
            return RES_EOF;
        }
        buf[strlen(buf)-1] = '\0';
    }
    name = strdup(buf);

    int res = add_vertex(graph, name);
    if (res == RES_ERR){
        printf("Error in D_AddVertex()\n");
        return RES_ERR;
    }
    printf("OK\n");
    return RES_OK;
}

int D_AddEdge(Graph* const graph){
    char* name1 = NULL;
    char* name2 = NULL;
    int weight = 0;
    char buf[BUF_SIZE];

    buf[0] = '\0';
    scanf("%*[^\n]");
    getchar();
    printf("Enter first person's name:\n");
    while (!strlen(buf)){
        if (!fgets(buf, BUF_SIZE-1, stdin)) {
            return RES_EOF;
        }
        buf[strlen(buf)-1] = '\0';
    }
    name1 = strdup(buf);

    buf[0] = '\0';
    printf("Enter second person's name:\n");
    while (!strlen(buf)){
        if (!fgets(buf, BUF_SIZE-1, stdin)) {
            return RES_EOF;
        }
        buf[strlen(buf)-1] = '\0';
    }
    name2 = strdup(buf);

    printf("Enter weight:\n");
    if (getIntInInterval(&weight, MIN_WEIGHT, MAX_WEIGHT) == RES_EOF){
        return RES_EOF;
    }
    //printf("getInt: %d\n", weight);

    int res = add_edge(graph, name1, name2, weight);
    if (res == RES_ERR){
        printf("Error in D_AddEdge()\n");
        return RES_ERR;
    }
    printf("OK\n");

    free(name1);
    free(name2);
    return RES_OK;
}

int D_DeleteEdge(Graph* const graph){
    char* name1 = NULL;
    char* name2 = NULL;
    char buf[BUF_SIZE];

    buf[0] = '\0';
    scanf("%*[^\n]");
    getchar();
    printf("Enter first person's name:\n");
    while (!strlen(buf)){
        if (!fgets(buf, BUF_SIZE-1, stdin)) {
            return RES_EOF;
        }
        buf[strlen(buf)-1] = '\0';
    }
    name1 = strdup(buf);

    buf[0] = '\0';
    printf("Enter second person's name:\n");
    while (!strlen(buf)){
        if (!fgets(buf, BUF_SIZE-1, stdin)) {
            return RES_EOF;
        }
        buf[strlen(buf)-1] = '\0';
    }
    name2 = strdup(buf);

    int res = delete_edge(graph, name1, name2);
    if (res == RES_ERR){
        printf("Error in D_AddEdge()\n");
        return RES_ERR;
    }
    printf("OK\n");

    free(name1);
    free(name2);
    return RES_OK;
}
int D_DeleteVertex(Graph* const graph){
    char* name = NULL;
    char buf[BUF_SIZE];

    buf[0] = '\0';
    scanf("%*[^\n]");
    getchar();
    printf("Enter person's name:\n");
    while (!strlen(buf)){
        if (!fgets(buf, BUF_SIZE-1, stdin)) {
            return RES_EOF;
        }
        buf[strlen(buf)-1] = '\0';
    }
    name = strdup(buf);

    int res = delete_vertex(graph, name);
    if (res == RES_ERR){
        printf("Error in D_AddEdge()\n");
        return RES_ERR;
    }
    printf("OK\n");

    free(name);
    return RES_OK;
}
int D_EditVertex(Graph* const graph){
    char* name1 = NULL;
    char* name2 = NULL;
    int weight = 0;
    char buf[BUF_SIZE];

    buf[0] = '\0';
    scanf("%*[^\n]");
    getchar();
    printf("Enter name:\n");
    while (!strlen(buf)){
        if (!fgets(buf, BUF_SIZE-1, stdin)) {
            return RES_EOF;
        }
        buf[strlen(buf)-1] = '\0';
    }
    name1 = strdup(buf);

    buf[0] = '\0';
    printf("Enter new name:\n");
    while (!strlen(buf)){
        if (!fgets(buf, BUF_SIZE-1, stdin)) {
            return RES_EOF;
        }
        buf[strlen(buf)-1] = '\0';
    }
    name2 = strdup(buf);

    int res = edit_vertex(graph, name1, name2);
    if (res == RES_ERR){
        printf("Error in D_AddEdge()\n");
        return RES_ERR;
    }
    printf("OK\n");

    free(name1);
    return RES_OK;
}

int D_EditEdge(Graph* const graph){
    char* name1 = NULL;
    char* name2 = NULL;
    int weight = 0;
    char buf[BUF_SIZE];

    buf[0] = '\0';
    scanf("%*[^\n]");
    getchar();
    printf("Enter first person's name:\n");
    while (!strlen(buf)){
        if (!fgets(buf, BUF_SIZE-1, stdin)) {
            return RES_EOF;
        }
        buf[strlen(buf)-1] = '\0';
    }
    name1 = strdup(buf);

    buf[0] = '\0';
    printf("Enter second person's name:\n");
    while (!strlen(buf)){
        if (!fgets(buf, BUF_SIZE-1, stdin)) {
            return RES_EOF;
        }
        buf[strlen(buf)-1] = '\0';
    }
    name2 = strdup(buf);

    printf("Enter weight:\n");
    if (getIntInInterval(&weight, MIN_WEIGHT, MAX_WEIGHT) == RES_EOF){
        return RES_EOF;
    }

    int res = edit_edge(graph, name1, name2, weight);
    if (res == RES_ERR){
        printf("Error in D_AddEdge()\n");
        return RES_ERR;
    }
    printf("OK\n");

    free(name1);
    free(name2);
    return RES_OK;
}

int D_Show(Graph* const graph){
    show(graph);
    return RES_OK;
}

int D_StronglyConnectedComponents(Graph* const graph){
    int res = strongly_connected_components(graph);
    if (res == RES_ERR){ printf("Error in D_StronglyConnectedComponents()\n"); }
    return res;
}
int D_Traverse(Graph* const graph){}
