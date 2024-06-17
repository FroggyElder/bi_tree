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

void BiTreeDestroy (struct bi_tree_node* root) {
    if (root==NULL) return;
    if (root->l_branch != NULL) BiTreeDestroy(root->l_branch);
    if (root->r_branch != NULL) BiTreeDestroy(root->r_branch);

    free(root);
    return;
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
    (struct bi_tree_node* root,BT_ELEM_TYPE* data,int (* dataCmp)(BT_ELEM_TYPE* a,BT_ELEM_TYPE* b)) 
{
    if (root==NULL) return NULL;

    if (dataCmp(data,&root->data)==0) return root;

    else return dataCmp(data,&root->data)<0 ?
    BiTreeIndexInOrder(root->l_branch,data,dataCmp):
    BiTreeIndexInOrder(root->r_branch,data,dataCmp);

}

bool BiTreeDeleteInOrder (struct bi_tree_node** node_ptr) {
    if(node_ptr==NULL) return false;
    if(*node_ptr==NULL) return true;

    if((*node_ptr)->l_branch!=NULL) {
        if((*node_ptr)->l_branch->r_branch==NULL) {
            (*node_ptr)->data = (*node_ptr)->l_branch->data;
            return BiTreeDeleteInOrder(&(*node_ptr)->l_branch);
        }
        else {
            struct bi_tree_node* p = (*node_ptr)->l_branch;
            while (p->r_branch->r_branch!=NULL)
                p=p->r_branch;
            (*node_ptr)->data = p->r_branch->data;
            return BiTreeDeleteInOrder(&(p->r_branch));
        }
    }
    else if((*node_ptr)->r_branch!=NULL) {
        if((*node_ptr)->r_branch->l_branch==NULL) {
            (*node_ptr)->data = (*node_ptr)->r_branch->data;
            return BiTreeDeleteInOrder(&(*node_ptr)->r_branch);
        }
        else {
            struct bi_tree_node* p = (*node_ptr)->r_branch;
            while (p->l_branch->l_branch!=NULL)
                p=p->l_branch;
            (*node_ptr)->data = p->l_branch->data;
            return BiTreeDeleteInOrder(&(p->l_branch));
        }
    }
    else {
        free(*node_ptr);
        *node_ptr=NULL;
    }

    return true;
}

bool BiTreeDeleteBydata 
    (struct bi_tree_node** root, BT_ELEM_TYPE* data,int (* dataCmp)(BT_ELEM_TYPE* a,BT_ELEM_TYPE* b)) 
{
    if(root==NULL||*root==NULL) return false;

    int cmp = dataCmp(data,&(*root)->data);

    if(cmp==0) {
        if((*root)->l_branch!=NULL) {
            if((*root)->l_branch->r_branch==NULL) {
                (*root)->data = (*root)->l_branch->data;
                return BiTreeDeleteInOrder(&(*root)->l_branch);
            }
            else {
                struct bi_tree_node* p = (*root)->l_branch;
                while (p->r_branch->r_branch!=NULL)
                    p=p->r_branch;
                (*root)->data = p->r_branch->data;
                return BiTreeDeleteInOrder(&p->r_branch);
            }
        }
        else if ((*root)->r_branch!=NULL) {
            if((*root)->r_branch->l_branch==NULL) {
                (*root)->data = (*root)->r_branch->data;
                return BiTreeDeleteInOrder(&(*root)->r_branch);
            }
            else {
                struct bi_tree_node* p = (*root)->r_branch;
                while (p->l_branch->l_branch!=NULL)
                    p=p->l_branch;
                (*root)->data = p->l_branch->data;
                return BiTreeDeleteInOrder(&p->l_branch);
            }
        }
        else {
            free(*root);
            *root = NULL;
        }
        return true;
    }
    else if(cmp<0) {
        return BiTreeDeleteBydata(&(*root)->l_branch,data,dataCmp);
    }
    else {
        return BiTreeDeleteBydata(&(*root)->r_branch,data,dataCmp);
    }
}