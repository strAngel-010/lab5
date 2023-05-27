//
// Created by vlad on 27.05.23.
//

#include "queue_mngr.h"

int add_all_vertices(Queue* const queue, Graph* const graph){
    for (int i = 0; i < graph->vertices; ++i) {
        Vertex* vertex = graph->adjList + i;
        if (!(vertex->name)){ continue; }

        Item* new_item = (Item*)malloc(sizeof(Item));
        if (!new_item){
            printf("Error in add_all_vertices()\n");
            return RES_ERR;
        }
        new_item->vertex_ind = i;
        new_item->next = queue->head;
        queue->head = new_item;
    }
    return RES_OK;
}

int extract_min(Queue* const queue, int* const dist){
    Item* res = queue->head;
    Item* res_prev = NULL;
    Item* cur = res->next;
    Item* cur_prev = res;
    while (cur){
        if (dist[cur->vertex_ind] < dist[res->vertex_ind]){
            res = cur;
            res_prev = cur_prev;
        }
        cur_prev = cur;
        cur = cur->next;
    }

    if (res_prev){ res_prev->next = res->next; }
    else { queue->head = res->next; }

    int min_ind = res->vertex_ind;
    free(res);
    return min_ind;
}
