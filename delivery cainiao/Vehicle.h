#pragma once
#include<vector>
#include "WareHouse.h"

//地图节点数
const int n = 14;
//路径长度上限
const int MaxDis = 1000;
//建筑物名称

const std::string building[n] = {
	"菜鸟驿站","西北门","理科大楼",
	"毛主席像","图书馆","文科大楼",
	"文附楼","北门","游泳池",
	"篮球场","河东食堂","文史楼",
	"体育馆","东门"
};

extern int arcs[n][n];

//前向定义
//class WareHouse;

class Vehicle
{
private:
	int SelfWeight = 10;
	int Capacity = 110;
	int CurWeight;
	int speed = 15;
	std::vector<Parcel> carriage;
	//总目的地个数
	int num;
	//总损耗
	int cost;
	//当前时间
	double time;
	//用于送货目的地
	std::vector<int> visited;
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
	//输出基本信息
	void ShowInfo(int);
	//最小生成树，遍历目的地
	int MinKey(const std::vector<int>&);
	//int MinDis(int, int);
	void deliver(WareHouse& wh);
	//输出完整路径
	void Route();
	void Reset();
};

