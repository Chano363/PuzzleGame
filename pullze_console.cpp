/* 学号 姓名 班级 */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

/* 提示：空文件，仅为了提醒你不要忘记首行 && 不要把文件名弄错 */

#include "pullze.h"

using namespace std;


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

void console_put_div_line(const int x, const int y, const int length, const int dir = 0, const int max_count = 0, const int category = 0)
{
	// ╔═════════════════════╗ 种类0
	// ╚═════════════════════╝ 种类1

	cct_gotoxy(x, y);
	// cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	if (dir == 0)
	{
		if (category == 0)
		{
			cout << "╔";
			for (int i = 0; i < length * 2; ++i)
			{
				cout << "═";
			}
			cout << "╗";
		}
		else
		{
			cout << "╚";
			for (int i = 0; i < length * 2; ++i)
			{
				cout << "═";
			}
			cout << "╝";
		}
		cout << endl;
	}
	else
	{
		for (int i = 0; i < length; ++i)
		{
			cout << "║";
			cct_gotoxy(x, y + i + 1);
		}
	}
	// cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

void console_display(const char board[max_board_size][max_board_size],const int board_size,const int nums[max_board_size][max_board_size][2],const int banner)
{
	char col = 'a', row = 'A';
	int cmd_x = 0, cmd_y = 0;
	cct_getxy(cmd_x, cmd_y);
	cout << endl;
	// 打印列号
	cout << "   ";
	for (int i = 0; i < board_size; ++i)
	{
		cout << col++ << ' ';
	}
	// 打印顶部边框线
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	cct_getxy(cmd_x, cmd_y);
	console_put_div_line(2, cmd_y + 1, board_size);
	// 打印列号
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_getxy(cmd_x, cmd_y);
	for (int i = 0; i < board_size; ++i)
	{
		cout << row++ <<' ' << endl;
	}
	// 打印左侧边框
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	console_put_div_line(2, cmd_y, board_size , 1);
	// 打印board
	cct_gotoxy(3, cmd_y);
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 0; j < board_size; ++j)
		{
			if (board[i][j] == 'O')
			{
				cct_setcolor(COLOR_HBLUE, COLOR_BLACK);
				cout << "〇";
				cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
			}
			else cout << "  ";
		}		
		cct_getxy(cmd_x, cmd_y);
		cct_gotoxy(3, cmd_y + 1);
	}
	// 打印右侧边框
	cct_getxy(cmd_x, cmd_y);
	console_put_div_line(3 + board_size * 2, cmd_y - board_size ,board_size,1);
	// 打印底部框线
	cct_getxy(cmd_x, cmd_y);
	console_put_div_line(2, cmd_y , board_size, 0, 0, 1);
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

void pullze_console(const bool banner) {
	int board_size;
	char data_board[max_board_size][max_board_size], input_board[max_board_size][max_board_size];
	int nums[max_board_size][max_board_size][2]; // 每行/列球的个数
	int cmd_x = 0, cmd_y = 0;
	initGame(&board_size, data_board, input_board, nums);
	cct_cls();
	cct_setconsoleborder(70, 32, 140, 64);
	cct_setfontsize("新宋体", 26);
	console_display(data_board, board_size, nums, banner);
	return;
}