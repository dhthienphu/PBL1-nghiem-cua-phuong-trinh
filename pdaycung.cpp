#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define e 0.001
double poly[100];
int n;
double findpolynominals(double *poly, int n, double c);
double f(double x);
int CheckMono(double *a, double *b);
void CheckInput(double *a, double *res, double *b);
void day_cung(double *a, double *b, double *res);
void Poly(double poly[]);

int main()
{
    Poly(poly);
    double a, res, b;
    CheckInput(&a, &res, &b);
    day_cung(&a, &b, &res);

    return 0;
}
void rootRange_suggest(double a[], int n)
{
    double firstRange[100];
    int cnt = 0;
    for (double i = -1000; i < 1000; i += 0.1)
    {
        if (f(a, n, i) * f(a, n, i + 0.1) < 0)
        {
            firstRange[cnt] = i;
            ++cnt;
        }
    }
    double rootRange[100];
    int cntRoot = 0;
    for (int i = 0; i < cnt; i++)
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
    printf("Phương trình f(x)=0 có %d nghiệm thực.", cnt);
    gotoXY(30, 7);
    printf("Đề xuất khoảng nghiệm là: ");
    for (int i = 0; i < cntRoot; i += 2)
    {
        printf("(%0.6g,%0.6g)  ", rootRange[i], rootRange[i + 1]);
    }
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

int CheckMono(double *a, double *b)
{
    double fa = f(*a);
    double fb = f(*b);

    // Kiểm tra hàm số đơn điệu tăng
    if (fa <= fb)
    {
        for (double x = *a; x < *b; x += 0.01)
        { // Duyệt qua các giá trị của x từ a đến b
            if (f(x) > f(x + 0.01))
            {
                return 0; // Hàm số không đơn điệu trên khoảng [a, b]
            }
        }
    }
    // Kiểm tra hàm số đơn điệu giảm
    else
    {
        for (double x = *a; x < *b; x += 0.01)
        { // Duyệt qua các giá trị của x từ a đến b
            if (f(x) < f(x + 0.01))
            {
                return 0; // Hàm số không đơn điệu trên khoảng [a, b]
            }
        }
    }

    return 1; // Hàm số đơn điệu trên khoảng [a, b]
}
void CheckInput(double *a, double *res, double *b)
{
    do
    {
        printf(".... Please enter the interval of solution.....\n  ");
        printf("   Enter a: ");
        scanf("%f", a);
        printf("    Enter b: ");
        scanf("%f", b);
        if ((CheckMono(a, b) == 0))
        {
            printf("The interval of solution is wrong\n Please enter again!\n");
            continue;
        }
        if (f(*a) * f(*b) > 0)
        {
            printf("The interval of solution is wrong\n Please enter again!\n");
            continue;
        }
    } while (((f(*a) * f(*b) > 0)) || CheckMono(a, b) == 0);
    if (f(*a) * f(*b) == 0)
        if (f(*a) == 0)
            *res = *a;
        else
            *res = *b;
}
void day_cung(double *a, double *b, double *res)
{
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
        *res = *a - (*b - *a) * f(poly, n, *a) / (f(poly, n, *b) - f(poly, n, *a));
        printf("    %0.6g    |      %0.6g     |      %0.6g      |      %0.6g     |\n", *a, *b, *res, f(poly, n, *res));
        if (f(poly, n, *res) < 0)
            *a = *res;
        else
            *b = *res;

    } while (fabs(*a - *b) > e);
    printf("Nghiệm của đa thức trong đoạn [%0.6g; %0.6g] là :  %0.6g\n", a_temp, b_temp, *res);
}
