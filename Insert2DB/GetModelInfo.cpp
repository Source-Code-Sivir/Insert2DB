#include"GetModelInfo.h"
#include<string>
#include<sstream>
using namespace std;
unordered_map<int, Component_Beam> getModelInfo::beams;
std::unordered_map<int, SpanInfo>getModelInfo::spans;
std::unordered_map<int, SpanBarInfo>getModelInfo::barinfos;
std::unordered_map<int, Point>getModelInfo::points;
std::unordered_map<int, Component_Column> getModelInfo::columns;
std::unordered_map<int, Shape*>getModelInfo::sections;

int getBar_callback(void* data, int argc, char** argv, char** azColName) {
	int id = stoi(argv[0]);
	int spanID = stoi(argv[1]);
	int num = stoi(argv[4]);
	int diameter = stoi(argv[5]);
	int steelgrade = stoi(argv[6]);
	int spacing = stoi(argv[8]);
	int position = stoi(argv[9]);
	printf("%d\n", spanID);
	switch (position)
	{
	case 1://1 上左 2上中 3 上右 4下左 5下中 6下右 7 腰部 8 左箍筋 9中箍筋 10 右箍筋
	{
		BasicBarInfo cur;
		cur.diameter = diameter;
		cur.BarType = SteelType(steelgrade);
		cur.numofRebar = num;
		getModelInfo::spans[spanID].span_bar_info.TopLeft.push_back(cur);
		break;
	}
	case 2://1 上左 2上中 3 上右 4下左 5下中 6下右 7 腰部 8 左箍筋 9中箍筋 10 右箍筋
	{
		BasicBarInfo cur;
		cur.diameter = diameter;
		cur.BarType = SteelType(steelgrade);
		cur.numofRebar = num;
		getModelInfo::spans[spanID].span_bar_info.TopMid.push_back(cur);
		break;
	}
	case 3://1 上左 2上中 3 上右 4下左 5下中 6下右 7 腰部 8 左箍筋 9中箍筋 10 右箍筋
	{
		BasicBarInfo cur;
		cur.diameter = diameter;
		cur.BarType = SteelType(steelgrade);
		cur.numofRebar = num;
		getModelInfo::spans[spanID].span_bar_info.TopRight.push_back(cur);
		break;
	}
	case 4://1 上左 2上中 3 上右 4下左 5下中 6下右 7 腰部 8 左箍筋 9中箍筋 10 右箍筋 11 拉筋
	{
		BasicBarInfo cur;
		cur.diameter = diameter;
		cur.BarType = SteelType(steelgrade);
		cur.numofRebar = num;
		getModelInfo::spans[spanID].span_bar_info.BotLeft.push_back(cur);
		break;
	}
	case 5://1 上左 2上中 3 上右 4下左 5下中 6下右 7 腰部 8 左箍筋 9中箍筋 10 右箍筋
	{
		BasicBarInfo cur;
		cur.diameter = diameter;
		cur.BarType = SteelType(steelgrade);
		cur.numofRebar = num;
		getModelInfo::spans[spanID].span_bar_info.BotMid.push_back(cur);
		break;
	}
	case 6://1 上左 2上中 3 上右 4下左 5下中 6下右 7 腰部 8 左箍筋 9中箍筋 10 右箍筋
	{
		BasicBarInfo cur;
		cur.diameter = diameter;
		cur.BarType = SteelType(steelgrade);
		cur.numofRebar = num;
		getModelInfo::spans[spanID].span_bar_info.BotRight.push_back(cur);
		break;
	}
	case 7://1 上左 2上中 3 上右 4下左 5下中 6下右 7 腰部 8 左箍筋 9中箍筋 10 右箍筋
	{
		SideBarInfo cur;
		cur.diameter = diameter;
		cur.BarType = SteelType(steelgrade);
		cur.numofRebar = num;
		if (argv[7] == "N") {
			++cur.numofRebar;//扭筋用奇数表示
		}
		getModelInfo::spans[spanID].span_bar_info.Side = cur;
		break;
	}
	case 8://1 上左 2上中 3 上右 4下左 5下中 6下右 7 腰部 8 左箍筋 9中箍筋 10 右箍筋
	{
		ShearLinkBasicInfo cur;
		cur.Diameter = diameter;
		cur.spacing = spacing;
		cur.BarType = SteelType(steelgrade);
		getModelInfo::spans[spanID].span_bar_info.ShearLinks.LeftZoneInfo = cur;
		break;
	}
	case 9://1 上左 2上中 3 上右 4下左 5下中 6下右 7 腰部 8 左箍筋 9中箍筋 10 右箍筋
	{
		ShearLinkBasicInfo cur;
		cur.Diameter = diameter;
		cur.spacing = spacing;
		cur.BarType = SteelType(steelgrade);
		getModelInfo::spans[spanID].span_bar_info.ShearLinks.NormalZoneInfo = cur;
		break;
	}
	case 10: {
		ShearLinkBasicInfo cur;
		cur.Diameter = diameter;
		cur.spacing = spacing;
		cur.BarType = SteelType(steelgrade);
		getModelInfo::spans[spanID].span_bar_info.ShearLinks.RightZoneInfo = cur;
		break;
	}
	default:
		break;
	}
	return 0;
}

int getBeam_callback(void* data, int argc, char** argv, char** azColName) {
	int id = stoi(argv[0]);
	int storeyID = stoi(argv[1]);
	int spanNum = stoi(argv[3]);
	int pt1ID = stoi(argv[4]), pt2ID = stoi(argv[5]);
	int material = stoi(argv[6]);
	int sectionID = stoi(argv[7]);
	int xstartOffset = stoi(argv[8]), xendoffset = stoi(argv[9]), ystartoffset = stoi(argv[10]), yendoffset = stoi(argv[11]);

	Component_Beam& curbeam = getModelInfo::beams[id];
	curbeam.beam_type = BeamType::Girder;
	curbeam.id = id;

	curbeam.section = getModelInfo::sections[sectionID];
	int height = static_cast<Rectangular_Shape*>(curbeam.section)->height;

	curbeam.begin.resize(3);
	curbeam.begin[0] = getModelInfo::points[pt1ID][0]+  xstartOffset;
	curbeam.begin[1] = getModelInfo::points[pt1ID][1] + ystartoffset;
	curbeam.begin[2] = getModelInfo::points[pt1ID][2]-0.5*height;

	double tmpx = curbeam.begin[0]- (getModelInfo::points[pt2ID][0] + xendoffset);
	double tmpy = curbeam.begin[1]- (getModelInfo::points[pt2ID][1] + yendoffset);
	
	curbeam.directionx.resize(3);
	curbeam.directionz.resize(3);
	curbeam.begin.resize(3);

	curbeam.storey = storeyID;

	double len = sqrt(tmpx * tmpx + tmpy * tmpy);
	curbeam.len = len;
	printf("%.3f", len);
	curbeam.directionz[0] = (getModelInfo::points[pt2ID][0] - getModelInfo::points[pt1ID][0])/len;
	curbeam.directionz[1]= (getModelInfo::points[pt2ID][1]- getModelInfo	::points[pt1ID][1])/len;

	if (curbeam.directionz[0] == 0) {//往y方向去的
		curbeam.directionx[0] = -1;
		curbeam.directionx[1] = 0;
		curbeam.directionx[2] = 0;
	}
	else if (curbeam.directionz[1] == 0)//x方向去的梁
	{
		curbeam.directionx[0] = 0;
		curbeam.directionx[1] = 1;
	}
	else {
		curbeam.directionx[0] = -1;
		curbeam.directionx[1] = curbeam.directionz[0]/curbeam.directionz[1];
	}
	
	curbeam.concrete_type = ConcreteType(material);
	return 0;
}

int getSpan_callback(void* data, int argc, char** argv, char** azColName) {
	int id = stoi(argv[0]);
	int type = stoi(argv[1]);
	int beamid = stoi(argv[2]);
	int pt1id = stoi(argv[3]);
	int pt2id = stoi(argv[4]);
	int xstartoffset = stoi(argv[5]), xendoffset = stoi(argv[6]), ystartoffset = stoi(argv[7]), yendoffset = stoi(argv[8]);
	int type1 = stoi(argv[10]), type2 = stoi(argv[11]);
	double tmpx = (getModelInfo::points[pt1id][0] + xstartoffset) - (getModelInfo::points[pt2id][0] +xendoffset);
	double tmpy = (getModelInfo::points[pt1id][1] + ystartoffset) - (getModelInfo::points[pt2id][1]+yendoffset);

	printf("%.3f %.3f", tmpx, tmpy);
	double len = sqrt(tmpx * tmpx + tmpy * tmpy);
	
	getModelInfo::beams[beamid].spans_clear_len.push_back(len);
	

	SpanInfo& span = getModelInfo::spans[id];
	
	span.span_type = SpanType(type);
	span.xstartoffset = xstartoffset;
	span.xendoffset = xendoffset;
	span.ystartoffset = ystartoffset;
	span.yendoffset = yendoffset;
	span.pt1Type = type1;
	span.pt2Type = type2;

	getModelInfo::beams[beamid].spans_info.emplace_back(span);
	return 0;
}

int getSection_callback(void* data, int argc, char** argv, char** azColName) {
	int id = stoi(argv[0]);
	int type = stoi(argv[1]);
	string parameter(argv[2]);

	stringstream ss(parameter);
	vector<int> datas;
	string tmp;
	while (ss>>tmp)
	{
		datas.push_back(stoi(tmp));
	}
	switch (type)
	{
	case 1: {//矩形截面
		Rectangular_Shape* shape = new Rectangular_Shape();
		shape->wide = datas[0];
		shape->height = datas[1];
		getModelInfo::sections[id] = shape;
		shape->parameter = argv[2];
		break;
	}
	default:
		break;
	}
	return 0;
}

int getPoint_callback(void* data, int argc, char** argv, char** azColName) {
	int id = stoi(argv[0]);
	int stdstyID = stoi(argv[1]);
	int x = stoi(argv[2]);
	int y = stoi(argv[3]);
	int z = stoi(argv[4]);
	getModelInfo::points[id].resize(3);
	getModelInfo::points[id][0] = x;
	getModelInfo::points[id][1] = y;
	getModelInfo::points[id][2] = z;
	return 0;
}


void getBar() {
	string comman("select * from Bar;");
	SqliteExecution::Instance()->SelectDb(comman, getBar_callback, 0);
}
void getBeam() {
	string command = "select * from ContinousBeam;";
	SqliteExecution::Instance()->SelectDb(command, getBeam_callback, 0);
}
void getPoint() {
	string command = "select * from Point;";
	SqliteExecution::Instance()->SelectDb(command, getPoint_callback, 0);
}
void getSection() {
	string command = "select * from Section;";
	SqliteExecution::Instance()->SelectDb(command, getSection_callback, 0);
}
void getSpan() {
	string command = "select * from Span;";
	SqliteExecution::Instance()->SelectDb(command, getSpan_callback, 0);
}