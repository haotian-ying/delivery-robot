#include <iostream>
#include <iomanip>
#include "WareHouse.h"
#include "Vehicle.h"

//WareHouse globalWarehouse;
//Vehicle globalVehicle;


int main()
{
	//实例化
	WareHouse wh(100);
	Vehicle cainiao;
	int cnt = 1;
	while (wh.CurSize() > 0 && cainiao.CurTime() <= 18)
	{
		cainiao.LoadParcel(wh);
		cainiao.ShowInfo(cnt);
		cainiao.deliver(wh);

		std::cout << "当前时间" << cainiao.CurTime() <<'\t' << "超时包裹数：" << wh.OverTime(cainiao.CurTime()) << std::endl;
		std::cout << "第"<<cnt<<"趟送货总耗费： "<<cainiao.TotalCost()<<"kg*m" << std::endl;
		//分割线
		std::cout <<std::endl << std::setfill('-') << std::setw(83) << "" << std::setfill(' ') << std::endl;
		cainiao.Reset();
		cnt++;
	}
}