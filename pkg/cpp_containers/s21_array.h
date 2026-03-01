#ifndef S21_ARRAY_H
#define S21_ARRAY_H

namespace S21 {

template <typename T, size_t capacity>
class Array {
   private:
    size_t m_size;
    T arr[capacity];

   public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* iterator;
    typedef const T* const_iterator;

   public:
    // конструктор по умолчанию
    Array();
    // конструктор инициализации списком
    Array(std::initializer_list<T> const& items);
    // конструктор копирования
    Array(const Array& other);
    // конструктор переноса
    Array(Array&& other);
    // деструктор
    ~Array() {}

    // перенос списка присваиванием
    Array<T, capacity>& operator=(Array&& other);

    // доступ к элементам
    T& at(size_t pos);
    T& operator[](size_t pos);
    const T& front();
    const T& back();
    iterator data();
    // проверка наполенности
    bool empty();
    size_t size();
    size_t max_size();
    // работа с итератором
    iterator begin();
    iterator end();
    // методы модификации
    void fill(const T& value);
    void swap(Array& other);
};

template <typename T, size_t capacity>
inline Array<T, capacity>::Array() {
    m_size = capacity;
}

template <typename T, size_t capacity>
inline Array<T, capacity>::Array(std::initializer_list<T> const& items) {
    m_size = capacity;
    size_t i = 0;
    for (auto it = items.begin(); it != items.end(); it++) {
        if (i >= m_size) break;
        arr[i++] = *it;
    }
}

template <typename T, size_t capacity>
inline Array<T, capacity>::Array(const Array& other) {
    m_size = capacity;
    for (size_t i = 0; i < other.m_size; ++i) {
        if (i >= m_size) break;
        arr[i] = other.arr[i];
    }
}

template <typename T, size_t capacity>
inline Array<T, capacity>::Array(Array&& other) {
    m_size = capacity;
    for (size_t i = 0; i < other.m_size; ++i) {
        if (i >= m_size) break;
        arr[i] = other.arr[i];
    }
    other.m_size = 0;
}

template <typename T, size_t capacity>
inline Array<T, capacity>& S21::Array<T, capacity>::operator=(Array&& other) {
    if (this != &other) {
        m_size = capacity;
        for (size_t i = 0; i < other.m_size; ++i) {
            if (i >= m_size) break;
            arr[i] = other.arr[i];
        }
        other.m_size = 0;
    }
    return *this;
}

template <typename T, size_t capacity>
inline T& Array<T, capacity>::at(size_t pos) {
    if (m_size <= pos) {
        throw std::range_error("Out of array");
    }
    return arr[pos];
}

template <typename T, size_t capacity>
inline T& Array<T, capacity>::operator[](size_t pos) {
    return at(pos);
}

template <typename T, size_t capacity>
inline const T& Array<T, capacity>::front() {
    if (m_size == 0) {
        throw std::runtime_error("Array is empty");
    }
    return arr[0];
}

template <typename T, size_t capacity>
inline const T& Array<T, capacity>::back() {
    if (m_size == 0) {
        throw std::runtime_error("Array is empty");
    }
    return arr[m_size - 1];
}

template <typename T, size_t capacity>
inline typename Array<T, capacity>::iterator Array<T, capacity>::data() {
    return arr;
}

template <typename T, size_t capacity>
inline bool Array<T, capacity>::empty() {
    return m_size == 0;
}

template <typename T, size_t capacity>
inline size_t Array<T, capacity>::size() {
    return m_size;
}

template <typename T, size_t capacity>
inline size_t Array<T, capacity>::max_size() {
    return std::numeric_limits<size_t>::max() / sizeof(T);
}

template <typename T, size_t capacity>
inline typename Array<T, capacity>::iterator Array<T, capacity>::begin() {
    return arr;
}

template <typename T, size_t capacity>
inline typename Array<T, capacity>::iterator Array<T, capacity>::end() {
    return arr + capacity;
}

template <typename T, size_t capacity>
inline void Array<T, capacity>::fill(const T& value) {
    for (size_t i = 0; i < m_size; ++i) {
        arr[i] = value;
    }
}

template <typename T, size_t capacity>
inline void Array<T, capacity>::swap(Array& other) {
    for (size_t i = 0; i < m_size; ++i) {
        T tmp = arr[i];
        arr[i] = other.arr[i];
        other.arr[i] = tmp;
    }
}

}  // namespace S21

#endif
