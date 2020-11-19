#include <exception>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

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
    explicit Date() : year_(0), month_(1), day_(1) {}
    explicit Date(int year, int month, int day)
        : year_(year), month_(month), day_(day) {
        if (month < 1 || month > 12) {
            throw std::domain_error("Month value is invalid: " +
                                    std::to_string(month));
        }
        if (day < 1 || day > 31) {
            throw std::domain_error("Day value is invalid: " +
                                    std::to_string(day));
        }
    }
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

Date toDate(const std::string& date_string, const char delim)
{
    std::istringstream ss(date_string);
    bool isDate= true;
    int year, month, day;
    isDate = isDate && (ss >> year);
    isDate = isDate && (ss.peek() == delim);
    ss.ignore(1);
    isDate = isDate && (ss >> month);
    isDate = isDate && (ss.peek() == delim);
    ss.ignore(1);
    isDate = isDate && (ss >> day);
    isDate = isDate && ss.eof();
    if (!isDate)
    {
        throw std::invalid_argument("Wrong date format: " + date_string);
    }
    return Date{year, month, day};
}

std::istream& operator>> (std::istream& in, Date& date) {
    std::string date_string;
    in >> date_string;
    date = toDate(date_string, '-');
    return in;
}

std::ostream& operator<< (std::ostream& out, const Date& date) {
    std::cout << std::setfill('0');
    std::cout << std::setw(4) << date.GetYear() << '-'
              << std::setw(2) << date.GetMonth() << '-'
              << std::setw(2) << date.GetDay();
    return out;
}

class Database {
public:
    void AddEvent(const Date& date, const std::string& event) {
        events[date].insert(event);
    }
    bool DeleteEvent(const Date& date, const std::string& event) {
        return events[date].erase(event);
    }
    int  DeleteDate(const Date& date) {
        size_t deleted_count = 0;
        if (events.count(date)) {
            deleted_count = events[date].size();
            events.erase(date);
        }
        return static_cast<int>(deleted_count);
    }
    std::set<std::string> Find(const Date& date) const {
        std::set<std::string> result;
        auto it = events.find(date);
        if (it != events.end()) {
            result = it->second;
        }
        return result;
    }
    void Print() const {
        for (const auto& [date, names] : events) {
            for (const auto& name : names) {
                std::cout << date << " "
                          << name << std::endl;
            }
        }
    }
private:
    std::map<Date, std::set<std::string> > events;
};

int main() {
    try {
        Database db;

        std::string query;
        while (getline(std::cin, query)) {
            // Считайте команды с потока ввода и обработайте каждую
            std::string command, event;
            Date date;
            if (query.empty()) continue;
            std::istringstream ss(query);
            ss >> command;
            if (command == "Add") {
                ss >> date >> event;
                db.AddEvent(date, event);
            } else if (command == "Del") {
                ss >> date >> event;
                if (!event.empty()) {
                    bool isDeleted = db.DeleteEvent(date, event);
                    if (isDeleted) {
                        std::cout << "Deleted successfully" << std::endl;
                    } else {
                        std::cout << "Event not found" << std::endl;
                    }
                } else {
                    int deleted_count = db.DeleteDate(date);
                    std::cout << "Deleted " << deleted_count << " events"
                              << std::endl;
                }
            } else if (command == "Find") {
                ss >> date;
                for (const auto& event : db.Find(date)) {
                    std::cout << event << std::endl;
                }
            } else if (command == "Print") {
                db.Print();
            } else {
                std::cout << "Unknown command: " << command << std::endl;
            }
        }
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;
    } catch (const std::domain_error& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}
