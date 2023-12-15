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

Node* bst_build(std::vector<int>& numbers){
    Node *root = new Node;
    root->value = numbers[0];
    Node *tmp = root;
    for(auto i : numbers){
        if(i > tmp->value) {
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
    return root;
}

void bst_output(Node* &tmp, std::vector<int>& sorted){
    if(tmp != nullptr){
        bst_output(tmp->left, sorted);
        sorted.push_back(tmp->value);
        bst_output(tmp->right, sorted);
    }
    return;
}

void bst(std::vector<int>& numbers){
    Node* tmp = bst_build(numbers);
    Node* tmp_ = tmp;
    numbers.clear();
    bst_output(tmp, numbers);
    delete_tree(tmp_);
}

#endif //PROJECT_1_2_BST_H
