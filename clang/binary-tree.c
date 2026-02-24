#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "stdbool.h"

struct Node {
    int val;
    struct Node *left;
    struct Node *right;
};

bool insert_node(struct Node *new, struct Node *root);
void print_tree(struct Node *root);

int main() {
    struct Node *root = (struct Node *)malloc(sizeof(struct Node));
    root->val = 7;
    int min = 1;
    int max = 16;
    srand(time(NULL));
    for(int i = 0; i < 10; i++) {
        int ran_num = (rand() % (max - min + 1)) + min;

        struct Node *node = malloc(sizeof(struct Node));
        node->val = ran_num;

        if(insert_node(node, root) == false) {
            printf("%d already is in the tree.\n", node->val);
            continue;
        }
        printf("Inserted: %d\n", ran_num);
    }

    print_tree(root);
    return 0;
}

bool insert_node(struct Node *new, struct Node *root) {
    if(new->val == root->val) return false;

    if(new->val < root->val) {
        if(root->left == NULL) {
            root->left = new;
            return true;
        }
        return insert_node(new, root->left);
    }
    if(root->right == NULL) {
        root->right = new;
        return true;
    }
    return insert_node(new, root->right);
}

int level = -1;
void print_tree(struct Node *root) {
    level++;
    printf("%*s %c %d\n", level, "", '>', root->val);
    if(root->left != NULL) {
        print_tree(root->left);
    }
    if(root->right != NULL) {
        print_tree(root->right);
    }
    level--;
    return;
}

