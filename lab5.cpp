#include <iostream>

template<typename T>
class circular_buffer{
public:
    class Iterator{
    public:
        T* curr;
        T* begin;
        T* end;
        explicit Iterator():curr(nullptr), begin(nullptr), end(nullptr){}
        explicit Iterator(T* first, T* begin, T* end) : curr(first), begin(begin), end(end){}
        Iterator( const Iterator &I){
            this->curr=I.curr;
            this->begin=I.begin;
            this->end=I.end;
        }
        Iterator & operator = (const Iterator& I){
            if (this != I) {
                this->curr = I.curr;
                this->begin = I.begin;
                this->end = I.end;
            }
            return *this;
        }
        Iterator& operator+ (const int n) {
            for(int i=0; i<n; i++){
                ++curr;
                if (curr == end)
                    curr = begin;
            }
            return *this;
        }
        Iterator& operator- (const int n) {
            for(int i=0; i<n; i++){
                --curr;
                if (curr == begin)
                    curr = end;
            }
            return *this;
        }
        Iterator& operator++ () {
            ++curr;
            if (curr == end)
                curr = begin;
            return *this;
        }
        Iterator& operator-- () {
            if (curr == begin)
                curr = end;
            --curr;
            return *this;
        }
        bool operator != (const Iterator& I) const { return curr != I.curr;}
        bool operator == (const Iterator& I) const { return curr == I.curr;}
    private:
        size_t poz(const Iterator& I) const{
            size_t n=0;
            T* cur=I.begin;
            while (cur != curr){
                ++n;
                ++cur;
                if (cur == I.end)
                    curr = I.begin;
            }
            return n;
        }
    public:
        bool operator >(const Iterator& I) const {return poz(this) > poz(I);}
        bool operator <(const Iterator& I) const {return poz(this) < poz(I);}
        T& operator* () const {return *curr;};
        T& operator-> () const {return curr;}
    };
    
private:
    T* _buffer;
    size_t _n;
    T* _head;
    T* _tail;
    T* _begin;
    T* _end;

    void plusplus(T*& curr){
        ++curr;
        if (curr == _end)
            curr = _begin;
    }
    void minusminus(T*& curr){
        if (curr == _begin)
            curr = _end;
        --curr;
    }
public:
    explicit circular_buffer(size_t n=1): _n(n){
        _buffer = new T[n];
        _head = _buffer;
        _tail = _buffer;
        _begin = _buffer;
        _end = _buffer+_n;
    }
    circular_buffer(const circular_buffer& b){
        this->_buffer=b._buffer;
        this->_n=b._n;
        this->_head=b._head;
        this->_tail=b._tail;
        this->_begin=b._begin;
        this->_end=b._end;
    }
    circular_buffer & operator = (const circular_buffer & b){
        if (this != b) {
            this->_buffer = b._buffer;
            this->_n = b._n;
            this->_head = b._head;
            this->_tail = b._tail;
            this->_begin = b._begin;
            this->_end = b._end;
        }
        return *this;
    }

    T& operator[] (const int&n){
        if (n>0 && n <_n)
            return _buffer[n];
        return _buffer[0];
    }
    const T& operator[] (const int&n) const{
        if (n>0 && n <_n)
            return _buffer[n];
        return _buffer[0];
    }

    Iterator begin() {return Iterator(_head, _begin, _end);}
    Iterator end() {return Iterator(_tail, _begin, _end);}
    const Iterator begin() const {return Iterator(_head, _begin, _end);}
    const Iterator end() const {return Iterator(_tail, _begin, _end);}
    Iterator& front() const {return &Iterator(_head, _begin, _end);}
    Iterator& back() const {return &Iterator(_tail, _begin, _end);}
    
    void push_front(T val){
        minusminus(_head);
        *_head=val;
        if (_tail == _head)
            minusminus(_tail);
    }

    void pop_front(){
        plusplus(_head);
    }
    void push_back(const T& val){
        *_tail=val;
        plusplus(_tail);
        if (_tail == _head)
            plusplus(_head);
    }
    void pop_back(){
        minusminus(_tail);
    }
    void resize(size_t n){
        T* buffer = new T[n];
        int i=0;
        while (_head != _tail && i<n){
            buffer[i]=*_head;
            plusplus(_head);
            ++i;
        }
        _buffer=buffer;
        _n=n;
        _head = _buffer;
        _tail = _buffer+i;
    }
    void out(){
        for(auto i=0; i<_n; i++){
            std::cout << _buffer[i]<< "\n";
        }
        std::cout<<"Value of first element: "<<*_head<<"\n";
        minusminus(_tail);
        std::cout<<"Value of last element: "<<*(_tail)<<"\n";
    }

};

int main() {
    return 0;
}
