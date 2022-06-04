#pragma once
class Shape {
	virtual const char* className()
	{
		return "Shape";
	}
};
class Rectangular :public Shape
{
	virtual const char* className()
	{
		return "Rectangular";
	}
	double length, wide;
	double area()
	{
		return length * wide;
	}
};