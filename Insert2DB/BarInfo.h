#pragma once
#ifndef BARINFOR_H
#define BARINFOR_H
#include<vector>
#include"enum.h"
#define TopLeft TopEndSupportBarInfo
#define TopMid TopLinkBarInfo;//上中
#define TopRight TopInternalSupportBarInfo;//上右
#define BotLeft BotEndSupprtBarInfo;//下左
#define BotMid BotSpanBarInfo;//下中
#define BotRight BotInternalSupportBarInfo;//下右
class BasicBarInfo
{
public:
	BasicBarInfo(int a = 0, int b = 0, int c = 0, int d = 0, int e = 0, int f = 0) :id(a), row(b), position(c), numofRebar(d), diameter(e), BarType(f) {};
	//BasicBarInfo() {};
	static int cur;
	int id;
	int row;
	int position;
	int numofRebar;
	int diameter;
	SteelType BarType;
	
};
struct LongitudinalBarInfo {
	std::vector<BasicBarInfo> BarInfos;
	//六个分别代表 
	LongitudinalBarInfo() :BarInfos(6) {};
};
struct ShearLinkBasicInfo
{
	static int cur;
	int id,position, numofLegs, Diameter, spacing;
	SteelType BarType;
	ShearLinkBasicInfo(int a = 0, int b = 0, int c = 0, SteelType d = HPB300, int e = 0, int f = 0) :id(a), position(b), numofLegs(c), BarType(d), Diameter(e), spacing(f) {};
	//ShearLinkBasicInfo() {};
};
struct SideBarInfo
{
	std::vector<BasicBarInfo> infos;
	SideBarInfo():infos(3) {};
};
struct ShearLinkInfo
{
	ShearLinkBasicInfo LeftZoneInfo, NormalZoneInfo, RightZoneInfo;
	ShearLinkInfo() {};
};
typedef BasicBarInfo TiedBarInfo;
class SpanBarInfo {
public:
	//为什么起这么拗口的名字，自己去问邓老师,我自己定义了别名没用这名字
	LongitudinalBarInfo TopEndSupportBarInfo;//上左
	LongitudinalBarInfo TopLinkBarInfo;//上中
	LongitudinalBarInfo TopInternalSupportBarInfo;//上右
	LongitudinalBarInfo BotEndSupprtBarInfo;//下左
	LongitudinalBarInfo BotSpanBarInfo;//下中
	LongitudinalBarInfo BotInternalSupportBarInfo;//下右

	SideBarInfo Side;

	ShearLinkInfo ShearLinks;

	TiedBarInfo Tied;
	SpanBarInfo(LongitudinalBarInfo topleft, LongitudinalBarInfo topmid, LongitudinalBarInfo topright,
		LongitudinalBarInfo botleft, LongitudinalBarInfo botmid, LongitudinalBarInfo botright, SideBarInfo side, ShearLinkInfo shear
		, TiedBarInfo tied) :TopEndSupportBarInfo(topleft), TopLinkBarInfo(topmid), TopInternalSupportBarInfo(topright), BotEndSupprtBarInfo(botleft),
		BotSpanBarInfo(botmid), BotInternalSupportBarInfo(botright), Side(side), ShearLinks(shear), Tied(tied) {};
	SpanBarInfo() {};

};
#endif // !BARINFOR_H

