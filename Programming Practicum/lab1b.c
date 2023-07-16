// Class 211 : Lab 1 part b
// Aqsa Arif
// 677417263
// Finding average, total, and count

#include <stdio.h>

int main (int argc, char** argv)
{
 
 int val = 0;
 int count = 0;
 int total = 0; 
 float average = 0.0;

 /* prompt the user for input */
 printf ("Enter in a list of numbers followed by the terminal value of -999\n");
 
 /* loop until the user enters -999 */
 scanf ("%d", &val);
 while (val != -999)
   {
    count = count + 1;
    total = total + val;
    scanf("%d", &val);
   }

 if( !(count == 0) && !(total == 0))
   {
    printf ("For the list of %d numbers with a total of %d\n", count, total);
    // Computing average here prevents floating point error of 0/0
    double tempTotal = (double)total;
    average = tempTotal / count; 
    printf ("   the average is: %15.5f\n", average);
   }
 else
   {
    printf("Error there is no valid input for computation\n");
   }
 return 0;
} 
