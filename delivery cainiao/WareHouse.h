#pragma once
#include<iostream>
#include<vector>
#include<string>
#include"graph.h"

struct Parcel
{
	//编号
	int number;
	int weight;
	int TimeLimit;
	//最晚时间，整点
	int destination;
	double priority;

	//其余元素自动生成
	Parcel();
	//生成测试样例
	Parcel(int,int,int);
};

class WareHouse
{
private:
	std::vector<Parcel> PacelQueue;
	std::vector<int> received;
	//仓库包裹数上限
	int OverTime = 0;
	int MaxNum = 300;
public:
	friend class Vehicle;
	WareHouse();
	WareHouse(int);
	//用于测试
	WareHouse(const Parcel&);
	~WareHouse();
	void Sort();
	//支持队列操作
	void pop();
	void push(const Parcel&);
	int CurSize();
	Parcel& front();
	//返回当前时间下超时包裹数
	int TimeCount(double,double);
	void UpdateOverTime();
	int TimeCountDP(double);
	void print();
	void PrintSend();
	//催货
	void Manual(int);
};

//各个送达点有包裹“发货”的模式
class DeliveryPoints
{
private:
	std::vector<WareHouse> WareHouseQueue;
	std::vector<int> sign;
public:
	friend class Vehicle;
	DeliveryPoints();
	int size();
	void show();
};


