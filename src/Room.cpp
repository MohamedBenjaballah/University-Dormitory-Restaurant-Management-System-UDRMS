#include "Room.h"
#include <algorithm>
#include <sstream>
#include <iostream>

Room::Room(int number, int cap) : roomNumber(number), capacity(cap) {}

int  Room::getRoomNumber() const { return roomNumber; }
int  Room::getCapacity()   const { return capacity; }
int  Room::getOccupancy()  const { return static_cast<int>(students.size()); }
bool Room::isFull()        const { return getOccupancy() >= capacity; }
bool Room::isEmpty()       const { return students.empty(); }

void Room::addStudent(const Student& s) {
    if (isFull())
        throw std::runtime_error("Room " + std::to_string(roomNumber) + " is full.");
    if (hasStudent(s.getId()))
        throw std::runtime_error("Student " + s.getId() + " already in room.");
    students.push_back(s);
}

void Room::removeStudent(const std::string& id) {
    auto it = std::find_if(students.begin(), students.end(),
                           [&id](const Student& s){ return s.getId() == id; });
    if (it == students.end())
        throw std::runtime_error("Student " + id + " not found in room.");
    students.erase(it);
}

bool Room::hasStudent(const std::string& id) const {
    return std::any_of(students.begin(), students.end(),
                       [&id](const Student& s){ return s.getId() == id; });
}

const std::vector<Student>& Room::getStudents() const { return students; }

void Room::display() const {
    std::cout << "  Room " << roomNumber
              << " [" << getOccupancy() << "/" << capacity << "]\n";
    for (const auto& s : students)
        std::cout << "    - " << s.getInfo() << "\n";
}

std::string Room::serialize() const {
    std::ostringstream oss;
    oss << roomNumber << "," << capacity;
    for (const auto& s : students)
        oss << ";" << s.getId() << "," << s.getName() << "," << s.getYear();
    return oss.str();
}

Room Room::deserialize(const std::string& line) {
    std::istringstream ss(line);
    std::string token;
    std::getline(ss, token, ',');
    int num = std::stoi(token);
    std::getline(ss, token, ';');
    int cap = std::stoi(token);
    Room r(num, cap);
    while (std::getline(ss, token, ';')) {
        std::istringstream ts(token);
        std::string id, name, yr;
        std::getline(ts, id,   ',');
        std::getline(ts, name, ',');
        std::getline(ts, yr,   ',');
        r.addStudent(Student(id, name, std::stoi(yr)));
    }
    return r;
}
