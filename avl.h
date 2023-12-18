#ifndef PROJECT_1_2_AVL_H
#define PROJECT_1_2_AVL_H

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

void left_rotation(Node_avl* &tmp, int subtree){ // subtree > 1 => left-right; subtree < -1 => left-left
    if(subtree > 1){
        Node_avl* x = tmp->right;
        Node_avl* y = tmp->right->right;            // left-left rotation
        Node_avl* y_left = y->left;
        tmp->right = y;
        y->left = x;
        x->right = y_left;
    }
    else { //subtree < -1
        Node_avl* x = tmp->left;
        Node_avl* y = nullptr;
        Node_avl* y_left = nullptr;
        if(x != nullptr) {          // left-right rotation
            y = tmp->left->right;
            y_left = y->left;
        }
        tmp->left = y;
        y->left = x;
        x->right = y_left;
    }
}
void right_rotation(Node_avl* &tmp, int subtree){ // subtree > 1 => right-right; subtree < -1 => right-left
    if(subtree > 1){
        Node_avl* x = tmp->right;
        Node_avl* y = tmp->right->left;            // right-left rotation
        Node_avl* y_right = y->right;
        tmp->right = y;
        y->right = x;
        x->left = y_right;
    }
    else { //subtree < -1
        Node_avl* x = tmp->left;
        Node_avl* y = nullptr;
        Node_avl* y_right = nullptr;
        if(x != nullptr) {          // right-right rotation
            y = tmp->left->left;
            y_right = y->right;
        }
        tmp->left = y;
        y->right = x;
        x->left = y_right;
    }
}

void avl_insert(Node_avl *root, int element){
    if(element <= root->value){
        if(root->left == nullptr) {
            root->left = new Node_avl;
            root->left->value = element;
            root->height = avl_height_calc(root);
            int balance = avl_balanced(root->left);
            if(balance < -1 || balance > 1){
                left_rotation(root, balance);
            } // left rotation
        }
        else{
            avl_insert(root->left, element);
        }
    }
    if(element > root->value){
        if(root->right == nullptr) {
            root->right = new Node_avl;
            root->right->value = element;
            root->height = avl_height_calc(root);
            int balance = avl_balanced(root->right);
            right_rotation(root, balance);
        } // right rotation
        else{
            avl_insert(root->right, element);
        }
    }
}

Node_avl* avl_build(std::vector<int>& numbers){
    Node_avl *root = new Node_avl;
    root->value = numbers[0];
    Node_avl *tmp = root;
    for(int i = 1; i < numbers.size(); i++){
        avl_insert(root, numbers[i]);
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
