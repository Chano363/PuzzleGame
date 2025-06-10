/* 学号 姓名 班级 */

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

/* 提示：空文件，仅为了提醒你不要忘记首行 && 不要把文件名弄错 */

#include "cmd_console_tools.h"
#include <iostream>

using namespace std;

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void putDivLine(const int x,const int y,const int length,const int dir = 0, const char ch = '-')
{
	cct_gotoxy(x, y);
	if (dir == 0) // 横向分割线
		for (int i = 0; i < length; ++i) cout << ch;
	else
		for (int i = 0; i < length; ++i)
		{
			cout << ch;
			cct_gotoxy(x, y + i + 1);
		}
	return;
}