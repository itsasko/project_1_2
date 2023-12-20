#ifndef PROJECT_1_2_AVL_H
#define PROJECT_1_2_AVL_H
#include <cassert>
struct Node_avl {
    int value, height = 0;
    Node_avl *left = nullptr;
    Node_avl *right = nullptr;
};
void delete_tree(Node_avl *root) {
    if (root != nullptr) {
        delete_tree(root->left);
        delete_tree(root->right);
        delete root;
    }
}
int avl_balanced(Node_avl* tmp){
    int left_height, right_height;
    if(tmp->left != nullptr) left_height = tmp->left->height;
    else left_height = -1;
    if(tmp->right != nullptr) right_height = tmp->right->height;
    else right_height = -1;
    int difference = left_height - right_height;
    return difference;
}
int avl_height_calc(Node_avl* tmp){
    if (tmp == nullptr) return -1;
    return std::max(avl_height_calc(tmp->left), avl_height_calc(tmp->right)) + 1;
}
void left_rotation(Node_avl* &tmp){
    Node_avl* x = tmp;
    Node_avl* y = tmp->right;            // left rotation
    Node_avl* y_left = y->left;
    tmp = y;
    y->left = x;
    x->right = y_left;
    tmp->left->height = avl_height_calc(tmp->left);
    tmp->height = avl_height_calc(tmp);
}
void right_rotation(Node_avl* &tmp){
    Node_avl* x = tmp;
    Node_avl* y = tmp->left;            // right rotation
    Node_avl* y_right = y->right;
    tmp = y;
    y->right = x;
    x->left = y_right;
    tmp->right->height = avl_height_calc(tmp->right);
    tmp->height = avl_height_calc(tmp);
}

void avl_fixing(Node_avl* &root){
    int balance = avl_balanced(root);
    int balance_2;
    if(balance > 1){ // left-
        balance_2 = avl_balanced(root->left);
        if(balance_2 == -1) {
            left_rotation(root->left); // left-right case
        }
        root->height = avl_height_calc(root);
        right_rotation(root);
        root->height = avl_height_calc(root);
    }
    else if(balance < -1){ // right-
        balance_2 = avl_balanced(root->right);
        if(balance_2 == 1) {
            right_rotation(root->right); // right-left case
        }
        root->height = avl_height_calc(root);
        left_rotation(root);
        root->height = avl_height_calc(root);
    }
}

void avl_insert(Node_avl* &root, int element){
    if(element <= root->value){
        if(root->left == nullptr) {
            root->left = new Node_avl;
            root->left->value = element;
            root->height = avl_height_calc(root);
        }
        else{
            avl_insert(root->left, element);
            root->height = avl_height_calc(root);
        }
        avl_fixing(root);
    } else {
        if(root->right == nullptr) {
            root->right = new Node_avl;
            root->right->value = element;
            root->height = root->height = avl_height_calc(root);
        }
        else{
            avl_insert(root->right, element);
            root->height = avl_height_calc(root);
        }
        avl_fixing(root);
        root->height = avl_height_calc(root);
    }
}

void prn(Node_avl *ptr, int depth=0) {
    if (ptr) {
        prn(ptr->left, depth + 1);
        for (int i = 0 ; i < depth ; i++) {
            std::cout << "   ";
        }
        std::cout << ptr->value << " " << ptr->height << std::endl;

        prn(ptr->right, depth + 1);
    }
}


int check(Node_avl *ptr) {
    if (ptr) {
        int left = check(ptr->left);
        int right = check(ptr->right);

        int balance = left - right;

        assert( balance > -2 && balance < 2);

        int h = std::max(left, right) + 1;

        assert( h == ptr->height);
        return h;
    }
    return -1;
}

Node_avl* avl_build(std::vector<int>& numbers){
    Node_avl *root = new Node_avl;
    root->value = numbers[0];
    Node_avl *tmp = root;
    for(int i = 1; i < numbers.size(); i++){
        prn(root);
        std::cout << " >>>>>>>>>>>>>>>> " << std::endl;
        std::cout << numbers[i] << std::endl;
        std::cout << " ============== " << std::endl;
        avl_insert(root, numbers[i]);
        prn(root);

        std::cout << " <<<<<<<<<<<<<<< " << std::endl;
        check(root);
    }
    return root;
}
void avl_output(Node_avl* &tmp, std::vector<int>& sorted){
    if(tmp != nullptr){
        avl_output(tmp->left, sorted);
        sorted.push_back(tmp->value);
        avl_output(tmp->right, sorted);
    }
    return;
}
void avl(std::vector<int>& numbers){
    Node_avl* tmp = avl_build(numbers);
    Node_avl* tmp_ = tmp;
    numbers.clear();
    avl_output(tmp, numbers);
    delete_tree(tmp_);
}

#endif //PROJECT_1_2_AVL_H