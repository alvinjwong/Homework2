#include <iostream>
#include <string>




class Event {
    private:
    std::string eventName;
    std::string eventDate;
    std::string location;
    public:
    Event(std::string name, std::string date, std::string location) : eventName(name), eventDate(date), location(location) {}
    void getDetails();
    bool isUpcoming();

};