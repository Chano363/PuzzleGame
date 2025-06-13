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
char menu() 
{
    cout << "---------------------------------------------------------" << endl;
    cout << " A.内部数组，原样输出" << endl;
    cout << " B.内部数组，生成提示行列并输出" << endl;
    cout << " C.内部数组，游戏版" << endl;
    cout << " --------------------------------------------------------" << endl;
    cout << " D.n*n的框架(无分隔线)，原样输出" << endl;
    cout << " E.n*n的框架(无分隔线)，含提示行列" << endl;
    cout << " F.n*n的框架(无分隔线)，显示初始状态，鼠标移动可显示坐标" << endl;
    cout << " G.cmd图形界面完整版(无分隔线)" << endl;
    cout << " --------------------------------------------------------" << endl;
    cout << " H.n*n的框架(有分隔线)，原样输出" << endl;
    cout << " I.n*n的框架(有分隔线)，含提示行列" << endl;
    cout << " J.n*n的框架(有分隔线)，显示初始状态，鼠标移动可显示坐标" << endl;
    cout << " K.cmd图形界面完整版(有分隔线)" << endl;
    cout << " --------------------------------------------------------" << endl;
    cout << " Q.退出" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "[请选择:] ";

    char c;
    while (1) {
        c = getchar();
        if ((c >= 'A' && c <= 'K') || (c >= 'a' && c <= 'k') || c == 'Q' || c == 'q') break;
    }
    putchar(c);
    putchar('\n');
    Sleep(200);
    return (c >= 'a' && c <= 'z') ? (c - 'a' + 'A') : c; // 转换为大写
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

void end_wait() {
    char buf[100] = { 0 };
    int x, y;
    cct_getxy(x, y);
    cin.ignore(100, '\n');

    while (1) {
        cct_gotoxy(x, y);
        cout << "                                ";
        cct_gotoxy(x, y);
        cout << "本小题结束，请输入End继续...";
        cin.getline(buf, 100, '\n');
        if (strlen(buf) == 3) {
            buf[0] = tolower(buf[0]), buf[1] = tolower(buf[1]), buf[2] = tolower(buf[2]);
            if (strcmp(buf, "end") == 0) break;
        }
        cin.clear();
        cct_gotoxy(x, y + 1);
        cout << "输入错误，请重新输入..." << endl;
    }
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/

bool check_win(const char input_board[max_board_size][max_board_size],const char data_board[max_board_size][max_board_size],const int board_size,const int nums[max_board_size][max_board_size][2])
{
	// 不相同但数量符合要求
	int nums_[max_board_size][max_board_size];
	bool lose1 = false;
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 0; j < board_size; ++j)
		{
			nums_[i][j] = 0;
		}
	}
	for (int i = 0; i < board_size && !lose1; ++i)
	{
		int cntConsecutive = (input_board[i][0] == 'O' ? 1 : 0);
		for (int j = 0; j < board_size; ++j)
		{
			if (input_board[i][j] != 'O' && input_board[i][j + 1] == 'O')
			{
				if (nums_[i][cntConsecutive] != nums[i][cntConsecutive][0]) {
					lose1 = true;
					break;
				}
				cntConsecutive++;
			}
			if (input_board[i][j] == 'O') {
				nums_[i][cntConsecutive];
			}
		}
	}
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 0; j < board_size; ++j)
		{
			nums_[i][j] = 0;
		}
	}
	for (int i = 0; i < board_size && !lose1; ++i)
	{
		int cntConsecutive = (input_board[0][i] == 'O' ? 1 : 0);
		for (int j = 0; j < board_size; ++j)
		{
			if (input_board[j][i] != 'O' && input_board[j + 1][i] == 'O') {
				if (nums_[i][cntConsecutive] != nums[i][cntConsecutive][1])
					lose1 = true;
				cntConsecutive++;
			}
			if (input_board[j][i] == 'O') {
				nums_[i][cntConsecutive] ++;
			}
		}
	}
	if (!lose1)
	{
		cout << endl << "提交成功，游戏结束" << endl;
		return true;
	}
    for (int i = 0; i < board_size; ++i)
    {
        for (int j = 0; j < board_size; ++j)
        {
            if (input_board[i][j] != data_board[i][j])
            {
                cout << "提交错误，[" << (char)('A' + i) << "]行[" << (char)('a' + j) << "列不符合要求" << endl;
                return false;
            }
        }
    }
    cout << endl << "提交成功，游戏结束" << endl;
    return true;
}

/***************************************************************************
  函数名称：
  功    能：随机生成初始时球的位置
  输入参数：
		   char board[][]: 区域数据
		   const int board_size: 区域大小
  返 回 值：无
  说    明：
***************************************************************************/

void generateBalls(char board[max_board_size][max_board_size], const int board_size, int nums[max_board_size][max_board_size][2])
{
	long num = board_size * board_size;
	if (num % 2 == 0) num = num / 2; else num = (num + 1) / 2;
	int count = 0;
	srand((unsigned int)time(NULL));
	while (count < num)
	{
		int x = rand() % board_size, y = rand() % board_size;
		while (board[x][y] != ' ')
		{
			x = rand() % board_size; y = rand() % board_size;
		}
		board[x][y] = 'O';
		count++;
	}
#ifndef NODEBUG
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 0; j < board_size; ++j)
		{
			cout << board[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
#endif
	int max_row_num = 0, max_col_num = 0; // 行/列连续数字的最大数量
	for (int i = 0; i < board_size; ++i)
	{
		int cntConsecutive = (board[i][0] == 'O' ? 1 : 0);
		for (int j = 0; j < board_size; ++j)
		{
			if (board[i][j] != 'O' && board[i][j + 1] == 'O') cntConsecutive++;
			if (board[i][j] == 'O') {
				nums[i][cntConsecutive][0] ++;
			}
		}
		nums[i][0][0] = cntConsecutive; // nums[i][0] 存放数字个数
		max_row_num = max_row_num > cntConsecutive ? max_row_num : cntConsecutive;
	}
	for (int i = 0; i < board_size; ++i)
	{
		int cntConsecutive = (board[0][i] == 'O' ? 1 : 0);
		for (int j = 0; j < board_size; ++j)
		{
			if (board[j][i] != 'O' && board[j + 1][i] == 'O') cntConsecutive++;
			if (board[j][i] == 'O') {
				nums[i][cntConsecutive][1] ++;
			}
		}
		nums[i][0][1] = cntConsecutive; // nums[i][0] 存放数字个数
		max_col_num = max_col_num > cntConsecutive ? max_col_num : cntConsecutive;
	}
	nums[board_size][0][0] = max_row_num;
	nums[board_size][0][1] = max_col_num;
#ifndef NODEBUG
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 1; j <= nums[i][0][0]; ++j)
			cout << nums[i][j][0] << ' ';
		cout << endl;
	}
	cout << endl;
	for (int i = 0; i < board_size; ++i)
	{
		for (int j = 1; j <= nums[i][0][1]; ++j)
			cout << nums[i][j][1] << ' ';
		cout << endl;
	}
#endif
	return;
}

/***************************************************************************
  函数名称：
  功    能: 初始化
  输入参数：
		   const char board: 区域数据
		   const int board_size: 区域大小
  返 回 值：无
  说    明：
***************************************************************************/

void initGame(int* board_size, char data_board[max_board_size][max_board_size], char input_board[max_board_size][max_board_size], int nums[max_board_size][max_board_size][2])
{

	cout << "请输入数据区大小(5/10/15)" << endl;
	cin >> *board_size;
	bool flag = false;
	while (true) {
		for (int i = 1; i <= 3; i++)
		{
			if (*board_size == 5 * i) { flag = true; break; }
		}
		if (flag) break;
		cct_cls();
		cout << "请输入重新输入数据区大小(5/10/15)" << endl;
		cin >> *board_size;
	}
	for (int i = 0; i < max_board_size; i++) {
		for (int j = 0; j < max_board_size; j++) {
			data_board[i][j] = ' ';
			input_board[i][j] = ' ';
			nums[i][j][0] = 0;
			nums[i][j][1] = 0;
		}
	}
	generateBalls(data_board, *board_size, nums);
}
