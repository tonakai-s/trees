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
int tree_height(struct Node *root, int depth);

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
    printf("Tree height: %d", tree_height(root, 0));
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
        return insert_node(&((*root)->right), node);
    }

    if((*root)->left == NULL) {
        (*root)->left = node;
        return true;
    }
    return insert_node(&((*root)->left), node);
}

int tree_height(struct Node *root, int depth) {
    if(root == NULL) {
        return depth;
    }

    if(root->left != NULL) {
        depth = tree_height(root, depth+1);
    }

    if(root->right != NULL) {
        depth = tree_height(root, depth+1);
    }

    return depth;
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
    printf("%c %d\n", '-', root->val);
    // printf("%*s %c %d\n", level-1, "|", '>', root->val);

    if(root->left != NULL) {
        print_tree(root->left);
    }
    if(root->right != NULL) {
        print_tree(root->right);
    }

    level--;
    return;
}
