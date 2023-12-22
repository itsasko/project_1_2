#ifndef PROJECT_1_2_TESTS_H
#define PROJECT_1_2_TESTS_H

#include <fstream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <random>
#include <cassert>
#include "avl.h"
#include "bst.h"


std::string gen_random_word(int lower_bound, int upper_bound) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<int> dist_elements(lower_bound, upper_bound);
    std::uniform_int_distribution<int> dist_char(65, 90);

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
    std::uniform_int_distribution<int> dist_length(0, 100);
    std::uniform_int_distribution<int> dist_char(65, 90);
    std::vector<std::string> random_test;
    int test_vector_size = dist_elements(gen);
    for(int i = 0; i < test_vector_size; i++){
        int string_length = dist_elements(gen);
        std::string random_string;
        for (int j = 0; j < string_length; j++) {
            random_string.push_back(static_cast<char>(dist_char(gen)));
        }
        random_test.push_back(random_string);
        fout << random_string << " ";
    }
    f_out << test_vector_size << std::endl;
    fout << std::endl;
    fout.close();
    return random_test;
}
static std::vector<std::string> ordered_random_words_generator(int lower_bound, int upper_bound, std::string filename, std::string filename_sizes){

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
    }
    std::sort(random_test.begin(), random_test.end());
    for(auto i : random_test) fout << i << std::endl;
    fout << std::endl;
    f_out << test_vector_size << std::endl;
    fout.close();
    return random_test;
}

static std::vector<std::string> nearly_ordered_random_words_generator(int lower_bound, int upper_bound, std::string filename, std::string filename_sizes){

    std::random_device rd;
    std::mt19937 gen(rd());

    std::ofstream fout(filename, std::ios::app);
    std::ofstream f_out(filename_sizes, std::ios::app);

    std::uniform_int_distribution<int> dist_elements(lower_bound, upper_bound);
    std::uniform_int_distribution<int> dist_char(65, 122);
    std::vector<std::string> random_test;
    int test_vector_size = dist_char(gen);
    for(int i = 0; i < test_vector_size-11; i++){
        int string_length = dist_elements(gen);
        std::string random_string;
        for (int j = 0; j < string_length; j++) {
            random_string.push_back(static_cast<char>(dist_char(gen)));
        }
        random_test.push_back(random_string);
    }
    std::sort(random_test.begin(), random_test.end());
    for(int i = 0; i < 11; i++){
        int string_length = dist_elements(gen);
        std::string random_string;
        for (int j = 0; j < string_length; j++) {
            random_string.push_back(static_cast<char>(dist_char(gen)));
        }
        random_test.push_back(random_string);
    }
    for(auto i : random_test) fout << i << std::endl;
    fout << std::endl;
    f_out << test_vector_size << std::endl;
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

#endif //PROJECT_1_2_TESTS_H
