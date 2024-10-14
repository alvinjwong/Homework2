#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <algoritm>

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

class SearchSPattern {
    public:
    virtual ~SearchSPattern();
    virtual void search(std::vector<std::unique_ptr<Event>>& events);
};

class DateSearch : public SearchSPattern {
    private:
    std::string date;
    public:
    DateSearch(std::string date) : date(date) {}
    void search(std::vector<std::unique_ptr<Event>>& events) {
        for (auto &event : events) {
            if (event->getDate() == date) {
                event->getDetails();
            }
        }
    }

};

class LocationSearch : public SearchSPattern {
    private:
    std::string location;
    public:
    LocationSearch(std::string location) : location(location) {}
    void search (std::vector<std::unique_ptr<Event>>& events) {
        for (auto &event : events) {
            if (event->getLocation() == location) {
                event->getDetails();
            }
        }
    }
};

int main() {
    bool isActive = true;
    std::vector<std::unique_ptr<Event>> events;
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

//https://www.geeksforgeeks.org/unique_ptr-in-cpp/
        switch (choice) {
            case 1: {
                std::cout << "Enter what event you would like to create (Workshop or Concert)" << std::endl;
                std::string type;
                std::cin >> type;
                std::shared_ptr<Event> event = nullptr;
                if (type == "Workshop" || type == "workshop") {
                    event = WorkshopFactory::createEvent();
                } else if (type == "Concert" || type == "concert") {
                    event = ConcertFactory::createEvent();
                } else {
                    std::cout << "That event type was not supported" << std::endl;
                    break;
                }
                if (event) {
                    events.push_back(event);
                }
                break;
            }
            case 2: {
                std::cout << "How would you like to search for the event" << std::endl;
                std::cout << "Type 1 for Date, Type 2 for Location" << std::endl;
                int eventChoice;
                std::cin >> eventChoice;
                std::shared_ptr<SearchSPattern> searchP = nullptr;
                if (eventChoice == 1) {
                    std::string date;
                    std::cout << "What is the date of the event you need?" << std::endl;
                    std::cin >> date;
                    searchP = std::shared_ptr<DateSearch>(date);
                } else if (eventChoice == 2) {
                    std::string location;
                    std::cout << "What is the location of the event you need?" << std::endl;
                    std::getline(std::cin, location);
                    searchP = std::shared_ptr<LocationSearch>(location);
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
                    if (eventFound != true) {
                        std::cout << "This event was not found" << std::endl;
                    }
                    break;
                }
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


