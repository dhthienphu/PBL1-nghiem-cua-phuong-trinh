#include <stdio.h>
#include <math.h>
#define e 0.001

// Định nghĩa hàm f(x) (ví dụ)
float f(float x)
{
    // Ví dụ: Hàm số x^2
    return (2 * x * x - 3 * x + 1);
}

// Hàm kiểm tra tính đơn điệu của hàm số trên một khoảng [a, b]
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
        printf("   Enter b: ");
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

float bisectionMethod(float *a, float *res, float *b)
{
    float tmp;
    float c;
    while (f(*a) * f(*b) == 0)
    {
        if (*res == *a)
        {
            printf("%f is solution of equation\n", *a);
            return 0;
        }
        if (*res == *b)
        {
            printf("%f is solution of equation\n", *b);
            return 0;
        }
    }
    if (*a > *b)
    {
        tmp = *a;
        *a = *b;
        *b = tmp;
    }
    printf("----------Table of solution by bisection method----------\n");
    printf(" a              |        b           |       c           |  f(c)          \n");

    while (f(*a) < 0 && f(*b) > 0)
    {
        c = (*a + *b) / 2;
        printf(" %0.6f   |     %0.6f       |    %0.6f       |   %0.6f    \n ", *a, *b, c, f(c));
        if (f(c) > 0)
        {
            *b = c;
        }
        else
            *a = c;
        if (fabs(*a - *b) <= e)
        {
            printf("-----The solution of the equation is %0.6f\n", *a);
            return 0;
        }
    }
    while (f(*a) > 0 && f(*b) < 0)
    {
        c = (*a + *b) / 2;
        printf(" %0.6f     |     %0.6f       |    %0.6f       |   %0.6f    \n ", *a, *b, c, f(c));
        if (f(c) < 0)
        {
            *b = c;
        }
        else
            *a = c;
        if (f(c) == 0)
        {
            printf("-----The solution of the equation is %0.6f\n", c);
            return 0;
        }
        if ((fabs(*a - *b) <= e) && f(c) != 0)
        {
            printf("-----The solution of the equation is %0.6f\n", *a);
            return 0;
        }
    }
}
int main()
{
    float a, res, b;
    CheckInput(&a, &res, &b);
    bisectionMethod(&a, &res, &b);

    return 0;
}
