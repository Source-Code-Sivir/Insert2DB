#pragma once
#ifndef VECTOR3D_H
#define VECTOR3D_H
struct Vector3D
{
	double val1, val2, val3;
	Vector3D(double a = 0, double b = 0, double c = 0) :val1(a), val2(b), val3(c) {};
	Vector3D() {};
};
struct Vector2D
{
	double val1, val2 ;
	Vector2D(double a = 0, double b = 0) :val1(a), val2(b) {};
	Vector2D() {};
};
typedef Vector3D Point3D;
typedef Vector3D Direction3D;
typedef Vector2D Point2D;
typedef Vector2D Direction2D;
struct Placement3D
{
	Point3D origin, directionX, directionZ;
};

#endif // !VECTOR3D_H
