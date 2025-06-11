/* 学号 姓名 班级 */

#include "pullze.h"
using namespace std;

// 输出分割线
void split_line(int size, int max_row = 0, bool head = 0) {
    // 分割线样式：

    // max_row = 4, head = false
    // ---------+-+-----------+-----------+
    //  2 1 3 4 |A| O  O O  O | O   O   O |

    // head = true (表头的两行分割线，没有行号)
    // -----------+-----------+-----------+
    //            | 2 3 1 5 3 | 4 2 1 1 1 |

    // max_row = 0, head = false
    // +-+-----------+
    // |A| O  O O  O |

    // 左边每行连续个数的空隙
    for (int i = 0; i < max_row; ++i) cout << "--";
    if (max_row > 0) cout << '-';

    // 行号上面的框
    cout << (head && max_row > 0 ? '-' : '+') << "-+";

    // 小球上面的框
    for (int i = 0; i < size; ++i) {
        cout << "--";
        if (i % 5 == 4) cout << "-+";
    }
    cout << endl;
}

// hint: 是否有提示行列
// play = 1: 交互游戏，无作弊
// play = 2: 交互游戏，有作弊
void array_print(int *array, bool hint = 0, int play = 0) {
    int size = array[0];
    int row[16][10] = {0}, col[16][10] = {0};
    anaylse_array(array, row, col);
    int max_row = 0, max_col = 0;
    for (int i = 0; i < size; ++i) {
        if (row[i][0] > max_row) max_row = row[i][0];
        if (col[i][0] > max_col) max_col = col[i][0];
    }
    if (!hint) max_row = max_col = 0; // 如果没有提示行列，则不显示

    if (hint) {
        split_line(size, max_row, 1);
        for (int i = 0; i < max_col; ++i) {
            for (int j = 0; j < max_row * 2 + 1 + 2; ++j) cout << ' ';
            cout << '|';
            for (int j = 0; j < size; ++j) {
                int index = max_col - i; // 目前是从下到上第几行
                // 输出的时候是从上到下，所以是反着的
                if (index <= col[j][0]) cout << setw(2) << col[j][col[j][0] - index + 1];
                else cout << "  ";
                if (j % 5 == 4) cout << " |";
            }
            cout << endl;
        }
        split_line(size, max_row, 1);
    }
    else split_line(size);

    // 列号表头
    if (hint) for (int j = 0; j < max_row * 2 + 1 + 2; ++j) cout << ' ';
    else cout << "| ";
    cout << '|';
    for (int i = 0; i < size; ++i) {
        cout << ' ' << char('a' + i);
        if (i % 5 == 4) cout << " |"; // 每5个列后输出一个分隔符
    }
    cout << endl;
    split_line(size, max_row);
    
    for (int i = 0; i < size; ++i) {
        // 输出每行每组连续小球长度
        for (int j = 0; j < max_row; ++j) {
            int index = max_row - j;
            if (index <= row[i][0]) cout << setw(2) << row[i][row[i][0] - index + 1];
            else cout << "  ";
        }
        if (hint) cout << ' ';
        // 行号表头
        cout << "|" << char('A' + i) << '|';
        // 输出每行每列小球
        for (int j = 0; j < size; ++j) {
            int ball = array[i * size + j + 1] % 2; // 实际有无小球
            int player = array[i * size + j + 1] / 2; // 用户是否选择此处有小球
            if (play == 0) cout << (ball ? " O" : "  "); // 原样输出
            else if (play == 1) { // 交互游戏，无作弊
                cout << ' ';
                if (player) cct_setcolor(COLOR_HYELLOW, COLOR_HBLUE), cout << "O", cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                else cout << ' ';
            }
            else if (play == 2) { // 有作弊
                cout << ' ';
                if (player) cct_setcolor(COLOR_HYELLOW, COLOR_HBLUE), cout << (ball ? 'O' : 'X'), cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                else cout << (ball ? 'O' : ' ');
            }
            if (j % 5 == 4) cout << " |"; // 每5个小球后输出一个分隔符
        }
        cout << endl;
        if (i % 5 == 4) split_line(size, max_row); // 每5行输出一条分隔线
    }
    cout << endl;
}

// -1: 退出
// -2: 提交
// -3: 作弊
// 其他：选中的小球位置
int get_opt(int size) {
    char buf[30];
    while (1) {
        cout << endl;
        cout << "命令形式：Aa=等价于图形游戏中鼠标左键选择Aa位(区分大小写)" << endl;
        cout << "            不需要支持图形界面的右键打叉，再次输入Aa相当于清除" << endl;
        cout << "        X/x=退出(新行仅有X/x，不分大小写)" << endl;
        cout << "        Y/y=提交(新行仅有Y/y，不分大小写)" << endl;
        cout << "        Z/z=作弊(新行仅有Z/z，不分大小写)" << endl;
        cout << "        Ctrl+c 强制退出" << endl;
        cout << "请输入 : ";
        char opt;
        int tot = 0;
        while ((opt = _getch()) != '\r' && tot < 19) {
            if (opt == 3) exit(-1);
            if (opt > 32 && opt < 127) {
                buf[tot++] = opt;
                putchar(opt);
            }
        }
        buf[tot] = '\0';
        if ((buf[0] == 'X' || buf[0] == 'x') && buf[1] == '\0') return -1;
        if ((buf[0] == 'Y' || buf[0] == 'y') && buf[1] == '\0') return -2;
        if ((buf[0] == 'Z' || buf[0] == 'z') && buf[1] == '\0') return -3;
        if (buf[0] >= 'A' && buf[0] <= 'A' + size - 1 && buf[1] >= 'a' && buf[1] <= 'a' + size - 1 && buf[2] == '\0') {
            return (buf[0] - 'A') * size + (buf[1] - 'a') + 1; // 返回位置
        }
        cout << "输入错误" << endl;
    }
}

void pullze_base(bool hint, bool play) {
    int array[300] = {0};
    generate_array(array);
    cout << "初始数组：" << endl;
    array_print(array, hint, play);

    if (!play) return;

    bool cheat = 0;
    int size = array[0];
    while (1) {
        int opt = get_opt(size);
        if (opt == -1) {
            cout << endl;
            return; // 退出
        }
        if (opt == -2) {
            bool win = check_win(array);
            if (win) {
                cout << endl << "提交成功，游戏结束" << endl;
                return;
            }
            else {
                cout << endl << "提交错误, 可用作弊模式查看" << endl;
                continue;
            }
        }
        if (opt == -3) {
            cout << endl << "输入Z/z后：" << endl;
            cheat ^= 1;
            array_print(array, 1, cheat + 1);
            continue;
        }
        int x = (opt - 1) / size; // 行
        int y = (opt - 1) % size; // 列
        cout << endl << "输入" << char('A' + x) << char('a' + y) << "后：" << endl;
        if (array[opt] / 2 == 0) array[opt] += 2; // 用户选择此处有小球
        else array[opt] -= 2; // 用户选择此处无小球
        array_print(array, 1, cheat + 1);
    }
}