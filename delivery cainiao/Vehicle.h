#pragma once
#include<vector>
#include "WareHouse.h"

class Vehicle
{
private:
	int SelfWeight = 10;
	int Capacity = 250;
	int CurWeight;
	int speed = 60;
	std::vector<Parcel> carriage;
	//总目的地个数
	int num;
	//总损耗
	int cost;
	//当前时间
	double time;
	//用于送货目的地
	std::vector<int> visited;
	//存储路径
	std::vector<int> route;
public:
	Vehicle();
	~Vehicle();	
	//确定送货地点，
	double CurTime();
	//目的地个数
	int NumOfDest();
	//总损耗
	int TotalCost();
	//装载包裹
	void LoadParcel(WareHouse&);
	std::vector<int> solveKnapsack(WareHouse&);
	void LoadParcelDP(WareHouse&);
	//输出基本信息
	void ShowInfo(int);

	//最小生成树，遍历目的地
	int MinKey(const std::vector<int>&);
	void deliver();
	
	//最近邻算法
	int NearestDest(int,bool);
	void NearestDeliver(WareHouse&);
	void NearestReceiver(DeliveryPoints&);
	//在驿站卸货
	void drop();                           
	//输出完整路径
	void track();
	void Reset();
};

