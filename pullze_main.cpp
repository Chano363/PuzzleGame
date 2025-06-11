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

int main()
{

	cct_setcursor(CURSOR_VISIBLE_NORMAL);
	cct_setfontsize("新宋体", 16);
	cct_setconsoleborder(120, 50, 120, 200);
	cct_setcolor(COLOR_BLACK, COLOR_WHITE);
	cct_cls();

	bool user_quit = 0;
	while (!user_quit) {
		cct_setcursor(CURSOR_VISIBLE_NORMAL);
		cct_setfontsize("新宋体", 16);
		cct_setconsoleborder(120, 50, 120, 200);
		cct_setcolor(COLOR_BLACK, COLOR_WHITE);
		cct_cls();
		char user_choice = menu();

		cct_cls();
		switch (user_choice) {
		case 'A': pullze_base(0,0); break;
		case 'B': pullze_base(1,0); break;
		case 'C': pullze_base(1,1); break;
		case 'D': pullze_console(); break;
		case 'E': pullze_console(); break;
		case 'F': pullze_console(); break;
		case 'G': pullze_console(); break;
		case 'H': pullze_console(); break;
		case 'I': pullze_console(); break;
		case 'J': pullze_console(); break;
		case 'K': pullze_console(); break;
		case 'Q': user_quit = 1; break;
		}
		if (user_choice != 'Q') end_wait();
	}

	cct_gotoxy(0, 23);
	system("pause");

}