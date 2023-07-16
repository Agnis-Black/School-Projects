
#include <stdio.h>
#include <stdlib.h>
/*CS 211 - Lab 3 
  Please Follow the instruction given in the pdf file */


#define SIZE 10


/* Task 1 -- add typedef and rename to Point3d */

typedef struct POINT_3D
{
  int x_cord;
  int y_cord; 
  int z_cord;
}Point3d;

/*Add function prototypes here*/


void init_Point1(Point3d* pt);

Point3d init_Point2(Point3d pt);

void PrintPoint1 (Point3d *pt);

void PrintPoint2(Point3d pt);


int main()
{
  int i;
  Point3d pt1;
  /* Task 2 -- using proper operator give values (5,4,2) to pt1
     and use the proper Print function to print it */
  pt1.x_cord = 5;
  pt1.y_cord = 4;
  pt1.z_cord = 2;
  printf("Printing Point3d:");
  PrintPoint2(pt1);
  /*Task 3 -- Declare a pointer of type Point3d named ptr1*/
  Point3d* ptr1;

  /*Task 4 -- Allocate memory for ptr1 and initialize it by 
  calling init_Point1() function and use the proper Print function to print it */
  ptr1 = (Point3d*) malloc(sizeof(Point3d));
  init_Point1(ptr1);

  printf("Printing Point3d:");
  PrintPoint1(ptr1);
  free(ptr1);
  //Declaring second variable pt2

  Point3d pt2; 

  /*Task 5 and 6 -- Compelete init_Point2 function and  
   call it with pt2 to create a point with random coordinates)
   , use the proper Print function to print it*/

  pt2 = init_Point2(pt2);

  printf("Printing Point3d:");
  PrintPoint2(pt2);

/************************************************/
/*************** Part 2 *************************/
/************************************************/
  /* All three variables p1, p2, and p3 are intended to be used as *
   * some form of array of the struct type declared above.         */
 
  Point3d p1[SIZE]; 
  Point3d* p2[SIZE];
  Point3d* p3;




  printf ("Calling init_Point1()\n");
  for (i = 0 ; i < SIZE; ++i)
    {
     printf ("For position %d\n", i);
     init_Point1 (&p1[i]);                     
     PrintPoint1(&p1[i]); 
     //PrintPoint2(p1[i])
    }

   
/*Task 7 -- Repeat the same steps for array p2, you must call a  
   proper init function and display the results by calling Print function */

/***********************************/
/* p2 : Declare, Initialize, Print */
    printf ("Calling init_Point1()\n");
    for (i = 0 ; i < SIZE; ++i)
    {
        printf ("For position %d\n", i);
        init_Point1 (*p2);
        PrintPoint1(*p2);
    }
/***********************************/
 





/* Task 8 -- p3 is a single pointer that must refer to an array of 10 instances
   allocated on the heap. Repeat the previous steps for p3 by initializing and 
  printing using proper functions*/

/***********************************/
/* p3 : Declare, Initialize, Print */
  p3 = (Point3d*) malloc(sizeof(Point3d)*10);
    printf ("Calling init_Point1()\n");
    for (i = 0 ; i < SIZE; ++i)
    {
        printf ("For position %d\n", i);
        init_Point1 (p3);
        PrintPoint1(p3);
    }
    free(p3);
/***********************************/






  return 0;
}


/************************/
/* function definitions */
/************************/


void init_Point1 (Point3d *pt)
{ 
  pt->x_cord = rand() % 100; 
  pt->y_cord = rand() % 1000;
  pt->z_cord = rand() % 100;  

}

/* Task 5 - write init_Point2() function definition */

Point3d init_Point2 (Point3d pt)
{
    Point3d temp;
    temp.x_cord = rand() % 100;
    temp.y_cord = rand() % 1000;
    temp.z_cord = rand() % 100;
    return temp;
}



void PrintPoint1 (Point3d *pt)
{
  printf("\t(x %d , y %d , z  %d ) \t", pt->x_cord, pt->y_cord, pt->z_cord);
  printf("\n");

}

void PrintPoint2 (Point3d pt)
{

  printf("\t(x %d , y %d , z  %d ) \t", pt.x_cord, pt.y_cord, pt.z_cord);
  printf("\n");

}