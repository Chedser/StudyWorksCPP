/* StudyWork10.cpp - Листинг программы для 10-ой лабораторной работ
* Вариант 7
*****************************************************************
* Имя файла : StudyWork10.cpp
* Резюме : Пример программы, написанной на языке программирования C++
* Описание : Разрабатываемая программа предназначена для хранения массива переменных структурного типа данных(записей)
* Дата создания : 2022/02/04
* Автор : Morozov Oleg
* Платформа : OS Linux Mint
*/

#include <iostream>
#include <exception>
#include "CircuitElement_h.h"
#include "IOManager_h.h"

typedef IOManager IOM;

int main(int argc, char** argv){
	setlocale(LC_ALL, "");

	string greetings = "*********************************************\n\
* Нижегородский государственный  технический университет *\n\
* Лабораторная работа №10. Вариант 7. *\n\
* Выполнил студент группы 21 - ИВТз Морозов Олег *\n\
* ****************************************************************\n";

	cout << greetings; 
       
    try {

        if (argc < 2) {

            cout << "Запуск без аргументов\n";

            cout << IOM::GetManual();

            exit(1);

        }

        if (argc == 3) {
        
            cout << "Неверное количество аргументов\n";

            cout << IOM::GetManual();

            exit(1);

        }

        string commandType = argv[1]; // Тип команды

       if (commandType == "-h" || commandType == "-help") {
         
            cout << IOM::GetManual();
            exit(0);

        }

       if (argc == 4 || argc == 5) {
       
           string recordsCountStr = argv[2]; // Количество записей
           string fileName = argv[3]; // Название файла
           int recordsCount = stoi(recordsCountStr); // Количество записей в число
           
           if (commandType == "-c" && argc == 5) { // Команда создания записей

               string circuitElementTypeStr = argv[4];

                   if (!IOM::IsDigit(circuitElementTypeStr)) {
               
                       cout << "Неизвестная команда\n";

                       cout << IOM::GetManual();
                       exit(1);

                   }

               int circuitElementType = stoi(circuitElementTypeStr); // Количество записей в число

               IOM::CreateRecords(recordsCount, fileName, ";", circuitElementType);
               exit(0);
           }

           if (commandType == "-r" && argc == 4) { // Команда создания записей

               IOM::PrintRecords(recordsCount, fileName, ";");
               exit(0);
           }

       }

        cout << "Неизвестная команда\n";

        cout << IOM::GetManual(); 

    }
    catch (const std::logic_error& str) {

        cout << "Неизвестная команда\n";

        cout << IOM::GetManual();

    }
   
	return 0;
}
