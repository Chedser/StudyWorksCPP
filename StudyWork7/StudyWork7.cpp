/*
StudyWork7.cpp - Листинг программы для 7-ой лабораторной работы
* Вариант 7
***************************************************************
* Имя файла : StudyWork7.cpp
* Резюме : Пример программы написанной на языке программирования С++
* Описание : Программа предназначена для хранения массива структурного типа данных (записей)
* Дата создания : 2022 / 01 / 29
* Автор : Vectorflex
* Платформа : OS Linux Mint
****************************************************************
*/

#include "sw7_h.h"

struct CmdArgs{
	string commandType = "";
	string recordsCountStr = "";
	string fileName = "";

}cmdArgs;

int main(int argc, char** argv){
setlocale(LC_ALL, "");

string greetings = "*********************************************\n\
* Нижегородский государственный  технический университет *\n\
* Лабораторная работа №7. Вариант 7. *\n\
* ****************************************************************\n";

cout << greetings;

  try{
    if(argc < 2 ){
        cout << "Запуск без аргументов\n";
        cout << GetManual();
        exit(1);
    }

    CmdArgs* cmd = &cmdArgs;
    cmd->commandType = argv[1]; // Тип команды

    if(cmd->commandType == "-h" || cmd->commandType == "-help"){
        cout << GetManual();
        exit(0);
    }

  cmd->recordsCountStr = argv[2]; // Количество записей
  cmd->fileName = argv[3]; // Название файла

    //Пользователь ввел 4 аргумента
    if((cmd->recordsCountStr.size() > 0 && cmd->fileName.size() > 0) && IsDigit(cmd->recordsCountStr)) {
    int recordsCount = stoi(cmd->recordsCountStr); // Количество записей в число
        if(cmd->commandType == "-c"){ // Команда создания записей
            CreateRecords(recordsCount, cmd->fileName);
            exit(0);
        }

        if(cmd->commandType == "-r"){
           PrintRecords(recordsCount, cmd->fileName);
    	   exit(0);
        }
    }
    
    cout << "Неизвестная команда\n";
    cout << GetManual();
    } catch(const std::logic_error &str){
    	cout << "Неизвестная команда\n";
    	cout << GetManual();
    }

    return 0;
}
