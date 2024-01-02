#include "WareHouse.h"
#include<set>
#include<random>
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

Parcel::Parcel(int sequence) : priority(sequence)
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
	std::uniform_int_distribution<> deliveryTimeDistribution(8, 18);
	TimeLimit = deliveryTimeDistribution(gen);
	//地址
	std::uniform_int_distribution<> DestinationDistribution(1, 13);
	destination = DestinationDistribution(gen);
	//bool operator<(const Parcel& rhs);
}

WareHouse::WareHouse() 
{
	for (int i = 0;i < MaxNum;i++)
	{
		Parcel temp(i);
		PacelQueue.push_back(temp);
	}
}

WareHouse::WareHouse(int num)
{
	num = std::min(num, MaxNum);
	for (int i = 0;i < num;i++)
	{
		Parcel temp(i);
		PacelQueue.push_back(temp);
	}

	/*for (int i = 0;i < num;i++)
	{
		std::cout << PacelQueue[i].destination << std::endl;
	}*/
}

WareHouse::~WareHouse()
{
	if (!PacelQueue.empty())
		PacelQueue.clear();
}

int WareHouse::CurSize()
{
	return PacelQueue.size();
}

int WareHouse::OverTime(double cur)
{
	int cnt = 0;
	for (const auto& temp : PacelQueue)
	{
		if (temp.TimeLimit < cur)
			cnt++;
	}
	return cnt;
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
			//PacelQueue[0].priority = 
		}
		else
			id++;
	}
}