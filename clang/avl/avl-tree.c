#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MIN 1
#define MAX 30

struct Node {
    int val;
    int balance_factor;
    struct Node *left;
    struct Node *right;
};

bool insert_node(struct Node **root, struct Node *node);
void print_tree(struct Node *root);
int tree_depth(struct Node *root, int depth);

int main() {
    srand(time(NULL));
    
    struct Node *root = NULL;

    int tree_nodes_quantity = (rand() % (MAX - MIN + 1)) + MIN;
    for(int i = 0; i < tree_nodes_quantity; i++) {
        int ran_num = (rand() % (MAX - MIN + 1)) + MIN;
        struct Node *node = (struct Node *)malloc(sizeof(struct Node));
        node->val = ran_num;
        insert_node(&root, node);
    }

    print_tree(root);
    printf("Tree depth: %d", tree_depth(root, 1));
    return 0;
}

bool insert_node(struct Node **root, struct Node *node) {
    if(*root == NULL) {
        *root = node;
        return true;
    }

    if((*root)->val == node->val) {
        return false;
    }

    if(node->val > (*root)->val) {
        if((*root)->right == NULL) {
            (*root)->right = node;
            return true;
        }

        bool insert_res = insert_node(&((*root)->right), node);
        if(insert_res == true) (*root)->balance_factor = tree_depth((*root)->left, 1) - tree_depth((*root)->right, 1);
        return insert_res;
    }

    if((*root)->left == NULL) {
        (*root)->left = node;
        return true;
    }

    bool insert_res = insert_node(&((*root)->left), node);
    if(insert_res == true) (*root)->balance_factor = tree_depth((*root)->left, 1) - tree_depth((*root)->right, 1);
    return insert_res;
}

int tree_depth(struct Node *root, int depth) {
    if(root == NULL) {
        return depth;
    }

    int l_depth = depth;
    if(root->left != NULL) {
        l_depth = tree_depth(root->left, l_depth+1);
    }

    int r_depth = depth;
    if(root->right != NULL) {
        r_depth = tree_depth(root->right, r_depth+1);
    }

    if(l_depth > r_depth) return l_depth;
    return r_depth;
}

int level = 0;
void print_tree(struct Node *root) {
    level++;
    if(root == NULL) {
        return;
    }
    for(int i = 1; i < level; i++) {
        printf("%s", "| ");
    }
    printf("%c %d -- %d\n", '-', root->val, root->balance_factor);

    if(root->left != NULL) {
        print_tree(root->left);
    }
    if(root->right != NULL) {
        print_tree(root->right);
    }

    level--;
    return;
}
