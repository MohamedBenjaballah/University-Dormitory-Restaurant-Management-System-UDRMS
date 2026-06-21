#pragma once
#include <string>
#include <iostream>

enum class MealType
{
    BREAKFAST,
    LUNCH,
    DINNER
};

class Menu
{
private:
    std::string breakfast;
    std::string lunch;
    std::string dinner;

public:
    Menu();

    void setMeal(MealType type, const std::string &items);
    std::string getMeal(MealType type) const;

    void displayMenu() const;

    // Serialisation helpers
    std::string serialize() const;
    void deserialize(const std::string &data);
};
