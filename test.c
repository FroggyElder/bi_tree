#include "bi_tree.h"
#include <string.h>
#include <stdio.h>

int dataNameCmp (BT_ELEM_TYPE* a,BT_ELEM_TYPE* b) {
    return strcmp(a->name,b->name);
}

int dataAgeCmp (BT_ELEM_TYPE* a,BT_ELEM_TYPE* b) {
    return a->val - b->val;
}

void printData (BT_ELEM_TYPE* data) {
    if(data==NULL) {
        DEBUG_INFO;
        return;
    }
    printf("[%s %d]\n",data->name,data->val);
}

int main () {
    //Create my tree, and fill it with some nonsense data
    BT_ELEM_TYPE tmp_data;
    int (* cmp)(BT_ELEM_TYPE*,BT_ELEM_TYPE*) = dataNameCmp;

    strcpy(tmp_data.name,"Walta"); tmp_data.val = 55;
    struct bi_tree_node* my_tree = BiTreeNodeInit(tmp_data);
    strcpy(tmp_data.name,"Kim"); tmp_data.val = 42;
    BiTreeInsertInOrder(my_tree,BiTreeNodeInit(tmp_data),cmp);
    strcpy(tmp_data.name,"Mike"); tmp_data.val = 67;
    BiTreeInsertInOrder(my_tree,BiTreeNodeInit(tmp_data),cmp);
    strcpy(tmp_data.name,"Jessie"); tmp_data.val = 24;
    BiTreeInsertInOrder(my_tree,BiTreeNodeInit(tmp_data),cmp);
    strcpy(tmp_data.name,"Saul"); tmp_data.val = 45;
    BiTreeInsertInOrder(my_tree,BiTreeNodeInit(tmp_data),cmp);
    strcpy(tmp_data.name,"Gus"); tmp_data.val = 80;
    BiTreeInsertInOrder(my_tree,BiTreeNodeInit(tmp_data),cmp);

    BiTreePrintInOrder(my_tree,printData);

    printf("\n");
    strcpy(tmp_data.name,"Saul"); tmp_data.val = 45;
    printData(&BiTreeIndexInOrder(my_tree,tmp_data,cmp)->data);


    BiTreeDestroy(my_tree);

}