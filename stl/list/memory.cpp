#include <cmath>    // std::abs
#include <iomanip>   // std::setw
#include <iostream> // std::cout
#include <list>     // std::list

// Аллокатор - класс, slave, который используется контейнером для выделения места
template <typename T>
struct MyAllocator {
    using value_type = T;
    MyAllocator() = default;

    template <typename U>
    MyAllocator(const MyAllocator<U>&) {}

    T* allocate(std::size_t n) {
        std::cout << "=== Выделение куска памяти объемом " << std::setw(5) << n << std::endl;
        auto data = ::operator new(n * sizeof(T));
        return static_cast<T*>(data);
    }

    void deallocate(T* p, std::size_t n) {
        std::cout << "=== Удаление  куска памяти объемом " << std::setw(5) << n << std::endl;
        ::operator delete(p);
    }
};

template <template<typename, typename> typename List, typename T, typename Alloc>
void printBigDistances(const List<T, Alloc>& l) {
    const int* prevAddress = 0;

    int elemNum = 0;
    for (const int& elem: l) {
        auto* newAddress = &elem;
        if (elemNum > 0 && std::abs(newAddress - prevAddress) > 10000) {
            prevAddress = newAddress;
            std::cout << "Большое расстояние между элементами " << elemNum - 1 << " и " << elemNum << std::endl;
        }
        ++elemNum;
    }
}

int main() {
    {
        std::cout << "Нахождение большого расстояния в памяти между элементами списка" << std::endl;
        auto l = std::list<int>{};
        for (int i = 0; i < 3000; ++i) {
            l.push_back(i);
            l.push_front(-i);
        }

        printBigDistances(l);
        std::cout << std::endl;
    }

    {
        {
            std::cout << "Как список выделяет себе память" << std::endl;
            auto l = std::list<int, MyAllocator<int>>{};
            for (int i = 0; i < 3; ++i) {
                l.push_back(i);
            }
        }
        std::cout << std::endl;
    }

    {
        auto l = std::list<int, MyAllocator<int>>{};
        
        l.resize(3);
        auto begin = l.begin();
        for (int i = 0; i < 3; ++i) {
            *begin = i;
            ++begin;
        }
    }

    return 0;
}