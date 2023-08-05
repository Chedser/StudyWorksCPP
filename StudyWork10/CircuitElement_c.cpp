#ifndef CIRCUITELEMENT_C
#define CIRCUITELEMENT_C

#include "CircuitElement_h.h"

BaseCircuitElement::BaseCircuitElement(float voltage, float resistance) {
	this->voltage = voltage;
	this->resistance = resistance;
}
float BaseCircuitElement::GetVoltage() { return voltage; }
float Resistor::GetEnergy() { return (voltage * voltage) / resistance; }
float Conductor::GetSectionalArea() { return sectionalArea; }
float Conductor::GetLength() { return length; }
float Conductor::GetResistivity() { return resistivity; }
float PowerSupply::GetEMF() { return emf; }
unsigned int BaseActiveCircuitElement::GetFrequency() { return frequency; }
unsigned int BaseActiveCircuitElement::GetAngularFrequency() { return 2 * PI * frequency; }
float Condenser::GetCapacity() { return capacity; }
unsigned int Condenser::GetCharge() { return capacity * voltage; }
float Inductor::GetInductance() { return inductance; }
float Triode::GetB() { return b; }
float Triode::GetA() { return b / (1 + b); }
#endif 
