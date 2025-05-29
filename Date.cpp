//
// Created by master on 2025/5/1.
//
#include "header.h"

string Date::toString() const {
    string str;
    str += to_string(Year);
    str += "-";
    if (Month <= 9) str += "0";
    str += to_string(Month);
    str += "-";
    if (Day <= 9) str += "0";
    str += to_string(Day);
    return str;
}

ostream& operator<<(ostream& os,const Date& date){
    os << date.Year << "-";
    if (date.Month <= 9) os << 0;
    os << date.Month << "-";
    if (date.Day <= 9) os << 0;
    os << date.Day;
    return os;
}

void Date::getCurrentDate() {
  std::time_t now = std::time(nullptr);
  std::tm* localTime = std::localtime(&now);

  setYear(localTime->tm_year + 1900);
  setMonth(localTime->tm_mon + 1);
  setDay(localTime->tm_mday);

}

istream& operator>>(istream& os, Date &date){
  string time;//cout << time << endl;
  os >> time;
  int num = 0,i = 0;
  for (i=0;i<time.size();i++){
    if (time[i] >= '0' && time[i] <= '9') num = num*10 + (time[i]-'0');
    else break;
  }
  i++;
  date.setYear(num);num = 0;
  for (;i<time.size();i++){
    if (time[i] >= '0' && time[i] <= '9') num = num*10 + (time[i]-'0');
    else break;
  }
  i++;
  date.setMonth(num);num = 0;
  for (;i<time.size();i++){
    if (time[i] >= '0' && time[i] <= '9') num = num*10 + (time[i]-'0');
    else break;
  }
  date.setDay(num);
  return os;
}

bool Date::operator<(const Date &t) const {
    if (Year != t.Year) return Year < t.Year;
    if (Month != t.Month) return Month < t.Month;
    return Day < t.Day;
}

bool Date::operator>(const Date &t) const {
    if (Year != t.Year) return Year > t.Year;
    if (Month != t.Month) return Month > t.Month;
    return Day > t.Day;
}

Date::Date(const Date &t) {
    Year = t.Year;
    Month = t.Month;
    Day = t.Day;
}

Date::Date(int y, int m, int d) {
    Year = y;
    Month = m;
    Day = d;
}