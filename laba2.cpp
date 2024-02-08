#include <iostream>
#include "windows.h"
#include <iomanip>

using namespace std;

void middleArithmetic(int data[18], int number );
void middleArithmeticSecond(int data[18], int number );

int main() {
    SetConsoleOutputCP(CP_UTF8);
    cout << "Вариант №6!" << endl;
    srand((unsigned) time(NULL));

    int data[15][18];


    for(auto& a : data) {
        for(auto& value : a) {
            value = rand()% 20 - 10;
        }
    }

    for(auto& a : data) {
        for(auto& value : a) {
            cout << setw(4) << value << " ";
        }
        cout << endl;
    }

    cout<< endl << "Первый способ" << endl;

    for(int i = 0; i < 15; i+=2) {
        middleArithmetic(data[i], i);
    }

    cout<< endl << "Второй способ" << endl;

    for(int i = 0; i < 15; i+=2) {
        middleArithmeticSecond(*(data + i), i);
    }

}

void middleArithmetic(int data[18], int number ) {

    float temp_result = 0, count_operation = 0;

    for(int i = 1; i < 18; i += 2) {

        if(data[i] < 0) continue;

        temp_result += data[i];
        count_operation++;
    }

    if(count_operation == 0) {
        cout << "К сожалению, все числа строки отрицательные!" << endl;
    } else {
        temp_result /=count_operation;
        cout << "Среднее арифметическое строки " << number << " равно: " << temp_result << endl;
    }
}

void middleArithmeticSecond(int * data, int number ) {

    float temp_result = 0, count_operation = 0;

    for(int i = 1; i < 18; i += 2) {

        if(*(data + i) < 0) continue;

        temp_result += *(data + i);
        count_operation++;
    }

    if(count_operation == 0) {
        cout << "К сожалению, все числа строки отрицательные!" << endl;
    } else {
        temp_result /=count_operation;
        cout << "Среднее арифметическое строки " << number << " равно: " << temp_result << endl;
    }
}