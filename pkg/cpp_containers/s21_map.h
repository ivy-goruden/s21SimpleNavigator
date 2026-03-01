#ifndef S21_MAP_H
#define S21_MAP_H

namespace S21 {

template <typename Key, typename T>
class map {
    using value_type = std::pair<Key, T>;
    using size_type = size_t;

   private:
    struct Node {
       public:
        Key first;
        T second;
        Node* next;
        Node* prev;
        Node(const value_type& val)
            : first(val.first),
              second(val.second),
              next(nullptr),
              prev(nullptr) {}
        Node(Key key, T value)
            : first(key), second(value), next(nullptr), prev(nullptr) {}
    };
    Node* head = nullptr;
    Node* tail = nullptr;

   public:
    class MapIterator {
       public:
        Node* iterator;
        MapIterator() : iterator(nullptr) {}
        MapIterator(Node* node) : iterator(node) {}
        MapIterator operator++(int) {
            MapIterator tmp(*this);
            if (iterator) iterator = iterator->next;
            return tmp;
        }
        MapIterator& operator++() {
            if (iterator) iterator = iterator->next;
            return *this;
        }
        MapIterator operator--(int) {
            MapIterator tmp(*this);
            if (iterator) iterator = iterator->prev;
            return tmp;
        }
        MapIterator& operator--() {
            if (iterator) iterator = iterator->prev;
            return *this;
        }
        volatile Node* operator->() const {
            if (iterator == nullptr)
                throw std::runtime_error("Iterator is null");
            return iterator;
        }
        std::pair<const Key&, T&> operator*() const {
            if (iterator == nullptr) {
                return std::pair<const Key&, T&>(NULL, NULL);
            }
            return std::pair<const Key&, T&>(iterator->first, iterator->second);
        }
        bool operator!=(const MapIterator& other) const {
            return other.iterator != iterator;
        }
        bool operator==(const MapIterator& other) const {
            return other.iterator == iterator;
        }
    };
    map() {
        head = nullptr;
        tail = nullptr;
    }
    ~map() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
    map(std::initializer_list<value_type> const& items) {
        head = new Node(*(items.begin()));
        Node* temp = head;
        temp->prev = nullptr;

        for (auto it = items.begin() + 1; it != items.end(); it++) {
            Node* new_node = new Node(*it);
            temp->next = new_node;
            tail = new_node;
            new_node->prev = temp;
            temp = temp->next;
        }
    }
    void print_map() {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->first + " - " + temp->second << std::endl;
            temp = temp->next;
        }
    }
    // copy
    map(const map& other) {
        if (other.head == other.tail->next) {
            return;
        }
        if (other.head == head) {
            return;
        }
        head = new Node(other.head->first, other.head->second);
        Node* current = head;
        Node* other_current = other.head->next;

        // Копируем остальные узлы
        while (other_current) {
            Node* new_node =
                new Node(other_current->first, other_current->second);
            current->next = new_node;
            new_node->prev = current;

            current = new_node;
            other_current = other_current->next;
        }

        tail = current;
    }
    // move
    map(map&& other) {
        head = other.head;
        tail = other.tail;
        head = other.head;
        tail = other.tail;
    }

    map& operator=(map&& other) {
        head = other.head;
        tail = other.tail;
        return *this;
    }

    map& operator=(const map& other) {
        if (other.head == other.tail->next) {
            return *this;
        }
        if (other.head == head) {
            return *this;
        }
        head = new Node(other.head->first, other.head->second);
        Node* current = head;
        Node* other_current = other.head->next;

        // Копируем остальные узлы
        while (other_current) {
            Node* new_node =
                new Node(other_current->first, other_current->second);
            current->next = new_node;
            new_node->prev = current;

            current = new_node;
            other_current = other_current->next;
        }

        tail = current;
        return *this;
    }

    MapIterator begin() { return MapIterator(head); }
    MapIterator end() { return MapIterator(nullptr); }
    const MapIterator begin() const { return MapIterator(head); }
    const MapIterator end() const { return MapIterator(nullptr); }
    bool empty() {
        if (head != nullptr) {
            return false;
        } else {
            return true;
        }
    }
    size_type size() {
        int num = 0;
        Node* src = head;
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
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
    }
    std::pair<MapIterator, bool> insert(const value_type& value) {
        std::pair<MapIterator, bool> result;
        Node* temp = head;
        if (head == nullptr) {
            Node* n = new Node(value);
            head = tail = n;
            return std::make_pair(MapIterator(n), true);
        }
        while (temp != nullptr) {
            // key is the same
            if (temp->first == value.first) {
                result.first = begin();
                result.second = false;
                return result;
            }
            temp = temp->next;
        }
        Node* new_node = new Node(value);
        new_node->prev = tail;
        tail->next = new_node;
        tail = tail->next;
        result.first = MapIterator(new_node);
        result.second = true;
        return result;
    }
    std::pair<MapIterator, bool> insert(const Key& key, const T& obj) {
        return insert(value_type(key, obj));
    }
    std::pair<MapIterator, bool> insert_or_assign(const Key& key,
                                                  const T& obj) {
        std::pair<MapIterator, bool> result;
        Node* temp = head;
        if (head == nullptr) {
            Node* n = new Node(key, obj);
            head = tail = n;
            return std::make_pair(MapIterator(n), true);
        }
        while (temp != nullptr) {
            // key is the same
            if (temp->first == key) {
                result.first = begin();
                result.second = false;
                temp->second = obj;
                return result;
            }
            temp = temp->next;
        }
        Node* new_node = new Node(key, obj);
        new_node->prev = tail;
        tail->next = new_node;
        tail = tail->next;
        result.first = MapIterator(new_node);
        result.second = true;
        return result;
    }

    void erase(MapIterator pos) {
        Node* rm = pos.iterator;
        Node* prev = rm->prev;
        Node* next = rm->next;
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
    void swap(map& other) {
        Node* prevh = head;
        Node* prevt = tail;
        head = other.head;
        tail = other.tail;
        other.head = prevh;
        other.tail = prevt;
    }
    void merge(map& other) {
        Node* cur = other.head;
        while (cur) {
            Node* next = cur->next;
            if (!contains(cur->first)) {
                Node* prev = cur->prev;
                Node* nxt = cur->next;
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
            }
            cur = next;
        }
    }
    bool contains(const Key& key) {
        Node* temp = head;
        while (temp != nullptr) {
            // key is the same
            if (temp->first == key) {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
};

}  // namespace S21

#endif
