#include"BarInfo.h"
#include"insertIfc.h"
#include<vector>
#include"GetCodePara.h"
using namespace std;
using namespace Insert2DB;

const double sqrt2 = sqrt(2) / 2;
vector<double> origin{ 0,0,0 }, Topdz{ -1,0,0 }, Topdx{ 0,0,1 }, Botdz{ 1,0,0 }, Botdx{ 0,0,1 };
vector<double> sheardz{ 0,0,1 }, sheardx{ 1,0,0 };
vector<double> tieddz{ 0,sqrt(2) / 2,sqrt(2) / 2 }, tieddx{ 1,0,0 };
vector<double> rightdz{ 1,0,0 }, rightdx{ 0,0,-1 }, rightbotdz{ -1,0,0 }, rightbotdx{ 0,0,-1 };

void Component_Beam::HandleRightSide() {//处理右边跨的钢筋
	int a = spans_info.size() - 1;
	SpanBarInfo& bar_info = spans_info[a].span_bar_info;
	int clear_span_len = spans_clear_len[a];
	int shearlinkDiameter = bar_info.ShearLinks.LeftZoneInfo.Diameter;
	//上右跨钢筋有 上右钢筋，下左钢筋

	LongitudinalBarInfo& top_right = bar_info.TopRight;
	Rectangular_Shape* shape = static_cast<Rectangular_Shape*>(section);
	int width = shape->wide, height = shape->height;
	int protect_thick = getProtectThick(environment_type, ComponentType::Beam);
	int curbegin = span_begin_point[a] + clear_span_len;
	//上右角部
	for (int i = 0; i < top_right.size(); i++) {
		BasicBarInfo& curbar_info = top_right[i];
		int LaE = GetLaE(curbar_info.BarType, earthquake_resistence, concrete_type, curbar_info.diameter);
		int labE = Getlabe(concrete_type, curbar_info.BarType, environment_type, curbar_info.diameter);
		double diameter = curbar_info.diameter;
		switch (i)
		{
		case 0: {
			vector<vector<double>> insert_point(2, vector<double>(3));
			insert_point[0][0] = -(curbegin + 0.4 * labE);
			insert_point[0][1] = 0.5 * height - protect_thick - shearlinkDiameter - 0.5 * curbar_info.diameter;
			insert_point[0][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15;

			insert_point[1][0] = insert_point[0][0];
			insert_point[1][1] = insert_point[0][1];
			insert_point[1][2] = -insert_point[0][2];
		
			vector<double> curve{ 15 * diameter,4 * diameter / 2, 0.4 * labE + clear_span_len-max(spans_clear_len[a],spans_clear_len[a-1])/3, 0, 0 };
			
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, rightdz, rightdx, storey);
			break;
		}
		case 1: {//第一排中部钢筋
			int barnum = curbar_info.numofRebar;
			double bar_span = (width - 2 * protect_thick - 2 * shearlinkDiameter - 45) / (barnum + 1);
			vector<vector<double>> insert_point(barnum, vector<double>(3));
			for (int i = 0; i < barnum; i++) {

				insert_point[i][0] = -(curbegin + 0.4 * labE);
				insert_point[i][1] = 0.5 * height - protect_thick - shearlinkDiameter - 0.5 * curbar_info.diameter;
				insert_point[i][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15 - (i + 1) * bar_span;
			}
			vector<double> curve{ 15 * diameter,4 * diameter / 2, 0.4 * labE + clear_span_len / 3,  0, 0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, rightdz, rightdx, storey);
		}
		case 2: {//第二排角部钢筋
			int d = max(top_right[0].diameter, 25);
			vector<vector<double>> insert_point(2, vector<double>(3));
			insert_point[0][0] =-(curbegin + 0.4 * labE-30);
			insert_point[0][1] = 0.5 * height - protect_thick - shearlinkDiameter - 2* d;
			insert_point[0][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15;

			insert_point[1][0] = insert_point[0][0];
			insert_point[1][1] = insert_point[0][1];
			insert_point[1][2] = -insert_point[0][2];

			vector<double> curve{ 15 * diameter,4 * diameter / 2, 0.4 * labE + 0.25 * clear_span_len ,  0, 0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, rightdz, rightdx, storey);//默认是一层
			break;
		}
		case 3: {//第二排中部钢筋
			int d = max(top_right[0].diameter, 25);
			int barnum = curbar_info.numofRebar;
			double bar_span = (width - 2 * protect_thick - 2 * shearlinkDiameter - 45) / (barnum + 1);
			vector<vector<double>> insert_point(barnum, vector<double>(3));
			for (int i = 0; i < barnum; i++) {
				insert_point[i][0] = -(curbegin + 0.4 * labE-30);
				insert_point[i][1] = 0.5 * height - protect_thick - shearlinkDiameter - 2 * d;
				insert_point[i][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15 - (i + 1) * bar_span;
			}
			vector<double> curve{ 15 * diameter,4 * diameter / 2, 0.4 * labE + clear_span_len / 4,  0, 0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, rightdz, rightdx, storey);
		}
		default:
			break;
		}
	}
	//处理下左
	LongitudinalBarInfo& bot_right = bar_info.BotLeft;
	for (int i = 0; i < bot_right.size(); i++) {
		BasicBarInfo& curbar_info = bot_right[i];
		int LaE = GetLaE(curbar_info.BarType, earthquake_resistence, concrete_type, curbar_info.diameter);
		int labE = Getlabe(concrete_type, curbar_info.BarType, environment_type, curbar_info.diameter);
		if (curbar_info.diameter == 0) {
			break;
		}
		
		switch (i)
		{
		case 0: {//第一排角部钢筋  //负筋在yz平面内 x为延伸长度  //暂时只支持矩形平面
			double diameter = curbar_info.diameter;
			int tmpmax = max(double(LaE), 0.5 * columns_len[a] + 5 * diameter);
			vector<vector<double>> insert_point(2, vector<double>(3));
			insert_point[0][0] = -(curbegin + 0.4 * labE);
			insert_point[0][1] = 0.5 * height - protect_thick - shearlinkDiameter -0.5*diameter;
			insert_point[0][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15;

			insert_point[1][0] = insert_point[0][0];
			insert_point[1][1] = insert_point[0][1];
			insert_point[1][2] = -insert_point[0][2];
			
			vector<double> curve{ 15 * diameter,4 * diameter / 2, clear_span_len + tmpmax+0.4*LaE,0,0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, rightbotdz, rightbotdx, storey);
			break;
		}
		case 1: {//第一排中部钢筋
			int barnum = curbar_info.numofRebar;
			double diameter = curbar_info.diameter;
			double bar_span = (width - 2 * protect_thick - 2 * shearlinkDiameter - 40) / (barnum + 1);
			int tmpmax = max(double(LaE), 0.5 * columns_len[a] + 5 * diameter);
			vector<vector<double>> insert_point(barnum, vector<double>(3));
			for (int i = 0; i < barnum; i++) {
				insert_point[i][0] = -(curbegin + 0.4 * labE);
				insert_point[i][1] = 0.5 * height - protect_thick - shearlinkDiameter - 0.5 * curbar_info.diameter;
				insert_point[i][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15 - (i + 1) * bar_span;

			}
			vector<double> curve{ 15 * diameter,4 * diameter / 2, clear_span_len + tmpmax + 0.4 * LaE,0,0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, rightbotdz, rightbotdx, storey);
			break;
		}
		case 2: {//第二排角部钢筋
			int d = max(25, top_right[0].diameter);
			double diameter = curbar_info.diameter;
			vector<vector<double>> insert_point(2, vector<double>(3));
			int tmpmax = max(double(LaE), 0.5 * columns_len[a] + 5 * diameter);

			insert_point[0][0] = -(curbegin + 0.4 * labE-40);
			insert_point[0][1] = 0.5 * height - protect_thick - shearlinkDiameter - 2*d;
			insert_point[0][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15;

			insert_point[1][0] = insert_point[0][0];
			insert_point[1][1] = insert_point[0][1];
			insert_point[1][2] = -insert_point[0][2];
			vector<double> curve{ 15 * diameter,4 * diameter / 2, clear_span_len + tmpmax + 0.4 * LaE,0,0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, rightbotdz, rightbotdx, storey);
			break;
		}
		case 3: {//第二排中部钢筋
			int barnum = curbar_info.numofRebar;
			int d = max(25, top_right[0].diameter);

			double diameter = curbar_info.diameter;
			int tmpmax = max(double(LaE), 0.5 * columns_len[a] + 5 * diameter);
			double bar_span = (width - 2 * protect_thick - 2 * shearlinkDiameter - 40) / (barnum + 1);
			vector<vector<double>> insert_point(barnum, vector<double>(3));
			for (int i = 0; i < barnum; i++) {
				insert_point[i][0] = -(curbegin + 0.4 * labE-40);
				insert_point[i][1] = 0.5 * height - protect_thick - shearlinkDiameter - 0.5 * curbar_info.diameter - 2 * d;
				insert_point[i][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15 - (i + 1) * bar_span;

			}
			vector<double> curve{ 15 * diameter,4 * diameter / 2, clear_span_len + tmpmax + 0.4 * LaE,0,0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, rightbotdz, rightbotdx, storey);
		}
		default:
			break;
		}
	}
	//处理下左部钢筋
	
}

void Component_Beam::HandleLeftSide() {//处理左边跨的钢筋
	SpanBarInfo& bar_info = spans_info[0].span_bar_info;
	int clear_span_len = spans_clear_len[0];
	int shearlinkDiameter = bar_info.ShearLinks.LeftZoneInfo.Diameter;

	int ln = max(spans_clear_len[0], spans_clear_len[1]);
	LongitudinalBarInfo& top_left = bar_info.TopLeft;
	Rectangular_Shape* shape = static_cast<Rectangular_Shape*>(section);
	int protect_thick = getProtectThick(environment_type, ComponentType::Beam);
	//上左角部
	for (int i = 0; i < top_left.size(); i++) {
		BasicBarInfo& curbar_info = top_left[i];
		int LaE = GetLaE(curbar_info.BarType, earthquake_resistence,concrete_type, curbar_info.diameter);
		int labE = Getlabe(concrete_type, curbar_info.BarType, environment_type, curbar_info.diameter);
		double diameter = curbar_info.diameter;
		switch (i)
		{
		case 0: {//第一排角部钢筋//负筋在yz平面内 x为延伸长度 不懂 //暂时只支持矩形平面
			vector<vector<double>> insert_point{ {-0.4 * labE,0.5 * height - protect_thick - shearlinkDiameter - 0.5 * curbar_info.diameter,0.5 * width - protect_thick - shearlinkDiameter - 15},{-0.4 * labE,0.5 * height - protect_thick - shearlinkDiameter - 0.5 * curbar_info.diameter,-(0.5 * width - protect_thick - shearlinkDiameter - 15)} };
			vector<double> curve{ 15 * diameter,4 * diameter / 2, 0.4 * labE + 2 * clear_span_len / 3,  0, 0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, Topdz, Topdx, storey);//默认是一层
			break;
		}
		case 1: {//第一排中部钢筋
			int barnum = curbar_info.numofRebar;
			double bar_span = (width - 2 * protect_thick - 2 * shearlinkDiameter - 45) / (barnum + 1);
			vector<vector<double>> insert_point(barnum, vector<double>(3));
			for (int i = 0; i < barnum; i++) {
				insert_point[i][0] = -0.4 * labE;
				insert_point[i][1] = 0.5 * height - protect_thick - shearlinkDiameter - 0.5 * curbar_info.diameter;
				insert_point[i][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15 - (i + 1) * bar_span;
			}
			vector<double> curve{ 15 * diameter,4 * diameter / 2, 0.4 * labE + clear_span_len / 3,  0, 0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, Topdz, Topdx, storey);
		}
		case 2: {//第二排角部钢筋
			int d = max(top_left[0].diameter, 25);
			vector<vector<double>> insert_point{ {-0.4 * labE+40,
				0.5 * height- 2*d- protect_thick - shearlinkDiameter,
				0.5 * width - protect_thick - shearlinkDiameter - 15},
				{-0.4 * labE+40,
				0.5 * height - protect_thick - shearlinkDiameter -2*d,
				-(0.5 * width - protect_thick - shearlinkDiameter - 15)} };
			vector<double> curve{ 15 * diameter,4 * diameter / 2, 0.4 * labE + 0.25 * clear_span_len ,  0, 0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, Topdz, Topdx, storey);//默认是一层
			break;
		}
		case 3: {//第二排中部钢筋
			int d = max(top_left[0].diameter, 25);
			int barnum = curbar_info.numofRebar;
			double bar_span = (width - 2 * protect_thick - 2 * shearlinkDiameter - 45) / (barnum + 1);
			vector<vector<double>> insert_point(barnum, vector<double>(3));
			for (int i = 0; i < barnum; i++) {
				insert_point[i][0] = -0.4 * labE+40;
				insert_point[i][1] = 0.5 * height - protect_thick - shearlinkDiameter-2*d;
				insert_point[i][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15 - (i + 1) * bar_span;
			}
			vector<double> curve{ 15 * diameter,4 * diameter / 2, 0.4 * labE + clear_span_len / 4,  0, 0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, Topdz, Topdx, storey);
		}
		default:
			break;
		}
	}
	//上中没有 处理上右 
	LongitudinalBarInfo& top_right = bar_info.TopRight;
	for (int i = 0; i < top_right.size(); i++) {
		BasicBarInfo& curbar_info = top_right[i];
		int LaE = GetLaE(curbar_info.BarType, earthquake_resistence, concrete_type, curbar_info.diameter);
		int labE = Getlabe(concrete_type, curbar_info.BarType, environment_type, curbar_info.diameter);
		
		if (curbar_info.diameter == 0) {
			break;
		}
		switch (i)
		{
		case 0: {//第一排角部钢筋  //负筋在yz平面内 x为延伸长度  //暂时只支持矩形平面
			double diameter = curbar_info.diameter;
			vector<vector<double>> insert_point(2, vector<double>(3));
			insert_point[0][0] = 2 * spans_clear_len[0] / 3;
			insert_point[0][1] = 0.5 * height - protect_thick - shearlinkDiameter - 0.5 * curbar_info.diameter;
			insert_point[0][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15;
			insert_point[1][0] = insert_point[0][0];
			insert_point[1][1] = insert_point[0][1];
			insert_point[1][2] = -insert_point[0][2];
			
			//{ {,,},{-0.4 * labE,0.5 * height - protect_thick - shearlinkDiameter - 0.5 * curbar_info.diameter,-(0.5 * width - protect_thick - shearlinkDiameter - 15)} };
			vector<double> curve{ 0,0, spans_clear_len[0]/3+spans_clear_len[1]*2/ 3 + columns_len[1],0,0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, Topdz, Topdx, storey);
			break;
		}
		case 1: {//第一排中部钢筋
			int barnum = curbar_info.numofRebar;
			double diameter = curbar_info.diameter;
			double bar_span = (width - 2 * protect_thick - 2 * shearlinkDiameter - 40) / (barnum + 1);
			
			vector<vector<double>> insert_point(barnum, vector<double>(3));
			for (int i = 0; i < barnum; i++) {
				insert_point[i][0] = spans_clear_len[0] -ln/3;
				insert_point[i][1] = 0.5 * height - protect_thick - shearlinkDiameter - 0.5 * curbar_info.diameter;
				insert_point[i][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15 - (i + 1) * bar_span;

			}
			vector<double> curve{ 0,0,0.66667 *ln  + columns_len[1],0,0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, Topdz, Topdx, storey);
		}
		case 2: {//第二排角部钢筋
			int d = max(25, top_right[0].diameter);
			double diameter = curbar_info.diameter;
			vector<vector<double>> insert_point(2, vector<double>(3));
			insert_point[0][0] =  spans_clear_len[0] -ln/4;
			insert_point[0][1] = 0.5 * height - protect_thick - shearlinkDiameter - 2 * d;
			insert_point[0][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15;
			insert_point[1][0] = insert_point[0][0];
			insert_point[1][1] = insert_point[0][1];
			insert_point[1][2] = -insert_point[0][2];
			
			vector<double> curve{ 0,0,0.5* ln + columns_len[1],0,0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, Topdz, Topdx, storey);
			break;
		}
		case 3: {//第二排中部钢筋
			int barnum = curbar_info.numofRebar;
			int d = max(25, top_right[0].diameter);
			double diameter = curbar_info.diameter;
			double bar_span = (width - 2 * protect_thick - 2 * shearlinkDiameter - 40) / (barnum + 1);
			vector<vector<double>> insert_point(barnum, vector<double>(3));
			for (int i = 0; i < barnum; i++) {
				insert_point[i][0] = spans_clear_len[0] - ln / 3;
				insert_point[i][1] = 0.5 * height - protect_thick - shearlinkDiameter - 0.5 * curbar_info.diameter-2*d;
				insert_point[i][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15 - (i + 1) * bar_span;

			}
			vector<double> curve{ 0,0,0.5* ln + columns_len[1],0,0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, Topdz, Topdx, storey);
		}
		default:
			break;
		}
	}
	//处理下左部钢筋
	LongitudinalBarInfo& botleft = bar_info.BotLeft;
	for (int i = 0; i < botleft.size(); i++) {
		BasicBarInfo& curbar_info = botleft[i];
		int LaE = GetLaE(curbar_info.BarType, earthquake_resistence, concrete_type, curbar_info.diameter);
		int labE = Getlabe(concrete_type, curbar_info.BarType, environment_type, curbar_info.diameter);
		double diameter = curbar_info.diameter;
		double anchor = max(double(LaE), 0.5 * columns_len[i + 1] + 5 * diameter);
		switch (i)
		{
		case 0: {//第一排角部钢筋//负筋在yz平面内 x为延伸长度 不懂 //暂时只支持矩形平面
			vector<vector<double>> insert_point{ {-0.4 * labE,0.5 * height - protect_thick - shearlinkDiameter - 0.5 * curbar_info.diameter,0.5 * width - protect_thick - shearlinkDiameter - 15},{-0.4 * labE,0.5 * height - protect_thick - shearlinkDiameter - 0.5 * curbar_info.diameter,-(0.5 * width - protect_thick - shearlinkDiameter - 15)} };
			vector<double> curve{ 15 * diameter,4 * diameter / 2, 0.4 * labE + clear_span_len +anchor,  0, 0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, Botdz, Botdx, storey);//默认是一层
			break;
		}
		case 1: {//第一排中部钢筋
			int barnum = curbar_info.numofRebar;
			double bar_span = (width - 2 * protect_thick - 2 * shearlinkDiameter - 45) / (barnum + 1);
			vector<vector<double>> insert_point(barnum, vector<double>(3));
			for (int i = 0; i < barnum; i++) {
				insert_point[i][0] = -0.4 * labE;
				insert_point[i][1] = 0.5 * height - protect_thick - shearlinkDiameter - 0.5 * curbar_info.diameter;
				insert_point[i][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15 - (i + 1) * bar_span;
			}
			vector<double> curve{ 15 * diameter,4 * diameter / 2, 0.4 * labE + clear_span_len + anchor,  0, 0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, Botdz, Botdx, storey);
		}
		case 2: {//第二排角部钢筋
			int d = max(botleft[0].diameter, 25);
			vector<vector<double>> insert_point{ {-0.4 * labE+40,
				0.5 * height - 2 * d - protect_thick - shearlinkDiameter,
				0.5 * width - protect_thick - shearlinkDiameter - 15},
				{-0.4 * labE+40,
				0.5 * height - protect_thick - shearlinkDiameter - 2 * d,
				-(0.5 * width - protect_thick - shearlinkDiameter - 15)} };
			vector<double> curve{ 15 * diameter,4 * diameter / 2, 0.4 * labE + clear_span_len + anchor ,  0, 0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, Botdz, Botdx, storey);//默认是一层
			break;
		}
		case 3: {//第二排中部钢筋
			int d = max(botleft[0].diameter, 25);
			int barnum = curbar_info.numofRebar;
			double bar_span = (width - 2 * protect_thick - 2 * shearlinkDiameter - 45) / (barnum + 1);
			vector<vector<double>> insert_point(barnum, vector<double>(3));
			for (int i = 0; i < barnum; i++) {
				insert_point[i][0] = -0.4 * labE+40;
				insert_point[i][1] = 0.5 * height - protect_thick - shearlinkDiameter  - 2 * d;
				insert_point[i][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15 - (i + 1) * bar_span;
			}
			vector<double> curve{ 15 * diameter,4 * diameter / 2,0.4 * labE + clear_span_len + anchor,  0, 0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, Botdz, Botdx, storey);
		}
		default:
			break;
		}
	}
}

void Component_Beam::HandleMid(int spamNo) {
	SpanBarInfo& cur_span_barinfo = spans_info[spamNo].span_bar_info;
	//对于中间跨钢筋，只有上右钢筋以及下左钢筋
	int ln = max(spans_clear_len[spamNo], spans_clear_len[spamNo + 1]);
	//处理上右
	int protect_thick = getProtectThick(environment_type, ComponentType::Beam);
	LongitudinalBarInfo& topright = cur_span_barinfo.TopRight;
	int shearlinkDiameter = cur_span_barinfo.ShearLinks.LeftZoneInfo.Diameter;
	for (int pos = 0; pos < topright.size(); pos++) {
		switch (pos)
		{
		case 0://第一排角部
		{
			vector<double>curve{ 0,0,spans_clear_len[spamNo] / 3 + spans_clear_len[spamNo + 1] * 2 / 3 + columns_len[spamNo + 1],0,0 };
			vector<vector<double>> insert_points(2,vector<double>(3));
			insert_points[0][0] = span_begin_point[spamNo] + 0.66667 * spans_clear_len[spamNo];
			insert_points[0][1] = 0.5 * height - protect_thick - shearlinkDiameter - 0.5 * topright[0].diameter;
			insert_points[0][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15;
			insert_points[1][0] = span_begin_point[spamNo] + 0.66667 * spans_clear_len[spamNo];
			insert_points[1][1] = 0.5 * height - protect_thick - shearlinkDiameter - 0.5 * topright[0].diameter;
			insert_points[1][2] = -(0.5 * width - protect_thick - shearlinkDiameter - 15);

			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, topright[0].diameter, insert_points, origin, Topdz, Topdx, storey);
		}
		case 1: {//第一排中部
			int diameter = topright[1].diameter;
			int barnum = topright[1].numofRebar;
			double bar_span = (width - 2 * protect_thick - 2 * shearlinkDiameter - 45) / (barnum + 1);
			vector<vector<double>> insert_point(barnum, vector<double>(3));
			for (int i = 0; i < barnum; i++) {
				insert_point[i][0] = span_begin_point[spamNo] + spans_clear_len[spamNo] -0.3333*ln;
				insert_point[i][1] = 0.5 * height - protect_thick - shearlinkDiameter - 0.5 * topright[0].diameter;
				insert_point[i][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15 - (i + 1) * bar_span;
			}
			vector<double> curve{0,0, ln*0.6666667+columns_len[spamNo + 1],  0, 0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, Topdz, Topdx, storey);
		}
		case 2: {//第二排角部钢筋
			int diameter = topright[2].diameter;
			int d = max(topright[0].diameter, 25);
			vector<vector<double>> insert_points(2, vector<double>(3));
			insert_points[0][0] = span_begin_point[spamNo] + spans_clear_len[spamNo] - 0.25 * ln;
			insert_points[0][1] = 0.5 * height - protect_thick - shearlinkDiameter -2*d;
			insert_points[0][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15;
			insert_points[1][0] = insert_points[0][0];
			insert_points[1][1] = 0.5 * height - protect_thick - shearlinkDiameter -2*d;
			insert_points[1][2] = -(0.5 * width - protect_thick - shearlinkDiameter - 15);
			vector<double> curve{ 0,0, 0.5*ln+columns_len[spamNo +1] ,  0, 0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_points, origin, Topdz, Topdx, storey);//默认是一层
			break;
		}
		case 3: {//第二排中部钢筋
			int d = max(topright[0].diameter, 25);
			int barnum = topright[3].numofRebar;
			double diameter = topright[3].diameter;
			double bar_span = (width - 2 * protect_thick - 2 * shearlinkDiameter - 45) / (barnum + 1);
			vector<vector<double>> insert_point(barnum, vector<double>(3));
			for (int i = 0; i < barnum; i++) {
				insert_point[i][0] = span_begin_point[spamNo] + spans_clear_len[spamNo] - 0.25 * ln;
				insert_point[i][1] = 0.5 * height - protect_thick - shearlinkDiameter - 2 * d;
				insert_point[i][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15 - (i + 1) * bar_span;
			}
			vector<double> curve{ 0,0, 0.5 * ln + columns_len[spamNo + 1],  0, 0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, Topdz, Topdx, storey);
		}
		default:
			break;
		}
	}
	///处理下左

	LongitudinalBarInfo& botLeft = cur_span_barinfo.BotLeft;
	for (int pos = 0; pos < botLeft.size(); pos++) {
		double diameter = botLeft[pos].diameter;
		int labE = Getlabe(concrete_type, botLeft[pos].BarType, environment_type, diameter);
		int laE = GetLaE(botLeft[pos].BarType, earthquake_resistence, concrete_type, diameter);
		int anchor = max(double(laE), 0.5 * columns_len[spamNo+ 1] + 5 * diameter);
		switch (pos)
		{
		case 0: {//第一排角部钢筋//负筋在yz平面内 x为延伸长度 不懂 //暂时只支持矩形平面
			vector<vector<double>> insert_point(2, vector<double>(3));
			insert_point[0][0] = span_begin_point[spamNo] - anchor;
			insert_point[0][1] = 0.5 * height - protect_thick - shearlinkDiameter - 0.5 * diameter;
			insert_point[0][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15;
			insert_point[1][0] = span_begin_point[spamNo] - anchor;
			insert_point[1][1] = 0.5 * height - protect_thick - shearlinkDiameter - 0.5 * diameter;
			insert_point[1][2] = -insert_point[0][2];
	
			vector<double> curve{ 0,0, anchor+spans_clear_len[spamNo]+anchor,  0, 0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, Botdz, Botdx, storey);//默认是一层
			break;
		}
		case 1: {//第一排中部钢筋
			int barnum = botLeft[1].numofRebar;
			double bar_span = (width - 2 * protect_thick - 2 * shearlinkDiameter - 45) / (barnum + 1);
			vector<vector<double>> insert_point(barnum, vector<double>(3));
			for (int j = 0; j < barnum; j++) {
				insert_point[j][0] = span_begin_point[spamNo] - anchor;
				insert_point[j][1] = 0.5 * height - protect_thick - shearlinkDiameter - 0.5 * diameter;
				insert_point[j][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15 - (j + 1) * bar_span;
			}
			vector<double> curve{ 0,0, anchor + spans_clear_len[spamNo] + anchor,  0, 0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, Botdz, Botdx, storey);
			break;
		}
		case 2: {//第二排角部钢筋
			int d = max(diameter, 25.0);
			vector<vector<double>> insert_point(2, vector<double>(3));
			insert_point[0][0] = span_begin_point[spamNo] - anchor;
			insert_point[0][1] = 0.5 * height - 2 * d - protect_thick - shearlinkDiameter;
			insert_point[0][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15;
			insert_point[1][0] = insert_point[0][0];
			insert_point[1][1] = insert_point[0][1];
			insert_point[1][2] = -insert_point[1][2];
			vector<double> curve{ 0,0, anchor + spans_clear_len[spamNo] + anchor,  0, 0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, Botdz, Botdx, storey);//默认是一层
			break;
		}
		case 3: {//第二排中部钢筋
			int d = max(diameter, 25.0);
			int barnum = botLeft[3].numofRebar;
			double bar_span = (width - 2 * protect_thick - 2 * shearlinkDiameter - 45) / (barnum + 1);
			vector<vector<double>> insert_point(barnum, vector<double>(3));
			for (int i = 0; i < barnum; i++) {
				insert_point[i][0] = span_begin_point[spamNo] - anchor;
				insert_point[i][1] = 0.5 * height - protect_thick - shearlinkDiameter - 2*d;
				insert_point[i][2] = 0.5 * width - protect_thick - shearlinkDiameter - 15 - (i + 1) * bar_span;
			}
			vector<double> curve{ 0,0, anchor + spans_clear_len[spamNo] + anchor,  0, 0 };
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, curve, diameter, insert_point, origin, Botdz, Botdx, storey);
		}
		default:
			break;
		}
	}
}


void Component_Beam::CalculateBeam() {
	vector<double>extrudedDirecion{0,0,1};
	InsertBeam(1, begin, directionz, directionx, section->shape_type, section->parameter, extrudedDirecion, len);
	int n = spans_info.size();
	int protect_thick = getProtectThick(this->environment_type, ComponentType::Beam);
	
	Rectangular_Shape* shape = static_cast<Rectangular_Shape*>(section);
	int width = shape->wide, height = shape->height;
	int curspanlen = 0;
	vector<vector<double>> shear_insert_point;
	for (int i = 0; i < spans_info.size(); i++) {
		SpanType type = spans_info[i].span_type;
		SpanBarInfo &bar_info = spans_info[i].span_bar_info;
		int clear_span_len = spans_clear_len[i];
		int shearlinkDiameter = bar_info.ShearLinks.LeftZoneInfo.Diameter;
		//每一跨的箍筋处理模式都相同
		if (shearlinkDiameter != 0)
		{
			//shear_insert_point.resize(0);
			int dense_span = bar_info.ShearLinks.LeftZoneInfo.spacing, sparse_span = bar_info.ShearLinks.NormalZoneInfo.spacing, dense_len = max(3 * height / 2, 500);
			int left_edge =  50 + dense_len, right_edge = clear_span_len - 50 - dense_len;
			for (int curpos = 50; curpos < clear_span_len - 50;) {
				shear_insert_point.push_back({ 0,0,span_begin_point[i]+curpos });
				if (curpos <= left_edge || curpos > right_edge) {
					curpos += dense_span;
				}
				else {
					curpos += sparse_span;
				}
			}//得到所有的位置参数
			//计算形状参数
			vector<double> shearsShape(3);
			shearsShape[2] = 2.25 * shearlinkDiameter;//形状一律用半径
			shearsShape[0] = width - 6 * shearlinkDiameter - 2 * protect_thick;
			shearsShape[1] = height - 6 * shearlinkDiameter - 2 * protect_thick;
			Insert2DB::InsertReinforcingBar(BarType::SheadLinks, shearsShape, shearlinkDiameter, shear_insert_point, origin, sheardz, sheardx, storey);
		
		}
		/**************处理腰筋以及拉筋*********/
		vector<vector<double>> side_insert_point;
		
		SideBarInfo& side_bar_info = bar_info.Side;
		if (side_bar_info.numofRebar > 0) {
			int rowCount = side_bar_info.numofRebar / 2;
			double side_bar_span = (height - 2 * protect_thick - 2 * 25) / (rowCount + 1);
			double sidez = 0.5 * width - protect_thick - shearlinkDiameter - 0.5 * side_bar_info.diameter;
			double sidex = span_begin_point[i] - columns_len[i];
			if (i == 0) {
				sidex = -15 / side_bar_info.diameter;
			}
			vector<double> side_curve{ 0,0,clear_span_len + columns_len[i],0,0 };
			if (i == 0) {
				sidex += 25;
				side_curve[2] -= 25;
			}
			for (int j = 0; j < rowCount; j++) {
				double sidey = 0.5 * height - protect_thick - 25 - (j + 1) * side_bar_span;
				side_insert_point.push_back({ sidex,sidey,sidez });
				side_insert_point.push_back({ sidex,sidey,-sidez });
			}
			//printf("%d", side_bar_info.diameter);
			Insert2DB::InsertReinforcingBar(BarType::LongitudinalBarCurve, side_curve, double(side_bar_info.diameter), side_insert_point, origin, Topdz, Topdx, storey);
			//插入 拉筋的位置与腰筋和箍筋类似
			
		}
		vector<vector<double>> tied_insert_point;
		int dis = bar_info.ShearLinks.NormalZoneInfo.spacing * 2;
		int row = side_bar_info.numofRebar / 2;
		int curpos = 50+span_begin_point[i];
		bool flag = 0;
		double adjust = 8;
		int tmp = 0;
		while (curpos<=shear_insert_point.back()[2]) {
			switch (row)
			{
			case 1:
			{
				tied_insert_point.push_back({ 0,adjust+side_insert_point[0][1] * sqrt2 - curpos * sqrt2,  curpos * sqrt2 + side_insert_point[0][1] * sqrt2 });
				break;
			}
			case 2: {
				if(flag)
					tied_insert_point.push_back({ 0,adjust + side_insert_point[0][1] * sqrt2 - curpos * sqrt2, curpos * sqrt2 + side_insert_point[0][1] * sqrt2 });
				else
					tied_insert_point.push_back({ 0,adjust + side_insert_point[2][1] * sqrt2 - curpos * sqrt2,curpos * sqrt2 +  side_insert_point[2][1] * sqrt2 });
				flag = !flag;
				break;
			}
			case 3: {
					tied_insert_point.push_back({ 0,adjust + side_insert_point[0][1] * sqrt2 - curpos * sqrt2,  curpos * sqrt2 + side_insert_point[0][1] * sqrt2 });
					tied_insert_point.push_back({ 0,adjust + side_insert_point[4][1] * sqrt2 - curpos * sqrt2,  curpos * sqrt2 + side_insert_point[4][1] * sqrt2 });
				flag = !flag;
			}
			default:
				break;
			}
			if (tmp == shear_insert_point.size() - 1) {
				break;
			}
			while (tmp<shear_insert_point.size()-1&&curpos + dis > shear_insert_point[tmp][2]) {
				//printf("%d", curpos);
				++tmp;
			}
			//printf("%d", curpos);
			curpos = shear_insert_point[tmp][2];
			
			
		}
		vector<double> tied_curve{ 5.0 * side_bar_info.diameter,2.0 * side_bar_info.diameter,width - 2.0 * protect_thick-4*shearlinkDiameter };
		InsertReinforcingBar(BarType::TiedBarCurve, tied_curve, bar_info.Tied.diameter, tied_insert_point, origin, tieddz, tieddx, storey);
		

		
		switch (type)
		{
		case SimplySupported:
		{

			break;
		}
		case LeftCantilever: {
			break;
		}
			
		case LeftSide: {//对于左边跨，有上左 上右以及 下左 箍筋 
			//先处理上左
			HandleLeftSide();
			}

			//上左中部没有，可以暂时忽略，
			// 处理上左 右部钢筋，此处包含了从当前跨到最右跨的钢筋
			
			
			break;
		
			
		case Internal: {//
			HandleMid(i);
			break;
		}
			
		case RightSide: {
			HandleRightSide();
			break;
		}
			
		case RightCantilever: {
			break;
		}
		default:
			break;
		}

		curspanlen += spans_clear_len[i] + columns_len[i + 1];
	}
}