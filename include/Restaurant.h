#pragma once
#include "Menu.h"
#include <string>
#include <set>

class Restaurant
{
private:
    std::string name;
    Menu menu;
    int mealsServed;
    std::set<std::string> servedToday; // student IDs served today

public:
    explicit Restaurant(const std::string &name = "University Restaurant");

    void setMenu(MealType type, const std::string &items);
    void displayMenu() const;
    bool serveMeal(const std::string &studentId);
    void resetDailyCount();
    int getMealsServed() const;

    const Menu &getMenu() const;
    std::string getName() const;
    void setName(const std::string &n);

    void display() const;

    // Persistence
    void saveToFile(const std::string &path) const;
    void loadFromFile(const std::string &path);
};
