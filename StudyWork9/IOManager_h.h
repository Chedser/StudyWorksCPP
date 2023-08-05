#ifndef IOMANAGER_H
#define IOMANAGER_H
#endif

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <limits>
#include "TicketCashier_h.h"

using std::cout;
using std::cin;
using std::string;
using std::ofstream;
using std::ifstream;
using std::vector;

 class IOManager {
	public:
		static  string GetManual(); // Сообщение об аргументах командной строки
        	static bool IsDigit(string); // Проверка на цифру
        	static bool IsDigit(String);
        	static bool FileIsEmpty(string); // Проверка файла на пустоту
        	static int GetRecordsCount(string); // Получить количество записей из файла
        	static vector<string> SplitString(string, string); // Разделение записи

        	static void CreateRecords(int, string, const char*);
        	static  void PrintRecords(int, string, const char*);
};

 string IOManager::GetManual() {
     string manual = "Поддерживаемые опции запуска:\n\
    -help или -h - запуск программы в режиме получения справки\n\
    -c [N] [file_name] - запуск программы в режиме создания электронной\n\
    таблицы записей, N - количество записей, file_name - имя текстового файла,\n\
    в котором будет сохранен массив(таблица) записей.\n\
    -r [N] [file_name] - запуск программы в режиме чтения содержимого\n\
    текстового файла file_name\n";

     return manual;
 }
 
bool IOManager::IsDigit(string str) {
     if (str.size() == 0) { return false; }

     bool isDigit = true;
     for (char s : str) {
         if (!isdigit(s)) {
             isDigit = false;
             break;
         }
     }

     return isDigit;
 }
  
bool IOManager::IsDigit(String str) {
      if (str.GetLen() == 0) { return false; }

      bool isDigit = true;
      const char* cha = str.GetString();

      for (int i = 0; i < str.GetLen(); i++) {
          if (!isdigit(cha[i])) {
              isDigit = false;
              break;
          }
      }
      return isDigit;
  }
  bool IOManager::FileIsEmpty(string fileName) {
      ifstream fin(fileName);

      if (!fin.is_open()) { throw std::runtime_error("Ошибка открытия файла\n"); }
      int symCount = 0;
      char c;

      while (!fin.eof()) {
          fin >> c;
          ++symCount;
      }

      fin.close();
      return (symCount == 1 || symCount == 0) ? true : false;
  }
  int IOManager::GetRecordsCount(string  fileName) {
      ifstream fin(fileName);

	if (!fin.is_open()) { throw std::runtime_error("Ошибка открытия файла\n"); }
      string str;
      int recordsCount = 0;
      while (getline(fin, str)) {
          ++recordsCount;
      }

      fin.close();
      return recordsCount;
  }
 
vector<string> IOManager::SplitString(string str, string delimiter) {
      std::vector<std::string> splittedString;
      int startIndex = 0;
      int  endIndex = 0;
      while ((endIndex = str.find(delimiter, startIndex)) < str.size()){
          std::string val = str.substr(startIndex, endIndex - startIndex);
          splittedString.push_back(val);
          startIndex = endIndex + delimiter.size();
      }
      if (startIndex < str.size()){
          std::string val = str.substr(startIndex);
          splittedString.push_back(val);
      }
      return splittedString;
  }
  
void IOManager::CreateRecords(int recordsCount, string fileName, const char* delimiter) {
      ofstream fout(fileName, std::ios::out | std::ios::app);
      if (!fout.is_open()) {
          cout << "Ошибка открытия файла\n";
          exit(1);
      }
      cout << "Количество записей для ввода " << recordsCount << "\n";

      TicketCashierInfo ticketCashierInfo;
      TicketCashier* ticketCashier = new TicketCashier[recordsCount]();
      for (int i = 0; i < recordsCount; i++) {
          cout << "\nВведите запись " << i + 1 << "\n";
          cout << "Введите номер кассы\n";
          cin >> ticketCashierInfo.officeNumber;
          cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
          cout << "Введите Ф.И.О кассира\n";
          getline(cin, ticketCashierInfo.fio, '\n');
          cout << "Введите количество проданных билетов\n";
          cin >> ticketCashierInfo.soldTicketsCout;
          cin.get();
          cout << "Введите суммарную выручку\n";
          cin >> ticketCashierInfo.revenue;
          cout << "Введите дату\n";
          cin >> ticketCashierInfo.date;
        
          ticketCashier[i].SetOfficeNumber(ticketCashierInfo.officeNumber);
          ticketCashier[i].SetFio(ticketCashierInfo.fio);
          ticketCashier[i].SetSoldTicketsCount(ticketCashierInfo.soldTicketsCout);
          ticketCashier[i].SetRevenue(ticketCashierInfo.revenue);
          ticketCashier[i].SetDate(ticketCashierInfo.date);
      }

      for (int i = 0; i < recordsCount; i++) {
          fout << ticketCashier[i].GetOfficeNumber() << delimiter;
          fout << ticketCashier[i].GetFio() << delimiter;
          fout << ticketCashier[i].GetSoldTicketsCount() << delimiter;
          fout << ticketCashier[i].GetRevenue() << delimiter;
          fout << ticketCashier[i].GetDate() << '\n';
      }

      fout.flush();
      fout.close();
  }
  
void IOManager::PrintRecords(int  recordsCount, string fileName, const char* delimiter) {
      ifstream fin(fileName);

      if (!fin.is_open()) {
          cout << "Ошибка открытия файла\n";
          exit(1);
      }

      if (FileIsEmpty(fileName)) { // Проверка файла на пустоту
          cout << "Файл " << fileName << " пуст\n";
          exit(1);
      }

      int recordsCountInFile = GetRecordsCount(fileName); // Количество записей в файле
      int recordsCountToPrint = recordsCount; // Количество записей для отображения пользователю

       // Если пользватель запросил больше чем надо записей или не больше нуля
      if ((recordsCountToPrint > recordsCountInFile) || recordsCountToPrint <= 0) {
          recordsCountToPrint = recordsCountInFile;
      }

      int currentRecordsCount = 0; // Счетчик для записей
      vector<string> vectorStr;
      string str;

      while (currentRecordsCount != recordsCountToPrint) {
          getline(fin, str);
         vectorStr = SplitString(str, delimiter);

          for (string str : vectorStr) { cout << str << " "; }

          cout << "\n";
          ++currentRecordsCount;
      }

	fin.close();
  }
