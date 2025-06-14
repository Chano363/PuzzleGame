/* 学号 姓名 班级 */

#pragma once
#include "cmd_console_tools.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <iomanip>

// pullze_tools 中的函数
char menu(); // 显示功能菜单，读取用户选用的功能
void end_wait(); // 等待用户输入"End"结束
int input_size(); // 获取区域大小
bool check_win(int *array); // 检查是否胜利
void generate_array(int *array); // 生成初始数组
void anaylse_array(int *array, int row[][10], int col[][10]); // 分析每行每列小球的连续个数数组

// pullze_base 中的函数
void pullze_base(bool hint = 0, bool play = 0);

// pullze_console 中的函数
void pullze_console(bool boarder = 0, bool hint = 0, bool listen = 0, bool play = 0);