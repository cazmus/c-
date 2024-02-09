#include <iostream>
#include "windows.h"
#include <string>

using namespace std;

bool parseIntegerError(const string &input, int &output);

int readLimitedInt(int max, int min, const string variableName);

int readInt(string variableName);

bool readBoolean(string variableName);

bool enterLimit(int max, int min, int value);

struct Data {
    int number, month, year;
};

struct Temperature {
    int day, night;
};

struct Template {
    Temperature temperature;
    Data data;
    //Осадки
    bool precipitation;
};


struct List {
    Template *dynamicList = new Template[0];
    int size = 0;

    Template get(int index) {
        return dynamicList[index];
    }

    void remove(int index) {

        if (size == 0 || size <= index) {
            cout << "Error! Out of range!" << endl;
            return;
        }

        auto *tempDynamicList = new Template[size - 1];
        int isRemoved = false;

        for (int i = 0; i < size; i++) {

            if (i == index) {
                isRemoved = true;
                continue;
            }

            tempDynamicList[i - isRemoved] = dynamicList[i];
        }

        delete[] dynamicList;
        dynamicList = tempDynamicList;
        size--;
    }

    void clear() {
        delete[] dynamicList;
        dynamicList = new Template[size];
        size = 0;
    }

    void add(Template newTemplate) {
        auto *tempDynamicList = new Template[size + 1];

        if (size > 0) {
            for (int i = 0; i < size; i++) {
                tempDynamicList[i] = dynamicList[i];
            }
        }

        tempDynamicList[size] = newTemplate;
        delete[] dynamicList;

        dynamicList = tempDynamicList;
        size++;
    }

};


int main() {
    cout << "Variant 6!" << endl;
    cout << "Start terminal! Please enter 'help' to information!" << endl;

    auto list = new List();

    while (true) {
        string command;
        getline(cin, command);


        if (command == "data" || command == "d") {

            if (list->size == 0) {
                cout << "Your list is empty! You need to add new elements" << endl;
                cout << "Enter 'h' or 'help' to get program instruction!" << endl;
                continue;
            }

            cout << "List size is: " << list->size << endl;

            for (int i = 0; i < list->size; i++) {
                cout << endl << "Element number " << i << endl;
                Template aTemplate = list->get(i);
                cout << "Temperature day is " << aTemplate.temperature.day << endl;
                cout << "Temperature night is " << aTemplate.temperature.night << endl;
                cout << "Data number is " << aTemplate.data.number << endl;
                cout << "Data month is " << aTemplate.data.month << endl;
                cout << "Data year is " << aTemplate.data.year << endl;
                cout << "Precipitation is " << aTemplate.precipitation << endl;
            }
        } else if (command == "add" || command == "a") {

            Template aTemplate = {
                    {
                        readLimitedInt(60, -60, "day temperature"),
                        readLimitedInt(60, -60, "night temperature")
                     }, {
                        readLimitedInt(31, 1, "number"),
                        readLimitedInt(12, 1, "month"),
                        readLimitedInt(2024, 1, "year")
                     },
                        readBoolean("precipitation")
            };

            list->add(aTemplate);

            cout << "Succsesfull!" << endl;
        } else if (command == "remove" || command == "r") {

            int index = readLimitedInt(list->size - 1, 0, "index");

            list->remove(index);

            cout << "Succsesfull!" << endl;
        } else if (command == "clear" || command == "c") {

            list->clear();

            cout << "Succsesfull!" << endl;
        } else if (command == "exit" || command == "e") {
            return 0;
        } else if (command == "task" || command == "t") {

            if (list->size == 0) {
                cout << "Your list is empty! You need to add new elements" << endl;
                cout << "Enter 'h' or 'help' to get program instruction!" << endl;
                continue;
            }

            int task = readLimitedInt(3, 1, "task id"), result, iteration_count = 0;

            switch(task) {
                case 1:
                    result = 61;
                    for(int i = 0; i < list->size; i++) {
                        Template aTemplate = list->get(i);
                        if(aTemplate.data.month == 12 || aTemplate.data.month == 1 || aTemplate.data.month == 2) {
                            result = min(result, aTemplate.temperature.day);
                            iteration_count++;
                        }
                    }
                    break;
                case 2:
                    result = 0;
                    for(int i = 0; i < list->size; i++) {
                        Template aTemplate = list->get(i);
                        result += aTemplate.temperature.day;
                        iteration_count++;
                    }
                    result /= list->size;
                    break;
                case 3:
                    result = 61;
                    for(int i = 0; i < list->size; i++) {
                        Template aTemplate = list->get(i);
                        if(aTemplate.data.month == 6 || aTemplate.data.month == 7 || aTemplate.data.month == 8) {
                            result = min(result, aTemplate.temperature.night);
                            iteration_count++;
                        }
                    }
                    break;
            }
            if(iteration_count == 0) {
                cout << "Not enouth data, add more templates!" << endl;
            } else {
                cout << "Task answer is " << result << endl;
            }

        } else {
            cout << "Enter 'h' or 'help' to get program instruction!" << endl;
            cout << "Enter 'd' or 'data' to get data!" << endl;
            cout << "Enter 'a' or 'add' to add data!" << endl;
            cout << "Enter 'r' or 'remove' to remove data!" << endl;
            cout << "Enter 'c' or 'clear' to clear data!" << endl;
            cout << "Enter 'e' or 'exit' to close program!" << endl;
            cout << "Enter 't' or 'task' to complete task!" << endl;
        }

    }
}

bool readBoolean(string variableName) {
    string temp_value;

    cout << "Enter value " << variableName << ":" << endl;

    getline(cin, temp_value);

    return temp_value != "false";
}


int readLimitedInt(int max, int min, string variableName) {

    int value = readInt(variableName);

    if (enterLimit(max, min, value)) return value;

    cout << "Your number is out of range! Range is [" << min << ";" << max << "]" << endl;

    return readLimitedInt(max, min, variableName);
}


bool parseIntegerError(const string &input, int &output) {

    try {
        output = stoi(input);
    } catch (exception) {
        return true;
    }

    return false;
}


int readInt(string variableName) {

    cout << "Enter value " << variableName << ":" << endl;

    int result;
    string temp_value;

    getline(cin, temp_value);

    while (parseIntegerError(temp_value, result)) {
        cout << "Error, your enter not int!" << endl;
        cout << "Enter value " << variableName << ":" << endl;
        getline(cin, temp_value);
    }

    return result;
}

bool enterLimit(int max, int min, int value) {
    return value >= min && max >= value;
}