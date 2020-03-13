#include <cstddef>  // std::size_t
#include <iomanip>   // std::setw
#include <iostream> // std::cout
#include <vector>   // std::vector

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

template < 
    template<typename, typename> typename Vec, 
    typename T, 
    typename Alloc
>
void fillVector(Vec<T, Alloc>& vec, T value = T()) {
    constexpr std::size_t fillSize = 1500;

    auto prevCapacity = vec.capacity();
    for (std::size_t i = 0; i < fillSize; ++i) {
        vec.push_back(value);
        auto newCapacity = vec.capacity();
        if (prevCapacity != newCapacity) {
            std::cout << "[ Добавление " << std::setw(4) << i + 1 << "-ого элемента ] Новая вместимость = " << std::setw(5) << newCapacity << std::endl;
            prevCapacity = newCapacity;
        }
    }
}


// Класс-наследник std::vector-а, который помогает переопределить политику роста std::vector
constexpr double MyVecFactor = 15;
template <typename T, typename Alloc>
struct MyVec final: public std::vector<T, Alloc> {
    static_assert(MyVecFactor > 1.0);

    using Base = std::vector<T, Alloc>;
    MyVec(int startSize = 0): Base{startSize} {}

    T& operator[] (std::size_t pos) {
        return Base::operator[](pos);
    }

    const T& operator[] (std::size_t pos) const {
        return Base::operator[](pos);
    }

    void push_back(const T& value) {
        grow();
        Base::push_back(value);
    }

    void push_back(T&& value) {
        grow();
        Base::push_back(value);
    }

    // TODO: other methods
private:
    void grow() {
        if (Base::capacity() == Base::size()) {
            Base::reserve(static_cast<std::size_t>(Base::size() * MyVecFactor));
        }
    }
};

template<typename T>
void printVec(const T& vec) {
    std::cout << "size     = " << vec.size() << std::endl;
    std::cout << "capacity = " << vec.capacity() << std::endl;
    std::cout << std::endl;
}

int main() {
    auto vec = std::vector<int, MyAllocator<int>>{};
    fillVector(vec);
    printVec(vec);

    std::cout << "Вызов функции shrink_to_fit" << std::endl;
    vec.shrink_to_fit();
    printVec(vec);

    std::cout << "Вызов функции reserve" << std::endl;
    vec.reserve(10000);
    printVec(vec);

    std::cout << "Вызов функции resize" << std::endl;
    vec.resize(10001);
    printVec(vec);

    std::cout << "Вызов функции clear" << std::endl;
    vec.clear();
    vec.shrink_to_fit();
    printVec(vec);

    return 0;
}