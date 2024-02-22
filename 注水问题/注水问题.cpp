//注水问题：源自信息论，将值为1的总功率分给n个信道，使得总功率最大。总功率为∑log(ai+xi)，ai为已知条件。

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <graphics.h>

using namespace std;

//定义一个判断是否找到最优解的函数，即比较∑max{0，v-ai}与1的大小，其中v为“水位”
int finished(vector<double>& ai, double v)
{
	//求和
	double sum = 0.0;
	for (double number : ai) {
		if (v - number > 0.0) {
			sum += v - number; //默认每个信道的宽度为1，所以（v - number）*1
		}
	}
	//与1比较，浮点数比较采用差值小于某个极小值作为依据
	if (abs(sum-1) < 0.000001)
	{
		return 0;
	}
	else if (sum - 1 >= 0.000001)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

int main()
{
	//随机初始化条件，包括n个信道、每个信道的ai
	//使用当前时间作为随机数种子
	srand(std::time(0));

	//生成一个介于10到50之间的随机整数n
	int n = rand() % 41 + 10;

	//生成n个0到(10/n)之间的随机小数ai，并存储在vector中
	vector<double> ai;
	for (int i = 0; i < n; ++i) {
		double randomDouble = static_cast<double>(rand()) / RAND_MAX * (10.0 / n);
		ai.push_back(randomDouble);
	}

	//使用二分法对v进行搜索
	double v = 0;     //v用于记录最终结果
	double v0 = 0.5;  //v0 < v1，用来代二分法的表初始区间
	double v1 = 0;

	//用于寻找初始区间(v0,v1)
	if (finished(ai, v0) == 1)
	{
		while (finished(ai, v0) == 1) //直至finished(ai, v0) != 1
		{
			v0 = v0 / 2;
		}
		v1 = 2 * v0;  //此时刚好finished(ai, v0) != 1,finished(ai, v1) == 1
	}
	else if (finished(ai, v0) == -1)
	{
		while (finished(ai, v0) == -1) //直至finished(ai, v0) != -1
		{
			v0 = v0 * 2;
		}
		v1 = v0;
		v0 = v0 / 2;  //此时刚好finished(ai, v1) != -1,finished(ai, v0) == -1
	}
	else
	{
		v = v0;  //在确定初始区间时恰好找到了最优解
	}

	//开始进行二分法搜索
	if(v != v0)
	{
		//vtemp用于记录中值
		double vtemp = (v0 + v1) / 2;
		while (finished(ai, vtemp))
		{
			if (finished(ai, vtemp) == 1) //中值过大，另v1=(v0 + v1) / 2，重复
			{
				v1 = vtemp;
				vtemp = (v0 + v1) / 2;
			}
			else if (finished(ai, vtemp) == -1) //中值过小，另v0=(v0 + v1) / 2，重复
			{
				v0 = vtemp;
				vtemp = (v0 + v1) / 2;
			}
		}
		v = vtemp;
	}

	//输出最优解v（注水高度，为书中的式子1/v*）
	cout << "水深为"<< v;

	int width = 800;
	int height = 600;
	initgraph(width, height);  //初始化图形窗口
	setbkcolor(0xFFFFFF);
	cleardevice();  //清空画布，以便背景颜色生效

	//绘制分段函数(y=ai)
	setcolor(0x0000FF);
	int startX = 0;
	for (int i = 0; i < ai.size(); ++i) {
		int endX = startX + 1;
		rectangle(startX * (width / n), ai[i] * height * n / 10, endX * (width / n), height); //数据随窗口大小调整 
		startX = endX;
	}

	//绘制直线(y=v)
	setcolor(0xFF0000);
	line(0, v * height * n / 10, width, v * height * n / 10);

	
	system("pause");

	return 0;

}