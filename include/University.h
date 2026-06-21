#pragma once
#include "Dormitory.h"
#include <vector>
#include <string>

class University
{
private:
    std::string name;
    std::vector<Dormitory> dormitories;

public:
    explicit University(const std::string &name);

    // Dormitory management
    void addDormitory(const std::string &dormName, int capacity);
    void removeDormitory(const std::string &dormName);
    Dormitory *findDormitory(const std::string &dormName);

    // Student management (university-level)
    void assignStudentToRoom(const std::string &dormName,
                             const Student &s,
                             int roomNumber);
    void removeStudent(const std::string &dormName,
                       const std::string &studentId,
                       int roomNumber);

    // Display
    void displayAll() const;
    void displayDormitories() const;
    std::string getName() const;

    const std::vector<Dormitory> &getDormitories() const;

    // Persistence
    void saveAll(const std::string &dataDir) const;
    void loadAll(const std::string &dataDir);
};
