#ifndef IOMANAGER_C
#define IOMANAGER_C

#include "CircuitElement_h.h"
#include "IOManager_h.h"

string IOManager::GetManual() {
    string manual = "Поддерживаемые опции запуска:\n\
    -help или -h - запуск программы в режиме получения справки\n\
    -c [N] [file_name] [circuit_element_type] - запуск программы в режиме создания электронной\n\
    таблицы записей, N - количество записей, file_name - имятекствого файла,\n\
    в котором будет сохранен массив(таблица) записей.\n\
    circuit_element_type - тип элемента электрической цепи:\n\
    1 - Резистор\n\
    2 - Проводник\n\
    3 - Источник питания\n\
    4 - Конденсатор\n\
    5 - Индуктор\n\
    6 - Биполярный транзистор\n\
    -r [N] [file_name] - запуск программы в режиме чтения содержимого \n\
    текстового фала file_name\n";

    return manual;
} 

bool IOManager::IsDigit(string str) {
   if (str.empty()) { return false; }

    bool isDigit = true;
    for (char s : str) {
        if (!isdigit(s)) {
            isDigit = false;
            break;
        }
    }
    return isDigit;
}

bool IOManager::FileIsEmpty(string fileName) {
    ifstream fin(fileName);

    if (!fin.is_open()) { throw std::runtime_error("Ошибка открытия файла\n"); }
    int symCount = 0;
    char c;

    while (!fin.eof()) {
        fin >> c;
        ++symCount;
    }

    fin.close();
    return (symCount == 1 || symCount == 0) ? true : false;
}

int IOManager::GetRecordsCount(string  fileName) {
    ifstream fin(fileName);

    if (!fin.is_open()) { throw std::runtime_error("Ошибка открытия файла\n"); }
    string str;
    int recordsCount = 0;
    while (getline(fin, str)) {
        ++recordsCount;
    }

    fin.close();
    return recordsCount;
}

vector<string> IOManager::SplitString(string str, string delimiter) {

    std::vector<std::string> splittedString;
    int startIndex = 0;
    int  endIndex = 0;
    while ((endIndex = str.find(delimiter, startIndex)) < str.size()){
        std::string val = str.substr(startIndex, endIndex - startIndex);
        splittedString.push_back(val);
        startIndex = endIndex + delimiter.size();
    }
    if (startIndex < str.size()){
        std::string val = str.substr(startIndex);
        splittedString.push_back(val);
    }
    return splittedString;
}

void IOManager::InputRecord(std::ostream& stream, const char* delimiter, int circuitElementType) {
    CircuitElementProperties circuitElementProperties;

    cout << "Введите напряжение\n";
    cin >> circuitElementProperties.voltage;

    Resistor* resistor;
    Conductor* conductor;
    PowerSupply* powerSupply;
    Condenser* condenser;
    Inductor* inductor;
    Triode* triode;

    switch (circuitElementType){
    case 1:  
        cout << "Введите сопротивление\n";
        cin >> circuitElementProperties.resistance;
        
        resistor = new Resistor(circuitElementProperties.voltage, circuitElementProperties.resistance);
        stream << "Resistor;" << "V" << resistor->GetVoltage() << delimiter << "R" << resistor->GetResistance() << delimiter <<
           "C" << resistor->GetCurrent() << delimiter << "E" << resistor->GetEnergy() << '\n';
            
        break;
    case 2: 
        cout << "Введите силу тока\n";
        cin >> circuitElementProperties.current;
        cout << "Введите площадь поперечного сечения\n";
        cin >> circuitElementProperties.sectionalArea;
        cout << "Введите длину\n";
        cin >> circuitElementProperties.length;
        cout << "Введите удельно сопротивление\n";
        cin >> circuitElementProperties.resistivity;
               
        conductor = new   Conductor(circuitElementProperties.voltage, circuitElementProperties.current, circuitElementProperties.sectionalArea, circuitElementProperties.length, circuitElementProperties.resistivity);  
        stream << "Conductor;" << "V" << conductor->GetVoltage() << delimiter << "R" << conductor->GetResistance() << delimiter <<
            "C" << conductor->GetCurrent() << delimiter << "S" << conductor->GetSectionalArea() << delimiter <<
             "L" << conductor->GetLength() << delimiter << "r" << conductor->GetResistivity() << '\n';
		break;

    case 3: 
        cout << "Введите внутреннее сопротивление\n";
        cin >> circuitElementProperties.resistance;
 
        powerSupply = new PowerSupply(circuitElementProperties.voltage, circuitElementProperties.resistance);
        stream << "Power Supply;" << "V" << powerSupply->GetVoltage() << delimiter << "R" << powerSupply->GetResistance() << delimiter <<
            "C" << powerSupply->GetCurrent() << delimiter << "EMF" << powerSupply->GetEMF() << '\n';
        
        break;
    case 4:  cout << "Введите частоту\n";
        cin >> circuitElementProperties.frequency;
        cout << "Введите емкость\n";
        cin >> circuitElementProperties.capacity;

        condenser = new Condenser(circuitElementProperties.voltage, circuitElementProperties.frequency, circuitElementProperties.capacity);
        stream << "Condenser;" << "V" << condenser->GetVoltage() << delimiter << "R" << condenser->GetResistance() << delimiter <<
            "Cap" << condenser->GetCapacity() << delimiter << "Ch" << condenser->GetCharge() << delimiter <<
            "F" << condenser->GetFrequency() << delimiter << condenser->GetAngularFrequency() << '\n';
        break;
    case 5: cout << "Введите частоту\n";
        cin >> circuitElementProperties.frequency;
        cout << "Введите индуктивнсть\n";
        cin >> circuitElementProperties.inductance;
       
        inductor = new Inductor(circuitElementProperties.voltage, circuitElementProperties.frequency, circuitElementProperties.inductance);
        stream << "Inductor;" << "V" << inductor->GetVoltage() << delimiter << "R" << inductor->GetResistance() << delimiter <<
            "Ind" << inductor->GetInductance() << delimiter <<
            "F" << inductor->GetFrequency() << delimiter << inductor->GetAngularFrequency() << '\n'; break;
    case 6: cout << "Введите частоту\n";
        cin >> circuitElementProperties.frequency;
        cout << "Введите коэффициент передачи базового тока\n";
        cin >> circuitElementProperties.b;
        cout << "Введите сопротивление\n";
        cin >> circuitElementProperties.resistance;

        triode = new Triode(circuitElementProperties.voltage, circuitElementProperties.resistance, circuitElementProperties.frequency, circuitElementProperties.b);
        stream << "Triode;" << "V" << triode->GetVoltage() << delimiter << "R" << triode->GetResistance() << delimiter <<
            "A" << triode->GetA() << delimiter << "B" << triode->GetB() <<
            "F" << triode->GetFrequency() << delimiter << triode->GetAngularFrequency() << '\n';
                break;

    default:
        cout << "Введите сопротивление\n";
        cin >> circuitElementProperties.resistance;

        resistor = new Resistor(circuitElementProperties.voltage, circuitElementProperties.resistance);
        stream << "Resistor;" << "V" << resistor->GetVoltage() << delimiter << "R" << resistor->GetResistance() << delimiter <<
            "C" << resistor->GetCurrent() << delimiter << "E" << resistor->GetEnergy() << '\n';
        break;
    }
}

void IOManager::CreateRecords(int recordsCount, string fileName, const char* delimiter, int circuitElementType) {
    ofstream fout(fileName, std::ios::out | std::ios::app);

    if (!fout.is_open()) {
        cout << "Ошибка открытия файла\n";
        exit(1);
    }

    switch (circuitElementType) {
    case 1: cout << "Резисторы " << recordsCount << "\n";break;
    case 2: cout << "Проводники " << recordsCount << "\n";   break;
    case 3: cout << "Источники питания " << recordsCount << "\n"; break; 
    case 4: cout << "Конденсаторы " << recordsCount << "\n"; break;
    case 5: cout << "Индукторы " << recordsCount << "\n"; break;
    case 6: cout << "Биполярные транзисторы " << recordsCount << "\n"; break;
    default:
        cout << "Резисторы " << recordsCount << "\n";
        break;
    }

    for (int i = 0; i < recordsCount; i++) {
        cout << "\nВведите запись " << i + 1 << "\n";
        InputRecord(fout, delimiter, circuitElementType);
    }

    fout.flush();
    fout.close();
}

void IOManager::PrintRecords(int  recordsCount, string fileName, const char* delimiter) {
    ifstream fin(fileName);

    if (!fin.is_open()) {
        cout << "Ошибка открытия файла\n";
        exit(1);
    }

    if (FileIsEmpty(fileName)) {
        cout << "Файл " << fileName << " пуст\n";
        exit(1);
    }

    int recordsCountInFile = GetRecordsCount(fileName); // Количество записей в файле
    int recordsCountToPrint = recordsCount; // Количество записей для отображения пользователю

     // Еси пользователь запросил больше чем надо записей или не больше нуля
    if ((recordsCountToPrint > recordsCountInFile) || recordsCountToPrint <= 0) {
        recordsCountToPrint = recordsCountInFile;
    }

    int currentRecordsCount = 0; // Счетчик для записей
    vector<string> vectorStr;
    string str;

    while (currentRecordsCount != recordsCountToPrint) {
        getline(fin, str);
        vectorStr = SplitString(str, delimiter);
        for (string str : vectorStr) { cout << str << " "; }
        cout << "\n";
        ++currentRecordsCount;
    }
    fin.close();
}
#endif
