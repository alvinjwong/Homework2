#include <iostream>
#include <string>



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
    bool isUpcoming() {return true;}
};

class Concert : public Event {
    private:
    std::string bandName;
    std::string genre;
    public:
    Concert(std::string name, std::string date, std::string location, std::string bandName, std::string genre) :
    Event(name, date, location), bandName(bandName), genre(genre) {}
    void getDetails() {std::cout << "Event: " << eventName << " Date: " << eventDate << " Location: " << location << " Band Name: " << bandName << " Genre: " << genre << std::endl;}

};