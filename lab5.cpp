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
            this->curr=I.curr;
            this->begin=I.begin;
            this->end=I.end;
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
        bool operator != (const Iterator& it) const { return curr != it.curr;}
        bool operator == (const Iterator& it) const { return curr == it.curr;}
        bool operator >(const Iterator& I) const {return this->curr > I.curr;}
        bool operator <(const Iterator& I) const {return this->curr < I.curr;}
        T& operator* () const {return *curr;};
        T& operator-> () const {return curr;}
    };
private:
    T* _buffer;
    size_t _n;
    Iterator _head;
    Iterator _tail;
public:
    explicit circular_buffer(size_t n=1): _n(n){
        _buffer = new T[n];
        _head = Iterator(_buffer,_buffer, _buffer+_n);
        _tail = Iterator(_buffer,_buffer, _buffer+_n);
        _head;
        --_tail;
    }
    circular_buffer(const circular_buffer& b){
        this->_buffer=b._buffer;
        this->_n=b._n;
        this->_head=b._head;
        this->_tail=b._tail;
    }
    circular_buffer & operator = (const circular_buffer & b){
        this->_buffer=b._buffer;
        this->_n=b._n;
        this->_head=b._head;
        this->_tail=b._tail;
        return *this;
    }

    T& operator[] (const int&n) const{
        if (n>0 && n <_n)
            return _buffer[n];
        return _buffer[0];
    }

    Iterator begin() {return _head;}
    Iterator end() {return _head;}

    void push_front(T val){
        --_head;
        *_head.curr=val;
        if (_head==_tail)
            --_tail;
    }

    void pop_front(){
        ++_head;
    }
    void push_back(T val){
        ++_tail;
        *_tail.curr=val;
        if (_head==_tail)
            ++_head;
    }
    void pop_back(){
        --_tail;
    }
    void resize(int n){
        T* buffer = new T[n];
        int i=0;
        while (_head != _tail && i<n){
            buffer[i]=*_head.curr;
            ++_head;
            ++i;
        }
        if (i<n)
            buffer[i]=*_head.curr;
        _buffer=buffer;
        _n=n;
        _head = Iterator(_buffer,_buffer, _buffer+_n);
        _tail = Iterator(_buffer+i,_buffer, _buffer+_n);
    }
    void out() const{
        for(auto i=0; i<_n; i++){
            std::cout << _buffer[i]<< "\n";
        }
        std::cout<<"Value of head: "<<*_head.curr<<"\n";
        std::cout<<"Value of tail: "<<*_tail.curr<<"\n";
    }

};

int main() {
    return 0;
}
