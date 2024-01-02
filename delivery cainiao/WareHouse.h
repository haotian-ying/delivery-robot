#pragma once
#include<iostream>
#include<vector>
#include<string>

struct Parcel
{
	//编号
	int number;
	int weight;
	int TimeLimit;
	//最晚时间，整点
	int destination;
	int priority;

	//其余元素自动生成
	Parcel(int sequence);
};

class WareHouse
{
private:
	std::vector<Parcel> PacelQueue;
	//仓库包裹数上限
	int MaxNum = 100;
public:
	//自动生成包裹序列
	WareHouse();
	WareHouse(int);
	friend class Vehicle;
	~WareHouse();
	//返回剩余包裹数
	int CurSize();
	//返回当前时间下超时包裹数
	int OverTime(double);
	//催货
	void Manual(int);
};

