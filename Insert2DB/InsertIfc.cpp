#include"insertIfc.h"
int GetID::CircleID = 0;
int GetID::CompositeCurveID = 0;
int GetID::DirectionID = 7;
int GetID::LineID = 0;
int GetID::Placement3DID = 0;
int GetID::PointID = 1;
int GetID::ShapreRepresentationID = 0;
int GetID::SweptDiskSolidID = 0;
int GetID::TrimmedCurveID = 0;
int GetID::ReinforcingBarID = 0;
int GetID::MappedItemID = 0;
int GetID::LocalPlacementID = 0;
int GetID::FloorID = 0;
int GetID::BuildingID = 0;
std::vector<int> GetID::floorLocalPlacementID;
std::vector<int> GetID::BuildingLocalPlacementID;
const double precision = 0.001;

std::unordered_map<std::string, int> longnitudal;//记录负筋形状参数所对应的sweptdisksolidid
std::unordered_map<std::string, int> shears;//记录箍筋形状参数对应的sweptdisksolidid
std::string GetInsertCommand(const char* tablename, const char* data) {
	char res[100];
	sprintf_s(res, 100, "Insert into %s values(%s);", tablename, data);
	std::string ans(res);
	//delete[]res;
	return ans;
}
std::string GetSelectCommand(const char* tablename, const char* cond) {
	
	return 0;
}
namespace Insert2DB {
	int InsertPoint3D(std::vector<double>& point) {
		if (point[0] == 0 && point[1] == 0 && point[2] == 0) {
			return 1;
		}
		char* cond = new char[100];
		int pid = GetID::getPointID();
		sprintf_s(cond, 100, "%d,%.2f,%.2f,%.2f", pid, point[0], point[1], point[2]);
		std::string command = GetInsertCommand("IfcPoint", cond);
		SqliteExecution::Instance()->insertDb(command);
		delete[]cond;
		return pid;
	}
	int InsertDirection3D(std::vector<double>& direction) {//处理double的精度问题
		double tmp = sqrt(2) / 2;
		if (abs(direction[0] - 1) < precision && direction[1] < precision && direction[2] < precision) {//1 0 0
			return 1;
		}
		else if (abs(direction[0] + 1) < precision && direction[1] < precision && direction[2] < precision) {//-1 0 0
			return 2;
		}
		else if (abs(direction[1] - 1) < precision && direction[0] < precision && direction[2] < precision) {// 0 1 0
			return 3;
		}
		else if (abs(direction[1] + 1) < precision && direction[0] < precision && direction[2] < precision) {//0 -1 0
			return 4;
		}
		else if (abs(direction[2] - 1) < precision && direction[1] < precision && direction[0] < precision) {//0 0 1
			return 5;
		}
		else if (abs(direction[2] + 1) < precision && direction[1] < precision && direction[0] < precision) {//0 0 -1
			return 6;
		}
		else if (abs(direction[0] - tmp) < precision && abs(direction[1] - tmp) < precision && direction[2] == 0) {
			return 7; //（根2，根2, 0）
		}
		else if (abs(direction[0] + tmp) < precision && abs(direction[1] - tmp) < precision && direction[2] == 0) {
			return 8;
		}//（-根2，根2,0）
		else if (abs(direction[0] + tmp) < precision && abs(direction[1] + tmp) < precision && direction[2] == 0) {
			return 9;
		}//（-根2，-根2,0）
		else if (abs(direction[0] - tmp) < precision && abs(direction[1] + tmp) < precision && direction[2] == 0) {
			return 10;
		}//（根2，-跟2）
		int directionID = GetID::getDirectionID();
		char* val = new char[100];
		sprintf_s(val, 100, "%d,%.3f,%.3f,%.3f", directionID, direction[0], direction[1], direction[2]);
		std::string command = GetInsertCommand("IfcDirection", val);
		SqliteExecution::Instance()->insertDb(command);
		delete[]val;
		return directionID;
	}
	int InsertPlacement3D(std::vector<double> point, std::vector<double> directionz, std::vector<double> directionx) {
		int id1 = InsertPoint3D(point), id2 = InsertDirection3D(directionz), id3 = InsertDirection3D(directionx);
		char* data = new char[100];
		int placeid = GetID::getLineID();
		sprintf_s(data, 100, "%d,%d,%d,%d", placeid, id1, id2, id3);
		std::string command = GetInsertCommand("IfcPlacement3D", data);
		SqliteExecution::Instance()->insertDb(command);
		delete[]data;
		return placeid;
	}
	int InsertLine(std::vector<double> point, std::vector<double> direction) {
		int n = point.size();
		int lineid = GetID::getLineID();
		std::string command;//二维直线或者是三维直线
		switch (n)
		{
		case 2: {
			break;
		}

		case 3: {
			int pointID = InsertPoint3D(point);
			int DirID = InsertDirection3D(direction);
			char* res = new char[100];

			sprintf_s(res, 100, "%d,%d,%d", lineid, pointID, DirID);
			command = GetInsertCommand("IfcLine", res);
			SqliteExecution::Instance()->insertDb(command);
			delete[]res;

			break;
		}
		default: {
			break;
		}

		}
		return lineid;
	}
	int InsertCircle(std::vector<double> point, std::vector<double> directionx, std::vector<double> directionz, double diameter) {
		int id1 = InsertPlacement3D(point, directionx, directionz);
		char* val = new char[100];
		int res = GetID::getCircleID();
		sprintf_s(val, 100, "%d,%d,%.3f", res, id1, diameter);
		std::string command = GetInsertCommand("IfcCircle", val);
		SqliteExecution::Instance()->insertDb(command);
		delete[]val;
		return res;
	}
	int InsertTrimmedCurve(CurveType type, double begin, double end, std::vector<double>& parameter, bool same, const char* last) {
		//curve 里对应的参数分别是 line  原点坐标，直线方向
		int id = GetID::getTrimmedCurveID();
		char* val = new char[100];
		switch (type)
		{
		case Line:
		{
			std::vector<double> point(parameter.begin(), parameter.begin() + 3);
			std::vector<double> direction(parameter.begin() + 3, parameter.end());
			int id1 = Insert2DB::InsertLine(point, direction);
			sprintf_s(val, 100, "%d,%d,%.3f,%.3f,%s", id, id1, begin, end, same ? "TRUE" : "FALSE");
			std::string command = GetInsertCommand("IfcTrimmedCurve", val);
			SqliteExecution::Instance()->insertDb(command);
			break;
		}
		case Circle:
			//circle的vector里面的参数分别是
		{
			std::vector<double> point(parameter.begin(), parameter.begin() + 3);
			std::vector<double> directionx(parameter.begin() + 3, parameter.begin() + 6);
			std::vector<double> directionz(parameter.begin() + 6, parameter.end());
			int id1 = Insert2DB::InsertCircle(point, directionx, directionz, parameter.back());
			sprintf_s(val, 100, "%d,%d,%.2f,%.2f,%s", id, id1, begin, end, same ? "TRUE" : "FALSE");
			std::string command = GetInsertCommand("IfcTrimmedCurve", val);
			SqliteExecution::Instance()->insertDb(command);
			break;
		}

		default:
			break;
		}
		delete[]val;
		return id;
	}
	int InsertCompositeCurve(std::vector<int> Trimmedcurve) {
		char* val = new char[100];
		int curID = GetID::getCompositeCurveID();
		std::string data;
		for (auto i : Trimmedcurve) {
			if (i == -1) {
				break;
			}

			data += std::to_string(i);
			data.push_back(' ');
		}
		sprintf_s(val,100, "insert into IfcCompositeCurve values(%d,'%s');", curID, data.data());
		SqliteExecution::Instance()->insertDb(val);
		delete[]val;
		return curID;
	}
	int InsertSweptDiskSlod(TrimmedCurveType type, std::vector<double> curve, double diameter) {//根据曲线形状插入不同的SweptDiskSolid
		std::vector<double> rec;
		for (auto i : curve) {
			rec.push_back(i);
		}
		int resid = -1;
		switch (type)
		{
		case LongitudinalBarCurve:
		{//5个参数 分别代表着左弯钩长度，左弯钩直径，长度，右弯钩直径，右弯钩长度
			char res[50];
			sprintf_s(res,50, "%.2f %.2f %.2f %.2f %.2f %d", curve[0], curve[1], curve[2], curve[3], curve[4], (int)diameter);
			std::string rec(res);
			if (longnitudal.count(rec)) {
				return longnitudal[rec];
			}
			resid = GetID::getSweptDiskSolidID();
			int pos = 0;

			std::vector<int> id(5, -1);
			for (int i = 0; i < 5; i++) {
				id[i] = -1;//存储5段curve的id
			}
			if (curve[0] != 0) {
				std::vector<double> point{ -4 * diameter,-4 * diameter - curve[0],0,0,1,0 };
				id[0] = InsertTrimmedCurve(CurveType::Line, 0, curve[0], point, true, 0);
			}
			if (curve[1] != 0) {
				std::vector<double> point{ 0,-4* diameter,0,0,0,-1,-1,0,0,double(diameter) * 4};
				id[1] = InsertTrimmedCurve(CurveType::Circle, 0, 1.571, point, true, 0);
			}
			if (curve[2] != 0) {
				std::vector<double> point{ 0,0,0,1,0,0 };
				id[2] = InsertTrimmedCurve(CurveType::Line, 0, curve[2], point, true, 0);
			}
			if (curve[3] != 0) {
				std::vector<double> point{ curve[2],-4 * diameter,0,0,0,1,1,0,0,double(diameter) * 4 };
				id[3] = InsertTrimmedCurve(CurveType::Line, 1.57, 0, point, false, 0);
			}
			if (curve[4] != 0) {
				std::vector<double> point{ curve[2] + 4 * diameter,-4* diameter,0,0,-1,0 };
				id[4] = InsertTrimmedCurve(CurveType::Line, 0, curve[4], point, true, 0);
			}
			int comid = InsertCompositeCurve(id);
			char* val = new char[150];

			sprintf_s(val, 150, "%d,%d,%.3f,%.3f,%.3f,%.3f", resid, comid, diameter, -1.0, -1.0, -1.0);
			std::string command = GetInsertCommand("IfcSweptDiskSolid", val);
			SqliteExecution::Instance()->insertDb(command);
			delete[]val;
			longnitudal[rec] = resid;
			break;
		}
		case TiedBarCurve:
			break;
		default:
			break;
		}
		return resid;
	}
	int InsertMappedItem(TrimmedCurveType type, std::vector<double> curve, double diameter, std::vector<double>& point) {
		int id = GetID::GetMappedItemID();
		int pointID = InsertPoint3D(point);
		int sweptDiskID = InsertSweptDiskSlod(type, curve, diameter);
		char command[150];
		sprintf_s(command,50, "insert into IfcMappedItem values(%d,%d,'%d',%d);", id, pointID, sweptDiskID, int(type));
		SqliteExecution::Instance()->insertDb(command);
		return id;
	}
	int InsertReinforcingBar(TrimmedCurveType type, std::vector<double> &curve, double diameter, std::vector<std::vector<double>>point, int parentLocalID, std::vector<double>& origin, std::vector<double>& dz, std::vector<double>& dx,int ParentStoreyID)
	//对应插入钢筋的所有参数，除此之外还要记录钢筋的localPlacement，也就是相当于梁的坐标系位置emmm，localplacement是需要大代价弄的
	{
		int barid = GetID::GetReinforcingBarID();
		std::vector<int>mappedid;
		for (auto& i : point) {
			mappedid.push_back(InsertMappedItem(type, curve, diameter, i));
		}
		int localplacementid = InsertLocalPlacement(parentLocalID, origin, dz, dx);
		std::string mappids;
		for (auto i : mappedid) {
			mappids += std::to_string(i);
			mappids.push_back(' ');
		}
		switch (type)
		{
		case LongitudinalBarCurve: {
			char command[100];
			sprintf_s(command,100, "insert into IfcReinforcingBar values(%d,%d,'%s','%s','%s',%d,'%s','%s',%d);", barid, -1, "Main", "bar", "grider", localplacementid, mappids.data(),"C30",ParentStoreyID);
			SqliteExecution::Instance()->insertDb(command);
			break;
		}
			
		case TiedBarCurve:
			break;
		default:
			break;
		}
		return barid;
	}
	int InsertLocalPlacement(int parentLocalID, std::vector<double>& point, std::vector<double>& dz, std::vector<double>& dx) {
		int placementid = InsertPlacement3D(point, dz, dx);
		char command[150];
		int id = GetID::GetLocalPlacementID();
		sprintf_s(command,50, "insert into IfcLocalPlacement values(%d,%d,%d);", id, parentLocalID, placementid);
		SqliteExecution::Instance()->insertDb(command);
		return id;
	}
	int InsertBuilding(int id_, const char* globalID, int ownerID, const char* name, const char* description, int objectType, std::vector<double>& origin, std::vector<double>& dz, std::vector<double>& dx) {
		int id = GetID::InsertBuildingID();//获取buildingID
		if (GetID::LocalPlacementID == 0)//还没有全局坐标系,新建一个全局坐标系
		{
			std::vector<double>origin = { 0,0,0 }, dz = { 0,0,1 }, dx = { 1,0,0 };
			int globalLocalPlacementID = InsertLocalPlacement(-1, origin, dz, dx);
		}
		int buildingPlacementID = InsertLocalPlacement(1, origin, dz, dx);
		GetID::BuildingLocalPlacementID.push_back(buildingPlacementID);//相对于全局坐标系新建一个基于建筑物的局部坐标系。
		char command[100];
		sprintf_s(command, 100, "insert into IfcBuilding values(%d,%d,'%s','%s',%d,%d);", id, ownerID, name, description, objectType, buildingPlacementID);
		SqliteExecution::Instance()->insertDb(command);
		return id;
	}
	int InsertBuildingStory(int id_, const char* globalID, int ownerID, const char* name, const char* description, int objectType, std::vector<double>& origin, std::vector<double>& dz, std::vector<double>& dx, int parentLocalPlacementID) {
		int id = GetID::InsertFloorID();
		int curLocalPlacementID = InsertLocalPlacement(GetID::BuildingLocalPlacementID.back(), origin, dz, dx);
		GetID::floorLocalPlacementID.push_back(curLocalPlacementID);	
		char command[100];
		sprintf_s(command, 100, "insert into IfcBuildingStory values(%d,%d,'%s','%s',%d,%d,%d);", id, ownerID, name, description, objectType, curLocalPlacementID,origin[2]);
		SqliteExecution::Instance()->insertDb(command);
		return id;
	}
}


