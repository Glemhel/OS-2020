#include <stdio.h>

int main(){
    int toy1;
    float toy2;
    double toy3;
    toy1 = __INT_MAX__;
    toy2 = __FLT_MAX__;
    toy3 = __DBL_MAX__;
    printf("Integer: size is %lu, value is %d\n", sizeof(toy1), toy1);
    printf("Float: size is %lu, value is %f\n", sizeof(toy2), toy2);
    printf("Double: size is %lu, value is %f\n", sizeof(toy3), toy3);
    return 0;
}
