#include <iostream>

using namespace std;

class Widget {
public:
  virtual void draw() = 0;
};
class TextField : public Widget {
  int width, height;
public:
  TextField(int w, int h) {
    width = w;
    height = h;
  }
  void draw() {
    cout<<"TextField: "<<width<<","<<height<<"\n";
  }
};

class Decorator : public Widget {
  Widget *wid;
public:
  Decorator(Widget *w) {
    wid = w;
  }
  void draw() {
    wid->draw();
  }
};

class BorderDecorator : public Decorator {
public:
  BorderDecorator(Widget *w): Decorator(w) {}
  void draw() {
    Decorator::draw();
    cout<<"  BorderDecorator"<<"\n";
  }
};
class ScrollDecorator : public Decorator {
public:
  ScrollDecorator(Widget *w): Decorator(w) {}
  void draw() {
    Decorator::draw();
    cout<<"  ScrollDecorator"<<"\n";
  }
};
int main() {
  Widget *aWidget = new BorderDecorator(new BorderDecorator(new ScrollDecorator(new TextField(80, 24))));
  aWidget->draw();
}
