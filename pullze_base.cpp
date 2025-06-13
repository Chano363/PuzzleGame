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
	// -------+--------------+ 种类0
	// -----+-+--------------+ 种类1

	cct_gotoxy(x, y);
	if (dir == 0) // 横向分割线
	{
		for (int i = 0; i < max_count * 2 + 1; ++i)
			cout << '-';
		if (category == 1)
		{
			cout << "+-+";
		}
		else cout << "--+";
		for (int i = 0; i < length * 2 + 1; ++i)
			cout << '-';
		cout << '+' << endl;
	}
	else          // 纵向分割线
		for (int i = 0; i < length; ++i)
		{
			cout << '|';
			cct_gotoxy(x, y + i + 1);
		}
	return;
}

/***************************************************************************
  函数名称：
  功    能：打印区域
  输入参数：
		   const char board[][]: 区域数据
		   const int board_size: 区域大小
		   const int nums[][]: 相应位置球的数量
		   const int mode: 是否启用作弊模式
  返 回 值：无
  说    明：
***************************************************************************/

void display(const int start_y, const char board[max_board_size][max_board_size], const char input[max_board_size][max_board_size], const int board_size, const int nums[max_board_size][max_board_size][2], const bool banner = 0, const bool play = 0, const bool cheat = 0)
{
	char col = 'a', row = 'A';
	int max_col_count = -1, max_row_count = -1; // 行/列的最大数量
	if (banner) 
	{
		max_row_count = nums[board_size][0][0];
		max_row_count = nums[board_size][0][1];
	}
	int cmd_x = 0, cmd_y = 0;
	cct_getxy(cmd_x, cmd_y);
	// 打印顶栏
	if (banner) {
		// 打印第一条横向分割线
		put_div_line(0, cmd_y, board_size, 0, max_row_count, 0);
		// 打印左侧纵向边框
		put_div_line(max_row_count * 2 + 3, cmd_y + 1, max_col_count, 1);
		// 打印顶栏数字
		for (int i = 0; i < board_size; ++i)
		{
			cct_getxy(cmd_x, cmd_y);
			cmd_y = start_y + 1 + max_col_count - nums[i][0][1];
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
	// 打印列号
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
			if (!play) {
				cout << board[i][j] << ' ';
				continue;
			}
			if (cheat)
			{
				if (input[i][j] != 'O')
				{
					cout << board[i][j] << ' ';
					continue;
				}
				cct_setcolor(COLOR_HYELLOW, COLOR_HBLUE);
				if (input[i][j] == board[i][j]) // 输入相符
					cout << input[i][j];
				else
					cout << 'X';
				cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				cout << ' ';
			}
			else
			{
				if (input[i][j] != 'O')
				{
					cout << "  ";
					continue;
				}
				cct_setcolor(COLOR_HYELLOW, COLOR_HBLUE), cout << input[i][j], cct_setcolor(COLOR_BLACK, COLOR_WHITE);
				cout << ' ';
			}
		}
		cct_getxy(cmd_x, cmd_y);
		cout << '|';
		cmd_x -= board_size * 2;
		cct_gotoxy(cmd_x, ++cmd_y);
	}
	// 打印第四条横向分割线
	put_div_line(0, cmd_y, board_size, 0, max_row_count, 1);
}


void pullze_base(const bool banner,const bool play) {
	int board_size;
	char data_board[max_board_size][max_board_size], input_board[max_board_size][max_board_size];
	int nums[max_board_size][max_board_size][2]; // 每行/列球的个数
	int cmd_x, cmd_y;
	initGame(&board_size, data_board, input_board, nums);
	cct_cls();
	if (!play)
	{
		display(0, data_board, input_board, board_size, nums, banner, play);
		return;
	}

	char opt[2];
	bool cheat = false;
	display(0, input_board, input_board, board_size, nums, banner, play, cheat);
	while (true)
	{
		cout << endl;
		cout << "命令形式：Aa=等价于图形游戏中鼠标左键选择Aa位(区分大小写)" << endl;
		cout << "            不需要支持图形界面的右键打叉，再次输入Aa相当于清除" << endl;
		cout << "        X/x=退出(新行仅有X/x，不分大小写)" << endl;
		cout << "        Y/y=提交(新行仅有Y/y，不分大小写)" << endl;
		cout << "        Z/z=作弊(新行仅有Z/z，不分大小写)" << endl;
		cout << "        Ctrl+c 强制退出" << endl;
		cout << "请输入 : ";
		cin >> opt[0];

		if (opt[0] >= 'A' && opt[0] <= 'A' + board_size - 1) {
			cin >> opt[1];
			if (input_board[opt[0] - 'A'][opt[1] - 'a'] != ' ') // 清除
			{
				input_board[opt[0] - 'A'][opt[1] - 'a'] = ' ';
			}
			else // 放置
				input_board[opt[0] - 'A'][opt[1] - 'a'] = 'O';
			cout << "输入" << opt[0] << opt[1] << "后：" << endl;
			cct_getxy(cmd_x, cmd_y);
			display(cmd_y, data_board, input_board, board_size, nums, banner, play, cheat);
		}
		else if (opt[0] == 'X' || opt[0] == 'x')
		{
  				return;
		}
		else if (opt[0] == 'Y' || opt[0] == 'y')
		{
			if (check_win(input_board, data_board, board_size,nums))
			{
				return;
			}
		}
		else if (opt[0] == 'Z' || opt[0] == 'z')
		{
			if (cheat) cheat = false;
			else cheat = true;
			cout << "输入" << opt[0] << "后：" << endl;
			cct_getxy(cmd_x, cmd_y);
			display(cmd_y,data_board,input_board, board_size, nums, banner, play, cheat);
		}
		else {
			cout << "输入错误" << endl;
		}
	}
	
	return;
}