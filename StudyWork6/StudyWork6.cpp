﻿
/* StudyWork6.cpp – Листинг программы для 6-ой лабораторной работы
* Вариант 7
*******************************************************************
* Имя файла : studywork6.cpp
* Резюме : Пример программы написанной на языке программирования С++
* Описание :  Программа, читающая информацию со стандартного потока
ввода и записывающая ее в файл. Имя файла программа принимает в
качестве аргумента командной строки. Чтение со стандартного потока
продолжается до тех пор, пока пользователь не нажмет 'Ctrl+Z' (EOF)
* Дата создания : 2022 / 01 / 28
* Автор : Vectorflex
* Платформа : OS Linux Mint
******************************************************************/

#include <iostream>
#include <fstream>

int main(int argc, char** argv){
    setlocale(LC_ALL, "");

    if (argc < 2) { //Выход из программы, если не ввели название файла
        printf("Отсутствует название файла\n");
        exit(1);
    }

    /* Приветствие */
    const  char* greeting = "***********************************************************\n\
* Нижегородский государственный технический университет *\n\
* Лабораторная работа №6.Вариант 7. *\n\
* **********************************************************\n";
    printf("%s",greeting);

    char ch;
    FILE* fp;
    char* fileName = argv[1];

    if ((fp = fopen(fileName, "w+")) == NULL){
        printf("Ошибка открытия файла \n");
        exit(1);
    }

    printf("Файл %s создан.\nВведите текст для записи и нажмите сочетание клавиш окончания ввода\n", fileName);

    for (;;){
        if ((ch = getchar()) == EOF) break;
        fputc(ch, fp);
     }
    
    fclose(fp);
    printf("\nТекст записан в файл\n");

    return 0;
}


