#pragma once
#include "Student.h"
#include <vector>
#include <stdexcept>

class Room
{
private:
    int roomNumber;
    int capacity;
    std::vector<Student> students;

public:
    Room(int number, int capacity);

    int getRoomNumber() const;
    int getCapacity() const;
    int getOccupancy() const;
    bool isFull() const;
    bool isEmpty() const;

    void addStudent(const Student &s);
    void removeStudent(const std::string &studentId);
    bool hasStudent(const std::string &studentId) const;

    const std::vector<Student> &getStudents() const;

    void display() const;

    // Persistence
    std::string serialize() const;
    static Room deserialize(const std::string &line);
};
