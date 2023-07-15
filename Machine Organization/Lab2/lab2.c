#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{

unsigned int second;
int first;
char *anArray;
srand(time(0));
time_t mytime;
time(&mytime);
anArray = ctime(&mytime);
first = rand()%100000;
second = rand() % 100000;

//set breakpoint here
printf("Values under consideration\n");
printf("%s\n",anArray);
printf("int %d\n",first);
printf("unsigned int %u\n",second);


return 0;
}
