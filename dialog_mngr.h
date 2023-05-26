//
// Created by vlad on 25.05.23.
//

#ifndef LAB5_DIALOG_MNGR_H
#define LAB5_DIALOG_MNGR_H

#include <stdio.h>
#include "structs.h"
#include "../aux_funcs/aux_funcs.h"
#include "graph_mngr.h"

int D_AddVertex(Graph* const graph);
int D_AddEdge(Graph* const graph);
int D_DeleteEdge(Graph* const graph);
int D_DeleteVertex(Graph* const graph);
int D_EditVertex(Graph* const graph);
int D_EditEdge(Graph* const graph);
int D_Show(Graph* const graph);
int D_StronglyConnectedComponents(Graph* const graph);
int D_Traverse(Graph* const graph);

#endif //LAB5_DIALOG_MNGR_H
