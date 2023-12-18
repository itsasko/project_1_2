#ifndef PROJECT_1_2_AVL_H
#define PROJECT_1_2_AVL_H

struct Node_avl {
    Node_avl(int x): value(x) {}
    int value;
    Node_avl *left = nullptr;
    Node_avl *right = nullptr;
    int height;
};

void delete_tree(Node_avl *root) {
    if (root != nullptr) {
        delete_tree(root->left);
        delete_tree(root->right);
        delete root;
    }
}
/* Node_avl* avl_build(std::vector<int>& numbers){
    Node_avl *root = new Node_avl;
    root->value = numbers[0];
    Node_avl *tmp = root;
    for(auto i : numbers){
        if(i > tmp->value) {
            tmp->right = new Node_avl;
            tmp->right->value = i;
            tmp = tmp->right;
        }
        else {
            tmp->left = new Node_avl;
            tmp->left->value = i;
            tmp = tmp->left;
        }
    }
    return root;
} */
/*
void ins_tree(Node_avl* tmp, int x){
    if(x > tmp->value){
        if(tmp->right != nullptr){
            ins_tree(tmp->right, x);
        }
        else tmp->right = new Node_avl(x);
    }
    else{ // x <= tmp->value
        if(tmp->left != nullptr){
            ins_tree(tmp->left, x);
        }
        else tmp->left = new Node_avl(x);
    }
} */
bool avl_balanced(){

}

void avl_insert(Node *root, int element){
    if(element <= root->value){
        if(root->left == nullptr) {
            Node* tmp = new Node;
            root->left = tmp;
            root->left->value = element;
            if(!avl_balanced); // rotate
        }
        else{
            avl_insert(root->left, element);
        }
    }
    if(element > root->value){
        if(root->right == nullptr) {
            Node* tmp = new Node;
            root->right = tmp;
            root->right->value = element;
            if(!avl_balanced); // rotate
        }
        else{
            avl_insert(root->right, element);
        }
    }
}

Node* avl_build(std::vector<int>& numbers){
    Node *root = new Node;
    root->value = numbers[0];
    Node *tmp = root;
    for(int i = 1; i < numbers.size(); i++){
        avl_insert(root, numbers[i]);
    }
    return root;
}

void avl_output(Node* &tmp, std::vector<int>& sorted){
    if(tmp != nullptr){
        avl_output(tmp->left, sorted);
        sorted.push_back(tmp->value);
        avl_output(tmp->right, sorted);
    }
    return;
}

void avl(std::vector<int>& numbers){
    Node* tmp = avl_build(numbers);
    Node* tmp_ = tmp;
    numbers.clear();
    avl_output(tmp, numbers);
    delete_tree(tmp_);
}

#endif //PROJECT_1_2_AVL_H
