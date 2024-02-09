#define _CRT_SECURE_NO_WARNINGS
#include<cstdio>
#include<ctime>
#include<cstring>
#include<cctype>
#include<stdlib.h>
#include<algorithm>
#include<vector>
#include<string>
#include<iomanip>
#include<iostream>
#include<fstream>
#define bit 7
using namespace std;

string path;
vector<string>vec;
string a;
char ch;
char s[2341];
int flag;

int designed();
void random();
void outputmode();
void swapmode();
void end();

int main(int argc, char* argv[])
{
	FILE* fflag = NULL;	//配置文件

	path = argv[0];

	//打开标志文件
	fflag = fopen("D:\\Program Files\\KawayamaProject\\Kawayama-Flag.txt", "r");
	//flag文件不存在 执行随机输出
	if (fflag == NULL)
	{
		random();
		return 0;
	}

	//读取标志
	fscanf(fflag, "%d", &flag);
	fclose(fflag);

	//flag为1/2/3 执行计划输出
	if (flag >= 1)
	{
		//flag为2 重置flag为1
		if (flag == 2)
		{
			fflag = fopen("D:\\Program Files\\KawayamaProject\\Kawayama-Flag.txt", "w");
			fprintf(fflag, "1");
			fclose(fflag);
		}

		//执行计划输出
		return designed();
	}
	else
	{
		//执行随机输出
		random();
	}

	return 0;
}

void random()
{
	freopen("name.in", "r", stdin);
	while (cin >> a)
	{
		vec.push_back(a);
	}
	fclose(stdin);
	freopen("seat.in", "r", stdin);
	int seed = time(NULL);
	srand(seed);
	random_shuffle(vec.begin(), vec.end());
	int i = 0, siz = vec.size();
	bool led = 0;
	while ((ch = getchar()) != EOF)
	{
		if (ch == '*')
		{
			if (i < siz)	cout << setw(bit) << left << vec[i++];
			else cout << setw(bit) << left;
		}
		else if (ch == '.')cout << setw(bit - 1) << left << ' ';
		else cout << endl;
	}
	fclose(stdin);
	freopen("CON", "r", stdin);

	//Optupt File
	freopen("seat.in", "r", stdin);
	freopen("seat.out", "w", stdout);
	i = 0, siz = vec.size();
	led = 0;
	while ((ch = getchar()) != EOF)
	{
		if (ch == '*')
		{
			if (i < siz)	cout << setw(bit) << left << vec[i++];
			else cout << setw(bit) << left;
		}
		else if (ch == '.')cout << setw(bit - 1) << left << ' ';
		else cout << endl;
	}

	//End
	freopen("CON", "w", stdout);
	freopen("CON", "r", stdin);

	end();

	return;
}

int designed()
{
	FILE *fsrc = NULL;	//计划文件

	//=====flag为1 仅交换模式=====
	if (flag == 1)
	{
		//打开交换列表文件
		fsrc = fopen("D:\\Program Files\\KawayamaProject\\Kawayama-Swap.txt", "r");

		//交换列表文件不存在
		if (fsrc == NULL)
		{
			//执行随机输出
			random();
			return 0;
		}

		//交换列表文件存在 关闭fsrc并调用交换模式
		fclose(fsrc);
		swapmode();
		return 2;
	}

	//=====flag为2或3 优先计划模式=====
	if (flag >= 2)
	{
		//打开计划文件
		fsrc = fopen("D:\\Program Files\\KawayamaProject\\Kawayama-List.txt", "r");

		//计划文件不存在
		if (fsrc == NULL)
		{
			//再打开交换列表文件
			fsrc = fopen("D:\\Program Files\\KawayamaProject\\Kawayama-Swap.txt", "r");

			//交换列表文件也不存在
			if (fsrc == NULL)
			{
				//执行随机输出
				random();
				return 0;
			}

			//计划文件不存在但交换列表文件存在 关闭fsrc并调用交换模式
			fclose(fsrc);
			swapmode();
			return 2;
		}

		//计划文件存在 关闭fsrc并调用计划模式
		fclose(fsrc);
		outputmode();
		return 1;
	}
}

void outputmode()
{
	char in_char;	//存储读取的char类型变量
	FILE* fsrc = NULL;	//计划文件
	FILE* fdest = NULL;	//输出文件
	
	//打开计划文件
	fsrc = fopen("D:\\Program Files\\KawayamaProject\\Kawayama-List.txt", "r");

	//输出到窗口
	while (!feof(fsrc))
	{
		if ((in_char = fgetc(fsrc)) != EOF)
		{
			putchar(in_char);
		}
	}

	//输出到文件
	//打开输出文件
	fdest = fopen("seat.out", "w");
	if (fdest == NULL)
	{
		return;
	}
	while (!feof(fsrc))
	{
		if ((in_char = fgetc(fsrc)) != EOF)
		{
			fputc(in_char, fdest);
		}
	}
	fclose(fsrc);
	fclose(fdest);

	end();

	return;
}

void swapmode()
{
	//先随机生成座位表
	freopen("name.in", "r", stdin);
	while (cin >> a)
	{
		vec.push_back(a);
	}
	fclose(stdin);
	freopen("seat.in", "r", stdin);
	int seed = time(NULL);
	srand(seed);
	random_shuffle(vec.begin(), vec.end());
	
	//再进行交换
	//读入交换列表文件
	FILE* fswap = NULL;
	fswap = fopen("D:\\Program Files\\KawayamaProject\\Kawayama-Swap.txt", "r");
	if (fswap != NULL)
	{
		while (!feof(fswap))
		{
			int seatid;	//目标座位号 以右下角为1
			char target_cstr[16];	//最大支持的姓名长度为15
			string target;	//目标姓名
			int index;
			int actualseatid;	//目标座位号对应vec编号(从左上角开始计算 不便于使用 且易在seat.in改变时变化)

			fscanf(fswap, "%d %[^\n]", &seatid, target_cstr);
			actualseatid = vec.size() - seatid;
			target = target_cstr;
			auto ind = std::find(vec.begin(), vec.end(), target);
			if (ind != vec.end())
			{
				index = distance(vec.begin(), find(vec.begin(), vec.end(), target));
				vec[index] = vec[actualseatid];
				vec[actualseatid] = target;
			}
		}
	}
	
	//关闭交换列表文件
	fclose(fswap);

	//输出
	int i = 0, siz = vec.size();
	bool led = 0;
	while ((ch = getchar()) != EOF)
	{
		if (ch == '*')
		{
			if (i < siz)	cout << setw(bit) << left << vec[i++];
			else cout << setw(bit) << left;
		}
		else if (ch == '.')cout << setw(bit - 1) << left << ' ';
		else cout << endl;
	}
	fclose(stdin);
	freopen("CON", "r", stdin);

	//输出到文件
	freopen("seat.in", "r", stdin);
	freopen("seat.out", "w", stdout);
	i = 0, siz = vec.size();
	led = 0;
	while ((ch = getchar()) != EOF)
	{
		if (ch == '*')
		{
			if (i < siz)	cout << setw(bit) << left << vec[i++];
			else cout << setw(bit) << left;
		}
		else if (ch == '.')cout << setw(bit - 1) << left << ' ';
		else cout << endl;
	}

	//重定向后面的输出到控制台
	freopen("CON", "w", stdout);
	freopen("CON", "r", stdin);

	end();

	return;
}

void end()
{
	string command;	//启动清理程序的命令

	printf("\nPress and enter to end\n");

	//启动清理程序
	command = "\"D:\\Program Files\\KawayamaProject\\KawayamaEnd.exe\" \"";	//启动程序
	command += path;	//传入目标路径
	command += "\" >nul 2>nul";	//屏蔽输出和错误信息
	system(command.c_str());
	
	//按任意键
	getchar();

	return;
}