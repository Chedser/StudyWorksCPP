#ifndef COFFEEMACHINE_H
#define COFFEEMACHINE_H

#define INGREDIENTS_COUNT 3

#include <iostream>
#include <string>
#include <cstring>
#include <fstream>
#include <chrono>
#include <thread>
#include "IOManager_h.h"

using std::cout;
using std::cin;
using std::string;
using std::ofstream;
using std::ifstream;

// Пространства имен для работы со временем
using namespace std::this_thread;
using namespace std::chrono;

namespace Morozov {
    enum class State { // Состояние кофемашины
        SwitchingOn = 1, // Запуск
        Reading, // Ожидание ввода
        Processing, // Приготовление кофе
        Uploading, // Загрузка ингредиента в емкость
        SwitchingOff // Выключение
    };

    enum class Ingredients { // Ингредиенты
        Coffee,
        Milk,
        Water
    };

    enum class CoffeeType { // Тип кофе
        Espresso = 1,
        Lungo,
        Melange
    };

    class CoffeeMachine {
        State state = State::SwitchingOn; // Текущее состояние кофемашины

        /* Начальный обЪем емкостей в миллилитрах */
        const int initCofeeVolume = 1000; // Начальный объем емкости с кофе
        const int initMilkVolume = 2000; // Начальный объем емкости с молоком
        const int initWaterVolume = 3000; // Начальный объем емкости с водой
        
        int currentReceiptNumber = 0;
        int currentCofeeVolume = 0; // Текущий объем емкости с кофе
        int currentMilkVolume = 0; // Текущий объем емкости с  молоком
        int currentWaterVolume = 0; // Текущий объем емкости с баком

        int enoughFlagsVolume[INGREDIENTS_COUNT] = { 1, 1, 1 }; // 1 - ингредиент есть, 0 - нет; 0 - кофе, 1 - молоко, 2 - вода
        int timer = 1;
        string fileName = "cm.txt"; // Файл для хранения ингредиентов

    public:
        CoffeeMachine();
        ~CoffeeMachine();

        // ПРОВЕРКА НА ДОСТАТОЧНОСТЬ ИНГРЕДИЕНТОВ
        bool IsCofeeEnough(int);
        bool IsMilkEnough(int);
        bool IsWaterEnough(int);

        // УМЕНЬШЕНИЕ ИНГРЕДИЕНТОВ В ЕМКОСТЯХ
        void TakeCoffeeDemage(int);
        void TakeMilkDemage(int);
        void TakeWaterDemage(int);

        void UpdateIngredientsVolume();

        State GetState();
        void SetState(State);
        void SetReceiptNumber(int);
        void SwitchTimer();

        bool CheckReceiptNumber(int);
        string GetReceiptType(int);

        
        int GetCurrentReceiptNumber(); // Получить текущий номер рецепта, который ввел пользователь

        void InitTimer();

        int GetTimer();

        bool IsEnoughIngredients(); // Проверяем достаточно ли ингредиентов
 
        void Processing(); // Готовка кофе

        void NotEnoughIngredientsMessage(); // Сообщение о том, что ингредиентов недостаточно

        // Файловые операции
        void InitFile(string);
        void ReadFile(string);
        void WriteFile(string);

        void AskDrinkYet();

        void PrintIngredietnsInfo();

    };
} // namespace Morozov
#endif
