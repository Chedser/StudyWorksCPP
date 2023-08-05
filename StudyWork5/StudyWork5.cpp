
/* StudyWork5.cpp – Листинг программы для 5-ой лабораторной работы
* Вариант 7
* Задание 1
*******************************************************************
* Имя файла : StudyWork5.cpp
* Резюме : Пример программы написанной на языке программирования С
* Описание :  Вставить слово в текст между двух заданных. 
Выводит обработанный текст и номера позиций начала и конца вставленного слова в новом
тексте.
Записывает в файл новый текст
* Дата создания : 2021 / 10 / 29
* Автор : Vectorflex
* Платформа : OS Linux Mint
******************************************************************/

/* Подключение необходимых библиотек */
#include <iostream>
#include <fstream>
#include <string.h>
#include <locale>
#include "study_work5.h" // Заголовочный файл функций для лабораторной работы

using std::ofstream;
using std::ifstream;
using std::cout;
using std::cin;
using namespace std;
int main(){
   	setlocale(LC_ALL, "");

	ofstream fout("test.txt"); // Создание потока для записи файл
	/* Проверка на ошибку открытия файла */
	if (!fout.is_open()) {
		cout << "Ошибка открытия файла\n";
		exit(1);
	} 

	cout << "Текст из файла\n";

	/* Запись в файл и отображение текста из файла*/
	for (string str : STR_TO_FILE) {
			fout << str << "\n";
			cout << str << "\n";
	}

	fout.flush(); // Очищаем файловый поток
	fout.close(); // Закрытие файлового потока

	/* Слова, между которыми нужно вставить текст */
	string word1; 
	string word2;
		
	string wordToInsert; // Слово для вставки

	cout << "Введите первое слово: \n";
	cin >> word1;
	cout << "Введите второе слово: \n";
	cin >> word2;
	cout << "Введите слово, которое нужно вставить: \n";
	cin >> wordToInsert;

	/* Проверка пользовательского ввода */
	if (cin.bad()) {
		cout << "Ошибка ввода\n";
		exit(1);
	}

	ifstream fin("test.txt"); // Создание потока для чтения из файла
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла\n";
		exit(1);
	}

	string textFromFile;
	string line = "";
	/* Чтение из файла */
	while (getline(fin, textFromFile)){
		  line += textFromFile;
	}

	textFromFile = line;
	fin.close(); // Закрытие файлового потока

	/* Проверка на присутствие слов в тексте */
	if (!IsFound(word1, word2, textFromFile)) {
		cout << "Слова не обнаружены\n";
		exit(1);
	} 

	int* indexes = new int[2];// Индексы начала и конца вставленного слова
	indexes = GetIndexes(word1,wordToInsert, textFromFile); // Получаем индексы
	string newText = InsertWord(textFromFile, wordToInsert, indexes[1]); // Новая строка после вставки
	
	cout << "\nНовый текст\n";
	cout << newText << "\n";
	cout << "Начальный индекс: " << indexes[0] + wordToInsert.size() << "\n";
	cout << "Конечный индекс: " << indexes[1] + wordToInsert.size() + 1 << "\n";

	fout.open("test.txt", ios_base::out);
	
	/* Проверка на ошибку открытия файла */
	if (!fout.is_open()) {
		cout << "Ошибка открытия файла\n";
		exit(1);
	}
		
	fout << newText; // Записываем новую строку в файл
	fout.flush(); // Очищаем файловый поток
	fout.close(); // Закрываем файловый поток

	return 0;
	}
