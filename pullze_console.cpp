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

// 定义输出部分的符号 前面的字母代表颜色
#define B_CIRCLE 0
#define R_CIRCLE 1
#define W_CIRCLE 2
#define B_CROSS 3
#define R_CROSS 4
#define BLANK 5

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

void console_put_div_line(const int x, const int y, const int length, const int dir = 0, const int max_count = 0, const int category = 0, const int split = 0)
{
	// 小球无边框
	// ╔═════════════════════╗ 种类0
	// ╚═════════════════════╝ 种类1
	// ╠═════════════════════╣ 种类2
	// ╔══════╦═════╬════════╣ 种类3
	// ╚══════╩═════╩════════╝ 种类4
	// 小球有边框
	// ╔══════╦════╦═════╦═══╗ 种类0
	// ╠══════╬════╬═════╬═══╣ 种类1
	// ╚══════╩════╩═════╩═══╝ 种类2
	// ╔═════════════════════╗ 种类3
	// ╠═════════════════════╣ 种类4
	// ╔═══╦═══╬═══╦═══╦═══╦═╣ 种类5

	cct_gotoxy(x, y);
	// cct_setcolor(COLOR_HWHITE, COLOR_BLACK);

	if (dir == 1)
	{
		for (int i = 0; i < length; ++i)
		{
			cout << "║";
			cct_gotoxy(x, y + i + 1);
		}
		return;
	}
	switch (split)
	{
	case 0:
		switch (category)
		{
		case 0:
		{
			cout << "╔";
			for (int i = 0; i < length * 2; ++i)
				cout << "═";
			cout << "╗";
			break;
		}
		case 1:
		{
			cout << "╚";
			for (int i = 0; i < length * 2; ++i)
				cout << "═";
			cout << "╝";
			break;
		}
		case 2:
		{
			cout << "╠";
			for (int i = 0; i < length * 2; ++i)
				cout << "═";
			cout << "╣";
			break;
		}
		case 3:
		{
			cout << "╔";
			for (int i = 0; i < max_count * 2 + 1; ++i)
				cout << "═";
			cout << "╦══╬";
			for (int i = 0; i < length * 2; ++i)
				cout << "═";
			cout << "╣";
			break;
		}
		case 4:
		{
			cout << "╚";
			for (int i = 0; i < max_count * 2 + 1; ++i)
				cout << "═";
			cout << "╩══╩";
			for (int i = 0; i < length * 2; ++i)
				cout << "═";
			cout << "╝";
			break;
		}
		default:
			break;
		}
		cout << endl;
		break;
	case 1:
		// 小球有边框
		// ╔══════╦════╦═════╦═══╗ 种类0
		// ╠══════╬════╬═════╬═══╣ 种类1
		// ╚══════╩════╩═════╩═══╝ 种类2
		// ╔═════════════════════╗ 种类3
		// ╠═════════════════════╣ 种类4
		// ╔═══╦═══╬═══╦═══╦═══╦═╣ 种类5
		switch (category)
		{
		case 0:
			cout << "╔";
			for (int i = 0; i < length; ++i)
			{
				for (int j = 0; j < 7; j++)
				{
					cout << "═";
				}
				if (i != length - 1)
					cout << "╦";
			}
			cout << "╗";
			break;
		case 1:
			cout << "╠";
			for (int i = 0; i < length; ++i)
			{
				for (int j = 0; j < 7; j++)
				{
					cout << "═";
				}
				if (i != length - 1)
					cout << "╬";
			}
			cout << "╣";
			break;
		case 2:
			cout << "╚";
			for (int i = 0; i < length; ++i)
			{
				for (int j = 0; j < 7; j++)
				{
					cout << "═";
				}
				if (i != length - 1)
					cout << "╩";
			}
			cout << "╝";
			break;
		case 3:
			cout << "╔";
			for (int i = 0; i < length; ++i)
				cout << "═";
			cout << "╗";
			break;
		case 4:
			cout << "╠";
			for (int i = 0; i < length; ++i)
				cout << "═";
			cout << "╣";
			break;
		case 5:
			cout << "╔";
			for (int i = 0; i < max_count * 2 + 2; ++i)
			{
				cout << "═";
			}
			cout << "╦════╬";
			for (int i = 0; i < length; ++i)
			{
				for (int j = 0; j < 7; j++)
				{
					cout << "═";
				}
				if (i != length - 1)
					cout << "╦";
			}
			cout << "╣";
		}
		cout << endl;
		break;
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

void console_display(const char board[max_board_size][max_board_size], const int board_size, const int nums[max_board_size][max_board_size][2], const int banner)
{
	char col = 'a', row = 'A';
	int max_col_count = -1, max_row_count = -1; // 行/列的最大数量
	if (banner)
	{
		max_row_count = nums[board_size][0][0];
		max_col_count = nums[board_size][0][1];
	}
	int cmd_x = 0, cmd_y = 0;
	cout << endl;
	if (banner)
	{
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		// 顶部框线
		cct_getxy(cmd_x, cmd_y);
		console_put_div_line(max_row_count * 2 + 5, cmd_y, board_size, 0, 0, 0);
		// 打印左侧纵向边框
		console_put_div_line(max_row_count * 2 + 5, cmd_y + 1, max_col_count, 1);
		// 打印顶栏数字
		cct_getxy(cmd_x, cmd_y);
		cct_gotoxy(cmd_x + 1, 2);
		for (int i = 0; i < board_size; ++i)
		{
			cct_getxy(cmd_x, cmd_y);
			for (int j = 1; j <= max_col_count - nums[i][0][1]; ++j)
			{
				cout << "  ";
				cct_gotoxy(cmd_x, cmd_y + j);
			}
			cct_getxy(cmd_x, cmd_y);
			for (int j = 1; j <= nums[i][0][1]; ++j)
			{
				cout << nums[i][j][1] << ' ';
				cct_gotoxy(cmd_x, cmd_y + j);
			}
			cct_getxy(cmd_x, cmd_y);
			cmd_y = 2;
			cmd_x += 2;
			cct_gotoxy(cmd_x, cmd_y);
		}

		// 打印右侧纵向边框
		cct_getxy(cmd_x, cmd_y);
		console_put_div_line(cmd_x, cmd_y, max_col_count, 1);
		// 打印顶栏第二条横向分割线
		cct_getxy(cmd_x, cmd_y);
		console_put_div_line(max_row_count * 2 + 5, cmd_y, board_size, 0, 0, 2);
		// 打印列号
		cct_getxy(cmd_x, cmd_y);
		cct_gotoxy(max_row_count * 2 + 5, cmd_y);
		cout << "║";
		for (int i = 0; i < board_size; ++i)
		{
			cout << col++ << ' ';
		}
		cout << "║";
		cct_getxy(cmd_x, cmd_y);
		console_put_div_line(0, cmd_y + 1, board_size, 0, max_row_count, 3);
		// 打印侧栏纵向边框线
		cct_getxy(cmd_x, cmd_y);
		console_put_div_line(cmd_x, cmd_y, board_size, 1);
		// 打印侧栏数字
		for (int i = 0; i < board_size; ++i)
		{
			cmd_x = 1;
			cct_gotoxy(cmd_x, cmd_y);
			for (int j = 0; j < max_row_count - nums[i][0][0]; ++j)
			{
				cout << "  ";
			}
			for (int j = 1; j <= nums[i][0][0]; ++j)
			{
				cout << nums[i][j][0] << ' ';
			}
			cmd_y++;
		}
		// 打印行号
		cct_getxy(cmd_x, cmd_y);
		cct_gotoxy(cmd_x, cmd_y - board_size + 1);
		for (int i = 0; i < board_size; ++i)
		{
			cout << " ║ " << row++ << "║";
			cct_getxy(cmd_x, cmd_y);
			cct_gotoxy(cmd_x - 5, cmd_y + 1);
		}
		cct_getxy(cmd_x, cmd_y);
		cct_gotoxy(cmd_x + 5, cmd_y);
	}
	else
	{
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
			cout << row++ << ' ' << endl;
		}
		// 打印左侧边框
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		console_put_div_line(2, cmd_y, board_size, 1);
	}
	// 打印board
	if (!banner)
		cct_gotoxy(3, cmd_y);
	else
	{
		cct_getxy(cmd_x, cmd_y);
		cct_gotoxy(cmd_x, cmd_y - board_size);
	}
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
			else
				cout << "  ";
		}
		cct_getxy(cmd_x, cmd_y);
		cct_gotoxy(cmd_x - board_size * 2, cmd_y + 1);
	}
	cct_getxy(cmd_x, cmd_y);
	if (banner)
	{
		// 打印右侧边框
		console_put_div_line(cmd_x + board_size * 2, cmd_y - board_size, board_size, 1);
		// 打印底部框线
		console_put_div_line(0, cmd_y, board_size, 0, max_row_count, 4);
	}
	else
	{
		// 打印右侧边框
		console_put_div_line(3 + board_size * 2, cmd_y - board_size, board_size, 1);
		// 打印底部框线
		cct_getxy(cmd_x, cmd_y);
		console_put_div_line(2, cmd_y, board_size, 0, 0, 1);
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
		  const int type: 0 为球，1 为 ×，2 为空
  返 回 值：
  说    明：
***************************************************************************/
void darw(const int top_left_x, const int top_left_y, const int x, const int y, const int type)
{
	switch (type)
	{
	case 0:
		cct_setcolor(COLOR_HBLUE, COLOR_BLACK);
		break;
	case 1:
		cct_setcolor(COLOR_HRED, COLOR_BLACK);
		break;
	case 2:
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		break;
	}
	cct_gotoxy(top_left_x + x * 8, top_left_y + y * 4);
	cout << (type == 2 ? "       " : " ╔═══╗ ");
	cct_gotoxy(top_left_x + x * 8, top_left_y + y * 4 + 1);
	if (type == 0)
		cout << " ║ 〇║ ";
	else if (type == 1)
		cout << "║ ×║ ";
	else if (type == 2)
		cout << "       ";
	cct_gotoxy(top_left_x + x * 8, top_left_y + y * 4 + 2);
	cout << (type == 2 ? "       " : " ╚═══╝ ");
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	return;
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void console_display_split(const char board[max_board_size][max_board_size], const int board_size, const int nums[max_board_size][max_board_size][2], const int banner)
{
	char col = 'a', row = 'A';
	int max_col_count = -1, max_row_count = -1; // 行/列的最大数量
	if (banner)
	{
		max_row_count = nums[board_size][0][0];
		max_col_count = nums[board_size][0][1];
	}
	int cmd_x = 0, cmd_y = 0;
	int top_left_x, top_left_y;
	if (!banner)
	{
		top_left_x = 2, top_left_y = 2;
		cout << endl;
		// 打印列号
		cout << "       ";
		for (int i = 0; i < board_size; ++i)
		{
			cout << col++ << "       ";
		}
		// 打印行号
		cct_gotoxy(0, 4);
		for (int i = 0; i < board_size; ++i)
		{
			cout << row++ << ' ';
			cct_getxy(cmd_x, cmd_y);
			cct_gotoxy(cmd_x - 2, cmd_y + 4);
		}
	}
	cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	if (banner)
	{
		top_left_x = max_row_count * 2 + 8;
		top_left_y = max_col_count + 4;
		// 打印顶部分割线
		console_put_div_line(top_left_x, 1, board_size * 8 - 1, 0, 0, 3, 1);
		// 打印顶栏左侧纵向分割线
		console_put_div_line(top_left_x, 2, max_col_count, 1);
		// 打印顶栏数字
		cct_getxy(cmd_x, cmd_y);
		cct_gotoxy(cmd_x + 1, cmd_y - max_col_count);
		for (int i = 0; i < board_size; ++i)
		{
			cct_getxy(cmd_x, cmd_y);
			for (int j = 1; j <= max_col_count - nums[i][0][1]; ++j)
			{
				cout << "   " << " " << "    ";
				cct_gotoxy(cmd_x, cmd_y + j);
			}
			cct_getxy(cmd_x, cmd_y);
			for (int j = 1; j <= nums[i][0][1]; ++j)
			{
				cout << "   " << nums[i][j][1] << "    ";
				cct_gotoxy(cmd_x, cmd_y + j);
			}
			cct_getxy(cmd_x, cmd_y);
			cmd_y = 2;
			cmd_x += 8;
			cct_gotoxy(cmd_x, cmd_y);
		}
		// 打印顶栏右侧纵向分割线
		console_put_div_line(top_left_x + board_size * 8, 2, max_col_count, 1);
		// 打印顶栏数字下方分割线
		console_put_div_line(top_left_x, max_col_count + 2, board_size * 8 - 1, 0, 0, 4, 1);
		// 打印列号
		cct_gotoxy(top_left_x, top_left_y - 1);
		cout << "║";
		for (int i = 0; i < board_size; ++i)
		{
			cout << "   " << col++;
			if (i != board_size - 1)
				cout << "    ";
			else
				cout << "   ";
		}
		cout << "║";
		// 打印列号下方分割线
		console_put_div_line(0, top_left_y, board_size, 0, max_row_count, 5, 1);
		// 打印左侧纵向分割线
		console_put_div_line(0, top_left_y + 1, board_size * 4, 1);
		// 打印侧栏数字
		cct_getxy(cmd_x, cmd_y);
		cct_gotoxy(cmd_x + 1, top_left_y + 1);
		for (int i = 0; i < board_size; ++i)
		{
			for (int r = 0; r < 4; ++r)
			{
				if (r != 1)
				{
					for (int j = 0; j < max_row_count; ++j)
					{
						cout << "    ";
					}
					cct_getxy(cmd_x, cmd_y);
					cct_gotoxy(1, cmd_y + 1);
					continue;
				}
				cout << " ";
				for (int j = 0; j < max_row_count - nums[i][0][0]; ++j)
				{
					cout << "   ";
				}
				for (int j = 1; j <= nums[i][0][0]; ++j)
				{
					cout << nums[i][j][0] << "  ";
				}
				cct_getxy(cmd_x, cmd_y);
				cct_gotoxy(1, cmd_y + 1);
			}
		}
		// 打印行号
		// ct_getxy(cmd_x, cmd_y);
		cct_gotoxy(top_left_x - 5, top_left_y + 1);
		for (int i = 0; i < board_size; ++i)
		{
			for (int r = 0; r < 4; ++r)
			{
				if (r == 1)
				{
					cout << "║  " << row++ << " ║";
				}
				else
					cout << "║    ║";
				cct_getxy(cmd_x, cmd_y);
				cct_gotoxy(cmd_x - 6, cmd_y + 1);
			}
		}
	}
	// 打印board
	// 打印顶部分割线
	if (!banner)
		console_put_div_line(top_left_x, top_left_y, board_size, 0, 0, 0, 1);
	for (int i = 0; i < board_size; ++i)
	{
		// 打印每行左侧边框线
		console_put_div_line(top_left_x, top_left_y + 1 + i * 4, 3, 1);
		for (int j = 0; j < board_size; ++j)
		{
			// cout << " ";
			if (board[i][j] == 'O')
				darw(top_left_x + 1, top_left_y + 1, j, i, 0);
			else
				darw(top_left_x + 1, top_left_y + 1, j, i, 2);
			// 打印每个球右侧边框线
			console_put_div_line(top_left_x + (j + 1) * 8, top_left_y + 1 + i * 4, 3, 1);
		}
		// 打印每行下方的边框线
		if (i != board_size - 1)
		{
			console_put_div_line(top_left_x, top_left_y + (i + 1) * 4, board_size, 0, 0, 1, 1);
		}
		else
		{
			// 打印底部边框线
			if (!banner)
				console_put_div_line(top_left_x, top_left_y + (i + 1) * 4, board_size, 0, 0, 2, 1);
			else
			{
				cct_getxy(cmd_x, cmd_y);
				cct_gotoxy(0, cmd_y);
				cout << "╚";
				for (int j = 0; j < max_row_count * 2 + 2; ++j)
				{
					cout << "═";
				}
				cout << "╩";
				cout << "════╩";
				for (int j = 0; j < board_size; ++j)
				{
					for (int k = 0; k < 7; ++k)
						cout << "═";
					if (j != board_size - 1)
					{
						cout << "╩";
					}
				}
				cout << "╝";
			}
		}
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

void put_character(const char ch, const int x, const int y)
{
	cct_gotoxy(x, y);
	switch (ch)
	{
	case 'O':
		cct_setcolor(COLOR_HBLUE, COLOR_BLACK);
		cout << "〇";
		break;
	case ' ':
		cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << "  ";
		break;
	case 'X':
		cct_setcolor(COLOR_HRED, COLOR_BLACK);
		cout << "X ";
		break;
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	return;
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void listen_event_split(const bool play, const char data_board[max_board_size][max_board_size], char input_board[max_board_size][max_board_size], const int board_size, const int nums[max_board_size][max_board_size][2])
{
	int mx, my, m_action, keycode1, keycode2;
	int ret;
	bool cheat = false;
	int top_left_x, top_left_y, bottom_y;
	char output_board[max_board_size][max_board_size];
	int max_row_count = nums[board_size][0][0], max_col_count = nums[board_size][0][1];
	top_left_x = max_row_count * 2 + 8;
	top_left_y = max_col_count + 4;
	bottom_y = top_left_y + board_size * 4;
	if (play)
	{
		for (int i = 0; i < board_size; ++i)
			for (int j = 0; j < board_size; ++j)
				output_board[i][j] = BLANK;
	}
	cct_enable_mouse();
	while (true)
	{
		ret = cct_read_keyboard_and_mouse(mx, my, m_action, keycode1, keycode2);
		cct_gotoxy(top_left_x, bottom_y + 2);
		for (int i = 0; i < 40; ++i)
			cout << ' '; // 清除之前的提示
		cct_gotoxy(top_left_x, bottom_y + 2);
		if (ret == CCT_MOUSE_EVENT) // 鼠标事件
		{
			int bx, by, goto_x, goto_y; // 在放置区域上的坐标
			bool good_pos;
			by = mx - top_left_x, bx = my - top_left_y;
			// cout << "x % 8 = " << by % 8 << " y % 4 = " << bx % 4 << endl;
			good_pos = by >= 0 && bx >= 0 && by % 8 > 0 && bx % 4 > 0;
			by /= 8, bx /= 4;
			// cout << "x = " << by << " y = " << bx << endl;
			good_pos = good_pos && by >= 0 && by < board_size && bx >= 0 && bx < board_size;
			if (!good_pos)
			{
				cout << "[当前光标] 位置非法";
				continue;
			}
			goto_x = top_left_x + bx * 8, goto_y = top_left_y + by * 4;
			switch (m_action)
			{
			case MOUSE_LEFT_BUTTON_CLICK:
				cout << "[左键按下] " << char(bx + 'A') << "行" << char(by + 'a') << "列" << endl;
				if (play)
				{
					if (input_board[bx][by] == 'O')
						input_board[bx][by] = ' ';
					else
						input_board[bx][by] = 'O';
					if (!cheat)
					{
						if (output_board[bx][by] == BLANK)
						{
							output_board[bx][by] = B_CIRCLE;
						}
						else
						{
							output_board[bx][by] = BLANK;
						}
						put_character(input_board[bx][by], goto_x, goto_y);
						cct_gotoxy(top_left_x, bottom_y + 2);
						break;
					}
					switch (output_board[bx][by])
					{
					case B_CIRCLE:
					case R_CROSS:
						cct_gotoxy(goto_x, goto_y);
						cct_setcolor(COLOR_HBLACK, COLOR_BLACK);
						cout << "〇";
						cct_setcolor(COLOR_BLACK, COLOR_WHITE);
						cct_gotoxy(top_left_x, bottom_y + 2);
						output_board[bx][by] = W_CIRCLE;
						break;
					case BLANK:
						cct_gotoxy(goto_x, goto_y);
						cct_setcolor(COLOR_HRED, COLOR_BLACK);
						cout << "〇";
						cct_setcolor(COLOR_BLACK, COLOR_WHITE);
						cct_gotoxy(top_left_x, bottom_y + 2);
						output_board[bx][by] = R_CIRCLE;
						break;
					case W_CIRCLE:
					case B_CROSS:
						put_character('O', goto_x, goto_y);
						cct_gotoxy(top_left_x, bottom_y + 2);
						output_board[bx][by] = B_CIRCLE;
						break;
					case R_CIRCLE:
						put_character(' ', goto_x, goto_y);
						cct_gotoxy(top_left_x, bottom_y + 2);
						output_board[bx][by] = BLANK;
					default:
						break;
					}
				}
				else
					return;
				break;
			case MOUSE_RIGHT_BUTTON_CLICK:
				cout << "[右键按下] " << char(bx + 'A') << "行" << char(by + 'a') << "列" << endl;
				if (play)
				{
					if (input_board[bx][by] == 'X')
						input_board[bx][by] = ' ';
					else
						input_board[bx][by] = 'X';
					if (!cheat)
					{
						if (output_board[bx][by] == BLANK)
						{
							output_board[bx][by] = R_CROSS;
						}
						else
						{
							output_board[bx][by] = BLANK;
						}
						put_character(input_board[bx][by], goto_x, goto_y);
						cct_gotoxy(top_left_x, bottom_y + 2);
						break;
					}
					switch (output_board[bx][by])
					{
					case R_CROSS:
						put_character(' ', goto_x, goto_y);
						cct_gotoxy(top_left_x, bottom_y + 2);
						output_board[bx][by] = BLANK;
						break;
					case B_CROSS:
						cct_gotoxy(goto_x, goto_y);
						cct_setcolor(COLOR_HBLACK, COLOR_BLACK);
						cout << "〇";
						cct_setcolor(COLOR_BLACK, COLOR_WHITE);
						cct_gotoxy(top_left_x, bottom_y + 2);
						output_board[bx][by] = W_CIRCLE;
						break;
					case W_CIRCLE:
					case B_CIRCLE:
						cct_gotoxy(goto_x, goto_y);
						cct_setcolor(COLOR_HBLUE, COLOR_BLACK);
						cout << "X ";
						cct_setcolor(COLOR_BLACK, COLOR_WHITE);
						cct_gotoxy(top_left_x, bottom_y + 2);
						output_board[bx][by] = B_CROSS;
						break;
					default: // BLANK R_CIRCLE
						put_character('X', goto_x, goto_y);
						cct_gotoxy(top_left_x, bottom_y + 2);
						output_board[bx][by] = R_CROSS;
						break;
					}
				}
				else
					return;
				break;
			default:
				cout << "[当前光标] " << char(bx + 'A') << "行" << char(by + 'a') << "列";
				break;
			}
		}
		if (ret == CCT_KEYBOARD_EVENT)
		{
			switch (keycode1)
			{
			case 224:
				switch (keycode2)
				{
				case KB_ARROW_UP:
					cout << "[读到上箭头]";
					break;
				case KB_ARROW_DOWN:
					cout << "[读到下箭头]";
					break;
				case KB_ARROW_LEFT:
					cout << "[读到左箭头]";
					break;
				case KB_ARROW_RIGHT:
					cout << "[读到右箭头]";
					break;
				}
				break;
			case 13:
				cout << "[读到回车键]" << endl;
				if (!play)
					return;
				break;
			case 'Y':
			case 'y':
				if (play)
				{
					if (check_win(input_board, data_board, board_size, nums))
					{
						return;
					}
				}
				else
					cout << "[读到键码] " << keycode1 << '/' << keycode2;
				break;
			case 'Q':
			case 'q':
				if (!play)
					cout << "[读到键码] " << keycode1 << '/' << keycode2;
				return;
				break;
			case 'Z':
			case 'z':
				if (cheat)
				{
					cheat = false;
					cout << "[作弊模式关]";
					for (int i = 0; i < board_size; ++i)
					{
						for (int j = 0; j < board_size; ++j)
						{
							int goto_x = top_left_x + i * 2, goto_y = top_left_y + j;
							switch (output_board[i][j])
							{
							case BLANK:
							case B_CIRCLE:
							case R_CROSS:
								break;
							case R_CIRCLE:
								put_character('O', goto_x, goto_y);
								cct_gotoxy(top_left_x, bottom_y + 2);
								output_board[i][j] = B_CIRCLE;
								break;
							case W_CIRCLE:
								put_character(' ', goto_x, goto_y);
								cct_gotoxy(top_left_x, bottom_y + 2);
								output_board[i][j] = BLANK;
								break;
							case B_CROSS:
								put_character('X', goto_x, goto_y);
								cct_gotoxy(top_left_x, bottom_y + 2);
								output_board[i][j] = R_CROSS;
								break;
							}
						}
					}
				}
				else
				{
					cheat = true;
					cout << "[作弊模式开]";
					for (int i = 0; i < board_size; ++i)
					{
						for (int j = 0; j < board_size; ++j)
						{
							int goto_x = top_left_x + j * 2, goto_y = top_left_y + i;
							switch (output_board[i][j])
							{
							case BLANK:
								if (data_board[i][j] == ' ')
									break;
								cct_gotoxy(goto_x, goto_y);
								cct_setcolor(COLOR_HBLACK, COLOR_BLACK);
								cout << "〇";
								cct_setcolor(COLOR_BLACK, COLOR_WHITE);
								cct_gotoxy(top_left_x, bottom_y + 2);
								output_board[i][j] = W_CIRCLE;
								break;
							case B_CIRCLE:
								if (data_board[i][j] == 'O')
									break;
								cct_gotoxy(goto_x, goto_y);
								cct_setcolor(COLOR_HRED, COLOR_BLACK);
								cout << "〇";
								cct_setcolor(COLOR_BLACK, COLOR_WHITE);
								cct_gotoxy(top_left_x, bottom_y + 2);
								output_board[i][j] = R_CIRCLE;
								break;
							case R_CROSS:
								if (data_board[i][j] == ' ')
									break;
								cct_gotoxy(goto_x, goto_y);
								cct_setcolor(COLOR_HBLUE, COLOR_BLACK);
								cout << "X ";
								cct_setcolor(COLOR_BLACK, COLOR_WHITE);
								cct_gotoxy(top_left_x, bottom_y + 2);
								output_board[i][j] = B_CROSS;
								break;
							default:
								break;
							}
						}
					}
					cct_setcolor(COLOR_BLACK, COLOR_WHITE);
					cct_gotoxy(top_left_x, bottom_y + 2);
				}
				break;
			default:
				cout << "[读到键码] " << keycode1 << '/' << keycode2;
			}
		}
	}
	cct_disable_mouse();
}


/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

void listen_event(const bool play, const char data_board[max_board_size][max_board_size], char input_board[max_board_size][max_board_size], const int board_size, const int nums[max_board_size][max_board_size][2])
{
	int mx, my, m_action, keycode1, keycode2;
	int ret;
	bool cheat = false;
	int top_left_x, top_left_y, bottom_right_x, bottom_right_y;
	char output_board[max_board_size][max_board_size];
	int max_row_count = nums[board_size][0][0], max_col_count = nums[board_size][0][1];
	top_left_x = max_row_count * 2 + 6;
	top_left_y = max_col_count + 5;
	bottom_right_x = top_left_x + board_size * 2 - 1;
	bottom_right_y = top_left_y + board_size - 1;
	if (play)
	{
		for (int i = 0; i < board_size; ++i)
			for (int j = 0; j < board_size; ++j)
				output_board[i][j] = BLANK;
	}
	cct_enable_mouse();
	while (true)
	{
		ret = cct_read_keyboard_and_mouse(mx, my, m_action, keycode1, keycode2);
		cct_gotoxy(top_left_x, bottom_right_y + 2);
		for (int i = 0; i < 40; ++i)
			cout << ' '; // 清除之前的提示
		cct_gotoxy(top_left_x, bottom_right_y + 2);
		if (ret == CCT_MOUSE_EVENT) // 鼠标事件
		{
			if (mx >= top_left_x && mx <= bottom_right_x && my >= top_left_y && my <= bottom_right_y)
			{
				int bx, by, goto_x, goto_y; // 在放置区域上的坐标
				by = (mx - top_left_x) / 2;
				bx = (my - top_left_y);
				goto_x = top_left_x + by * 2;
				goto_y = top_left_y + bx;
				switch (m_action)
				{
				case MOUSE_LEFT_BUTTON_CLICK:
					cout << "[左键按下] " << char(bx + 'A') << "行" << char(by + 'a') << "列" << endl;
					if (play)
					{
						if (input_board[bx][by] == 'O')
							input_board[bx][by] = ' ';
						else
							input_board[bx][by] = 'O';
						if (!cheat)
						{
							if (output_board[bx][by] == BLANK)
							{
								output_board[bx][by] = B_CIRCLE;
							}
							else
							{
								output_board[bx][by] = BLANK;
							}
							put_character(input_board[bx][by], goto_x, goto_y);
							cct_gotoxy(top_left_x, bottom_right_y + 2);
							break;
						}
						switch (output_board[bx][by])
						{
						case B_CIRCLE:
						case R_CROSS:
							cct_gotoxy(goto_x, goto_y);
							cct_setcolor(COLOR_HBLACK, COLOR_BLACK);
							cout << "〇";
							cct_setcolor(COLOR_BLACK, COLOR_WHITE);
							cct_gotoxy(top_left_x, bottom_right_y + 2);
							output_board[bx][by] = W_CIRCLE;
							break;
						case BLANK:
							cct_gotoxy(goto_x, goto_y);
							cct_setcolor(COLOR_HRED, COLOR_BLACK);
							cout << "〇";
							cct_setcolor(COLOR_BLACK, COLOR_WHITE);
							cct_gotoxy(top_left_x, bottom_right_y + 2);
							output_board[bx][by] = R_CIRCLE;
							break;
						case W_CIRCLE:
						case B_CROSS:
							put_character('O', goto_x, goto_y);
							cct_gotoxy(top_left_x, bottom_right_y + 2);
							output_board[bx][by] = B_CIRCLE;
							break;
						case R_CIRCLE:
							put_character(' ', goto_x, goto_y);
							cct_gotoxy(top_left_x, bottom_right_y + 2);
							output_board[bx][by] = BLANK;
						default:
							break;
						}
					}
					else
						return;
					break;
				case MOUSE_RIGHT_BUTTON_CLICK:
					cout << "[右键按下] " << char(bx + 'A') << "行" << char(by + 'a') << "列" << endl;
					if (play)
					{
						if (input_board[bx][by] == 'X')
							input_board[bx][by] = ' ';
						else
							input_board[bx][by] = 'X';
						if (!cheat)
						{
							if (output_board[bx][by] == BLANK)
							{
								output_board[bx][by] = R_CROSS;
							}
							else
							{
								output_board[bx][by] = BLANK;
							}
							put_character(input_board[bx][by], goto_x, goto_y);
							cct_gotoxy(top_left_x, bottom_right_y + 2);
							break;
						}
						switch (output_board[bx][by])
						{
						case R_CROSS:
							put_character(' ', goto_x, goto_y);
							cct_gotoxy(top_left_x, bottom_right_y + 2);
							output_board[bx][by] = BLANK;
							break;
						case B_CROSS:
							cct_gotoxy(goto_x, goto_y);
							cct_setcolor(COLOR_HBLACK, COLOR_BLACK);
							cout << "〇";
							cct_setcolor(COLOR_BLACK, COLOR_WHITE);
							cct_gotoxy(top_left_x, bottom_right_y + 2);
							output_board[bx][by] = W_CIRCLE;
							break;
						case W_CIRCLE:
						case B_CIRCLE:
							cct_gotoxy(goto_x, goto_y);
							cct_setcolor(COLOR_HBLUE, COLOR_BLACK);
							cout << "X ";
							cct_setcolor(COLOR_BLACK, COLOR_WHITE);
							cct_gotoxy(top_left_x, bottom_right_y + 2);
							output_board[bx][by] = B_CROSS;
							break;
						default: // BLANK R_CIRCLE
							put_character('X', goto_x, goto_y);
							cct_gotoxy(top_left_x, bottom_right_y + 2);
							output_board[bx][by] = R_CROSS;
							break;
						}
					}
					else
						return;
					break;
				default:
					cout << "[当前光标] " << char(bx + 'A') << "行" << char(by + 'a') << "列";
					break;
				}
			}
			else
				cout << "[当前光标] 位置非法";
		}
		if (ret == CCT_KEYBOARD_EVENT)
		{
			switch (keycode1)
			{
			case 224:
				switch (keycode2)
				{
				case KB_ARROW_UP:
					cout << "[读到上箭头]";
					break;
				case KB_ARROW_DOWN:
					cout << "[读到下箭头]";
					break;
				case KB_ARROW_LEFT:
					cout << "[读到左箭头]";
					break;
				case KB_ARROW_RIGHT:
					cout << "[读到右箭头]";
					break;
				}
				break;
			case 13:
				cout << "[读到回车键]" << endl;
				if (!play)
					return;
				break;
			case 'Y':
			case 'y':
				if (play)
				{
					if (check_win(input_board, data_board, board_size, nums))
					{
						return;
					}
				}
				else
					cout << "[读到键码] " << keycode1 << '/' << keycode2;
				break;
			case 'Q':
			case 'q':
				if (!play)
					cout << "[读到键码] " << keycode1 << '/' << keycode2;
				return;
				break;
			case 'Z':
			case 'z':
				if (cheat)
				{
					cheat = false;
					cout << "[作弊模式关]";
					for (int i = 0; i < board_size; ++i)
					{
						for (int j = 0; j < board_size; ++j)
						{
							int goto_x = top_left_x + i * 2, goto_y = top_left_y + j;
							switch (output_board[i][j])
							{
							case BLANK:
							case B_CIRCLE:
							case R_CROSS:
								break;
							case R_CIRCLE:
								put_character('O', goto_x, goto_y);
								cct_gotoxy(top_left_x, bottom_right_y + 2);
								output_board[i][j] = B_CIRCLE;
								break;
							case W_CIRCLE:
								put_character(' ', goto_x, goto_y);
								cct_gotoxy(top_left_x, bottom_right_y + 2);
								output_board[i][j] = BLANK;
								break;
							case B_CROSS:
								put_character('X', goto_x, goto_y);
								cct_gotoxy(top_left_x, bottom_right_y + 2);
								output_board[i][j] = R_CROSS;
								break;
							}
						}
					}
				}
				else
				{
					cheat = true;
					cout << "[作弊模式开]";
					for (int i = 0; i < board_size; ++i)
					{
						for (int j = 0; j < board_size; ++j)
						{
							int goto_x = top_left_x + j * 2, goto_y = top_left_y + i;
							switch (output_board[i][j])
							{
							case BLANK:
								if (data_board[i][j] == ' ')
									break;
								cct_gotoxy(goto_x, goto_y);
								cct_setcolor(COLOR_HBLACK, COLOR_BLACK);
								cout << "〇";
								cct_setcolor(COLOR_BLACK, COLOR_WHITE);
								cct_gotoxy(top_left_x, bottom_right_y + 2);
								output_board[i][j] = W_CIRCLE;
								break;
							case B_CIRCLE:
								if (data_board[i][j] == 'O')
									break;
								cct_gotoxy(goto_x, goto_y);
								cct_setcolor(COLOR_HRED, COLOR_BLACK);
								cout << "〇";
								cct_setcolor(COLOR_BLACK, COLOR_WHITE);
								cct_gotoxy(top_left_x, bottom_right_y + 2);
								output_board[i][j] = R_CIRCLE;
								break;
							case R_CROSS:
								if (data_board[i][j] == ' ')
									break;
								cct_gotoxy(goto_x, goto_y);
								cct_setcolor(COLOR_HBLUE, COLOR_BLACK);
								cout << "X ";
								cct_setcolor(COLOR_BLACK, COLOR_WHITE);
								cct_gotoxy(top_left_x, bottom_right_y + 2);
								output_board[i][j] = B_CROSS;
								break;
							default:
								break;
							}
						}
					}
					cct_setcolor(COLOR_BLACK, COLOR_WHITE);
					cct_gotoxy(top_left_x, bottom_right_y + 2);
				}
				break;
			default:
				cout << "[读到键码] " << keycode1 << '/' << keycode2;
			}
		}
	}
	cct_disable_mouse();
}

void pullze_console(const bool banner, const bool mouse, const bool play)
{
	int board_size;
	char data_board[max_board_size][max_board_size], input_board[max_board_size][max_board_size];
	int nums[max_board_size][max_board_size][2]; // 每行/列球的个数
	int cmd_x = 0, cmd_y = 0;
	initGame(&board_size, data_board, input_board, nums);
	cct_cls();
	cct_setconsoleborder(70, 32, 140, 64);
	cct_setfontsize("新宋体", 26);
	if (play)
	{
		cout << "左键选〇，右键选X ，Y/y提交，Z/z作弊，Q/q退出";
	}
	if (play)
	{
		console_display(input_board, board_size, nums, banner);
	}
	else
		console_display(data_board, board_size, nums, banner);
	if (mouse)
	{
		listen_event(play, data_board, input_board, board_size, nums);
	}
	return;
}

void pullze_console_split(const bool banner, const bool mouse, const bool play)
{
	int board_size;
	char data_board[max_board_size][max_board_size], input_board[max_board_size][max_board_size];
	int nums[max_board_size][max_board_size][2]; // 每行/列球的个数
	int cmd_x = 0, cmd_y = 0;
	initGame(&board_size, data_board, input_board, nums);
	cct_cls();
	cct_setfontsize("新宋体", 10 + (15 - board_size));
	cct_setconsoleborder(150, 150, 300, 300);
	if (play)
	{
		console_display_split(input_board, board_size, nums, banner);
	}
	else
		console_display_split(data_board, board_size, nums, banner);
	if (mouse)
	{
		if (play)
		{
			cout << "左键选〇，右键选X ，Y/y提交，Z/z作弊，Q/q退出";
		}
		else cout << "测试键盘/鼠标左键/右键，按回车退出";
		listen_event_split(play, data_board, input_board, board_size, nums);
	}
	return;
}
