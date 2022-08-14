#pragma once
#ifndef GETMODELINFO_H
#define GETMODELINFO_H
#include<unordered_map>
#include"BarInfo.h"
#include"sqlBag.h"
int getBar_callback(void* data, int argc, char** argv, char** azColName);
int getBeam_callback(void* data, int argc, char** argv, char** azColName);
int getSection_callback(void* data, int argc, char** argv, char** azColName);
int getSpan_callback(void* data, int argc, char** argv, char** azColName);
int getPoint_callback(void* data, int argc, char** argv, char** azColName);
void getBar();
void getBeam();
void getPoint();
void getSection();
void getSpan();

class getModelInfo {
public:
	static std::unordered_map<int, Component_Beam>beams;
	static std::unordered_map<int, SpanInfo>spans;
	static std::unordered_map<int, SpanBarInfo>barinfos;
	static std::unordered_map<int, Point>points;
	static std::unordered_map<int, Component_Column> columns;
	static std::unordered_map<int, Shape*>sections;
};
#endif // !GETMODELINFO_H

