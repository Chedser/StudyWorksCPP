/*
* StudyWork8.cpp - Листинг программы для 8-й лабораторной работы
* Вариант 7
****************************************************************
* Имя файла : StudyWork8.cpp
* Резюме : Пример программы, написанной на языке программирования C++
* Описание : Разрабатываемая программа предназначена для хранения массива переменных структурного типа данных
* Дата создания :
* Автор : Morozov Oleg
* Платформа : OS Linux Debian
*/

#include "IOManager_h.h"

using namespace Morozov;

int main(int argc, char** argv){

setlocale(LC_ALL, "");

string greetings = "**********************************************************\n\
* Нижегородский Государственный Технический Университет *\n\
* Лабораторная работа №8. Вариант 7\n\
* Выполнил студент группы 21 - ИВТз Морозов Олег\n\
* ****************************************************************\n";

cout << greetings;

if(argc < 2){

	cout << "Запуск без аргументов\n";
	cout << IOManager::GetManual();
	exit(1); 

}

if(strcmp(argv[1],"-h") == 0 || strcmp(argv[1],"-help") == 0){

	cout << IOManager::GetManual();
	exit(0);

}



if(argc == 4){

	string recordsCountStr = argv[2];

		if(!IOManager::IsDigit(recordsCountStr)){
			
			cout << "Неизвестная команда\n";
			cout << IOManager::GetManual();			
			exit(1);
		}

	int recordsCount = stoi(recordsCountStr);

	string commandType = argv[1];
	string fileName = argv[3];


		if(commandType == "-c"){
		
		IOManager::CreateRecords(fileName, recordsCount);
		exit(0);
		}

		if(commandType == "-r"){

		IOManager::PrintRecords(fileName, recordsCount);
		exit(0);
		}
	
	cout << "Неизвестная комманда\n";
	cout << IOManager::GetManual();
	exit(1);


}

cout << "Неизвестная комманда\n";
cout << IOManager::GetManual();
exit(1);


/****************************************************************************/

/*

// ЧТЕНИЕ
/* ifstream fin("someFile", std::ios::in | std::ios::binary);

if(!fin){

	cout << "Ошибка открытия файла\n";
	exit(1);

}

fin.read((char*)ticketCashier, sizeof(TicketCashier));

cout << "Номер кассы\n";
cout << ticketCashier->officeNumber << '\n';
cout << "Ф.И.О кассира\n";
cout << ticketCashier->fio << '\n';
cout << "Количество проданных билетов\n";
cout << ticketCashier->soldTicketsCount << '\n';
cout << "Cуммарная выручка\n";
cout << ticketCashier->revenue << '\n';
cout << "Дата\n";
cout << ticketCashier->date << '\n';

fin.close();*/ 

return 0;

}
