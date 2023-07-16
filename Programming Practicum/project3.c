// Name: Aqsa Arif
// UIN: 677417263
// Class: CS 211
// Project 3: Maze Solving

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// declare maze struct
typedef struct mazeStruct {
    char **arr;  // simply declare so that size can be initialized on heap with exact values
    int xsize, ysize;
    int xstart, ystart;
    int xend, yend;
} maze;
// This function dynamically allocates size on heap
maze initializeSize(maze temp) {
    char **arr2;
    int i;
    arr2 = (char**) malloc(sizeof(char*) * (temp.xsize + 2));
    for(i = 0 ; i < (temp.xsize + 2) ; i++) {
        arr2[i] = (char*)malloc(sizeof(char) * (temp.ysize + 2));
    }
    temp.arr = arr2;
    return temp;
}
// This linked list struct will manage printing and coin-block locations
typedef struct nodeStruct {
    int row;
    int col;
    char carr;
    struct nodeStruct* next;
}node;
// This struct will serve as the stack linked list
typedef struct stackStruct {
    int row;
    int col;
    int count;
    struct stackStruct* next;
}stack;
// This function will push values onto node
node* pushNode (node* hd, int valOne, int valTwo, char letter) {
    node* ptr = (node*) malloc (sizeof(node));
    ptr->row = valOne;
    ptr->col = valTwo;
    ptr->carr = letter;
    ptr->next = hd;
    return ptr;
}
// This function initializes top values to start position
stack* startPosition(maze temp, stack* curr){
    stack* ptr = (stack*) malloc (sizeof(stack));
    ptr->row = temp.xstart;
    ptr->col = temp.ystart;
    ptr->count = 0;
    ptr->next = curr;
    return ptr;
}
// This function serves as the push function for the stack
stack* push(stack* curr, int row, int col, char coinVar) {
    stack* ptr = (stack*) malloc (sizeof(stack));
    ptr->row = row;
    ptr->col = col;
    ptr->count = curr->count;
    if( coinVar == 'C') {
        ptr->count = 1 + curr->count;
    }
    ptr->next = curr;
    return ptr;
}
// This function will change index on maze to coin or a block
maze markCoinBlock(maze temp, node* hd){
    while(hd != NULL) {
        if(temp.arr[hd->row][hd->col] == '.'){
            temp.arr[hd->row][hd->col] = hd->carr;
        }
        hd = hd->next;
    }
    return temp;
}
// This function prints out node elements
void printElement (node* hd) {
    while (hd != NULL) {
        printf("(%d,%d) ", hd->row, hd->col);
        hd = hd->next;
    }
    printf ("\n");
}
// This function prints stack in order
void printStack(stack* hd, node* temp) {

    while (hd != NULL) {
        temp = pushNode(temp, hd->row, hd->col,'.');
        hd = hd->next;
    }
    printElement(temp);
    while(temp != NULL) {
        node* tmp = temp;
        temp = temp->next;
        free(tmp);
    }
}
// Initialize maze values for initial check
maze initializeValue(maze *temp) {
    temp->xsize = -1;
    temp->ysize = -1;
    temp->xstart = -1;
    temp->ystart = -1;
    temp->xend = -1;
    temp->yend = -1;
    return *temp;
}
// This function serves as a boolean for initial file values
int validInputCheck(maze temp){
    if(temp.xsize == -1){
        return 0;
    }
    if(temp.ysize == -1){
        return 0;
    }
    if(temp.xstart == -1){
        return 0;
    }
    if(temp.ystart == -1){
        return 0;
    }
    if(temp.xend == -1){
        return 0;
    }
    if(temp.yend == -1){
        return 0;
    }
    return 1;
}
// This function is a boolean for start values
int checkStart(maze temp){
    if((temp.xsize < temp.xstart) || (temp.xstart <= 0)) {
        return 0;
    }
    if((temp.ysize < temp.ystart) || (temp.ystart <= 0)) {
        return 0;
    }
    return 1;
}
// This function is a boolean for end values
int checkEnd(maze temp){
    if((temp.xsize < temp.xend) || (temp.xend <= 0)) {
        return 0;
    }

    if((temp.ysize < temp.yend) || (temp.yend <= 0)) {
        return 0;
    }
    return 1;
}
// Checks if size is valid
int sizeCheck(maze temp) {
    if((temp.xsize <= 0) || (temp.ysize <= 0)) {
        return 0;
    }
    return 1;
}
// Valid character check
char checkCharacter(char letter) {
    if(letter == 'c') {
        return 'C';
    }
    if(letter == 'b') {
        return '*';
    }
    fprintf(stderr, "Invalid type: type is not recognized.\n");
    return 'X';
}
// This function checks if location of a block or coin is valid within size or isn't
// in the start or end position
int checkRange(maze temp, int row, int col) {
    if((temp.xstart == row) && (temp.ystart == col)){
        fprintf(stderr, "Invalid coordinates: attempting to block start/end position.\n");
        return 0;
    }
    if((temp.xend == row) && (temp.yend == col)){
        fprintf(stderr, "Invalid coordinates: attempting to block start/end position.\n");
        return 0;
    }
    if((temp.xsize < row) || (temp.ysize < col)) {
        fprintf(stderr, "Invalid coordinates: outside of maze range.\n");
        return 0;
    }
    if((row <= 0) || (col <= 0)) {
        fprintf(stderr, "Invalid coordinates: outside of maze range.\n");
        return 0;
    }
    return 1;
}
// Pop function for stack, return by reference
void pop (stack** hd) {
    stack* temp = *hd;
    *hd = (*hd)->next;
    free(temp);
}
// top function in stack, returns row and column value by reference to use for navigation
void top (stack* hd, int *row, int *col) {
    *row = hd->row;
    *col = hd->col;
}
// Checks if stack is empty
int isEmpty (stack* hd) {
    if (hd == NULL){
        return 1;
    }
    return 0;
}
// This function checks if a solution was found
int checkEndFound(maze temp, stack* path) {
    if((temp.xend == path->row) && (temp.yend == path->col)) {
        return 1;
    }
    return 0;
}
int main (int argc, char **argv) {
    setbuf(stdout, NULL);
    maze m1;
    node* head = NULL;
    stack* path = NULL;
    char c;
    int i,j;
    int validNums;
    int debug = 0;
    FILE *src;

    /* verify the proper number of command line arguments were given */

    if(argc > 3) {
        printf("Usage: %s <input file name> or %s -d <input file name>\n", argv[0], argv[0]);
        exit(-1);
    } else if(argc == 1) {
        printf("Usage: %s <input file name>\n", argv[0]);
        exit(-1);
    }
    // Checks if -d flag present and assigns boolean debug as true
    if(argc == 3) {
        if(strncmp(argv[1], "-d",2) == 0){
            debug = 1;
        }
        if(strncmp(argv[2], "-d",2) == 0){
            debug = 1;
        }
    }

    /* Try to open the input file. */
    if ( ( src = fopen( argv[1], "r" )) == NULL ) {
        printf ( "Can't open input file: %s\n", argv[1] );
        exit(-1);
    }

    initializeValue(&m1);
    fscanf (src, "%d %d", &m1.xsize, &m1.ysize);
    fscanf (src, "%d %d", &m1.xstart, &m1.ystart);
    fscanf (src, "%d %d", &m1.xend, &m1.yend);
    if(validInputCheck(m1) == 0){
        fprintf (stderr,"Invalid data file.\n");
        exit(-1);
    }
    if(sizeCheck(m1) == 0) {
        fprintf(stderr,"Maze sizes must be greater than 0.\n");
        exit(-1);
    }
    printf ("size: %d, %d\n", m1.xsize, m1.ysize);

    if(checkStart(m1) == 0) {
        fprintf(stderr,"Start/End position outside of maze range.");
        exit(-1);
    }
    printf ("start: %d, %d\n", m1.xstart, m1.ystart);
    if(checkEnd(m1) == 0) {
        fprintf(stderr,"Start/End position outside of maze range.");
        exit(-1);
    }
    printf ("end: %d, %d\n", m1.xend, m1.yend);
    m1 = initializeSize(m1);

    while(fscanf(src, "%d %d %c" ,&i, &j, &c ) != EOF){
        c = checkCharacter(c);
        validNums = checkRange(m1, i, j);
        if( (c != 'X') && (validNums != 0)) {
            head = pushNode(head, i, j, c);
        }
    }
    // initialize the maze to empty
    for (i = 0; i < m1.xsize+2; i++){
        for (j = 0; j < m1.ysize+2; j++) {
            m1.arr[i][j] = '.';
        }
    }
    m1 = markCoinBlock(m1, head);
    while(head != NULL) { // By freeing here can use again for printing
        node* tmp = head;
        head = head->next;
        free(tmp);
    }

    // mark the borders of the maze with *'s
    for (i=0; i < m1.xsize+2; i++) {
        m1.arr[i][0] = '*';
        m1.arr[i][m1.ysize+1] = '*';
    }
    for (i=0; i < m1.ysize+2; i++) {
        m1.arr[0][i] = '*';
        m1.arr[m1.xsize+1][i] = '*';
    }

    // mark the starting and ending positions in the maze
    m1.arr[m1.xstart][m1.ystart] = 's';
    m1.arr[m1.xend][m1.yend] = 'e';

    //print out the initial maze
    for (i = 0; i < m1.xsize+2; i++) {
        for (j = 0; j < m1.ysize+2; j++) {
            printf ("%c", m1.arr[i][j]);
        }
        printf("\n");
    }

    path = startPosition(m1,path);
    if(debug == 1){
        printf("(%d,%d) pushed into the stack.\n", m1.xstart, m1.ystart);
    }
    // The giant while loop that manages the navigation
    while((isEmpty(path) == 0) && (checkEndFound(m1, path) == 0)) {
        top(path, &i, &j);
        if((m1.arr[i+1][j] == '.') || (m1.arr[i+1][j] == 'C') || (m1.arr[i+1][j] == 'e')) { // go right
            c = m1.arr[i+1][j];
            path = push(path, i+1, j, c);
            m1.arr[i+1][j] = 'V';
            if(debug == 1){
                printf("(%d,%d) pushed into the stack.\n", i+1, j);
            }
        } else if((m1.arr[i][j+1] == '.') || (m1.arr[i][j+1] == 'C') || (m1.arr[i][j+1] == 'e')) { // go down
            c = m1.arr[i][j+1];
            path = push(path, i, j+1, c);
            m1.arr[i][j+1] = 'V';
            if(debug == 1){
                printf("(%d,%d) pushed into the stack.\n", i, j+1);
            }
        } else if((m1.arr[i-1][j] == '.') || (m1.arr[i-1][j] == 'C') || (m1.arr[i-1][j] == 'e')) { // go left
            c = m1.arr[i-1][j];
            path = push(path, i-1, j, c);
            m1.arr[i-1][j] = 'V';
            if(debug == 1){
                printf("(%d,%d) pushed into the stack.\n", i-1, j);
            }
        } else if ((m1.arr[i][j-1] == '.') || (m1.arr[i][j-1] == 'C') || (m1.arr[i][j-1] == 'e')) { // go up
            c = m1.arr[i][j-1];
            path = push(path, i, j-1, c);
            m1.arr[i][j-1] = 'V';
            if(debug == 1){
                printf("(%d,%d) pushed into the stack.\n", i, j-1);
            }
        } else {
            pop(&path);
            if(debug == 1){
                printf("(%d,%d) popped off the stack.\n", i, j);
            }
        }
    }
    if(isEmpty(path) == 1) {
        printf("This maze has no solution.\n");
    } else if(checkEndFound(m1,path) == 1) {
        printf("The maze has a solution.\n");
        printf("The amount of coins collected: %d\n", path->count);
        printf("The path from start to end: \n");
        printStack(path,head);
    }
    while(path != NULL) {
        if(debug == 1){
            printf("(%d,%d) popped off the stack.\n", path->row, path->col);
        }
        stack* tmp = path;
        path = path->next;
        free(tmp);
    }
    //Close the file
    fclose(src);

    // deallocate 2D array
    for(i = 0 ; i < (m1.xsize + 2) ; i++){
        free(m1.arr[i]);
    }
    free(m1.arr);
}