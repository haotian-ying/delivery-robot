#pragma once
#include<iostream>

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

struct Pos
{
	//编号
	int no;
	std::string name;

	Pos();
	Pos(int number, const std::string& s) : no(number), name(s){}
};

struct Map
{
	//顶点表
	Pos vexs[n];
	//距离邻接矩阵
	int arcs[n][n];
	//路径数
	int arcnum = 1;

	Map()
	{
		//初始化顶点
		for (int i = 0;i < n;i++)
		{
			vexs[i] = Pos(i, building[i]);
		}
		//初始化网
		for (int i = 0;i < n;i++)
		{
			for (int j = 0;j < n;j++)
			{
				if (i == j)
					arcs[i][i] = 0;
				else
					arcs[i][j] = MaxDis;
			}
		}
		//路径距离
		arcs[0][1] = arcs[1][0] = 96;
		arcs[0][2] = arcs[2][0] = 281;
		arcs[0][3] = arcs[3][0] = 318;
		arcs[0][4] = arcs[4][0] = 323;
		arcs[0][8] = arcs[8][0] = 532;
		arcs[1][2] = arcs[2][1] = 312;
		arcs[2][3] = arcs[3][2] = 145;
		arcs[2][4] = arcs[4][2] = 442;
		arcs[2][5] = arcs[5][2] = 541;
		arcs[3][4] = arcs[4][3] = 226;
		arcs[4][5] = arcs[5][4] = 437;
		arcs[4][8] = arcs[8][4] = 98;
		arcs[4][9] = arcs[9][4] = 112;
		arcs[5][6] = arcs[6][5] = 47;
		arcs[5][9] = arcs[9][5] = 346;
		arcs[5][12] = arcs[12][5] = 162;
		arcs[6][12] = arcs[12][6] = 198;
		arcs[7][8] = arcs[8][7] = 152;
		arcs[8][9] = arcs[9][8] = 143;
		arcs[8][10] = arcs[10][8] = 251;
		arcs[9][11] = arcs[11][9] = 96;
		arcs[9][12] = arcs[12][9] = 412;
		arcs[10][11] = arcs[11][10] = 85;
		arcs[11][12] = arcs[12][11] = 348;
		arcs[11][13] = arcs[13][11] = 261;
		arcs[12][13] = arcs[13][12] = 187;
		

		/*arcs[n][n] = {
			0{0,96,281,318,323,MaxDis,MaxDis,MaxDis,532,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis},
			1{96,0,312,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis},
			2{281,312,0,145,442,541,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis},
			3{318,MaxDis,145,0,226,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis},
			4{323,MaxDis,442,226,0,437,MaxDis,MaxDis,98,112,MaxDis,MaxDis,MaxDis,MaxDis},
			5{MaxDis,MaxDis,MaxDis,MaxDis,437,0,47,MaxDis,MaxDis,346,MaxDis,MaxDis,162,MaxDis},
			6{MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,47,0,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,198,MaxDis},
			7{MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,0,152,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis},
			8{532,MaxDis,MaxDis,MaxDis,98,MaxDis,MaxDis,152,0,143,251,MaxDis,MaxDis,MaxDis},
			9{MaxDis,MaxDis,MaxDis,MaxDis,112,346,MaxDis,MaxDis,143,0,MaxDis,96,412,MaxDis},
			10{MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,251,MaxDis,0,85,MaxDis,MaxDis},
			11{MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,96,85,0,348,261},
			12{MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,162,198,MaxDis,MaxDis,412,MaxDis,348,0,187},
			13{MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,MaxDis,261,187,0}
		};*/
	}
};

