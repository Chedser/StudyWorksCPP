#include "IOManager_h.h"

using namespace Vectorlfex;

string IOManager::GetManual() {
    string manual = "Поддерживаемые опции запуска:\n\
    -help или -h - справка\n\
    [N] - выбор рецепта кофе:\n\
    1 - Espresso\n\
    2 - Lungo\n\
    3 - Melange\n";

    return manual;
}


bool IOManager::FileExists(string fileName) {
    bool isExist = false;
    std::ifstream fin(fileName.c_str());

    if (fin.is_open())isExist = true;

    fin.close();
    return isExist;
}

bool IOManager::FileIsEmpty(string fileName) {
   bool isExist = false;

    ifstream fin(fileName, std::ios_base::in); // Открываем файл для чтения
    if (!fin.is_open()) {
        throw std::runtime_error("Ошибка открытия файла\n");
    }

    int symCount = 0;
    char c;

    while (!fin.eof()) {
        fin >> c;
        ++symCount;
    }

    fin.close();
    return (symCount == 1 || symCount == 0) ? true : false;
}

bool IOManager::IsDigit(string str) {
    if (str.empty()) { return false; }

    bool isDigit = true;
    for (char s : str) {
        if (!isdigit(s)) {
            isDigit = false;
            break;
        }
    }
    return isDigit;
}
