/* 学号 姓名 班级 */
#pragma once

/* 提示：空文件，仅为了提醒你不要忘记首行 && 不要把文件名弄错 */
#include <time.h>
#include <cmath>
#include <iostream>
#include <windows.h>

#include "cmd_console_tools.h"


const int max_board_size = 15;

char menu();
void end_wait();
bool check_win(const char input[max_board_size][max_board_size],const char data[max_board_size][max_board_size],const int size);
void initGame(int* board_size, char data_board[max_board_size][max_board_size], char input_board[max_board_size][max_board_size], int nums[max_board_size][max_board_size][2]);
void generateBalls(char board[max_board_size][max_board_size], const int board_size, int nums[max_board_size][max_board_size][2]);

void pullze_base(const bool banner, const bool play);

void pullze_console(const bool banner);
