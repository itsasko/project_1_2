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
void bst_insert(Node *root, int element){
    if(element <= root->value){
        if(root->left == nullptr) {
            root->left = new Node;
            root->left->value = element;
        }
        else{
            bst_insert(root->left, element);
        }
    }
    if(element > root->value){
        if(root->right == nullptr) {
            root->right = new Node;
            root->right->value = element;
        }
        else{
            bst_insert(root->right, element);
        }
    }
}

Node* bst_build(std::vector<int>& numbers){
    Node *root = new Node;
    root->value = numbers[0];
    Node *tmp = root;
    for(int i = 1; i < numbers.size(); i++){
        bst_insert(root, numbers[i]);
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

bool bst_search(Node_avl* root, std::string &searching_el){
    if(searching_el == root->value) return true;
    else{
        if(searching_el > root->value){
            if(root->right != nullptr) return avl_search(root->right, searching_el);
            else return false;
        }
        else{
            if(root->left != nullptr) return avl_search(root->left, searching_el);
            else return false;
        }
    }
}

void bst(std::vector<int>& numbers){
    Node* tmp = bst_build(numbers);
    Node* tmp_ = tmp;
    numbers.clear();
    bst_output(tmp, numbers);
    delete_tree(tmp_);
}

#endif //PROJECT_1_2_BST_H
