
/* StudyWork2_2.cpp – Листинг программы для 2-ой лабораторной работы
* Вариант 7
* Задание 2
*******************************************************************
* Имя файла : StudyWork2_2.cpp
* Резюме : Пример программы написанной на языке программирования С
* Описание :  Программа отображает таблицу значений функции на интервале [a, b] c шагом h.
Находит минимальное и максимальное значение, принимаемое функцией на заданном интервале.
Вычисляет среднее арифметическое таблицы значений
* Дата создания : 2021 / 10 / 23
* Автор : Vectorflex
* Платформа : OS Linux Mint
******************************************************************/

/* Подключение необходимых бибилотек */
#include <iostream>
#include <list>
#include <locale.h>
#include <vector>
#include <cmath>

using std::cout;
using std::vector;

/* Начальные значения */
float initX = 0.05f;
float endX = 1.55f;
float step = 0.05f;

/* Прототипы функций */
vector<float> GetRange(float,float,float); // Прототип функции получения промежутка аргументов
vector<double> GetValues(vector<float>); // Прототип функции получения значений функции f(x)
template<typename T, typename C> void ShowValues(vector<T>,vector<C>); // Прототип функции отображения значений

template<typename T> T min(vector<T>); // Прототип функции нахождения минимального значения
template<typename T> T max(vector<T>); // Прототип функции нахождения максимального значения
template<typename T> T mean(vector<T>); // Прототип функции нахождения среднего арифметического 

int main(){
    setlocale(LC_ALL, ""); // Настройка отображения кириллицы

    /* Приветствие */
    const  char* greeting = "***********************************************************\n\
* Нижегородский государственный технический университет *\n\
* Лабораторная работа №2. Задание 2. Вариант 7. *\n\
* **********************************************************\n";
    printf("%s",greeting);

    vector<float> listX = GetRange(initX, endX,step); // Получаем значения промежутка из диапазона
    vector<double> listY = GetValues(listX); // Получаем значения функции

    cout << "Значения функции на интервале " << "[" << initX << "," << endX << "]\n";

    ShowValues(listX, listY); // Отображаем пару аргумент-значение

    cout << "Минимальное значение функции на интервале " << "[" << initX << "," << endX << "]: ";
    printf("%.2f\n", min(listY));
    cout << "Мaксимальное значение функции на интервале " << "[" << initX << "," << endX << "]: ";
    printf("%.2f\n", max(listY));
    cout << "Среднее арифметическое значений функции на интервале " << "[" << initX << "," << endX << "]: ";
    printf("%.2f\n", mean(listY));

    return 0;
}

/* Определения функций */
vector<float> GetRange(float initX, float endX, float step) {
    vector<float> rangeList = {};

    for (float i = initX; i <= endX; i += step) {
       rangeList.push_back(i);
    }
    return rangeList;
}

vector<double> GetValues(vector<float> l) {
    vector<double> listValues;
    double currentValue = 0.0f;

    for (float i : l) {
        currentValue = 3 * pow(i, 5) - 3/i - sqrt(pow(i, 3)) + 10/(pow(i, 5));
        listValues.push_back(currentValue);
    }
    return listValues;
}

template<typename T, typename C>  void ShowValues(vector<T> x, vector<C> y) {
    for (int i = 0; i < x.size(); i++) {
        printf("%d : %.2f : %.2f\n", i + 1, x[i], y[i]);
    }
}

template<typename T>  T min(vector<T> l) {
    T min = l.front();
    
    for (T i: l) {
        if (i < min) {
            min = i;
        }
    }
    return min;
}

template<typename T> T max(vector<T> l) {
    T max = l.front(); 

    for (T i : l) {
        if (i > max) {
            max = i;
        }
    }
    return max;
}

template<typename T> T sum(vector<T> l) {
    if (l.size() == 0) { return 0; }

    T sum = 0;
    for (T i : l) {
        sum += i;
    }
    return sum;
}

template<typename T> T mean(vector<T> l) {
    if (l.size() == 0) { return 0; }
    return sum(l) / l.size();
}
