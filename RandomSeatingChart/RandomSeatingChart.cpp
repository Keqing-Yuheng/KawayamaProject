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
#define bit 7
using namespace std;

vector<string>vec;
string a;
char ch;
char s[2341];

int main()
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

	printf("\nPress ENTER to exit...\n");
	getchar();
}