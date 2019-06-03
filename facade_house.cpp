#include <string>
#include <iostream>

using namespace std;
class Alarm {
public:
  void alamOn() {
    cout<<"Alarm is on and house is secured"<<endl;
  }
  void alamOff() {
    cout<<"Alarm is off and house is open"<<endl;
  }
};
class Ac {
public:
  void acOn() {
    cout<<"Ac is on"<<endl;
  }
  void acOff() {
    cout<<"Ac is off"<<endl;
  }
};
class Tv {
public:
  void TvOn() {
    cout<<"Tv is on"<<endl;
  }
  void TvOff() {
    cout<<"Tv is off"<<endl;
  }
};
class HouseFacade {
  Alarm alarm;
  Ac ac;
  Tv tv;
public:
  HouseFacade() {}
  void goToWork() {
    ac.acOff();
    tv.TvOff();
    alarm.alamOn();
  }
  void comHome() {
    ac.acOn();
    tv.TvOn();
    alarm.alamOff();
  }
};

int main() {
  HouseFacade hf;
  hf.goToWork();
  hf.comHome();
}
