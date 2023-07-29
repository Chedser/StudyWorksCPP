#ifndef STUDY_WORK5
#define STUDY_WORK5

/* Подключение необходимых библиотек */
#include <iostream>
#include <string>

using std::string;

/* Массив строк для записи в файл */
string STR_TO_FILE[] = { "Stroustrup is best known for his work on C++.", "In 1979, he began developing C++ (initially called C with Classes). In his own words, he invented C++, wrote its early definitions,and produced its first implementation chose and formulated the design criteria for C++, designed all its major facilities,and was responsible for the processing of extension proposals in the C++ standards committee.",
"C++ was made generally available in 1985."};

/* Поиск слов в строке*/ 
bool IsFound(string word1, string word2, string str) {
	if (str.find(word1) == -1 || str.find(word2) == -1) {
		return false;
	}
	return true;
}

/* Получить индексы начала и конца, вставленной строки */
int* GetIndexes(string word1, string word3, string str){
		int begin = str.find(word1);
		int end = begin + word3.size();
			
		int* indexes = new int[2];

		indexes = new int[2];
		indexes[0] = begin;
		indexes[1] = end;
	
return indexes;
}

/* Получение новой строки после вставки слова */
string InsertWord(string str, string word3, int index) {
		string newStr = str.insert(index, " " + word3 + " ");
		return newStr;
}
#endif

