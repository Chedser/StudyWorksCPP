/* StudyWork11.cpp - Листинг программы для 11-ой лабораторной работ
* Вариант 7
*****************************************************************
* Имя файла : StudyWork11.cpp
* Резюме : Пример программы, написанной на языке программирования C++
* Описание : Разрабатываемая программа моделирует процесс кофемашины
* Дата создания : 2022/02/05
* Автор : Vectorflex
* Платформа : OS Linux Mint
*/

#include "CoffeeMachine_h.h"

using namespace Vectorflex;

int main(int argc, char** argv){
    setlocale(LC_ALL, "");

    string greetings = "*********************************************\n\
* Нижегородский государственный  технический университет *\n\
* Лабораторная работа №11. Вариант 7. *\n\
* ****************************************************************\n";
    cout << greetings;

    if (argc < 2) {
        cout << "Запуск без аргументов\n";
        cout << IOManager::GetManual();
        exit(1);
    }

    if (strcmp(argv[1],"-h") == 0 || strcmp(argv[1], "-help") == 0) {
        cout << IOManager::GetManual();
        exit(0);
    }

    cout << "Программа моделирует работу кофемашины\n\
             Команды:\n\
             1 - Espresso\n\
             2 - Lungo\n\
             3 - Melange\n\
             0 - Выход";

    cout << "\n< ЗАПУСК >\n";
    CoffeeMachine* coffeeMachine = new CoffeeMachine(); // Объект кофемашины
    // Симуляция включения кофемашины
    coffeeMachine->SwitchTimer();
    coffeeMachine->InitTimer();
   
    coffeeMachine->SetState(State::Reading);
     int receiptNumber = 0;
    bool  inputFlag = false; // Проверка корректности ввода при первом запуске

    if (argc >= 2) {
        if (IOManager::IsDigit(argv[1])) {
             receiptNumber = std::stoi(argv[1]);
               if (receiptNumber >= 0 && receiptNumber <= 3) {
                    inputFlag = true;
                }
        }
    }

    // Пока машина не выключится
    while (coffeeMachine->GetState() != State::SwitchingOff) {
            // Состояние ожидания ввода пользователя
        if (coffeeMachine->GetState() == State::Reading) {
               if (inputFlag) {
                     inputFlag = false;
            }
            else {
                cout << "Введите номер рецепта\n";
                cin >> receiptNumber;

                if (cin.bad()) {
                    cout << "Здесь нет таких кнопок!!!\n";
                    continue;
                }
            }
           
            if (receiptNumber == 0) { // Пользователь хочет выйти
                coffeeMachine->SetState(State::SwitchingOff);

                cout << "< ВЫХОД >\n";
                continue;
            }

                // Проверяем адекватность введеного числа
                if (coffeeMachine->CheckReceiptNumber(receiptNumber)) {
                    coffeeMachine->SetReceiptNumber(receiptNumber);
                    coffeeMachine->SetState(State::Processing); // Переключаемся в состояние главного процесса
                    }
        }

        // Главное состояние готовки кофе
        if (coffeeMachine->GetState() == State::Processing) {
                 // Каких-то ингредиентов не хватает
            if (coffeeMachine->IsEnoughIngredients() == false) {
                    coffeeMachine->SetState(State::Uploading);
                    continue;
            }

            if (coffeeMachine->GetTimer() == 1) { // Симуляция времени приготовления кофе
                string receiptType = coffeeMachine->GetReceiptType(coffeeMachine->GetCurrentReceiptNumber());
                cout << "Готовлю " << receiptType << '\n';
                                
                coffeeMachine->SwitchTimer();
                coffeeMachine->Processing();
                cout << receiptType << " готово!\n";
                coffeeMachine->InitTimer();
                coffeeMachine->PrintIngredietnsInfo();

                if (coffeeMachine->IsEnoughIngredients() == false) {
                    coffeeMachine->SetState(State::Uploading);
                    continue;
                }
                /* Спросить выпить еще */
                coffeeMachine->AskDrinkYet();
            }
        }
  
        // Состояние загрузки кофе
        if (coffeeMachine->GetState() == State::Uploading) {
            coffeeMachine->NotEnoughIngredientsMessage();
            string answer;
            cout << "Хотите наполнить емкости? Y/N\n";
            cin >> answer;

            if (answer == "Y" || answer == "y") {
                coffeeMachine->InitTimer();
                cout << "Вы наполняете емкости\n";
                coffeeMachine->SwitchTimer();
                coffeeMachine->UpdateIngredientsVolume();
                cout << "Емкости с ингредиентами наполнены\n";
                coffeeMachine->InitTimer();
                coffeeMachine->PrintIngredietnsInfo();
                /* Спросить выпить еще */
                coffeeMachine->AskDrinkYet();
            }
            else {
                coffeeMachine->SetState(State::SwitchingOff);
                cout << "< Выход >\n";
            }
        }
    }
    coffeeMachine->~CoffeeMachine(); // Явный вызов деструктора для обновления информации в файле
    return 0;
}
