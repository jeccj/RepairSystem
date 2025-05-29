//
// Created by master on 2025/5/7.
//

#ifndef REPAIRSYSTEM_DATE_H
#define REPAIRSYSTEM_DATE_H
#include "header.h"

class Date{
private:
  int Year;
  int Month;
  int Day;
public:
  Date(const Date&);
  explicit Date(int y=2025, int m=5, int d=1);
  string toString() const;
  void getCurrentDate();
  void setYear(int y){ Year = y; }
  void setMonth(int m){ Month = m; }
  void setDay(int d){ Day = d; }
  friend ostream& operator<<(ostream&,const Date&);
  friend istream& operator>>(istream&,Date&);
  bool operator<(const Date& t) const;
  bool operator>(const Date& t) const;
};

#endif // REPAIRSYSTEM_DATE_H
