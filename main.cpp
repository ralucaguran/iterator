#include <iostream>
#include "iterator.h"


int main() {
    homemade::Vector<int> v(5);
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);
    homemade::Iterator<int> it(v);
    std::cout << *it << std::endl;
    ++it;
    it++;
    std::cout << *it << std::endl;

    homemade::Iterator<int> it2 = v.begin();
    while (it2.hasNext()) {
        std::cout << it2.next() << std::endl;
    }

    try {
        std::cout << it2.next() << std::endl;
    }
    catch (std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }

    for (auto it3 = v.begin(); it3 != v.end(); ++it3) {
        std::cout << *it3 << std::endl;
    }

    return 0;
}

