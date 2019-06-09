#include <cstddef>
#include <iostream>
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};

template<class _Tp, class _Distance> struct input_iterator {
  typedef input_iterator_tag  iterator_category;
  typedef _Tp                 value_type;
  typedef _Distance           difference_type;
  typedef _Tp*                pointer;
  typedef _Tp&                reference;
};

struct output_iterator {
  typedef output_iterator_tag iterator_category;
  typedef void                value_type;
  typedef void                difference_type;
  typedef void                pointer;
  typedef void                reference;
};

template<class _Tp, class _Distance> struct forward_iterator {
  typedef forward_iterator_tag  iterator_category;
  typedef _Tp                   value_type;
  typedef _Distance             difference_type;
  typedef _Tp*                  pointer;
  typedef _Tp&                  reference;
};

template<class _Tp, class _Distance> struct bidirectional_iterator {
  typedef bidirectional_iterator_tag  iterator_category;
  typedef _Tp                         value_type;
  typedef _Distance                   difference_type;
  typedef _Tp*                        pointer;
  typedef _Tp&                        reference;
};

template<class _Tp, class _Distance> struct random_access_iterator {
  typedef random_access_iterator_tag  iterator_category;
  typedef _Tp                         value_type;
  typedef _Distance                   difference_type;
  typedef _Tp*                        pointer;
  typedef _Tp&                        reference;
};


template<class _Iterator>
struct iterator_traits {
  typedef typename _Iterator::iterator_category    iterator_category;
  typedef typename _Iterator::value_type           value_type;
  typedef typename _Iterator::difference_type      difference_type;
  typedef typename _Iterator::pointer              pointer;
  typedef typename _Iterator::reference            reference;
};


template<class _Tp>
struct iterator_traits<_Tp*> {
  typedef random_access_iterator_tag  iterator_category;
  typedef _Tp                         value_type;
  typedef ptrdiff_t                   difference_type;
  typedef _Tp*                        pointer;
  typedef _Tp&                        reference;
};


template<class _Tp>
struct iterator_traits<const _Tp*> {
  typedef random_access_iterator_tag  iterator_category;
  typedef _Tp                                value_type;
  typedef ptrdiff_t                          difference_type;
  typedef const _Tp*                         pointer;
  typedef const _Tp&                         reference;
};

template<class _Iter>
inline typename iterator_traits<_Iter>::iterator_category
__iterator_category(const _Iter&) {
  typedef typename iterator_traits<_Iter>::iterator_category _Category;
  return _Category();
}


template<class _Iter>
inline typename iterator_traits<_Iter>::difference_type*
__distance_type(const _Iter&) {
  return static_cast<typename iterator_traits<_Iter>::difference_type*>(0);
}

template<class _Iter>
inline typename iterator_traits<_Iter>::value_type*
__value_type(const _Iter&) {
  return static_cast<typename iterator_traits<_Iter>::value_type*>(0);
}


template<class _Iter>
inline typename iterator_traits<_Iter>::iterator_category
iterator_category(const _Iter& __i) {
  return __iterator_category(__i);
}
template <class _Iter>
inline typename iterator_traits<_Iter>::difference_type*
distance_type(const _Iter& __i) { return __distance_type(__i); }

template <class _Iter>
inline typename iterator_traits<_Iter>::value_type*
value_type(const _Iter& __i) { return __value_type(__i); }

#define __ITERATOR_CATEGORY(__i)  __iterator_category(__i)
#define __DISTANCE_TYPE(__i)      __distance_type(__i)
#define __VALUE_TYPE(__i)         __value_type(__i)


template<class _InputIter, class _Distance>
inline void __advance(_InputIter& __i, _Distance __n, input_iterator_tag) {
  while(__n--) ++__i;
}

template<class _BidirectionalIterator, class _Distance>
inline void __advance(_BidirectionalIterator& __i, _Distance __n,
                      bidirectional_iterator_tag) {
  if (__n >= 0) {
    while (__n--) ++__i;
  } else {
    while (__n++) --__i;  
  }
}

template<class _RandomAccessIterator, class _Distance>
inline void __advance(_RandomAccessIterator& __i, _Distance __n, random_access_iterator_tag) {
  __i += __n;
}

template<class _InputIter, class _Distance>
inline void advance(_InputIter& __i, _Distance __n) {
  __advance(__i, __n, iterator_category(__i));
}

// 阉割版vector
template<class T>
class Vector {
private:
  T *start_;
  T *finish_;
public:
  typedef T         value_type;
  typedef T*        iterator;
  typedef const T*  const_iterator;
  typedef iterator  pointer;
  typedef T&        reference;
  typedef const T&  const_reference;
  typedef size_t    size_type;
  typedef ptrdiff_t difference_type;
  
public:
  explicit Vector(const size_type n) {
    start_ = new T[n];
    finish_ = start_ + n;
  }
  ~Vector() {
    delete [] start_;
    start_ = finish_ = 0;
  }
  iterator begin() {
    return start_;
  }
  iterator end() {
    return finish_;
  }
  
};
int main() {
  Vector<int> a(10);
  Vector<int>::iterator it;
  for (it = a.begin(); it != a.end(); advance(it, 1)) {
    std::cout<<*it<<std::endl;
  }
}
