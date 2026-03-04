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
bool exists(int val, struct Node *root);
int size(struct Node *root, int count);

int main() {
    struct Node *root = (struct Node *)malloc(sizeof(struct Node));
    root->val = 7;
    int min = 1;
    int max = 20;

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

    int search = 4;
    print_tree(root);
    printf("Tree size: %d\n", size(root, 0));

    if (exists(search, root)) {
        printf("%d exists? Sim\n", search);
    } else {
        printf("%d exists? Nao\n", search);
    }
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

int size(struct Node *root, int count) {
    if(root == NULL) return count;

    if(root->left != NULL) {
        return size(root->left, count+1);
    }
    if(root->right != NULL) {
        return size(root->right, count+1);
    }

    return count;
}

bool exists(int val, struct Node *root) {
    if(root == NULL) return false;
    if(root->val == val) return true;

    if(root->left != NULL) {
        return exists(val, root->left);
    }
    if(root->right != NULL) {
        return exists(val, root->right);
    }
    return false;
}


int level = 0;
void print_tree(struct Node *root) {
    level++;
    if(root == NULL) return;
    printf("%*s %c %d\n", level-1, "", '>', root->val);

    if(root->left != NULL) {
        print_tree(root->left);
    }
    if(root->right != NULL) {
        print_tree(root->right);
    }

    level--;
    return;
}

