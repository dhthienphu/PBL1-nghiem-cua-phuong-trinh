#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <math.h>
// isClick(1, 17, 0, 3) == return
// isClick(96, 119, 0, 2) == exit
HANDLE hStdin;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
COORD click;

int x_click, y_click;
int count_exit = 0;
int prev_x = 0, prev_y = 0;
void gotoXY(int x, int y);

COORD processInputEvents();
VOID WriteError(LPCSTR lpszMessage);
void getMouseClick();
int isClick_main();
int isClick_inputData();
int getMouseClick_main();
int getMouseClick_1();
int getMouseClick_11();

void button_return();
void button_exit();
void menu_main();
void Dashboard();
void menu_InputData();
void MENU_INPUT();

void loading_message(char *message);
void input_keyboard(double poly[], int *n);

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    int n;
    double poly[100];
    int choice_main, choice_1, choice_11;

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
        choice_main = getMouseClick_1();
        if (choice_main == -2)
        {
            system("cls");
            goto label_1;
        }
        x_click = 0;
        y_click = 100;

        switch (choice_main)
        {
        // ----> case 11 <------
        case 11:
            system("cls");

            input_keyboard(poly, &n);
            button_exit();
            button_return();
        // gotoXY(20,20);
        // printf("Nhap n: ");
        // scanf("%d", &n);
        // printf("huhu");
        // getchar();
        // gotoXY(30, 8 + n + 6);
        // printf("huhuhuuhuh");
        // printf("%d     ",choice_11);
        label_11:;
            choice_11 = getMouseClick_11();
            if (choice_11 == -2)
            {
                Sleep(1);
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
        case 12:
            printf("coming soon");

            break;
        }
        break;
        // ----> case 1 <------
    }

label_exit:;
}
VOID WriteError(LPCSTR lpszMessage)
{
    printf("%s\n", lpszMessage);
    ExitProcess(0);
}
// hàm này d? l?y v? trí chu?t trên std
COORD processInputEvents()
{
    DWORD cNumRead, fdwMode, i;
    INPUT_RECORD irInBuf[128];

    // Get the standard input handle.
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        WriteError("GetStdHandle");

    // Set the console mode
    fdwMode = ENABLE_EXTENDED_FLAGS;
    if (!SetConsoleMode(hStdin, fdwMode))
    {
        WriteError("SetConsoleMode");
    }

    // Set the console mode to accept input
    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
    if (!SetConsoleMode(hStdin, fdwMode))
    {
        WriteError("SetConsoleMode");
    }

    // Loop until a mouse click event is detected
    while (true)
    {
        // Peek at the event
        if (!PeekConsoleInput(hStdin, irInBuf, 128, &cNumRead))
        {
            WriteError("PeekConsoleInput");
        }
        // Process each event
        for (i = 0; i < cNumRead; i++)
        {
            if (irInBuf[i].EventType == MOUSE_EVENT && irInBuf[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED)
            {
                // Remove the event from the buffer
                INPUT_RECORD dummy;
                DWORD dummyNumRead;
                ReadConsoleInput(hStdin, &dummy, 1, &dummyNumRead);

                // Flush the console input buffer
                FlushConsoleInputBuffer(hStdin);

                return irInBuf[i].Event.MouseEvent.dwMousePosition;
            }
        }
    }
}

void getMouseClick()
{
    click = processInputEvents();
    x_click = click.X;
    y_click = click.Y;
}
int isClick_main()
{

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

    x_click = 0;
    y_click = 100;
    return -2;
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
    printf("┌---------┐");
    gotoXY(1, 0 + 1);
    printf("| Trở lại |");
    gotoXY(1, 0 + 2);
    printf("└---------┘");
}
void button_exit()
{
    gotoXY(96, 0);
    printf("┌----------------------┐");
    gotoXY(96, 0 + 1);
    printf("|  Thoát chương trình  |");
    gotoXY(96, 0 + 2);
    printf("└----------------------┘");
}
void menu_main()
{
    int x = 30, y = 0;
    gotoXY(x, y);
    printf("               ┌---------------┐            \n");
    gotoXY(x, y + 1);
    printf("               |      MENU     |            \n");
    gotoXY(x, y + 2);
    printf("               └---------------┘            \n");
    gotoXY(x, y + 3);

    printf("┌---------------------------------------------┐\n");
    gotoXY(x, y + 4);
    printf("|                                             |\n");
    gotoXY(x, y + 5);
    printf("|               ┌--------------┐              |\n");
    gotoXY(x, y + 6);
    printf("|       1       | Nhập dữ liệu |              |\n");
    gotoXY(x, y + 7);
    printf("|               └--------------┘              |\n");
    gotoXY(x, y + 8);
    printf("|          ┌------------------------┐         |\n");
    gotoXY(x, y + 9);
    printf("|       2  | Giải phương trình bằng |         |\n");
    gotoXY(x, y + 10);
    printf("|          | phương pháp dây cung   |         |\n");
    gotoXY(x, y + 11);
    printf("|          └------------------------┘         |\n");
    gotoXY(x, y + 12);
    printf("|          ┌------------------------┐         |\n");
    gotoXY(x, y + 13);
    printf("|       3  | Giải phương trình bằng |         |\n");
    gotoXY(x, y + 14);
    printf("|          | phương pháp chia đôi   |         |\n");
    gotoXY(x, y + 15);
    printf("|          └------------------------┘         |\n");
    gotoXY(x, y + 16);
    printf("|               ┌--------------┐              |\n");
    gotoXY(x, y + 17);
    printf("|       4       | Xuất dữ liệu |              |\n");
    gotoXY(x, y + 18);
    printf("|               └--------------┘              |\n");
    gotoXY(x, y + 19);
    printf("|                                             |\n");
    gotoXY(x, y + 20);
    printf("└---------------------------------------------┘\n");
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
    char message[] = "Mời bạn chọn phương thức nhập dữ liệu.....";
    gotoXY(x, y);
    // loading_message(message);
    gotoXY(x, y + 3);
    printf("┌------------------------------------------------┐\n");
    gotoXY(x, y + 4);
    printf("|                                                |\n");
    gotoXY(x, y + 5);
    printf("|               ┌-----------------┐              |\n");
    gotoXY(x, y + 6);
    printf("|         1     | Nhập dữ liệu từ |              |\n");
    gotoXY(x, y + 7);
    printf("|               |    bàn phím     |              |\n");
    gotoXY(x, y + 8);
    printf("|               └-----------------┘              |\n");
    gotoXY(x, y + 9);
    printf("|               ┌-----------------┐              |\n");
    gotoXY(x, y + 10);
    printf("|         2     | Nhập dữ liệu từ |              |\n");
    gotoXY(x, y + 11);
    printf("|               |       file      |              |\n");
    gotoXY(x, y + 12);
    printf("|               └-----------------┘              |\n");
    gotoXY(x, y + 13);
    printf("|               ┌-----------------┐              |\n");
    gotoXY(x, y + 14);
    printf("|         3     | Nhập dữ liệu từ |              |\n");
    gotoXY(x, y + 15);
    printf("|               |      random     |              |\n");
    gotoXY(x, y + 16);
    printf("|               └-----------------┘              |\n");
    gotoXY(x, y + 17);
    printf("|                                                |\n");
    gotoXY(x, y + 18);
    printf("└------------------------------------------------┘\n");
}
void MENU_INPUT()
{
    button_exit();
    button_return();
    menu_InputData();
}
int isClick_inputData()
{
    if (x_click >= 1 && x_click <= 17 && y_click >= 0 && y_click <= 2)
    {
        return 0;
    }
    if (x_click >= 96 && x_click <= 119 && y_click >= 0 && y_click <= 2)
    {
        return -1;
    }
    if (x_click >= 37 && x_click <= 53 && y_click >= 5 && y_click <= 7)
    {
        return 11;
    }
    if (x_click >= 37 && x_click <= 53 && y_click >= 9 && y_click <= 11)
    {
        return 12;
    }
    if (x_click >= 37 && x_click <= 53 && y_click >= 13 && y_click <= 15)
    {
        return 13;
    }
    return -2;
}

void input_keyboard(double poly[], int *n)
{
    gotoXY(30, 5);
    printf("Nhập bậc của đa thức cần tính: ");
    scanf("%d", n);
    int i;
    for (i = *n; i >= 0; i--)
    {
        gotoXY(30, 8 + *n - i);
        printf("Nhập hệ số của x^%d: ", i);
        scanf("%lf", &poly[i]);
    }
    gotoXY(30, 8 + *n + 2);
    printf("Đã nhập xong đa thức... ");
    gotoXY(30, 8 + *n + 4);
    printf("Nhấn vào nút quay lại để quay lại menu chính....");

    //   printf("Đa thức của bạn vừa nhập là: ");
    // coming soon xử lý in đa thức đẹp hơn.
}

int getMouseClick_main()
{   prev_x=x_click;
    prev_y=y_click;
    if(abs(prev_x-x_click)>1 || abs(prev_y-y_click)>1)
    {
        return -2;
    }
    click = processInputEvents();
    x_click = click.X;
    y_click = click.Y;
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
    if (x_click >= 37 && x_click <= 53 && y_click >= 5 && y_click <= 7)
    {
        return 11;
    }
    if (x_click >= 37 && x_click <= 53 && y_click >= 9 && y_click <= 11)
    {
        return 12;
    }
    if (x_click >= 37 && x_click <= 53 && y_click >= 13 && y_click <= 15)
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