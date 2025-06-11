/* 学号 姓名 班级 */

#include "pullze.h"
using namespace std;

// 显示功能菜单，读取用户选用的功能
char menu() {
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
        c = _getch();
        if ((c >= 'A' && c <= 'K') || (c >= 'a' && c <= 'k') || c == 'Q' || c == 'q') break;
    }
    putchar(c);
    putchar('\n');
    Sleep(200);
    return (c >= 'a' && c <= 'z') ? (c - 'a' + 'A') : c; // 转换为大写
}

// 等待用户输入"End"结束
void end_wait() {
    char buf[100] = {0};
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

// 获取区域大小
int input_size() {
    int size;
    do {
        while (1) {
            cout << "请输入区域大小(5/10/15) ：";
            if (cin >> size) break;
            cin.clear();
        }
    } while (size != 5 && size != 10 && size != 15);
    return size;
}

// 数组第一个数为尺寸，后面的为二维数组展平后某位置是否有球
// 二进制第一位 (x % 2)：0 表示没有球，1 表示有球
// 二进制第二位 (x / 2 % 2)：0 用户未选择此位置有球，1 用户选择此位置有球
// 二进制第三位 (x / 4 % 2)：1 用户选择此位置无球 (打X) 0 用户未选择此位置无球
// 第三位用处不大，仅用于后面图形界面记录打X操作
void generate_array(int *array) {
    int size = input_size();
    array[0] = size;

    int tot = (size * size + 1) / 2; 
    // size 为奇数，直接加一除二就是上取整
    
    for (int i = 1; i <= tot; ++i) array[i] = 0;
    while (tot) {
        int x = rand() % size;
        int y = rand() % size;
        if (!array[x * size + y + 1]) {
            array[x * size + y + 1] = 1;
            tot--;
        }
    }
}

// 分析每行每列小球的连续个数数组
void anaylse_array(int *array, int row[][10], int col[][10]) {
    int size = array[0];

    // 每行数组第一个数(index 0)表示有几组连续小球，后面的数表示每组的长度
    for (int i = 0; i < size; ++i) {
        int &tot = row[i][0];
        tot = 0;
        int count = 0;
        for (int j = 0; j < size; ++j) {
            if (array[i * size + j + 1] % 2) count++;
            else {
                if (count > 0) row[i][++tot] = count;
                count = 0;
            }
        }
        if (count > 0) row[i][++tot] = count;
        if (tot == 0) row[i][++tot] = 0; // 如果没有小球，至少有一个0
    }

    // 每列数组第一个数(index 0)表示有几组连续小球，后面的数表示每组的长度
    for (int j = 0; j < size; ++j) {
        int &tot = col[j][0];
        tot = 0;
        int count = 0;
        for (int i = 0; i < size; ++i) {
            if (array[i * size + j + 1] % 2) count++;
            else {
                if (count > 0) col[j][++tot] = count;
                count = 0;
            }
        }
        if (count > 0) col[j][++tot] = count;
        if (tot == 0) col[j][++tot] = 0; // 如果没有小球，至少有一个0
    }
}

bool check_win(int *array) {
    int num_sol[10], num_player[10]; // 某行或某列每组连续小球个数，用于检查
    int size = array[0];

    for (int i = 0; i < size; ++i) {
        int sol_tot = 0, player_tot = 0;
        int sol_count = 0, player_count = 0;

        for (int j = 0; j < size; ++j) {
            int ball = array[i * size + j + 1] % 2; // 实际有无小球
            int player = array[i * size + j + 1] / 2 % 2; // 用户是否选择此处有小球
            // 统计实际连续小球的个数
            if (ball) sol_count++;
            else {
                if (sol_count > 0) num_sol[++sol_tot] = sol_count;
                sol_count = 0;
            }
            // 统计用户选择的连续小球的个数
            if (player) player_count++;
            else {
                if (player_count > 0) num_player[++player_tot] = player_count;
                player_count = 0;
            }
        }
        if (sol_count > 0) num_sol[++sol_tot] = sol_count;
        if (player_count > 0) num_player[++player_tot] = player_count;

        // 检查是否相等
        if (sol_tot != player_tot) return 0;
        for (int j = 1; j <= sol_tot; ++j) {
            if (num_sol[j] != num_player[j]) return 0;
        }
    }

    for (int j = 0; j < size; ++j) {
        int sol_tot = 0, player_tot = 0;
        int sol_count = 0, player_count = 0;

        for (int i = 0; i < size; ++i) {
            int ball = array[i * size + j + 1] % 2; // 实际有无小球
            int player = array[i * size + j + 1] / 2 % 2; // 用户是否选择此处有小球
            // 统计实际连续小球的个数
            if (ball) sol_count++;
            else {
                if (sol_count > 0) num_sol[++sol_tot] = sol_count;
                sol_count = 0;
            }
            // 统计用户选择的连续小球的个数
            if (player) player_count++;
            else {
                if (player_count > 0) num_player[++player_tot] = player_count;
                player_count = 0;
            }
        }
        if (sol_count > 0) num_sol[++sol_tot] = sol_count;
        if (player_count > 0) num_player[++player_tot] = player_count;

        // 检查是否相等
        if (sol_tot != player_tot) return 0;
        for (int j = 1; j <= sol_tot; ++j) {
            if (num_sol[j] != num_player[j]) return 0;
        }
    }

    return 1;
}