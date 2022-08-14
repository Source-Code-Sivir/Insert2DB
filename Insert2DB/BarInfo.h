#pragma once
#ifndef BARINFOR_H
#define BARINFOR_H
#include<vector>
#include"enum.h"
#include"Shape.h"
//#define TopLeft TopEndSupportBarInfo
//#define TopMid TopLinkBarInfo//����
//#define TopRight TopInternalSupportBarInfo//����
//#define BotLeft BotEndSupprtBarInfo//����
//#define BotMid BotSpanBarInfo//����
//#define BotRight BotInternalSupportBarInfo//����
//using point = std::vector<double>[3];
//using direction = std::vector<double>[3];
typedef std::vector<double> Point;
typedef std::vector<double> Direction;

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
	LongitudinalBarInfo TopLeft;//����
	LongitudinalBarInfo TopMid;//����
	LongitudinalBarInfo TopRight;//����
	LongitudinalBarInfo BotLeft;//����
	LongitudinalBarInfo BotMid;//����
	LongitudinalBarInfo BotRight;//����

	SideBarInfo Side;

	ShearLinkInfo ShearLinks;

	TiedBarInfo Tied;
	SpanBarInfo(LongitudinalBarInfo topleft, LongitudinalBarInfo topmid, LongitudinalBarInfo topright,
		LongitudinalBarInfo botleft, LongitudinalBarInfo botmid, LongitudinalBarInfo botright, SideBarInfo side, ShearLinkInfo shear
		, TiedBarInfo tied) :TopLeft(topleft), TopMid(topmid), TopRight(topright), BotLeft(botleft),
		BotMid(botmid), BotRight(botright), Side(side), ShearLinks(shear), Tied(tied) {};
	SpanBarInfo() {};

};
class SpanInfo {//Ĭ����z�������
public:
	int xstartoffset, xendoffset, ystartoffset, yendoffset;
	SpanBarInfo span_bar_info;
	SpanType span_type;
	int pt1Type, pt2Type;
};
class Component_Beam:public Component {//�����ݿ������Ĳ���������columnslenû��ȷ��
public:
	int id;
	std::vector<SpanInfo> spans_info;
	std::vector<double> columns_len;
	std::vector<double>spans_clear_len;
	std::vector<double> span_begin_point;
	BeamType beam_type;
	double len;
	std::vector<double> begin;
	std::vector<double> directionz,directionx;//ָ��z�᷽��
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
	void CalculateBar();//����ֽ����״��λ�ò���
	void handleSignal();
	inline void handlecolumn();
};
class Component_Column:public Component {
	int ptID;
	int xstartoffser, xendoffset, ystartoddset, yendoffset;
	
	Shape* section;
	int width, height;
	
};
#endif // !BARINFOR_H

