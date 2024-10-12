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
        std::string name;
        std::string date;
        std::string location;
        int duration;
        std::string instructor;
        std::cout << "Enter Workshop Name: " << std::endl;
        std::getline(std::cin, name);
        std::cout << "Enter Workshop Date: " << std::endl;
        std::getline(std::cin, date);
        std::cout << "Enter Workshop Location: " << std::endl;
        std::getline(std::cin, location);
        std::cout << "Enter Workshop Duration: " << std::endl;
        std::cin >> duration;
        std::cin.ignore();
        std::cout << "Enter Workshop Instructor Name: " << std::endl;
        std::getline(std::cin, instructor);
        return std::make_shared<Workshop>(name, date, location, duration, instructor);
    }
};

class ConcertFactory : public EventFactory {
    public:
    std::shared_ptr<Event> createEvent() {
        std::string name;
        std::string date;
        std::string location;
        std::string bandName;
        std::string genre;
        std::cout << "Enter Concert Name: " << std::endl;
        std::getline(std::cin, name);
        std::cout << "Enter Concert Date: " << std::endl;
        std::getline(std::cin, date);
        std::cout << "Enter Concert Location: " << std::endl;
        std::getline(std::cin, location);
        std::cout << "Enter Concert Band: " << std::endl;
        std::getline(std::cin, bandName);
        std::cout << "Enter Genre of Concert: " << std::endl;
        std::getline(std::cin, genre);
        return std::make_shared<Concert>(name, date, location, bandName, genre);
    }
};


