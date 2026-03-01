#ifndef S21_VECTOR_H
#define S21_VECTOR_H

namespace S21 {

template <typename T>
class Vector {
   private:
    size_t m_size;
    size_t m_capacity;
    T* arr;

   private:
    void reserve_more_capacity(size_t size);

   public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef T* iterator;
    typedef const T* const_iterator;

   public:
    // конструктор по умолчанию
    Vector() : m_size(0), m_capacity(0), arr(nullptr) {}
    // вектор заданного размера
    Vector(size_t n);
    // конструктор инициализации списком
    Vector(std::initializer_list<T> const& items);
    // конструктор копирования
    Vector(const Vector& other);
    // конструктор переноса
    Vector(Vector&& other);
    // деструктор
    ~Vector() { clear(); }

    // перенос списка присваиванием
    Vector<T>& operator=(Vector&& other);

    // доступ к элементам
    T& at(size_t pos);
    T& operator[](size_t pos);
    const T& front();
    const T& back();
    T* data();
    // проверка наполенности
    bool empty();
    size_t size();
    size_t max_size();
    void reserve(size_t size);
    size_t capacity();
    void shrink_to_fit();
    // работа с итератором
    iterator begin();
    iterator end();
    // методы модификации
    void clear();
    iterator insert(iterator pos, const T& value);
    void erase(iterator pos);
    void push_tail(const T& value);
    void pop_tail();
    void swap(Vector& other);
};

template <typename T>
inline void Vector<T>::reserve_more_capacity(size_t size) {
    if (size > m_capacity) {
        T* buff = new T[size];
        for (size_t i = 0; i < m_size; ++i) {
            buff[i] = std::move(arr[i]);
        }
        delete[] arr;
        arr = buff;
        m_capacity = size;
    }
}

template <typename T>
inline Vector<T>::Vector(size_t n) {
    if (n == 0) {
        throw std::runtime_error("wrong vector capacity");
    }
    m_size = n;
    m_capacity = n;
    arr = new T[n];
}

template <typename T>
inline Vector<T>::Vector(std::initializer_list<T> const& items) {
    arr = new T[items.size()];
    size_t i = 0;
    for (auto it = items.begin(); it != items.end(); ++it) {
        arr[i++] = *it;
    }
    m_size = m_capacity = items.size();
}

template <typename T>
inline Vector<T>::Vector(const Vector& other) {
    m_size = other.m_size;
    m_capacity = other.m_size;
    arr = m_size ? new T[m_size] : nullptr;
    for (size_t i = 0; i < m_size; ++i) {
        arr[i] = other.arr[i];
    }
}

template <typename T>
inline Vector<T>::Vector(Vector&& other) {
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    arr = other.arr;
    other.m_size = 0;
    other.m_capacity = 0;
    other.arr = nullptr;
}

template <typename T>
inline Vector<T>& Vector<T>::operator=(Vector&& other) {
    if (this != &other) {
        clear();
        m_size = other.m_size;
        m_capacity = other.m_capacity;
        arr = other.arr;
        other.m_size = 0;
        other.m_capacity = 0;
        other.arr = nullptr;
    }
    return *this;
}

template <typename T>
inline T& Vector<T>::at(size_t pos) {
    if (m_size <= pos) {
        throw std::range_error("out of vector");
    }
    return arr[pos];
}

template <typename T>
inline T& Vector<T>::operator[](size_t pos) {
    return at(pos);
}

template <typename T>
inline const T& Vector<T>::front() {
    if (m_size == 0) {
        throw std::runtime_error("vector is empty");
    }
    return arr[0];
}

template <typename T>
inline const T& Vector<T>::back() {
    if (m_size == 0) {
        throw std::runtime_error("vector is empty");
    }
    return arr[m_size - 1];
}

template <typename T>
inline T* Vector<T>::data() {
    return arr;
}

template <typename T>
inline bool Vector<T>::empty() {
    return m_size == 0;
}

template <typename T>
inline size_t Vector<T>::size() {
    return m_size;
}

template <typename T>
inline size_t Vector<T>::max_size() {
    return std::numeric_limits<size_t>::max() / sizeof(T);
}

template <typename T>
inline void Vector<T>::reserve(size_t size) {
    reserve_more_capacity(m_capacity + size);
}

template <typename T>
inline size_t Vector<T>::capacity() {
    return m_capacity;
}

template <typename T>
inline void Vector<T>::shrink_to_fit() {
    T* buff = new T[m_size];
    for (size_t i = 0; i < m_size; ++i) {
        buff[i] = arr[i];
    }
    delete[] arr;
    arr = buff;
    m_capacity = m_size;
}

template <typename T>
inline typename Vector<T>::iterator Vector<T>::begin() {
    return arr;
}

template <typename T>
inline typename Vector<T>::iterator Vector<T>::end() {
    return arr ? arr + m_size : nullptr;
}

template <typename T>
inline void Vector<T>::clear() {
    delete[] arr;
    m_size = 0;
    m_capacity = 0;
    arr = nullptr;
}

template <typename T>
inline typename Vector<T>::iterator Vector<T>::insert(iterator pos,
                                                      const T& value) {
    if (empty()) {
        push_tail(value);
        return arr;
    } else {
        size_t i = 0;
        T* buff = new T[m_size + 1];
        for (T* p = arr; p <= pos; ++p) {
            buff[i++] = *p;
        }
        buff[i++] = value;
        for (T* p = (pos + 1); p < (arr + m_size); ++p) {
            buff[i++] = *p;
        }
        delete[] arr;
        arr = buff;
        m_size = m_size + 1;
        m_capacity = m_size;
        return pos + 1;
    }
}

template <typename T>
inline void Vector<T>::erase(iterator pos) {
    if (pos == nullptr) return;
    if (pos == (arr + m_size - 1)) {
        pop_tail();
    } else {
        T* ps = pos;
        for (T* p = (pos + 1); p < (arr + m_size); ++p) {
            *ps = *p;
            ps++;
        }
        m_size = m_size - 1;
    }
}

template <typename T>
inline void Vector<T>::push_tail(const T& value) {
    if (!arr) {
        m_capacity = 10;
        arr = new T[m_capacity];
    } else {
        if (m_size == m_capacity) {
            reserve_more_capacity(m_capacity + 10);
        }
    }
    arr[m_size++] = value;
}

template <typename T>
inline void Vector<T>::pop_tail() {
    if (m_size == 0) {
        throw std::runtime_error("vector is empty");
    }
    m_size--;
}

template <typename T>
inline void Vector<T>::swap(Vector& other) {
    T* ptr = arr;
    arr = other.arr;
    other.arr = ptr;

    size_t tmp_s = m_size;
    m_size = other.m_size;
    other.m_size = tmp_s;

    size_t tmp_c = m_capacity;
    m_capacity = other.m_capacity;
    other.m_capacity = tmp_c;
}

}  // namespace S21

#endif
