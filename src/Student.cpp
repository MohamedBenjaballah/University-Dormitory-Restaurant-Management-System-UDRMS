#include "Student.h"
#include <sstream>

Student::Student(const std::string& id, const std::string& name, int year)
    : studentId(id), fullName(name), academicYear(year) {}

std::string Student::getId()   const { return studentId; }
std::string Student::getName() const { return fullName; }
int         Student::getYear() const { return academicYear; }

std::string Student::getInfo() const {
    std::ostringstream oss;
    oss << "[" << studentId << "] " << fullName << " (Year " << academicYear << ")";
    return oss.str();
}

void Student::display() const {
    std::cout << "  Student ID   : " << studentId    << "\n"
              << "  Full Name    : " << fullName      << "\n"
              << "  Academic Year: " << academicYear  << "\n";
}

bool Student::operator==(const Student& other) const {
    return studentId == other.studentId;
}
bool Student::operator==(const std::string& id) const {
    return studentId == id;
}
