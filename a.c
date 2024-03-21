#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *left;
    struct node *right;
};

typedef struct node *BTREE;

BTREE insert(BTREE root, int x) {
    if (root == NULL) {
        BTREE new_node = malloc(sizeof(struct node));
        new_node->left = new_node->right = NULL;
        new_node->data = x;
        return new_node;
    }
    if (root->data < x) {
        root->right = insert(root->right, x);
    } else if (root->data > x) {
        root->left = insert(root->left, x);
    }
    return root;
}

void traverse(BTREE root) {
    if (root == NULL)
        return;
    else {
        BTREE temp;
        temp = root->left;
        root->left = root->right;
        root->right = temp;
        traverse(root->left);
        traverse(root->right);
    }
}

BTREE delete_node(BTREE root, int x) {
    BTREE p, q;
    if (root == NULL)
        return NULL;
    if (root->data == x) {
        if (root->left == root->right) {
            free(root);
            return NULL;
        } else {
            if (root->left == NULL) {
                p = root->right;
                free(root);
                return p;
            } else if (root->right == NULL) {
                p = root->left;
                free(root);
                return p;
            } else {
                p = q = root->right;
                while (p->left != NULL)
                    p = p->left;
                p->left = root->left;
                free(root);
                return q;
            }
        }
    }
    if (root->data < x)
        root->right = delete_node(root->right, x);
    else
        root->left = delete_node(root->left, x);
    return root;
}

int main() {
    BTREE root = NULL;
    root = insert(root, 12);
    root = insert(root, 55);
    root = insert(root, 21);
    root = insert(root, 3);

    traverse(root);
    delete_node(root, 21);
    printf("\n");
    traverse(root);

    return 0;
}
