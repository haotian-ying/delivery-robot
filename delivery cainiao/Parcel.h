#pragma once
#include<string>
class WareHouse;

class Parcel
{
public:
	//编号
	int number;
	int weight;
	int TimeLimit;
	//最晚时间，整点
	std::string destination;
	int priority;

	//其余元素自动生成
	Parcel(int ddl,int sequence,std::string dest);
	~Parcel();
	bool operator<(const Parcel& rhs);
	void ChangePriority(int);
};

