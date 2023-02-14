/* StudyWork4.cpp – Листинг программы для 4-ой лабораторной работы
* Вариант 7
* Задание 1
*******************************************************************
* Имя файла : StudyWork4.cpp
* Резюме : Пример программы написанной на языке программирования С
* Описание :  Программа вычисляет и печатает таблицу значений функции f(x) и определяет, 
является ли она монотонной на интервале [a, b] при дискретном увеличении аргумента от x=a с шагом h.
* Дата создания : 2021 / 10 / 27
* Автор : Morozov Oleg
* Платформа :OS Linux Mint
******************************************************************/

/* Подключение необходимых заголовочных файлов */
#include <iostream>
#include <locale>
#include "study_work4.h" // Заголовочный файл пространства имен Morozov

using namespace Morozov;

int rangeCount = 0; // Количество аргументов диапазона текущей функции
const double STEP = 0.1; // Шаг приращения

/* Массивы аргументов для соответствующих функций */
double* arctRange;
double* cosRange;
double* minRange;

/* Массив значений текущей функции */
double* values;

int main(){

	setlocale(LC_ALL, "");

	/* Приветствие */
	string greeting = "***********************************************************\n\
* Нижегородский государственный технический университет *\n\
* Лабораторная работа №4. Задание 1. Вариант 7. *\n\
* Выполнил студент группы 21 - ИВТз Морозов Олег *\n\
* **********************************************************\n";
	cout << greeting;

	/* ПЕРВАЯ ФУНКЦИЯ */
	rangeCount = GetCountOfElementsInRange(-10, -0.1, STEP); // Определяем количество аргументов согласно диапазону
	arctRange = new double[rangeCount]; // Выделяем память под массив аргументов
	values = new double[rangeCount]; // Выделяем память под массив значений

	FillRange(arctRange,-10, -0.1, STEP); // Заполняем массив аргументов согласно диапазона
	SetValues(arctRange, rangeCount, values, First); // Вычисляем значения функции

	cout << "Значения первой функции \n";
	ShowValues(arctRange, values, rangeCount); // Отображаем пары аргумент-значение
	CheckRising(values, arctRange,  rangeCount); // Проверяем монотонность функции
	/* Далее аналогично... */

	/* ВТОРАЯ ФУНКЦИЯ */
	rangeCount = GetCountOfElementsInRange(0, 0.9, STEP);
	cosRange = new double[rangeCount]; 
	values = new double[rangeCount];

	FillRange(cosRange, 0, 0.9, STEP);
	SetValues(cosRange, rangeCount, values, Second);

	cout << "Значения второй функции \n";
	ShowValues(cosRange, values, rangeCount);
	CheckRising(values, cosRange, rangeCount);

	/* ТРЕТЬЯ ФУНКЦИЯ */
	 rangeCount = GetCountOfElementsInRange(1, 9.9, STEP); 
	 minRange = new double[rangeCount]; 
	 values = new double[rangeCount];

	 FillRange(minRange, 1, 9.9, STEP);

	SetValues(minRange, rangeCount, values);

	cout << "Значения третьей функции \n";
	ShowValues(minRange, values, rangeCount);
	CheckRising(values, minRange, rangeCount);

}

