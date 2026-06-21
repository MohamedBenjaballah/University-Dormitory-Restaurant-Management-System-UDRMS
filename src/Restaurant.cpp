#include "Restaurant.h"
#include <iostream>
#include <fstream>

Restaurant::Restaurant(const std::string& n)
    : name(n), mealsServed(0) {}

void Restaurant::setMenu(MealType type, const std::string& items) {
    menu.setMeal(type, items);
}

void Restaurant::displayMenu() const {
    std::cout << "=== Menu: " << name << " ===\n";
    menu.displayMenu();
}

bool Restaurant::serveMeal(const std::string& studentId) {
    if (servedToday.count(studentId)) {
        std::cout << "Student " << studentId << " already served today.\n";
        return false;
    }
    servedToday.insert(studentId);
    ++mealsServed;
    std::cout << "Meal served to student " << studentId << ".\n";
    return true;
}

void Restaurant::resetDailyCount() {
    mealsServed = 0;
    servedToday.clear();
}

int         Restaurant::getMealsServed() const { return mealsServed; }
const Menu& Restaurant::getMenu()        const { return menu; }
std::string Restaurant::getName()        const { return name; }
void        Restaurant::setName(const std::string& n) { name = n; }

void Restaurant::display() const {
    std::cout << "Restaurant : " << name << "\n"
              << "Meals served today: " << mealsServed << "\n";
    menu.displayMenu();
}

void Restaurant::saveToFile(const std::string& path) const {
    std::ofstream f(path);
    if (!f) return;
    f << name << "\n" << mealsServed << "\n" << menu.serialize() << "\n";
}

void Restaurant::loadFromFile(const std::string& path) {
    std::ifstream f(path);
    if (!f) return;
    std::getline(f, name);
    f >> mealsServed; f.ignore();
    std::string mdata;
    std::getline(f, mdata);
    menu.deserialize(mdata);
}
