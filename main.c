#include <stdio.h>
#include "rtklib.h"

/**
 * 特别注意,在二次开发环境下,头文件中的被标记为application defined functions的函数中的showmsg不可调用,因为需要窗口支持.
 *
 */

int main() {
    printf("Welcome to use rtklib with your APs!\n");
    return 0;
}
