//���˻�����

#define _CRT_SECURE_NO_DEPRECATE
//#pragma warning(disable:4996)

#include<iostream>
#include<string>
#include<map>
#include<vector>
#include<algorithm>

using namespace std;

struct Point      //�˴����Զ���һ����
{
	int x, y, z;
	bool isOk;

	Point() {}   //һ��Ҫ��Ĭ�Ϲ��캯��
	Point(int x, int y, int z, bool isOk) :x(x), y(y), z(z), isOk(isOk) {}   //���캯�����б��ʼ��
};

#define MAX_SIZE (1<<12)
int main()
{
	FILE *fp1 = fopen("in1.txt","r");      //�������ļ����ļ�1�������˻����ͻ�������Ϣ
	FILE *fp2 = fopen("in2.txt","r");     //�ļ�2��������������ļ�

	//��ȡ�ļ�2�е�ѯ����ţ�������ȥ�أ����ٺ�����������
	vector<int>tag;
	for (int x; fscanf(fp2, "%d", &x) != EOF; tag.push_back(x)) {}
	sort(tag.begin(), tag.end());
	tag.erase(unique(tag.begin(), tag.end()), tag.end());
	
	fclose(fp2);    //ע�⣡��ȡ���ļ���һ��Ҫ�ر��ļ��������ļ�ָ���ÿ�
	fp2 = nullptr;

	//ʹ��map���ȡ�����ļ�1�е�����
	int top = 0;
	map<string, Point> mp;
	char s[MAX_SIZE];
	for (int index = 0; fscanf(fp1, "%s", s)!=EOF; index++)
	{
		bool f = false;
		int x, y, z, offsetX, offsetY, offsetZ;
		fscanf(fp1,"%d%d%d",&x,&y,&z);
		if (fgetc(fp1) != '\n')
		{
			fscanf(fp1, "%d%d%d", &offsetX, &offsetY, &offsetZ);
			f = true;
		}
		if (mp.find(s) == mp.end())
		{
			if (!f)
				mp[s] = Point(x, y, z, true);
			else
				mp[s] = Point(0, 0, 0, false);
		}
		else
		{
			if (mp[s].isOk && mp[s].x == x&&mp[s].y == y&&mp[s].z == z)
				mp[s] = Point(x + offsetX, y + offsetY, z + offsetZ, true);
			else
				mp[s].isOk = false;
		}
	
		if (tag[top] == index)
		{
			if (!mp[s].isOk)
				printf("Error: %d\n", index);
			else
				printf("%s %d %d %d %d\n", s, index, x, y, z);
			top++;
		}
	}

	for (; top < (int)tag.size(); ++top)
	{
		printf("cannot find %d\n", tag[top]);
	}
	fclose(fp1);
	fp1 = NULL;

	return 0;
}