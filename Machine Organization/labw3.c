#include <stdio.h>
#include<time.h>

int main() 
{
float f;
double d;
d = time(NULL) / 32768.0;
f = d;
// add breakpoint here
printf("exiting program");
}
