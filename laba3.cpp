#include <iostream>
#include "windows.h"

using namespace std;

void doTask(int & plusValue, int & minusValue, int * data, int size);


int main() {
    SetConsoleOutputCP(CP_UTF8);
    cout << "Вариант №6!" << endl;
    srand((unsigned) time(NULL));

    int A[12], B[10], SaP, SaM, SbP, SbM;

    for(int & i : A) {
        i = rand() % 20 - 10;
        cout << i << " ";
    }
    cout << endl;

    for(int & i : B) {
        i = rand() % 20 - 10;
        cout << i << " ";
    }
    cout << endl;

    doTask(SaP, SaM, A, 12);
    doTask(SbP, SbM, B, 10);

    cout << "Результат: " << (((double) SaP)*SbM)/(SbP*SbM);

}

void doTask(int & plusValue, int & minusValue, int * data, int size) {
    for(int i = 0; i < size; i++) {
        int tempValue = *(data + i);

        if(tempValue > 0) plusValue += tempValue;
        else minusValue += tempValue;
    }
}
