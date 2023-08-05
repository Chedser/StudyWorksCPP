#ifndef IOMANAGER_C
#define IOMANAGER_C

#include "IOManager_h.h"

using namespace Vectorflex;

string IOManager::GetManual(){

string manual = "Поддерживаемые опции запуска:\n\
-help или -h - запуск программы в режиме получения справки\n\
-с [N] [file_name] - запуск программы в режиме создания электронной таблицы записей\n\
N - количество записей, file_name - имя текстового файла, \n\
в котором будет сохранен массив(таблица) записей.\n\
-r [N] [file_name] - запуск программы в режиме  чтения содержимого\n\
бинарного файла file_name\n";

return manual;
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

bool IOManager::FileExists(string fileName) {
    bool isExist = false;
    std::ifstream fin(fileName.c_str());

    if (fin.is_open())isExist = true;
    fin.close();
    return isExist;
}

bool IOManager::FileIsEmpty(string fileName){
	ifstream fin(fileName, std::ios::in | std::ios::binary | std::ios::ate);

	if(!fin.is_open()){
		cout << "Ошибка открытия файла\n";
		exit(1);
	}
	std::streampos size = fin.tellg();
	return (size == 0 || size == 1)?true:false;
}

void IOManager::InitFile(string fileName) { 
     ofstream fout(fileName, std::ios_base::out | std::ios::binary | std::ios::trunc);

    if (!fout.is_open()) { throw std::runtime_error("Ошибка открытия файла\n"); }
	unsigned long descriptor = 0;
	fout.write((char*)&descriptor, sizeof(unsigned long));

   	fout.flush();
   	fout.close();
}


void IOManager::CreateRecords(string fileName,int recordsCount){
if(!FileExists(fileName) || FileIsEmpty(fileName)){ // Файл не существует или пустой
	InitFile(fileName);
}

//ЗАПИСЬ ФАЙЛА
  ofstream fout(fileName, std::ios::out | std::ios::binary | std::ios::app);

if(!fout){
	cout << "Ошибка открытия файла\n";
	exit(1);
}

TicketCashier* ticketCashier = new TicketCashier();	
cout << "Записей для ввода " << recordsCount << "\n";

for(int i = 0; i < recordsCount; i++){
cout << "\nЗапись " << (i + 1) << "\n"; 

cout << "Введите номер кассы\n";
cin >> ticketCashier->officeNumber;
if(cin.bad()){
cout << "Неверный ввод\n";
--i;
continue;
}

cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
cout << "Введите Ф.И.О кассира\n";
cin.getline(ticketCashier->fio, 80, '\n');
cout << "Введите количество проданных билетов\n";
cin >> ticketCashier->soldTicketsCount;
if(cin.bad()){
cout << "Неверный ввод\n";
--i;
continue;
}
cout << "Введите суммарную выручку\n";
cin >> ticketCashier->revenue;
if(cin.bad()){

cout << "Неверный ввод\n";
--i;
continue;
}
cout << "Введите дату\n";
cin >> ticketCashier->date;
if(cin.bad()){
cout << "Неверный ввод\n";
--i;
continue;
}
fout.write((char*)ticketCashier, sizeof(TicketCashier));
}

unsigned int newRecordsCount = GetRecordsCount(fileName) + recordsCount;
fout.seekp(0, std::ios::beg);
fout.write((char*)&newRecordsCount, sizeof(int));
fout.flush();
fout.close();
}

unsigned int IOManager::GetRecordsCount(string fileName){
    if (!FileExists(fileName) || FileIsEmpty(fileName)) {
       return 0;
    }

unsigned int recordsCount = 0;
ifstream fin(fileName, std::ios::in | std::ios::binary);
    if (!fin.is_open()) {
        return 0;
    }

	int currentRecord = 0;
	TicketCashier*  ticketCashier = new TicketCashier();

	while(!fin.eof()){
	fin.read((char*)ticketCashier, sizeof(TicketCashier));
	++currentRecord;
	}

	fin.close();	
	return currentRecord;
}

void IOManager::PrintRecords(string fileName, int recordsCount){
     if (FileIsEmpty(fileName)) {
        cout << "Файл " << fileName << " пуст\n";
        exit(1);
    }

ifstream fin(fileName, std::ios::in | std::ios::binary);
    if (!fin.is_open()) {
        cout << "Ошибка открытия файла\n";
        exit(1);
    }

  unsigned  int recordsCountInFile = GetRecordsCount(fileName); // Количество записей в файле
   unsigned int recordsCountToPrint = recordsCount; // Количество записей для отображения пользователю

     // Если пользователь запросил больше чем надо записей или не больше нуля
    if ((recordsCountToPrint > recordsCountInFile) || recordsCountToPrint <= 0) {
        recordsCountToPrint = recordsCountInFile;
    }

	unsigned int rc = 0;
	fin.read((char*)&rc, sizeof(unsigned int));
	cout << "Записей всего " << recordsCountInFile << "\n";
	TicketCashier* ticketCashier = new TicketCashier();
	for(int i = 0; i < recordsCountToPrint; i++){
		cout << "\nЗапись " << (i + 1) << "\n";		
		fin.read((char*)ticketCashier, sizeof(TicketCashier));
		cout << "Номер кассы " << ticketCashier->officeNumber << "\n";
		cout << "Ф.И.О. кассира " << ticketCashier->fio << "\n";
		cout << "Количество проданных билетов " << ticketCashier->soldTicketsCount << "\n";
		cout << "Суммарная выручка " << ticketCashier->revenue << "\n";
		cout << "Дата " << ticketCashier->date << "\n";
	
	}
    
    fin.close();
}
#endif

