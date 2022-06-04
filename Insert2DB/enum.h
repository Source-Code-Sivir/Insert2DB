#pragma once
#ifndef ENUM_H
#define ENUM_H
enum BeamType {
	Girder
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
	first,secondA,secondB,threeA,threeB,four,five
};
enum ShapeRepresentationType {
	MappedItem,
	SweptDiskSolid
};
enum TrimmedCurveType {
	LongitudinalBarCurve = 1,
	TiedBarCurve,
};
enum CurveType {
	Line,
	Circle
};
#endif // !ENUM_H

