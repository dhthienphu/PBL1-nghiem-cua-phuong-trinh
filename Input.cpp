// scan tung thanh phan charname cua cau truc roi tu do trich tung thang cau truc ra.
#include <stdio.h>
#include <string.h>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
// struct element{
//     double he_so;
//     int bac;
// };
struct element
{
    int dau; // =0 la + , =1 la -
    int x;
    int id_dau;
};
double stringToDouble(const char *str)
{
    double result = 0.0;
    int i = 0;
    double sign = 1.0;
    double decimalPlace = 0.1; // Used for decimal portion

    // Handle leading whitespace
    while (str[i] == ' ')
    {
        i++;
    }

    // Handle sign
    if (str[i] == '-')
    {
        sign = -1.0;
        i++;
    }
    else if (str[i] == '+')
    {
        i++;
    }

    // Convert digits before decimal point
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = result * 10.0 + (str[i] - '0');
        i++;
    }

    // Convert digits after decimal point
    if (str[i] == '.')
    {
        i++;
        while (str[i] >= '0' && str[i] <= '9')
        {
            result = result + (str[i] - '0') * decimalPlace;
            decimalPlace *= 0.1;
            i++;
        }
    }

    // Apply sign
    result *= sign;

    return result;
}

int main()
{
    char name[1000];
    fgets(name, sizeof(name), stdin);
    for (int i = 0; i <= strlen(name); i++)
    {
        printf("%c", name[i]);
    }
    int length = strlen(name);
    // Dem so luong element nhap vao.
    vector<int> id_ele;
    for (int i = 0; i < length; i++)
    {
        if (name[i] == '+' || name[i] == '-')
        {
            id_ele.push_back(i);
        }
    }
    int element_count = id_ele.size() + 1;
    //
    struct element ele[element_count];
    // lay dau + or - va index
    int j = 1;
    for (int i = 0; i < length; i++)
    {
        // xu ly xong phan dau
        if (name[0] != '-')
        {
            ele[0].dau = 0;
            ele[0].id_dau = -1;
        }
        else
        {
            ele[0].dau = 1;
            ele[0].id_dau = -1;
        }
        // xu ly phan sau
        if (name[i] == '+' || name[i] == '-')
        {
            if (name[i] == '+')
            {
                ele[j].dau = 0;
                ele[j++].id_dau = i;
            }
        }
    }

    // tao mang luu chi so ki tu + decode 0 and 1 then *decimalnumber gan lai cho bien
    int id_dau[100];
    int j = 0;
    for (int i = 0; i < length; i++)
    {
        if (name[i] == '+' || name[i] == '-')
        {
            if (name[i] == '+')
                id_dau[j++] = i;
        }
    }
}