
/* StudyWork9.cpp - Листинг программы для 9-й лабораторной работы****************
* Имя файла : StudyWork9.cpp
* Резюме : Пример программы, написанной на языке программирования C++
* Описание : Разрабатываемая программа предназначена для хранения массива переменных структурного типа данных(записей)
* Дата создания : 2022/02/03
* Автор : Morozov Oleg
* Платформа : OS Linux Mint
*/

#include "TicketCashier_h.h"
#include "IOManager_h.h"

typedef IOManager IOM;

int main(int argc, char** argv){
 
    setlocale(LC_ALL, "");

	string greetings = "*********************************************\n\
* Нижегородский государственный  технический университет *\n\
* Лабораторная работа №9. Вариант 7. *\n\
* Выполнил студент группы 21 - ИВТз Морозов Олег *\n\
* ****************************************************************\n";

	cout << greetings;
	
    try {

        if (argc < 2) {

            cout << "Запуск без аргументов\n";

            cout << IOM::GetManual();

            exit(1);

        }

        string commandType = argv[1]; // Тип команды

        if (commandType == "-h" || commandType == "-help") {

            cout << IOM::GetManual();
            exit(0);

        }

        string recordsCountStr = argv[2]; // Количество записей
        string fileName = argv[3]; // Название файла

        //Пользователь ввел 4 аргумента
        if ((recordsCountStr.size() > 0 && fileName.size() > 0) && IOM::IsDigit(recordsCountStr)) {

            int recordsCount = stoi(recordsCountStr); // Количество записей в число

            if (commandType == "-c") { // Команда создания записей

                IOM::CreateRecords(recordsCount, fileName, ";");
                exit(0);
            }

            if (commandType == "-r") { // Команда чтения записей

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

