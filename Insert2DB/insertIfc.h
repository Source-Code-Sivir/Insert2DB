#pragma once
#ifndef INSERT2DB
#define INSERT2DB
#include<initializer_list>
#include<string>
#include"enum.h"
#include"sqlBag.h"
#include"GetID.h"
#include<vector>
#include<unordered_map>
#include<string>
namespace Insert2DB {
	//�������ռ��и��𽫶�Ӧ��ʵ����뵽���ݿ��У����ҷ��ز����ʵ�������ݿ��е�id
	//���ݿ��Ѿ���������� select id 
	//extern std::unordered_map<std::string, int> longnitudal;//��¼������״��������Ӧ��sweptdisksolidid
	//extern std::unordered_map<std::string, int> shears;//��¼������״������Ӧ��sweptdisksolidid
	int InsertPoint3D(std::vector<double>& point);
	int InsertDirection3D(std::vector<double>& direction);
	int InsertPlacement3D(std::vector<double> point, std::vector<double> directionz, std::vector<double> directionx);
	int InsertLine(std::vector<double> point, std::vector<double> direction);
	int InsertCircle(std::vector<double> point, std::vector<double> directionx, std::vector<double> directionz, double diameter);
	int InsertTrimmedCurve(CurveType type, double begin, double end, std::vector<double>& parameter, bool same, const char* last);
	int InsertCompositeCurve(std::vector<int> Trimmedcurve);
	int InsertSweptDiskSlod(TrimmedCurveType type, std::vector<double> curve, double diameter);
	int InsertMappedItem(TrimmedCurveType type, std::vector<double> curve, double diameter, std::vector<double>&point);
	int InsertReinforcingBar(TrimmedCurveType type, std::vector<double>& curve, double diameter, std::vector<std::vector<double>>point, int parentLocalID, std::vector<double>& origin, std::vector<double>& dz, std::vector<double>& dx);
	//��Ӧ����ֽ�����в���������֮�⻹Ҫ��¼�ֽ��localPlacement��Ҳ�����൱����������ϵλ��emmm��localplacement����Ҫ���ǮŪ��
	int InsertLocalPlacement(int parentLocalID,std::vector<double> &point,std::vector<double>&dz,std::vector<double>&dx);
	
	int InsertBuilding();
	int InsertStory();

}
#endif // !INSERT@DB

