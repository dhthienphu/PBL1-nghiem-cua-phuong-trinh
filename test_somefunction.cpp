#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <Windows.h>
char Input_Choice(int n, char *notice)
{
    int c, d, check = 0;
    do
    {
        printf("nhap su lua chon (yeu cau 1,2): ");
        c = getchar();
        if (c == '\n')
        {
            continue;
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
    return c;
}
BOOL WINAPI SetConsoleOutputCP(_In_ UINT wCodePageID);
int main()
{
    SetConsoleOutputCP(65001);
    char *notice_main = "Please input again, your input doesn't match the menu............";
    char s = Input_Choice(10, notice_main);
    for (int i = 0; i <= 100; i++)
    {

        printf("\rLoading %d %%...", i);

        usleep(15000);
    }
    printf("\n");
    printf("Loading complete\n");

    printf("Đoàn Hoàng Thiên Phú\n");
    printf("In được tiếng việt nè ae");

    // printf("%c", s);
}
