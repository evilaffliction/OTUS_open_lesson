#include <iostream>         // std::cout
#include <map>              // std::map
#include <string>           // std::string
#include <utility>          // std::pair

int main() {
    auto hm = std::map<int, std::string>{};
    hm[1]  = "one";
    hm[2]  = "two";
    hm[3]  = "tree";
    hm[4]  = "four";
    hm[5]  = "five";
    hm[6]  = "six";
    hm[7]  = "seven";
    hm[8]  = "eight";
    hm[9]  = "nine";
    hm[10] = "ten";

    for (const std::pair<int, std::string>& elem: hm) {
        std::cout << elem.first << ":" << elem.second << std::endl;
    }

    return 0;
}