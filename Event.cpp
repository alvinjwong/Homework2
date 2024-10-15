#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>

//the instructions: make run in the terminal
//you get a prompt, you choose 1-5
//you can then create events etc


//https://www.geeksforgeeks.org/factory-method-pattern-c-design-patterns/
//https://www.geeksforgeeks.org/smart-pointers-cpp/

//abstract class to make it easier to implement throughout the code
class Event {
    protected:
    std::string eventName;
    std::string eventDate;
    std::string location;
    public:
    Event(std::string name, std::string date, std::string location) : eventName(name), eventDate(date), location(location) {}
    virtual ~Event();
    virtual void getDetails() = 0;
    bool isUpcoming() {return true;
    //I could not figure out how to do time, when I looked online, it did not make sense to me
    //I couldnt figure out how to make it check the current time with the time I implemented.
    }
    std::string getName() {return eventName;}
    std::string getDate() {return eventDate;}
    std::string getLocation() {return location;}
};
Event::~Event() {}
//deconstructors all throughout

//These classes inherit from the virtual event, its so the workshop and concert can inherit the needed things easier
//both workshop and concert inherit the needed functions and needed data from the virtual event
class Workshop : public Event {
    private:
    int duration;
    std::string instructor;
    public:
    Workshop(std::string name, std::string date, std::string location, int duration, std::string instructor) :
    Event(name, date, location), duration(duration), instructor(instructor) {}
    ~Workshop() override;
    void getDetails() override {std::cout << "Event: " << eventName << " Date: " << eventDate << " Location: " << location << " Duration: " << duration << " Instructor: " << instructor << std::endl;}
    bool isUpcoming() {return true;}
};

Workshop::~Workshop() {}

class Concert : public Event {
    private:
    std::string bandName;
    std::string genre;
    public:
    Concert(std::string name, std::string date, std::string location, std::string bandName, std::string genre) :
    Event(name, date, location), bandName(bandName), genre(genre) {}
    ~Concert() override;
    void getDetails() override {std::cout << "Event: " << eventName << " Date: " << eventDate << " Location: " << location << " Band Name: " << bandName << " Genre: " << genre << std::endl;}

};

Concert::~Concert() {}

//These are the design patterns, the factory method made it really easy to create events, because all i did
//was call these factories, especially the concert and workshop one, and it asks all the needed questions and
//implements them.
class EventFactory {
public:
    virtual std::shared_ptr<Event> createEvent() = 0;
    virtual ~EventFactory();
    
};

EventFactory::~EventFactory() {}

//I used shared pointers so I can store both Workshop and Concert into events with pointers, and then I could
//have everything pointing there without having to create separate pointers, it also manages memory for me
class WorkshopFactory : public EventFactory {
public:
    std::shared_ptr<Event> createEvent() override {
        std::string name;
        std::string date;
        std::string location;
        int duration;
        std::string instructor;
        std::cout << "Enter Workshop Name: " << std::endl;
        std::getline(std::cin, name);
        std::cout << "Enter Workshop Date: (MM-DD-YYYY)" << std::endl;
        std::getline(std::cin, date);
        std::cout << "Enter Workshop Location: " << std::endl;
        std::getline(std::cin, location);
        std::cout << "Enter Workshop Duration: (just type the number, its in hours)" << std::endl;
        std::cin >> duration;
        std::cin.ignore();
        std::cout << "Enter Workshop Instructor Name: " << std::endl;
        std::getline(std::cin, instructor);
        return std::make_shared<Workshop>(name, date, location, duration, instructor);
    }
    ~WorkshopFactory() override {};
};

class ConcertFactory : public EventFactory {
    public:
    std::shared_ptr<Event> createEvent() override {
        std::string name;
        std::string date;
        std::string location;
        std::string bandName;
        std::string genre;
        std::cout << "Enter Concert Name: " << std::endl;
        std::getline(std::cin, name);
        std::cout << "Enter Concert Date: (MM-DD-YYYY)" << std::endl;
        std::getline(std::cin, date);
        std::cout << "Enter Concert Location: " << std::endl;
        std::getline(std::cin, location);
        std::cout << "Enter Concert Band: " << std::endl;
        std::getline(std::cin, bandName);
        std::cout << "Enter Genre of Concert: " << std::endl;
        std::getline(std::cin, genre);
        return std::make_shared<Concert>(name, date, location, bandName, genre);
    }
    ~ConcertFactory() override {};
};

//I had a lot of issue trying to figure out this search pattern
//https://sourcemaking.com/design_patterns/strategy/cpp/1
//https://www.geeksforgeeks.org/strategy-method-design-pattern-c-design-patterns/
//I had to look up many sources to try to figure out a semblence of what is going on
//it is quite useful for the search function
class SearchSPattern {
    public:
    virtual ~SearchSPattern();
    virtual void search(std::vector<std::shared_ptr<Event>>& events) = 0;
};
SearchSPattern::~SearchSPattern() {}

class DateSearch : public SearchSPattern {
    private:
    std::string date;
    public:
    DateSearch(std::string date) : date(date) {}
    void search(std::vector<std::shared_ptr<Event>>& events) override {
        for (auto &event : events) {
            if (event->getDate() == date) {
                event->getDetails();
            }
        }
    }
    ~DateSearch() override {}

};

class LocationSearch : public SearchSPattern {
    private:
    std::string location;
    public:
    LocationSearch(std::string location) : location(location) {}
    void search (std::vector<std::shared_ptr<Event>>& events) override {
        for (auto &event : events) {
            if (event->getLocation() == location) {
                event->getDetails();
            }
        }
    }
    ~LocationSearch() override {}
};
//this my main, that basically asks everything the code needs
int main() {
    bool isActive = true;
    std::vector<std::shared_ptr<Event>> events;
    while (isActive) {
        std::cout << "This is the Event Management System:" << std::endl;
        std::cout << "Enter a number for the option you would like" << std::endl;
        std::cout << "1. Create a new event" << std::endl;
        std::cout << "2. Search for an event" << std::endl;
        std::cout << "3. Display details of event" << std::endl;
        std::cout << "4. List upcoming events" << std::endl;
        std::cout << "5. Exit Program" << std::endl;

        int choice;
        std::cin >> choice;
        switch (choice) {
            case 1: {
                std::cout << "Enter what event you would like to create (Workshop or Concert)" << std::endl;
                std::string type;
                std::cin >> type;
                std::cin.ignore();
                std::shared_ptr<EventFactory> eventF = nullptr;
                if (type == "Workshop" || type == "workshop") {
                    eventF = std::make_shared<WorkshopFactory>();
                } else if (type == "Concert" || type == "concert") {
                    eventF = std::make_shared<ConcertFactory>();
                } else {
                    std::cout << "That event type was not supported" << std::endl;
                    break;
                }
                if (eventF) {
                    events.push_back(eventF->createEvent());
                }
                break;
            }
            case 2: {
                std::cout << "How would you like to search for the event" << std::endl;
                std::cout << "Type 1 for Date, Type 2 for Location" << std::endl;
                int eventChoice;
                std::cin >> eventChoice;
                std::cin.ignore();
                std::shared_ptr<SearchSPattern> searchP = nullptr;
                if (eventChoice == 1) {
                    std::string date;
                    std::cout << "What is the date of the event you need?" << std::endl;
                    std::getline(std::cin, date);
                    searchP = std::make_shared<DateSearch>(date);
                } else if (eventChoice == 2) {
                    std::string location;
                    std::cout << "What is the location of the event you need?" << std::endl;
                    std::getline(std::cin, location);
                    searchP = std::make_shared<LocationSearch>(location);
                } else {
                    std::cout << "That was not a valid option" << std::endl;
                    break;
                }
                if (searchP) {
                    searchP->search(events);
                }
                break;
            }
            case 3: {
                std::cin.ignore();
                std::cout << "What event would you like details for?" << std::endl;
                std::string answer;
                std::getline(std::cin, answer);
                bool eventFound = false;
                for (auto& event : events) {
                    if (event->getName() == answer) {
                        event->getDetails();
                        eventFound = true;
                        break;
                        }
                    }
                    if (eventFound != true) {
                        std::cout << "This event was not found" << std::endl;
                }
                break;
            }
            case 4: {
                for (auto& event : events) {
                    if (event->isUpcoming()) {
                        event->getDetails();
                    }
                }
                break;
            }
            case 5: {
                isActive = false;
                break;
            }
            default: {
                std::cout << "Please enter a valid number" << std::endl;
            }
            }
        }
        return 0;
    }


