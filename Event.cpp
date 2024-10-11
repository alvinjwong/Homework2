#include <iostream>
#include <string>
#include <vector>
#include <memory>

//https://www.geeksforgeeks.org/factory-method-pattern-c-design-patterns/
//https://www.geeksforgeeks.org/smart-pointers-cpp/

class Event {
    protected:
    std::string eventName;
    std::string eventDate;
    std::string location;
    public:
    Event(std::string name, std::string date, std::string location) : eventName(name), eventDate(date), location(location) {}
    virtual ~Event();
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

class EventFactory {
public:
    std::shared_ptr<Event> createEvent();
    virtual ~EventFactory();
    
};

class WorkshopFactory : public EventFactory {
public:
    std::shared_ptr<Event> createEvent() {
        std::string name, date, location, instructor;
        int duration;
        std::cout << "Enter Workshop Name: ";
        std::getline(std::cin, name);
        std::cout << "Enter Date (YYYY-MM-DD): ";
        std::getline(std::cin, date);
        std::cout << "Enter Location: ";
        std::getline(std::cin, location);
        std::cout << "Enter Duration (in hours): ";
        std::cin >> duration;
        std::cin.ignore();
        std::cout << "Enter Instructor Name: ";
        std::getline(std::cin, instructor);
        return std::make_shared<Workshop>(name, date, location, duration, instructor);
    }
};
