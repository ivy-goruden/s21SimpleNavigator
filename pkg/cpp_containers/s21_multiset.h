#include <cstddef>
namespace S21 {
template <typename T>
class multiset {
    using size_type = size_t;

   private:
    class Node {
       public:
        T value;
        Node *next;
        Node *prev;
        Node(T val) {
            value = val;
            prev = next = nullptr;
        }
    };
    Node *head;
    Node *tail;

   public:
    void print_multiset() {
        Node *temp = head;
        while (temp != nullptr) {
            std::cout << temp->value << std::endl;
            temp = temp->next;
        }
    }
    multiset() { head = tail = nullptr; }
    multiset(std::initializer_list<T> const &items) {
        head = tail = nullptr;
        if (items.size() == 0) {
            return;
        }
        for (auto it = items.begin(); it != items.end(); ++it) {
            insert(*it);
        }
    }
    // copy
    multiset(const multiset &ms) {
        head = tail = nullptr;
        if (ms.head == nullptr) {
            return;
        }
        for (Node *it = ms.head; it != nullptr; it = it->next) {
            insert(it->value);
        }
    }
    // move
    multiset(multiset &&ms) {
        head = ms.head;
        tail = ms.tail;
        ms.head = nullptr;
        ms.tail = nullptr;
    }
    ~multiset() { clear(); };
    multiset operator=(multiset &&ms) {
        Node *prevh = head;
        Node *prevt = tail;
        head = ms.head;
        tail = ms.tail;
        ms.head = prevh;
        ms.tail = prevt;
    }
    class MultisetIterator {
       public:
        Node *iterator;
        MultisetIterator() : iterator(nullptr) {}
        MultisetIterator(Node *node) : iterator(node) {}
        MultisetIterator operator++(int) {
            MultisetIterator tmp(*this);
            if (iterator) iterator = iterator->next;
            return tmp;
        }
        MultisetIterator &operator++() {
            if (iterator) iterator = iterator->next;
            return *this;
        }
        MultisetIterator operator--(int) {
            MultisetIterator tmp(*this);
            if (iterator) iterator = iterator->prev;
            return tmp;
        }
        MultisetIterator &operator--() {
            if (iterator) iterator = iterator->prev;
            return *this;
        }
        Node *operator->() const {
            if (iterator == nullptr) {
                throw std::runtime_error("Iterator is null");
            }
            return iterator;
        }
        const T &operator*() const {
            if (iterator == nullptr) {
                throw std::runtime_error("Dereferencing null iterator");
            }
            return iterator->value;
        }
        bool operator!=(const MultisetIterator &other) const {
            return other.iterator != iterator;
        }
        bool operator==(const MultisetIterator &other) const {
            return other.iterator == iterator;
        }
    };

    MultisetIterator begin() { return MultisetIterator(head); }
    MultisetIterator end() {
        return MultisetIterator(tail ? tail->next : nullptr);
    }
    const MultisetIterator begin() const { return MultisetIterator(head); }
    const MultisetIterator end() const { return MultisetIterator(tail->next); }
    bool empty() {
        if (head != nullptr) {
            return false;
        } else {
            return true;
        }
    }
    size_type size() {
        int num = 0;
        Node *src = head;
        while (src != nullptr) {
            num++;
            src = src->next;
        }
        return num;
    }
    size_type max_size() {
        return std::numeric_limits<size_type>::max() / sizeof(Node);
    }

    void clear() {
        while (head != nullptr) {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }

    MultisetIterator insert(const T &value) {
        if (!head) {
            head = tail = new Node(value);
            return MultisetIterator(head);
        }
        Node *temp = head;
        while (temp && temp->value < value) {
            temp = temp->next;
        }
        Node *new_node = new Node(value);
        if (!temp) {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        } else {
            if (temp == head) {
                head = new_node;
            } else {
                temp->prev->next = new_node;
            }
            new_node->prev = temp->prev;
            new_node->next = temp;
            temp->prev = new_node;
        }
        return MultisetIterator(new_node);
    }
    void erase(MultisetIterator pos) {
        Node *rm = pos.iterator;
        Node *prev = rm->prev;
        Node *next = rm->next;
        if (next != nullptr) {
            next->prev = prev;
        } else {
            tail = prev;
        }
        if (prev != nullptr) {
            prev->next = next;
        } else {
            head = next;
        }
        delete rm;
    }
    void swap(multiset &other) {
        Node *prevh = head;
        Node *prevt = tail;
        head = other.head;
        tail = other.tail;
        other.head = prevh;
        other.tail = prevt;
    }
    void merge(multiset &other) {
        Node *cur = other.head;
        while (cur) {
            Node *next = cur->next;
            Node *prev = cur->prev;
            Node *nxt = cur->next;
            if (prev)
                prev->next = nxt;
            else
                other.head = nxt;
            if (nxt)
                nxt->prev = prev;
            else
                other.tail = prev;
            cur->prev = tail;
            cur->next = nullptr;
            if (tail)
                tail->next = cur;
            else
                head = cur;
            tail = cur;
            cur = next;
        }
    }

    size_type count(const T &key) {
        size_type num = 0;
        Node *temp = head;
        while (temp) {
            if (temp->value == key) {
                num++;
            }
            temp = temp->next;
        }
        return num;
    }
    MultisetIterator find(const T &key) {
        Node *temp = head;
        Node *res = nullptr;
        while (temp) {
            if (temp->value == key) {
                res = temp;
                break;
            }
            temp = temp->next;
        }
        return MultisetIterator(res);
    }
    bool contains(const T &key) {
        Node *temp = head;
        while (temp != nullptr) {
            // key is the same
            if (temp->value == key) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    };
    std::pair<MultisetIterator, MultisetIterator> equal_range(const T &key) {
        Node *temp = head;
        std::pair<MultisetIterator, MultisetIterator> res;
        while (temp != nullptr) {
            // key is the same
            if (temp->value == key) {
                if (res.first == nullptr) {
                    res.first = temp;
                    res.second = temp;
                } else {
                    res.second = temp->next;
                }
            }
            temp = temp->next;
        }
        return res;
    }
    MultisetIterator lower_bound(const T &key) {
        Node *temp = head;
        while (temp != nullptr) {
            if (temp->value >= key) {
                return MultisetIterator(temp);
            }
            temp = temp->next;
        }
        return MultisetIterator(temp);
    }
    MultisetIterator upper_bound(const T &key) {
        Node *temp = head;
        while (temp != nullptr) {
            if (temp->value > key) {
                return MultisetIterator(temp);
            }
            temp = temp->next;
        }
        return MultisetIterator(temp);
    }
};
}  // namespace S21
