/* 学号 姓名 班级 */

#include "pullze.h"
using namespace std;

void draw_line(const char *begin, const char *end, int count) {
    cout << begin << ' ';
    for (int i = 0; i < count; ++i) cout << "═ ";
    cout << end << ' ';
}

void draw_three_line(const char *begin, const char *mid1, const char *mid2, const char *end, int count1, int count2, int count3) {
    cout << begin << ' ';
    for (int i = 0; i < count1; ++i) cout << "═ ";
    cout << mid1 << ' ';
    for (int i = 0; i < count2; ++i) cout << "═ ";
    cout << mid2 << ' ';
    for (int i = 0; i < count3; ++i) cout << "═ ";
    cout << end << ' ';
}

void draw_lines(int n, char chars[][3], int *count, bool *no_divider) {
    for (int i = 0; i < n; ++i) {
        cout << chars[i] << ' ';
        for (int j = 0; j < count[i]; ++j) cout << (no_divider[i] ? "  " : "═ ");
    }
    cout << chars[n] << ' ';
}

// type: 0 为球，1 为 ×，2 为空
void draw(int type, int x, int y, int x_begin, int y_begin, int bg_color, int fg_color, bool boarder) {
    cct_setcolor(bg_color, fg_color);
    if (!boarder) {
        cct_gotoxy(x_begin + x * 2, y_begin + y);
        if (type == 0) cout << "〇";
        else if (type == 1) cout << "×";
        else if (type == 2) cout << "  ";
    }
    else {
        cct_gotoxy(x_begin + x * 8, y_begin + y * 4);
        cout << (type == 2 ? "      " : "╔ ═ ╗ ");
        cct_gotoxy(x_begin + x * 8, y_begin + y * 4 + 1);
        if (type == 0) cout << "║ 〇║ ";
        else if (type == 1) cout << "║ ×║ ";
        else if (type == 2) cout << "      ";
        cct_gotoxy(x_begin + x * 8, y_begin + y * 4 + 2);
        cout << (type == 2 ? "      " : "╚ ═ ╝ ");
    }
    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
}

void decide_type_color(int value, bool cheat, int &type, int &bg_color, int &fg_color) {
    bool ball = value % 2;
    bool player = value / 2 % 2;
    bool wrong = value / 4 % 2;

    if (wrong) bg_color = (cheat && ball) ? COLOR_HBLUE : COLOR_HRED, fg_color = COLOR_BLACK, type = 1;
    else if (player) bg_color = (cheat && !ball) ? COLOR_HRED : COLOR_HBLUE, fg_color = COLOR_BLACK, type = 0;
    else if (cheat && ball) bg_color = COLOR_WHITE, fg_color = COLOR_BLACK, type = 0;
    else bg_color = COLOR_HWHITE, fg_color = COLOR_BLACK, type = 2;
}

void update_ball(int value, bool cheat, int x, int y, int x_begin, int y_begin, bool boarder) {
    int type, bg_color, fg_color;
    decide_type_color(value, cheat, type, bg_color, fg_color);
    draw(type, x, y, x_begin, y_begin, bg_color, fg_color, boarder);
}

// x_begin, y_begin: 小球填充起始位置
// 返回棋盘的下一行
int console_array_print(int *array, int &x_begin, int &y_begin, bool hint, int play) {
    int size = array[0];
    int row[16][10] = {0}, col[16][10] = {0};
    anaylse_array(array, row, col);
    int max_row = 0, max_col = 0;
    for (int i = 0; i < size; ++i) {
        if (row[i][0] > max_row) max_row = row[i][0];
        if (col[i][0] > max_col) max_col = col[i][0];
    }

    cout << endl;

    int pos_row;

    if (!hint) {
        // 列号和行号表头
        cout << "   ";
        for (int i = 0; i < size; ++i) cout << ' ' << char('a' + i);
        for (int i = 0; i < size; ++i) cct_gotoxy(0, 3 + i), cout << char('A' + i);

        // 整个球盘
        cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
        pos_row = 2;
        cct_gotoxy(2, pos_row++);
        draw_line("╔", "╗", size); // 顶部边框
        // 小球填充起始位置
        x_begin = 4, y_begin = pos_row;
        for (int i = 0; i < size; ++i) {
            cct_gotoxy(2, pos_row++);
            cout << "║ ";
            for (int j = 0; j < size; ++j) cout << "  ";
            cout << "║ ";
        }
        cct_gotoxy(2, pos_row++);
        draw_line("╚", "╝", size); // 底部边框
    }
    else {
        pos_row = 1;
        cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
        int space = 6 + 2 * max_row; // 左侧空格
        cct_gotoxy(space, pos_row++); // 起始位置

        draw_line("╔", "╗", size); // 顶部边框
        // 每列每组连续小球个数
        for (int i = 0; i < max_col; ++i) {
            cct_gotoxy(space, pos_row++);
            cout << "║ ";
            for (int j = 0; j < size; ++j) {
                int index = max_col - i;
                if (index <= col[j][0]) cout << setw(2) << col[j][col[j][0] - index + 1];
                else cout << "  ";
            }
            cout << "║ ";
        }

        cct_gotoxy(space, pos_row++);
        draw_line("╠", "╣", size); // 数字和列号分割

        // 列号表头
        cct_gotoxy(space, pos_row++);
        cout << "║ ";
        for (int i = 0; i < size; ++i) cout << ' ' << char('a' + i);
        cout << "║ " << endl;
        pos_row++;

        draw_three_line("╔", "╦", "╬", "╣", max_row, 1, size); // 顶部边框和列号
        cout << endl;

        // 小球填充起始位置
        x_begin = space + 2, y_begin = pos_row;
        pos_row++;

        // 每行每组连续小球长度，及后面的球盘
        for (int i = 0; i < size; ++i) {
            cout << "║";
            for (int j = 0; j < max_row; ++j) {
                int index = max_row - j;
                if (index <= row[i][0]) cout << setw(2) << row[i][row[i][0] - index + 1];
                else cout << "  ";
            }
            cout << " ║  " << char('A' + i) << "║ ";
            for (int j = 0; j < size; ++j) cout << "  ";
            cout << "║ " << endl;
            pos_row++;
        }

        draw_three_line("╚", "╩", "╩", "╝", max_row, 1, size); // 底部边框
    }
    
    if (!play) { // 画出小球
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (array[i * size + j + 1]) draw(0, j, i, x_begin, y_begin, COLOR_HBLUE, COLOR_BLACK, 0); // 有小球
            }
        }
    }

    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    return pos_row;
}

// 每个小球之间都有框线
// x_begin, y_begin: 小球填充起始位置
// 返回棋盘的下一行
int console_array_print_full(int *array, int &x_begin, int &y_begin, bool hint, int play) {
    int size = array[0];
    int row[16][10] = {0}, col[16][10] = {0};
    anaylse_array(array, row, col);
    int max_row = 0, max_col = 0;
    for (int i = 0; i < size; ++i) {
        if (row[i][0] > max_row) max_row = row[i][0];
        if (col[i][0] > max_col) max_col = col[i][0];
    }

    cout << endl;

    int pos_row;
    char chars[20][3];
    int count[20] = {0};
    bool no_divider[20] = {0};

    if (!hint) {
        // 列号和行号表头
        cout << "      ";
        for (int i = 0; i < size; ++i) cout << char('a' + i) << (i == size - 1 ? "" : "       ");
        for (int i = 0; i < size; ++i) cct_gotoxy(0, 4 + i * 4), cout << char('A' + i);

        // 整个球盘
        cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
        pos_row = 2;
        cct_gotoxy(2, pos_row++);

        // 顶部边框
        for (int i = 0; i < size; ++i) strcpy(chars[i], "╦"), count[i] = 3;
        strcpy(chars[0], "╔"), strcpy(chars[size], "╗");
        draw_lines(size, chars, count, no_divider);

        // 处理好分割线
        for (int i = 0; i < size; ++i) strcpy(chars[i], "╬"), count[i] = 3;
        strcpy(chars[0], "╠"), strcpy(chars[size], "╣");
        // 小球填充起始位置
        x_begin = 4, y_begin = pos_row;

        for (int i = 0; i < size; ++i) {
            for (int _ = 0; _ < 3; ++_) {
                cct_gotoxy(2, pos_row++);
                cout << "║ ";
                for (int j = 0; j < size; ++j) cout << "      ║ ";
            }
            cct_gotoxy(2, pos_row++);

            if (i == size - 1) {
                for (int j = 0; j < size; ++j) strcpy(chars[j], "╩");
                strcpy(chars[0], "╚"), strcpy(chars[size], "╝");
            }
            draw_lines(size, chars, count, no_divider);
        }
    }
    else {
        pos_row = 1;
        cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
        int space = 6 + 2 * max_row; // 左侧空格
        cct_gotoxy(space, pos_row++); // 起始位置

        draw_line("╔", "╗", 4 * size - 1); // 顶部边框
        // 每列每组连续小球个数
        for (int i = 0; i < max_col; ++i) {
            cct_gotoxy(space, pos_row++);
            cout << "║  ";
            for (int j = 0; j < size; ++j) {
                int index = max_col - i;
                if (index <= col[j][0]) cout << setw(2) << col[j][col[j][0] - index + 1];
                else cout << "  ";
                cout << (j == size - 1 ? "   " : "      ");
            }
            cout << "║ ";
        }

        cct_gotoxy(space, pos_row++);
        draw_line("╠", "╣", 4 * size - 1); // 数字和列号分割

        // 列号表头
        cct_gotoxy(space, pos_row++);
        cout << "║  ";
        for (int i = 0; i < size; ++i) cout << ' ' << char('a' + i) << (i == size - 1 ? "   " : "      ");
        cout << "║ " << endl;
        pos_row++;

        // 列号跟球之间的分割线
        for (int i = 0; i < size; ++i) strcpy(chars[i + 2], "╦"), count[i + 2] = 3;
        strcpy(chars[0], "╔"), strcpy(chars[1], "╦"), strcpy(chars[2], "╬"), strcpy(chars[size + 2], "╣");
        count[0] = max_row, count[1] = 1;
        draw_lines(size + 2, chars, count, no_divider);
        cout << endl;

        // 小球填充起始位置
        x_begin = space + 2, y_begin = pos_row;
        pos_row++;

        // 处理好后面的分割线
        for (int i = 0; i < size; ++i) strcpy(chars[i + 2], "╬");
        strcpy(chars[0], "║"), strcpy(chars[1], "║"), strcpy(chars[2], "╠"), strcpy(chars[size + 2], "╣");
        no_divider[0] = 1, no_divider[1] = 1;

        // 每行每组连续小球长度，及后面的球盘
        for (int i = 0; i < size; ++i) {
            for (int _ = 0; _ < 3; ++_) {
                cout << "║";
                for (int j = 0; j < max_row; ++j) {
                    int index = max_row - j;
                    if (_ == 1 && index <= row[i][0]) cout << setw(2) << row[i][row[i][0] - index + 1];
                    else cout << "  ";
                }
                cout << " ║  " << (_ == 1 ? char('A' + i) : ' ') << "║ ";
                for (int j = 0; j < size; ++j) cout << "      ║ ";
                cout << endl;
                pos_row++;
            }
            if (i == size - 1) {
                for (int j = 0; j < size; ++j) strcpy(chars[j + 2], "╩");
                strcpy(chars[0], "╚"), strcpy(chars[1], "╩"), strcpy(chars[2], "╩"), strcpy(chars[size + 2], "╝");
                no_divider[0] = 0, no_divider[1] = 0;
            }
            draw_lines(size + 2, chars, count, no_divider);
            cout << endl;
            pos_row++;
        }
    }
    
    if (!play) { // 画出小球
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (array[i * size + j + 1]) draw(0, j, i, x_begin, y_begin, COLOR_HBLUE, COLOR_BLACK, 1); // 有小球
            }
        }
    }

    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    return pos_row;
}

void listen_loop(int *array, bool play, int row, int x_begin, int y_begin, bool boarder) {
    int X = 0, Y = 0, maction, keycode1, keycode2;
    int size = array[0];
    cct_enable_mouse();
    cct_setcursor(CURSOR_INVISIBLE);
    bool cheat = 0;

    while (1) {
        int ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
        cct_gotoxy(14, row);
        for (int i = 0; i < 40; ++i) cout << ' '; // 清除之前的提示
        cct_gotoxy(14, row);
        
        if (ret == CCT_MOUSE_EVENT) { // 鼠标事件
            int posx, posy;
            bool good_pos;
            if (!boarder) {
                posx = (X - x_begin) / 2, posy = Y - y_begin;
                good_pos = X >= x_begin && Y >= y_begin && posx >= 0 && posx < size && posy >= 0 && posy < size;
            }
            else {
                posx = X - x_begin, posy = Y - y_begin;
                good_pos = X >= x_begin && Y >= y_begin && posx % 8 < 6 && posy % 4 < 3;
                posx /= 8, posy /= 4;
                good_pos = good_pos && posx >= 0 && posx < size && posy >= 0 && posy < size;
            }
            switch (maction) {
                case MOUSE_LEFT_BUTTON_CLICK: 
                    if (play && good_pos) {
                        int &ball = array[posy * size + posx + 1];
                        if (ball / 2 % 2 == 0) ball += 2, ball -= 4 * (ball / 4); // 之前没有选择这里有球，如果之前选择没球要取消
                        else ball -= 2; // 之前选择这里有球，取消选择
                        update_ball(array[posy * size + posx + 1], cheat, posx, posy, x_begin, y_begin, boarder);
                    }
                    cct_gotoxy(14, row);
                    cout << "[读到左键] "; 
                    for (int i = 0; i < 40; ++i) cout << ' ';
                    cct_gotoxy(14, row);
                    break;
                case MOUSE_RIGHT_BUTTON_CLICK:
                    if (play && good_pos) {
                        int &ball = array[posy * size + posx + 1];
                        if (ball / 4 % 2 == 0) ball += 4, ball -= 2 * (ball / 2 % 2); // 之前没有选择这里没球，如果之前选择有球要取消
                        else ball -= 4; // 之前选择这里没球，取消选择
                        update_ball(array[posy * size + posx + 1], cheat, posx, posy, x_begin, y_begin, boarder);
                    }
                    cct_gotoxy(14, row);
                    for (int i = 0; i < 40; ++i) cout << ' ';
                    cct_gotoxy(14, row);
                    cout << "[读到右键] "; 
                    break;
                default: cout << "[当前光标] "; break;
            }
            if (good_pos) cout << char('A' + posy) << "行" << char('a' + posx) << "列";
            else cout << "位置非法";
        }
        else if (ret == CCT_KEYBOARD_EVENT) { // 键盘事件
            bool worked = 0;
            if (play) {
                bool win;
                switch (keycode1) {
                    case 'y': case 'Y':
                        worked = 1;
                        cout << "[读到提交键]";
                        Sleep(100);
                        win = check_win(array);
                        cct_gotoxy(14, row);
                        for (int i = 0; i < 30; ++i) cout << ' ';
                        cct_gotoxy(14, row);
                        if (win) {
                            cout << "[提交成功]" << endl;
                            return;
                        }
                        cout << "提交错误, 可用作弊模式查看";
                        break;
                    case 'z': case 'Z':
                        worked = 1;
                        cheat ^= 1;
                        cout << "[作弊模式" << (cheat ? "开" : "关") << "]" << endl;
                        for (int i = 0; i < size; ++i) {
                            for (int j = 0; j < size; ++j) {
                                update_ball(array[i * size + j + 1], cheat, j, i, x_begin, y_begin, boarder);
                            }
                        }
                        break;
                    case 'q': case 'Q':
                        worked = 1;
                        cout << "[读到Q/q，游戏结束]" << endl;
                        return;
                }
            }
            if (!worked) switch (keycode1) {
                case 224:
                    switch (keycode2) {
                        case KB_ARROW_UP: cout << "[读到上箭头]"; break;
                        case KB_ARROW_DOWN: cout << "[读到下箭头]"; break;
                        case KB_ARROW_LEFT: cout << "[读到左箭头]"; break;
                        case KB_ARROW_RIGHT: cout << "[读到右箭头]"; break;
                    }
                    worked = 1;
                    break;
                case 13: cout << "[读到回车键]" << endl; if (!play) return; break;
                default: cout << "[读到键码] " << keycode1 << '/' << keycode2;
            }
        }
    }

    cct_disable_mouse();
    cct_setcursor(CURSOR_VISIBLE_NORMAL);
}

void pullze_console(bool boarder, bool hint, bool listen, bool play) {
    int array[300] = {0};
    generate_array(array);
    cct_cls();
    if (!boarder) cct_setconsoleborder(70, 32, 140, 64), cct_setfontsize("新宋体", 26);
    else cct_setconsoleborder(90, 150, 180, 300), cct_setfontsize("新宋体", 13 + (15 - array[0]));
    cct_setcursor(CURSOR_INVISIBLE); // 隐藏光标
    if (play) cout << "左键选〇/右键选×,Y/y提交,Z/z作弊,Q/q结束";
    else if (listen) cout << "测试键盘/鼠标左键/右键，按回车退出";

    int x_begin, y_begin, row;
    if (!boarder) row = console_array_print(array, x_begin, y_begin, hint, play);
    else row = console_array_print_full(array, x_begin, y_begin, hint, play);

    if (listen) listen_loop(array, play, row, x_begin, y_begin, boarder);
    cct_gotoxy(0, row + 1);
}