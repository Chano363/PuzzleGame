/* ѧ�� ���� �༶ */

#pragma once
#include "cmd_console_tools.h"
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <ctime>
#include <iomanip>

// pullze_tools �еĺ���
char menu(); // ��ʾ���ܲ˵�����ȡ�û�ѡ�õĹ���
void end_wait(); // �ȴ��û�����"End"����
int input_size(); // ��ȡ�����С
bool check_win(int *array); // ����Ƿ�ʤ��
void generate_array(int *array); // ���ɳ�ʼ����
void anaylse_array(int *array, int row[][10], int col[][10]); // ����ÿ��ÿ��С���������������

// pullze_base �еĺ���
void pullze_base(bool hint = 0, bool play = 0);

// pullze_console �еĺ���
void pullze_console(bool boarder = 0, bool hint = 0, bool listen = 0, bool play = 0);