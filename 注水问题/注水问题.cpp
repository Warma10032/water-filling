//עˮ���⣺Դ����Ϣ�ۣ���ֵΪ1���ܹ��ʷָ�n���ŵ���ʹ���ܹ�������ܹ���Ϊ��log(ai+xi)��aiΪ��֪������

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <graphics.h>

using namespace std;

//����һ���ж��Ƿ��ҵ����Ž�ĺ��������Ƚϡ�max{0��v-ai}��1�Ĵ�С������vΪ��ˮλ��
int finished(vector<double>& ai, double v)
{
	//���
	double sum = 0.0;
	for (double number : ai) {
		if (v - number > 0.0) {
			sum += v - number; //Ĭ��ÿ���ŵ��Ŀ��Ϊ1�����ԣ�v - number��*1
		}
	}
	//��1�Ƚϣ��������Ƚϲ��ò�ֵС��ĳ����Сֵ��Ϊ����
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
	//�����ʼ������������n���ŵ���ÿ���ŵ���ai
	//ʹ�õ�ǰʱ����Ϊ���������
	srand(std::time(0));

	//����һ������10��50֮����������n
	int n = rand() % 41 + 10;

	//����n��0��(10/n)֮������С��ai�����洢��vector��
	vector<double> ai;
	for (int i = 0; i < n; ++i) {
		double randomDouble = static_cast<double>(rand()) / RAND_MAX * (10.0 / n);
		ai.push_back(randomDouble);
	}

	//ʹ�ö��ַ���v��������
	double v = 0;     //v���ڼ�¼���ս��
	double v0 = 0.5;  //v0 < v1�����������ַ��ı��ʼ����
	double v1 = 0;

	//����Ѱ�ҳ�ʼ����(v0,v1)
	if (finished(ai, v0) == 1)
	{
		while (finished(ai, v0) == 1) //ֱ��finished(ai, v0) != 1
		{
			v0 = v0 / 2;
		}
		v1 = 2 * v0;  //��ʱ�պ�finished(ai, v0) != 1,finished(ai, v1) == 1
	}
	else if (finished(ai, v0) == -1)
	{
		while (finished(ai, v0) == -1) //ֱ��finished(ai, v0) != -1
		{
			v0 = v0 * 2;
		}
		v1 = v0;
		v0 = v0 / 2;  //��ʱ�պ�finished(ai, v1) != -1,finished(ai, v0) == -1
	}
	else
	{
		v = v0;  //��ȷ����ʼ����ʱǡ���ҵ������Ž�
	}

	//��ʼ���ж��ַ�����
	if(v != v0)
	{
		//vtemp���ڼ�¼��ֵ
		double vtemp = (v0 + v1) / 2;
		while (finished(ai, vtemp))
		{
			if (finished(ai, vtemp) == 1) //��ֵ������v1=(v0 + v1) / 2���ظ�
			{
				v1 = vtemp;
				vtemp = (v0 + v1) / 2;
			}
			else if (finished(ai, vtemp) == -1) //��ֵ��С����v0=(v0 + v1) / 2���ظ�
			{
				v0 = vtemp;
				vtemp = (v0 + v1) / 2;
			}
		}
		v = vtemp;
	}

	//������Ž�v��עˮ�߶ȣ�Ϊ���е�ʽ��1/v*��
	cout << "ˮ��Ϊ"<< v;

	int width = 800;
	int height = 600;
	initgraph(width, height);  //��ʼ��ͼ�δ���
	setbkcolor(0xFFFFFF);
	cleardevice();  //��ջ������Ա㱳����ɫ��Ч

	//���Ʒֶκ���(y=ai)
	setcolor(0x0000FF);
	int startX = 0;
	for (int i = 0; i < ai.size(); ++i) {
		int endX = startX + 1;
		rectangle(startX * (width / n), ai[i] * height * n / 10, endX * (width / n), height); //�����洰�ڴ�С���� 
		startX = endX;
	}

	//����ֱ��(y=v)
	setcolor(0xFF0000);
	line(0, v * height * n / 10, width, v * height * n / 10);

	
	system("pause");

	return 0;

}