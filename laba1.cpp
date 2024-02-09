#include <iostream>
#include "windows.h"

using namespace std;

float readNextFloat(string name);

float getMin(float a, float b, float c);

float doTask(float a, float b, float c, float d);

float getMax(float a, float b, float c);

int main() {
    SetConsoleOutputCP(CP_UTF8);
    cout << "Вариант №6!" << endl;
    float a = readNextFloat("a"), b = readNextFloat("b"), c = readNextFloat("c"), d = readNextFloat("d");

    if (getMin(a, b, c) == 0) {
        cout << "Ошибка! Знаменатель равен 0!" << endl;
        cout << "Программа перезапустилла работу, введите все значения заного!" << endl;
        return main();
    }
    cout << "Ваш ответ: " << doTask(a, b, c, d) << endl;

    return main();
}

float doTask(float a, float b, float c, float d) {
    return (getMax(a, b, c) * getMin(a, c, d) - getMax(b, c, d)) / getMin(a, b, c);
}

float getMin(float a, float b, float c) {
    return min(a, min(b, c));
}

float getMax(float a, float b, float c) {
    return max(a, max(b, c));
}

float readNextFloat(string name) {
    float temp_value;
    cout << "Введите число: " << name << endl;
    cin >> temp_value;
    return temp_value;
}