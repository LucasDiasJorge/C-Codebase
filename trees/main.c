#include <stdio.h>
#include <stdlib.h>

typedef struct tree{
    int value;
    struct tree * right;
    struct tree * left;
} tree;

static void print_tree_sideways(const tree* root, int depth, char branch){
    if(root == NULL) return;

    print_tree_sideways(root->right, depth + 1, '/');
    for(int i = 0; i < depth; i++) printf("    ");
    if(branch != '\0') printf("%c-- ", branch);
    printf("%d\n", root->value);
    print_tree_sideways(root->left, depth + 1, '\\');
}

void print_tree(tree* root){
    if(root == NULL){
        puts("(arvore vazia)");
        return;
    }
    print_tree_sideways(root, 0, '\0');
}

static tree* insert_node(tree* root, tree* leaf){
    if(root == NULL) return leaf;
    if(leaf->value < root->value)
        root->left = insert_node(root->left, leaf);
    else
        root->right = insert_node(root->right, leaf);
    return root;
}

tree* create_leaf(tree* root, int value){
    tree* leaf = malloc(sizeof(*leaf));
    if(leaf == NULL) return NULL;
    leaf->value = value;
    leaf->left = NULL;
    leaf->right = NULL;
    return insert_node(root, leaf);
}

static void free_tree(tree* root){
    if(root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(void) {
    tree* root = NULL;
    tree* new_root = create_leaf(root, 1);
    if(new_root == NULL){
        perror("malloc");
        free_tree(root);
        return EXIT_FAILURE;
    }
    root = new_root;

    print_tree(root);
    free_tree(root);
    return 0;
}