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

    int getValue();

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

int Number::getValue() {
    return this->default_value;
}


class Super_Number: public Number {
public:
    Super_Number(int defaultValue) : Number(defaultValue) {}
    Super_Number() : Number(0) {}
    Super_Number(Super_Number & number) : Number(number) {}

    Super_Number* applyValue(int value);

    Super_Number* degressValue(int value);
};

Super_Number * Super_Number::degressValue(int value) {
    return new Super_Number(this->getValue() - value);
}

Super_Number * Super_Number::applyValue(int value) {
    return new Super_Number(this->getValue() + value);
}


int main() {

    cout << "Variant 6!" << endl;

    auto number = new Super_Number(8);
    number->showValue();
    cout << endl;
    cout<< number->isEquals(8)<<endl;
    cout << endl;
    number->setValue(22);
    number->showValue();
    cout << endl;
    auto gg = number->degressValue(10);
    gg->showValue();
    cout << endl;
    auto temp = number->applyValue(110);
    temp->showValue();
    cout << endl;
}

string getValueInSystem(int value, int system) {

    string result = "";

    while (value != 0) {
        result = to_string(value % system) + result;
        value /= system;
    }

    return result;
}