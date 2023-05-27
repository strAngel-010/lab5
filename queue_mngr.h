//
// Created by vlad on 27.05.23.
//

#ifndef LAB5_QUEUE_MNGR_H
#define LAB5_QUEUE_MNGR_H

#include <stdlib.h>
#include <stdio.h>
#include "structs.h"
#include "../aux_funcs/aux_funcs.h"

typedef struct Item{
    int vertex_ind;
    struct Item* next;
}Item;

typedef struct Queue{
    Item* head;
}Queue;

int add_all_vertices(Queue* const queue, Graph* const graph);
int extract_min(Queue* const queue, int* const dist);

#endif //LAB5_QUEUE_MNGR_H
