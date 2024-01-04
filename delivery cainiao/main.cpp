#include <iostream>
#include <iomanip>
#include "WareHouse.h"
#include "Vehicle.h"

int main()
{
	char mode;
	bool LoopFlag = true;
	while (LoopFlag)
	{
		Vehicle cainiao;

		std::cout << "输入1进行样例测试，2进行简单模拟，3查看仓库信息并进行优先级调整，4增加各个送达点有包裹“发货”的模式，q退出：" << std::endl;
		std::cin >> mode;
		while (mode != '1' && mode != '2' && mode != '3' && mode != '4' && mode != 'q' && mode != 'Q')
		{
			std::cout << "输入1进行样例测试，2进行简单模拟，3进行优先级调整，4进行简单模拟，q退出：" << std::endl;
			std::cin >> mode;
		}

		if(mode == '1')
		{
			int w, ddl, dest;
			std::cout << "请输入样例重量：" << std::endl;
			std::cin >> w;
			std::cout << "请输入样例最晚送达时间（8-18）：" << std::endl;
			std::cin >> ddl;
			std::cout << "请输入样例目的地（1-13，以下标表示）：" << std::endl;
			std::cin >> dest;
			Parcel temp(w,ddl,dest);
			WareHouse test(temp);
			cainiao.LoadParcel(test);

			double prev = cainiao.CurTime();
			int cnt = 1;
			cainiao.ShowInfo(cnt);
			cainiao.NearestDeliver(test);
			std::cout << "当前时间" << cainiao.CurTime() << '\t' << "超时包裹数：" << test.TimeCount(prev,cainiao.CurTime()) << std::endl;
			std::cout << "第" << cnt << "趟送货路径： " << std::endl;
			cainiao.track();
			std::cout << "第" << cnt << "趟送货总耗费： " << cainiao.TotalCost() << "kg*m" << std::endl;
			//分割线
			std::cout << std::endl << std::setfill('-') << std::setw(83) << "" << std::setfill(' ') << std::endl;
			cainiao.Reset();
		}

		if(mode == '2')
		{
			WareHouse wh(300);
			wh.Sort();
			int cnt = 1;
			while (wh.CurSize() > 0 && cainiao.CurTime() <= 18)
			{
				double prev = cainiao.CurTime();
				cainiao.LoadParcel(wh);
				cainiao.ShowInfo(cnt);
				cainiao.NearestDeliver(wh);

				std::cout << "当前时间" << cainiao.CurTime() << '\t' << "超时包裹数：" << wh.TimeCount(prev,cainiao.CurTime()) << std::endl;
				std::cout << "第" << cnt << "趟送货路径： " << std::endl;
				cainiao.track();
				std::cout << "第" << cnt << "趟送货总耗费： " << cainiao.TotalCost() << "kg*m" << std::endl;
				//分割线
				std::cout << std::endl << std::setfill('-') << std::setw(83) << "" << std::setfill(' ') << std::endl;
				cainiao.Reset();
				cnt++;
			}
		}

		if (mode == '3')
		{
			WareHouse wh(300);
			wh.print();
			bool flag = true;
			while (flag)
			{
				std::cout << "是否需要修改包裹优先级?(输入y以继续,n以退出)" << std::endl;
				char sign;
				std::cin >> sign;
				if (sign == 'y')
				{
					std::cout << "输入需要修改优先级的包裹编号" << std::endl;
					int num;
					std::cin >> num;
					wh.Manual(num);
				}
				else if (sign == 'n')
					flag = false;
				else
					flag = false;
			}

			int cnt = 0;
			while (wh.CurSize() > 0 && cainiao.CurTime() <= 18)
			{
				double prev = cainiao.CurTime();
				cainiao.LoadParcel(wh);
				cainiao.ShowInfo(cnt);
				cainiao.NearestDeliver(wh);

				std::cout << "当前时间" << cainiao.CurTime() << '\t' << "超时包裹数：" << wh.TimeCount(prev, cainiao.CurTime()) << std::endl;
				std::cout << "第" << cnt << "趟送货路径： " << std::endl;
				cainiao.track();
				std::cout << "第" << cnt << "趟送货总耗费： " << cainiao.TotalCost() << "kg*m" << std::endl;
				//分割线
				std::cout << std::endl << std::setfill('-') << std::setw(83) << "" << std::setfill(' ') << std::endl;
				cainiao.Reset();
				cnt++;
			}
		}

		if (mode == '4')
		{
			WareHouse wh(300);
			wh.Sort();
			int cnt = 1;
			while (wh.CurSize() > 0 && cainiao.CurTime() <= 18)
			{
				double prev = cainiao.CurTime();
				cainiao.LoadParcel(wh);
				cainiao.ShowInfo(cnt);
				cainiao.NearestDeliver(wh);

				std::cout << "当前时间" << cainiao.CurTime() << '\t' << "超时包裹数：" << wh.TimeCount(prev, cainiao.CurTime()) << std::endl;
				std::cout << "第" << cnt << "趟送货路径： " << std::endl;
				cainiao.track();
				std::cout << "第" << cnt << "趟送货总耗费： " << cainiao.TotalCost() << "kg*m" << std::endl;
				//分割线
				std::cout << std::endl << std::setfill('-') << std::setw(83) << "" << std::setfill(' ') << std::endl;
				cainiao.Reset();
				cnt++;
			}
			DeliveryPoints dp;
			dp.show();
			cainiao.NearestReceiver(dp);
			std::cout << "收货路径： " << std::endl;
			cainiao.track();
		}
		if (mode == 'q' || mode == 'Q')//退出
		{
			std::cout << "谢谢，再见！\n";
			LoopFlag = false;
		}
	}
}