#include <iostream>
#include <chrono>

#include "tests.h"
#include "bst.h"
#include "avl.h"

long long time_measurement_bst(){
    std::pair<Node* &, Node_avl* &> roots = testing();
    using namespace std::chrono;
    auto start = std::chrono::steady_clock::now();
    bst_insert(roots.first, element);
    auto end = std::chrono::steady_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    return duration;
}

int main() {

    return 0;
}

