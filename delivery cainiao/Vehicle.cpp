#include "Vehicle.h"
#include<vector>
#include<iomanip>

int arcs[n][n] = {
			{0,96,281,318,323,MaxDis,MaxDis,MaxDis,532,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis},
			{96,0,312,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis},
			{281,312,0,145,442,541,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis},
			{318,MaxDis,145,0,226,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis},
			{323,MaxDis,442,226,0,437,MaxDis,MaxDis,98,112,MaxDis,MaxDis,MaxDis,MaxDis},
			{MaxDis,MaxDis,MaxDis,MaxDis,437,0,47,MaxDis,MaxDis,346,MaxDis,MaxDis,162,MaxDis},
			{MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,47,0,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,198,MaxDis},
			{MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,0,152,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis},
			{532,MaxDis,MaxDis,MaxDis,98,MaxDis,MaxDis,152,0,143,251,MaxDis,MaxDis,MaxDis},
			{MaxDis,MaxDis,MaxDis,MaxDis,112,346,MaxDis,MaxDis,143,0,MaxDis,96,412,MaxDis},
			{MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,251,MaxDis,0,85,MaxDis,MaxDis},
			{MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,96,85,0,348,261},
			{MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,162,198,MaxDis,MaxDis,412,MaxDis,348,0,187},
			{MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,261,187,0}
};

Vehicle::Vehicle()
{
	cost = 0;
	time = 8;
	num = 0;
	CurWeight = SelfWeight;
	for (int i = 0;i < n;i++)
	{
		//默认为访问过
		visited.push_back(1);
	}
}

Vehicle::~Vehicle()
{
	CurWeight = SelfWeight;
	cost = 0;
	carriage.clear();
	visited.clear();
}

double Vehicle::CurTime()
{
	return time;
}

int Vehicle::NumOfDest()
{
	int cnt = 0;
	for (int i = 0;i < n;i++)
	{
		if (visited[i] == 0)
			cnt++;
	}
	return cnt;
}

int Vehicle::TotalCost()
{
	return cost;
}

void Vehicle::ShowInfo(int cnt)
{
	/*for (int i = 0;i < carriage.size();i++)
	{
		std::cout << "编号：" << carriage[i].number<<'\t' << "重量：" << carriage[i].weight << '\t'
				  << "目的地：" << building[carriage[i].destination] << '\t'
				  << "时限：" << carriage[i].TimeLimit << '\t' << "优先级：" << carriage[i].priority <<std::endl;
	}*/
	std::cout << "当前时间：" << time << "时" << std::endl;
	std::cout << "第" << cnt << "趟小车货物基本信息:" << std::endl;
	for (int i = 0; i < carriage.size(); i++)
	{

		std::cout << std::setw(8) << "编号："  << carriage[i].number<<'\t'
			<< std::setw(8) << "重量：" << std::setw(2) << carriage[i].weight
			<< std::setw(16) << "目的地：" << std::setw(7) <<building[carriage[i].destination]<<'\t'
			<< std::setw(8) << "时限：" << std::setw(2) << carriage[i].TimeLimit<<'\t'
			<< std::setw(8) << "优先级：" << std::setw(3) << carriage[i].priority << std::endl;
	}
}

//删除已配送包裹
void Vehicle::LoadParcel(WareHouse& wh)
{
	//载货至装满
	while (CurWeight <= Capacity)
	{
		if (!wh.PacelQueue.empty())
		{
			//装卸货
			Parcel temp = wh.PacelQueue.front();
			auto it = wh.PacelQueue.erase(wh.PacelQueue.begin());
			carriage.push_back(temp);
			CurWeight += temp.weight;
			//std::cout << temp.weight<<std::endl;
			//标记目的地
			visited[temp.destination] = 0;
		}
	}
	//std::cout << NumOfDest() << std::endl;
}

int Vehicle::MinKey(const std::vector<int>& key)
{
	int min = std::numeric_limits<int>::max();
	int MinIndex = -1;

	for (int v = 0; v < n; ++v) {
		if (!visited[v] && key[v] < min) {
			min = key[v];
			MinIndex = v;
		}
	}
	return MinIndex;
}

void Vehicle::deliver(WareHouse& wh)
{
	//前驱
	std::vector<int> parent(n, -1);
	//距离
	std::vector<int> key(n, std::numeric_limits<int>::max());
	//从驿站开始
	key[0] = 0;
	for (int i = 1;i < n;i++)
	{
		if (!visited[i])
		{
			key[i] = arcs[0][i];
			parent[i] = 0;
		}
	}

	int total = NumOfDest();
	for (int i = 1;i < total;i++)
	{
		int k = MinKey(key);
		key[k] = 0;
		if (k != -1)
		{
			visited[k] = 1;
			//计算损耗
			cost += CurWeight * arcs[parent[k]][k];  
			//cost++;
			//std::cout << cost << std::endl;
			//更新耗时
			time += arcs[parent[k]][k] / speed / 60;
			//更新送达后重量
			for (auto it = carriage.begin();it != carriage.end();)
			{
				if (it->destination == k)
				{
					/*if (time > it->TimeLimit)
					{
						wh.OverTime++;
					}*/
					CurWeight -= it->weight;
					it = carriage.erase(it);
				}
				else
					it++;
			}


			for (int j = 0;j < total;j++)
			{
				if (!visited[j] && arcs[k][j] < key[j])
				{
					key[j] = arcs[k][j];
					parent[j] = k;
				}
			}
 		}
	}
}

void Vehicle::Reset()
{
	//std::cout << carriage.size() << std::endl;
	cost = 0;
	for (int i = 0;i < n;i++)
	{
		visited[i] = 1;
	}
}
