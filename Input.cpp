// scan tung thanh phan charname cua cau truc roi tu do trich tung thang cau truc ra.
#include <stdio.h>
#include <string.h>

double stringToDouble(const char *str);
int Find(char *temp, char x)
{
    return strchr(temp, x) != NULL;
}
struct element
{
    char string_num[100];
    char string_bac[100];
    int sign; // =0 la + , =1 la -
    int id_var;
    int id_sign;
    int bac_0;
};
int Find_id(char *temp, char x)
{
    int n = strlen(temp);
    for (int i = 0; i < n; i++)
    {
        if (temp[i] == x)
        {
            return i;
        }
    }
    return -1;
}
int main()
{
    char expression[1000];
    fgets(expression, sizeof(expression), stdin);
    for (int i = 0; i <= strlen(expression); i++)
    {
        printf("%c", expression[i]);
    }
    int length = strlen(expression);
    struct element ele[100];

    char *temp = strtok(expression, " ");
    int j = 0;
    while (temp != NULL)
    {

        if (Find(temp, '-'))
        {
            ele[j].sign = -1;
        }
        else
            ele[j].sign = 1;
        // xu ly dau cua phan tu dau.

        if (j == 0)
        {
            if (Find(temp, 'x'))
            {
                for (int i = 0; i < Find_id(temp, 'x'); i++)
                {
                    // if (ele[j].sign == -1)
                    // {
                    //     if (i == 0)
                    //         continue;
                    // }
                    ele[j].string_num[i] = expression[i];
                }
            }
            else
            {
                for (int i = 0; i < strlen(temp); i++)
                {
                    // if (ele[j].sign == -1)
                    // {
                    //     if (i == 0)
                    //         continue;
                    // }
                    ele[j].string_num[i] = expression[i];
                }
            }
        }
        printf("%s ", ele[0].string_num);
        temp = strtok(NULL, " "); // Lấy phần tử tiếp theo
    }
    // Dem so luong element nhap vao.
    // vector<int> id_ele;
    // for (int i = 0; i < length; i++)
    // {
    //     if (name[i] == '+' || name[i] == '-')
    //     {
    //         id_ele.push_back(i);
    //     }
    // }
    // int element_count;
    // if (name[0] == '+')
    // {
    //     element_count = id_ele.size() + 1;
    // }
    // else
    //     element_count = id_ele.size();
    // //
    // struct element ele[element_count];
    // // lay dau + or - va index
    // int j = 0;
    // for (int i = 0; i < length; i++)
    // {

    //     // xu ly xong phan dau
    //     if (name[0] != '-')
    //     {
    //         ele[0].dau = 0;
    //         ele[0].id_dau = -1;
    //     }
    //     else
    //     {
    //         ele[0].dau = 1;
    //         ele[0].id_dau = -1;
    //     }
    //     if (name[i] == 'x')
    //     {
    //         ele[j].x = i;
    //     }
    //     if (ele[j].x == 0)
    //     {
    //         ele[j].bac_0 = 1;
    //     }
    //     if (j == 0)
    //         ++j;
    //     // xu ly phan sau
    //     if (name[i] == '+' || name[i] == '-')
    //     {

    //             if (name[i] == '+')
    //             {
    //                 ele[j].dau = 0;
    //                 ele[j++].id_dau = i;
    //             }
    //             else
    //             {
    //                 ele[j].dau = 1;
    //                 ele[j++].id_dau = i;
    //             }
    //     }
    // }

    // // tao mang luu chi so ki tu + decode 0 and 1 then *decimalnumber gan lai cho bien
    // int id_dau[100];
    // int j = 0;
    // for (int i = 0; i < length; i++)
    // {
    //     if (name[i] == '+' || name[i] == '-')
    //     {
    //         if (name[i] == '+')
    //             id_dau[j++] = i;
    //     }
    // }
}

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
