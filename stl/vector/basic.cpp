#include <iostream> // std::cout
#include <string>   // std::string
#include <utility>  // std::pair, std::move
#include <vector>   // std::vector

using demo_pair = std::pair<int, std::string>;

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2> pair) {
    return os << "std::pair{" << pair.first << ", " << pair.second <<  "}";
}

template<typename T>
void printVecStat(const std::string& headline, const std::vector<T>& v) {
    // Блок печати общей информации
    std::cout << "===== " << headline << " =====" << std::endl;
    std::cout << "size = " << v.size() << std::endl;
    std::cout << "capacity = " << v.capacity() << std::endl;

    // Блок печати элементов
    for (const auto& elem: v) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // Строка - разделитель блоков
    std::cout << std::endl;
}

int main() {
    // Объявление и наполнение объектов класса std::vector
    {
        // Простое
        auto vec1 = std::vector<int>{};
        vec1.push_back(3);
        vec1.push_back(5);
        printVecStat("Простой vec1", vec1);

        // C++ 17
        auto vec2 = std::vector{"hello", "world", "!!!"}; 
        printVecStat("Объявление vec2 в стиле С++ 17", vec2);

        // std::initializer_list
        auto vec3 = std::vector< demo_pair >
        {
            {1, "string 1"},
            {2, "string 2"},
            {3, "string 3"} 
        };
        printVecStat("Объявление vec3 через список инициализации", vec3);
    }

    // Итераторы
    {
        auto vec = std::vector<int>{1, 2, 3};

        // в С++ итератор begin показывает на первый элемент
        //                end показывает на элемент, следующий за последним
        // vec == [begin, end)
        auto autoBegin = vec.begin();
        std::vector<int>::iterator begin = vec.begin();
        std::vector<int>::iterator end = vec.end();

        std::vector<int>::const_iterator cbegin = vec.begin();
        std::vector<int>::const_iterator cend = vec.end();
    }

    // Работа с элементами вектора
    {
        auto vec = std::vector<demo_pair>{};

        // Простая вставка назад
        auto my_pair = demo_pair{1, "1"};
        vec.push_back(my_pair);
        vec.push_back(std::move(demo_pair{2, "2"}));
        vec.push_back(std::pair{3, "3"}); // C++ 17

        // Создание объекта in-place, perfect forwarding
        vec.emplace_back(3, "3");

        // Вставка элемента в середину вектора
        vec.insert(vec.begin() + 1, std::pair{5, "5"});
        vec.emplace(vec.begin() + 1, 6, "6");

        printVecStat("Различные способы добавления элементов в вектор", vec);

        // Удаление элемента с конца вектора
        vec.pop_back();

        // Удаление элемента из середины вектора
        vec.erase(vec.begin() + 2); // O(n)

        printVecStat("Различные способы удаления элементов из вектора", vec);
    }

    return 0;
}