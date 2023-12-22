#include <iostream>
#include <chrono>

#include "tests.h"
#include "bst.h"
#include "avl.h"

void data_recording_ins(std::tuple<long long, long long> insertion_pair, std::string filename_b, std::string filename_a){
    std::ofstream fb_out(filename_b, std::ios::app);
    std::ofstream fa_out(filename_a, std::ios::app);

    fb_out << std::get<0>(insertion_pair) << std::endl;
    fa_out << std::get<1>(insertion_pair) << std::endl;

    fb_out.close();
    fa_out.close();
}

void time_measurement_insertion(std::vector<std::string> &words, std::string filename_b, std::string filename_a){
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

    data_recording_ins(duration, filename_b, filename_a);
}

void data_recording_search(std::tuple<long long, long long> search_pair, std::string filename_b, std::string filename_a){

    std::ofstream fb_out(filename_b, std::ios::app);
    std::ofstream fa_out(filename_a, std::ios::app);


    fb_out << std::get<0>(search_pair) << std::endl;
    fa_out << std::get<1>(search_pair) << std::endl;

    fb_out.close();
    fa_out.close();
}
void data_recording_search_if_not_ex(std::tuple<long long, long long> search_pair, std::string filename_b_, std::string filename_a_){
    std::ofstream fb_out(filename_b_, std::ios::app);
    std::ofstream fa_out(filename_a_, std::ios::app);


    fb_out << std::get<0>(search_pair) << std::endl;
    fa_out << std::get<1>(search_pair) << std::endl;

    fb_out.close();
    fa_out.close();
}


void time_measurement_searching(std::vector<std::string> &words, std::string random_word, std::string filename_b,
                                std::string filename_a, std::string filename_b_, std::string filename_a_){


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

    if(file) data_recording_search(duration, filename_a, filename_b);
    else data_recording_search_if_not_ex(duration, filename_b_, filename_a_);
}

int main() {
    for(int i = 0; i < 1000; i++){
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

        time_measurement_insertion(words_random, "bst_insert_time_taken_random.txt", "avl_insert_time_taken_random.txt");
        time_measurement_insertion(words_ordered, "bst_insert_time_taken_ordered.txt", "avl_insert_time_taken_ordered.txt");
        time_measurement_insertion(words_ordered_nearly, "bst_insert_time_taken_nearly.txt", "avl_insert_time_taken_nearly.txt");

        time_measurement_searching(words_random, word_from_tree, "bst_search_time_taken_random.txt",
                                   "avl_search_time_taken_random.txt", "bst_search_time_taken_non_existing_random.txt",
                                   "avl_search_time_taken_non_existing_random.txt");
        time_measurement_searching(words_ordered, word_from_tree_2, "bst_search_time_taken_ordered.txt",
                                   "avl_search_time_taken_ordered.txt", "bst_search_time_taken_non_existing_ordered.txt",
                                   "avl_search_time_taken_non_existing_ordered.txt");
        time_measurement_searching(words_ordered_nearly, word_from_tree_3, "bst_search_time_taken_nearly.txt",
                                   "avl_search_time_taken_nearly.txt", "bst_search_time_taken_non_existing_nearly.txt",
                                   "avl_search_time_taken_non_existing_nearly.txt");
        time_measurement_searching(words_random, random_word, "bst_search_time_taken_random.txt",
                                   "avl_search_time_taken_random.txt", "bst_search_time_taken_non_existing_random.txt",
                                   "avl_search_time_taken_non_existing_random.txt");
        time_measurement_searching(words_ordered, random_word, "bst_search_time_taken_ordered.txt",
                                   "avl_search_time_taken_ordered.txt", "bst_search_time_taken_non_existing_ordered.txt",
                                   "avl_search_time_taken_non_existing_ordered.txt");
        time_measurement_searching(words_ordered_nearly, random_word, "bst_search_time_taken_nearly.txt",
                                   "avl_search_time_taken_nearly.txt", "bst_search_time_taken_non_existing_nearly.txt",
                                   "avl_search_time_taken_non_existing_nearly.txt");


    }
    return 0;
}

