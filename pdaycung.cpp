#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define e 0.001
float f(float x)
{
    // Ví dụ: Hàm số x^2
    return (2 * x * x - 3 * x + 1);
}
int CheckMono(float *a, float *b)
{
    float fa = f(*a);
    float fb = f(*b);

    // Kiểm tra hàm số đơn điệu tăng
    if (fa <= fb)
    {
        for (float x = *a; x < *b; x += 0.01)
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
        for (float x = *a; x < *b; x += 0.01)
        { // Duyệt qua các giá trị của x từ a đến b
            if (f(x) < f(x + 0.01))
            {
                return 0; // Hàm số không đơn điệu trên khoảng [a, b]
            }
        }
    }

    return 1; // Hàm số đơn điệu trên khoảng [a, b]
}
void CheckInput(float *a, float *res, float *b)
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
    } while ((f(*a) * f(*b) > 0));
    if (f(*a) * f(*b) == 0)
        if (f(*a) == 0)
            *res = *a;
        else
            *res = *b;
}
void day_cung(float *a, float *b, float *res)
{
    printf("........Table of solution......\n");
    printf("    a         |      b          |      x          |      f(x)      |\n");
    do
    {

        if (f(*a) > 0 && f(*b) < 0)

        {

            int tam = *a;
            *a = *b;
            *b = tam;
        }
        *res = *a - (*b - *a) * f(*a) / (f(*b) - f(*a));
        printf("    %0.4f     |      %0.4f      |      %0.4f      |      %0.4f      |\n", *a, *b, *res, f(*res));
        if (f(*res) < 0)
            *a = *res;
        else
            *b = *res;

    } while (fabs(*a - *b) > e);
    printf("-----The solution of the equation is %0.6f\n", *res);
}
int main()
{
    float a, res, b;
    CheckInput(&a, &res, &b);
    day_cung(&a, &b, &res);

    return 0;
}
