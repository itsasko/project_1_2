#ifndef PROJECT_1_2_BST_H
#define PROJECT_1_2_BST_H

#include <vector>

struct Node {
    int value;
    Node *left = nullptr;
    Node *right = nullptr;
};
void delete_tree(Node *root) {
    if (root != nullptr) {
        delete_tree(root->left);
        delete_tree(root->right);
        delete root;
    }
}

void bst_build(std::vector<int>& numbers){
    Node *root = new Node;
    root->value = numbers[0];
    Node *tmp = root;
    for(auto i : numbers){
        if(i > root->value) {
            tmp->right = new Node;
            tmp->right->value = i;
            tmp = tmp->right;
        }
        else {
            tmp->left = new Node;
            tmp->left->value = i;
            tmp = tmp->left;
        }
    }
}

#endif //PROJECT_1_2_BST_H
