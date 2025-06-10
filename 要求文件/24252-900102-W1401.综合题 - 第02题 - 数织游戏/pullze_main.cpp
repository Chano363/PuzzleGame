/* 学号 姓名 班级 */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

/* 提示：空文件，仅为了提醒你不要忘记首行 && 不要把文件名弄错 */

#include <iostream>
#include <time.h>
#include <cmath>

#include "cmd_console_tools.h"
#include "pullze.h"

using namespace std;
const int maxSize = 15;

/***************************************************************************
  函数名称：
  功    能：随机生成初始时球的位置
  输入参数：
		   char board[][]: 区域数据
		   const int board_size: 区域大小
  返 回 值：无
  说    明：
***************************************************************************/

void generateBalls(char board[maxSize][maxSize],const int board_size,int nums[maxSize][maxSize][2])
{
	long num = board_size * board_size;
	if (num % 2 == 0) num = num / 2; else num = (num + 1) / 2;
	int count = 0;
	srand(time(NULL));
	while (count < num)
	{
		int x = rand() % board_size, y = rand() % board_size;
		while (board[x][y] != ' ')
		{
			x = rand() % board_size; y = rand() % board_size;
		}
		board[x][y] = '0';
		count++;
	}
#if 0
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 0; j < board_size; ++j)
		{
			cout << board[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
#endif
	for (int i = 0; i < board_size; ++i)
	{
		int cntConsecutive = (board[i][0] == '0' ? 1 : 0);
		for (int j = 0; j < board_size; ++j)
		{
			if (board[i][j] != '0' && board[i][j + 1] == '0') cntConsecutive++;
			if (board[i][j] == '0') {
				nums[i][cntConsecutive][0] ++;
			}
		}
		nums[i][0][0] = cntConsecutive; // nums[i][0] 存放数字个数
	}
	for (int i = 0; i < board_size; ++i)
	{
		int cntConsecutive = (board[0][i] == '0' ? 1 : 0);
		for (int j = 0; j < board_size; ++j)
		{
			if (board[j][i] != '0' && board[j + 1][i] == '0') cntConsecutive++;
			if (board[j][i] == '0') {
				nums[i][cntConsecutive][1] ++;
			}
		}
		nums[i][0][1] = cntConsecutive; // nums[i][0] 存放数字个数
	}
#if 0
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 1; j <= nums[i][0][0]; ++j)
			cout << nums[i][j][0] << ' ';
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 1; j <= nums[i][0][1]; ++j)
			cout << nums[i][j][1] << ' ';
		cout << endl;
	}
#endif
	return;
}

/***************************************************************************
  函数名称：
  功    能：打印区域
  输入参数：
		   const char board: 区域数据
		   const int board_size: 区域大小
  返 回 值：无
  说    明：
***************************************************************************/

void display(const char board[maxSize][maxSize], const int board_size, const int nums[maxSize][maxSize][2])
{
	cct_cls();
	char col = 'a', row = 'A';
	int maxColCount = -1, maxRowCount = -1; // 行/列的最大数量
	for (int i = 0; i < board_size; ++i) maxRowCount = maxRowCount > nums[i][0][0] ? maxRowCount : nums[i][0][0]; 
	for (int i = 0; i < board_size; ++i) maxColCount = maxColCount > nums[i][0][1] ? maxColCount : nums[i][0][1];
	int cmd_x = 0, cmd_y = 0;
	// 打印顶栏
	// 打印第一条横向分割线
	putDivLine(0, 0, maxRowCount * 2 + 3);
	putchar('+');
	cct_getxy(cmd_x, cmd_y);
	putDivLine(cmd_x, 0,board_size * 2 + 1);
	putchar('+');
	// 打印左侧纵向边框
	putDivLine(maxRowCount * 2 + 3, 1, maxColCount, 1, '|');
	// 打印数字
	for (int i = 0; i < board_size; ++i)
	{
		cct_getxy(cmd_x, cmd_y);
		cmd_y = 1 + maxColCount - nums[i][0][1];
		cmd_x += 2;
		cct_gotoxy(cmd_x, cmd_y);
		for (int j = 1; j <= nums[i][0][1]; ++j)
		{
			cout << nums[i][j][1] << ' ';
			cct_gotoxy(cmd_x, cmd_y + j + 1);
		}
	}
	// 打印右侧纵向边框
	cct_getxy(cmd_x, cmd_y);
	putDivLine(cmd_x + 2, 1, maxColCount, 1, '|');
	// 打印顶栏第二条横向分割线
	cct_getxy(cmd_x, cmd_y);
	putDivLine(0, cmd_y, maxRowCount * 2 + 3);
	putchar('+');
	cct_getxy(cmd_x, cmd_y);
	putDivLine(cmd_x, cmd_y, board_size * 2 + 1);
	putchar('+');
	// 打印列编号
	cct_getxy(cmd_x, cmd_y);
	cct_gotoxy(maxRowCount * 2 + 3, cmd_y + 1);
	cout << "| ";
	for (int i = 0; i < board_size; ++i)
	{
		cout << col++ << ' ';
	}
	putchar('|');
	// 打印第三条横向分割线
	cct_getxy(cmd_x, cmd_y);
	putDivLine(0, ++cmd_y, maxRowCount * 2 + 1);
	cout << "+-+";
	cct_getxy(cmd_x, cmd_y);
	putDivLine(cmd_x, cmd_y, board_size * 2 + 1);
	putchar('+');
	// 打印侧栏数字
	for (int i = 0; i < board_size; ++i)
	{
		cct_getxy(cmd_x, cmd_y);
		cmd_x =  1 + (maxRowCount - nums[i][0][0]) * 2;
		cmd_y ++;
		cct_gotoxy(cmd_x, cmd_y);
		for (int j = 1; j <= nums[i][0][0]; ++j)
		{
			cout << nums[i][j][0] << ' ';
			// cct_gotoxy(cmd_x + j + 1, cmd_y);
		}
	}
	// 打印行号
	cct_getxy(cmd_x, cmd_y);
	cct_gotoxy(cmd_x, cmd_y - board_size + 1);
	for (int i = 0; i < board_size; ++i)
	{
		cout <<'|' << row++ <<'|';
		cct_getxy(cmd_x, cmd_y);
		cmd_x -= 3;
		cct_gotoxy(cmd_x, ++cmd_y);
	}
	cmd_x += 4;
	cmd_y -= board_size;
	cct_gotoxy(cmd_x, cmd_y);
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 0; j < board_size; ++j)
		{
			cout << board[i][j] << ' ';
		}
		cct_getxy(cmd_x, cmd_y);
		cout << '|';
		cmd_x -= board_size * 2;
		cct_gotoxy(cmd_x, ++cmd_y);
	}
	// 打印第四条横向分割线
	cct_getxy(cmd_x, cmd_y);
	putDivLine(0, cmd_y, maxRowCount * 2 + 1);
	cout << "+-+";
	cct_getxy(cmd_x, cmd_y);
	putDivLine(cmd_x, cmd_y, board_size * 2 + 1);
	putchar('+');
}

/***************************************************************************
  函数名称：
  功    能：打印区域
  输入参数：
		   const char board: 区域数据
		   const int board_size: 区域大小
  返 回 值：无
  说    明：
***************************************************************************/

void initGame(int* board_size,char board[maxSize][maxSize],int nums[maxSize][maxSize][2])
{
	
	cout << "请输入数据区大小(5/10/15)" << endl;
	cin >> *board_size;
	bool flag = false;
	while (true) {
		for (int i = 1; i <= 3; i++)
		{
			if (*board_size == 5 * i) { flag = true; break; }
		}
		if (flag) break;
		cct_cls();
		cout << "请输入重新输入数据区大小(5/10/15)" << endl;
		cin >> *board_size;
	}
	for (int i = 0; i < maxSize; i++) {
		for (int j = 0; j < maxSize; j++) {
			board[i][j] = ' ';
			nums[i][j][0] = 0;
			nums[i][j][1] = 0;
		}
	}
	generateBalls(board, *board_size, nums);
}

int main()
{
	int board_size;
	char board[maxSize][maxSize];
	int nums[maxSize][maxSize][2]; // 每行/列球的个数
	initGame(&board_size, board,nums);
	display(board, board_size,nums);
	while (true)
	{

	}




}