#include <stdio.h>
#include <linux/unistd.h>

int main(void)
{
    int mul_ret = 0;
    int x = 2, y = 5;
    int i;
    i = syscall(318, x,y,&mul_ret);
    printf("x is %d \n y is %d \n ret is %d\n",x,y,mul_ret);
    return 0;
}