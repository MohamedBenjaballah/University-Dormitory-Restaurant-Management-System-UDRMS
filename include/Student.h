#pragma once
#include <string>
#include <iostream>

class Student
{
private:
    std::string studentId;
    std::string fullName;
    int academicYear;

public:
    Student(const std::string &id, const std::string &name, int year);

    std::string getId() const;
    std::string getName() const;
    int getYear() const;
    std::string getInfo() const;

    void display() const;

    bool operator==(const Student &other) const;
    bool operator==(const std::string &id) const;
};
