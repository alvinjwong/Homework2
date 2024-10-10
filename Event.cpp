#include <iostream>
#include <string>
#include <ctime>

//https://www.w3schools.com/cpp/cpp_date.asp#:~:text=The%20difftime()%20function%20measures,measuring%20time%20differences%20between%20dates.



class Event {
    protected:
    std::string eventName;
    std::string eventDate;
    std::string location;
    public:
    Event(std::string name, std::string date, std::string location) : eventName(name), eventDate(date), location(location) {}
    void getDetails() {std::cout << "Event: " << eventName << " Date: " << eventDate << " Location: " << location << std::endl;}
    bool isUpcoming() {return true;}
    std::string getName() {return eventName;}
    std::string getDate() {return eventDate;}
    std::string getLocation() {return location;}
};

class Workshop : public Event {
    private:
    int duration;
    std::string instructor;
    public:
    Workshop(std::string name, std::string date, std::string location, int duration, std::string instructor) :
    Event(name, date, location), duration(duration), instructor(instructor) {}
    void getDetails() {std::cout << "Event: " << eventName << " Date: " << eventDate << " Location: " << location << " Duration: " << duration << " Instructor: " << instructor << std::endl;}


};