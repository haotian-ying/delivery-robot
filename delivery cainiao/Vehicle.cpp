#include "Vehicle.h"
#include<vector>
#include<stack>
#include<iomanip>

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
	while (CurWeight <= Capacity && !wh.PacelQueue.empty())
	{
			//装卸货
			Parcel temp = wh.PacelQueue.front();
			auto it = wh.PacelQueue.erase(wh.PacelQueue.begin());
			carriage.push_back(temp);
			CurWeight += temp.weight;
			//标记目的地
			visited[temp.destination] = 0;
	}
}

std::vector<int> Vehicle::solveKnapsack(WareHouse& wh)
{
	int len = wh.PacelQueue.size();
	std::vector<std::vector<double>> dp(len + 1, std::vector<double>(Capacity - SelfWeight + 1, 0));

	for (int i = 1; i <= len; ++i) {
		for (int w = 0; w <= Capacity - SelfWeight; ++w) 
		{
			int approxValue = static_cast<int>(wh.PacelQueue[i - 1].priority);
			if (approxValue < w)
				dp[i][w] = std::max(dp[i - 1][w], dp[i - 1][w - approxValue] + wh.PacelQueue[i - 1].priority);
			else 
				dp[i][w] = dp[i - 1][w];
		}
	}

	// 回溯获取所选择的包裹编号
	std::vector<int> selectedParcels;
	int i = len, w = Capacity - SelfWeight;
	while (i > 0 && w > 0) {
		if (dp[i][w] != dp[i - 1][w]) {
			selectedParcels.push_back(i - 1);
			w -= wh.PacelQueue[i - 1].weight;
		}
		--i;
	}

	return selectedParcels;
}


void Vehicle::LoadParcelDP(WareHouse& wh)
{
	// 使用背包问题解决函数获取选择的包裹编号
	std::vector<int> selectedParcels = solveKnapsack(wh);

	// 根据选择的包裹编号进行装载
	for (int idx : selectedParcels) {
		carriage.push_back(wh.PacelQueue[idx]);
		CurWeight += wh.PacelQueue[idx].weight;
		visited[wh.PacelQueue[idx].destination] = 0;
		wh.received[idx] = 1;
	}
}

int Vehicle::NearestDest(int start,bool back)
{
	visited[start] = 1; 
	std::vector<int> s(n, 0);
	std::vector<int> path(n, 0);
	std::vector<int> d(n, 0);

	for (int i = 0;i < n;i++)
	{
		s[i] = 0;
		d[i] = arcs[start][i];
		if (d[i] < MaxDis)
			path[i] = start;
		else
			path[i] = -1;
	}
	s[start] = 1;
	d[start] = 0;

	for (int i = 1;i < n;i++)
	{
		int v = 0;
		int min = MaxDis;
		for (int j = 0;j < n;++j) 
		{
			if (s[j] == 0 && d[j] < min)
			{
				v = j;
				min = d[j];
			}
		}
		s[v] = true;
		
		//更新其余最短路径
		for (int j = 0;j < n;j++)
		{
			if (!s[j] && (d[v] + arcs[v][j] < d[j]))
			{
				d[j] = d[v] + arcs[v][j];
				path[j] = v;
			}
		}
	}

	//找出下一个目的地
	int min = std::numeric_limits<int>::max();;
	int next = 0;

	if (!back)
	{
		for (int i = 0;i < n;i++)
		{
			if (!visited[i] && (d[i] < min))
			{
				min = d[i];
				next = i;
			}
		}
	}

	int temp = next;
	std::stack<int> helper;
	while (temp != start)
	{
		helper.push(temp);
		//找前驱结点
		cost += arcs[temp][path[temp]] * CurWeight;
		time += static_cast<double>(arcs[temp][path[temp]]) / speed / 60.0;
		temp = path[temp];
	}

	while (!helper.empty())
	{
		int temp = helper.top();
		route.push_back(temp);
		helper.pop();
	}
	return next;
}

void Vehicle::NearestDeliver(WareHouse& wh)
{
	int total = NumOfDest();
	int start = 0;
	int cur;
	route.push_back(0);
	for (int i = 0;i < total;i++)
	{
		cur = NearestDest(start,false);
		//卸货
		for (auto it = carriage.begin();it != carriage.end();)
		{
			if (it->destination == cur)
			{
				CurWeight -= it->weight;
				//送达过程中超时
				if (time > it->TimeLimit)
				{
					wh.UpdateOverTime();
				}
				it = carriage.erase(it);
			}
			else
				it++;
		}
		start = cur;
	}
	cur = NearestDest(start, true);
}

void Vehicle::drop()
{
	if (carriage.size() > 0)
	{
		std::cout << "到站包裹信息:" << std::endl;
		for (auto it = carriage.begin();it != carriage.end();)
		{
			CurWeight -= it->weight;
			std::cout << std::setw(8) << "编号：" << it->number << '\t'
				<< std::setw(8) << "重量：" << std::setw(2) << it->weight<<std::endl;
			it = carriage.erase(it);
		}
	}
}

void Vehicle::NearestReceiver(DeliveryPoints& dp)
{
	int total = dp.WareHouseQueue.size();
	for (int i = 0;i < n;i++)
	{
		visited[i] = dp.sign[i];
	}
	int start = 0;
	int cur;
	route.push_back(0);
	int i = 0;
	while(i < total)
	{
		//装载量未满则继续装载
		cur = NearestDest(start, false);
		
		//接收货物
		LoadParcel(dp.WareHouseQueue[i]);
		if (dp.WareHouseQueue[i].PacelQueue.size() > 0)
		{
			//仍未送完
			visited[i] = 0;
		}
		//该点完成
		else {
			dp.sign[i] = 1;
			i++;
		}
		
		if (cur == 0)
		{
			//顺路回原点则卸货
			drop();
			CurWeight = 0;
		}
		start = cur;
		//std::cout << CurWeight << std::endl;
	}
	//最终返回
	cur = NearestDest(start, true);
	drop();
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


void Vehicle::deliver()
{
	//
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
			time += arcs[parent[k]][k] / speed / 60.0;
			//更新送达后重量
			for (auto it = carriage.begin();it != carriage.end();)
			{
				if (it->destination == k)
				{
					/*if (time > it->TimeLimit)
					{
						wh.UpdateOverTime();
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
	cost = 0;
	for (int i = 0;i < n;i++)
	{
		visited[i] = 1;
	}
	route.clear();
}

void Vehicle::track()
{
	for (int i = 0;i < route.size();i++)
	{
		if (i != route.size() - 1)
			std::cout << building[route[i]] << "---->";
		else
			std::cout << building[route[i]] << std::endl;
	}
}
