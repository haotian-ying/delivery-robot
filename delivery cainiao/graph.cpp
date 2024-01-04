#include"graph.h"

const int n = 14;
const int MaxDis = 1000;

const std::string building[n] = {
	"菜鸟驿站","西北门","理科大楼",
	"毛主席像","图书馆","文科大楼",
	"文附楼","北门","游泳池",
	"篮球场","河东食堂","文史楼",
	"体育馆","东门"
};

std::vector<std::vector<int>> arcs = {
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
