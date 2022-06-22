#pragma once
#ifndef BARINFOR_H
#define BARINFOR_H
#include<vector>
#include"enum.h"
#include"Shape.h"
//#define TopLeft TopEndSupportBarInfo
//#define TopMid TopLinkBarInfo//上中
//#define TopRight TopInternalSupportBarInfo//上右
//#define BotLeft BotEndSupprtBarInfo//下左
//#define BotMid BotSpanBarInfo//下中
//#define BotRight BotInternalSupportBarInfo//下右
//using point = std::vector<double>[3];
//using direction = std::vector<double>[3];

class Building {
public:
	EnvironmentType environment_type;
};
class Component {
public:
	EnvironmentType environment_type;
	EarthquakeResistence earthquake_resistence;
};
class BasicBarInfo
{
public:
	BasicBarInfo( int d = 0, int e = 0, int f = 0) : numofRebar(d), diameter(e), BarType(SteelType(f)) {};
	//BasicBarInfo() {};
	int numofRebar;
	int diameter;
	SteelType BarType;
	
};

struct ShearLinkBasicInfo
{
	static int cur;
	int id,position, numofLegs, Diameter, spacing;
	SteelType BarType;
	ShearLinkBasicInfo(int a = 0, int b = 0, int c = 0, SteelType d = HPB300, int e = 0, int f = 0) :id(a), position(b), numofLegs(c), BarType(d), Diameter(e), spacing(f) {};
	//ShearLinkBasicInfo() {};
};
typedef std::vector<BasicBarInfo> LongitudinalBarInfo;
typedef BasicBarInfo SideBarInfo;
struct ShearLinkInfo
{
	ShearLinkBasicInfo LeftZoneInfo, NormalZoneInfo, RightZoneInfo;
	ShearLinkInfo() {};
};
typedef BasicBarInfo TiedBarInfo;
class SpanBarInfo {
public:
	//为什么起这么拗口的名字，自己去问邓老师,我自己定义了别名没用这名字
	LongitudinalBarInfo TopLeft;//上左
	LongitudinalBarInfo TopMid;//上中
	LongitudinalBarInfo TopRight;//上右
	LongitudinalBarInfo BotLeft;//下左
	LongitudinalBarInfo BotMid;//下中
	LongitudinalBarInfo BotRight;//下右

	SideBarInfo Side;

	ShearLinkInfo ShearLinks;

	TiedBarInfo Tied;
	SpanBarInfo(LongitudinalBarInfo topleft, LongitudinalBarInfo topmid, LongitudinalBarInfo topright,
		LongitudinalBarInfo botleft, LongitudinalBarInfo botmid, LongitudinalBarInfo botright, SideBarInfo side, ShearLinkInfo shear
		, TiedBarInfo tied) :TopLeft(topleft), TopMid(topmid), TopRight(topright), BotLeft(botleft),
		BotMid(botmid), BotRight(botright), Side(side), ShearLinks(shear), Tied(tied) {};
	SpanBarInfo() {};

};
class SpanInfo {//默认沿z轴延伸哈
public:
	SpanBarInfo span_bar_info;
	SpanType span_type;
};
class Component_Beam:public Component {
public:
	std::vector<SpanInfo> spans_info;
	std::vector<double> columns_len;
	std::vector<double>spans_clear_len;
	std::vector<double> span_begin_point;
	BeamType beam_type;
	double len;
	std::vector<double> begin;
	std::vector<double> directionz,directionx;//指定z轴方向
	Shape* section;
	int height, width;
	//double xstratoffset, xendoffset, ystartoffset, yendoffset;
	ConcreteType concrete_type;
	int storey;
	void CalculateBeam();
	void HandleLeftSide();
	void HandleRightSide();
	void HandleMid(int i);
	void handleInternal(int i);
	void handleRightSide();
	void CalculateBar();//计算钢筋的形状，位置参数
};
struct Point {
	double x, y, z;
};
typedef Point Direction;

#endif // !BARINFOR_H

