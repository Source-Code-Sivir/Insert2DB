#pragma once
#ifndef GETCODEPARA_H
#define GETCODEPARA_H
#include"enum.h"
inline double GetHookDia(int degree, int diameter) {
	return 8 * diameter;
}
inline int Getlabe(ConcreteType ctype, SteelType stype, EnvironmentType eType,int diameter) {
	return 33 * diameter;
}
inline int GetLaE(SteelType steel, EarthquakeResistence earthqR, ConcreteType cType, int diameter) {
	return 30 * diameter;
}
inline int getProtectThick(EnvironmentType etype, ComponentType ctype) {
	return 25;
}
inline int GetLle(SteelType stype, ConcreteType ctype, int diameter, double precentage,EarthquakeResistence er) {
	return 41 * diameter;
}
inline int GetLl(SteelType stype, ConcreteType ctype, int diameter, double precentage) {
	return 41 * diameter;
}
#endif // !GETCODEPARA_H

