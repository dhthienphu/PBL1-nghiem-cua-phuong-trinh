#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>
// isClick(1, 17, 0, 3) == return
// isClick(96, 119, 0, 2) == exit
HANDLE hStdin;
HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;
COORD click;
#define eps 0.00001

int nRoots;
int x_click, y_click;
int count_exit = 0;
int prev_x = 0, prev_y = 0;
void gotoXY(int x, int y);
double result_file_2;
double result_file_3;

COORD processInputEvents();
VOID WriteError(LPCSTR lpszMessage);
void getMouseClick();
int isClick_main();
int isClick_inputData();
int getMouseClick_main();
int getMouseClick_1();
int getMouseClick_11();
void rootRange_suggest(double a[], int n);
double f(double a[], int n, double x);
void checkInputRange(double poly[], int n, double *a, double *b, int control_method);
double bisectionMethod(double poly[], int n, double *a, double *b);
void BowstringMethod(double poly[], int n, double *a, double *b);
void writeDataToFile(char fileName[], double poly[], int n);

void input_keyboard(double poly[], int *n);
void readNameFile(char *fileName);
void readPolyFromFile(FILE *file, char *fileName, double poly[], int *n);
void readDataFromFile(char *fileName, double poly[], int *n);
void printPoly(double poly[], int n);

void button_return();
void button_exit();
void menu_main();
void Dashboard();
void menu_InputData();
void MENU_INPUT();

void loading_message(char *message);

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    int n;
    double a, b;
    double poly[100];
    int choice_main, choice_1, choice_11, choice_12, choice_3, choice_2;
    char fileName[100];
    char *fileResult;

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
        case 13:
            system("cls");
            button_exit();
            button_return();
            // coming soon random data.
            break;
        }
        break;
        // ----> case 1 <------
        // ----> case 3 <------
    case 3:
        system("cls");
        button_exit();
        button_return();
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
        writeDataToFile(fileResult, poly, n);
        // coming soon output data.
        break;
    }

label_exit:;
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
            if (irInBuf[i].EventType == MOUSE_EVENT &&
                irInBuf[i].Event.MouseEvent.dwButtonState == FROM_LEFT_1ST_BUTTON_PRESSED &&
                irInBuf[i].Event.MouseEvent.dwEventFlags == 0) // Check if it's a click event
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
    COORD defaultCoord = {100, 100};
    return defaultCoord;
}
void getMouseClick()
{
    click = processInputEvents();
    x_click = click.X;
    y_click = click.Y;
}
int isClick_main()
{
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
    if (x_click >= 46 && x_click <= 66 && y_click >= 5 && y_click <= 7) // button 1
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
    printf("┌----------┐");
    gotoXY(1, 0 + 1);
    printf("| Quay lại |");
    gotoXY(1, 0 + 2);
    printf("└----------┘");
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
    char *superscripts[] = {"⁰", "¹", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "⁹", "¹⁰", "¹¹", "¹²", "¹³", "¹⁴", "¹⁵", "¹⁶", "¹⁷", "¹⁸", "¹⁹", "²⁰"};
    gotoXY(30, 5);
    printf("Nhập bậc của đa thức cần tính: ");
    scanf("%d", n);
    int i;
    for (i = *n; i >= 0; i--)
    {
        gotoXY(30, 8 + *n - i);
        printf("Nhập hệ số của x%s: ", superscripts[i]);
        scanf("%lf", &poly[i]);
    }
    gotoXY(30, 8 + *n + 2);
    printf("Đã nhập xong đa thức... ");
    gotoXY(30, 8 + *n + 3);
    printf("Đa thức của bạn vừa nhập là: ");
    printPoly(poly, *n);
    gotoXY(30, 8 + *n + 4);
    printf("Nhấn vào nút \"Quay lại\" để quay lại menu chính....");
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
void readNameFile(char *fileName)
{
    gotoXY(30, 5);
    printf("Nhập tên file cần đọc: ");
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

    fscanf(file, "%d", n);
    for (int i = *n; i >= 0; i--)
    {
        fscanf(file, "%lf", &poly[i]);
    }
    fclose(file);
}
void readDataFromFile(char *fileName, double poly[], int *n)
{
    int cnt = 0;
    FILE *file;
    do
    {
        readNameFile(fileName);
        file = fopen(fileName, "r");

        if (file == NULL)
        {
            system("cls");
            gotoXY(30, 6);
            printf("Không thể mở file %s, vui lòng nhập lại tên file..... ", fileName);
            gotoXY(30, 5);
        }
        ++cnt;
    } while (file == NULL);
    gotoXY(30, 6);
    printf("Đọc dữ liệu từ file %s thành công.................. ", fileName);
    readPolyFromFile(file, fileName, poly, n);
    gotoXY(30, 8);
    printf("Đã nhập xong đa thức từ %s... ", fileName);
    // coming soon in đa thức.
    gotoXY(30, 8 + 1);
    printf("Đa thức của bạn là: ");
    printPoly(poly, *n);
    gotoXY(30, 8 + 3);
    printf("Nhấn vào nút \"Quay lại\" để quay lại menu chính....");
}
void printPoly(double poly[], int n)
{
    char *superscripts[] = {"⁰", "¹", "²", "³", "⁴", "⁵", "⁶", "⁷", "⁸", "⁹", "¹⁰", "¹¹", "¹²", "¹³", "¹⁴", "¹⁵", "¹⁶", "¹⁷", "¹⁸", "¹⁹", "²⁰"};
    for (int i = n; i >= 0; i--)
    {
        if (i == n)
        { // Highest degree term
            printf("%.10gx%s ", poly[i], superscripts[i]);
        }
        else if (i == 1)
        { // x term
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
        { // Constant term
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
        { // Other terms
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
    return res;
}
void rootRange_suggest(double a[], int n)
{
    double firstRange[100];
    nRoots = 0;
    for (double i = -1000; i < 1000; i += 0.1)
    {
        if (f(a, n, i) * f(a, n, i + 0.1) < 0)
        {
            firstRange[nRoots] = i;
            ++nRoots;
        }
    }
    double rootRange[100];
    int cntRoot = 0;
    for (int i = 0; i < nRoots; i++)
    {
        rootRange[cntRoot] = firstRange[i] - 1;
        ++cntRoot;

        rootRange[cntRoot] = ceil(firstRange[i]);
        if (rootRange[cntRoot] == 0)
        {
            rootRange[cntRoot] = 0;
        }
        ++cntRoot;
    }
    gotoXY(30, 6);
    printf("Phương trình f(x)=0 có %d nghiệm thực.", nRoots);
    if (nRoots == 0)
    {
        return;
    }
    gotoXY(30, 7);
    printf("Đề xuất khoảng nghiệm là: ");
    for (int i = 0; i < cntRoot; i += 2)
    {
        printf("(%0.6g,%0.6g)  ", rootRange[i], rootRange[i + 1]);
    }
}
void checkInputRange(double poly[], int n, double *a, double *b, int control_method)
{
    double fa, fb;
    // gotoXY(30, 5);
    // printf("Đa thức f(x) của bạn là: ");
    // printPoly(poly, n);
    // gotoXY(30,7);
    // printf("Tìm nghiệm gần đúng của phương trình f(x)=0 trên bằng phương pháp chia đôi\n");

    do
    {
        gotoXY(30, 3);
        printf("Đa thức f(x) của bạn là: ");
        printPoly(poly, n);
        gotoXY(30, 4);
        if (control_method == 2)
        {
            printf("Tìm nghiệm gần đúng của phương trình f(x)=0 trên bằng phương pháp dây cung\n");
        }
        else
        {
            printf("Tìm nghiệm gần đúng của phương trình f(x)=0 trên bằng phương pháp chia đôi\n");
        }
        rootRange_suggest(poly, n);
        if (nRoots == 0)
        {
            return;
        }

        gotoXY(30, 9);
        printf("Nhập khoảng nghiệm [a;b] :\n  ");
        gotoXY(30, 10);
        printf("Nhập a: ");
        scanf("%lf", a);
        gotoXY(30, 11);
        printf("Nhập b: ");
        scanf("%lf", b);
        fa = f(poly, n, *a);
        fb = f(poly, n, *b);
        if (fa * fb > 0)
        {
            system("cls");
            gotoXY(30, 13);
            printf("*Vui lòng nhập lại khoảng nghiệm, không tồn tại nghiệm trong đoạn [%0.6g;%0.6g]\n", *a, *b);
        }

    } while (f(poly, n, *a) * f(poly, n, *b) > 0);
    gotoXY(30, 13);
    printf("                                                                                                   ");
    if (fa * fb == 0)
    {
        if (fa == 0)
        {
            gotoXY(30, 13);
            printf("Nghiệm của đa thức trong đoạn [%0.6g;%0.6g] là : x = %0.6g\n", *a, *b, *a);
        }
        else
        {
            gotoXY(30, 13);
            printf("Nghiệm của đa thức trong đoạn [%0.6g;%0.6g] là : x = %0.6g\n", *a, *b, *b);
        }
    }
}
double bisectionMethod(double poly[], int n, double *a, double *b)
{
    double a_tmp = *a;
    double b_tmp = *b;
    double c;
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
    printf("--------------------------Phương pháp chia đôi-----------------------\n");
    printf(" a              |        b           |       c=(a+b)/2           |          f(c)          \n");

    while (f(poly, n, *a) < 0 && f(poly, n, *b) > 0)
    {
        c = (*a + *b) / 2;
        printf(" %0.6g   |     %0.6g       |    %0.6g       |   %0.6g    \n ", *a, *b, c, f(poly, n, c));
        if (f(poly, n, c) > 0)
        {
            *b = c;
        }
        else
            *a = c;
        if (f(poly, n, c) == 0)
        {
            printf("Nghiệm của đa thức trong đoạn [%.6g;%.6g] là : x = %0.6g\n", a_tmp, b_tmp, c);
            result_file_3 = c;
            return 0;
        }
        if (fabs(*a - *b) <= eps)
        {
            printf("Nghiệm của đa thức trong đoạn [%.6g;%.6g] là : x = %0.6g\n", a_tmp, b_tmp, *a);
            result_file_3 = *a;
            return 0;
        }
    }
    while (f(poly, n, *a) > 0 && f(poly, n, *b) < 0)
    {
        c = (*a + *b) / 2;
        printf(" %0.6g     |     %0.6g       |    %0.6g       |   %0.6g    \n ", *a, *b, c, f(poly, n, c));
        if (f(poly, n, c) < 0)
        {
            *b = c;
        }
        else
            *a = c;
        if (f(poly, n, c) == 0)
        {
            printf("Nghiệm của đa thức trong đoạn [%.6g;%.6g] là : x = %0.6g\n", a_tmp, b_tmp, c);
            result_file_3 = c;
            return 0;
        }
        if ((fabs(*a - *b) <= eps))
        {
            printf("Nghiệm của đa thức trong đoạn [%.6g;%.6g] là : x = %0.6g\n", a_tmp, b_tmp, *a);
            result_file_3 = *a;
            return 0;
        }
    }
}
void BowstringMethod(double poly[], int n, double *a, double *b)
{
    double res;
    double a_temp = *a;
    double b_temp = *b;
    printf("--------------------------Phương pháp dây cung-----------------------\n");
    printf("    a         |      b          |      x          |      f(x)        |\n");
    do
    {

        if (f(poly, n, *a) > 0 && f(poly, n, *b) < 0)

        {

            int tam = *a;
            *a = *b;
            *b = tam;
        }
        res = *a - (*b - *a) * f(poly, n, *a) / (f(poly, n, *b) - f(poly, n, *a));
        printf("    %0.6g    |      %0.6g     |      %0.6g      |      %0.6g     |\n", *a, *b, res, f(poly, n, res));
        if (f(poly, n, res) < 0)
            *a = res;
        else
            *b = res;

    } while (fabs(*a - *b) > eps && f(poly, n, res) > eps);
    printf("Nghiệm của đa thức trong đoạn [%0.6g; %0.6g] là : x= %0.6g\n", a_temp, b_temp, res);
    result_file_2 = res;
}

