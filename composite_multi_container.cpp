#include <iostream>
#include <vector>

using namespace std;

class Component {
public:
  virtual void traverse() = 0;
};

class Primitive : public Component {
  int value;
public:
  Primitive(int val) {
    value = val;
  }
  void traverse() {
    cout<<value<<" ";
  }
};

class Composite: public Component {
  vector<Component*> children;
  int value;
public:
  Composite(int val) : value(val) {}
  void add(Component* c) {
    children.push_back(c);
  }
  void traverse() {
    cout<<value<<" ";
    for (int i = 0; i < children.size(); ++i) {
      children[i]->traverse();
    }
  }
};

class Row: public Composite {
public:
  Row(int val): Composite(val) {}
  void traverse() {
    cout<<"Row";
    Composite::traverse();
  }
};
class Column: public Composite {
public:
  Column(int val): Composite(val) {}
  void traverse() {
    cout<<"Col";
    Composite::traverse();
  }
};

int main() {
  Row first(1);
  Column second(2);
  Column third(3);
  Row fourth(4);
  Row fifth(5);
  first.add(&second);
  first.add(&third);
  first.add(&fourth);
  first.add(&fifth);
  Primitive p6 = Primitive(6);
  Primitive p7 = Primitive(7);
  Primitive p8 = Primitive(8);
  Primitive p9 = Primitive(9);
  Primitive p10 = Primitive(10);
  first.add(&p6);
  second.add(&p7);
  third.add(&p8);
  fourth.add(&p9);
  fifth.add(&p10);
  first.traverse();
  cout<<"\n";
}
