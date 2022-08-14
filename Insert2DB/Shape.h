#pragma once
#include"enum.h"
#include<string>
class Shape {
public:
	ShapeType shape_type;
	std::string parameter;
	virtual const char* className()
	{
		return "Shape";
	}
};
class Rectangular_Shape :public Shape
{
public:
	virtual const char* className()
	{
		return "Rectangular";
	}
	double height, wide;
	double area()
	{
		return height * wide;
	}
};