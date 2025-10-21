#include <iostream>
#include <cassert>

using namespace std;

class SmartRectangle {
private:
    double width, height;
    static int total_created; // Статический счетчик

    mutable double cached_area; // Mutable кеш
    mutable bool area_valid{false};

    // Приватный валидатор
    bool validateDimensions() const {
        return width > 0 && height > 0;
    }

public:
    SmartRectangle(double w, double h) : width(w), height(h) {
        total_created++;
        if (!validateDimensions()) {
            cout << "Error: Invalid dimensions" << endl;
            width = 0.0;
            height = 0.0;
        }
    }

    ~SmartRectangle() {
        total_created--;
    }

    // Статический метод
    static int getTotalCount() {
        return total_created;
    }

    // Const метод с mutable кешем
    double getArea() const {
        if (!area_valid) {
            cached_area = width * height;
            area_valid = true;
        }
        return cached_area;
    }

    // Функциональный объект для масштабирования
    SmartRectangle operator()(double scale) const {
        return SmartRectangle(width * scale, height * scale);
    }

    // Друзья
    friend ostream& operator<<(ostream& os, const SmartRectangle& r);
    friend class SmartRectangleTest;
};

// Определение статической переменной
int SmartRectangle::total_created = 0;

// Дружественная функция для вывода
ostream& operator<<(ostream& os, const SmartRectangle& r) {
    os << "SmartRectangle[" << r.width << " x " << r.height << "]";
    return os;
}

// Класс для тестирования SmartRectangle
class SmartRectangleTest {
public:
    static void testValidation() {
        cout << "\n=== Testing Validation (with private field access) ===" << endl;

        // Тест с корректными размерами
        SmartRectangle valid(10, 20);
        // Проверяем приватные поля напрямую
        assert(valid.width == 10);
        assert(valid.height == 20);
        assert(valid.validateDimensions() == true);
        cout << "Valid rectangle test passed (width=" << valid.width
             << ", height=" << valid.height << ")" << endl;

        // Тест с некорректными размерами (должен вывести ошибку и установить 0x0)
        SmartRectangle invalid(-5, 10);
        // Проверяем, что приватные поля были скорректированы
        assert(invalid.width == 0);
        assert(invalid.height == 0);
        assert(invalid.validateDimensions() == false);
        cout << "Invalid rectangle test passed (corrected to width=" << invalid.width
             << ", height=" << invalid.height << ")" << endl;

        // Тест с нулевыми размерами
        SmartRectangle zero(0, 5);
        assert(zero.width == 0);
        assert(zero.height == 0);
        assert(zero.validateDimensions() == false);
        cout << "Zero dimension test passed (corrected to width=" << zero.width
             << ", height=" << zero.height << ")" << endl;

        cout << "All validation tests passed!" << endl;
    }

    static void testAreaCaching() {
        cout << "\n=== Testing Area Caching (with private field access) ===" << endl;

        SmartRectangle r(5, 10);

        // Проверяем приватные поля
        assert(r.width == 5);
        assert(r.height == 10);

        // Проверяем начальное состояние кеша
        assert(r.area_valid == false);
        cout << "Initial cache state: area_valid=" << r.area_valid << endl;

        // Первый вызов должен вычислить площадь
        double area1 = r.getArea();
        assert(area1 == 50);
        // Проверяем, что кеш был обновлен
        assert(r.area_valid == true);
        assert(r.cached_area == 50);
        cout << "First area calculation: " << area1
             << " (cached_area=" << r.cached_area
             << ", area_valid=" << r.area_valid << ")" << endl;

        // Второй вызов должен вернуть кешированное значение
        double area2 = r.getArea();
        assert(area2 == 50);
        assert(r.area_valid == true);
        assert(r.cached_area == 50);
        cout << "Second area calculation (from cache): " << area2 << endl;

        // Проверка масштабирования
        SmartRectangle scaled = r(2.0);
        assert(scaled.width == 10);
        assert(scaled.height == 20);
        assert(scaled.getArea() == 200);
        cout << "Scaled rectangle: width=" << scaled.width
             << ", height=" << scaled.height
             << ", area=" << scaled.getArea() << endl;

        cout << "All caching tests passed!" << endl;
    }
};

int main() {
    // Тестируем статический счетчик
    cout << "Initial count: " << SmartRectangle::getTotalCount() << endl;

    SmartRectangle r1(10, 20);
    SmartRectangle r2(5, 15);
    cout << "After creation: " << SmartRectangle::getTotalCount() << endl; // 2

    // Тестируем вывод
    cout << "r1: " << r1 << endl;
    cout << "r2: " << r2 << endl;

    // Тестируем кеширование
    cout << "Area 1: " << r1.getArea() << endl;
    cout << "Area 1 again: " << r1.getArea() << endl;

    // Функциональный объект
    SmartRectangle scaled = r1(2.0);
    cout << "Scaled: " << scaled << endl;

    // Запускаем тесты
    SmartRectangleTest::testValidation();
    SmartRectangleTest::testAreaCaching();

    return 0;
}
