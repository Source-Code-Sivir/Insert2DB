#include"insertIfc.h"
#include"BarInfo.h"
#include"GetModelInfo.h"
using namespace Insert2DB;
using namespace std;
/*
<!--

					   _ooOoo_
					  o8888888o
					  88" . "88
					  (| -_- |)
					  O\  =  /O
				   ____/`---'\____
				 .'  \\|     |//  `.
				/  \\|||  :  |||//  \
			   /  _||||| -:- |||||-  \
			   |   | \\\  -  /// |   |
			   | \_|  ''\-/''  |   |
			   \  .-\__  `-`  ___/-. /
			 ___`. .'  /-.-\  `. . __
		  ."" '<  `.___\_<|>_/___.'  >'"".
		 | | :  `- \`.;`\ _ /`;.`/ - ` : | |
		 \  \ `-.   \_ __\ /__ _/   .-` /  /
	======`-.____`-.___\_____/___.-`____.-'======
					   `=-='

-->电子佛保佑代码跑的动！*/
int main() {
	SqliteExecution::Instance()->Init("D:\\lib\\sqlite\\model.db");
	getSection();
	getPoint();
	getBeam();
	getBar();
	getSpan();
	SqliteExecution::Instance()->closeDb();


	SqliteExecution::Instance()->Init("IfcDb.db");
	SqliteExecution::Instance()->eraseAllTable();
	SqliteExecution::Instance()->insertDb("insert into IfcDirection values(1,1,0,0),\
(2,-1,0,0),(3,0,1,0),(4,0,-1,0),(5,0,0,1),(6,0,0,-1),(7,0.7071,0.7071,0),(8,-0.7071,0.7071,0),\
(9,-0.7071,-0.7071,0),(10,0.7071,-0.7071,0);");
	SqliteExecution::Instance()->insertDb("insert into IfcPoint values(1,0,0,0);");
	SqliteExecution::Instance()->insertDb("insert into IfcPlacement3D values(1,1,5,1);");

	vector<double> dz = { 0,0,1 }, dx = { 1,0,0 }, origin = { 0,0,0 };
	InsertBuilding(1, nullptr, 1, nullptr, nullptr, 1, origin, dz, dx);
	InsertBuildingStory(1, nullptr, 1, nullptr, nullptr, 1, origin, dz, dx, GetID::localPlacementIDStack.back());
	
	for (auto& i : getModelInfo::beams) {
		i.second.CalculateBeam();
	}
	
	
	//std::vector<double> longcurve = { 375,100,2000,0,0 }, shearcurve{ 400,700,40 }, tiedcurve{ 40,15,400 };
	//std::vector<std::vector<double>> shearps = { {0,0,100},{0,0,300} }, longps = { {0,400,200},{0,400,-200} };
	//vector<double> dz = { 0,0,1 }, dx = { 1,0,0 }, origin = { 0,0,0 };
	////vector<double> beamorigin = { 0,0,0 };
	//InsertBuilding(1, nullptr, 1, nullptr, nullptr, 1, origin, dz, dx);
	//vector<double> storey{ 0,0,0 };
	//vector<double> bardz{ -1,0,0 }, bardx{ 0,0,1 }, beamdz{ 0,1,0 }, beamdx{ -1,0,0 }, beamexrtude{ 0,0,1 }, beamorigin{ 100,500,1000 };
	//InsertBuildingStory(1, nullptr, 1, nullptr, nullptr, 1, storey, dz, dx, GetID::localPlacementIDStack.back());
	//InsertBeam(1, beamorigin, beamdz, beamdx, ShapeType::Rectangular, "600 900", beamexrtude, 2000);
	////InsertReinforcingBar(BarType::SheadLinks, longcurve, 10, ps, origin, bardz, bardx, GetID::FloorID);
	//vector<double> shearbardz{ 0,0 ,1}, shearbardx{ 1,0,0 };
	//InsertReinforcingBar(BarType::LongitudinalBarCurve, longcurve, 25, longps,origin, bardz, bardx,GetID::FloorID);
	////InsertReinforcingBar(BarType::SheadLinks, shearcurve, 10, shearps, origin, shearbardz, shearbardx, GetID::FloorID);
	////InsertReinforcingBar(BarType::TiedBarCurve, tiedcurve, 10, longps, origin, shearbardz, shearbardx, GetID::FloorID);
	return 0;
}