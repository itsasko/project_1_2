#include <iostream>
#include <chrono>

#include "tests.h"
#include "bst.h"
#include "avl.h"

void data_recording_ins(std::tuple<long long, long long> insertion_pair){
    std::ofstream fb_out("bst_insert_time_taken.txt");
    std::ofstream fa_out("avl_insert_time_taken.txt");

    fb_out << std::get<0>(insertion_pair) << std::endl;
    fb_out << std::get<1>(insertion_pair) << std::endl;

    fb_out.close();
    fa_out.close();
}

void time_measurement_insertion(std::tuple<Node* &, Node_avl* &> roots ){
    std::string random_word = gen_random_word(0, 1000);

    using namespace std::chrono;

    auto start = std::chrono::steady_clock::now();
    bst_insert(std::get<0>(roots), random_word);
    auto end = std::chrono::steady_clock::now();

    auto duration_bst_ins = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    start = std::chrono::steady_clock::now();
    avl_insert(std::get<1>(roots), random_word);
    end = std::chrono::steady_clock::now();

    auto duration_avl_ins = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::tuple<long long, long long> duration(duration_bst_ins, duration_avl_ins);

    data_recording_ins(duration);
}

void data_recording_search(std::tuple<long long, long long> search_pair, bool file){
    std::ofstream fb_out;
    std::ofstream fa_out;
    if(file){
        std::ofstream fb_out("bst_search_time_taken.txt");
        std::ofstream fa_out("avl_search_time_taken.txt");
    }
    else {
        std::ofstream fb_out("bst_search_time_taken_non_existing.txt");
        std::ofstream fa_out("avl_search_time_taken_non_existing.txt");
    }


    fb_out << std::get<0>(search_pair) << std::endl;
    fb_out << std::get<1>(search_pair) << std::endl;

    fb_out.close();
    fa_out.close();
}

void time_measurement_searching(std::tuple<Node* &, Node_avl* &> roots){
    std::string random_word = gen_random_word(0, 1000);

    using namespace std::chrono;

    auto start = std::chrono::steady_clock::now();
    bool res = bst_search(std::get<0>(roots), random_word);
    auto end = std::chrono::steady_clock::now();

    bool file;
    if(res) file = true;
    else file = false;

    auto duration_bst_ins = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    start = std::chrono::steady_clock::now();
    avl_search(std::get<1>(roots), random_word);
    end = std::chrono::steady_clock::now();

    auto duration_avl_ins = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::tuple<long long, long long> duration(duration_bst_ins, duration_avl_ins);

    data_recording_search(duration, file);
}

int main() {
    std::tuple<Node* &, Node_avl* &> roots_1 = testing_ordered();
    std::tuple<Node* &, Node_avl* &> roots_2 = testing_nearly_ordered();
    std::tuple<Node* &, Node_avl* &> roots_3 = testing_random();

    for(int i = 0; i < 10000; i++){
        time_measurement_insertion(roots_1);
        time_measurement_insertion(roots_2);
        time_measurement_insertion(roots_3);        time_measurement_insertion(roots_1);
        time_measurement_searching(roots_3);        time_measurement_insertion(roots_1);
        time_measurement_searching(roots_2);
        time_measurement_searching(roots_3);
    }
    return 0;
}

