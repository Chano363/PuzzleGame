/* ѧ�� ���� �༶ */

#include "pullze.h"
using namespace std;

// ����ָ���
void split_line(int size, int max_row = 0, bool head = 0) {
    // �ָ�����ʽ��

    // max_row = 4, head = false
    // ---------+-+-----------+-----------+
    //  2 1 3 4 |A| O  O O  O | O   O   O |

    // head = true (��ͷ�����зָ��ߣ�û���к�)
    // -----------+-----------+-----------+
    //            | 2 3 1 5 3 | 4 2 1 1 1 |

    // max_row = 0, head = false
    // +-+-----------+
    // |A| O  O O  O |

    // ���ÿ�����������Ŀ�϶
    for (int i = 0; i < max_row; ++i) cout << "--";
    if (max_row > 0) cout << '-';

    // �к�����Ŀ�
    cout << (head && max_row > 0 ? '-' : '+') << "-+";

    // С������Ŀ�
    for (int i = 0; i < size; ++i) {
        cout << "--";
        if (i % 5 == 4) cout << "-+";
    }
    cout << endl;
}

// hint: �Ƿ�����ʾ����
// play = 1: ������Ϸ��������
// play = 2: ������Ϸ��������
void array_print(int *array, bool hint = 0, int play = 0) {
    int size = array[0];
    int row[16][10] = {0}, col[16][10] = {0};
    anaylse_array(array, row, col);
    int max_row = 0, max_col = 0;
    for (int i = 0; i < size; ++i) {
        if (row[i][0] > max_row) max_row = row[i][0];
        if (col[i][0] > max_col) max_col = col[i][0];
    }
    if (!hint) max_row = max_col = 0; // ���û����ʾ���У�����ʾ

    if (hint) {
        split_line(size, max_row, 1);
        for (int i = 0; i < max_col; ++i) {
            for (int j = 0; j < max_row * 2 + 1 + 2; ++j) cout << ' ';
            cout << '|';
            for (int j = 0; j < size; ++j) {
                int index = max_col - i; // Ŀǰ�Ǵ��µ��ϵڼ���
                // �����ʱ���Ǵ��ϵ��£������Ƿ��ŵ�
                if (index <= col[j][0]) cout << setw(2) << col[j][col[j][0] - index + 1];
                else cout << "  ";
                if (j % 5 == 4) cout << " |";
            }
            cout << endl;
        }
        split_line(size, max_row, 1);
    }
    else split_line(size);

    // �кű�ͷ
    if (hint) for (int j = 0; j < max_row * 2 + 1 + 2; ++j) cout << ' ';
    else cout << "| ";
    cout << '|';
    for (int i = 0; i < size; ++i) {
        cout << ' ' << char('a' + i);
        if (i % 5 == 4) cout << " |"; // ÿ5���к����һ���ָ���
    }
    cout << endl;
    split_line(size, max_row);
    
    for (int i = 0; i < size; ++i) {
        // ���ÿ��ÿ������С�򳤶�
        for (int j = 0; j < max_row; ++j) {
            int index = max_row - j;
            if (index <= row[i][0]) cout << setw(2) << row[i][row[i][0] - index + 1];
            else cout << "  ";
        }
        if (hint) cout << ' ';
        // �кű�ͷ
        cout << "|" << char('A' + i) << '|';
        // ���ÿ��ÿ��С��
        for (int j = 0; j < size; ++j) {
            int ball = array[i * size + j + 1] % 2; // ʵ������С��
            int player = array[i * size + j + 1] / 2; // �û��Ƿ�ѡ��˴���С��
            if (play == 0) cout << (ball ? " O" : "  "); // ԭ�����
            else if (play == 1) { // ������Ϸ��������
                cout << ' ';
                if (player) cct_setcolor(COLOR_HYELLOW, COLOR_HBLUE), cout << "O", cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                else cout << ' ';
            }
            else if (play == 2) { // ������
                cout << ' ';
                if (player) cct_setcolor(COLOR_HYELLOW, COLOR_HBLUE), cout << (ball ? 'O' : 'X'), cct_setcolor(COLOR_BLACK, COLOR_WHITE);
                else cout << (ball ? 'O' : ' ');
            }
            if (j % 5 == 4) cout << " |"; // ÿ5��С������һ���ָ���
        }
        cout << endl;
        if (i % 5 == 4) split_line(size, max_row); // ÿ5�����һ���ָ���
    }
    cout << endl;
}

// -1: �˳�
// -2: �ύ
// -3: ����
// ������ѡ�е�С��λ��
int get_opt(int size) {
    char buf[30];
    while (1) {
        cout << endl;
        cout << "������ʽ��Aa=�ȼ���ͼ����Ϸ��������ѡ��Aaλ(���ִ�Сд)" << endl;
        cout << "            ����Ҫ֧��ͼ�ν�����Ҽ���棬�ٴ�����Aa�൱�����" << endl;
        cout << "        X/x=�˳�(���н���X/x�����ִ�Сд)" << endl;
        cout << "        Y/y=�ύ(���н���Y/y�����ִ�Сд)" << endl;
        cout << "        Z/z=����(���н���Z/z�����ִ�Сд)" << endl;
        cout << "        Ctrl+c ǿ���˳�" << endl;
        cout << "������ : ";
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
            return (buf[0] - 'A') * size + (buf[1] - 'a') + 1; // ����λ��
        }
        cout << "�������" << endl;
    }
}

void pullze_base(bool hint, bool play) {
    int array[300] = {0};
    generate_array(array);
    cout << "��ʼ���飺" << endl;
    array_print(array, hint, play);

    if (!play) return;

    bool cheat = 0;
    int size = array[0];
    while (1) {
        int opt = get_opt(size);
        if (opt == -1) {
            cout << endl;
            return; // �˳�
        }
        if (opt == -2) {
            bool win = check_win(array);
            if (win) {
                cout << endl << "�ύ�ɹ�����Ϸ����" << endl;
                return;
            }
            else {
                cout << endl << "�ύ����, ��������ģʽ�鿴" << endl;
                continue;
            }
        }
        if (opt == -3) {
            cout << endl << "����Z/z��" << endl;
            cheat ^= 1;
            array_print(array, 1, cheat + 1);
            continue;
        }
        int x = (opt - 1) / size; // ��
        int y = (opt - 1) % size; // ��
        cout << endl << "����" << char('A' + x) << char('a' + y) << "��" << endl;
        if (array[opt] / 2 == 0) array[opt] += 2; // �û�ѡ��˴���С��
        else array[opt] -= 2; // �û�ѡ��˴���С��
        array_print(array, 1, cheat + 1);
    }
}