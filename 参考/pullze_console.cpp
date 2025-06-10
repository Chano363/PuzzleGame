/* ѧ�� ���� �༶ */

#include "pullze.h"
using namespace std;

void draw_line(const char *begin, const char *end, int count) {
    cout << begin << ' ';
    for (int i = 0; i < count; ++i) cout << "�T ";
    cout << end << ' ';
}

void draw_three_line(const char *begin, const char *mid1, const char *mid2, const char *end, int count1, int count2, int count3) {
    cout << begin << ' ';
    for (int i = 0; i < count1; ++i) cout << "�T ";
    cout << mid1 << ' ';
    for (int i = 0; i < count2; ++i) cout << "�T ";
    cout << mid2 << ' ';
    for (int i = 0; i < count3; ++i) cout << "�T ";
    cout << end << ' ';
}

void draw_lines(int n, char chars[][3], int *count, bool *no_divider) {
    for (int i = 0; i < n; ++i) {
        cout << chars[i] << ' ';
        for (int j = 0; j < count[i]; ++j) cout << (no_divider[i] ? "  " : "�T ");
    }
    cout << chars[n] << ' ';
}

// type: 0 Ϊ��1 Ϊ ����2 Ϊ��
void draw(int type, int x, int y, int x_begin, int y_begin, int bg_color, int fg_color, bool boarder) {
    cct_setcolor(bg_color, fg_color);
    if (!boarder) {
        cct_gotoxy(x_begin + x * 2, y_begin + y);
        if (type == 0) cout << "��";
        else if (type == 1) cout << "��";
        else if (type == 2) cout << "  ";
    }
    else {
        cct_gotoxy(x_begin + x * 8, y_begin + y * 4);
        cout << (type == 2 ? "      " : "�X �T �[ ");
        cct_gotoxy(x_begin + x * 8, y_begin + y * 4 + 1);
        if (type == 0) cout << "�U ���U ";
        else if (type == 1) cout << "�U ���U ";
        else if (type == 2) cout << "      ";
        cct_gotoxy(x_begin + x * 8, y_begin + y * 4 + 2);
        cout << (type == 2 ? "      " : "�^ �T �a ");
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

// x_begin, y_begin: С�������ʼλ��
// �������̵���һ��
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
        // �кź��кű�ͷ
        cout << "   ";
        for (int i = 0; i < size; ++i) cout << ' ' << char('a' + i);
        for (int i = 0; i < size; ++i) cct_gotoxy(0, 3 + i), cout << char('A' + i);

        // ��������
        cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
        pos_row = 2;
        cct_gotoxy(2, pos_row++);
        draw_line("�X", "�[", size); // �����߿�
        // С�������ʼλ��
        x_begin = 4, y_begin = pos_row;
        for (int i = 0; i < size; ++i) {
            cct_gotoxy(2, pos_row++);
            cout << "�U ";
            for (int j = 0; j < size; ++j) cout << "  ";
            cout << "�U ";
        }
        cct_gotoxy(2, pos_row++);
        draw_line("�^", "�a", size); // �ײ��߿�
    }
    else {
        pos_row = 1;
        cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
        int space = 6 + 2 * max_row; // ���ո�
        cct_gotoxy(space, pos_row++); // ��ʼλ��

        draw_line("�X", "�[", size); // �����߿�
        // ÿ��ÿ������С�����
        for (int i = 0; i < max_col; ++i) {
            cct_gotoxy(space, pos_row++);
            cout << "�U ";
            for (int j = 0; j < size; ++j) {
                int index = max_col - i;
                if (index <= col[j][0]) cout << setw(2) << col[j][col[j][0] - index + 1];
                else cout << "  ";
            }
            cout << "�U ";
        }

        cct_gotoxy(space, pos_row++);
        draw_line("�d", "�g", size); // ���ֺ��кŷָ�

        // �кű�ͷ
        cct_gotoxy(space, pos_row++);
        cout << "�U ";
        for (int i = 0; i < size; ++i) cout << ' ' << char('a' + i);
        cout << "�U " << endl;
        pos_row++;

        draw_three_line("�X", "�j", "�p", "�g", max_row, 1, size); // �����߿���к�
        cout << endl;

        // С�������ʼλ��
        x_begin = space + 2, y_begin = pos_row;
        pos_row++;

        // ÿ��ÿ������С�򳤶ȣ������������
        for (int i = 0; i < size; ++i) {
            cout << "�U";
            for (int j = 0; j < max_row; ++j) {
                int index = max_row - j;
                if (index <= row[i][0]) cout << setw(2) << row[i][row[i][0] - index + 1];
                else cout << "  ";
            }
            cout << " �U  " << char('A' + i) << "�U ";
            for (int j = 0; j < size; ++j) cout << "  ";
            cout << "�U " << endl;
            pos_row++;
        }

        draw_three_line("�^", "�m", "�m", "�a", max_row, 1, size); // �ײ��߿�
    }
    
    if (!play) { // ����С��
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (array[i * size + j + 1]) draw(0, j, i, x_begin, y_begin, COLOR_HBLUE, COLOR_BLACK, 0); // ��С��
            }
        }
    }

    cct_setcolor(COLOR_BLACK, COLOR_WHITE);
    return pos_row;
}

// ÿ��С��֮�䶼�п���
// x_begin, y_begin: С�������ʼλ��
// �������̵���һ��
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
        // �кź��кű�ͷ
        cout << "      ";
        for (int i = 0; i < size; ++i) cout << char('a' + i) << (i == size - 1 ? "" : "       ");
        for (int i = 0; i < size; ++i) cct_gotoxy(0, 4 + i * 4), cout << char('A' + i);

        // ��������
        cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
        pos_row = 2;
        cct_gotoxy(2, pos_row++);

        // �����߿�
        for (int i = 0; i < size; ++i) strcpy(chars[i], "�j"), count[i] = 3;
        strcpy(chars[0], "�X"), strcpy(chars[size], "�[");
        draw_lines(size, chars, count, no_divider);

        // ����÷ָ���
        for (int i = 0; i < size; ++i) strcpy(chars[i], "�p"), count[i] = 3;
        strcpy(chars[0], "�d"), strcpy(chars[size], "�g");
        // С�������ʼλ��
        x_begin = 4, y_begin = pos_row;

        for (int i = 0; i < size; ++i) {
            for (int _ = 0; _ < 3; ++_) {
                cct_gotoxy(2, pos_row++);
                cout << "�U ";
                for (int j = 0; j < size; ++j) cout << "      �U ";
            }
            cct_gotoxy(2, pos_row++);

            if (i == size - 1) {
                for (int j = 0; j < size; ++j) strcpy(chars[j], "�m");
                strcpy(chars[0], "�^"), strcpy(chars[size], "�a");
            }
            draw_lines(size, chars, count, no_divider);
        }
    }
    else {
        pos_row = 1;
        cct_setcolor(COLOR_HWHITE, COLOR_BLACK);
        int space = 6 + 2 * max_row; // ���ո�
        cct_gotoxy(space, pos_row++); // ��ʼλ��

        draw_line("�X", "�[", 4 * size - 1); // �����߿�
        // ÿ��ÿ������С�����
        for (int i = 0; i < max_col; ++i) {
            cct_gotoxy(space, pos_row++);
            cout << "�U  ";
            for (int j = 0; j < size; ++j) {
                int index = max_col - i;
                if (index <= col[j][0]) cout << setw(2) << col[j][col[j][0] - index + 1];
                else cout << "  ";
                cout << (j == size - 1 ? "   " : "      ");
            }
            cout << "�U ";
        }

        cct_gotoxy(space, pos_row++);
        draw_line("�d", "�g", 4 * size - 1); // ���ֺ��кŷָ�

        // �кű�ͷ
        cct_gotoxy(space, pos_row++);
        cout << "�U  ";
        for (int i = 0; i < size; ++i) cout << ' ' << char('a' + i) << (i == size - 1 ? "   " : "      ");
        cout << "�U " << endl;
        pos_row++;

        // �кŸ���֮��ķָ���
        for (int i = 0; i < size; ++i) strcpy(chars[i + 2], "�j"), count[i + 2] = 3;
        strcpy(chars[0], "�X"), strcpy(chars[1], "�j"), strcpy(chars[2], "�p"), strcpy(chars[size + 2], "�g");
        count[0] = max_row, count[1] = 1;
        draw_lines(size + 2, chars, count, no_divider);
        cout << endl;

        // С�������ʼλ��
        x_begin = space + 2, y_begin = pos_row;
        pos_row++;

        // ����ú���ķָ���
        for (int i = 0; i < size; ++i) strcpy(chars[i + 2], "�p");
        strcpy(chars[0], "�U"), strcpy(chars[1], "�U"), strcpy(chars[2], "�d"), strcpy(chars[size + 2], "�g");
        no_divider[0] = 1, no_divider[1] = 1;

        // ÿ��ÿ������С�򳤶ȣ������������
        for (int i = 0; i < size; ++i) {
            for (int _ = 0; _ < 3; ++_) {
                cout << "�U";
                for (int j = 0; j < max_row; ++j) {
                    int index = max_row - j;
                    if (_ == 1 && index <= row[i][0]) cout << setw(2) << row[i][row[i][0] - index + 1];
                    else cout << "  ";
                }
                cout << " �U  " << (_ == 1 ? char('A' + i) : ' ') << "�U ";
                for (int j = 0; j < size; ++j) cout << "      �U ";
                cout << endl;
                pos_row++;
            }
            if (i == size - 1) {
                for (int j = 0; j < size; ++j) strcpy(chars[j + 2], "�m");
                strcpy(chars[0], "�^"), strcpy(chars[1], "�m"), strcpy(chars[2], "�m"), strcpy(chars[size + 2], "�a");
                no_divider[0] = 0, no_divider[1] = 0;
            }
            draw_lines(size + 2, chars, count, no_divider);
            cout << endl;
            pos_row++;
        }
    }
    
    if (!play) { // ����С��
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (array[i * size + j + 1]) draw(0, j, i, x_begin, y_begin, COLOR_HBLUE, COLOR_BLACK, 1); // ��С��
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
        for (int i = 0; i < 40; ++i) cout << ' '; // ���֮ǰ����ʾ
        cct_gotoxy(14, row);
        
        if (ret == CCT_MOUSE_EVENT) { // ����¼�
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
                        if (ball / 2 % 2 == 0) ball += 2, ball -= 4 * (ball / 4); // ֮ǰû��ѡ�������������֮ǰѡ��û��Ҫȡ��
                        else ball -= 2; // ֮ǰѡ����������ȡ��ѡ��
                        update_ball(array[posy * size + posx + 1], cheat, posx, posy, x_begin, y_begin, boarder);
                    }
                    cct_gotoxy(14, row);
                    cout << "[�������] "; 
                    for (int i = 0; i < 40; ++i) cout << ' ';
                    cct_gotoxy(14, row);
                    break;
                case MOUSE_RIGHT_BUTTON_CLICK:
                    if (play && good_pos) {
                        int &ball = array[posy * size + posx + 1];
                        if (ball / 4 % 2 == 0) ball += 4, ball -= 2 * (ball / 2 % 2); // ֮ǰû��ѡ������û�����֮ǰѡ������Ҫȡ��
                        else ball -= 4; // ֮ǰѡ������û��ȡ��ѡ��
                        update_ball(array[posy * size + posx + 1], cheat, posx, posy, x_begin, y_begin, boarder);
                    }
                    cct_gotoxy(14, row);
                    for (int i = 0; i < 40; ++i) cout << ' ';
                    cct_gotoxy(14, row);
                    cout << "[�����Ҽ�] "; 
                    break;
                default: cout << "[��ǰ���] "; break;
            }
            if (good_pos) cout << char('A' + posy) << "��" << char('a' + posx) << "��";
            else cout << "λ�÷Ƿ�";
        }
        else if (ret == CCT_KEYBOARD_EVENT) { // �����¼�
            bool worked = 0;
            if (play) {
                bool win;
                switch (keycode1) {
                    case 'y': case 'Y':
                        worked = 1;
                        cout << "[�����ύ��]";
                        Sleep(100);
                        win = check_win(array);
                        cct_gotoxy(14, row);
                        for (int i = 0; i < 30; ++i) cout << ' ';
                        cct_gotoxy(14, row);
                        if (win) {
                            cout << "[�ύ�ɹ�]" << endl;
                            return;
                        }
                        cout << "�ύ����, ��������ģʽ�鿴";
                        break;
                    case 'z': case 'Z':
                        worked = 1;
                        cheat ^= 1;
                        cout << "[����ģʽ" << (cheat ? "��" : "��") << "]" << endl;
                        for (int i = 0; i < size; ++i) {
                            for (int j = 0; j < size; ++j) {
                                update_ball(array[i * size + j + 1], cheat, j, i, x_begin, y_begin, boarder);
                            }
                        }
                        break;
                    case 'q': case 'Q':
                        worked = 1;
                        cout << "[����Q/q����Ϸ����]" << endl;
                        return;
                }
            }
            if (!worked) switch (keycode1) {
                case 224:
                    switch (keycode2) {
                        case KB_ARROW_UP: cout << "[�����ϼ�ͷ]"; break;
                        case KB_ARROW_DOWN: cout << "[�����¼�ͷ]"; break;
                        case KB_ARROW_LEFT: cout << "[�������ͷ]"; break;
                        case KB_ARROW_RIGHT: cout << "[�����Ҽ�ͷ]"; break;
                    }
                    worked = 1;
                    break;
                case 13: cout << "[�����س���]" << endl; if (!play) return; break;
                default: cout << "[��������] " << keycode1 << '/' << keycode2;
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
    if (!boarder) cct_setconsoleborder(70, 32, 140, 64), cct_setfontsize("������", 26);
    else cct_setconsoleborder(90, 150, 180, 300), cct_setfontsize("������", 13 + (15 - array[0]));
    cct_setcursor(CURSOR_INVISIBLE); // ���ع��
    if (play) cout << "���ѡ��/�Ҽ�ѡ��,Y/y�ύ,Z/z����,Q/q����";
    else if (listen) cout << "���Լ���/������/�Ҽ������س��˳�";

    int x_begin, y_begin, row;
    if (!boarder) row = console_array_print(array, x_begin, y_begin, hint, play);
    else row = console_array_print_full(array, x_begin, y_begin, hint, play);

    if (listen) listen_loop(array, play, row, x_begin, y_begin, boarder);
    cct_gotoxy(0, row + 1);
}