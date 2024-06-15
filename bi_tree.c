#include "bi_tree.h"

struct bi_tree_node* BiTreeNodeInit (BT_ELEM_TYPE data) {
    struct bi_tree_node* new_node = (struct bi_tree_node*)malloc(sizeof(struct bi_tree_node));
    if(new_node==NULL) {
        DEBUG_INFO;
        perror("");
        return NULL;
    }

    new_node->data = data;
    new_node->l_branch = NULL;
    new_node->r_branch = NULL;

    return new_node;
}

bool BiTreeDestroy (struct bi_tree_node* root) {
    if (root==NULL) return true;
    if (root->l_branch != NULL) BiTreeDestroy(root->l_branch);
    if (root->r_branch != NULL) BiTreeDestroy(root->r_branch);

    free(root);
}

bool BiTreeInsertInOrder (struct bi_tree_node* root,struct bi_tree_node* new_node,
                            int (* dataCmp)(BT_ELEM_TYPE* a,BT_ELEM_TYPE* b)) 
{
    if(root==NULL||new_node==NULL) {
        DEBUG_INFO;
        return false;
    }

    if(dataCmp(&new_node->data,&root->data) < 0) {
        if (root->l_branch != NULL)
            return BiTreeInsertInOrder (root->l_branch,new_node,dataCmp);
        else root->l_branch=new_node;
    }
    else {
        if (root->r_branch != NULL)
            return BiTreeInsertInOrder (root->r_branch,new_node,dataCmp);
        else root->r_branch=new_node;
    }

    return true;
}

bool BiTreePrintInOrder (struct bi_tree_node* root,void (* dataPrint)(BT_ELEM_TYPE* data)) 
{
    if (root==NULL) {
        DEBUG_INFO;
        return false;
    }

    if(root->l_branch) BiTreePrintInOrder(root->l_branch,dataPrint);

    dataPrint(&root->data);

    if(root->r_branch) BiTreePrintInOrder(root->r_branch,dataPrint);

    return true;
}

struct bi_tree_node* BiTreeIndexInOrder 
    (struct bi_tree_node* root,BT_ELEM_TYPE data,int (* dataCmp)(BT_ELEM_TYPE* a,BT_ELEM_TYPE* b)) 
{
    if (root==NULL) return NULL;

    if (dataCmp(&data,&root->data)==0) return root;

    else return dataCmp(&data,&root->data)<0 ?
    BiTreeIndexInOrder(root->l_branch,data,dataCmp):
    BiTreeIndexInOrder(root->r_branch,data,dataCmp);

}

bool BiTreeDeleteInOrder (struct bi_tree_node** node_ptr) {
    if(node_ptr==NULL) return false;
    if(*node_ptr==NULL) return true;

    if((*node_ptr)->l_branch!=NULL) {
        if((*node_ptr)->l_branch->r_branch==NULL) return BiTreeDeleteInOrder(&(*node_ptr)->l_branch);
        else {
            struct bi_tree_node* p = (*node_ptr)->l_branch;
            while (p->r_branch->r_branch!=NULL)
                p=p->r_branch;
            return BiTreeDeleteInOrder(&(p->r_branch));
        }
    }
    else if((*node_ptr)->r_branch!=NULL) {
        if((*node_ptr)->r_branch->l_branch==NULL) return BiTreeDeleteInOrder(&(*node_ptr)->r_branch);
        else {
            struct bi_tree_node* p = (*node_ptr)->r_branch;
            while (p->l_branch->l_branch!=NULL)
                p=p->l_branch;
            return BiTreeDeleteInOrder(&(p->l_branch));
        }
    }
    else {
        free(*node_ptr);
        *node_ptr=NULL;
    }

    return true;
}