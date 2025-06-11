/* 学号 姓名 班级 */

#include "pullze.h"
using namespace std;

int main() {
    // 用GB 2312编码的中文字符集
    SetConsoleOutputCP(936);
    SetConsoleCP(936);
    srand(time(0));

    bool user_quit = 0;
    while (!user_quit) {
        cct_setcursor(CURSOR_VISIBLE_NORMAL);
        cct_setfontsize("新宋体", 16);
        cct_setconsoleborder(120, 50, 120, 200);
        cct_setcolor(COLOR_BLACK, COLOR_WHITE);
        cct_cls();
        char user_choice = menu();
        
        cct_cls();
        switch (user_choice) {
            case 'A': pullze_base(); break;
            case 'B': pullze_base(1); break;
            case 'C': pullze_base(1, 1); break;
            case 'D': pullze_console(0, 0, 0, 0); break;
            case 'E': pullze_console(0, 1, 0, 0); break;
            case 'F': pullze_console(0, 1, 1, 0); break;
            case 'G': pullze_console(0, 1, 1, 1); break;
            case 'H': pullze_console(1, 0, 0, 0); break;
            case 'I': pullze_console(1, 1, 0, 0); break;
            case 'J': pullze_console(1, 1, 1, 0); break;
            case 'K': pullze_console(1, 1, 1, 1); break;
            case 'Q': user_quit = 1; break;
        }
        if (user_choice != 'Q') end_wait();
    }

    cct_gotoxy(0, 23);
    system("pause");
}