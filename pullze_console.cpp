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

void put_div_line(const int x, const int y, const int length, const int dir = 0, const int max_count = 0, const int category = 0)
{
	// ╔═════════════════════╗ 种类0
	// ╚═════════════════════╝ 种类1

	cct_gotoxy(x, y);
	if (dir == 0)
	{
		if (category == 0)
		{
			cout << '╔';
			for (int i = 0; i < length; ++i)
			{
				cout << '═';
			}
			cout << '╗';
		}
		else
		{
			cout << '╚';
			for (int i = 0; i < length; ++i)
			{
				cout << '═';
			}
			cout << '╝';
		}
	}
	
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
	int max_col_count = -1, max_row_count = -1; // 行/列的最大数量
	if (banner)
	{
		for (int i = 0; i < board_size; ++i) max_row_count = max_row_count > nums[i][0][0] ? max_row_count : nums[i][0][0];
		for (int i = 0; i < board_size; ++i) max_col_count = max_col_count > nums[i][0][1] ? max_col_count : nums[i][0][1];
	}
	int cmd_x = 0, cmd_y = 0;
	cct_getxy(cmd_x, cmd_y);
	// 打印顶栏
	if (banner) {
		// 打印第一条横向分割线
		put_div_line(0, cmd_y, board_size, 0, max_row_count, 0);
		// 打印左侧纵向边框
		put_div_line(max_row_count * 2 + 3, cmd_y + 1, max_col_count, 1);
		// 打印数字
		for (int i = 0; i < board_size; ++i)
		{
			cct_getxy(cmd_x, cmd_y);
			cmd_y =  1 + max_col_count - nums[i][0][1];
			cmd_x += 2;
			cct_gotoxy(cmd_x, cmd_y);
			for (int j = 1; j <= nums[i][0][1]; ++j)
			{
				cout << nums[i][j][1] << ' ';
				cct_gotoxy(cmd_x, cmd_y + j);
			}
		}

		// 打印右侧纵向边框
		cct_getxy(cmd_x, cmd_y);
		put_div_line(cmd_x + 2, cmd_y - max_col_count, max_col_count, 1);
	}
	// 打印顶栏第二条横向分割线
	cct_getxy(cmd_x, cmd_y);
	put_div_line(0, cmd_y, board_size, 0, max_row_count, 0);
	// 打印列编号
	cct_getxy(cmd_x, cmd_y);
	if (banner) {
		cct_gotoxy(max_row_count * 2 + 3, cmd_y);
		cout << "| ";
	}
	else cout << "| | ";
	for (int i = 0; i < board_size; ++i)
	{
		cout << col++ << ' ';
	}
	putchar('|');
	// 打印第三条横向分割线
	cct_getxy(cmd_x, cmd_y);
	put_div_line(0, cmd_y + 1, board_size, 0, max_row_count, 1);
	// 打印侧栏数字
	if (banner)
	{
		cct_getxy(cmd_x, cmd_y);
		for (int i = 0; i < board_size; ++i)
		{
			cmd_x = 1 + (max_row_count - nums[i][0][0]) * 2;

			cct_gotoxy(cmd_x, cmd_y);
			for (int j = 1; j <= nums[i][0][0]; ++j)
			{
				cout << nums[i][j][0] << ' ';
				// cct_gotoxy(cmd_x + j + 1, cmd_y);
			}
			cmd_y++;
		}
	}
	// 打印行号
	cct_getxy(cmd_x, cmd_y);
	if (banner)
	{
		cct_gotoxy(cmd_x, cmd_y - board_size + 1);
	}
	for (int i = 0; i < board_size; ++i)
	{
		cout << '|' << row++ << '|';
		cct_getxy(cmd_x, cmd_y);
		cmd_x -= 3;
		cct_gotoxy(cmd_x, ++cmd_y);
	}
	// 打印board
	cmd_x += 4;
	cmd_y -= board_size;
	cct_gotoxy(cmd_x, cmd_y);
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 0; j < board_size; ++j)
		{
			if (play && board[i][j] == 'O' && !cheat)
			{
				cct_setcolor(COLOR_HYELLOW, COLOR_HBLUE), cout << board[i][j], cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				cout << ' ';
			}
			else cout << board[i][j] << ' ';
		}
		cct_getxy(cmd_x, cmd_y);
		cout << '|';
		cmd_x -= board_size * 2;
		cct_gotoxy(cmd_x, ++cmd_y);
	}
	// 打印第四条横向分割线
	put_div_line(0, cmd_y, board_size, 0, max_row_count, 1);
}

void pullze_console(const bool banner) {
	int board_size;
	char data_board[max_board_size][max_board_size], input_board[max_board_size][max_board_size];
	int nums[max_board_size][max_board_size][2]; // 每行/列球的个数
	int cmd_x, cmd_y;
	initGame(&board_size, data_board, input_board, nums);
	cct_cls();
	cct_setconsoleborder(1920, 1080, 1920, 1080);
	console_display();
	return;
}