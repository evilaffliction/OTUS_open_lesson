#include <iostream>         // std::cout
#include <unordered_map>    // std::unordered_map
#include <string>           // std::string
#include <utility>          // std::pair, std::move

void printElements(const std::unordered_map<int, std::string>& hm) {
    for (const auto& elem: hm) {
    // for (const std::pair<int, std::string>& elem: hm) {
        std::cout << elem.first << ":" << elem.second << std::endl;
    }
}

int main() {
    auto hm = std::unordered_map<int, std::string>{};
    hm[1]  = "один";
    hm[2]  = "два";
    hm[3]  = "три";
    hm[4]  = "четыре";
    hm[5]  = "пять";
    hm[6]  = "шесть";
    hm[7]  = "семь";
    hm[8]  = "восемь";
    hm[9]  = "девять";
    hm[10] = "десять";
    printElements(hm);

    std::cout << std::endl;
    std::cout << "hm[1] = " << hm[1] << std::endl;

    std::cout << std::endl;
    {
        const auto& chm = hm;
        std::cout << "chm[1] = " << chm.at(1) << std::endl;
        try {
            std::cout << "chm[11] = " << chm.at(11) << std::endl;
        } catch(...) {
            std::cout << "Не удалось получить доступ к chm[11]" << std::endl;
        }
        
        auto it = chm.find(2);
        if (it != chm.end()) {
            std::cout << "chm[2] = " << it->second << std::endl;
        }
    }
    std::cout << std::endl;

    hm.emplace(11, "одиннадцать");
    hm.try_emplace(12, "двенадцать");
    

    auto node = hm.extract(12);
    node.key() = 13;
    hm.insert(std::move(node));
    printElements(hm);

    auto it = hm.find(1);
    if (it != hm.end()) {
        it->second = -1;
    }
    hm.erase(it);
    hm.reserve(100);

    return 0;
}