#include <iostream>
#include <iomanip>
#include <memory>
#include <vector>
#include <string>

using namespace std;
class TimeImp {
public:
  TimeImp(int hr, int min): hr_(hr), min_(min) {
  }
  virtual void tell() {
    cout<<"time is "<<<<hr_<<" : "<<min_<<endl;
  }
protected:
  int hr_, min_;
};
class CivilianTimeImp :public TimeImp {
public:
  CivilianTimeImp(int hr, int min, int pm): TimeImp(hr, min) {
    if (pm)
      whichM_ = "PM";
    else
      whichM_ = "AM";
  }

  void tell() {
    cout<<"time is "<<hr_<<":"<<min_<<whichM_<<endl;
  }
protected:
  string whichM_;
};


class Time {
public:
  Time() {}
  Time(int hr, int min) {
    imp_.reset(new TimeImp(hr, min));
  }
  virtual void tell() {
    imp_->tell();
  }
protected:
  shared_ptr<TimeImp> imp_;
};
class CivilianTime: public Time {
public:
  CivilianTime(int hr, int min, int pm) {
    imp_.reset(new CivilianTimeImp(hr, min, pm));
  }
};


int main() {
  vector<shared_ptr<Time>> times;
  times.push_back(shared_ptr<Time>(new Time(14,30)));
  times.push_back(shared_ptr<CivilianTime>(new CivilianTime(2,30,1)));
  for (auto p : times)
    p->tell();

}
