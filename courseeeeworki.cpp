#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <thread>
#include <chrono>
#include <algorithm>

using namespace std;

class MenuItem {
private:
    int id;
    string name;
    int quantity;
    float price;

public:
    MenuItem(int _id, string _name, int _quantity, float _price) 
        : id(_id), name(_name), quantity(_quantity), price(_price) {}

    int getId() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    float getPrice() const { return price; }
    void setQuantity(int _quantity) { quantity = _quantity; }
};

class FoodSet {
private:
    int id;
    string name;
    vector<MenuItem> items;
    float price;

public:
    FoodSet(int _id, string _name, const vector<MenuItem>& _items, float _price) 
        : id(_id), name(_name), items(_items), price(_price) {}

    int getId() const { return id; }
    string getName() const { return name; }
    vector<MenuItem> getItems() const { return items; }
    float getPrice() const { return price; }
};

class Order {
private:
    vector<MenuItem> items;
    vector<FoodSet> sets;
    int orderId;
    static int nextId;
public:
    Order() : orderId(nextId++) {}

    void addItem(const MenuItem& item, int quantity) {
        MenuItem orderedItem = item;
        orderedItem.setQuantity(quantity);
        items.push_back(orderedItem);
    }

    void addSet(const FoodSet& set) {
        sets.push_back(set);
    }

    float calculateTotal() const {
        float total = 0;
        for (const auto& item : items) {
            total += item.getPrice() * item.getQuantity();
        }
        for (const auto& set : sets) {
            total += set.getPrice();
        }
        return total;
    }

    void printOrder() const {
        cout << "Order #" << orderId << "\n";
        for (const auto& item : items) {
            cout << item.getName() << " x " << item.getQuantity() << " = " 
                 << fixed << setprecision(2) << item.getPrice() * item.getQuantity() << "\n";
        }
        for (const auto& set : sets) {
            cout << set.getName() << " = " << fixed << setprecision(2) << set.getPrice() << "\n";
        }
        cout << "Total: " << fixed << setprecision(2) << calculateTotal() << "\n";
    }
};

int Order::nextId = 1;

class User {
private:
    string username;
public:
    User(string _username) : username(_username) {}
    string getUsername() const { return username; }
};

class Admin {
public:
    static const int PASSWORD = 123321;
};

class Payment {
public:
    enum Method { CASH, CREDIT };

    static void processPayment(float amount, Method method) {
        switch (method) {
            case CASH:
                cout << "Paid " << fixed << setprecision(2) << amount << " in cash.\n";
                break;
            case CREDIT:
                cout << "Paid " << fixed << setprecision(2) << amount << " with credit card.\n";
                break;
        }
    }
};

class Receipt {
public:
    static void printReceipt(const Order& order) {
        cout << "****************** Receipt ******************\n";
        order.printOrder();
        cout << "*********************************************\n";
    }
};

class Backup {
public:
    static void performBackup() {
        cout << "Performing system backup...\n";
    }
};

class Report {
public:
    static void generateDailyReport() {
        cout << "Generating daily report...\n";
    }
};

class UI {
public:
    static void clearScreen() {
        system("cls");
    }

    static void delay(int milliseconds) {
        this_thread::sleep_for(chrono::milliseconds(milliseconds));
    }

    static void setColor(int colorCode) {
        // Windows specific function
        // HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        // SetConsoleTextAttribute(hConsole, colorCode);
    }

    static void welcomeMessage() {
        cout << "*********************************************\n";
        cout << "*    WELCOME TO THE RESTAURANT SYSTEM       *\n";
        cout << "*********************************************\n";
    }

    static void loadingBar() {
        for (int i = 0; i <= 100; i += 10) {
            clearScreen();
            cout << "Loading: " << i << "%\n";
            cout << "[";
            for (int j = 0; j < i; j += 10) {
                cout << "=";
            }
            cout << "]\n";
            delay(200);
        }
        clearScreen();
    }
};

class Restaurant {
private:
    vector<MenuItem> menu;
    vector<FoodSet> sets;
    vector<MenuItem> drinks;
    vector<Order> orders;

    float totalRevenue;

public:
    Restaurant() : totalRevenue(0) {
        initializeMenu();
        initializeDrinks();
        initializeSets();
    }

    void initializeMenu() {
        menu.push_back(MenuItem(1, "Kotlety", 50, 5.99));
        menu.push_back(MenuItem(1, "Beshbarmak", 10, 8.99));
        menu.push_back(MenuItem(2, "Pure potato", 30, 7.99));
        menu.push_back(MenuItem(3, "Olivie", 20, 4.99));
              menu.push_back(MenuItem(3, "Slice of Bread", 20, 4.99));
    }

    void initializeDrinks() {
        drinks.push_back(MenuItem(101, "Kompot", 100, 1.99));
        drinks.push_back(MenuItem(102, "Zharma", 80, 1.99));
        drinks.push_back(MenuItem(103, "Tea", 70, 1.99));
    }

    void initializeSets() {
        sets.push_back(FoodSet(201, "Kyrgyz Combo", {menu[1], drinks[1]}, 7.99));
        sets.push_back(FoodSet(202, "Russian Combo", {menu[0], drinks[0]}, 9.99));
    }

    void displayMenu() const {
        cout << "Menu:\n";
        for (const auto& item : menu) {
            cout << item.getId() << ". " << item.getName() << " - $" << item.getPrice() 
                 << " (In Stock: " << item.getQuantity() << ")\n";
        }
    }

    void displaySets() const {
        cout << "Sets:\n";
        for (const auto& set : sets) {
            cout << set.getId() << ". " << set.getName() << " - $" << set.getPrice() << "\n";
            for (const auto& item : set.getItems()) {
                cout << "    " << item.getName() << "\n";
            }
        }
    }

    void displayDrinks() const {
        cout << "Drinks:\n";
        for (const auto& drink : drinks) {
            cout << drink.getId() << ". " << drink.getName() << " - $" << drink.getPrice() 
                 << " (In Stock: " << drink.getQuantity() << ")\n";
        }
    }

    bool checkForCancellation(int choice) const {
        if (choice == -1) {
            cout << "Order cancelled. Returning to main menu...\n";
            return true;
        }
        return false;
    }

    void takeOrder() {
        int choice, quantity;
        Order order;

        cout << "Enter -1 at any time to cancel the order and return to the main menu.\n";

        displayMenu();
        cout << "Enter the item number to order (0 to finish): ";
        while (cin >> choice && choice != 0) {
            if (checkForCancellation(choice)) return;
            cout << "Enter quantity: ";
            cin >> quantity;
            if (checkForCancellation(quantity)) return;
            bool itemFound = false;
            for (auto& item : menu) {
                if (item.getId() == choice) {
                    itemFound = true;
                    if (item.getQuantity() >= quantity) {
                        item.setQuantity(item.getQuantity() - quantity);
                        order.addItem(item, quantity);
                    } else {
                        cout << "Not enough stock for " << item.getName() << ".\n";
                    }
                    break;
                }
            }
            if (!itemFound) {
                cout << "Invalid item number. Please try again.\n";
            }
            cout << "Enter the item number to order (0 to finish): ";
        }

        displaySets();
        cout << "Enter the set number to order (0 to finish): ";
        while (cin >> choice && choice != 0) {
            if (checkForCancellation(choice)) return;
            bool setFound = false;
            for (const auto& set : sets) {
                if (set.getId() == choice) {
                    setFound = true;
                    order.addSet(set);
                    break;
                }
            }
            if (!setFound) {
                cout << "Invalid set number. Please try again.\n";
            }
            cout << "Enter the set number to order (0 to finish): ";
        }

        displayDrinks();
        cout << "Enter the drink number to order and the quantity separated by space (0 to finish): ";
        while (cin >> choice && choice != 0) {
            if (checkForCancellation(choice)) return;
            cin >> quantity;
            if (checkForCancellation(quantity)) return;
            bool drinkFound = false;
            for (auto& drink : drinks) {
                if (drink.getId() == choice) {
                    drinkFound = true;
                    if (drink.getQuantity() >= quantity) {
                        drink.setQuantity(drink.getQuantity() - quantity);
                        order.addItem(drink, quantity);
                    } else {
                        cout << "Not enough stock for " << drink.getName() << ".\n";
                    }
                    break;
                }
            }
            if (!drinkFound) {
                cout << "Invalid drink number. Please try again.\n";
            }
            cout << "Enter the drink number to order and the quantity separated by space (0 to finish): ";
        }

        orders.push_back(order);

        float total = order.calculateTotal();
        totalRevenue += total;
        Receipt::printReceipt(order);
        cout << "Select payment method (1. Cash, 2. Credit): ";
        int method;
        cin >> method;
        if (checkForCancellation(method)) return;
        Payment::processPayment(total, static_cast<Payment::Method>(method - 1));
    }

    void adminPanel() {
        int choice;
        cout << "Enter admin password: ";
        cin >> choice;
        if (choice != Admin::PASSWORD) {
            cout << "Incorrect password.\n";
            return;
        }
        do {
            cout << "Admin Panel:\n"
                 << "1. View total revenue\n"
                 << "2. Add new item\n"
                 << "3. Add new set\n"
                 << "4. Remove item\n"
                 << "5. Remove set\n"
                 << "6. Add new drink\n"
                 << "7. Remove drink\n"
                 << "8. View orders\n"
                 << "0. Exit\n";
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "Total revenue: $" << fixed << setprecision(2) << totalRevenue << "\n";
                    break;
                case 2: {
                    int id, quantity;
                    float price;
                    string name;
                    cout << "Enter item ID: ";
                    cin >> id;
                    if (checkForCancellation(id)) return;
                    cout << "Enter item name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter item quantity: ";
                    cin >> quantity;
                    if (checkForCancellation(quantity)) return;
                    cout << "Enter item price: ";
                    cin >> price;
                    if (checkForCancellation(price)) return;
                    menu.push_back(MenuItem(id, name, quantity, price));
                    break;
                }
                case 3: {
                    int id, numItems;
                    float price;
                    string name;
                    vector<MenuItem> items;
                    cout << "Enter set ID: ";
                    cin >> id;
                    if (checkForCancellation(id)) return;
                    cout << "Enter set name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter number of items in the set: ";
                    cin >> numItems;
                    if (checkForCancellation(numItems)) return;
                    for (int i = 0; i < numItems; ++i) {
                        cout << "Enter item ID to add to set: ";
                        int itemId;
                        cin >> itemId;
                        if (checkForCancellation(itemId)) return;
                        for (const auto& item : menu) {
                            if (item.getId() == itemId) {
                                items.push_back(item);
                                break;
                            }
                        }
                    }
                    cout << "Enter set price: ";
                    cin >> price;
                    if (checkForCancellation(price)) return;
                    sets.push_back(FoodSet(id, name, items, price));
                    break;
                }
                case 4: {
                    int id;
                    cout << "Enter item ID to remove: ";
                    cin >> id;
                    if (checkForCancellation(id)) return;
                    menu.erase(remove_if(menu.begin(), menu.end(), [id](const MenuItem& item) {
                        return item.getId() == id;
                    }), menu.end());
                    break;
                }
                case 5: {
                    int id;
                    cout << "Enter set ID to remove: ";
                    cin >> id;
                    if (checkForCancellation(id)) return;
                    sets.erase(remove_if(sets.begin(), sets.end(), [id](const FoodSet& set) {
                        return set.getId() == id;
                    }), sets.end());
                    break;
                }
                case 6: {
                    int id, quantity;
                    float price;
                    string name;
                    cout << "Enter drink ID: ";
                    cin >> id;
                    if (checkForCancellation(id)) return;
                    cout << "Enter drink name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter drink quantity: ";
                    cin >> quantity;
                    if (checkForCancellation(quantity)) return;
                    cout << "Enter drink price: ";
                    cin >> price;
                    if (checkForCancellation(price)) return;
                    drinks.push_back(MenuItem(id, name, quantity, price));
                    cout << "Drink added successfully.\n";
                    break;
                }
                case 7: {
                    int id;
                    cout << "Enter drink ID to remove: ";
                    cin >> id;
                    if (checkForCancellation(id)) return;
                    auto it = find_if(drinks.begin(), drinks.end(), [id](const MenuItem& drink) {
                        return drink.getId() == id;
                    });
                    if (it != drinks.end()) {
                        drinks.erase(it);
                        cout << "Drink removed successfully.\n";
                    } else {
                        cout << "Drink with ID " << id << " not found.\n";
                    }
                    break;
                }
                case 8:
                    for (const auto& order : orders) {
                        order.printOrder();
                    }
                    break;
                case 0:
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }

    void run() {
        int choice;
        do {
            UI::clearScreen();
            UI::welcomeMessage();
            cout << "Restaurant Management System\n1. Order food\n2. Admin panel\n0. Exit\n";
            cin >> choice;
            switch (choice) {
                case 1:
                    takeOrder();
                    break;
                case 2:
                    adminPanel();
                    break;
                case 0:
                    cout << "Exiting...\n";
                    break;
                default:
                    cout << "Invalid choice.\n";
            }
        } while (choice != 0);
    }
};

int main() {
    UI::loadingBar();
    Restaurant restaurant;
    restaurant.run();
    return 0;
}
