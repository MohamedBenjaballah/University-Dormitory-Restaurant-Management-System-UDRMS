#include "University.h"
#include <iostream>
#include <limits>
#include <stdexcept>

static const std::string DATA_DIR = "./data";

// ── helpers ───────────────────────────────────────────────────────────────────

static void clearInput() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static int getInt(const std::string& prompt) {
    int v;
    while (true) {
        std::cout << prompt;
        if (std::cin >> v) { clearInput(); return v; }
        std::cin.clear(); clearInput();
        std::cout << "  [!] Please enter a valid integer.\n";
    }
}

static std::string getLine(const std::string& prompt) {
    std::string s;
    std::cout << prompt;
    std::getline(std::cin, s);
    return s;
}

static void pause() {
    std::cout << "\nPress Enter to continue...";
    std::cin.get();
}

// ── menus ─────────────────────────────────────────────────────────────────────

static void printHeader(const std::string& title) {
    std::cout << "\n\n"
              << title;
    int pad = 29 - (int)title.size();
    for (int i = 0; i < pad; ++i) std::cout << ' ';
    std::cout << "\n\n";
}

void menuRestaurant(Dormitory& dorm) {
    bool back = false;
    while (!back) {
        printHeader("Restaurant");
        std::cout << " 1. Display today's menu\n"
                  << " 2. Set breakfast\n"
                  << " 3. Set lunch\n"
                  << " 4. Set dinner\n"
                  << " 5. Serve meal to student\n"
                  << " 6. Reset daily count\n"
                  << " 0. Back\n";
        switch (getInt(" > ")) {
            case 1: dorm.getRestaurant().displayMenu(); pause(); break;
            case 2: dorm.getRestaurant().setMenu(MealType::BREAKFAST, getLine("Breakfast items: ")); break;
            case 3: dorm.getRestaurant().setMenu(MealType::LUNCH,     getLine("Lunch items: ")); break;
            case 4: dorm.getRestaurant().setMenu(MealType::DINNER,    getLine("Dinner items: ")); break;
            case 5: dorm.getRestaurant().serveMeal(getLine("Student ID: ")); pause(); break;
            case 6: dorm.getRestaurant().resetDailyCount(); std::cout << "Daily count reset.\n"; break;
            case 0: back = true; break;
            default: std::cout << "Invalid option.\n";
        }
    }
}

void menuDormitory(University& uni) {
    bool back = false;
    while (!back) {
        printHeader("Dormitory Manager");
        uni.displayDormitories();
        std::cout << "\n 1. Add dormitory\n"
                  << " 2. Remove dormitory\n"
                  << " 3. Add room\n"
                  << " 4. Assign student to room\n"
                  << " 5. Remove student from room\n"
                  << " 6. Display all rooms\n"
                  << " 7. Manage restaurant\n"
                  << " 0. Back\n";
        int choice = getInt(" > ");
        if (choice == 0) { back = true; continue; }

        try {
            switch (choice) {
                case 1: {
                    std::string n = getLine("Dormitory name: ");
                    int cap = getInt("Capacity: ");
                    uni.addDormitory(n, cap);
                    std::cout << "Dormitory '" << n << "' added.\n";
                    break;
                }
                case 2: {
                    std::string n = getLine("Dormitory name to remove: ");
                    uni.removeDormitory(n);
                    std::cout << "Removed.\n";
                    break;
                }
                case 3: {
                    std::string dn = getLine("Dormitory name: ");
                    Dormitory* d = uni.findDormitory(dn);
                    if (!d) { std::cout << "Not found.\n"; break; }
                    int rnum = getInt("Room number: ");
                    int rcap = getInt("Room capacity: ");
                    d->addRoom(rnum, rcap);
                    std::cout << "Room " << rnum << " added.\n";
                    break;
                }
                case 4: {
                    std::string dn = getLine("Dormitory name: ");
                    std::string id   = getLine("Student ID: ");
                    std::string name = getLine("Student full name: ");
                    int year = getInt("Academic year: ");
                    int rnum = getInt("Room number: ");
                    uni.assignStudentToRoom(dn, Student(id, name, year), rnum);
                    std::cout << "Student assigned.\n";
                    break;
                }
                case 5: {
                    std::string dn = getLine("Dormitory name: ");
                    std::string id = getLine("Student ID: ");
                    int rnum = getInt("Room number: ");
                    uni.removeStudent(dn, id, rnum);
                    std::cout << "Student removed.\n";
                    break;
                }
                case 6: {
                    std::string dn = getLine("Dormitory name: ");
                    Dormitory* d = uni.findDormitory(dn);
                    if (!d) { std::cout << "Not found.\n"; break; }
                    d->displayRooms();
                    pause();
                    break;
                }
                case 7: {
                    std::string dn = getLine("Dormitory name: ");
                    Dormitory* d = uni.findDormitory(dn);
                    if (!d) { std::cout << "Not found.\n"; break; }
                    menuRestaurant(*d);
                    break;
                }
                default: std::cout << "Invalid option.\n";
            }
        } catch (const std::exception& e) {
            std::cout << "[Error] " << e.what() << "\n";
        }
    }
}

// ── main ──────────────────────────────────────────────────────────────────────

int main() {
    University uni("ENSIA University");
    uni.loadAll(DATA_DIR);

    bool running = true;
    while (running) {
        printHeader("UDRMS Main Menu");
        std::cout << " 1. Dormitory & Room Manager\n"
                  << " 2. Display all\n"
                  << " 3. Save data\n"
                  << " 0. Exit\n";
        switch (getInt(" > ")) {
            case 1: menuDormitory(uni); break;
            case 2: uni.displayAll(); pause(); break;
            case 3:
                uni.saveAll(DATA_DIR);
                std::cout << "Data saved to " << DATA_DIR << "\n";
                break;
            case 0:
                uni.saveAll(DATA_DIR);
                std::cout << "Goodbye!\n";
                running = false;
                break;
            default: std::cout << "Invalid option.\n";
        }
    }
    return 0;
}
