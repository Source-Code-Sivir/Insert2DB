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
	SqliteExecution::Instance()->insertDb("insert into IfcPlacement3D values(1,1,3,1);");
	std::vector<double>curve = { 375,100,2000,0,0 };
	std::vector<std::vector<double>> ps = { {0,0,0},{0,500,0} };
	vector<double> dz = { 0,0,1 }, dx = { 1,0,0 }, origin = { 0,0,0 };
	InsertReinforcingBar(TrimmedCurveType::LongitudinalBarCurve, curve, 25, ps, -1,origin, dz, dx);
	return 0;
}