#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

int dummy_function(int i, int j){
    return i&(~j);
}

int main(){
    char* str = "The finest Arabica in Vietnam thrives in the cool mountains above Dalat.\0";
    // char* str = 0x5468652066696e657374204172616269636120696e20566965746e616d207468726976657320696e2074686520636f6f6c206d6f756e7461696e732061626f76652044616c61742e00;
    int i = INT_MAX - 7;
    long l = LONG_MIN + 7;
    struct S7 {
        int i; int j; char c;
    };
    struct S7 s;
    struct S7 r[2];
    printf("%d", dummy_function(7,77));
    return 0;
}