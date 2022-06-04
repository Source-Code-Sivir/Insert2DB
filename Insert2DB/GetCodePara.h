#pragma once
#ifndef GETCODEPARA_H
#define GETCODEPARA_H
#include"enum.h"
inline double GetHookDia(int degree, int diameter) {
	return 8 * diameter;
}
int Getlabe(ConcreteType ctype, SteelType stype, EnvironmentType eType,int diameter) {
	return 33 * diameter;
}
int getProtectThick(EnvironmentType etype, ComponentType ctype) {
	return 25;
}
#endif // !GETCODEPARA_H

