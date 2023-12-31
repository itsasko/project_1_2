#ifndef PROJECT_1_2_BST_H
#define PROJECT_1_2_BST_H

#include <vector>

struct Node {
    std::string value;
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
void bst_insert(Node *&root, std::string element){
    //std::cout << element << std::endl;

    if(element <= root->value){
        //std::cout << element << " <= " << root->value << std::endl;
        if(root->left == nullptr) {
            root->left = new Node;
            root->left->value = element;
        }
        else{
            bst_insert(root->left, element);
        }
    }
    else if(element > root->value){
        //std::cout << element << " > " << root->value << std::endl;
        if(root->right == nullptr) {
            root->right = new Node;
            root->right->value = element;
        }
        else{
            bst_insert(root->right, element);
        }
    }
}

Node* bst_build(std::vector<std::string>& words){
    Node *root = new Node;
    root->value = words[0];
    Node *tmp = root;
    for(int i = 1; i < words.size(); i++){
        bst_insert(root, words[i]);
    }
    return root;
}

void bst_output(Node* &tmp, std::vector<std::string>& sorted){
    if(tmp != nullptr){
        bst_output(tmp->left, sorted);
        sorted.push_back(tmp->value);
        bst_output(tmp->right, sorted);
    }
    return;
}

bool bst_search(Node* root, std::string searching_el){
    if(searching_el == root->value) return true;
    else{
        if(searching_el > root->value){
            if(root->right != nullptr) return bst_search(root->right, searching_el);
            else return false;
        }
        else{
            if(root->left != nullptr) return bst_search(root->left, searching_el);
            else return false;
        }
    }
}

void bst(std::vector<std::string>& numbers){
    Node* tmp = bst_build(numbers);
    Node* tmp_ = tmp;
    numbers.clear();
    bst_output(tmp, numbers);
    delete_tree(tmp_);
}

#endif //PROJECT_1_2_BST_H
