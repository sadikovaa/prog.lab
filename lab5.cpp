template<typename T>
class circular_buffer{
public:
    class Iterator;
private:
    T* _buffer;
    int _n;
    Iterator _begin;
    Iterator _end;
    Iterator _head;
    Iterator _tail;
public:
    circular_buffer(int n=1):
            _n(n){
        _buffer = new T(n);
        _begin = _buffer;
        _end = _buffer+_n;
        _head = _buffer;
        _tail = _buffer+_n;
    }
    T& operator[] (const int&n){
        if (n>0 && n <_n)
            return _buffer[n];
        return _buffer[0];
    }

    class Iterator{
    private:
        T* curr;
    public:
        Iterator(T* first) : curr(first){}

        T& operator+ (int n) {return *(curr + n);}
        T& operator- (int n) {return *(curr - n);}

        T& operator++ () {return *(++curr);}
        T& operator-- () {return *(--curr);}

        bool operator != (const Iterator& it) { return curr != it.curr;}
        bool operator == (const Iterator& it) { return curr == it.curr;}
        T& operator* () {return *curr;};
    };

    T index(const int n) const{return _head+n;}
    T begin() {return *_begin;}
    T end() {return *_end;}

    void push_front(T val){
        if (_begin == _head)
            _begin = --_tail;
        else
            --_begin;
        _begin = Iterator(val);
    }

    void pop_front(){
        if (_begin == _tail)
            _begin = _head;
        else
            ++_begin;
    }
    void push_back(T val){
        if (_end == _tail)
            _end = _head;
        _end = Iterator(val);
        ++_end;
    }
    void pop_back(T val){
        if (_end == --_head)
            _end = _tail;
        else
            --_end;
    }

    void increasing_size(int n){
        _tail=_tail+n;

    }

    void reducing_size(int n){

    }

};

int main() {
    return 0;
}
