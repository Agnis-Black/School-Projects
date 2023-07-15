#include <stdio.h>

int main(){
	short numArray[9];
	int i;
	char c;

	printf("Please enter 9 numbers:");

	for(i=0;i<9;i++){
		scanf("%hd",&(numArray[i]));
	}

	scanf("%c",&c);
	printf("Press any key to continue:");
	scanf("%c",&c);

	long cube[2][3][2];
	printf("Please enter 12 numbers:");
	long *ptr;
	ptr = &(cube[0][0][0]);

	for(i=0;i<12;i++){
		scanf("%ld",ptr);
		ptr++;
	}

	scanf("%c",&c);
	printf("Press any key to continue:");
	scanf("%c",&c);
	return 0;
}