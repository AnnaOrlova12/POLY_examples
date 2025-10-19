#include <iostream>
using namespace std;

class Rectangle {
private:
    double width;
    double height;

public:
    // Дефолтный конструктор
    Rectangle() : width(0.0), height(0.0) {
        cout << "Default constructor called" << endl;
    }

    // Параметризованный конструктор
    Rectangle(double w, double h) : width(w), height(h) {
        cout << "Parameterized constructor called" << endl;
    }

    // Конструктор копирования
    Rectangle(const Rectangle& other) : width(other.width), height(other.height) {
        cout << "Copy constructor called" << endl;
    }

    // Деструктор
    ~Rectangle() {
        cout << "Destructor called for rectangle (" << width << "x" << height << ")" << endl;
    }

    // Getters
    double getWidth() const {
        return width;
    }

    double getHeight() const {
        return height;
    }

    // Setters
    void setWidth(double w) {
        width = w;
    }

    void setHeight(double h) {
        height = h;
    }

    // Метод для вывода информации
    void display() const {
        cout << "Rectangle: " << width << "x" << height << endl;
    }

    // Метод для вычисления площади
    double getArea() const {
        return width * height;
    }

    /*bool operator<(Rectangle& rect) const {
        return getArea() < rect.getArea();
    }*/

};

// 1. Передача в функцию по значению - вызывает конструктор копирования
void passByValue(Rectangle rect) {
    cout << "Inside passByValue function:" << endl;
    rect.display();
}

// 2. Возврат из функции по значению - вызывает конструктор копирования
Rectangle returnByValue() {
    cout << "Inside returnByValue function:" << endl;
    Rectangle temp(7.0, 8.0);
    return temp;
}

// 3. Возврат из функции по значению (создание объекта прямо в return)
Rectangle* createDynamicRectangle(double w, double h) {
    cout << "Inside createDynamicRectangle function:" << endl;
    Rectangle* rect = new Rectangle(w, h);
    return rect;
}

int main() {
    cout << "=== 1. Default constructor ===" << endl;
    Rectangle rect1;
    rect1.display();
    cout << endl;

    cout << "=== 2. Parameterized constructor ===" << endl;
    Rectangle rect2(5.0, 3.0);
    rect2.display();
    cout << endl;

    cout << ((rect1 < rect2) ? "smaller"  : "bigger") << endl;

    cout << "=== 3. Copy initialization (assignment syntax) ===" << endl;
    Rectangle rect3 = rect2;  // Инициализация через присваивание
    rect3.display();
    cout << endl;

    cout << "=== 4. Explicit copy initialization ===" << endl;
    Rectangle rect4(rect2);  // Явная инициализация
    rect4.display();
    cout << endl;

    cout << "=== 5. Pass by value to function ===" << endl;
    passByValue(rect2);  // Передача в функцию по значению
    cout << endl;

    cout << "=== 6. Return by value from function ===" << endl;
    Rectangle rect5 = returnByValue();  // Возврат из функции по значению
    rect5.display();
    cout << endl;

    cout << "=== 7. Return pointer from function ===" << endl;
    Rectangle* rect6 = createDynamicRectangle(10.0, 12.0);
    rect6->display();
    cout << endl;

    cout << "=== All objects going out of scope - destructors will be called ===" << endl;
    delete rect6;
    return 0;
}
