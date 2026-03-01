#ifndef S21_SET_H
#define S21_SET_H

namespace S21 {

template <typename Key>
class Set {
   private:
    struct node {
        node* parent;
        node* left;
        node* right;
        Key key;
        node(node* p, Key k)
            : parent(p), left(nullptr), right(nullptr), key(k) {}
        node(node* p, node* l, node* r, Key k)
            : parent(p), left(l), right(r), key(k) {}
    };

    node* root;
    size_t m_size;

   public:
    class SetIterator {
       private:
        node* ptr;

        node* prev_parent(node* tree) {
            if (!tree) {
                return nullptr;
            }
            if (!tree->parent) {
                return nullptr;
            }
            node* child = tree;
            node* current = child->parent;
            while (current && current->right != child) {
                child = current;
                current = child->parent;
            }
            return current;
        }
        node* next_parent(node* tree) {
            if (!tree) {
                return nullptr;
            }
            if (!tree->parent) {
                return nullptr;
            }
            node* child = tree;
            node* current = child->parent;
            while (current && current->left != child) {
                child = current;
                current = child->parent;
            }
            return current;
        }
        node* final_left(node* tree) {
            if (!tree) {
                return nullptr;
            }
            node* current = tree;
            while (current->left) current = current->left;
            return current;
        }
        node* final_right(node* tree) {
            if (!tree) {
                return nullptr;
            }
            node* current = tree;
            while (current->right) current = current->right;
            return current;
        }
        node* prev(node* tree) {
            if (!tree->left) {
                node* p = prev_parent(tree);
                if (p) {
                    return p;
                } else {
                    return nullptr;
                }
            } else {
                return final_right(tree->left);
            }
        }
        node* next(node* tree) {
            if (!tree->right) {
                node* p = next_parent(tree);
                if (p) {
                    return p;
                } else {
                    return nullptr;
                }
            } else {
                return final_left(tree->right);
            }
        }

       public:
        SetIterator() { ptr = nullptr; }
        SetIterator(node* node) { ptr = node; }
        ~SetIterator() {}

        Key& operator*() { return ptr->key; }
        SetIterator& operator++() {
            if (ptr) ptr = next(ptr);
            return *this;
        }
        SetIterator operator++(int) {
            SetIterator tmp = *this;
            ++(*this);
            return tmp;
        }
        SetIterator& operator--() {
            if (ptr) ptr = prev(ptr);
            return *this;
        }
        SetIterator operator--(int) {
            SetIterator tmp = *this;
            --(*this);
            return tmp;
        }
        bool operator==(const SetIterator& other) { return other.ptr == ptr; }
        bool operator!=(const SetIterator& other) { return other.ptr != ptr; }
    };

   private:
    void clear_tree(node* root);
    node* seek_insert_root(node* tree, const Key& value);
    node* find_tree(node* tree, const Key& key);
    node* final_left(node* tree);

   public:
    typedef Key key_value;
    typedef Key value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef SetIterator iterator;

   public:
    // конструктор по умолчанию
    Set();
    // конструктор инициализации списком
    Set(std::initializer_list<Key> items);
    // конструктор копирования
    Set(Set& other);
    // конструктор переноса
    Set(Set&& other);
    // деструктор
    ~Set();

    // оператор присваивания копированием
    Set& operator=(Set& other);
    // перенос списка присваиванием
    Set& operator=(Set&& other);

    // работа с итератором
    iterator begin();
    iterator end();
    // проверка наполненности
    bool empty();
    size_t size();
    size_t max_size();
    // изменение контейнера
    void clear();
    std::pair<Set<Key>::iterator, bool> insert(const value_type& value);
    void erase(iterator pos);
    void swap(Set& other);
    void merge(Set& other);
    // просмотр контейнера
    iterator find(const Key& key);
    bool contains(const Key& key);
};

template <typename Key>
inline void Set<Key>::clear_tree(node* root) {
    if (!root) return;
    clear_tree(root->left);
    clear_tree(root->right);
    delete root;
}

template <typename Key>
inline typename Set<Key>::node* Set<Key>::seek_insert_root(node* tree,
                                                           const Key& value) {
    if (!tree) return nullptr;
    if (value < tree->key) {
        if (!tree->left) {
            m_size++;
            tree->left = new node(tree, value);
            return tree->left;
        }
        return seek_insert_root(tree->left, value);
    } else if (value > tree->key) {
        if (!tree->right) {
            m_size++;
            tree->right = new node(tree, value);
            return tree->right;
        }
        return seek_insert_root(tree->right, value);
    }
    throw std::runtime_error("set contains a key");
}

template <typename Key>
inline typename Set<Key>::node* Set<Key>::find_tree(node* tree,
                                                    const Key& key) {
    if (!tree) return nullptr;
    node* left_ = find_tree(tree->left, key);
    if (left_) return left_;
    if (tree->key == key) return tree;
    node* right_ = find_tree(tree->right, key);
    if (right_) return right_;
    return nullptr;
}

template <typename Key>
inline typename Set<Key>::node* Set<Key>::final_left(node* tree) {
    if (!tree) return nullptr;
    node* current = tree;
    while (current->left) current = current->left;
    return current;
}

template <typename Key>
inline Set<Key>::Set() {
    root = nullptr;
    m_size = 0;
}

template <typename Key>
inline Set<Key>::Set(std::initializer_list<Key> items) {
    root = nullptr;
    m_size = 0;
    for (auto&& i : items) {
        insert(i);
    }
}

template <typename Key>
inline Set<Key>::Set(Set& other) {
    root = nullptr;
    m_size = 0;
    for (auto&& i : other) {
        insert(i);
    }
}

template <typename Key>
inline Set<Key>::Set(Set&& other) {
    root = other.root;
    m_size = other.m_size;
    other.root = nullptr;
    other.m_size = 0;
}

template <typename Key>
inline Set<Key>::~Set() {
    clear();
}

template <typename Key>
inline Set<Key>& Set<Key>::operator=(Set& other) {
    if (this != &other) {
        clear();
        for (auto&& i : other) {
            insert(i);
        }
    }
    return *this;
}

template <typename Key>
inline Set<Key>& Set<Key>::operator=(Set&& other) {
    if (this != &other) {
        clear();
        root = other.root;
        m_size = other.m_size;
        other.root = nullptr;
        other.m_size = 0;
    }
    return *this;
}

template <typename Key>
inline typename Set<Key>::iterator Set<Key>::begin() {
    return iterator(final_left(root));
}

template <typename Key>
inline typename Set<Key>::iterator Set<Key>::end() {
    return iterator(nullptr);
}

template <typename Key>
inline bool Set<Key>::empty() {
    return m_size == 0;
}

template <typename Key>
inline size_t Set<Key>::size() {
    return m_size;
}

template <typename Key>
inline size_t Set<Key>::max_size() {
    return std::numeric_limits<size_t>::max() / sizeof(node);
}

template <typename Key>
inline void Set<Key>::clear() {
    clear_tree(root);
    root = nullptr;
    m_size = 0;
}

template <typename Key>
inline typename std::pair<typename Set<Key>::iterator, bool> Set<Key>::insert(
    const value_type& value) {
    if (root == nullptr) {
        m_size = 1;
        root = new node(root, value);
        return std::make_pair(begin(), true);
    }
    node* item = seek_insert_root(root, value);
    return std::make_pair(iterator(item), true);
}

template <typename Key>
inline void Set<Key>::erase(Set<Key>::iterator pos) {
    Set<Key> tmp;
    auto beg = begin();
    while (beg != pos) {
        tmp.insert(*beg);
        beg++;
    }
    pos++;
    while (pos != nullptr && pos != end()) {
        tmp.insert(*pos);
        pos++;
    }
    swap(tmp);
}

template <typename Key>
inline void Set<Key>::swap(Set& other) {
    node* tmp = root;
    root = other.root;
    other.root = tmp;

    size_t sz = m_size;
    m_size = other.m_size;
    other.m_size = sz;
}

template <typename Key>
inline void Set<Key>::merge(Set& other) {
    for (auto&& i : other) {
        if (!contains(i)) insert(i);
    }
}

template <typename Key>
inline typename Set<Key>::iterator Set<Key>::find(const Key& key) {
    if (root == nullptr) {
        return iterator(nullptr);
    }
    node* left_ = find_tree(root->left, key);
    if (left_) return iterator(left_);
    if (root->key == key) return iterator(root);
    node* right_ = find_tree(root->right, key);
    if (right_) return iterator(right_);
    return iterator(nullptr);
}

template <typename Key>
inline bool Set<Key>::contains(const Key& key) {
    return find(key) != nullptr;
}

}  // namespace S21

#endif
