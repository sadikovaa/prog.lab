template <typename IT, class P>
bool all_of(IT begin, IT end, P pred){
    while (begin != end) {
        if (!pred(*begin))
            return false;
        ++begin;
    }
    return true;
}

template <typename IT, class P>
bool any_of(IT begin, IT end, P pred){
    while (begin != end) {
        if (pred(*begin))
            return true;
        ++begin;
    }
    return false;
}

template <typename IT, class P>
bool none_of(IT begin, IT end, P pred){
    /*while (begin != end) {
        if (pred(*begin))
            return false;
        ++begin;
    }
    return true;*/
    return !(all_of(begin, end, pred));
}

template <typename IT, class P>
bool one_of(IT begin, IT end, P pred){
    bool one=false;
    while (begin != end ) {
        if (pred(*begin))
            if (!one)
                one = true;
            else
                return false;
        ++begin;
    }
    if (one)
        return true;
    return false;
}

template <typename IT, class C>
bool is_sorted(IT begin, IT end, C cond) {
    IT curr = begin;
    while (curr != end){
        if (cond(*(++curr), *(begin)))
            return false;
        ++begin;
    }
    return true;
}

template <typename IT, class C>
bool is_partitioned(IT begin, IT end, C cond){
    while (begin!=end && cond(*begin))
        ++begin;
    while (begin!=end) {
        if (cond(*begin))
            return false;
        ++begin;
    }
    return true;
}

template <typename IT, typename E>
IT find_not(IT begin, IT end, E el){
    while (begin != end) {
        if (*begin != el)
            return begin;
        ++begin;
    }
    return end;
}

template <typename IT, typename E>
IT find_backward(IT begin, IT end, E el){
    IT last = end;
    while (begin != end) {
        --end;
        if ( *end == el)
            return end;
    }
    return last;
}

template <typename IT, class C>
bool is_pallindrome(IT begin, IT end, C cond){
    --end;
    IT first = begin;
    IT last = end;
    while (begin != end && first!= end && last != begin){
        --end;
        if (cond(*begin) != cond(*end))
            return false;
        ++begin;
    }
    return true;
}



int main() {
    return 0;
}
