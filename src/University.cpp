#include "University.h"
#include <algorithm>
#include <iostream>
#include <fstream>
#include <stdexcept>

University::University(const std::string& n) : name(n) {}

void University::addDormitory(const std::string& dormName, int cap) {
    if (findDormitory(dormName))
        throw std::runtime_error("Dormitory '" + dormName + "' already exists.");
    dormitories.emplace_back(dormName, cap);
}

void University::removeDormitory(const std::string& dormName) {
    auto it = std::find_if(dormitories.begin(), dormitories.end(),
                           [&dormName](const Dormitory& d){ return d.getName() == dormName; });
    if (it == dormitories.end())
        throw std::runtime_error("Dormitory '" + dormName + "' not found.");
    dormitories.erase(it);
}

Dormitory* University::findDormitory(const std::string& dormName) {
    auto it = std::find_if(dormitories.begin(), dormitories.end(),
                           [&dormName](const Dormitory& d){ return d.getName() == dormName; });
    return (it != dormitories.end()) ? &(*it) : nullptr;
}

void University::assignStudentToRoom(const std::string& dormName,
                                     const Student& s, int roomNumber) {
    Dormitory* d = findDormitory(dormName);
    if (!d) throw std::runtime_error("Dormitory not found.");
    d->assignStudentToRoom(s, roomNumber);
}

void University::removeStudent(const std::string& dormName,
                               const std::string& id, int roomNumber) {
    Dormitory* d = findDormitory(dormName);
    if (!d) throw std::runtime_error("Dormitory not found.");
    d->removeStudentFromRoom(id, roomNumber);
}

void University::displayAll() const {
    std::cout << "=== " << name << " ===\n";
    for (const auto& d : dormitories) {
        std::cout << "\n";
        d.display();
    }
}

void University::displayDormitories() const {
    std::cout << "Dormitories in " << name << ":\n";
    for (const auto& d : dormitories)
        std::cout << "  - " << d.getName()
                  << " (" << d.getOccupancy() << "/" << d.getCapacity() << ")\n";
}

std::string University::getName() const { return name; }
const std::vector<Dormitory>& University::getDormitories() const { return dormitories; }

void University::saveAll(const std::string& dir) const {
    std::ofstream idx(dir + "/index.txt");
    idx << dormitories.size() << "\n";
    for (const auto& d : dormitories) {
        idx << d.getName() << "\n";
        d.saveToFile(dir);
    }
}

void University::loadAll(const std::string& dir) {
    std::ifstream idx(dir + "/index.txt");
    if (!idx) return;
    int n; idx >> n; idx.ignore();
    dormitories.clear();
    for (int i = 0; i < n; ++i) {
        std::string dormName;
        std::getline(idx, dormName);
        dormitories.emplace_back(dormName, 0);
        dormitories.back().loadFromFile(dir);
    }
}
