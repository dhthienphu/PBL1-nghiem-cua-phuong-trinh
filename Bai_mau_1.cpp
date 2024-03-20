#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float matrixAns_sum[1000][1000];
float matrixAns_multi[1000][1000];
float matrixA[1000][1000];
float matrixB[1000][1000];

int checkData(FILE *file, float matrixA[1000][1000], int *n, int *check);
void out(float matrix[1000][1000], int n);
void sumAndmulti(float matrixA[1000][1000], float matrixB[1000][1000], int n);
void Replace(float *a, float *b);
void replace_multi(float matrix[1000][1000], int n, int *p, int *q);
void readMatrixFromFile(FILE *file, float matrixA[1000][1000], int *n, int *check);
void printMatrixToFile(FILE *file, float matrix[1000][1000], int n);
void readNameFile(char *fileName, int cnt);
void rewriteFileName(char *fileName, FILE *file, int cnt, float matrix[1000][1000], int *n, int check);
void printResultToFile(FILE *file, char *fileName, int n);
void printMatrixSumAndMulti(float matrixA[][1000], float matrixB[][1000], int n);

int main()
{
    char fileName1[1000], fileName2[1000], fileName3[1000];
    int n, p, q, num_1, num_2, check1 = 1, check2 = 1;
    FILE *file1, *file2, *file3;
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
    sumAndmulti(matrixA, matrixB, n);
    printMatrixSumAndMulti(matrixAns_sum, matrixAns_multi, n);
    printResultToFile(file3, fileName3, n);
}
void out(float matrix[1000][1000], int n)
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
void sumAndmulti(float matrixA[1000][1000], float matrixB[1000][1000], int n)
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
void Replace(float *a, float *b)
{
    float tmp = *b;
    *b = *a;
    *a = tmp;
}
void replace_multi(float matrix[1000][1000], int n, int *p, int *q)
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
        Replace(&matrix[i][a], &matrix[i][b]);
    }
}
int checkData(FILE *file, float matrixA[1000][1000], int *n, int *check)
{

    int s = 0, i, j;
    fscanf(file, "%d", n);
    for (i = 0; i <= *n; i++)
    {
        for (j = 0; j <= *n; j++)
            if (fscanf(file, "%f", &matrixA[i][j]) == 1)
                s++;
    }
    if (s != (*n) * (*n))
        return 0;

    fclose(file);
    return 1;
}

void readMatrixFromFile(FILE *file, float matrixA[1000][1000], int *n, int *check)
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
void printMatrixToFile(FILE *file, float matrix[1000][1000], int n)
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
    fgets(fileName, 1000, stdin);
    // xu ly dau \n khi nhap.
    int length = strlen(fileName);
    if (length > 0 && fileName[length - 1] == '\n')
    {
        fileName[length - 1] = '\0';
    }
}//hello
void rewriteFileName(char *fileName, FILE *file, int cnt, float matrix[1000][1000], int *n, int check)
{
    do
    {
        do
        {
            readNameFile(fileName, cnt);
            file = fopen(fileName, "r");
            if (checkData(file, matrix, n, &check) == 0 || file == NULL)
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

    readNameFile(fileName, 3);
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
void printMatrixSumAndMulti(float matrixA[][1000], float matrixB[][1000], int n)
{
    printf("Ma tran tong:\n");
    out(matrixA, n);
    printf("Ma tran tich:\n");
    out(matrixB, n);
}
