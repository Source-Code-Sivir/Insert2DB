#pragma once
#ifndef GETID_H
#define GETID_H
class GetID {
public:
	static int getShapeRepresentationID() {
		return ++ShapreRepresentationID;
	}
	static int getLineID() {
		return ++LineID;
	}
	static int getCircleID() {
		return ++CircleID;
	}
	static int getPointID() {
		return ++PointID;
	}
	static int getDirectionID() {
		return ++DirectionID;
	}
	static int getPlacement3DID() {
		return ++Placement3DID;
	}
	static int getTrimmedCurveID() {
		return ++TrimmedCurveID;
	}
	static int getCompositeCurveID() {
		return ++CompositeCurveID;
	}
	static int getSweptDiskSolidID() {
		return ++SweptDiskSolidID;
	}
	static int GetMappedItemID() {
		return ++MappedItemID;
	}
	static int GetReinforcingBarID() {
		return ++ReinforcingBarID;
	}
	static int GetLocalPlacementID() {
		return ++LocalPlacementID;
	}
	static int GetFloorID() {
		return FloorID;
	}
	static int InsertFloorID() {
		return ++FloorID;
	}
	static int InsertBuildingID() {
		return ++BuildingID;
	}
	static int GetBeamID() {
		return ++BeamID;
	}
	static int GetExtrudedAreaSolidID() {
		return ++ExtrudedAreaSolidID;
	}
	static int ExtrudedAreaSolidID;
	static int BeamID;
	static int FloorID;
	static std::vector<int> localPlacementIDStack;//尾元素为当前相对的LocalPlacementID，注意出栈
	static int BuildingID;
	static std::vector<int> BuildingStoreyIDStack;//默认就是一个
	static int ReinforcingBarID;
	static int MappedItemID;
	static int ShapreRepresentationID;
	static int LineID;
	static int CircleID;
	static int PointID;
	static int DirectionID;
	static int Placement3DID;
	static int LocalPlacementID;
	//static int DirectionID;
	//static int CircleID;
	static int TrimmedCurveID;
	static int CompositeCurveID;
	static int SweptDiskSolidID;
};
#endif // !GETID_H