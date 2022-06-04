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