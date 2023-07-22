#include "CoffeeMachine_h.h"

using namespace Morozov;

CoffeeMachine::CoffeeMachine() {
    try {
        if (IOManager::FileExists(fileName)) { // Файл существует
            if (IOManager::FileIsEmpty(fileName)) { // Файл пуст
                InitFile(fileName); // Пишем начальные значения
                ReadFile(fileName); // Сразу читаем из файла в переменные
            }
            else { // Читаем из файла в переменные
                ReadFile(fileName);
            }
        }
        else { // Файл не существует
            InitFile(fileName);
            ReadFile(fileName);
        }
    }
    catch (std::runtime_error& err) {
        cout << err.what();
        exit(1);
    }
}

CoffeeMachine::~CoffeeMachine() { WriteFile(fileName); }

bool CoffeeMachine::IsCofeeEnough(int coffeeVolume) {
    bool isCoffeEnough = true;

    if ((currentCofeeVolume - coffeeVolume) < 0) {
        isCoffeEnough = false;
        enoughFlagsVolume[(int)Ingredients::Coffee] = 0;
    }
    return isCoffeEnough;
}
bool CoffeeMachine::IsMilkEnough(int milkVolume) {
    bool isMilkEnough = true;

    if ((currentMilkVolume - milkVolume) < 0) {
        isMilkEnough = false;
        enoughFlagsVolume[(int)Ingredients::Milk] = 0;
    }
    return isMilkEnough;
}
bool CoffeeMachine::IsWaterEnough(int waterVolume) {
    bool isWaterEnough = true;

    if ((currentWaterVolume - waterVolume) < 0) {
        isWaterEnough = false;
        enoughFlagsVolume[(int)Ingredients::Water] = 0;
    }
    return isWaterEnough;
}

void CoffeeMachine::TakeCoffeeDemage(int demage) {currentCofeeVolume -= demage;}
void CoffeeMachine::TakeMilkDemage(int demage) {currentMilkVolume -= demage;}
void CoffeeMachine::TakeWaterDemage(int demage) {currentWaterVolume -= demage;}

void CoffeeMachine::UpdateIngredientsVolume() {
    ofstream fout(fileName, std::ios_base::out);

    if (!fout.is_open()) { throw std::runtime_error("Ошибка открытия файла\n"); }

    int i = 0;

    while (i != INGREDIENTS_COUNT) {
 
        switch (i) {
        case (int)Ingredients::Coffee: fout <<  initCofeeVolume << "\n";  break;
        case (int)Ingredients::Milk: fout << initMilkVolume << "\n"; break;
        case (int)Ingredients::Water: fout << initMilkVolume; break;

            if (fout.good() && enoughFlagsVolume[i] == 0) {
                enoughFlagsVolume[i] = 1;
                throw std::runtime_error("Неизвестная ошибка\n");
            }
        }
        ++i;
    }

    fout.close();
    ReadFile(fileName);
}
State CoffeeMachine::GetState() { return state; }
void CoffeeMachine::SetState(State state) { this->state = state; }
void CoffeeMachine::SetReceiptNumber(int receiptNumber) { currentReceiptNumber = receiptNumber; }
void CoffeeMachine::SwitchTimer() {// Таймер для симуляции работы кофемашины

    while (timer <= 3) {
        cout << "    " << timer++ << "\a\n";
	sleep_for(nanoseconds(10));
        sleep_until(system_clock::now() + seconds(1));
    }
}
bool CoffeeMachine::CheckReceiptNumber(int receiptNumber) { // Проверка правильности ввода
    bool isGood = true;

    if (receiptNumber < 0 || receiptNumber > INGREDIENTS_COUNT) {
        cout << "Неизвестная команда\n\n";
        isGood = false;
    }
    return isGood;
}

string CoffeeMachine::GetReceiptType(int receiptNumber) {
    string receiptType = "Espresso";

    switch (receiptNumber) {
    case (int)CoffeeType::Lungo: receiptType = "Lungo"; break;
    case (int)CoffeeType::Melange: receiptType = "Melange"; break;
    default: receiptType = "Espresso";
    }
    return receiptType;
}

int CoffeeMachine::GetCurrentReceiptNumber() { return currentReceiptNumber; }
void CoffeeMachine::InitTimer() { timer = 1; }
int CoffeeMachine::GetTimer() { return timer; }
bool CoffeeMachine::IsEnoughIngredients() {
    bool isEnough = false;

    int coffeeDemage = 50;
    int milkDemage = 50;
    int waterDemage = 50;

    switch (currentReceiptNumber) {
        //Эспрессо 50мл кофе, 50мл воды, 50мл молока
    case (int)CoffeeType::Espresso:
        if (IsCofeeEnough(coffeeDemage) && IsMilkEnough(milkDemage) && IsWaterEnough(waterDemage)) {
            isEnough = true;
        }
        break;
        // Лунго 30мл кофе, 120 вода
    case (int)CoffeeType::Lungo:
        coffeeDemage = 30;
        waterDemage = 120;
        if (IsCofeeEnough(coffeeDemage) && IsWaterEnough(waterDemage)) { isEnough = true; }
        break;
        // Меланж 70мл кофе, 80мл вода
    case (int)CoffeeType::Melange:
        coffeeDemage = 70;
        milkDemage = 80;
        if (IsCofeeEnough(coffeeDemage) && IsWaterEnough(milkDemage)) { isEnough = true; }
        break;
    }
	WriteFile(fileName); // Обновляем информацию в файле об ингредиентах
    return isEnough;
}
void CoffeeMachine::Processing() { // Готовка кофе
    int coffeeDemage = 50;
    int milkDemage = 50;
    int waterDemage = 50;

    switch (currentReceiptNumber) {
        // //Эспрессо 50мл кофе, 50мл воды, 50мл молока
    case (int)CoffeeType::Espresso:
        if (IsCofeeEnough(coffeeDemage) && IsMilkEnough(milkDemage) && IsWaterEnough(waterDemage)) {
            TakeCoffeeDemage(coffeeDemage);
            TakeMilkDemage(milkDemage);
            TakeWaterDemage(waterDemage);
        }
        break;
         // Лунго 30мл кофе, 120 вода
    case (int)CoffeeType::Lungo:
        coffeeDemage = 30;
        waterDemage = 120;
        if (IsCofeeEnough(coffeeDemage) && IsWaterEnough(waterDemage)) {
            TakeCoffeeDemage(coffeeDemage);
            TakeWaterDemage(waterDemage);
        }
        break;
      // Меланж 70мл кофе, 80мл вода
    case (int)CoffeeType::Melange:
        coffeeDemage = 70;
        milkDemage = 80;

        if (IsCofeeEnough(coffeeDemage) && IsMilkEnough(milkDemage)) {
            TakeCoffeeDemage(coffeeDemage);
            TakeMilkDemage(milkDemage);
        }
        break;
    }

}
void CoffeeMachine::NotEnoughIngredientsMessage() { // Сообщение о недостаточности ингредиентов
    for (int i = 0; i < INGREDIENTS_COUNT; i++) {
        if (enoughFlagsVolume[i] == 0) {
            switch (i) {
                //кофе
            case (int)Ingredients::Coffee: cout << "Засыпьте кофе в емкость\n"; break;
                //молоко
            case (int)Ingredients::Milk: cout << "Залейте молоко в емкость\n"; break;
                //воду
            case (int)Ingredients::Water: cout << "Залейте воду в емкость\n"; break;
           }
        }
    }
}

void CoffeeMachine::PrintIngredietnsInfo() {
    cout << "Остатки: Кофе " << currentCofeeVolume << " Молоко " << currentMilkVolume << " Вода " << currentWaterVolume << '\n';
}

void  CoffeeMachine::AskDrinkYet() { // Спросить об еще одной чашке
    cout << "Еще по чашке? Y/N\n";
    string answer = "";

    cin >> answer;
   
	if (answer == "Y" || answer == "y") {
       	 SetState(State::Reading);
    }
    else {
        SetState(State::SwitchingOff);
        cout << "< ВЫХОД >\n";
    }
}

void CoffeeMachine::InitFile(string fileName) { // Заполнить файл значениями по умолчанию 
    ofstream fout(fileName, std::ios_base::out);

    if (!fout.is_open()) { throw std::runtime_error("Ошибка открытия файла\n"); }
       
    fout << initCofeeVolume << "\n" << initMilkVolume << "\n" << initWaterVolume;
    fout.close();
}

void CoffeeMachine::ReadFile(string fileName) {
    ifstream fin(fileName, std::ios_base::in);

    if (!fin.is_open()) { throw std::runtime_error("Ошибка открытия файла\n"); }
   
    int i = 0;
    string line;
   
	while (!fin.eof()) {
         getline(fin, line, '\n');
        switch (i) {
            case (int)Ingredients::Coffee: currentCofeeVolume = stoi(line);  break;
            case (int)Ingredients::Milk: currentMilkVolume = stoi(line); break;
            case (int)Ingredients::Water: currentWaterVolume = stoi(line); break;
        }
        ++i;
    }
     fin.close();
}

void  CoffeeMachine::WriteFile(string fileName) {
    ofstream fout(fileName, std::ios_base::out | std::ios_base::trunc);

    if (!fout.is_open()) { throw std::runtime_error("Ошибка открытия файла\n"); }

    fout << currentCofeeVolume << "\n" << currentMilkVolume << "\n" << currentWaterVolume;
    fout.close();
}
