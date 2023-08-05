#ifndef CIRCUITELEMENT_H
#define CIRCUITELEMENT_H

#define PI 3.1415926535

struct CircuitElementProperties {
	float voltage = 0.0f; // Напряжение
	float resistance = 0.0f; // Сопротивление
	float current = 0.0f; // Ток
	float energy = 0.0f; // Мощность
	float sectionalArea = 0.0f; // Площадь поперечного сечения проводника
	float length = 0.0f; // Длина проводника
	float resistivity = 0.0f; // Удельное сопротивление проводника
	float emf = 0.0f; //ЭДС (по умолчанию равно напряжению, если не подключен к цепи)
	unsigned int frequency = 0; // Частота
	unsigned int angularFrequency = 0; // Угловая частота
	float capacity = 0.0f; // Емкость
	unsigned int charge = 0; // Заряд
	float inductance = 0.0f; //Индуктивность
	float b = 0.0f; // Коэффициент передачи базового тока
	float a = 0.0f; // Коэффициент передачи эмитерного тока

};

enum class CircuitElementType {Resistor = 1, 
					Conductor, 
					PowerSupply, 
					Condenser, 
					Inductor, 
					Triode
};

/* КЛАСС ЭЛЕМЕНТА ЦЕПИ (абстрактный) */
class BaseCircuitElement {
protected:
		float voltage = 0.0f; // Напряжение
		float resistance = 0.0f; // Сопротивление

		BaseCircuitElement(float voltage, float resistance);
        	virtual ~BaseCircuitElement(){
        		delete &voltage;
        		delete &resistance;
		}

	public:
		float GetVoltage();
		virtual float GetResistance() = 0;
};

/* КЛАСС ПАССИВНОГО ЭЛЕМЕНТА ЦЕПИ (абстрактный) */
class BasePassiveCircuitElement:public BaseCircuitElement {
protected:
	float current = 0.0f; // Сила тока
	protected:
		BasePassiveCircuitElement(float voltage, float resistance, float current):BaseCircuitElement(voltage, resistance) {
			this->current = current;
		}
        virtual ~BasePassiveCircuitElement(){delete &current;}
	public:
		virtual float GetCurrent() = 0;
};

/************ РЕАЛЬНЫЕ КЛАССЫ ПАССИВНЫХ ЭЛЕМЕНТОВ ЦЕПИ ********************/
// Резистор
class Resistor:public BasePassiveCircuitElement {
	float energy = 0.0f; // Мощность

	public:
	Resistor(float voltage, float currentResistance):BasePassiveCircuitElement(voltage, currentResistance, this->GetCurrent()) {
		energy = GetEnergy();}

		float GetCurrent() override {return voltage / resistance;}
		float GetResistance() override { return resistance; }
		float GetEnergy();
	};

// Проводник
class Conductor:public BasePassiveCircuitElement {
	float sectionalArea = 0.0f; // Площадь поперечного сечения
	float length = 0.0f; // Длина
	float resistivity = 0.0f; // Удельное сопротивление
	public:
		Conductor(float voltage, float current, float sectionalArea, float length, float resistivity):BasePassiveCircuitElement(voltage, this->GetResistance(), current) {
			this->sectionalArea = sectionalArea;
			this->length = length;
			this->resistivity = resistivity;
		}

		float GetResistance() override { return (resistivity * length) / sectionalArea; }
		float GetSectionalArea();
		float GetLength();
		float GetResistivity();
		float GetCurrent() override { return current; }
};

// Источник питания
class PowerSupply:public BasePassiveCircuitElement {
	float emf; // ЭДС
	public:
		PowerSupply(float voltage, float resistance):BasePassiveCircuitElement(voltage, resistance, GetCurrent()) {
				this->emf = voltage;
				}

		float GetCurrent() override { return emf / resistance; } //Получить ток короткогозамыкания
		float GetResistance() override { return resistance; }
		float GetEMF();
};

/* КЛАСС АКТИВНОГО ЭЛЕМЕНТА ЦЕПИ (абстрактный) */
class BaseActiveCircuitElement:public BaseCircuitElement {
	protected:
	unsigned int frequency = 0;
	unsigned int angularFrequency = 0;
    
    BaseActiveCircuitElement(float voltage, float resistance, int           frequency):BaseCircuitElement(voltage, resistance) {
			this->frequency = frequency;
			this->angularFrequency = GetAngularFrequency();
		}

    virtual ~BaseActiveCircuitElement(){
        delete &frequency;
        delete &angularFrequency;}
	public:
		unsigned int GetFrequency();
		unsigned int GetAngularFrequency();
};

/************ РЕАЛЬНЫЕ КЛАССЫ АКТИВНЫХ ЭЛЕМЕНТОВ ЦЕПИ ********************/
// Конденсатор
class Condenser: public BaseActiveCircuitElement{
	float capacity; //Емкость
	unsigned int charge; //Накапливаемый заряд
public:
	Condenser(float voltage, int frequency, float capacity):BaseActiveCircuitElement(voltage,GetResistance(),frequency){
		this->capacity = capacity;
		this->charge = GetCharge();
	}

	float GetResistance() override { return 1 / (angularFrequency * capacity); }
	float GetCapacity();
	unsigned int GetCharge();
};

class Inductor:public BaseActiveCircuitElement {
	float inductance = 0.0f; // Индуктивность
	public:
		Inductor(float voltage, int frequency, float inductance):BaseActiveCircuitElement(voltage, GetResistance(), frequency) {
			this->inductance = inductance;
		}

		float GetResistance() override { return angularFrequency * inductance; }
		float GetInductance();
};

// Биполярнй транзистор
class Triode:public BaseActiveCircuitElement {
	float b = 0.0f; // Коэффициент передачи базового тока
	float a = 0.0f; // Коэффициент передачи эмитерноо тока
	public:
		Triode(float voltage, float resistance, int frequency, float b) :BaseActiveCircuitElement(voltage, resistance, frequency){
			this->b = b;
			this->a = GetA();
		}

		float GetResistance() override { return resistance; }
		float GetB();
		float GetA();
};
#endif
