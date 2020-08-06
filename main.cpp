#include <iostream>
#include <string>
#include <set>

// Реализуйте функции и методы классов и при необходимости добавьте свои

class Date {
public:
    int GetYear() const {
        return year;
    }
    int GetMonth() const {
        return month;
    }
    int GetDay() const {
        return day;
    }
    Date(int year, int month, int day) : year(year), month(month), day(day) {}
private:
  int year;
  int month;
  int day;
};

bool operator==(const Date& lhs, const Date& rhs) {
    return lhs.GetYear() == rhs.GetYear() &&
            lhs.GetMonth() == rhs.GetMonth() &&
            lhs.GetDay() == rhs.GetDay();
}

bool operator<(const Date& lhs, const Date& rhs) {
    if (lhs.GetYear() == rhs.GetYear()) {
        if (lhs.GetMonth() == rhs.GetMonth()) {
            return lhs.GetDay() < rhs.GetDay();
        } else {
            return lhs.GetMonth() < rhs.GetMonth();
        }
    }
    return lhs.GetYear() < rhs.GetYear();
}

class Event {
public:
    std::string GetType() const {
        return type;
    }
    Date GetDate() const {
        return date;
    }
private:
    std::string type;
    Date date;
};

bool operator<(const Event& lhs, const Event& rhs) {
    if (lhs.GetDate() == rhs.GetDate()) {
        return lhs.GetType() < rhs.GetType();

    }
    return lhs.GetDate() < rhs.GetDate();
}


class Database {
public:
  void AddEvent(const Date& date, const std::string& event);
  bool DeleteEvent(const Date& date, const std::string& event);
  int  DeleteDate(const Date& date);

  Event Find(const Date& date) const;

  void Print() const;
private:
    std::set<Event> events;
};

int main() {
  Database db;

  std::string command;
  while (getline(std::cin, command)) {
    // Считайте команды с потока ввода и обработайте каждую
  }

  return 0;
}
