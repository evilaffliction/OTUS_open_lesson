#include <iostream> // std::cout
#include <vector>   // std::vector

int main() {
    auto v = std::vector<bool>{true, true, true, false}; // -> int8 00001110 vs 4 int8
    // auto v = std::vector<int>{1, 2, 3, 4};

    for (auto b = v.begin(), e = v.end(); b != e; ++b) {
        std::cout << "elem = " << *b << std::endl;
    }
    auto it = v.begin() + 2;
    std::cout << "it = " << *it << std::endl;

    std::cout << "vec size = " <<v.size() << std::endl;
    
    return 0;
}