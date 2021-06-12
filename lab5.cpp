#include <iostream>

template<typename T>
class Iterator {
public:
    T *curr;
    T *begin;
    T *head;
    T *end;

    explicit Iterator() : curr(nullptr), begin(nullptr), head(nullptr), end(nullptr) {}

    explicit Iterator(T *first, T *begin, T *end, T *head) : curr(first), begin(begin), head(head), end(end) {}

    Iterator(const Iterator &I) {
        this->curr = I.curr;
        this->begin = I.begin;
        this->end = I.end;
    }

    Iterator &operator=(const Iterator &I) {
        if (this == I)
            return *this;
        this->curr = I.curr;
        this->begin = I.begin;
        this->end = I.end;
        return *this;
    }

    Iterator &operator+=(const int n) {
        if (n < 0)
            return *this -= -n;
        for (int i = 0; i < n; i++) {
            ++curr;
            if (curr == end)
                curr = begin;
        }
        return *this;
    }

    Iterator operator+(const int n) const {
        Iterator iter(*this);
        iter += n;
        return iter;
    }

    Iterator &operator-=(const int n) {
        if (n < 0)
            return *this += -n;
        for (int i = 0; i < n; i++) {
            --curr;
            if (curr == begin)
                curr = end;
        }
        return *this;
    }

    Iterator operator-(const int n) const {
        Iterator iter(*this);
        iter -= n;
        return iter;
    }

    Iterator &operator++() {
        ++curr;
        if (curr == end)
            curr = begin;
        return *this;
    }

    Iterator &operator--() {
        if (curr == begin)
            curr = end;
        --curr;
        return *this;
    }


private:
    size_t poz(const Iterator &I) const {
        size_t n = 0;
        T *cur = I.head;
        while (cur != I.curr) {
            if (cur == I.end)
                cur = I.begin;
            ++n;
            ++cur;
        }
        return n;
    }

public:
    bool operator!=(const Iterator &I) const { return curr != I.curr; }

    bool operator==(const Iterator &I) const { return curr == I.curr; }

    bool operator>(const Iterator &I) const { return poz(*this) > poz(I); }

    bool operator<(const Iterator &I) const { return poz(*this) < poz(I); }

    bool operator<=(const Iterator &I) const { return !(*this > I); }

    bool operator>=(const Iterator &I) const { return !(*this < I); }

    T &operator*() const { return *curr; };

    T &operator->() const { return curr; }
};


template<typename T, class Alloc = std::allocator<T>>
class circular_buffer {
public:
    using alloc_type = Alloc;
    using alloc_traits = std::allocator_traits<Alloc>;

private:
    T *_buffer;
    size_t _n;
    T *_head;
    T *_tail;
    T *_begin;
    alloc_type _alloc;

    void plusplus(T *&curr) {
        ++curr;
        if (curr == _begin + _n + 1)
            curr = _begin;
    }

    void minusminus(T *&curr) {
        if (curr == _begin)
            curr = _begin + _n + 1;
        --curr;
    }

public:
    explicit circular_buffer(size_t n = 1, const alloc_type &al = alloc_type()) : _n(n), _alloc(al) {
        _buffer = alloc_traits::allocate(_alloc, n + 1);
        _head = _buffer;
        _tail = _buffer;
        _begin = _buffer;

    }

    ~circular_buffer() {
        alloc_traits::deallocate(_alloc, _buffer, _n + 1);
    }

    circular_buffer &operator=(const circular_buffer &b) {
        if (*this == b)
            return *this;
        this->_buffer = b._buffer;
        this->_n = b._n;
        this->_head = b._head;
        this->_tail = b._tail;
        this->_begin = b._begin;
        return *this;
    }

    T &operator[](const int &n) const {
        if (_begin + _n + 1 <= _head + n) {
            return *(_head - (_n + 1 - n));
        }
        return *(_head + n);
    }


    Iterator<T> begin() { return Iterator(_head, _begin, _begin + _n, _head); }

    Iterator<T> end() { return Iterator(_tail, _begin, _begin + _n, _head); }

    T &front() const { return _head; }

    T &back() const {
        if (_tail == _begin) {
            if (_head == _begin)
                return *_tail;
            return *(_begin + _n);
        }
        return *(_tail - 1);
    }

    Iterator<const T> begin() const{ return Iterator(_head, _begin, _begin + _n, _head); }

    Iterator<const T> end() const{ return Iterator(_tail, _begin, _begin + _n, _head); }

    const T &const_front() const { return _head; }

    const T &const_back() const {
        if (_tail == _begin) {
            if (_head == _begin)
                return *_tail;
            return *(_begin + _n);
        }
        return *(_tail - 1);
    }

    void push_front(const T &val) {
        minusminus(_head);
        alloc_traits::construct(_alloc, _head, val);
        if (_head == _tail) {
            minusminus(_tail);
            alloc_traits::destroy(_alloc, _tail);
        }
    }

    void pop_front() {
        if (_head == _tail)
            return;
        alloc_traits::destroy(_alloc, _head);
        plusplus(_head);
    }

    void push_back(const T &val) {
        alloc_traits::construct(_alloc, _tail, val);
        plusplus(_tail);
        if (_tail == _head) {
            plusplus(_head);
            alloc_traits::destroy(_alloc, _tail);
        }
    }

    void pop_back() {
        if (_head == _tail)
            return;
        minusminus(_tail);
        alloc_traits::destroy(_alloc, _tail);
    }

    void resize(size_t n) {
        T *buffer = alloc_traits::allocate(_alloc, n + 1);
        int i = 0;
        T* head = _head;
        while (_head != _tail && i < n) {
            alloc_traits::construct(_alloc, (buffer + i), *_head);
            plusplus(_head);
            ++i;
        }
        while (head != _tail) {
            alloc_traits::destroy(_alloc, (head));
            plusplus(head);
        }
        alloc_traits::deallocate(_alloc, _buffer, _n + 1);
        _buffer = buffer;
        _n = n;
        _head = _buffer;
        _tail = _buffer + i;
    }

    size_t size() const {
        return _n;
    }

    void out(){
        for (auto iter = _head; iter != _tail; plusplus(iter))
            std::cout << *iter << "\n";
        std::cout << "Value of first element: " << *_head << "\n";
        std::cout << "Value of last element: " << back() << "\n";
    }
    friend std::ostream operator<<(std::ostream &out, circular_buffer& b);
};
template<typename T>
std::ostream& operator<<(std::ostream &out, circular_buffer<T>& b){
    for (auto iter = b._head; iter != b._tail; plusplus(iter))
        out << *iter << "\n";
    out << "Value of first element: " << *b._head << "\n";
    out << "Value of last element: " << b.back() << "\n";
}


int main() {
    return 0;
}
