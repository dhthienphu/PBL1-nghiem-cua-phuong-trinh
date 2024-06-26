#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdarg.h>

#define italic "\e[3m"
#define off "\e[m"
#define bold "\e[1m"

#define orange "\e[38:5:3m"
#define purple "\e[38:5:6m"
#define green "\e[38:5:2m"
#define red "\e[38:5:1m"
#define blue "\e[38:5:4m"
#define purple1 "\e[38:5:5m"
HANDLE hStdin;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
COORD click;
#define eps 0.001
double smallNumber = 0.0000001;
int intro_off = 0;
#define LINE_WIDTH 80

int nRoots;
int x_click, y_click;
int count_exit = 0;
int prev_x = 0, prev_y = 0;
void gotoXY(int x, int y);
double result_file_2;
double result_file_3;
int process_bisec = 0, process_bows = 0;
int isHavingData = 0;
const int MAX_SIZE = 100;
struct dataLog
{
    double a, b, ans;
};
typedef struct dataLog *data;

struct ListInfo
{
    int max_size;
    int count;
    data *list;
};
typedef struct ListInfo *Log;
typedef int Position;

COORD processInputEvents();
VOID WriteError(LPCSTR lpszMessage);
void getMouseClick();

int getMouseClick_main();
int getMouseClick_1();
int getMouseClick_11();
int getMouseClick_intro();
void rootRange_suggest(double a[], int n);
double f(double a[], int n, double x);
void checkInputRange(double poly[], int n, double *a, double *b, int control_method);
double bisectionMethod(double poly[], int n, double *a, double *b);
void BowstringMethod(double poly[], int n, double *a, double *b);
void ensureFileSize(FILE *file, int y);
void writeDataToFile(char fileName[], int n, double poly[]);
void writeAtPosition(FILE *file, int x, int y, const char *format, ...);
void printPolyToFile(FILE *file, double poly[], int n);

void input_keyboard(double poly[], int *n);
void readNameFile(char *fileName, int control_method);
void readPolyFromFile(FILE *file, char *fileName, double poly[], int *n);
void readDataFromFile(char *fileName, double poly[], int *n);
void printPoly(double poly[], int n);

void button_return();
void button_exit();
void menu_main();
void Dashboard();
void menu_InputData();
void MENU_INPUT();
void alert_message();
void loading_message(char *message);
void INTRO();
double handleZero(double *x)
{
    if (fabs(*x) < smallNumber)
    {
        return 0.0;
    }
    return *x;
}
Log createLog(int max_size);
data createData(double a, double b, double ans);
void addDataToLog(Log cls, data s, Position p);

Log logAns_bisec = createLog(MAX_SIZE);
Log logAns_bows = createLog(MAX_SIZE);
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    int n;
    double a, b;
    double poly[100];
    int choice_main, choice_1, choice_11, choice_12, choice_3, choice_2, choice_4;
    char fileName[100];
    char fileName_1[100];
    char *fileResult;
    n = 3;
    poly[0] = 1;
    poly[1] = -3;
    poly[2] = 5;
    poly[3] = -1;
    isHavingData = 0;

    INTRO();
label_intro:;
    int choice_intro = getMouseClick_intro();
    switch (choice_intro)
    {
    case -2:
        goto label_intro;
        break;
    case 1:
        system("cls");
        break;
    }
label_dashboard:;
    Dashboard();

    choice_main = getMouseClick_main();
    if (choice_main == -2)
    {
        system("cls");
        goto label_dashboard;
    }
    x_click = 0;
    y_click = 100;

    switch (choice_main)
    {
    // ----> case 1 <------ 
    case 1:

    label_1:;
        system("cls");
        MENU_INPUT();
        choice_1 = getMouseClick_1();
        if (choice_1 == -2)
        {
            system("cls");
            goto label_1;
        }
        x_click = 0;
        y_click = 100;

        switch (choice_1)
        {
        case 0:
            system("cls");
            choice_main = -100;
            goto label_dashboard;
            break;
        case -1:
            system("cls");
            goto label_exit;
            break;
        // ----> case 11 <------
        case 11:
            system("cls");

            input_keyboard(poly, &n);
            button_exit();
            button_return();
        label_11:;
            choice_11 = getMouseClick_11();
            if (choice_11 == -2)
            {
                
                goto label_11;
            }

            switch (choice_11)
            {
            case 0:
                system("cls");
                choice_main = -100;
                goto label_dashboard;
                break;
            case -1:
                system("cls");
                goto label_exit;
                break;
            }

            break;
        // ----> case 12 <------
        case 12:
            system("cls");
            readDataFromFile(fileName, poly, &n);
            button_exit();
            button_return();
        label_12:;
            choice_12 = getMouseClick_11();
            if (choice_12 == -2)
            {
                goto label_12;
            }
            switch (choice_12)
            {
            case 0:
                system("cls");
                choice_main = -100;
                goto label_dashboard;
                break;
            case -1:
                system("cls");
                goto label_exit;
                break;
            }
            break;
            // ----> case 12 <------
            // ----> case 13 <------
        }
        break;
        // ----> case 1 <------
        // ----> case 3 <------
    case 3:
        system("cls");
        button_exit();
        button_return();
        if (isHavingData == 0)
        {
            alert_message();
            goto label_3;
        }
        checkInputRange(poly, n, &a, &b, 3);
        if (nRoots == 0)
        {
            button_exit();
            button_return();
            gotoXY(30, 8);
            printf("Nhấn vào nút \"Quay lại\" để quay lại menu chính....");
        }
        if (nRoots != 0)
            bisectionMethod(poly, n, &a, &b);

    label_3:;

        choice_3 = getMouseClick_11();
        if (choice_3 == -2)
        {
            goto label_3;
        }
        switch (choice_3)
        {
        case 0:
            system("cls");
            choice_main = -100;
            goto label_dashboard;
            break;
        case -1:
            system("cls");
            goto label_exit;
            break;
        }

        break;
        // ----> case 3 <------
    // ----> case 2 <------
    case 2:
        system("cls");
        button_exit();
        button_return();
        if (isHavingData == 0)
        {
            alert_message();
            goto label_2;
        }
        checkInputRange(poly, n, &a, &b, 2);
        if (nRoots == 0)
        {
            button_exit();
            button_return();
            gotoXY(30, 8);
            printf("Nhấn vào nút \"Quay lại\" để quay lại menu chính....");
        }
        if (nRoots != 0)
            BowstringMethod(poly, n, &a, &b);

    label_2:;
        choice_2 = getMouseClick_11();
        if (choice_2 == -2)
        {
            goto label_2;
        }
        switch (choice_2)
        {
        case 0:
            system("cls");
            choice_main = -100;
            goto label_dashboard;
            break;
        case -1:
            system("cls");
            goto label_exit;
            break;
        }
        break;
    // ----> case 2 <------
    // ----> case 4 <------
    case 4:
        system("cls");
        writeDataToFile(fileName, n, poly);
        button_exit();
        button_return();
    label_4:;
        choice_4 = getMouseClick_11();
        if (choice_4 == -2)
        {
            goto label_4;
        }
        switch (choice_4)
        {
        case 0:
            system("cls");
            choice_main = -100;
            goto label_dashboard;
            break;
        case -1:
            system("cls");
            goto label_exit;
            break;
        }
        break;
    }

label_exit:;
    intro_off = 1;
    system("cls");
    INTRO();
}
VOID WriteError(LPCSTR lpszMessage)
{
    printf("%s\n", lpszMessage);
    ExitProcess(0);
}
COORD processInputEvents()
{
    DWORD cNumRead, fdwMode, i;
    INPUT_RECORD irInBuf[128];

    // Lay su kien dau vao
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        WriteError("GetStdHandle");

    // Set the console mode
    fdwMode = ENABLE_EXTENDED_FLAGS;
    if (!SetConsoleMode(hStdin, fdwMode))
    {
        WriteError("SetConsoleMode");
    }
    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT; // bat su kien chuot
    if (!SetConsoleMode(hStdin, fdwMode))
    {
        WriteError("SetConsoleMode");
    }

    while (true)
    {

        if (!PeekConsoleInput(hStdin, irInBuf, 128, &cNumRead))
        {
            WriteError("PeekConsoleInput");
        }

        for (i = 0; i < cNumRead; i++)
        {
            if (irInBuf[i].EventType == MOUSE_EVENT &&
                irInBuf[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
                irInBuf[i].Event.MouseEvent.dwEventFlags == 0) // Check if it's a click event
            {

                INPUT_RECORD dummy;
                DWORD dummyNumRead;
                ReadConsoleInput(hStdin, &dummy, 1, &dummyNumRead);

                FlushConsoleInputBuffer(hStdin);

                return irInBuf[i].Event.MouseEvent.dwMousePosition;
            }
        }
    }
    COORD defaultCoord = {100, 100};
    return defaultCoord;
}
void getMouseClick()
{
    click = processInputEvents();
    x_click = click.X;
    y_click = click.Y;
}

void gotoXY(int x, int y)
{
    CursorPosition.X = x;
    CursorPosition.Y = y;
    SetConsoleCursorPosition(console, CursorPosition);
}
void button_return()
{
    gotoXY(1, 0);
    printf(green "╔----------╗ ");
    gotoXY(1, 0 + 1);
    printf("║ Quay lại ║ ");
    gotoXY(1, 0 + 2);
    printf("╚----------╝" off);
}

void button_exit()
{
    gotoXY(96, 0);
    printf(red "╔----------------------╗");
    gotoXY(96, 0 + 1);
    printf("║  Thoát chương trình  ║");
    gotoXY(96, 0 + 2);
    printf("╚----------------------╝" off);
}

void menu_main()
{
    int x = 35, y = 0;
    gotoXY(x, y);
    printf("               " red "╔═══════════════╗" off "      \n");
    gotoXY(x, y + 1);
    printf("               " italic red "║      MENU     ║" off "        \n");
    gotoXY(x, y + 2);
    printf("               " red "╚═══════════════╝" off "        \n");
    gotoXY(x, y + 3);
    printf(red "╔═════════════════════════════════════════════╗\n");
    gotoXY(x, y + 4);
    printf("║                                             " red "║\n");
    gotoXY(x, y + 5);
    printf(purple "║          " purple "╔════════════════════════╗" off "         " purple "║\n");
    gotoXY(x, y + 6);
    printf(purple "║          " purple bold "║      Nhập đa thức      ║" off "        " purple " ║\n");
    gotoXY(x, y + 7);
    printf(purple "║          " purple "╚════════════════════════╝" off "        " purple " ║\n");

    gotoXY(x, y + 8);
    printf(orange "║          " orange "╔════════════════════════╗" off "         " orange "║\n");
    gotoXY(x, y + 9);
    printf(orange "║          " orange "║ Giải phương trình bằng ║" off "         " orange "║\n");
    gotoXY(x, y + 10);
    printf(orange "║          " orange "║ phương pháp dây cung   ║" off "         " orange "║\n");
    gotoXY(x, y + 11);
    printf(orange "║          " orange "╚════════════════════════╝" off "         " orange "║\n");
    gotoXY(x, y + 12);
    printf(blue "║          " blue "╔════════════════════════╗" off "         " blue "║\n");
    gotoXY(x, y + 13);
    printf(blue "║          " blue "║ Giải phương trình bằng ║" off "         " blue "║\n");
    gotoXY(x, y + 14);
    printf(blue "║          " blue "║ phương pháp chia đôi   ║" off "         " blue "║\n");
    gotoXY(x, y + 15);
    printf(blue "║          " blue "╚════════════════════════╝" off "         " blue "║\n");
    gotoXY(x, y + 16);
    printf(green "║          " green "╔════════════════════════╗" off "         " green "║\n");
    gotoXY(x, y + 17);
    printf(green "║          " green bold "║      Xuất dữ liệu      ║" off "        " green " ║\n");
    gotoXY(x, y + 18);
    printf(green "║          " green "╚════════════════════════╝" off "        " green " ║\n");
    gotoXY(x, y + 19);
    printf(red "║                                             ║\n");
    gotoXY(x, y + 20);
    printf(red "╚═════════════════════════════════════════════╝\n" off);
}

void Dashboard()
{
    button_exit();
    menu_main();
    // coming soon menu ho ten voi detai.
}
void loading_message(char *message)
{
    for (int i = 0; i < strlen(message); i++)
    {
        printf("%c", message[i]);
        Sleep(10);
    }
}
void menu_InputData()
{
    int x = 30, y = 0;
    gotoXY(x, y);
    gotoXY(x, y + 3);
    printf(purple "╔════════════════════════════════════════════════╗\n");
    gotoXY(x, y + 4);
    printf("║                                                ║\n");
    gotoXY(x, y + 5);
    printf(purple "║               " orange "╔═════════════════╗" off "              " purple "║\n");
    gotoXY(x, y + 6);
    printf("║               " orange "║ Nhập đa thức từ ║" purple "              ║\n");
    gotoXY(x, y + 7);
    printf("║               " orange "║   bàn phím      ║" purple "              ║\n");
    gotoXY(x, y + 8);
    printf("║               " orange "╚═════════════════╝" purple "              ║\n");
    gotoXY(x, y + 9);
    printf("║               " purple1 "╔═════════════════╗" purple "              ║\n");
    gotoXY(x, y + 10);
    printf("║               " purple1 "║ Nhập đa thức từ ║" purple "              ║\n");
    gotoXY(x, y + 11);
    printf("║               " purple1 "║       file      ║" purple "              ║\n");
    gotoXY(x, y + 12);
    printf("║               " purple1 "╚═════════════════╝" purple "              ║\n");
    gotoXY(x, y + 13);
    printf("║                                                ║\n");
    gotoXY(x, y + 14);
    printf("╚════════════════════════════════════════════════╝\n" off);
}

void MENU_INPUT()
{
    button_exit();
    button_return();
    menu_InputData();
}
void alert_message()
{
    int x = 25, y = 5;
    gotoXY(x, y);
    printf(purple1 "┌---------------------------------------------------------------┐\n");
    gotoXY(x, y + 1);
    printf("|     " red "Vui lòng nhập đa thức trước khi thực hiện tính toán" purple1 "       |\n");
    gotoXY(x, y + 2);
    printf("└---------------------------------------------------------------┘\n" off);
    gotoXY(x, y + 5);
    printf(green italic "Nhấn vào nút \"Quay lại\" để quay lại menu chính...." off);
}
void INTRO()
{ //
    int x = 15, y = 6;
    gotoXY(x, 2);
    printf(blue "╔═══════════════════════════════════════════════════════════════════════════════════════╗\n" off);
    gotoXY(x, 3);
    printf(blue "║                           " purple "       ╔══════════════╗       " off "                       " blue "       ║\n");
    gotoXY(x, 4);
    printf(blue "║                             " purple "     ║    NHÓM 8    ║  " off "                               " blue "    ║");
    gotoXY(x, 5);
    printf(blue "║                              " purple "    ╚══════════════╝       " off "                          " blue "    ║");
    gotoXY(x, y);
    printf(blue "║            " green " ĐỀ TÀI: " italic "Tìm nghiệm của phương trình đa thức bậc n bằng  " off "  " off "              " blue "  ║\n");
    gotoXY(x, y + 1);
    printf(blue "║                                                                                       ║\n" off);
    gotoXY(x, y + 2);
    printf(blue "║             " italic green "     phương pháp CHIA ĐÔI và phương pháp DÂY CUNG  " off "                 " blue "      ║\n");
    gotoXY(x, y + 3);
    printf(blue "┣────────────────────────────────────┳──────────────────────────────────────────────────┫\n" off);
    gotoXY(x, y + 4);
    printf(blue "║        " purple "  ╔-------------╗   " off "    " blue "    │ " off "      " purple "        ╔-----------------╗  " off "             " blue " ║\n");
    gotoXY(x, y + 5);
    printf(blue "║        " purple "  ║   " off " " purple "Mô tả" off " " purple "   ║ " off "     " blue "     │" off "        " purple "       ║ " off "" purple "Người thực hiện" off "" purple " ║" off "           " blue "     ║\n");
    gotoXY(x, y + 6);
    printf(blue "║          " purple "╚-------------╝  " off "    " blue "     │ " off "      " purple "        ╚-----------------╝ " off "           " blue "    ║\n");
    gotoXY(x, y + 7);
    printf(blue "┣────────────────────────────────────╋──────────────────────────────────────────────────┫\n" off);
    gotoXY(x, y + 8);
    printf(blue "║ " italic orange " - Đọc đa thức từ bàn phím" off "  " blue "       │ " off " " green "   1.       ĐOÀN HOÀNG THIÊN PHÚ   " off "       " blue "      ║\n");
    gotoXY(x, y + 9);
    printf(blue "║ " italic orange "   hoặc từ file " off "      " blue "       " blue "      │ " off "" italic green "    Lớp: 23T_DT3            MSSV: 102230313 " off "  " blue "   ║\n");
    gotoXY(x, y + 10);
    printf(blue "║ " italic orange " - Chọn phương pháp để tìm nghiệm" off "  " blue "│                                                 " blue " ║ \n");
    gotoXY(x, y + 11);
    printf(blue "║ " italic orange " - Đề xuất khoảng nghiệm " off "    " blue "      │ " off "" green "    2.       NGUYỄN THỊ THÙY  " off "   " blue "                ║\n");
    gotoXY(x, y + 12);
    printf(blue "║ " italic orange " - Nhập vào khoảng nghiệm cần tìm " off " " blue "│" off " " italic green "    Lớp: 23T_DT3            MSSV: 102230323 " off "  " blue "   ║\n");
    gotoXY(x, y + 13);
    printf(blue "║" italic orange "  - In kết quả ra màn hình và file" off " " blue " │                                                  " blue "║\n");
    gotoXY(x, y + 14);
    printf(blue "║                                " blue "    ┣──────────────────────────────────────────────────" blue "┫\n" off);
    gotoXY(x, y + 15);
    printf(blue "║                                 " blue "   │ " off " " red "   3. GIẢNG VIÊN HƯỚNG DẪN: ĐỖ THỊ TUYẾT HOA " off " " blue "  ║\n" off);
    gotoXY(x, y + 16);
    printf(blue "╚════════════════════════════════════┻══════════════════════════════════════════════════╝\n" off);
    if (intro_off == 0)
    {
        gotoXY(x, y + 17);
        printf(purple "                                                                  ╔----------------╗      \n" off);
        gotoXY(x, y + 18);
        printf(purple "                                                                  ║   Tiếp tục...  ║      \n" off);
        gotoXY(x, y + 19);
        printf(purple "                                                                  ╚----------------╝      \n" off);
    }
}

void input_keyboard(double poly[], int *n)
{
    isHavingData = 1;
label:;
    gotoXY(30, 5);
    printf("Nhập bậc của đa thức cần tính: ");
    scanf("%d", n);
    int i;
    if (*n < 0)
    {
        system("cls");
        gotoXY(30, 6);
        printf("Bậc của đa thức không hợp lệ! Vui lòng nhập lại");
        goto label;
    }
    for (i = *n; i >= 0; i--)
    {
        gotoXY(30, 8 + *n - i);
        printf("Nhập hệ số của x^%d: ", i);
        scanf("%lf", &poly[i]);
    }
    gotoXY(30, 8 + *n + 2);
    printf("Đã nhập xong đa thức... ");
    gotoXY(30, 8 + *n + 3);
    printf("Đa thức của bạn vừa nhập là: ");
    printPoly(poly, *n);
    gotoXY(30, 8 + *n + 4);
    printf("Nhấn vào nút quay lại để quay lại menu chính....");

    //   printf("Đa thức của bạn vừa nhập là: ");
    // coming soon xử lý in đa thức đẹp hơn.
}
int getMouseClick_main()
{

    click = processInputEvents();
    x_click = click.X;
    y_click = click.Y;
    if (x_click >= 42 && x_click <= 68 && y_click >= 8 && y_click <= 10)
    {
        x_click = 0;
        y_click = 100;
        return 2;
    }
    if (x_click >= 42 && x_click <= 70 && y_click >= 12 && y_click <= 14)
    {
        x_click = 0;
        y_click = 100;
        return 3;
    }
    if (x_click >= 47 && x_click <= 66 && y_click >= 16 && y_click <= 18)
    {
        x_click = 0;
        y_click = 100;
        return 4;
    }
    if (x_click >= 96 && x_click <= 119 && y_click >= 0 && y_click <= 2)
    {
        x_click = 0;
        y_click = 100;
        return -1;
    }
    if (x_click >= 47 && x_click <= 63 && y_click >= 5 && y_click <= 7) // button 1
    {
        x_click = 0;
        y_click = 100;
        return 1;
    }
    if (x_click >= 1 && x_click <= 17 && y_click >= 0 && y_click <= 2)
    {
        return 0;
    }
    if (x_click >= 96 && x_click <= 119 && y_click >= 0 && y_click <= 2)
    {
        return -1;
    }

    x_click = 0;
    y_click = 100;
    return -2;
}
int getMouseClick_intro()
{
    click = processInputEvents();
    x_click = click.X;
    y_click = click.Y;
    if (x_click >= 82 && x_click <= 105 && y_click >= 23 && y_click <= 26)
    {
        x_click = 0;
        y_click = 100;
        return 1;
    }
    x_click = 0;
    y_click = 100;
    return -2;
}
int getMouseClick_1()
{
    click = processInputEvents();
    x_click = click.X;
    y_click = click.Y;
    if (x_click >= 1 && x_click <= 17 && y_click >= 0 && y_click <= 2)
    {
        return 0;
    }
    if (x_click >= 96 && x_click <= 119 && y_click >= 0 && y_click <= 2)
    {
        return -1;
    }
    if (x_click >= 47 && x_click <= 68 && y_click >= 5 && y_click <= 7)
    {
        return 11;
    }
    if (x_click >= 47 && x_click <= 68 && y_click >= 9 && y_click <= 11)
    {
        return 12;
    }
    if (x_click >= 47 && x_click <= 68 && y_click >= 13 && y_click <= 15)
    {
        return 13;
    }
    return -2;
}
int getMouseClick_11()
{
    click = processInputEvents();
    ++count_exit;
    x_click = click.X;
    y_click = click.Y;
    if (x_click >= 1 && x_click <= 17 && y_click >= 0 && y_click <= 2)
    {
        return 0;
    }
    if (x_click >= 96 && x_click <= 119 && y_click >= 0 && y_click <= 2)
    {
        return -1;
    }
    return -2;
}

void readNameFile(char *fileName, int control_method)
{
    gotoXY(30, 5);
    if (control_method == 0)
    {
        printf(orange "Nhập tên file cần đọc: " off);
    }
    else
    {
        printf(orange "Nhập tên file cần ghi : " off);
    }
    fgets(fileName, 100, stdin);
    // xu ly dau \n khi nhap.
    int length = strlen(fileName);
    if (length > 0 && fileName[length - 1] == '\n')
    {
        fileName[length - 1] = '\0';
    }
    // gotoXY(30, 8);
    // printf("Đã nhập xong tên file... ");
    // gotoXY(30, 10);
    // printf("Nhấn vào nút quay lại để quay lại menu chính....");
}
void readPolyFromFile(FILE *file, char *fileName, double poly[], int *n)
{
label:;
    fscanf(file, "%d", n);
    if (*n < 0)
    {
        system("cls");
        gotoXY(30, 5);
        printf("Bậc của đa thức không hợp lệ");
        goto label;
        system("cls");
    }

    for (int i = *n; i >= 0; i--)
    {
        fscanf(file, "%lf", &poly[i]);
    }
    fclose(file);
}
void readDataFromFile(char *fileName, double poly[], int *n)
{
    isHavingData = 1;
    int cnt = 0;
    FILE *file;
    do
    {
        readNameFile(fileName, 0);
        file = fopen(fileName, "r");

        if (file == NULL)
        {
            system("cls");
            gotoXY(30, 7);
            printf(red italic "*Không thể mở file %s, vui lòng nhập lại tên file..... " off, fileName);
            gotoXY(30, 5);
        }
        ++cnt;
    } while (file == NULL);
    gotoXY(30, 7);
    printf(green italic "Đọc dữ liệu từ file %s thành công                              " off, fileName);
    readPolyFromFile(file, fileName, poly, n);

   
    gotoXY(30, 9 + 1);
    printf(orange "Đa thức của bạn là: " off);
    printPoly(poly, *n);
    gotoXY(30, 8 + 4);
    printf(green italic "Nhấn vào nút \"Quay lại\" để quay lại menu chính...." off);
}
void printPoly(double poly[], int n)
{
    char *superscripts[] = {"⁰", "¹", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "⁹", "¹⁰", "¹¹", "¹²", "¹³", "¹⁴", "¹⁵", "¹⁶", "¹⁷", "¹⁸", "¹⁹", "²⁰"};
    for (int i = n; i >= 0; i--)
    {
        if (poly[i] == 0)
        {
            continue;
        }
        if (i == n)
        { 
            if (poly[i] == 0)
            {
                continue;
            }
            if (poly[i] == 1)
            {
                printf("x%s ", superscripts[i]);
            }
            else if (poly[i] == -1)
            {
                printf("-x%s ", superscripts[i]);
            }
            else
            {
                printf("%.10gx%s ", poly[i], superscripts[i]);
            }
        }
        else if (i == 1)
        { 
            if (poly[i] > 0)
            {
                printf("+ %.10gx ", poly[i]);
            }
            else if (poly[i] < 0)
            {
                printf("- %.10gx ", -poly[i]);
            }
        }
        else if (i == 0)
        { 
            if (poly[i] > 0)
            {
                printf("+ %.10g", poly[i]);
            }
            else if (poly[i] < 0)
            {
                printf("- %.10g", -poly[i]);
            }
        }
        else
        { 
            if (poly[i] > 0)
            {
                printf("+ %.10gx%s ", poly[i], superscripts[i]);
            }
            else if (poly[i] < 0)
            {
                printf("- %.10gx%s ", -poly[i], superscripts[i]);
            }
        }
    }
    printf("\n");
}
double f(double a[], int n, double x)
{
    double res = a[n];
    for (int i = n - 1; i >= 0; i--)
    {
        res = res * x + a[i];
    }
    return handleZero(&res);
}

void rootRange_suggest(double a[], int n)
{
    double firstRange[100];
    nRoots = 0;
    for (double i = -1000; i < 1000; i += 0.1)
    {
        if ((f(a, n, i) * f(a, n, i + 0.1) < 0) || (f(a, n, i) * f(a, n, i + 0.1) == 0))
        {
            firstRange[nRoots] = i;
            ++nRoots;
            if (f(a, n, i) * f(a, n, i + 0.1) == 0)
                i += 0.1;
        }
    }
    double rootRange[100];
    int cntRoot = 0;
    for (int i = 0; i < nRoots; i++)
    {
        if (i == nRoots - 1)
        {
            rootRange[cntRoot] = firstRange[i] - 1;
            ++cntRoot;
            rootRange[cntRoot] = firstRange[i] + 1;
            break;
        }
        rootRange[cntRoot] = firstRange[i] - 1;
        ++cntRoot;

        rootRange[cntRoot] = firstRange[i + 1] - 0.1;

        ++cntRoot;
    }
    gotoXY(30, 7);
    printf(orange "Phương trình f(x)=0 có " red "%d" orange " nghiệm thực." off, nRoots);
    if (nRoots == 0)
    {
        return;
    }
    gotoXY(30, 8);
    printf(orange "Đề xuất các khoảng nghiệm là: " off);
    for (int i = 0; i < cntRoot; i += 2)
    {
        printf("(%0.6g,%0.6g)  ", rootRange[i], rootRange[i + 1]);
    }
}
void checkInputRange(double poly[], int n, double *a, double *b, int control_method)
{
    double fa, fb;

    do
    {
        gotoXY(30, 3);
        printf(orange "Đa thức f(x) của bạn là: " off);
        printPoly(poly, n);
        gotoXY(30, 5);
        if (control_method == 2)
        {
            printf(purple italic "Tìm nghiệm gần đúng của phương trình f(x)=0 trên bằng phương pháp dây cung\n" off);
        }
        else
        {
            printf(purple italic "Tìm nghiệm gần đúng của phương trình f(x)=0 trên bằng phương pháp chia đôi\n" off);
        }
        rootRange_suggest(poly, n);
        if (nRoots == 0)
        {
            return;
        }

        gotoXY(30, 10);
        printf(blue "Nhập khoảng nghiệm [a;b] :\n  " off);
        gotoXY(30, 11);
        printf(blue "Nhập a: " off);
        scanf("%lf", a);
        gotoXY(30, 12);
        printf(blue "Nhập b: " off);
        scanf("%lf", b);
        fa = f(poly, n, *a);
        fb = f(poly, n, *b);
        if (fa * fb > 0)
        {
            system("cls");
            button_exit();
            button_return();
            gotoXY(30, 14);
            printf(red italic "*Khoảng nghiệm [%0.6g;%0.6g] không phù hợp với phương pháp giải \n" off, *a, *b);
        }

    } while (f(poly, n, *a) * f(poly, n, *b) > 0);
    gotoXY(30, 14);
    printf("                                                                                                   ");
    if (fa * fb == 0)
    {
        if (fa == 0)
        {
            gotoXY(30, 13);
            printf(green "Nghiệm của đa thức trong đoạn [%0.6g;%0.6g] là : x = %0.6g\n" off, *a, *b, *a);
        }
        else
        {
            gotoXY(30, 13);
            printf(green "Nghiệm của đa thức trong đoạn [%0.6g;%0.6g] là : x = %0.6g\n" off, *a, *b, *b);
        }
    }
}
double bisectionMethod(double poly[], int n, double *a, double *b)
{
    data s;
    process_bisec = 1;
    double a_tmp = *a;
    double b_tmp = *b;
    double c;
    double final_a, final_b;
    double tmp;
    if (f(poly, n, *a) * f(poly, n, *b) == 0)
    {
        return 0;
    }

    if (*a > *b)
    {
        tmp = *a;
        *a = *b;
        *b = tmp;
    }
    printf(" %-40s\n", red "                                         Phương pháp chia đôi" off);

    printf("%-18s%-40s", " ", purple "╔═══════════════╦════════════════════╦═════════════════════════╦════════════════════╗\n" off);
    printf(purple "%-18s║" off orange "%-15s" purple "║" orange "%-20s" purple "║" orange "%-25s" purple "║" orange "%-20s" purple "║" off "\n", " ", "       a", "          b", "        c=(a+b)/2", "        f(c)");
    printf(purple "%-18s%-40s\n" off, " ", "╠═══════════════╬════════════════════╬═════════════════════════╬════════════════════╣");
    if (f(poly, n, *a) > 0 && f(poly, n, *b) < 0)
    {
        double swap_tmp = *a;
        *a = *b;
        *b = swap_tmp;
    }
    while (f(poly, n, *a) < 0 && f(poly, n, *b) > 0)
    {
        c = (*a + *b) / 2;
        final_a = *a;
        final_b = *b;
        if (f(poly, n, c) > 0)
            final_a = c;
        else
            final_b = c;
        if ((fabs(final_a - final_b) <= eps) || (f(poly, n, c) == 0))
        {
            printf(purple "%-18s%-40s\n" off, " ", "║───────────────║────────────────────║─────────────────────────║────────────────────║");
            printf(purple "%-18s║" green "%5s%-7.4g%-3s" purple "║" green "%-7s%-7.4g%-6s" purple "║" green "%-10s%-7.4g%-8s" purple "║" green "%-5s%-10.4g%-5s" purple "║" off "\n", " ", " ", *a, " ", " ", *b, " ", " ", c, " ", " ", f(poly, n, c), " ");
        }
        else
            printf(purple "%-18s║" red "%5s%-7.4g%-3s" purple "║" red "%-7s%-7.4g%-6s" purple "║" red "%-10s%-7.4g%-8s" purple "║" red "%-5s%-10.4g%-5s" purple "║" off "\n", " ", " ", *a, " ", " ", *b, " ", " ", c, " ", " ", f(poly, n, c), " ");

        if (f(poly, n, c) > 0)
        {
            *b = c;
        }
        else
            *a = c;

        if (f(poly, n, c) == 0)
        {
            printf(purple "%-18s%-40s" off, " ", "╚═══════════════╩════════════════════╩═════════════════════════╩════════════════════╝\n\n");

            printf(orange "          Nghiệm của đa thức trong đoạn [%.6g;%.6g] là :" green " x = %0.4g\n" off, a_tmp, b_tmp, c);
            s = createData(a_tmp, b_tmp, c);
            addDataToLog(logAns_bisec, s, logAns_bisec->count);
            result_file_3 = c;
            return 0;
        }
        if (fabs(*a - *b) <= eps)
        {
            printf(purple "%-18s%-40s" off, " ", "╚═══════════════╩════════════════════╩═════════════════════════╩════════════════════╝\n\n");

            printf(orange "          Nghiệm của đa thức trong đoạn [%.6g;%.6g] là :" green " x = %0.4g\n" off, a_tmp, b_tmp, *a);
            s = createData(a_tmp, b_tmp, *a);
            addDataToLog(logAns_bisec, s, logAns_bisec->count);
            result_file_3 = *a;
            return 0;
        }
    }

    return 0;
}
void BowstringMethod(double poly[], int n, double *a, double *b)
{
    data s;
    process_bows = 1;
    double final_a, final_b;
    double res;
    double a_temp = *a;
    double b_temp = *b;
    if (f(poly, n, *a) * f(poly, n, *b) == 0)
    {
        return;
    }
    printf(red " %-40s\n" off, "                                     Phương pháp dây cung");

    printf("%-18s%-40s", " ", purple "╔═══════════════╦════════════════════╦═════════════════════════╦════════════════════╗\n" off);
    printf(purple "%-18s║" off orange "%-15s" purple "║" orange "%-20s" purple "║" orange "%-25s" purple "║" orange "%-20s" purple "║" off "\n", " ", "       a", "          b", "           x", "        f(x)");
    printf(purple "%-18s%-40s\n" off, " ", "╠═══════════════╬════════════════════╬═════════════════════════╬════════════════════╣");

    res = *a - (*b - *a) * f(poly, n, *a) / (f(poly, n, *b) - f(poly, n, *a));

    printf(purple "%-18s║" red "%5s%-7.4g%-3s" purple "║" red "%-7s%-7.4g%-6s" purple "║" red "%-10s%-7.4g%-8s" purple "║" red "%-5s%-10.4g%-5s" purple "║" off "\n", " ", " ", *a, " ", " ", *b, " ", " ", res, " ", " ", f(poly, n, res), " ");

    if (f(poly, n, res) * f(poly, n, *a) < 0)
    {
        do
        {

            *b = res;
            final_a = *a;
            final_b = *b;
            res = *a - (*b - *a) * f(poly, n, *a) / (f(poly, n, *b) - f(poly, n, *a));
            if ((fabs(final_b - res) > eps || fabs(f(poly, n, res)) > eps) == 0)
            {
               
                printf(purple "%-18s%-40s\n" off, " ", "║───────────────║────────────────────║─────────────────────────║────────────────────║");
                printf(purple "%-18s║" green "%5s%-7.4g%-3s" purple "║" green "%-7s%-7.4g%-6s" purple "║" green "%-10s%-7.4g%-8s" purple "║" green "%-5s%-10.4g%-5s" purple "║" off "\n", " ", " ", *a, " ", " ", *b, " ", " ", res, " ", " ", f(poly, n, res), " ");
            }
            else
            {   
                printf(purple "%-18s║" red "%5s%-7.4g%-3s" purple "║" red "%-7s%-7.4g%-6s" purple "║" red "%-10s%-7.4g%-8s" purple "║" red "%-5s%-10.4g%-5s" purple "║" off "\n", " ", " ", *a, " ", " ", *b, " ", " ", res, " ", " ", f(poly, n, res), " ");
            }
        } while (fabs(*b - res) > eps || fabs(f(poly, n, res)) > eps);
    }
    else
    {
        if (f(poly, n, res) * f(poly, n, *b) < 0)
        {
            do
            {

                *a = res;
                final_a = *a;
                final_b = *b;
                res = *a - (*b - *a) * f(poly, n, *a) / (f(poly, n, *b) - f(poly, n, *a));
                if ((fabs(final_a - res) > eps || fabs(f(poly, n, res)) > eps) == 0)
                {   
                    
                    printf(purple "%-18s%-40s\n" off, " ", "║───────────────║────────────────────║─────────────────────────║────────────────────║");
                    printf(purple "%-18s║" green "%5s%-7.4g%-3s" purple "║" green "%-7s%-7.4g%-6s" purple "║" green "%-10s%-7.4g%-8s" purple "║" green "%-5s%-10.4g%-5s" purple "║" off "\n", " ", " ", *a, " ", " ", *b, " ", " ", res, " ", " ", f(poly, n, res), " ");
                }
                else
                {   
                    printf(purple "%-18s║" red "%5s%-7.4g%-3s" purple "║" red "%-7s%-7.4g%-6s" purple "║" red "%-10s%-7.4g%-8s" purple "║" red "%-5s%-10.4g%-5s" purple "║" off "\n", " ", " ", *a, " ", " ", *b, " ", " ", res, " ", " ", f(poly, n, res), " ");
                }
            } while (fabs(*a - res) > eps || fabs(f(poly, n, res)) > eps);
        }
    }

    printf(purple "%-18s%-40s" off, " ", "╚═══════════════╩════════════════════╩═════════════════════════╩════════════════════╝\n\n");

    printf(orange "          Nghiệm của đa thức trong đoạn [%.6g;%.6g] là :" green " x = %0.4g\n" off, a_temp, b_temp, res);
    s = createData(a_temp, b_temp, res);
    addDataToLog(logAns_bows, s, logAns_bows->count);
    result_file_2 = res;
}

void ensureFileSize(FILE *file, int y)
{

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);

    long requiredSize = (y + 1) * LINE_WIDTH;

    if (fileSize < requiredSize)
    {

        fseek(file, fileSize, SEEK_SET);
        for (long i = fileSize; i < requiredSize; i++)
        {
            if ((i + 1) % LINE_WIDTH == 0)
            {
                fputc('\n', file);
            }
            else
            {
                fputc(' ', file);
            }
        }
    }
}
void writeAtPosition(FILE *file, int x, int y, const char *format, ...)
{

    ensureFileSize(file, y);

    long offset = y * LINE_WIDTH + x;

    fseek(file, offset, SEEK_SET);

    va_list args;
    va_start(args, format);

    vfprintf(file, format, args);

    va_end(args);
}
void printPolyToFile(FILE *file, double poly[], int n)
{
    char *superscripts[] = {"⁰", "¹", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "⁹", "¹⁰", "¹¹", "¹²", "¹³", "¹⁴", "¹⁵", "¹⁶", "¹⁷", "¹⁸", "¹⁹", "²⁰"};

    for (int i = n; i >= 0; i--)
    {
        if (poly[i] == 0)
        {
            continue;
        }
        if (i == n)
        { // Highest degree term

            if (poly[i] == 0)
            {
                continue;
            }
            if (poly[i] == 1)
            {
                fprintf(file, "x%s ", superscripts[i]);
            }
            else if (poly[i] == -1)
            {
                fprintf(file, "-x%s ", superscripts[i]);
            }
            else
            {
                fprintf(file, "%0.6gx%s ", poly[i], superscripts[i]);
            }
        }
        else if (i == 1)
        { // x term
            if (poly[i] > 0)
            {
                fprintf(file, " + %0.6gx", poly[i]);
            }
            else if (poly[i] < 0)
            {
                fprintf(file, " - %0.6gx", -poly[i]);
            }
        }
        else if (i == 0)
        { // Constant term
            if (poly[i] > 0)
            {
                fprintf(file, " + %0.6g", poly[i]);
            }
            else if (poly[i] < 0)
            {
                fprintf(file, " - %0.6g", -poly[i]);
            }
        }
        else
        { // Other terms
            if (poly[i] > 0)
            {
                fprintf(file, " + %0.6gx%s ", poly[i], superscripts[i]);
            }
            else if (poly[i] < 0)
            {
                fprintf(file, " - %0.6gx%s ", -poly[i], superscripts[i]);
            }
        }
    }
    fprintf(file, " = 0\n");
}

void writeDataToFile(char fileName_1[], int n, double poly[])
{
    int x = 10, y = 3;
    if (logAns_bows->count == 0 && logAns_bisec->count == 0)
    {
        gotoXY(x + 20, y + 3);
        // printf("Không có dữ liệu để ghi vào file");
        printf(purple1 "┌---------------------------------------------------------------┐\n");
        gotoXY(x + 20, y + 4);
        printf("|               " red "Không có dữ liệu để ghi vào File" purple1 "                |\n");
        gotoXY(x + 20, y + 5);
        printf("└---------------------------------------------------------------┘\n" off);
        gotoXY(x + 20, y + 7);

        printf(green italic "Nhấn vào nút \"Quay lại\" để quay lại menu chính...." off);
        return;
    }
    FILE *file;
    int i;

    do
    {
        gotoXY(30, 5);
        readNameFile(fileName_1, 1);
        file = fopen(fileName_1, "w");

    } while (file == NULL);
    writeAtPosition(file, 20, 0, "Giải phương trình:  ");
    printPolyToFile(file, poly, n);
    gotoXY(30, 9);
    printf(green italic "Đã ghi vào file %s" off, fileName_1);

    if (logAns_bisec->count > 0)
    {
        writeAtPosition(file, x, y, "Các nghiệm gần đúng của phương trình trên đã tìm bằng phương pháp CHIA ĐÔI là:");
        fprintf(file, "\n");

        for (i = 0; i < logAns_bisec->count; i++)
        {
            fprintf(file, "\n");
            fprintf(file, "   -Trên khoảng [%.6g;%.6g] là: x = %.6g", logAns_bisec->list[i]->a, logAns_bisec->list[i]->b, logAns_bisec->list[i]->ans);
        }
    }
    if (logAns_bows->count > 0)
    {
        writeAtPosition(file, x, y + logAns_bisec->count + 3, "Các nghiệm gần đúng của phương trình trên đã tìm bằng phương pháp DÂY CUNG là:");
        fprintf(file, "\n");

        for (i = 0; i < logAns_bows->count; i++)
        {
            fprintf(file, "\n");
            fprintf(file, "   -Trên khoảng [%.6g;%.6g] là: x = %.6g", logAns_bows->list[i]->a, logAns_bows->list[i]->b, logAns_bows->list[i]->ans);
        }
    }

    fclose(file);
}

Log createLog(int max_size)
{
    Log cls = (ListInfo *)malloc(sizeof(struct ListInfo));
    cls->count = 0;
    cls->max_size = max_size;
    cls->list = (data *)malloc(max_size * sizeof(data));
    return cls;
}

data createData(double a, double b, double ans)
{
    data std = (dataLog *)malloc(sizeof(struct dataLog));
    std->a = a;
    std->b = b;
    std->ans = ans;
    return std;
}

void addDataToLog(Log cls, data s, Position p)
{
    Position current;
    if (p > cls->count || cls->count == cls->max_size)
        return;
    current = cls->count;
    while (current != p)
    {
        cls->list[current] = cls->list[current - 1];
        current--;
    }
    cls->list[current] = s;
    cls->count++;
}
