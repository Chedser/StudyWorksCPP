#ifndef SW7_H_H_INCLUDED
#define SW7_H_H_INCLUDED
#endif

#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
#include <vector>
#include <limits>

using std::string;
using std::cout;
using std::cin;
using std::ofstream;
using std::ifstream;
using std::vector;

string GetManual(); // Справка
bool IsDigit(string); // Проверка на цифру
void CreateRecords(int,string);// Создание записей
void PrintRecords(int,string); // Вывод записей
bool FileIsEmpty(string); // Проверка файла на пустоту
int GetRecordsCount(string); // Получить количество записей из файла
vector<string> SplitString(string,string); //Разделение записи

string GetManual(){

    string manual = "Поддерживаемые опции запуска:\n\
    -help или -h - запуск программы в режиме получения справки\n\
    -c [N] [file_name] - запуск программы в режиме создания электронной\n\
    таблицы записей, N - количество записей, file_name - имя текстового файла,\n\
    в котором будет сохранен массив(таблица) записей.\n\
    -r [N] [file_name] - запуск программы в режиме чтения содержимого\n\
    текстового файла file_name\n";

    return manual;

}

bool IsDigit(string str){

    if(str.size() == 0){return false;}

    bool isDigit = true;

    for(char s : str){

        if(!isdigit(s)){

            isDigit = false;
            break;

        }

    }

    return isDigit;

}

void CreateRecords(int recordsCount, string fileName){

    ofstream fout(fileName, std::ios::app);

    if(!fout.is_open()){

        cout << "Ошибка открытия файла\n";
        exit(1);

    }

    cout << "Количество записей для ввода " << recordsCount << "\n";

    unsigned int number; // Номер кассы
    string initialsCashier; // Ф.И.О. кассира
    unsigned int ticketsSoldCount; // Количество проданных билетов
    unsigned int revenue; //Суммарная выручка
    string date; // Дата продаж


    for(int i = 0; i < recordsCount; i++){

        cout << "\nВведите запись " << i + 1 << "\n";

        cout << "Введите номер кассы\n";
        cin >> number;
        fout << number << ",";

           cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
         cout << "Введите Ф.И.О. кассира\n";
        getline(cin, initialsCashier);

        fout << initialsCashier << ",";

        cout << "Введите количество проданных билетов\n";
        cin >> ticketsSoldCount;
        cin.get();
        fout << ticketsSoldCount << ",";

        cout << "Введите суммарную выручку\n";
        cin >> revenue;
        fout << revenue << ",";

        cout << "Введите дату\n";
        cin >> date;
        fout << date << "\n";

    }

    fout.flush();
    fout.close();

}

void PrintRecords(int  recordsCount, string fileName){

    ifstream fin(fileName);

    if(!fin.is_open()){

        cout << "Ошибка открытия файла\n";
        exit(1);

    }

    if(FileIsEmpty(fileName)){ //Проверка файла на пустоту

        cout << "Файл пуст\n";
        exit(1);

    }

    int recordsCountInFile = GetRecordsCount(fileName); //  Количество записей в файле
    int recordsCountToPrint = recordsCount; //  Количество записей для отображения пользователю

     // Если  пользователь запросил больше чем надо записей или не больше нуля
    if((recordsCountToPrint > recordsCountInFile) || recordsCountToPrint <= 0){

        recordsCountToPrint = recordsCountInFile;

    }

    int currentRecordsCount = 0; //Счетчик для записей
    vector<string> vectorStr;
    string str;

    while(currentRecordsCount != recordsCountToPrint){

    getline(fin, str);

    vectorStr = SplitString(str, ",");

    for(string str:vectorStr){cout << str << " ";}

    cout << "\n";
    ++currentRecordsCount;
    }


}

bool FileIsEmpty(string fileName){

    ifstream fin(fileName);

    if(!fin.is_open()){throw std::runtime_error("Ошибка открытия файла");}

    int symCount = 0;
    char c;

    while(!fin.eof()){

        fin >> c;
        ++symCount;

    }

    fin.close();

    return (symCount == 1 || symCount == 0)?true:false;

}

int GetRecordsCount(string  fileName){

    ifstream fin(fileName);

    if(!fin.is_open()){throw std::runtime_error("Ошибка открытия файла\n");}

    string str;

    int recordsCount = 0;

    while(getline(fin,str)){

        ++recordsCount;

    }

    fin.close();

    return recordsCount;

}

vector<string> SplitString(string str, string delimiter) {

    std::vector<std::string> splittedString;
    int startIndex = 0;
    int  endIndex = 0;
    while ((endIndex = str.find(delimiter, startIndex)) < str.size())
    {
        std::string val = str.substr(startIndex, endIndex - startIndex);
        splittedString.push_back(val);
        startIndex = endIndex + delimiter.size();
    }
    if (startIndex < str.size())
    {
        std::string val = str.substr(startIndex);
        splittedString.push_back(val);
    }
    return splittedString;

}

