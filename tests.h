#ifndef PROJECT_1_2_TESTS_H
#define PROJECT_1_2_TESTS_H

#include <fstream>
#include <vector>
#include <algorithm>
#include <random>
#include <cassert>
#include "avl.h"
#include "bst.h"

static std::vector<int> random_numbers_generator(int lower_bound, int upper_bound, std::string filename, std::string filename_sizes){

    std::random_device rd;
    std::mt19937 gen(rd());

    std::ofstream fout(filename, std::ios::app);
    std::ofstream f_out(filename_sizes, std::ios::app);

    std::uniform_int_distribution<int> dist_elements(lower_bound, upper_bound);
    std::uniform_int_distribution<int> dist_size(1, 50000);
    std::vector<int> random_test;
    int test_vector_size = dist_size(gen);
    f_out << test_vector_size << std::endl;
    int element;
    for(int i = 0; i < test_vector_size; i++){
        element = dist_elements(gen);
        random_test.push_back(element);
        fout << element << " ";
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

void print_vector(std::vector<int> some_vector){
    for (auto i : some_vector) std::cout << i << " ";
    std::cout << std::endl;
}

void avl_testing(){
    std::vector<int> test(random_numbers_generator(-1000, 1000, "quick_sort_numbers.txt",
                                                   "quick_sort_sizes.txt"));

    std::vector<int> test2(test);
    std::sort(test2.begin(), test2.end());
    avl(test);

    for (auto x : test) {
        std::cout << x << ", ";
    }
    std::cout << std::endl;
    for (auto x : test2) {
        std::cout << x << ", ";
    }
    std::cout << std::endl;

    assert(test2 == test);

    if(passed_test(test)) std::cout << "PASSED" << std::endl;
    else std::cout << "NOT PASSED" << std::endl;

}
#endif //PROJECT_1_2_TESTS_H
