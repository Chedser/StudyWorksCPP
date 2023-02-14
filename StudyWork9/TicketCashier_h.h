#ifndef TICKET_CASHIER_H
#define TICKET_CASHIER_H


#include "String_h.h"

/* СТРУКТУРА АТРИБУТОВ КЛАССА TicketCashier*/
struct TicketCashierInfo {

	int officeNumber = 0; // Номер кассы
	string fio; // ФИО кассира
	int soldTicketsCout = 0; // Количество проданных билетов
	float revenue; // Суммарная выручка
	string date; // Дата

};

class TicketCashier {

	TicketCashierInfo ticketCashierInfo;

public:
	// Конструкторы
	TicketCashier() {}
	TicketCashier(int, string, int, float, string);
	TicketCashier(int, const char*, int, float, const char*);
	
	// Сеттеры
	void SetOfficeNumber(int);
	void SetFio(string);
	void SetFio(const char*);
	void SetSoldTicketsCount(int);
	void SetRevenue(float);
	void SetDate(string);
	void SetDate(const char*);

	// Геттеры
	int GetOfficeNumber();
	string GetFio();
	int GetSoldTicketsCount();
	float GetRevenue();
	string GetDate();

	// Отладочное отображение информации
	void PrintInfo();

};

TicketCashier::TicketCashier(int officeNumber, string fio, int soldTicketsCount, float revenue, string date) {

	SetOfficeNumber(officeNumber);
	SetFio(fio);
	SetSoldTicketsCount(soldTicketsCount);
	SetRevenue(revenue);
	SetDate(date);
	

}
TicketCashier::TicketCashier(int officeNumber, const char* fio, int soldTicketsCount, float revenue, const char* date) {

	SetOfficeNumber(officeNumber);
	SetFio(fio);
	SetSoldTicketsCount(soldTicketsCount);
	SetRevenue(revenue);
	SetDate(date);

}


void TicketCashier::SetOfficeNumber(int officeNumber) {ticketCashierInfo.officeNumber = officeNumber;}
void TicketCashier::SetFio(string fio) {ticketCashierInfo.fio = fio;}
void TicketCashier::SetFio(const char* fio) {ticketCashierInfo.fio = fio; }
void TicketCashier::SetSoldTicketsCount(int soldTicketsCout) { ticketCashierInfo.soldTicketsCout = soldTicketsCout; }
void TicketCashier::SetRevenue(float revenue) { ticketCashierInfo.revenue = revenue; }
void TicketCashier::SetDate(string date) { const char* dateNew = date.c_str(); ticketCashierInfo.date = dateNew; }
void TicketCashier::SetDate(const char* date) {ticketCashierInfo.date = date; }

int TicketCashier::GetOfficeNumber() {return ticketCashierInfo.officeNumber;}
string TicketCashier::GetFio() { return ticketCashierInfo.fio; }
int TicketCashier::GetSoldTicketsCount() { return ticketCashierInfo.soldTicketsCout; }
float TicketCashier::GetRevenue() { return ticketCashierInfo.revenue; }
string TicketCashier::GetDate() { return ticketCashierInfo.date; }

void TicketCashier::PrintInfo() {

	cout << "Номер кассы " << ticketCashierInfo.officeNumber << "\nФИО " << ticketCashierInfo.fio <<
		"\nКоличество проданных билетов " << ticketCashierInfo.soldTicketsCout <<
         "\nСуммарная выручка " << ticketCashierInfo.revenue << 
		"\nДата " << ticketCashierInfo.date << '\n';

}
#endif
