#ifndef PROJECT_1_2_TESTS_H
#define PROJECT_1_2_TESTS_H

#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>
#include "avl.h"
#include "bst.h"


std::string random_word(int lower_bound, int upper_bound) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dist_elements(lower_bound, upper_bound);
    std::uniform_int_distribution<int> dist_char(65, 122);

    int string_length = dist_elements(gen);
    std::string random_string;
    for (int j = 0; j < string_length; j++) {
        random_string.push_back(static_cast<char>(dist_char(gen)));
    }

    return random_string;
}

static std::vector<std::string> random_words_generator(int lower_bound, int upper_bound, std::string filename, std::string filename_sizes){

    std::random_device rd;
    std::mt19937 gen(rd());

    std::ofstream fout(filename, std::ios::app);
    std::ofstream f_out(filename_sizes, std::ios::app);

    std::uniform_int_distribution<int> dist_elements(lower_bound, upper_bound);
    std::uniform_int_distribution<int> dist_char(65, 122);
    std::vector<std::string> random_test;
    int test_vector_size = dist_char(gen);
    for(int i = 0; i < test_vector_size; i++){
        int string_length = dist_elements(gen);
        std::string random_string;
        for (int j = 0; j < string_length; j++) {
            random_string.push_back(static_cast<char>(dist_char(gen)));
        }
        random_test.push_back(random_string);
        fout << random_string << " ";
    }
    fout << std::endl;
    fout.close();
    return random_test;
}
static bool passed_test(std::vector<int> test){
    bool isPassed = true;
    for(int i = 1; i < test.size(); i++){
        if(test[i] < test[i-1]){
            isPassed = false;
        }
    }
    return isPassed;
}

std::pair<Node* &, Node_avl* &> testing(){
    std::vector<std::string> words(random_words_generator(-1000, 1000, "words.txt",
                                                 "words_amount.txt"));

    Node_avl* avl_root = avl_build(words);
    Node* bst_root = bst_build(words);
    std::pair<Node* &, Node_avl* &> roots(bst_root, avl_root);
    return roots;

}
#endif //PROJECT_1_2_TESTS_H
