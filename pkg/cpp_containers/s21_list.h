#ifndef S21_LIST_H
#define S21_LIST_H

namespace S21 {

template <typename T>
class List {
   private:
    struct node {
        node* prev;
        node* next;
        T data;
        node(node* prev, node* next, T data)
            : prev(prev), next(next), data(data) {}
    };

    node* head;
    node* tail;

   public:
    class ListIterator {
       public:
        node* node_ptr;
        ListIterator() { this->node_ptr = nullptr; }
        ListIterator(node* node) { this->node_ptr = node; }
        ~ListIterator() {}

        T& operator*() { return this->node_ptr->data; }
        ListIterator& operator++() {
            if (this->node_ptr) this->node_ptr = this->node_ptr->next;
            return *this;
        }
        ListIterator operator++(int) {
            ListIterator tmp = *this;
            ++(*this);
            return tmp;
        }
        ListIterator& operator--() {
            if (this->node_ptr) this->node_ptr = this->node_ptr->prev;
            return *this;
        }
        ListIterator operator--(int) {
            ListIterator tmp = *this;
            --(*this);
            return tmp;
        }
        bool operator==(const ListIterator& other) {
            return other.node_ptr == this->node_ptr;
        }
        bool operator!=(const ListIterator& other) {
            return other.node_ptr != this->node_ptr;
        }
    };

   public:
    typedef T value_type;
    typedef T& reference;
    typedef const T& const_reference;
    typedef ListIterator iterator;

   public:
    // конструктор по умолчанию
    List();
    // конструктор инициализации списком
    List(std::initializer_list<T> items);
    // конструктор копирования
    List(const List& other);
    // конструктор переноса
    List(List&& other);
    // деструктор
    ~List();

    // перенос списка присваиванием
    List<T>& operator=(List&& other);

    // доступ к элементам
    const T& front();
    const T& back();
    // проверка наполенности
    bool empty();
    int size();
    // работа с итератором
    iterator begin();
    iterator end();
    // методы модификации
    void clear();
    iterator insert(iterator pos, const T& value);
    void erase(iterator pos);
    void push_front(const T& value);
    void pop_front();
    void push_back(const T& value);
    void pop_back();
    void swap(List& other);
    void merge(List& other);
    void splice(iterator pos, List& other);
    void reverse();
    void unique();
    void sort();
};

template <typename T>
inline List<T>::List() {
    head = tail = nullptr;
}

template <typename T>
inline List<T>::List(std::initializer_list<T> items) {
    head = tail = nullptr;
    for (const auto& item : items) {
        push_back(item);
    }
}

template <typename T>
inline List<T>::List(const List& other) {
    head = tail = nullptr;
    node* curr = other.head;
    while (curr) {
        push_back(curr->data);
        curr = curr->next;
    }
}

template <typename T>
inline List<T>::List(List&& other) {
    head = other.head;
    tail = other.tail;
    other.head = other.tail = nullptr;
}

template <typename T>
inline List<T>::~List() {
    clear();
}

template <typename T>
inline List<T>& List<T>::operator=(List&& other) {
    if (this != &other) {
        clear();
        this->head = other.head;
        this->tail = other.tail;
        other.head = other.tail = nullptr;
    }
    return *this;
}

template <typename T>
inline const T& List<T>::front() {
    return tail->data;
}

template <typename T>
inline const T& List<T>::back() {
    return head->data;
}

template <typename T>
inline bool List<T>::empty() {
    return !head && !tail;
}

template <typename T>
inline int List<T>::size() {
    int s = 0;
    node* tmp = head;
    while (tmp) {
        tmp = tmp->next;
        s++;
    }
    return s;
}

template <typename T>
inline typename List<T>::iterator List<T>::begin() {
    return iterator(head);
}

template <typename T>
inline typename List<T>::iterator List<T>::end() {
    return iterator();
}

template <typename T>
inline void List<T>::clear() {
    while (head) {
        node* tmp = head;
        head = head->next;
        delete tmp;
    }
    tail = nullptr;
}

template <typename T>
inline typename List<T>::iterator List<T>::insert(iterator pos,
                                                  const T& value) {
    node* curr = pos.node_ptr;
    if (curr) {
        node* node_;
        if (curr->next) {
            node* next = curr->next;
            node_ = new node(curr, next, value);
            curr->next = next->prev = node_;
        } else {
            node_ = new node(curr, nullptr, value);
            curr->next = tail = node_;
        }
        return iterator(node_);
    }
    return iterator();
}

template <typename T>
inline void List<T>::erase(iterator pos) {
    node* curr = pos.node_ptr;
    if (curr) {
        if (!curr->prev) {
            pop_front();
        } else if (!curr->next) {
            pop_back();
        } else {
            node* prev = curr->prev;
            node* next = curr->next;
            delete curr;
            prev->next = next;
            next->prev = prev;
        }
    }
}

template <typename T>
inline void List<T>::push_back(const T& value) {
    if (empty()) {
        node* node_ = new node(nullptr, nullptr, value);
        head = tail = node_;
    } else {
        node* node_ = new node(tail, nullptr, value);
        tail->next = node_;
        tail = node_;
    }
}

template <typename T>
inline void List<T>::pop_back() {
    if (tail) {
        node* tmp = tail;
        if (tmp->prev) {
            tail = tmp->prev;
            tail->next = nullptr;
        } else {
            head = tail = nullptr;
        }
        delete tmp;
    }
}

template <typename T>
inline void List<T>::push_front(const T& value) {
    if (empty()) {
        node* node_ = new node(nullptr, nullptr, value);
        head = tail = node_;
    } else {
        node* node_ = new node(nullptr, head, value);
        head->prev = node_;
        head = node_;
    }
}

template <typename T>
inline void List<T>::pop_front() {
    if (head) {
        node* tmp = head;
        if (tmp->next) {
            head = tmp->next;
            head->prev = nullptr;
        } else {
            head = tail = nullptr;
        }
        delete tmp;
    }
}

template <typename T>
inline void List<T>::swap(List& other) {
    node* node_;
    node_ = head;
    head = other.head;
    other.head = node_;
    node_ = tail;
    tail = other.tail;
    other.tail = node_;
}

template <typename T>
inline void List<T>::merge(List& other) {
    if (other.empty()) {
        return;
    }
    if (empty()) {
        head = other.head;
        tail = other.tail;
        other.head = nullptr;
        other.tail = nullptr;
        return;
    }
    tail->next = other.head;
    other.head->prev = tail;
    tail = other.tail;
    other.head = nullptr;
    other.tail = nullptr;
}

template <typename T>
inline void List<T>::splice(iterator pos, List& other) {
    if (pos == nullptr) {
        return;
    }
    node* node_ = pos.node_ptr;
    if (!other.empty()) {
        if (node_->prev == nullptr) {
            // transfer to the very begining
            other.tail->next = node_;
            node_->prev = other.tail;
            head = other.head;
        } else {
            // transfer to the middle
            node* prev_ = node_->prev;
            node* next_ = node_;

            other.head->prev = prev_;
            prev_->next = other.head;

            other.tail->next = next_;
            next_->prev = other.tail;
        }
        other.head = nullptr;
        other.tail = nullptr;
    }
}

template <typename T>
inline void List<T>::reverse() {
    if (!empty()) {
        List<T> tmp;
        node* curr = head;
        while (curr) {
            tmp.push_front(curr->data);
            curr = curr->next;
        }
        *this = std::move(tmp);
    }
}

template <typename T>
inline void List<T>::unique() {
    if (!empty()) {
        List<T> tmp;
        bool first = true;
        T& prev_data = head->data;
        node* curr = head;
        while (curr) {
            if (first || prev_data != curr->data) {
                tmp.push_back(curr->data);
                prev_data = curr->data;
            }
            curr = curr->next;
            first = false;
        }
        *this = std::move(tmp);
    }
}

// Insertion Sort
template <typename T>
inline void List<T>::sort() {
    if (size() > 1) {
        node* sh = head;
        node* nsh = head->next;
        sh->next = nullptr;
        tail = sh;
        while (nsh) {
            node* gt_curr = nullptr;
            node* curr = sh;
            while (curr) {
                if (curr->data >= nsh->data) {
                    gt_curr = curr;
                    break;
                }
                curr = curr->next;
            }

            node* new_item = nsh;
            nsh = nsh->next;
            if (!gt_curr) {
                tail->next = new_item;
                new_item->prev = tail;
                new_item->next = nullptr;
                tail = new_item;
            } else {
                node* new_prev = gt_curr->prev;
                node* new_next = gt_curr;

                new_item->prev = new_prev;
                new_item->next = new_next;
                gt_curr->prev = new_item;
                if (new_prev) {
                    new_prev->next = new_item;
                } else {
                    sh = new_item;
                    head = new_item;
                }
            }
        }
    }
}

}  // namespace S21

#endif
