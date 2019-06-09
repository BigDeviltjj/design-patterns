// template<class T>
// struct Base {
//   void interface() {
//     static_cast<T*>(this)->implementation();
//   }
//   static void static_func() {
//     T::static_sub_func();
//   }
// };
// 
// struct Derived : Base<Derived> {
//   void implementation();
//   static void static_sub_func();
// };

#include <iostream>
using namespace std;
template<typename T>
struct counter {
  static int objects_created;
  static int objects_alive;
  counter() {
    ++objects_created;
    ++objects_alive;
  }
  counter(const counter&) {
    ++objects_created;
    ++objects_alive;
  }
protected:
  ~counter() {
    --objects_alive;
  }
};

template<typename T> int counter<T>::objects_created(0);
template<typename T> int counter<T>::objects_alive(0);

class X : counter<X> {

};

class Y : counter<Y> {

};
int main () {
  X x1;
  Y Y1;
  {
    X x2;
    Y y2;
    cout<<"x alived "<<counter<X>::objects_alive<<endl;
    cout<<"x created "<<counter<X>::objects_created<<endl;
    cout<<"y alived "<<counter<Y>::objects_alive<<endl;
    cout<<"y created "<<counter<Y>::objects_created<<endl;
  }
  cout<<"x alived "<<counter<X>::objects_alive<<endl;
  cout<<"x created "<<counter<X>::objects_created<<endl;
  cout<<"y alived "<<counter<Y>::objects_alive<<endl;
  cout<<"y created "<<counter<Y>::objects_created<<endl;
}
