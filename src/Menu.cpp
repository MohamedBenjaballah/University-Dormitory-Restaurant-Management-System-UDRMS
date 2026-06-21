#include "Menu.h"
#include <sstream>

Menu::Menu() : breakfast("Not set"), lunch("Not set"), dinner("Not set") {}

void Menu::setMeal(MealType type, const std::string& items) {
    switch (type) {
        case MealType::BREAKFAST: breakfast = items; break;
        case MealType::LUNCH:     lunch     = items; break;
        case MealType::DINNER:    dinner    = items; break;
    }
}

std::string Menu::getMeal(MealType type) const {
    switch (type) {
        case MealType::BREAKFAST: return breakfast;
        case MealType::LUNCH:     return lunch;
        case MealType::DINNER:    return dinner;
    }
    return "";
}

void Menu::displayMenu() const {
    std::cout << "  Breakfast : " << breakfast << "\n"
              << "  Lunch     : " << lunch     << "\n"
              << "  Dinner    : " << dinner    << "\n";
}

std::string Menu::serialize() const {
    return breakfast + "|" + lunch + "|" + dinner;
}

void Menu::deserialize(const std::string& data) {
    std::istringstream ss(data);
    std::getline(ss, breakfast, '|');
    std::getline(ss, lunch,     '|');
    std::getline(ss, dinner,    '|');
}
