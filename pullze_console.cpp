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
	// ╠═════════════════════╣ 种类2
	// ╔══════╦═════╬════════╣ 种类3
	// ╚══════╩═════╩════════╝ 种类4
	
	cct_gotoxy(x, y);
	// cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
	if (dir == 0)
	{
		switch (category)
		{
		case 0: {
			cout << "╔";
			for (int i = 0; i < length * 2; ++i)
			{
				cout << "═";
			}
			cout << "╗";
			break;
		}
		case 1: {
			cout << "╚";
			for (int i = 0; i < length * 2; ++i)
			{
				cout << "═";
			}
			cout << "╝";
			break;
		}
		case 2: {
			cout << "╠";
			for (int i = 0; i < length * 2; ++i)
			{
				cout << "═";
			}
			cout << "╣";
			break;
		}
		case 3: {
			cout << "╔";
			for (int i = 0; i < max_count * 2 + 1; ++i)
			{
				cout << "=";
			}
			cout << "╦══╬";
			for (int i = 0; i < length * 2; ++i)
			{
				cout << "=";
			}
			cout << "╣";
			break;
		}
		case 4: {
			cout << "╚";
			for (int i = 0; i < max_count * 2 + 1; ++i)
			{
				cout << "=";
			}
			cout << "╩══╩";
			for (int i = 0; i < length * 2; ++i)
			{
				cout << "=";
			}
			cout << "╝";
			break;
		}
		default:
			break;
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

int* console_display(const char board[max_board_size][max_board_size],const int board_size,const int nums[max_board_size][max_board_size][2],const int banner)
{
	char col = 'a', row = 'A';
	int max_col_count = -1, max_row_count = -1; // 行/列的最大数量
	int board_pos[5]; // 记录board的左上角右下角的坐标;
	if (banner)
	{
		for (int i = 0; i < board_size; ++i) max_row_count = max_row_count > nums[i][0][0] ? max_row_count : nums[i][0][0];
		for (int i = 0; i < board_size; ++i) max_col_count = max_col_count > nums[i][0][1] ? max_col_count : nums[i][0][1];
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
		console_put_div_line(cmd_x , cmd_y, max_col_count, 1);
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
				// cct_gotoxy(cmd_x + j + 1, cmd_y);
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
	else {
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
	if (!banner)cct_gotoxy(3, cmd_y);
	else {
		cct_getxy(cmd_x, cmd_y);
		cct_gotoxy(cmd_x, cmd_y - board_size);
		board_pos[0] = cmd_x;
		board_pos[1] = cmd_y - board_size;
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
			else cout << "  ";
		}		
		cct_getxy(cmd_x, cmd_y);
		/*if (!banner)cct_gotoxy(3, cmd_y + 1);
		else*/ 
		cct_gotoxy(cmd_x - board_size * 2, cmd_y + 1);
	}
	cct_getxy(cmd_x, cmd_y);
	board_pos[2] = cmd_x + board_size * 2 - 1;
	board_pos[3] = cmd_y - 1;
	if (banner) {
		// 打印右侧边框
		console_put_div_line(cmd_x + board_size * 2, cmd_y - board_size, board_size, 1);
		// 打印底部框线
		console_put_div_line(0, cmd_y, board_size, 0, max_row_count, 4);
	}
	else {
		// 打印右侧边框
		console_put_div_line(3 + board_size * 2, cmd_y - board_size, board_size, 1);
		// 打印底部框线
		cct_getxy(cmd_x, cmd_y);
		console_put_div_line(2, cmd_y, board_size, 0, 0, 1);
	}
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	return board_pos;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

void listen_event(const int top_left_x,const int top_left_y,const int bottom_right_x,const int bottom_right_y)
{
	int mx, my, m_action, keycode1, keycode2;
	int ret;
	bool worked = false;
	
	cct_enable_mouse();
	while (true)
	{
		ret = cct_read_keyboard_and_mouse(mx,my, m_action, keycode1, keycode2);
		cct_gotoxy(top_left_x, bottom_right_y + 2);
		for (int i = 0; i < 40; ++i)cout << ' '; // 清除之前的提示
		cct_gotoxy(top_left_x, bottom_right_y + 2);
		if (ret == CCT_MOUSE_EVENT) // 鼠标事件
		{
			if (mx >= top_left_x && mx <= bottom_right_x && my >= top_left_y && my <= bottom_right_y)
			{
				mx = (mx - top_left_x) / 2;
				my = (my - top_left_y);
				switch (m_action)
				{
				case MOUSE_LEFT_BUTTON_CLICK:
					cout << "[左键按下] " << char(my + 'A') << "行" << char(mx + 'a') << "列" << endl;
					return;
				case MOUSE_RIGHT_BUTTON_CLICK:
					cout << "[右键按下] " << char(my + 'A') << "行" << char(mx + 'a') << "列" << endl;
					return;
				default:
					cout << "[当前光标] " << char(my + 'A') << "行" << char(mx + 'a') << "列";
					break;
				}
			}
			else cout << "[当前光标] 位置非法";
		}
		if (ret == CCT_KEYBOARD_EVENT)
		{
			switch (keycode1) {
			case 224:
				switch (keycode2) {
				case KB_ARROW_UP: cout << "[读到上箭头]"; break;
				case KB_ARROW_DOWN: cout << "[读到下箭头]"; break;
				case KB_ARROW_LEFT: cout << "[读到左箭头]"; break;
				case KB_ARROW_RIGHT: cout << "[读到右箭头]"; break;
				}
				break;
			case 13: cout << "[读到回车键]" << endl; return;
			default: cout << "[读到键码] " << keycode1 << '/' << keycode2;
			}
		}
	}
	cct_disable_mouse();
}

void pullze_console(const bool banner,const bool mouse) {
	int board_size;
	char data_board[max_board_size][max_board_size], input_board[max_board_size][max_board_size];
	int nums[max_board_size][max_board_size][2]; // 每行/列球的个数
	int cmd_x = 0, cmd_y = 0;
	int* board_pos,top_left_x, top_left_y, bottom_right_x, bottom_right_y;
	initGame(&board_size, data_board, input_board, nums);
	cct_cls();
	cct_setconsoleborder(70, 32, 140, 64);
	cct_setfontsize("新宋体", 26);
	board_pos = console_display(data_board, board_size, nums, banner);
	top_left_x = board_pos[0], top_left_y = board_pos[1], bottom_right_x = board_pos[2], bottom_right_y = board_pos[3];
	if (mouse)
	{
		listen_event(top_left_x, top_left_y, bottom_right_x, bottom_right_y);
	}
	return;
}