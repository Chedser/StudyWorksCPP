/* BaseClassRefDemo.cpp - Листинг программы для 10-ой лабораторной работ
* Вариант 7
*****************************************************************
* Имя файла : BaseClassRefDemo.cpp
* Резюме : Пример программы, написанной на языке программирования C++
* Описание : Разрабатываемая программа предназначена для хранения массива переменных структурного типа данных(записей)
* Дата создания : 2022/02/04
* Автор : Vectorflex
* Платформа : OS Linux Mint
*/

#include <iostream>
#include <exception>
#include "CircuitElement_h.h"

using std::cout;

class TriodeTestParent{
    protected:
        float voltage;
        float  resistance;
        float frequency;
        float b;  
    public:    
    TriodeTestParent(float voltage, float resistance, int frequency, float b){
    cout << "Вызов конструктора базового класса TriodeTestParent\n";
        this->voltage = voltage;
    	this->resistance = resistance;
   	 this->frequency = frequency;
    	this->b = b;
    }
    
   virtual ~TriodeTestParent(){
 	cout << "Вызов деструктора базового класса TriodeTestParent\n";
   }
};

class TriodeTestChild:public TriodeTestParent{
     public:    
    		TriodeTestChild(float voltage, float resistance, int frequency, float b) :TriodeTestParent(voltage, resistance, frequency, b){
    			cout << "Вызов конструктора базового класса TriodeTestChild\n";
		}
 virtual ~TriodeTestChild(){
	cout << "Вызов деструктора базового класса TriodeTestChild\n";}
};

int main(int argc, char** argv){
	setlocale(LC_ALL, "");
    
    TriodeTestChild child(220, 10, 50, 20);
    TriodeTestParent* parent = &child; 
  	return 0;
}
