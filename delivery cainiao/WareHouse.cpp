#include "WareHouse.h"
#include<set>
#include <iomanip>
#include<random>
#include <algorithm> 
#include<iostream>

int generateUniqueRandomNumber() {
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> distribution(10000, 99999);
	//确保不重复
	std::set<int> uniqueNumbers;

	while (true) {
		int randomNumber = distribution(gen);
		auto insertionResult = uniqueNumbers.insert(randomNumber);

		if (insertionResult.second) {
			//成功插入，则独特
			return randomNumber;
		}
	}
}

Parcel::Parcel()
{ 
	//生成编号
	number = generateUniqueRandomNumber();
	//随机数生成器
	std::random_device rd;
	std::mt19937 gen(rd());
	//均匀分布，生成重量
	std::uniform_real_distribution<> weightDistribution(1, 20);
	weight = weightDistribution(gen);
	//包裹送达时限
	std::uniform_int_distribution<> deliveryTimeDistribution(9, 18);
	TimeLimit = deliveryTimeDistribution(gen);
	//地址
	std::uniform_int_distribution<> DestinationDistribution(1, 13);
	destination = DestinationDistribution(gen);
	//基于时限，距离，重量生成优先级,
	priority = 24 - TimeLimit;
}
 
Parcel::Parcel(int w, int ddl,int dest)
{
	number = generateUniqueRandomNumber();
	weight = w;
	TimeLimit = ddl;
	destination = dest;
	priority = 1;
	priority = 24 - TimeLimit;
}

WareHouse::WareHouse() 
{
	for (int i = 0;i < MaxNum;i++)
	{
		Parcel temp;
		PacelQueue.push_back(temp);
		received.push_back(0);
	}
}

WareHouse::WareHouse(int num)
{
	num = std::min(num, MaxNum);
	for (int i = 0;i < num;i++)
	{
		Parcel temp;
		PacelQueue.push_back(temp);
		received.push_back(0);
	}
}


WareHouse::WareHouse(const Parcel& p)
{
	PacelQueue.push_back(p);
	received.push_back(0);
}

WareHouse::~WareHouse()
{
	if (!PacelQueue.empty())
		PacelQueue.clear();
}

bool CmpTimeLimit(const Parcel& a, const Parcel& b)
{
	return a.TimeLimit < b.TimeLimit;
}

void WareHouse::Sort()
{
	std::sort(PacelQueue.begin(), PacelQueue.end(), CmpTimeLimit);
}

void WareHouse::pop()
{
	PacelQueue.erase(PacelQueue.begin());
}

void WareHouse::push(const Parcel& temp)
{
	PacelQueue.push_back(temp);
}

Parcel& WareHouse::front()
{
	return PacelQueue[0];
}

int WareHouse::CurSize()
{
	return PacelQueue.size();
}

void WareHouse::UpdateOverTime()
{
	OverTime++;
}

int WareHouse::TimeCount(double prev,double cur)
{
	for (int i = 0;i < PacelQueue.size();i++)
	{
		if (PacelQueue[i].TimeLimit < cur && PacelQueue[i].TimeLimit > prev)
		{
			OverTime++;
			PacelQueue[i].priority = 0;
		}
	}
	return OverTime;
}

int WareHouse::TimeCountDP(double cur)
{
	for (int i = 0;i < PacelQueue.size();i++)
	{
		if (PacelQueue[i].TimeLimit < cur && received[i] == 0)
		{
			OverTime++;
		}
	}
	return OverTime;
}

void WareHouse::print()
{
	for (int i = 0; i < PacelQueue.size(); i++)
	{

		std::cout << std::setw(8) << "编号：" << PacelQueue[i].number << '\t'
			<< std::setw(8) << "重量：" << std::setw(2) << PacelQueue[i].weight
			<< std::setw(16) << "目的地：" << std::setw(7) << building[PacelQueue[i].destination] << '\t'
			<< std::setw(8) << "时限：" << std::setw(2) << PacelQueue[i].TimeLimit << '\t'
			<< std::setw(8) << "优先级：" << std::setw(3) << PacelQueue[i].priority << std::endl;
	}
}

void WareHouse::PrintSend()
{
	for (int i = 0; i < PacelQueue.size(); i++)
	{
		std::cout << std::setw(8) << "编号：" << PacelQueue[i].number << '\t'
			<< std::setw(8) << "重量：" << std::setw(2) << PacelQueue[i].weight << std::endl;
	}
}

void WareHouse::Manual(int no)
{
	//定位催货元素
	int id = 0;
	for (const auto& temp : PacelQueue)
	{
		if (temp.number == no)
		{
			//删除被催货元素
			Parcel temp = PacelQueue[id];
			PacelQueue.erase(PacelQueue.begin() + id);
			//首位插入，完成催货
			PacelQueue.insert(PacelQueue.begin(), temp);
		}
		else
			id++;
	}
}

DeliveryPoints::DeliveryPoints()
{
	for (int i = 0;i < n;i++)
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		//设置寄货点
		std::uniform_int_distribution<int> distribution(0, 5);
		int num ;
		if (i == 0)
			num = 0;
		else
			num = distribution(gen);
		if (num > 0)
			sign.push_back(0);
		else
			sign.push_back(1);
		WareHouse temp(num);
		WareHouseQueue.push_back(temp);
	}
}

int DeliveryPoints::size()
{
	int cnt = 0;
	for (int i = 0;i < n;i++)
	{
		if (sign[i] == 0)
		{
			cnt++;
		}
	}
	return cnt;
}

void DeliveryPoints::show()
{
	std::cout << "各个送达点有发货包裹信息如下:" << std::endl;
	for (int i = 1;i < n;i++)
	{
		if (sign[i] == 1)
			std::cout << building[i] << "不需要寄包裹" << std::endl;
		else {
			std::cout << building[i] << "包裹编号：" ;
			WareHouseQueue[i].PrintSend();
		}
	}
}