#include"insertIfc.h"
using namespace Insert2DB;
using namespace std;
int main() {
	SqliteExecution::Instance()->Init("IfcDb.db");
	SqliteExecution::Instance()->eraseAllTable();
	SqliteExecution::Instance()->insertDb("insert into IfcDirection values(1,1,0,0),\
(2,-1,0,0),(3,0,1,0),(4,0,-1,0),(5,0,0,1),(6,0,0,-1),(7,0.7071,0.7071,0),(8,-0.7071,0.7071,0),\
(9,-0.7071,-0.7071,0),(10,0.7071,-0.7071,0);");
	SqliteExecution::Instance()->insertDb("insert into IfcPoint values(1,0,0,0);");
	SqliteExecution::Instance()->insertDb("insert into IfcPlacement3D values(1,1,5,1);");
	std::vector<double>curve = { 400,700,40 };
	std::vector<std::vector<double>> ps = { {0,400,200},{0,400,-200} };
	vector<double> dz = { 0,0,1 }, dx = { 1,0,0 }, origin = { 0,0,0 };
	//vector<double> beamorigin = { 0,0,0 };
	InsertBuilding(1, nullptr, 1, nullptr, nullptr, 1, origin, dz, dx);
	vector<double> storey{ 0,0,0 };
	GetID::localPlacementIDStack.push_back(-1);
	vector<double> bardz{ -1,0,0 }, bardx{ 0,0,1 }, beamdz{ 0,1,0 }, beamdx{ -1,0,0 }, beamexrtude{ 0,0,1 }, beamorigin{ 100,500,1000 };
	InsertBuildingStory(1, nullptr, 1, nullptr, nullptr, 1, storey, dz, dx, GetID::localPlacementIDStack.back());
	//InsertBeam(1, beamorigin, beamdz, beamdx, ShapeType::Rectangular, "600 900", beamexrtude, 2000);
	InsertReinforcingBar(BarType::SheadLinks, curve, 10, ps,origin, bardz, bardx,GetID::FloorID);
	return 0;
}