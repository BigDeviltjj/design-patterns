#include <iostream>
using namespace std;

class Command {
public:
  virtual void execute() = 0;
};

class Light {
public:
  Light() {}
  void turnOn() {
    cout<<"The light is on"<<endl;
  }
  void turnOff() {
    cout<<"The light is off"<<endl;
  }
};

class FlipUpCommand : public Command {
public:
  FlipUpCommand(Light& light) : theLight(light) {}
  virtual void execute() {
    theLight.turnOn();
  }
private:
  Light& theLight;
};

class FlipDownCommand : public Command {
public:
  FlipDownCommand(Light& light) : theLight(light) {}
  virtual void execute() {
    theLight.turnOff();
  }
private:
  Light& theLight;
};

class Switch {
public:
  Switch(Command& flipUpCmd, Command& flipDownCmd) :
    flipUpCommand(flipUpCmd), flipDownCommand(flipDownCmd) {}
  void flipUp() {
    flipUpCommand.execute();
  }
  void flipDown() {
    flipDownCommand.execute();
  }
private:
  Command& flipUpCommand;
  Command& flipDownCommand;
};

int main() {
  Light lamp;
  FlipUpCommand switchUp(lamp);
  FlipDownCommand switchDown(lamp);
  Switch s(switchUp, switchDown);
  s.flipUp();
  s.flipDown();
}
