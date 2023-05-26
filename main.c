#include "dialog_mngr.h"
#include "graph_mngr.h"

int init();
int dialog(const char* msgs[], int N);

int main() {
    if (init()){
        printf("Program finished with errors\n");
    } else {
        printf("Program finished successfully\n");
    }
    return 0;
}

int init(){
    const char* msgs[] = {"0. Quit", "1. Add Vertex", "2. Add Edge", "3. Delete Vertex",
                          "4. Delete Edge", "5. Edit Vertex", "6. Edit Edge", "7. Show",
                          "8. Strongly Connected Components", "9. Traverse"};
    const int NMsgs = sizeof(msgs)/sizeof(msgs[0]);
    int (*fptr[])(Graph* const) = {NULL, D_AddVertex, D_AddEdge, D_DeleteVertex, D_DeleteEdge,
                                   D_EditVertex, D_EditEdge, D_Show, D_StronglyConnectedComponents, D_Traverse};
    Graph graph = {0, NULL};
    int res = 0;
    int rc = 0;

    while (rc = dialog(msgs, NMsgs)){
        if (rc >= NMsgs || rc < 0){
            printf("Wrong input format\n");
            continue;
        }
        res = fptr[rc](&graph);
        if (res == RES_ERR || res == RES_EOF){
            break;
        }
    }

    erase(&graph);
    return res == RES_ERR ? RES_ERR : RES_OK;
}

int dialog(const char* msgs[], const int N){
    int rc, res;
    for (int i = 0; i < N; ++i) {
        puts(msgs[i]);
    }
    printf("Make your choice:\n");
    res = getUInt(&rc);
    if (res == RES_EOF){
        rc = 0;
    }
    return rc;
}

