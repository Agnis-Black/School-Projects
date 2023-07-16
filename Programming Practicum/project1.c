#include <stdio.h>
#include <stdlib.h>

// This function makes the copy
void makeArrayCopy (int fromArray[], int toArray[], int size){
  for(int i = 0 ; i < size ; i++){
    toArray[i] = fromArray[i];
  }
}
// This function is to delete the empty spaces in the dynamic array
void deleteExtra(const int array[], int *size){
    for(int i = (*size) - 1; i != 0 ; i--){
        if(array[i] == 0){
            (*size)--;
        }
    }
}
// Insertion sort
void myFavoriteSort (int arr[], int size){
    for(int i = 1; i < size ; i++){
        int key = arr[i];
        int j = i - 1; // reverse count for comparison
        while(j != -1){
            if (key < arr[j]) {
                arr[j + 1] = arr[j];
                arr[j] = key;
            }
            j--;
        }
    }
}
// This is the function for first input
void indexComparison(const int unsortedArray[],const int sortedArray[],int size, int *counter){
    for(int i = 0; i < size; i ++){
        if(unsortedArray[i] == sortedArray[i]){
            (*counter) = (*counter) + 1;
        }
    }
}
// targetSum function
int targetSum(int arr[], int size, int target, int* high, int* low){
    for(int i = 0; i < size ; i++){
        int sum = arr[*low] + arr[*high];
        if(sum > target){
            (*high)--;
        }
        if ( sum < target) {
            (*low)++;
        }
        if ( (*low) == (*high)) {
            return -1;
        }
        if ( sum == target) {
            return 1;
        }
    }
    return 0;
}

int main (int argc, char** argv)
{
 int val;
 int userInput;
 int *arr;  // Declare the pointer
 int size = 4; // Declare a variable for size
 int i = 0;
 int k = 0;
 arr = (int*)malloc(sizeof(int)*size);  // allocating an array of 5 integers
 printf ("Enter in a list of numbers to be stored in a dynamic array.\n");
 printf ("End the list with the terminal value of -999\n");
 scanf ("%d", &val);
 while (val != -999) // loop until the user enters -999
 {
     if(i >= size){
         int *tmp ;  // set tmp to refer to the location of old array
         tmp = arr; // allocate new space for the larger array
         arr = (int*)malloc(sizeof(int)*size*2);
         for(k = 0 ; k <size ; k++) {
             arr[k] = tmp[k]; // copy the existing values from the original array to the larger array
         }
         free(tmp); // return the allocated memory from the original array back to the OS
         size = size *2; // update the size1 variable to properly reflect the current size of the array
    }
    arr[i] = val ;
    i++;
    scanf("%d", &val); // get next value
 }
 deleteExtra(arr,&size);
 int *copyArr; // temporary array for the copy
 copyArr = (int *) malloc(sizeof(int) * size);
 makeArrayCopy(arr, copyArr, size);
 myFavoriteSort(copyArr, size);
 deleteExtra(copyArr,&size);
 // Prompt user to enter a value to pick a task
 printf("Enter 1 to perform index comparison, enter 2 to perform target sum.\n");
 scanf ("%d", &userInput);
 while((userInput != 1) && (userInput != 2)) { // keep looping until input is 1 or 2
     printf("Invalid input. Enter 1 or 2.\n");
     scanf ("%d", &userInput);
 }
 // If user input is 1, perform index comparison
 if (userInput == 1) {
     int counter = 0;
     indexComparison(arr, copyArr, size, &counter);
     if(counter != 0) {
         printf("%d values are in the same location in both arrays.\n", counter);
     } else {
         printf ("All elements change location in the sorted array.\n");
     }
 }
 // If user input is 2, perform targetSum
 if(userInput == 2) {
     printf("Enter in a list of numbers to use for searching.  \n");
     printf("End the list with a terminal value of -999\n");
     int size1 = 5;
     i = 0;
     int *array2;
     array2 = (int *) malloc(sizeof(int) * size1);
     scanf("%d", &val);
     while (val != -999) {
         if (i >= size1) {
             int *tmp1;
             tmp1 = array2;
             array2 = (int *) malloc(sizeof(int) * size1 * 2);
             for (k = 0; k < size1; k++) {
                 array2[k] = tmp1[k];
             }
             free(tmp1);
             size1 = size1 * 2;
         }
         array2[i] = val;
         i++;
         scanf("%d", &val);
     }
     deleteExtra(array2, &size1);
     for(int x = 0; x < size1; x++) {  // iterate through target values
         int high = size - 1;
         int low = 0;
         int output = targetSum(copyArr, size, array2[x], &high, &low);
         if( output == -1) {
             printf("Target sum failed!\n");
         }
         if ( output == 0 ) { // default case
             printf("Error in targetsum logic\n");
         }
         if ( output == 1) {
             printf("Success! Elements at indices %d and %d add up to %d\n", low, high, array2[x]);
         }
     }
     free(copyArr);
     free(array2);
     free(arr);
 }
 printf ("Good bye");
 return 0;
}
