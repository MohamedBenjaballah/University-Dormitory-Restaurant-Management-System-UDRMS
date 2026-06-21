#include "Dormitory.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>

Dormitory::Dormitory(const std::string& n, int cap)
    : name(n), capacity(cap), restaurant(n + " Restaurant") {}

// ── Room management ───────────────────────────────────────────────────────────

void Dormitory::addRoom(int number, int roomCap) {
    if (findRoom(number))
        throw std::runtime_error("Room " + std::to_string(number) + " already exists.");
    rooms.emplace_back(number, roomCap);
}

void Dormitory::removeRoom(int number) {
    auto it = std::find_if(rooms.begin(), rooms.end(),
                           [number](const Room& r){ return r.getRoomNumber() == number; });
    if (it == rooms.end())
        throw std::runtime_error("Room " + std::to_string(number) + " not found.");
    rooms.erase(it);
}

Room* Dormitory::findRoom(int number) {
    auto it = std::find_if(rooms.begin(), rooms.end(),
                           [number](const Room& r){ return r.getRoomNumber() == number; });
    return (it != rooms.end()) ? &(*it) : nullptr;
}

// ── Student management ────────────────────────────────────────────────────────

void Dormitory::assignStudentToRoom(const Student& s, int roomNumber) {
    if (getOccupancy() >= capacity)
        throw std::runtime_error("Dormitory " + name + " is at full capacity.");
    Room* r = findRoom(roomNumber);
    if (!r) throw std::runtime_error("Room not found.");
    r->addStudent(s);
}

void Dormitory::removeStudentFromRoom(const std::string& id, int roomNumber) {
    Room* r = findRoom(roomNumber);
    if (!r) throw std::runtime_error("Room not found.");
    r->removeStudent(id);
}

bool Dormitory::isStudentInDormitory(const std::string& id) const {
    for (const auto& r : rooms)
        if (r.hasStudent(id)) return true;
    return false;
}

// ── Display ───────────────────────────────────────────────────────────────────

void Dormitory::displayRooms() const {
    std::cout << "Rooms in " << name << ":\n";
    for (const auto& r : rooms) r.display();
}

void Dormitory::displayAvailableRooms() const {
    std::cout << "Available rooms in " << name << ":\n";
    for (const auto& r : rooms)
        if (!r.isFull())
            std::cout << "  Room " << r.getRoomNumber()
                      << " (" << r.getOccupancy() << "/" << r.getCapacity() << ")\n";
}

void Dormitory::display() const {
    std::cout << "Dormitory : " << name << "\n"
              << "Capacity  : " << getOccupancy() << "/" << capacity << "\n";
    displayRooms();
    restaurant.display();
}

// ── Accessors ─────────────────────────────────────────────────────────────────

std::string Dormitory::getName()     const { return name; }
int         Dormitory::getCapacity() const { return capacity; }

int Dormitory::getOccupancy() const {
    int total = 0;
    for (const auto& r : rooms) total += r.getOccupancy();
    return total;
}

Restaurant&       Dormitory::getRestaurant()       { return restaurant; }
const Restaurant& Dormitory::getRestaurant() const { return restaurant; }
const std::vector<Room>& Dormitory::getRooms() const { return rooms; }

// ── Persistence ───────────────────────────────────────────────────────────────

void Dormitory::saveToFile(const std::string& dir) const {
    std::string path = dir + "/" + name + "_dorm.txt";
    std::ofstream f(path);
    if (!f) return;
    f << name << "\n" << capacity << "\n" << rooms.size() << "\n";
    for (const auto& r : rooms) f << r.serialize() << "\n";
    restaurant.saveToFile(dir + "/" + name + "_rest.txt");
}

void Dormitory::loadFromFile(const std::string& dir) {
    std::string path = dir + "/" + name + "_dorm.txt";
    std::ifstream f(path);
    if (!f) return;
    std::getline(f, name);
    f >> capacity;
    int n; f >> n; f.ignore();
    rooms.clear();
    for (int i = 0; i < n; ++i) {
        std::string line;
        std::getline(f, line);
        rooms.push_back(Room::deserialize(line));
    }
    restaurant.loadFromFile(dir + "/" + name + "_rest.txt");
}
