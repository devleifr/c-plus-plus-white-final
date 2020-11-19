#include <exception>
#include <iomanip>
#include <iostream>
#include <vector>
#include <set>
#include <string>

// Реализуйте функции и методы классов и при необходимости добавьте свои

class Date {
public:
    int GetYear() const {
        return year_;
    }
    int GetMonth() const {
        return month_;
    }
    int GetDay() const {
        return day_;
    }
    explicit Date(int year, int month, int day)
        : year_(year), month_(month), day_(day) {}
private:
  int year_;
  int month_;
  int day_;
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
        return type_;
    }
    Date GetDate() const {
        return date_;
    }
    explicit Event(const std::string& type, const Date& date)
        : type_(type), date_(date) {}
private:
    std::string type_;
    Date date_;
};

bool operator<(const Event& lhs, const Event& rhs) {
    if (lhs.GetDate() == rhs.GetDate()) {
        return lhs.GetType() < rhs.GetType();
    }
    return lhs.GetDate() < rhs.GetDate();
}


class Database {
public:
    void AddEvent(const Date& date, const std::string& event) {
        if (date.GetMonth() < 1 || date.GetMonth() > 12) {
            throw std::invalid_argument(std::to_string(date.GetMonth()));
        }
        if (date.GetDay() < 1 || date.GetDay() > 31) {
            throw std::invalid_argument(std::to_string(date.GetDay()));
        }
        events.insert(Event{event, date});
    }
    bool DeleteEvent(const Date& date, const std::string& event) {
        return events.erase(Event(event, date));
    }
    int  DeleteDate(const Date& date) {
        return std::erase_if(events, [date](const Event& e) -> bool {
            return e.GetDate() == date;
        });
    }
    std::vector<std::string> Find(const Date& date) const {
        std::vector<std::string> event_types;
        for (const auto& ev : events) {
            if (ev.GetDate() == date) event_types.push_back(ev.GetType());
        }
        return event_types;
    }
    void Print() const {
        std::cout << std::setfill('0');
        for (const auto& ev : events) {
            Date date = ev.GetDate();
            std::cout << std::setw(4) << date.GetYear() << '.'
                      << std::setw(2) << date.GetMonth() << '.'
                      << std::setw(2) << date.GetDay() << ' '
                      << ev.GetType() << std::endl;
        }
    }
private:
    std::set<Event> events;
};

int main() {
  Database db;

  std::string command;
  while (getline(std::cin, command)) {
      try {

      }  catch () {

      }
    // Считайте команды с потока ввода и обработайте каждую
  }

  return 0;
}
