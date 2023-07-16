#include <stdio.h>
#include <stdlib.h>

#define TRUE   1
#define FALSE  0

#define COUNT 10

struct nodeStruct
{
 int elem;
 struct nodeStruct*  next;
};

typedef struct nodeStruct node;
typedef node* nodePtr;


/* prototypes of the functions used in this code  */
/*   also called "forward function declarations" */
int listLength    (node* hd);
int listLengthPBR (node** hd);


void printElement  (node* hd);


void  insertAtFront  (node** hd,  int val);
node* insertAtFront2 (node* hd,   int val);


void  removeFromFront  (node** hd);
node* removeFromFront2 (node* hd);


int getFirstValue (node* hd);
int isEmpty (node* hd);





/********************************************************
 * Function:       insertAtFront
 * Parrameters:    C-style pass-by-reference head pointer
 *                 an int value to add to the linked list
 * Return value:   none
 *******************************************************/

void insertAtFront (node** hd, int val)
{
 node* ptr = (node*) malloc (sizeof(node));
 ptr->elem = val;
 ptr->next = *hd;       /* note that hd must be "de-referenced" when used */
 *hd = ptr;             /*   the unary * operator is the "de-reference" operator */
}

/********************************************************
Task 1 - Complete insertAtFront2 function
/********************************************************
 * Function:       insertAtFront2
 * Parrameters:    C-style pass-by-value head pointer
 *                 an int value to add to the linked list
 * Return value:   node*
 *******************************************************/

//Task 1
node* insertAtFront2 (node* hd, int val)
{
    node* ptr = (node*) malloc (sizeof(node));
    ptr->elem = val;
    ptr->next = hd;       /* note that hd must be "de-referenced" when used */
    return ptr;

}

/********************************************************
 * Function:       printElement
 * Parrameters:    C-style pass-by-value head pointer
 * Return value:   none
 *
 * Display the items in a list
 *******************************************************/

void printElement (node* hd)
{
 /* loop until the PBV parameter is NULL */
 while (hd != NULL)
   {
    printf ("%d, ", hd->elem);   /* access the value at the node */
    hd = hd->next;               /* move to the next node */
   }
 printf ("\n");
}
/********************************************************
 * Function:       listLength
 * Parrameters:    C-style pass-by-value head pointer
 * Return value:   int value which is the length of a list
 *******************************************************/

/* calling code:                          */
/*     node* head = NULL;               */
/*      ...                               */
/*     listLength (head);                 */
int listLength (node* hd)
{
 int length = 0;
 while (hd != NULL)
   {
    length++;
    hd = hd->next;
   }
 return length;
}

/********************************************************
Task 3 - Complete listLengthPBR function
/********************************************************
 * Function:       listLengthPBR
 * Parrameters:    C-style pass-by-reference head pointer
 * Return value:   int value which is the length of a list
 *******************************************************/

//Task 3
int listLengthPBR (node** hd)
{
    int length = 0;
    node *ptr = (node*)malloc(sizeof(node));
    ptr = *hd;
    while (ptr != NULL)
    {
        length++;
        ptr = ptr->next;
    }
    return length;
}

/********************************************************
Task 4 - Complete find function
/********************************************************
 * Function:       find
 * Parrameters:    C-style pass-by-value head pointer
 *                  and an int value  "target"
 * Return value:   True if target is in the linked list
 *                 False otherwise
 *******************************************************/

// Task 4
int find (node* hd , int target){
    while (hd != NULL) {
        if(target == hd->elem){
            return TRUE;
        }
        hd = hd->next;
    }
    return FALSE;
}

/********************************************************
Task 5 - Complete modifyList function
/********************************************************
 * Function:       modifyList
 * Parrameters:    Decide the type of parameter passing
 * Return value:   None
 * The function will increment all of the values in
 *the linked list by 50
 *******************************************************/

// Task 5

void modifyList(node** hd){
    node *ptr = *hd;
    while (ptr != NULL) {
        ptr->elem = ptr->elem + 50;
        ptr = ptr->next;
    }
}


/********************************************************
Task 7 - Complete removeFromFront function
/********************************************************
 * Function:       removeFromFront
 * Parrameters:    C-style pass-by-reference head pointer
 * Return value:   None
 *******************************************************/

// Task 7
void removeFromFront (node** hd)
{
    node *temp = *hd ;
    //update the head
    *hd = (*hd)->next;
    free(temp);

}


/********************************************************
Task 8 - Complete removeFromFront2 function
/********************************************************
 * Function:       removeFromFront2
 * Parrameters:    C-style pass-by-reference head pointer
 * Return value:   node *
 *******************************************************/

// Task 8

node* removeFromFront2 (node* hd)
{
    return (hd)->next;

}

/********************************************************
 * Function:       getFirstValue
 * Parrameters:    C-style pass-by-value head pointer
 * Return value:   int value
 *******************************************************/

int getFirstValue (node* hd)
{
 if (hd != NULL)
   return hd->elem;
 else
   return -999;   /* returns -999 if list is empty */
}


/********************************************************
 * Function:       isEmpty
 * Parrameters:    C-style pass-by-value head pointer
 * Return value:   int value
 *******************************************************/

int isEmpty (node* hd)
{
 if (hd == NULL)
   return TRUE;
 else
   return FALSE;
}





int main (int argc, char**argv)
{
  /* two lists declared with just a pointer to a list head */
  /* initialize the head to null to indicate an empty list */
  node* head = NULL;
  node* head2 = NULL;



  int i;
  int temp;

  /* adding values to the front of the list */
  for (i = 0 ; i < COUNT; ++i)
    {
     temp = rand() % 100;
     printf ("In main(): temp: %6d\n", temp);

     /* head being sent as C-style pass-by-reference */
     insertAtFront (&head, temp + 100);		  /* must send the address of head here */

    /********************************************
     * Task 2: Using head2 and insertAtFront2
     * add value of "temp + 200" to the other
     * linked list
     * Send head2 as C pass-by-value
     ********************************************/
     /* Your code for Task 2 */
     head2 = insertAtFront2(head2, temp + 200);



     printf ("List 1 has %d nodes\n", listLength(head));
     printElement (head);
     printf ("List 2 has %d nodes\n", listLengthPBR(&head2));
     printElement (head2);
    }

    printf("here now\n");


    printf("Can we find the value?  %d\n", find(head, 130));

    /* Task 6 - Call modifyList function */
    modifyList ( &head );

    /* Print the elements after modification*/
    printElement(head);

   printf ("\n\nRemoving items from the list\n");
    for (i = 0 ; i < COUNT/2 ; i++)
      {
       int val = getFirstValue (head);
       printf ("The first item in the list is: %d\n", val);
       removeFromFront (&head);

     /* to help show what is going on */
    printf ("The list has %d nodes\n", listLength(head));
     printElement (head);
    }

  printf ("\n");

  printf ("\n\nRemoving items from the list2\n");
  for (i = 0 ; i < COUNT/2 ; i++)
    {
     int val = getFirstValue (head2);
     printf ("The first item in the list is: %d\n", val);
     head2 = removeFromFront2 (head2);

     /* to help show what is going on */
   printf ("List 2 has %d nodes\n", listLength(head2));
     printElement (head2);
    }

  printf ("\n");


}
