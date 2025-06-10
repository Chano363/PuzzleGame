/* ѧ�� ���� �༶ */

#include "pullze.h"
using namespace std;

// ��ʾ���ܲ˵�����ȡ�û�ѡ�õĹ���
char menu() {
    cout << "---------------------------------------------------------" << endl;
    cout << " A.�ڲ����飬ԭ�����" << endl;
    cout << " B.�ڲ����飬������ʾ���в����" << endl;
    cout << " C.�ڲ����飬��Ϸ��" << endl;
    cout << " --------------------------------------------------------" << endl;
    cout << " D.n*n�Ŀ��(�޷ָ���)��ԭ�����" << endl;
    cout << " E.n*n�Ŀ��(�޷ָ���)������ʾ����" << endl;
    cout << " F.n*n�Ŀ��(�޷ָ���)����ʾ��ʼ״̬������ƶ�����ʾ����" << endl;
    cout << " G.cmdͼ�ν���������(�޷ָ���)" << endl;
    cout << " --------------------------------------------------------" << endl;
    cout << " H.n*n�Ŀ��(�зָ���)��ԭ�����" << endl;
    cout << " I.n*n�Ŀ��(�зָ���)������ʾ����" << endl;
    cout << " J.n*n�Ŀ��(�зָ���)����ʾ��ʼ״̬������ƶ�����ʾ����" << endl;
    cout << " K.cmdͼ�ν���������(�зָ���)" << endl;
    cout << " --------------------------------------------------------" << endl;
    cout << " Q.�˳�" << endl;
    cout << "---------------------------------------------------------" << endl;
    cout << "[��ѡ��:] ";

    char c;
    while (1) {
        c = _getch();
        if ((c >= 'A' && c <= 'K') || (c >= 'a' && c <= 'k') || c == 'Q' || c == 'q') break;
    }
    putchar(c);
    putchar('\n');
    Sleep(200);
    return (c >= 'a' && c <= 'z') ? (c - 'a' + 'A') : c; // ת��Ϊ��д
}

// �ȴ��û�����"End"����
void end_wait() {
    char buf[100] = {0};
    int x, y;
    cct_getxy(x, y);
    cin.ignore(100, '\n');

    while (1) {
        cct_gotoxy(x, y);
        cout << "                                ";
        cct_gotoxy(x, y);
        cout << "��С�������������End����...";
        cin.getline(buf, 100, '\n');
        if (strlen(buf) == 3) {
            buf[0] = tolower(buf[0]), buf[1] = tolower(buf[1]), buf[2] = tolower(buf[2]);
            if (strcmp(buf, "end") == 0) break;
        }
        cin.clear();
        cct_gotoxy(x, y + 1);
        cout << "�����������������..." << endl;
    }
}

// ��ȡ�����С
int input_size() {
    int size;
    do {
        while (1) {
            cout << "�����������С(5/10/15) ��";
            if (cin >> size) break;
            cin.clear();
        }
    } while (size != 5 && size != 10 && size != 15);
    return size;
}

// �����һ����Ϊ�ߴ磬�����Ϊ��ά����չƽ��ĳλ���Ƿ�����
// �����Ƶ�һλ (x % 2)��0 ��ʾû����1 ��ʾ����
// �����Ƶڶ�λ (x / 2 % 2)��0 �û�δѡ���λ������1 �û�ѡ���λ������
// �����Ƶ���λ (x / 4 % 2)��1 �û�ѡ���λ������ (��X) 0 �û�δѡ���λ������
// ����λ�ô����󣬽����ں���ͼ�ν����¼��X����
void generate_array(int *array) {
    int size = input_size();
    array[0] = size;

    int tot = (size * size + 1) / 2; 
    // size Ϊ������ֱ�Ӽ�һ����������ȡ��
    
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

// ����ÿ��ÿ��С���������������
void anaylse_array(int *array, int row[][10], int col[][10]) {
    int size = array[0];

    // ÿ�������һ����(index 0)��ʾ�м�������С�򣬺��������ʾÿ��ĳ���
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
        if (tot == 0) row[i][++tot] = 0; // ���û��С��������һ��0
    }

    // ÿ�������һ����(index 0)��ʾ�м�������С�򣬺��������ʾÿ��ĳ���
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
        if (tot == 0) col[j][++tot] = 0; // ���û��С��������һ��0
    }
}

bool check_win(int *array) {
    int num_sol[10], num_player[10]; // ĳ�л�ĳ��ÿ������С����������ڼ��
    int size = array[0];

    for (int i = 0; i < size; ++i) {
        int sol_tot = 0, player_tot = 0;
        int sol_count = 0, player_count = 0;

        for (int j = 0; j < size; ++j) {
            int ball = array[i * size + j + 1] % 2; // ʵ������С��
            int player = array[i * size + j + 1] / 2 % 2; // �û��Ƿ�ѡ��˴���С��
            // ͳ��ʵ������С��ĸ���
            if (ball) sol_count++;
            else {
                if (sol_count > 0) num_sol[++sol_tot] = sol_count;
                sol_count = 0;
            }
            // ͳ���û�ѡ�������С��ĸ���
            if (player) player_count++;
            else {
                if (player_count > 0) num_player[++player_tot] = player_count;
                player_count = 0;
            }
        }
        if (sol_count > 0) num_sol[++sol_tot] = sol_count;
        if (player_count > 0) num_player[++player_tot] = player_count;

        // ����Ƿ����
        if (sol_tot != player_tot) return 0;
        for (int j = 1; j <= sol_tot; ++j) {
            if (num_sol[j] != num_player[j]) return 0;
        }
    }

    for (int j = 0; j < size; ++j) {
        int sol_tot = 0, player_tot = 0;
        int sol_count = 0, player_count = 0;

        for (int i = 0; i < size; ++i) {
            int ball = array[i * size + j + 1] % 2; // ʵ������С��
            int player = array[i * size + j + 1] / 2 % 2; // �û��Ƿ�ѡ��˴���С��
            // ͳ��ʵ������С��ĸ���
            if (ball) sol_count++;
            else {
                if (sol_count > 0) num_sol[++sol_tot] = sol_count;
                sol_count = 0;
            }
            // ͳ���û�ѡ�������С��ĸ���
            if (player) player_count++;
            else {
                if (player_count > 0) num_player[++player_tot] = player_count;
                player_count = 0;
            }
        }
        if (sol_count > 0) num_sol[++sol_tot] = sol_count;
        if (player_count > 0) num_player[++player_tot] = player_count;

        // ����Ƿ����
        if (sol_tot != player_tot) return 0;
        for (int j = 1; j <= sol_tot; ++j) {
            if (num_sol[j] != num_player[j]) return 0;
        }
    }

    return 1;
}