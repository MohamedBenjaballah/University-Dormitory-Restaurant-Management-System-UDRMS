#pragma once
#include "Room.h"
#include "Restaurant.h"
#include <vector>
#include <string>

class Dormitory
{
private:
    std::string name;
    int capacity; // max total students
    std::vector<Room> rooms;
    Restaurant restaurant; // composition: exactly one per dormitory

public:
    Dormitory(const std::string &name, int capacity);

    // Room management
    void addRoom(int roomNumber, int roomCapacity);
    void removeRoom(int roomNumber);
    Room *findRoom(int roomNumber);

    // Student management
    void assignStudentToRoom(const Student &s, int roomNumber);
    void removeStudentFromRoom(const std::string &studentId, int roomNumber);
    bool isStudentInDormitory(const std::string &studentId) const;

    // Display
    void displayRooms() const;
    void displayAvailableRooms() const;
    void display() const;

    // Accessors
    std::string getName() const;
    int getCapacity() const;
    int getOccupancy() const;
    Restaurant &getRestaurant();
    const Restaurant &getRestaurant() const;
    const std::vector<Room> &getRooms() const;

    // Persistence
    void saveToFile(const std::string &dir) const;
    void loadFromFile(const std::string &dir);
};
