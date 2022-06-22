#include"insertIfc.h"
#include"BarInfo.h"
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



	Component_Beam test;
	test.storey = 1;
	
	test.len = 22150;
	test.begin = { 0,0,0 };
	//test.end = { 0,22150,0 };
	test.directionz = { 1,0,0 };
	test.directionx = { 0,1,0 };
	test.height = 850;
	test.width = 300;
	Rectangular_Shape section;
	section.shape_type = ShapeType::Rectangular;
	section.wide = 300;
	section.height = 850;
	section.parameter = "300 850";
	test.section = &section;
	test.concrete_type = ConcreteType::C30;
	//test.extru
	SpanInfo leftspan;
	leftspan.span_type = SpanType::LeftSide;
	leftspan.span_bar_info.TopLeft.resize(3);
	leftspan.span_bar_info.TopLeft[0].diameter = 25;
	leftspan.span_bar_info.TopLeft[0].numofRebar = 2;
	leftspan.span_bar_info.TopLeft[1].diameter = 25;
	leftspan.span_bar_info.TopLeft[1].numofRebar = 2;
	leftspan.span_bar_info.TopLeft[2].diameter = 25;
	leftspan.span_bar_info.TopLeft[2].numofRebar = 2;

	leftspan.span_bar_info.BotLeft.resize(2);
	leftspan.span_bar_info.BotLeft[0].diameter = 25;
	leftspan.span_bar_info.BotLeft[0].numofRebar = 2;
	leftspan.span_bar_info.BotLeft[1].diameter = 25;
	leftspan.span_bar_info.BotLeft[1].numofRebar = 2;

	leftspan.span_bar_info.Side.diameter = 12;
	leftspan.span_bar_info.Side.numofRebar = 6;

	leftspan.span_bar_info.TopRight.resize(3);
	leftspan.span_bar_info.TopRight[0].numofRebar = 2;
	leftspan.span_bar_info.TopRight[0].diameter = 25;
	leftspan.span_bar_info.TopRight[1].numofRebar = 1;
	leftspan.span_bar_info.TopRight[1].diameter = 25;
	leftspan.span_bar_info.TopRight[2].numofRebar = 2;
	leftspan.span_bar_info.TopRight[2].diameter = 25;

	leftspan.span_bar_info.ShearLinks.LeftZoneInfo.Diameter = 8;
	leftspan.span_bar_info.ShearLinks.LeftZoneInfo.spacing = 100;
	leftspan.span_bar_info.ShearLinks.NormalZoneInfo.Diameter = 8;
	leftspan.span_bar_info.ShearLinks.NormalZoneInfo.spacing = 150;
	leftspan.span_bar_info.ShearLinks.RightZoneInfo.Diameter = 8;
	leftspan.span_bar_info.ShearLinks.RightZoneInfo.spacing = 100;
	
	leftspan.span_bar_info.Tied.diameter = 6;

	SpanInfo midspan;
	midspan.span_type = SpanType::Internal;
	midspan.span_bar_info.BotLeft.resize(2);
	midspan.span_bar_info.BotLeft[0].diameter = 25;
	midspan.span_bar_info.BotLeft[0].numofRebar = 2;
	midspan.span_bar_info.BotLeft[1].diameter = 25;
	midspan.span_bar_info.BotLeft[1].numofRebar = 2;

	midspan.span_bar_info.TopRight = leftspan.span_bar_info.TopRight;
	
	midspan.span_bar_info.ShearLinks = leftspan.span_bar_info.ShearLinks;

	midspan.span_bar_info.Side = leftspan.span_bar_info.Side;

	midspan.span_bar_info.Tied.diameter = 6;

	SpanInfo rightspan;
	rightspan.span_type = SpanType::RightSide;

	rightspan.span_bar_info.TopRight = leftspan.span_bar_info.TopLeft;
	rightspan.span_bar_info.BotLeft = midspan.span_bar_info.BotLeft;
	rightspan.span_bar_info.ShearLinks = leftspan.span_bar_info.ShearLinks;
	rightspan.span_bar_info.Side = leftspan.span_bar_info.Side;
	rightspan.span_bar_info.Tied.diameter = 6;

	test.spans_info.push_back(leftspan);
	test.spans_info.push_back(midspan);
	test.spans_info.push_back(rightspan);

	test.spans_clear_len.push_back(7750);
	test.spans_clear_len.push_back(5350);
	test.spans_clear_len.push_back(7750);

	test.columns_len.push_back(650);
	test.columns_len.push_back(650);
	test.columns_len.push_back(650);
	test.columns_len.push_back(650);

	test.span_begin_point.push_back(0);
	test.span_begin_point.push_back(8400);
	test.span_begin_point.push_back(14400);

	vector<double> dz = { 0,0,1 }, dx = { 1,0,0 }, origin = { 0,0,0 };
	InsertBuilding(1, nullptr, 1, nullptr, nullptr, 1, origin, dz, dx);
	InsertBuildingStory(1, nullptr, 1, nullptr, nullptr, 1, origin, dz, dx, GetID::localPlacementIDStack.back());
	test.CalculateBeam();

	
	
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