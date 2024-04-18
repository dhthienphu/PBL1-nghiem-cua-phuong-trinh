#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

float matrixAns_sum[100][100];
float matrixAns_multi[100][100];
float matrixA[100][100];
float matrixB[100][100];

char *notice_main = "Please input again, your input doesn't match the menu............";
char *notice_1 = "Please input again, you can choose 1 or 2 to continue...... ";
char *notice_2345 = "Don't have a DATA, please choose 1 to input data ......... ";
char *notice_6 = "Don't have a DATA to print, please choose 1 to input data....... ";
char *notice_er = "Please input again, you can choose \"r\" or \"e\" to continue.....";
char time_str[12];

char Input_Choice(int n, char *notice, int control);
void MENU_MAIN();
void MENU_1();
void MENU_2();
void print_result_sum(int n);
void MENU_3();
void print_result_multi(int n);
void InputData_keyboard(float matrixA[][100], float matrixB[][100], int *n);
void gotoxy(int x, int y);

int checkData(FILE *file, float matrixA[100][100], int *n, int *check);
void out(float matrix[100][100], int n);
void sumAndmulti(float matrixA[100][100], float matrixB[100][100], int n);
void Swap(float *a, float *b);
void replace_multi(float matrix[100][100], int n, int *p, int *q);
void readMatrixFromFile(FILE *file, float matrixA[100][100], int *n, int *check);
void printMatrixToFile(FILE *file, float matrix[100][100], int n);
void readNameFile(char *fileName, int cnt);
void rewriteFileName(char *fileName, FILE *file, int cnt, float matrix[100][100], int *n, int check);
void printResultToFile(FILE *file, char *fileName, int n);
void printMatrixSumAndMulti(float matrixA[][100], float matrixB[][100], int n);
void permutation_Matrix(float matrix[][100], int n);

int main()
{
    char fileName1[100], fileName2[100], fileName3[100];
    int n, p, q, num_1, num_2, check1 = 1, check2 = 1;
    char choice_main, choice_1;
    int isHavingData = 0;
    FILE *file1, *file2, *file3;
    // Lấy thời gian hiện tại
    time_t current_time = time(NULL);

    strftime(time_str, sizeof(time_str), "%I:%M %p", localtime(&current_time));

label_main:;
    MENU_MAIN();
    choice_main = Input_Choice(6, notice_main, 0);
    switch (choice_main)
    {
        //-->input1<--
    case '1':
        system("cls");
        MENU_1();
        choice_1 = Input_Choice(2, notice_1, 1);
        switch (choice_1)
        {
        case '1':
            // input from file
            do
            {
                rewriteFileName(fileName1, file1, 1, matrixA, &num_1, check1);
                rewriteFileName(fileName2, file2, 2, matrixB, &num_2, check2);
                if (num_1 != num_2)
                {
                    printf("2 ma tran khong cung cap, yeu cau nhap lai file \n");
                }
                else
                {
                    n = num_1;
                }
            } while (num_1 != num_2);
            isHavingData = 1;
            printf("%s --- Message  --- Input Data successfully....\n", time_str);
            // input choice for r or e
            char choice_1_1 = Input_Choice(0, notice_er, 1);
            // return dashboard or exit program.

            if (choice_1_1 == 'r')
            {
                system("cls");
                goto label_main;
            }
            else
            {
                system("cls");
                goto label_exit;
            }
            break;
        case '2':
            // input from keyboard
            InputData_keyboard(matrixA, matrixB, &n);
            isHavingData = 1;
            printf("%s Message  --- Input Data successfully....\n", time_str);
            char choice_1_1 = Input_Choice(0, notice_er, 1);
            // return dashboard or exit program.
            if (choice_1_1 == 'r')
            {
                system("cls");
                goto label_main;
            }
            else
            {
                system("cls");
                goto label_exit;
            }
            break;
        case 'r':
            goto label_main;
            break;
        }
        break;
    //-->input1<--
    //-->input2<--
    case '2':
        system("cls");
        if (isHavingData == 0)
        {
            printf("%s --- Message --- Don't have a DATA, please press \"r\" to return menu main then press 1 to input data .... \n", time_str);
            char choice_2 = Input_Choice(0, "", 1);
            if (choice_2 == 'r')
            {
                system("cls");
                goto label_main;
            }
        }
        else
        {
            MENU_2();
            print_result_sum(n);
            char choice_2 = Input_Choice(0, notice_er, 1);
            // return dashboard or exit program.
            if (choice_2 == 'r')
            {
                system("cls");
                goto label_main;
            }
            else
            {
                system("cls");
                goto label_exit;
            }
            break;
        }

        break;
        //-->input2<--
    }

label_exit:;
}

// chinh lai ham input choice: them nhap r de return va nhap e de ket thuc...

char Input_Choice(int n, char *notice, int control)
{
    if (control == 1)
    {
        printf("--Press \"r\" to return the main menu....\n");
        printf("--Press \"e\" to close program...");
    }
    int c, d, check = 0;
    do
    {
        printf("Input your choice: ");
        c = getchar();
        if (c == '\n')
        {
            continue;
        }
        if (c == 'r' || c == 'e')
        {
            break;
        }
        for (int i = 49; i <= 49 + n - 1; i++)
        {

            if ((int)c == i)
            {
                check = 1;
                break;
            }
        }
        if (check == 1)
        {
            break;
        }

        d = getchar();
        while (d != '\n')
        {
            d = getchar();
        }
        printf("%s \n", notice);
    } while (1);
    printf("--------Input successfully-------");
    return c;
}

void out(float matrix[100][100], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%6.2lf ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
void sumAndmulti(float matrixA[100][100], float matrixB[100][100], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrixAns_sum[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrixAns_multi[i][j] = 0;
            for (int k = 0; k < n; k++)
            {
                matrixAns_multi[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
}
void permutation_Matrix(float matrix[][100], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = matrix[j][i];
        }
    }
}
void Swap(float *a, float *b)
{
    float tmp = *b;
    *b = *a;
    *a = tmp;
}
void replace_multi(float matrix[100][100], int n, int *p, int *q)
{
    int a, b;
    do
    {
        printf("Nhap 2 cot can doi (<=%d): ", n);
        scanf("%d %d", p, q);
        a = *p - 1;
        b = *q - 1;
        if (a < 0 || a > n - 1 || b < 0 || b > n - 1)
            printf("Co cot khong ton tai yeu cau nhap lai. \n\n");
        else
            break;
    } while (1);
    for (int i = 0; i < n; i++)
    {
        Swap(&matrix[i][a], &matrix[i][b]);
    }
}
int checkData(FILE *file, float matrixA[100][100], int *n, int *check)
{

    int s = 0, i, j;
    fscanf(file, "%d", n);
    for (i = 0; i < *n; i++)
    {
        for (j = 0; j < *n; j++)
        {
            if (fscanf(file, "%f", &matrixA[i][j]) != 1)
            {
                fclose(file);
                return 0;
            }
        }
        char a = fgetc(file);
        if (a == ' ')
        {
            fclose(file);
            return 0;
        }
    }
    return 1;
    // rewind(file);
    // fclose(file);
    // if (s != (*n) * (*n))
    //     return 0;

    // return 1;
}

void readMatrixFromFile(FILE *file, float matrixA[100][100], int *n, int *check)
{

    if (file == NULL)
    {
        *check = 0;
        return;
    }
    else
    {
        *check = 1;
        fscanf(file, "%d", n);
        for (int i = 0; i < *n; i++)
        {
            for (int j = 0; j < *n; j++)
                fscanf(file, "%f", &matrixA[i][j]);
        }
    }
    fclose(file);
}
void printMatrixToFile(FILE *file, float matrix[100][100], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fprintf(file, "%6.2f ", matrix[i][j]);
        }
        fprintf(file, "\n");
    }
}

void readNameFile(char *fileName, int cnt)
{
    if (cnt < 3)
        printf("Nhap ten file chua ma tran %d:  ", cnt);
    else
    {
        printf("Nhap ten file ghi ket qua: ");
    }
    fgets(fileName, 100, stdin);
    // xu ly dau \n khi nhap.
    int length = strlen(fileName);
    if (length > 0 && fileName[length - 1] == '\n')
    {
        fileName[length - 1] = '\0';
    }
} // hello
void rewriteFileName(char *fileName, FILE *file, int cnt, float matrix[100][100], int *n, int check)
{
    do
    {
        do
        {
            readNameFile(fileName, cnt);
            file = fopen(fileName, "r");
            if (checkData(file, matrix, n, &check) == 0 || file == NULL)
            // if (file == NULL)
            {
                if (file == NULL)
                {
                    printf("File: %s khong ton tai, vui long nhap lai.\n\n", fileName);
                }
                else
                    printf("Loi du lieu trong file\n Moi ban nhap lai\n\n");
                // readNameFile(fileName, cnt);
            }
            else
                break;
        } while (1);
        readMatrixFromFile(file, matrix, n, &check);

        // if (check == 0)
        // {
        //     printf("File: %s khong ton tai, vui long nhap lai.\n", fileName);
        // }
        //     else
        //       {
        printf("Nhap file: %s thanh cong.\n\n", fileName);
        //        }
    } while (check == 0);
}
void printResultToFile(FILE *file, char *fileName, int n)
{

    file = fopen(fileName, "w");
    int p, q;
    // //
    fprintf(file, "Ma tran 1:\n");
    printMatrixToFile(file, matrixA, n);
    fprintf(file, "Ma tran 2:\n");
    printMatrixToFile(file, matrixB, n);
    fprintf(file, "Ma tran tong:\n");
    printMatrixToFile(file, matrixAns_sum, n);
    fprintf(file, "Ma tran tich:\n");
    printMatrixToFile(file, matrixAns_multi, n);
    replace_multi(matrixAns_multi, n, &p, &q);
    out(matrixAns_multi, n);
    printf("Ket qua da duoc luu o %s.", fileName);
    fprintf(file, "Ket qua sau khi hoan doi cot %d và %d la:\n ", p, q);
    printMatrixToFile(file, matrixAns_multi, n);
    fclose(file);
}
void printMatrixSumAndMulti(float matrixA[][100], float matrixB[][100], int n)
{
    printf("Ma tran tong:\n");
    out(matrixA, n);
    printf("Ma tran tich:\n");
    out(matrixB, n);
}
void gotoxy(int x, int y) // x,y là tọa điểm x,y trên màn hình
{

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD a = {x, y};
    SetConsoleCursorPosition(h, a);
}

void InputData_keyboard(float matrixA[][100], float matrixB[][100], int *n)
{
    printf("Input the level of the matrix: \n");
    scanf("%d", n);
    printf("Input the matrix A with level %d : ", *n);
    for (int i = 0; i < *n; i++)
    {
        for (int j = 0; j < *n; j++)
        {
            printf("matrixA[%d][%d]= \n", i + 1, j + 1);
            scanf("%f", matrixA[i][j]);
        }
    }
    printf("\n");
    printf("Input the matrix B with level %d : ", *n);
    for (int i = 0; i < *n; i++)
    {
        for (int j = 0; j < *n; j++)
        {
            printf("matrixB[%d][%d]= \n", i + 1, j + 1);
            scanf("%f", matrixB[i][j]);
        }
    }
    printf("\n");
}

void MENU_MAIN()
{
    printf(" -----------------------------------------------------\n");
    printf(" |             1. Input Data                         |\n");
    printf(" |             2. Sum of Two Matrices                |\n");
    printf(" |             3. Product of Two Matrices            |\n");
    printf(" |             4. Permutation matrix                 |\n");
    printf(" |             5. Swap the Two Columns of the Matrix |\n");
    printf(" |             6. Print Data to FILE                 |\n");
    printf(" -----------------------------------------------------\n");
}
void MENU_1()
{
    printf("   Please choose your data input method\n  ");
    printf(" ----------------------------------------\n");
    printf(" |    1. Input data from FILE           |\n");
    printf(" |    2. Input data from keyboard       |\n");
    printf(" |    Press \"r\" to return main menu   |\n");
    printf(" ----------------------------------------\n");
}
void MENU_2()
{
    printf("%s ---Message--- We have calculated the sum of your 2 matrices.\n", time_str);
    printf("\n");
    printf("Here are your results :");
}
void print_result_sum(int n)
{
    sumAndmulti(matrixA, matrixB, n);
    gotoxy(5, 20);
    printf("--Matrix A-- ");
    gotoxy(7, 22);
    out(matrixA, n);
    gotoxy(50, 20);
    printf("--Matrix B--");
    gotoxy(52, 22);
    out(matrixB, n);
    gotoxy(5, 22 + n + 4);
    printf("--Sum of two matrices--");
    gotoxy(24, 22 + n + 6);
    out(matrixAns_sum, n);
}
void MENU_3()
{
    printf(" We have calculated the sum of your 2 matrices.\n");
    printf("\n");
    printf("Here are your results :");
}
void print_result_multi(int n)
{
    sumAndmulti(matrixA, matrixB, n);
    gotoxy(5, 20);
    printf("--Matrix A-- ");
    gotoxy(7, 22);
    out(matrixA, n);
    gotoxy(50, 20);
    printf("--Matrix B--");
    gotoxy(52, 22);
    out(matrixB, n);
    gotoxy(5, 22 + n + 4);
    printf("--Product of two matrices--");
    gotoxy(24, 22 + n + 6);
    out(matrixAns_multi, n);
}
