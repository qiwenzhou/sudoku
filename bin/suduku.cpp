// suduku.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<IOSTREAM>
#include<CTIME>
#include <fstream>
using namespace std;
int sudo[9][9], hole[9][9];
int checkCol[9][9];
int checkBox[9][9];
ofstream out;
void printSudo()
{
	//ofstream out;
	/*try { out.open("sudoku.txt",ios::trunc); }
	catch (exception e) {
		cout << "打开文件：sudoku.txt 失败！！";
	}*/
	for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			out << sudo[y][x] << " ";
		}
		out << "\n";
	}
	out << "\n";
	/*for (int y = 0; y < 9; y++) {
		for (int x = 0; x < 9; x++) {
			cout << sudo[y][x] << " ";
		}
		cout << "\n";
	}
	cout << "\n";*/
	//out.close();
}
void init() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			sudo[i][j] = 0;
			checkCol[i][j] = 0;
			checkBox[i][j] = 0;
		}
	}
	//作业要求：
	sudo[0][0] = 7;

	checkCol[0][6] = 1;
	checkBox[0][6] = 1;
}
/*
	检查放置的位置是否合法。因为是按行放置，所以不用急检查行冲突
	checkCol[i][j]表示第i列的数字 j+1 是否放置过.0表示还没放置，1表示放置过。
	将九宫格从上到下，从左到右编号。
	checkBox[i][j]  等于1表示 第i个九宫格 j+1 已在这一九宫格中.
	| 0 | 1 | 2 |
	| 3 | 4 | 5 |
	| 6 | 7 | 8 |
*/
bool set(int x, int y, int val)
{
	if (sudo[y][x] != 0)//非空  
		return false;
	if (checkCol[x][val - 1] == 1)
		return false;
	int y0 = y / 3;
	int x0 = x / 3;
	int i = y0 * 3 + x0;
	if (checkBox[i][val - 1] == 1)
		return false;
	checkCol[x][val - 1] = 1;
	checkBox[i][val - 1] = 1;
	sudo[y][x] = val;
	//printSudo();
	return true;

}

void reset(int x, int y, int val)
{
	sudo[y][x] = 0;
	checkCol[x][val - 1] = 0;
	checkBox[y / 3 * 3 + x / 3][val - 1] = 0;
}

void initXOrd(int* xOrd)//0~8随机序列  
{
	int i, k, tmp;
	for (i = 0; i<9; i++)
	{
		xOrd[i] = i;
	}
	for (i = 0; i<9; i++)
	{
		k = rand() % 9;
		tmp = xOrd[k];
		xOrd[k] = xOrd[i];
		xOrd[i] = tmp;
	}
}

bool fillFrom(int y, int val)
{
	int xOrd[9];
	initXOrd(xOrd);
	for (int i = 0; i<9; i++)
	{
		int x = xOrd[i];
		//作业要求
		if (val == 7 && x == 0 && y == 0) {
			if (fillFrom(y + 1, val))//直接下一行继续填数  
				return true;
			else {
				continue;
			}
		}
		if (set(x, y, val))
		{
			if (y == 8)//到了最后一行  
			{
				if (val == 9 || fillFrom(0, val + 1))//当前填9则结束, 否则从第一行填下一个数  
					return true;
			}
			else
			{
				if (fillFrom(y + 1, val))//下一行继续填当前数  
					return true;
			}
			//回溯 
			reset(x, y, val);
		}
	}
	return false;
}



int main(int argc, char* argv[])
{
	double num = 0;
	cin >> num;
	try { out.open("sudoku.txt", ios::trunc); }
	catch (exception e) {
		cout << "打开文件：sudoku.txt 失败！！";
	}
	for (double i = 0; i < num; i++) {
		init();
		srand((unsigned)(time(NULL) + i));
		while (!fillFrom(0, 1));
		printSudo();
	}
	out.close();
}

