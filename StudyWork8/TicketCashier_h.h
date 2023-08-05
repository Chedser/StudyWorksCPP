#ifndef TICKETCAHIER_H
#define TICKETCASHIER_H

namespace Vectorflex{
	class TicketCashier{
	public:
		unsigned int officeNumber; // Номер кассы
		char fio[80]; // Ф.И.О. кассира
		unsigned int soldTicketsCount; //Количество проданных билетов
		float revenue; // Cуммарная выручка
		char date[10]; // Дата

	TicketCashier(){}
	~TicketCashier(){}
	};
}
#endif
