#include <cstdio>
#include <vector>
#include <iostream>
#include <memory>
#include <functional>
using namespace std;

class ExecuteInterface {
public:
  virtual ~ExecuteInterface() {}
  virtual void execute() = 0;
};

template<typename T>
class ExecuteAdapter : public ExecuteInterface {
public:
  ExecuteAdapter(shared_ptr<T> o, function<void()> m) {
    object = o;
    method = m;
  }
  ~ExecuteAdapter() {
  }
  void execute() {
    method();
  }
private:
  shared_ptr<T> object;
  function<void()> method;
};

class A {
public:
  ~A() {
    cout<<"A::dtor"<<endl;
  }
  void doThis() {
    cout<<"A::doThis()"<<endl;
  }
};
class B {
public:
  ~B() {
    cout<<"B::dtor"<<endl;
  }
  void doThis() {
    cout<<"B::doThis()"<<endl;
  }
};
class C {
public:
  ~C() {
    cout<<"C::dtor"<<endl;
  }
  void doThis() {
    cout<<"C::doThis()"<<endl;
  }
};

auto initialize() {
  vector<shared_ptr<ExecuteInterface>> array; //基类无模板，方便实现多态
  shared_ptr<A> a(new A);
  function<void()> f = bind(&A::doThis, a);
  shared_ptr<B> b(new B);
  shared_ptr<C> c(new C);
  // array.push_back(shared_ptr<ExecuteInterface>(new ExecuteAdapter<A>(a, bind(&A::doThis, a.get()))));
  array.push_back(shared_ptr<ExecuteInterface>(new ExecuteAdapter<A>(a, [a](){a->doThis();}))); //bind不好，尽量用lambda表达式
  array.push_back(shared_ptr<ExecuteInterface>(new ExecuteAdapter<B>(b, [b](){b->doThis();})));
  array.push_back(shared_ptr<ExecuteInterface>(new ExecuteAdapter<C>(c, [c](){c->doThis();})));
  return array;
}

int main () {
  vector<shared_ptr<ExecuteInterface>> obj = initialize();
  for (int i = 0; i < 3; ++i )
    obj[i]->execute();
  return 0;
  
}
