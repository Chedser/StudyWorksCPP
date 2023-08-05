#include <locale>
#include <fstream>
#include <iostream>
#include "Header.h" // Заголовочный файл функций для лабораторной работы

char wordLeft[80];
char wordRight[80];
char wordToInsert[80];

int wordLeftIndex;
int wordRightIndex;
int wordLeftSize;
int wordRightSize;
int wordToInsertSize;

int textSize;
int newTextSize;

int magicNumber = 4; // Какая-то цифра

const char* text = "Stroustrup is best known for his work on C++.\
In 1979, he began developing C++ (initially called C with Classes).\
In his own words, he invented C++, wrote its early definitions, and produced its first implementation choseand formulated the design criteria for C++,\
designed all its major facilities, and was responsible for the processing of extension proposals in the C++ standards committee.\
C++ was made generally available in 1985.";

char* textFromFile;

using std::ofstream;
using std::ifstream;

int main(){
	
	setlocale(LC_ALL, "");

	/* ПРЕДВАРИТЕЛЬНАЯ РАБОТА С ФАЙЛОМ */
	ofstream fout("file.txt", std::ios_base::trunc); // создаём объект класса ofstream для записи 

	if (!fout.is_open()) {
	
		printf("Ошибка открытия файла");
		exit(1);
	}

	fout << text; // запись строки в файл
	fout.flush();
	fout.close();

	textSize = strlen(text);
	textFromFile = (char*)malloc(sizeof(char) * textSize);
	ifstream fin("file.txt");

	if (!fin.is_open()) {
		printf("Ошибка открытия файла");
		exit(1);
	}

	fin.getline(textFromFile, textSize + 1);
	//Закрываем файл
	fin.close();

	printf("Текст из файла\n");
	printf("%s\n\n",textFromFile);
	
	/* ВВОД ПОЛЬЗОВАТЕЛЯ */
	printf("Введите первое слово\n");
	scanf("%s", wordLeft);
	
	wordLeftIndex = strIndex(text, wordLeft);
	CheckIndex(wordLeftIndex, wordLeft);
	printf("Введите второе слово\n");
	scanf("%s", wordRight);
	
	wordRightIndex = strIndex(text, wordRight);
	CheckIndex(wordRightIndex, wordRight);
	CheckWordOrder(wordLeftIndex, wordRightIndex);

	wordLeftSize = strlen(wordLeft);
	wordRightSize = strlen(wordRight);
	printf("Введите слово, которое нужно вставить\n");
	scanf("%s", wordToInsert);
	wordToInsertSize = strlen(wordToInsert);
	newTextSize = textSize + wordToInsertSize;
	
	/* ГЛАВНАЯ ЛОГИКА ПРОГРАММЫ */
char* newText = (char*)malloc(sizeof(char) * newTextSize);
int firstHalfSize = newTextSize;
char* firstHalf = (char*)malloc(sizeof(char) * firstHalfSize);

/* Получаем первую половину текста со вставленным словом */
for (int i = 0, j = 0; i < firstHalfSize; i++) {
	if (i < (wordLeftIndex + wordLeftSize + 1)) {
		firstHalf[i] = textFromFile[i];
	}else {
		firstHalf[i] = wordToInsert[j];
		++j;
	}
}

int secondHalfSize =  textSize - (wordLeftSize + wordLeftIndex + magicNumber);
char* secondHalf = (char*)malloc(sizeof(char) * secondHalfSize);

/* Получаем вторую половину текста */
for (int i = wordLeftIndex + wordLeftSize, j = 0; i < textSize; i++, j++) {
	secondHalf[j] = textFromFile[i];
}

strncat(firstHalf, secondHalf, secondHalfSize + magicNumber); /* Объединяем строки */
fout.open("file.txt", std::ios_base::trunc); 

if (!fout.is_open()) {
	printf("Ошибка открытия файла");
	exit(1);
}

fout << firstHalf; // запись строки в файл
fout.flush();
fout.close();

newTextSize = strlen(firstHalf);
textFromFile = (char*)malloc(sizeof(char) * newTextSize);
fin.open("file.txt");

if (!fin.is_open()) {
	printf("Ошибка открытия файла");
	exit(1);
}

fin.getline(textFromFile, newTextSize + 1);
//Закрываем файл
fin.close();

printf("Новый текст\n");
printf("%s\n", textFromFile);
	return 0;
}

