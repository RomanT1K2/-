#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;


class Dish {
private:
    string name;
    double price;
    int    calories;

public:
    Dish() : Dish("Невідома страва", 0.0, 0) {}

    Dish(const string& n, double p, int c = 0)
        : name(n), price(p), calories(c) {
    }

   /* ~Dish() {
        cout << "[Dish] \"" << name << "\" видалена.\n";
    }
    */
    double getPrice() const { return price; }

    void showInfo() const {
        cout << fixed << setprecision(2)
            << "  Страва: " << left << setw(22) << name
            << "| Ціна: " << setw(8) << price
            << "| Калорії: " << calories << "\n";
    }
};


class Menu {
private:
    vector<Dish> dishes;

public:
   /* ~Menu() {
        cout << "[Menu] Меню видалено.\n";
    }
*/
    void addDish(const Dish& d) {
        dishes.push_back(d);
    }

    void showMenu() const {
        cout << "\n======= МЕНЮ =======\n";
        for (size_t i = 0; i < dishes.size(); ++i) {
            cout << "[" << (i + 1) << "] ";
            dishes[i].showInfo();
        }
        cout << "====================\n";
    }
};


class Customer {
private:
    string name;
    string phone;

public:
    Customer() : Customer("Гість", "Немає номера") {}

    Customer(const string& n, const string& p) : name(n), phone(p) {}

   /* ~Customer() {
        cout << "[Customer] \"" << name << "\" видалений.\n";
    }
*/
    void showInfo() const {
        cout << "  Клієнт: " << name << " | Телефон: " << phone << "\n";
    }
};


class Order {
private:
    int          orderID;
    Customer     customer;
    vector<Dish> dishes;
    double       discount;

public:
    Order() : Order(0, Customer()) {}

    Order(int id, const Customer& c, double d = 0.0)
        : orderID(id), customer(c), discount(d) {
    }

    ~Order() {
        cout << "[Order] Замовлення №" << orderID << " закрите.\n";
    }

    void addDish(const Dish& d) {
        dishes.push_back(d);
    }

    double getTotal() const {
        double sum = 0.0;
        for (const auto& d : dishes)
            sum += d.getPrice();
        return sum * (1.0 - discount / 100.0);
    }

    void showOrder() const {
        cout << "\n===== ЗАМОВЛЕННЯ №" << orderID << " =====\n";
        customer.showInfo();
        cout << "  Страви:\n";
        for (const auto& d : dishes)
            d.showInfo();
        cout << fixed << setprecision(2);
        if (discount > 0)
            cout << "  Знижка: " << discount << "%\n";
        cout << "  До сплати: " << getTotal() << " грн\n";
        cout << "========================\n";
    }
};


int main() {
    // Меню
    Menu menu;
	setlocale(LC_ALL, "Ukrainian");
    menu.addDish(Dish("Піцца Маргарита", 180.50, 850));
    menu.addDish(Dish("Борщ Український", 95.00, 320));
    menu.addDish(Dish("Вареники з м'ясом", 120.00, 480));
    menu.addDish(Dish("Салат Цезар", 110.00, 250));
    menu.showMenu();

    // Замовлення 1
    Customer roman("Роман", "+380991234567");
    Order order1(1, roman);
    order1.addDish(Dish("Піцца Маргарита", 180.50, 850));
    order1.addDish(Dish("Салат Цезар", 110.00, 250));
    order1.showOrder();

    // Замовлення 2 зі знижкою 10%
    Customer olena("Олена", "+380671112233");
    Order order2(2, olena, 10.0);
    order2.addDish(Dish("Борщ Український", 95.00, 320));
    order2.addDish(Dish("Вареники з м'ясом", 120.00, 480));
    order2.showOrder();

    // Перевірка ціни через if/else
    double testPrice = -10.0;
    if (testPrice < 0) {
        cout << "\nПомилка: ціна не може бути від'ємною!\n";
    }
    else {
        Dish good("Тест", testPrice);
        good.showInfo();
    }

    return 0;
}