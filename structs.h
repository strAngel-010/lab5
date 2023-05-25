//
// Created by vlad on 25.05.23.
//

#ifndef LAB5_STRUCTS_H
#define LAB5_STRUCTS_H

typedef struct Node{
    int ind;
    int weight;
    struct Node* next;
}Node;

typedef struct Vertex{
    int ind;
    char* name;
    Node* list;
}Vertex;

typedef struct Graph{
    int vertices;
    Vertex* adjList;
}Graph;

#endif //LAB5_STRUCTS_H
