﻿
/* StudyWork1.cpp – Листинг программы для 1-ой лабораторной работы
* Вариант 7
*******************************************************************
* Имя файла : StudyWork1.cpp
* Резюме : Пример программы написанной на языке программирования С++
* Описание :  Программа получает значения A и X от пользователя.
Решает уравнения Y(A,X) и Z(A,X). Отображает резельтат пользователю  
* Дата создания : 2021 / 09 / 19
* Автор : Vectorflex
* Платформа : OS Linux Mint
******************************************************************/

/* Включаемые в программу заголовочные файлы */
#include <stdio.h>
#include <locale.h>
#include <cmath>

/* Определение констант верного ввода */
#define RIGHT_A 2.48f
#define RIGHT_X 0.21f

void SetResultOfExpressions(double, double, double*); // Прототип функции решения выражений Y(A, X) и Z(A, X)

/* Переменные ввода пользователя */
float userA = 0.0f;
float userX = 0.0f;
double resultValues[] = {0.0, 0.0};

/* Начало главной функции */
int main() {

	setlocale(LC_ALL, ""); // Вызов функции для отображения русских символов

	/* Приветствие */
	const  char* greeting = "***********************************************************\n\
* Нижегородский государственный технический университет *\n\
* Лабораторная работа №1. Задание 1. Вариант 7. *\n\
* Выполнил студент группы 21 - ИВТз Морозов Олег *\n\
* **********************************************************\n";
	printf("%s",greeting);

	/* Пользователь вводит переменную А */
	printf("Введите A = 2.48 и нажмите Enter\n");
	int inputHandler = scanf("%f", &userA);

	if (userA != RIGHT_A) { // Если ввод неверен...
		printf("Ошибка ввода\n"); // ...отображается сообщение...
		return EXIT_FAILURE; // ..и программа завершает свою работу
	}

	/* Пользователь вводит переменную X */
	printf("Введите X = 0.21 и нажмите Enter\n");
	inputHandler = scanf("%f", &userX);
	
	if (inputHandler && userX == RIGHT_X) {// Если пользователь ввел число и число верное...

		SetResultOfExpressions(userA, userX, resultValues); //.. вызывается функция решения выражений
		printf("Y = %f: Z = %f \n", resultValues[0], resultValues[1]); // Отображение выражений пользователю

	}
	else { // В противном случае отображается сообщение об ошибке 

		printf("Ошибка ввода\n");

	}

	return EXIT_SUCCESS; // Выход из главной функции

} // Конец главной функции

/* Определение функции решения выражений  */
void SetResultOfExpressions(double a, double x, double* resultValues) {

/* Цель: Решение выражений Y(A,X) и Z(A, X) */
/* Исходные данные: 
 а – первая переменная 
 x – вторая переменная */
/* Результат: пара значений Y и Z, в виде указателя на массив */
/* Вызываемые модули: нет */
/* Описание алгоритма: 
Вычисляются пары значений в соответствии с формулой*/
/* Дата: 2021 / 09 / 19 Версия 1.01 */
/* Автор: Vectorflex */
/* Исправления: нет */
/*****************************************************************/

	double Y = cos(pow(x, 3) + pow(a, 3));
	double Z = atan(sqrt(2*x + a));
	resultValues[0] = Y;
        resultValues[1] = Z;

}
