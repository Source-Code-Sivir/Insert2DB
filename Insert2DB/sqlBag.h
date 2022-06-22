#pragma once
#include"sqlite3.h"
#include<string>
#include<vector>
#pragma comment(lib,"sqlite3.lib")

//��sqliteҪ�õĲ���ɾ��������װһ��
class SqliteExecution
{ 
public:
	//Ŀ����ʲô���Ƿ���һ���Ѿ���ʼ����sqlite3��ʵ��
	static SqliteExecution *Instance() {
		static SqliteExecution ins;
		return &ins;
	}
	void Init(std::string file) {//��init��ʱ���Ѿ���ʼ����db�ˣ�����ֱ�ӵ��þ����ˡ�
		int rc = sqlite3_open(file.data(),&db);
		if (rc) {
			fprintf(stderr, "error:cannot open database:%s\n", sqlite3_errmsg(db));
			exit(0);
		}
		else {
			fprintf(stderr, "Open successfully!\n");
		}
		sqlite3_exec(db, "begin;", 0, 0, 0);
	}




	void closeDb() {
		sqlite3_exec(db, "commit;", 0, 0, 0);
		sqlite3_close(db);
	}
	void insertDb(std::string command) {
		char* errmsg = 0;

		int rc = sqlite3_exec(db,command.data(),0,0,&errmsg);//�������������Բ��ô� insert��delete���ø�
		if (rc != SQLITE_OK) {
			fprintf(stderr, "Insert failed!:%s\n", errmsg);
			sqlite3_free(errmsg);
		}
		else {
			fprintf(stdout, "Insert Successfully!\n");
		}
	}
	void SelectDb(std::string command,int(*callback)(void*, int, char**, char**), void*tmp) {
		char* errmsg = 0;
		int rc = sqlite3_exec(db, command.data(), callback, tmp, &errmsg);
		if (rc != SQLITE_OK) {
			fprintf(stderr,"SELECT Failed!:%s\n", errmsg);
			sqlite3_free(errmsg);
		}
		else {
			fprintf(stdout, "SELECT Successfully!\n");
		}
	}
	void eraseAllTable() {
		std::vector<std::string> commands;
		commands.emplace_back("delete from IfcCircle;");
		commands.emplace_back("delete from IfcCompositeCurve;");
		commands.emplace_back("delete from IfcDirection;");
		commands.emplace_back("delete from IfcLine;");
		commands.emplace_back("delete from IfcLocalPlacement;");
		commands.emplace_back("delete from IfcMappedItem;");
		commands.emplace_back("delete from IfcPlacement3D;");
		commands.emplace_back("delete from IfcPoint;");
		commands.emplace_back("delete from IfcReinforcingBar;");
		commands.emplace_back("delete from IfcSweptDiskSolid;");
		commands.emplace_back("delete from IfcTrimmedCurve;");
		commands.emplace_back("delete from IfcBeam;");
		commands.emplace_back("delete from IfcBuildingStory;");
		commands.emplace_back("delete from IfcExtrudedAreaSolid;");
		for (auto& i : commands) {
			insertDb(i);
		}
	}
private:
	SqliteExecution() {};
	~SqliteExecution() { closeDb(); };
	sqlite3* db;
};

