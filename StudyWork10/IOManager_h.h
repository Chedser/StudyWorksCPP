#ifndef IOMANAGER_H
#define IOMANAGER_H


#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <vector>
#include <limits>

using std::cout;
using std::cin;
using std::string;
using std::ofstream;
using std::ifstream;
using std::vector;

class IOManager {

public:

    static  string GetManual(); // Справка
    static bool IsDigit(string); // Проверка на цифру
    static bool FileIsEmpty(string); // Проверка файла на пустоту
    static int GetRecordsCount(string); // Получить количество записей в файле
    static vector<string> SplitString(string, string); // Разбиение строки по разделителю

   static void CreateRecords(int, string, const char*, int); // Создание записей
   static  void PrintRecords(int, string, const char*); // Вывод записей из файла в консоль
   static void InputRecord(std::ostream&, const char*, int); // Ввод одной записи

};
#endif
