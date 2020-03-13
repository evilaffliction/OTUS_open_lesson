#include <iostream> // std::cout
#include <list>     // std::list

template <
    template<typename, typename> typename List,
    typename T, typename Alloc>
void printList(const List<T, Alloc>& l) {
    std::cout << "size = " << l.size() << std::endl;
    for (const auto& elem: l) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;

    // Дополнительная линия разделения
    std::cout << std::endl;
}

int main() {
    auto l = std::list<int>{};

    std::cout << "Заполнение std::list" << std::endl;
    // Добавление элементов одного конца
    l.push_back(1);     // 1
    l.emplace_back(2);  // 1, 2

    // Добавление элементов с другого конца
    l.push_front(3);    // 3, 1, 2
    l.emplace_front(4); // 4, 3, 1, 2

    // Добавление элементов в середину
    l.insert(++l.begin(), 5); // 4, 5, 3, 1, 2
    l.insert((++l.rbegin()).base(), 6); // 4, 5, 3, 1, 6, 2

    printList(l);

    std::cout << "Операция reverse" << std::endl;
    l.reverse();  // 2, 6, 1, 3, 5, 4
    printList(l);

    std::cout << "Операция sort" << std::endl;
    l.sort();     // 1, 2, 3, 4, 5, 6
    printList(l);

    std::cout << "Операция merge" << std::endl;
    auto l2 = std::list{1, 1, 3, 9, -2};
    l2.sort();
    l.merge(l2);
    printList(l);

}