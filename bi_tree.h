#ifndef _BI_TREE_
#define _BI_TREE_

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define DEBUG_INFO printf("%s:%s:%d\n",__FILE__,__func__,__LINE__)

typedef struct DataType{
    char name[32];
    int val;
}BT_ELEM_TYPE;

struct bi_tree_node {
    BT_ELEM_TYPE data;
    struct bi_tree_node* l_branch;
    struct bi_tree_node* r_branch;
};

struct bi_tree_node* BiTreeNodeInit (BT_ELEM_TYPE data);

void BiTreeDestroy (struct bi_tree_node* root);

bool BiTreeInsertInOrder (struct bi_tree_node* root,struct bi_tree_node* new_node,int (* dataCmp)(BT_ELEM_TYPE* a,BT_ELEM_TYPE* b));

bool BiTreePrintInOrder (struct bi_tree_node* root,void (* dataPrint)(BT_ELEM_TYPE* data));

struct bi_tree_node* BiTreeIndexInOrder 
    (struct bi_tree_node* root,BT_ELEM_TYPE* data,int (* dataCmp)(BT_ELEM_TYPE* a,BT_ELEM_TYPE* b));

bool BiTreeDeleteInOrder (struct bi_tree_node** node_ptr);

bool BiTreeDeleteBydata 
    (struct bi_tree_node** root, BT_ELEM_TYPE* data,int (* dataCmp)(BT_ELEM_TYPE* a,BT_ELEM_TYPE* b));

#endif