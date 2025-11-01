#include <iostream>
using namespace std;

// Класс с SHALLOW COPY (неправильная реализация)
class DynamicArrayShallow {
private:
    int* data;
    int size;

public:
    // Конструктор
    DynamicArrayShallow(int s) : size(s) {
        data = new int[size];
        cout << "[Shallow] Constructor called, allocated memory at " << data << endl;
        for (int i = 0; i < size; i++) {
            data[i] = i * 10;
        }
    }

    // SHALLOW COPY - компилятор создает такой конструктор по умолчанию
    // Копирует только указатель, а не данные!
    DynamicArrayShallow(const DynamicArrayShallow& other) : data(other.data), size(other.size) {
        cout << "[Shallow] Copy constructor called, copied pointer " << data << endl;
        cout << "[Shallow] WARNING: Both objects point to the SAME memory!" << endl;
    }

    // Деструктор
    ~DynamicArrayShallow() {
        cout << "[Shallow] Destructor called for memory at " << data << endl;
        delete[] data;
    }

    void display() const {
        cout << "[Shallow] Array at " << data << ": ";
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    void modify(int index, int value) {
        if (index >= 0 && index < size) {
            data[index] = value;
        }
    }

    int* getDataPointer() const {
        return data;
    }
};

// Класс с DEEP COPY (правильная реализация)
class DynamicArrayDeep {
private:
    int* data;
    int size;

public:
    // Конструктор
    DynamicArrayDeep(int s) : size(s) {
        data = new int[size];
        cout << "[Deep] Constructor called, allocated memory at " << data << endl;
        for (int i = 0; i < size; i++) {
            data[i] = i * 10;
        }
    }

    // DEEP COPY - создает полную независимую копию данных
    DynamicArrayDeep(const DynamicArrayDeep& other) : size(other.size) {
        data = new int[size];  // Выделяем НОВУЮ память
        cout << "[Deep] Copy constructor called, allocated NEW memory at " << data << endl;
        cout << "[Deep] Copying data from " << other.data << " to " << data << endl;

        // Копируем данные
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }
    }

    // Оператор присваивания (Deep Copy)
    DynamicArrayDeep& operator=(const DynamicArrayDeep& other) {
        cout << "[Deep] Assignment operator called" << endl;

        // 1. Проверка на самоприсваивание
        if (this == &other) {
            cout << "[Deep] Self-assignment detected, returning *this" << endl;
            return *this;
        }

        // 2. Освобождаем старую память
        cout << "[Deep] Deleting old memory at " << data << endl;
        delete[] data;

        // 3. Копируем размер
        size = other.size;

        // 4. Выделяем новую память
        data = new int[size];
        cout << "[Deep] Allocated new memory at " << data << endl;

        // 5. Копируем данные
        for (int i = 0; i < size; i++) {
            data[i] = other.data[i];
        }

        return *this;
    }

    // Деструктор
    ~DynamicArrayDeep() {
        cout << "[Deep] Destructor called for memory at " << data << endl;
        delete[] data;
    }

    void display() const {
        cout << "[Deep] Array at " << data << ": ";
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    void modify(int index, int value) {
        if (index >= 0 && index < size) {
            data[index] = value;
        }
    }

    int* getDataPointer() const {
        return data;
    }
};

void demonstrateShallowCopy() {
    cout << "\n========================================" << endl;
    cout << "ДЕМОНСТРАЦИЯ SHALLOW COPY (ПРОБЛЕМА!)" << endl;
    cout << "========================================\n" << endl;

    DynamicArrayShallow arr1(5);
    arr1.display();

    cout << "\n--- Creating copy ---" << endl;
    DynamicArrayShallow arr2 = arr1;  // Shallow copy
    arr2.display();

    cout << "\n--- Pointers comparison ---" << endl;
    cout << "arr1 pointer: " << arr1.getDataPointer() << endl;
    cout << "arr2 pointer: " << arr2.getDataPointer() << endl;
    cout << "Are they the same? " << (arr1.getDataPointer() == arr2.getDataPointer() ? "YES!" : "NO") << endl;

    cout << "\n--- Modifying arr2[0] to 999 ---" << endl;
    arr2.modify(0, 999);
    cout << "arr1: ";
    arr1.display();
    cout << "arr2: ";
    arr2.display();
    cout << "PROBLEM: Modifying arr2 also changed arr1!" << endl;

    cout << "\n--- Objects going out of scope ---" << endl;
    cout << "WARNING: Double deletion will occur (crash or undefined behavior)!" << endl;
}

void demonstrateDeepCopy() {
    cout << "ДЕМОНСТРАЦИЯ DEEP COPY (ПРАВИЛЬНО!)" << endl;
  
    DynamicArrayDeep arr1(5);
    arr1.display();

    cout << "\n--- Creating copy ---" << endl;
    DynamicArrayDeep arr2 = arr1;  // Deep copy
    arr2.display();

    cout << "\n--- Pointers comparison ---" << endl;
    cout << "arr1 pointer: " << arr1.getDataPointer() << endl;
    cout << "arr2 pointer: " << arr2.getDataPointer() << endl;
    cout << "Are they different? " << (arr1.getDataPointer() != arr2.getDataPointer() ? "YES!" : "NO") << endl;

    cout << "\n--- Modifying arr2[0] to 999 ---" << endl;
    arr2.modify(0, 999);
    cout << "arr1: ";
    arr1.display();
    cout << "arr2: ";
    arr2.display();
    cout << "SUCCESS: Arrays are independent!" << endl;

    cout << "\n--- Objects going out of scope ---" << endl;
}

void demonstrateAssignmentOperator() {
    cout << "\n========================================" << endl;
    cout << "ДЕМОНСТРАЦИЯ ОПЕРАТОРА ПРИСВАИВАНИЯ" << endl;
    cout << "========================================\n" << endl;

    DynamicArrayDeep arr1(5);
    arr1.display();

    DynamicArrayDeep arr2(3);
    arr2.display();

    cout << "\n--- Assignment: arr2 = arr1 ---" << endl;
    arr1 = arr1;

    cout << "\nAfter assignment:" << endl;
    cout << "arr1: ";
    arr1.display();
    cout << "arr2: ";
    arr2.display();

    cout << "\n--- Modifying arr2[1] to 777 ---" << endl;
    arr2.modify(1, 777);
    cout << "arr1: ";
    arr1.display();
    cout << "arr2: ";
    arr2.display();

    cout << "\n--- Testing self-assignment: arr1 = arr1 ---" << endl;
    arr1 = arr1;

    cout << "\n--- Objects going out of scope ---" << endl;
}

int main() {
    cout << "==================================================" << endl;
    cout << "SHALLOW COPY vs DEEP COPY DEMONSTRATION" << endl;
    cout << "==================================================" << endl;

    // ВНИМАНИЕ: Эта демонстрация может вызвать краш из-за double deletion!
    // Раскомментируйте на свой риск:
    // demonstrateShallowCopy();

    cout << "\n\nNOTE: Shallow copy demonstration is commented out to prevent crash." << endl;
    cout << "Uncomment demonstrateShallowCopy() to see the problem (may crash).\n" << endl;

    // demonstrateDeepCopy();

    demonstrateAssignmentOperator();

    cout << "\n==================================================" << endl;
    cout << "PROGRAM ENDED SUCCESSFULLY" << endl;
    cout << "==================================================" << endl;

    return 0;
}
