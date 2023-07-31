#include <iostream>

#include "sSort.h"

int main() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(-999, 999);
    std::vector<int> v;
    std::generate_n(back_inserter(v), 20, bind(dist, gen));

    std::cout << "Before sort: " << std::showpos;
    for (auto e : v) std::cout << e << ' ';

    sSort(v.begin(), v.end());

    std::cout << "\nAfter sort : ";
    for (auto e : v) std::cout << e << ' ';
    std::cout << '\n';

    return 0;
}