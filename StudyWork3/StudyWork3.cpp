/* StudyWork3.cpp – Листинг программы для 3-ей лабораторной работы
* Вариант 7
* Задание 1
*******************************************************************
* Имя файла : StudyWork3.cpp
* Резюме : Пример программы написанной на языке программирования С
* Описание : Программа формирует двумерный статический массив значений вещественного типа, 
соответствующий таблице значений функции на заданном
интервале [a,b] с заданным шагом дискретизации ∆x. 
По сформированным данным вычисляет наибольше и наименьшее значение функции y=f(x) на
заданном интервале.
Выводит на экран и в файл содержимое массива в следующем виде:
i : X[i] : Y[i] : &X[i] : &Y[i]
* Дата создания : 2021 / 10 / 25
* Автор : Vectorflex
* Платформа : OS Linux Mint
******************************************************************/

/* Подключение необходимых заголовочных файлов */
#include <iostream>
#include <math.h>
#include <iomanip>
#include <string>
#include <fstream>
#include <cfloat>

using std::cout;
using std::string;
using std::ofstream;

/* Начальные значения */
float initX = 1.0f;
float endX = 2.0f;
float step = 0.1f;

/* Псевдомаксимальное и псевдоминимальное значение */
double min = DBL_MAX;
double max = -DBL_MIN;

const int PAIRS_COUNT = 11; // Количество пар аргумент-значение
const int ELEMENTS_IN_PAIR_COUNT = 4; // Количество элементов в паре

double pairs[PAIRS_COUNT][ELEMENTS_IN_PAIR_COUNT]; // Двумерный массив пар

int main(){
    /* Настройка отображения вывода на консоль */
    setlocale(LC_ALL, "");
    std::cout.precision(1);
    std::cout.setf(std::ios::fixed, std::ios::floatfield);
    
    /* Приветствие */
    string greeting = "***********************************************************\n\
* Нижегородский государственный технический университет *\n\
* Лабораторная работа №3. Задание 1. Вариант 7. *\n\
* Выполнил студент группы 21 - ИВТз Морозов Олег *\n\
* **********************************************************\n";
    cout << greeting;

    ofstream outf("SomeFile.txt"); // Создание файлового потока для записи
    // Если мы не можем открыть этот файл для записи данных,
    if (!outf) {// Выход из программы
        cout << "Ошибка открытия файла";
        exit(1);
    }

    cout << "Значения функции\n";
    cout << "     X\t" << "  Y\t" << " &X\t" << "   &Y\n";

    float currentX = initX; // Текущее значение аргумента функции

    //Вычисление, отображение и запись в файл значений функции
    for (int i = 0; i < PAIRS_COUNT; i++) {
        cout << i + 1 << " : ";
        outf << i + 1 << " : ";

        for (int j = 0; j < 4; j++) {
            switch (j) {
            case 0: pairs[i][j] = currentX; 
            cout << pairs[i][j] << " : "; 
            outf << pairs[i][j] << " : ";
            break;
            case 1:  pairs[i][j] = pow((currentX + 1) / currentX, 3);
                cout << pairs[i][j] << " : ";
                outf << pairs[i][j] << " : ";
                if (pairs[i][j] < min) { // min
                    min = pairs[i][j];
                }
                if (pairs[i][j] > max) { // max
                    max = pairs[i][j];
                }
                break;
            case 2:  cout << &pairs[i][j] << " : "; 
                outf << &pairs[i][j] << " : ";
                break;
            case 3: cout << &pairs[i][j]; 
                    outf << &pairs[i][j];
                break;
            }
        }

        currentX += step;
        cout << "\n";
        outf << "\n";
    }

    cout << "Наименьшее значение функции на интервале [" << initX << ", " << endX << "]: " << min << "\n";
    cout << "Наибольшее значение функции на интервале [" << initX << ", " << endX << "]: " << max << "\n";

    outf.flush(); // Очистка файлового потока
    outf.close(); // Закрытие файлового потока

    return 0;
}
