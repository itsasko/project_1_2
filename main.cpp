#include <iostream>
#include <chrono>

#include "tests.h"
#include "bst.h"
#include "avl.h"

void data_recording_ins(std::tuple<long long, long long> insertion_pair){
    std::ofstream fb_out("bst_insert_time_taken.txt", std::ios::app);
    std::ofstream fa_out("avl_insert_time_taken.txt", std::ios::app);

    fb_out << std::get<0>(insertion_pair) << std::endl;
    fb_out << std::get<1>(insertion_pair) << std::endl;

    fb_out.close();
    fa_out.close();
}

void time_measurement_insertion(std::vector<std::string> &words){
    using namespace std::chrono;

    auto start = std::chrono::steady_clock::now();
    bst_build(words);
    auto end = std::chrono::steady_clock::now();

    auto duration_bst_ins = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    duration_bst_ins /= words.size();

    start = std::chrono::steady_clock::now();
    avl_build(words);
    end = std::chrono::steady_clock::now();

    auto duration_avl_ins = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    duration_avl_ins /= words.size();

    std::tuple<long long, long long> duration(duration_bst_ins, duration_avl_ins);

    data_recording_ins(duration);
}

void data_recording_search(std::tuple<long long, long long> search_pair){
    std::ofstream fb_out("bst_search_time_taken.txt", std::ios::app);
    std::ofstream fa_out("avl_search_time_taken.txt", std::ios::app);


    fb_out << std::get<0>(search_pair) << std::endl;
    fb_out << std::get<1>(search_pair) << std::endl;

    fb_out.close();
    fa_out.close();
}
void data_recording_search_if_not_ex(std::tuple<long long, long long> search_pair){
    std::ofstream fb_out("bst_search_time_taken_non_existing.txt", std::ios::app);
    std::ofstream fa_out("avl_search_time_taken_non_existing.txt", std::ios::app);


    fb_out << std::get<0>(search_pair) << std::endl;
    fb_out << std::get<1>(search_pair) << std::endl;

    fb_out.close();
    fa_out.close();
}


void time_measurement_searching(std::vector<std::string> &words, std::string random_word){


    using namespace std::chrono;

    Node* root_bst = bst_build(words);
    Node_avl* root_avl = avl_build(words);

    auto start = std::chrono::steady_clock::now();
    bool res = bst_search(root_bst, random_word);
    auto end = std::chrono::steady_clock::now();

    bool file;
    if(res) file = true;
    else file = false;

    auto duration_bst_ins = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    start = std::chrono::steady_clock::now();
    avl_search(root_avl, random_word);
    end = std::chrono::steady_clock::now();

    auto duration_avl_ins = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    std::tuple<long long, long long> duration(duration_bst_ins, duration_avl_ins);

    if(file) data_recording_search(duration);
    else data_recording_search_if_not_ex(duration);
}

int main() {
    for(int i = 0; i < 100; i++){
        std::vector<std::string> words_random(random_words_generator(1, 1000, "words_random.txt",
                                                                     "words_random_amount_2.txt"));
        std::vector<std::string> words_ordered(ordered_random_words_generator(1, 1000, "words_ordered.txt",
                                                                      "words_ordered_amount_2.txt"));
        std::vector<std::string> words_ordered_nearly(nearly_ordered_random_words_generator(1, 1000, "words_nearly.txt",
                                                                             "words_ordered_nearly_amount_2.txt"));
        std::string random_word = gen_random_word(0, 1000);
        std::string word_from_tree = words_random[0];
        std::string word_from_tree_2 = words_ordered[0];
        std::string word_from_tree_3 = words_ordered_nearly[0];
        time_measurement_insertion(words_random);
        time_measurement_insertion(words_ordered);
        time_measurement_insertion(words_ordered_nearly);
        time_measurement_searching(words_random, word_from_tree);
        time_measurement_searching(words_ordered, word_from_tree_2);
        time_measurement_searching(words_ordered_nearly, word_from_tree_3);
        time_measurement_searching(words_random, random_word);
        time_measurement_searching(words_ordered, random_word);
        time_measurement_searching(words_ordered_nearly, random_word);
    }
    return 0;
}

