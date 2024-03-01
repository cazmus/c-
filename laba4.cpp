#include <iostream>
#include <string>
#include "iomanip"

using namespace std;

bool parseIntegerError(const string &input, int &output);

int readLimitedInt(int max, int min, string variableName);

int readInt(string variableName);

bool readBoolean(string variableName);

bool enterLimit(int max, int min, int value);

struct Data {
    int number, month, year;

    string getData() {
        return to_string(number) + "." + to_string(month) + "." + to_string(year);
    }
};

struct Temperature {
    int day, night;
};

struct Template {
    Data data;
    Temperature temperature;
    //Осадки
    bool precipitation;
};

template<typename T>

struct List {
    T *dynamicList = new T[0];
    int size = 0;

    T get(int index) {
        if (size == 0 || size <= index) {
            cout << "Error! Out of range!" << endl;
        }

        return dynamicList[index];
    }

    void remove(int index) {
        if (size == 0 || size <= index) {
            cout << "Error! Out of range!" << endl;
            return;
        }

        auto *tempDynamicList = new T[size - 1];
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
        dynamicList = new T[size];
        size = 0;
    }

    void add(T newTemplate) {
        auto *tempDynamicList = new T[size + 1];

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

void sendHelp();

void sendDataInformation(List<Template> *list);

int main() {
    cout << "Variant 6!" << endl;
    sendHelp();
    srand(time(NULL));

    auto list = new List<Template>();

    while (true) {
        string command;
        getline(cin, command);


        if (command == "data" || command == "d" || command == "2") {
            if (list->size == 0) {
                cout << "Your list is empty! You need to add new elements" << endl;
                cout << "Enter 'h' or 'help' to get program instruction!" << endl;
                continue;
            }

            sendDataInformation(list);
        } else if (command == "add" || command == "a" || command == "3") {

            if (readBoolean("auto generate")) {
                for (int i = 0; i < 30; i++) {
                    Template aTemplate = {
                        {rand() % 31 + 1, rand() % 12 + 1, rand() % 2024 + 1},
                        {rand() % 121 - 60, rand() % 121 - 60},
                        rand() % 2 == 1
                    };
                    list->add(aTemplate);
                }
            } else {
                Template aTemplate = {
                    {
                        readLimitedInt(31, 1, "day"),
                        readLimitedInt(12, 1, "month"),
                        readLimitedInt(2024, 1, "year")
                    },
                    {
                        readLimitedInt(60, -60, "day temperature"),
                        readLimitedInt(60, -60, "night temperature")
                    },
                    readBoolean("precipitation")
                };

                list->add(aTemplate);
            }

            cout << "Succsesfull!" << endl;
        } else if (command == "remove" || command == "r" || command == "4") {
            int index = readLimitedInt(list->size - 1, 0, "index");

            list->remove(index);

            cout << "Succsesfull!" << endl;
        } else if (command == "clear") {

            if (readBoolean("agree, that clear the list data")) {
                list->clear();

                cout << "Succsesfull!" << endl;
            }

        } else if (command == "exit" || command == "e" || command == "6") {
            return 0;
        } else if (command == "task" || command == "t" || command == "7") {
            if (list->size == 0) {
                cout << "Your list is empty! You need to add new elements" << endl;
                cout << "Enter 'h' or 'help' to get program instruction!" << endl;
                continue;
            }

            int task = readLimitedInt(3, 1, "task id"), result, iteration_count = 0;
            int temp = 0, tempData[4] = {0, 0, 0, 0}, tempDataSize[4] = {0, 0, 0, 0};

            switch (task) {
                case 1:
                    for (int i = 0; i < list->size; i++) {
                        Template aTemplate = list->get(i);
                        if (aTemplate.data.month == 12 || aTemplate.data.month == 1 || aTemplate.data.month == 2) {
                            if (list->get(temp).data.month != 12 && list->get(temp).data.month != 1 && list->get(temp).data.month != 2 || list->get(i).temperature.day < list->get(temp).temperature.day) {
                                temp = i;
                            }

                            iteration_count++;
                        }
                    }
                    if (iteration_count == 0) {
                        cout << "Not enouth data, add more templates!" << endl;
                    } else {
                        Template aTemplate = list->get(temp);

                        cout << "Task answer is " << aTemplate.data.getData() << endl;
                    }
                    break;
                case 2:

                    for (int i = 0; i < list->size; i++) {
                        Template aTemplate = list->get(i);

                        int index_total;
                        switch (aTemplate.data.month) {
                            case 12: case 1: case 2: index_total = 0; break;
                            case 3: case 4: case 5: index_total = 1; break;
                            case 6: case 7: case 8: index_total = 2; break;
                            default: index_total = 3; break;
                        }

                        tempData[index_total] += aTemplate.temperature.day;
                        tempDataSize[index_total] = tempDataSize[index_total] + 1;
                    }

                    for (int i = 0; i < 4; i++) {
                        string seazon_name;

                        switch (i) {
                            case 0:
                                seazon_name = "zima";
                                break;
                            case 1:
                                seazon_name = "vesna";
                                break;
                            case 2:
                                seazon_name = "leto";
                                break;
                            default:
                                seazon_name = "osenb";
                                break;
                        }

                        cout << "seazon " << seazon_name << " is " << (tempData[i] / static_cast<float>(max(1, tempDataSize[i]))) << endl;
                    }

                    break;
                default:
                    result = 61;
                    for (int i = 0; i < list->size; i++) {
                        Template aTemplate = list->get(i);
                        if (aTemplate.data.month == 6 || aTemplate.data.month == 7 || aTemplate.data.month == 8) {
                            result = min(result, aTemplate.temperature.night);
                            iteration_count++;
                        }
                    }
                    if (iteration_count == 0) {
                        cout << "Not enouth data, add more templates!" << endl;
                    } else {
                        cout << "Task answer is " << result << endl;
                    }
                    break;
            }

        } else if (command != "help" && command != "h" && command != "1") {
            cout << "Error! Not correct data!" << endl;
        }
        sendHelp();
    }
}

void sendDataInformation(List<Template> *list) {
    cout << "List size is: " << list->size << endl;
    cout << string(81, '-') << endl;
    cout << "|" << setw(8) << "Index |" << setw(18) << "Data |" << setw(18) << "Temper night |" << setw(18) <<
            "Temper day |" << setw(18) << "Precipitation |" << endl;
    cout << string(81, '-') << endl;
    for (int i = 0; i < list->size; i++) {
        Template aTemplate = list->get(i);
        cout << "|" << setw(7) << i << "|";
        cout << setw(17) << aTemplate.data.getData() << "|";
        cout << setw(17) << aTemplate.temperature.day << "|";
        cout << setw(17) << aTemplate.temperature.night << "|";
        cout << setw(17) << (aTemplate.precipitation ? "true" : "false") << "|" << endl;
        cout << string(81, '-') << endl;
    }
}

void sendHelp() {
    cout << endl;
    cout << "Help menu" << endl;
    cout << ">> Enter '1' or 'h' or 'help' to get program instruction!" << endl;
    cout << ">> Enter '2' or 'd' or 'data' to get data!" << endl;
    cout << ">> Enter '3' or 'a' or 'add' to add data!" << endl;
    cout << ">> Enter '4' or 'r' or 'remove' to remove data!" << endl;
    cout << ">> Enter 'clear' to clear data!" << endl;
    cout << ">> Enter '6' or 'e' or 'exit' to close program!" << endl;
    cout << ">> Enter '7' or 't' or 'task' to complete task!" << endl;
    cout << endl;
}

bool readBoolean(string variableName) {
    string temp_value;

    cout << "Enter value " << variableName << "! Use 'false', '0' or not to disagree:" << endl;

    getline(cin, temp_value);

    return temp_value != "false" && temp_value != "0" && temp_value != "not";
}


int readLimitedInt(int max, int min, string variableName) {
    int value = readInt(variableName + "! Range is [" + to_string(min) + ";" + to_string(max) + "]");

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
