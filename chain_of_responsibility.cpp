#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

class Base {
  Base *next;
public:
  Base() {
    next = nullptr;
  }
  void setNext(Base *n) {
    next = n;
  }
  void add(Base *n) {
    if (next)
      next->add(n);
    else
      next = n;
  }
  virtual void handle(int i) {
    next->handle(i);
  }
};

class Handler1 : public Base {
public:
  void handle(int i) {
    if (rand() % 3) {
      cout<<"h1 passed "<<i<<" ";
      Base::handle(i);
    }
    else 
      cout<<"H1 handled "<<i<<" ";
  }
};

class Handler2 : public Base {
public:
  void handle(int i) {
    if (rand() % 3) {
      cout<<"h2 passed "<<i<<" ";
      Base::handle(i);
    }
    else 
      cout<<"H2 handled "<<i<<" ";
  }
};

class Handler3 : public Base {
public:
  void handle(int i) {
    if (rand() % 3) {
      cout<<"h3 passed "<<i<<" ";
      Base::handle(i);
    }
    else 
      cout<<"H3 handled "<<i<<" ";
  }
};


int main() {
  srand(time(0));
  Handler1 root;
  Handler2 two;
  Handler3 thr;
  root.add(&two);
  root.add(&thr);
  thr.setNext(&root);
  for (int i = 0; i < 10; ++i) {
    root.handle(i);
    cout<<"\n";
  }
}
