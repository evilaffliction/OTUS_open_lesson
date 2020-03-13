#include <iostream>         // std::cout
#include <unordered_map>    // std::unordered_map
#include <string>           // std::string

struct SimpleStruct {
    int i = 0;
    std::string s = "";
};

struct MyStruct {
    MyStruct() = default;
    MyStruct(int i, const std::string& s): i{i}, s{s} {}

    int i = 0;
    std::string s = "";
};

template<class T> class MyHash;
template<>
class MyHash<MyStruct> {
public:
    size_t operator()(const MyStruct &mstruct) const
    {
        size_t h1 = std::hash<int>()(mstruct.i);
        size_t h2 = std::hash<std::string>()(mstruct.s);
        return h1 ^ (h2 << 1);
    }
};


int main() {
    auto goodHashtable = std::unordered_map<MyStruct, int, MyHash<MyStruct>>{};
    // auto simpleHashTable = std::unordered_map<SimpleStruct, int>{};
    // auto simpleHashTable = std::unordered_map<SimpleStruct, int, std::hash<SimpleStruct>>{};
}