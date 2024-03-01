#include <iostream>
#include "string"

using namespace std;


string getValueInSystem(int value, int system);

class Number {

private:
    int octal_value, default_value;

public:
    Number(Number & number) {
        this->setValue(number.default_value + 10);
    }
    Number(int default_value) {
        this->setValue(default_value);
    }

    Number() {
        this->setValue(0);
    }

    ~Number();

    int getOctalValue();

    void showValue();

    bool isEquals(int value);

    void setValue(int value);
};

int Number::getOctalValue() {
    return stoi(getValueInSystem(default_value, 8));
}

void Number::showValue() {
    cout << "Start value is " << this->default_value << endl;
    cout << "Octal value is " << this->octal_value << endl;
}

bool Number::isEquals(int value) {
    return this->default_value == value;
}

void Number::setValue(int value) {
    this->default_value = value;
    this->octal_value = getOctalValue();
}


int main() {

    cout << "Variant 6!" << endl;

    auto number = new Number(8);
    number->showValue();
    cout<< number->isEquals(8)<<endl;
    number->setValue(22);

    number->showValue();


    auto second_number = new Number(* number);
    second_number->showValue();

}

string getValueInSystem(int value, int system) {

    string result = "";

    while (value != 0) {
        result = to_string(value % system) + result;
        value /= system;
    }

    return result;
}