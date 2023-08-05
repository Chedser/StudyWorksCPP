#ifndef IOMANAGER_H
#define IOMANAGER_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <limits>

#include "TicketCashier_h.h"

using std::cout;
using std::cin;
using std::string;
using std::ofstream;
using std::ifstream;

namespace Vectorflex{
class FileInfo{
	public:
	 int totalRecordsCount = 0;
};

class IOManager{
public:
	static string GetManual();
	static bool IsDigit(string);
	static void InitFile(string);
	static bool FileExists(string fileName);
	static void CreateRecords(string,int);
	static void PrintRecords(string, int);
	static bool FileIsEmpty(string);
	static unsigned int GetRecordsCount(string);
};
}
#endif
