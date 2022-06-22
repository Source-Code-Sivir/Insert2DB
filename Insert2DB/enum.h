#pragma once
#ifndef ENUM_H
#define ENUM_H
enum BeamType {
	Girder
};
enum ShapeType
{
	Rectangular = 1,
	Circle_Section
};
enum ComponentType {
	Beam,Slab,Wall,Column
};
enum SpanType {
	SimplySupported,
	LeftCantilever,
	LeftSide,
	Internal,
	RightSide,
	RightCantilever
};
enum ConcreteType {
	C20,C25,C30,C35,C40,C45,C50,C55,C60
};
enum SteelType {
	HPB300,HRB335,HPB335,HRB400,HRBF400,HRB500,HRBF500
};
enum EnvironmentType {
	first=1,secondA,secondB,threeA,threeB,four,five
};
enum ShapeRepresentationType {
	SweptDiskSolid=1,

};
enum BarType {
	LongitudinalBarCurve = 1,
	TiedBarCurve,
	SheadLinks,
	WaistBar
};
enum CurveType {
	Line_Curve = 1,
	Circle_Curve
};
enum EarthquakeResistence {
	firstR = 1,
	secondR,
	thirdR,
};
#endif // !ENUM_H

