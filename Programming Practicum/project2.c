#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stack {
    char* array;
    int size;
    int inUse;
}stack;

stack initializeStack() {
    stack* copy = (stack*) malloc(sizeof(stack));
    copy->size = 4;
    copy->inUse = 1;
    copy->array = (char*) malloc(4 * sizeof(char));
    return *copy;
}

void push(stack* originalStack, char currLetter)
{
    if(originalStack->inUse != originalStack->size){
        originalStack->array[originalStack->inUse] = currLetter;
        originalStack->inUse++;
    }
    else {
        /* set tmp to refer to the location of old array*/
        char *tmp ;
        tmp = originalStack->array;
        /*allocate new space for the larger array*/
        originalStack->array = (char*)malloc(sizeof(char) * originalStack->size + 4);
        /*copy the existing values from the original array to the larger array*/
        for(int k = 0 ; k <originalStack->size ; k++){
            originalStack->array[k] = tmp[k];
        }
        free(tmp);
        originalStack->size = originalStack->size + 4;
        originalStack->array[originalStack->inUse] = currLetter;
        originalStack->inUse++;
    }
}

void pop(stack* originalStack) {
    originalStack->inUse = originalStack->inUse - 1;
}

int isEmpty(const stack* originalStack) {
    if(originalStack->inUse == 0){
        return 1;
    }
    return 0;
}

char top(const stack* originalStack){
    return originalStack->array[originalStack->inUse - 1];
    //printf("%c",originalStack->array[originalStack->inUse - 1]);
}

int validChar(char letter){
    if((letter == 'a') || (letter == 'b') || (letter == 'c') || (letter == 'd')){
        return 1;
    }
    if((letter == 'm') || (letter == 'n') || (letter == 'o') || (letter == 'p')){
        return 2;
    }
    return 0;
}

int checkMatching(const stack* mainChars, char curr){
    char topChar = mainChars->array[mainChars->inUse - 1];
    if((curr == 'm') && (topChar == 'a')){
        return 1;
    }
    if((curr == 'n') && (topChar == 'b')){
        return 1;
    }
    if((curr == 'o') && (topChar == 'c')){
        return 1;
    }
    if((curr == 'p') && (topChar == 'd')){
        return 1;
    }
    return 0;
}

void emptyArray(char* array) {
    for (int i = 0; i < 300; i++) {
        array[i] = '\0';
    }
}


int main(int argc, char const *argv[])
{

    char input[300];
    char decryptedMessage[300];
    emptyArray(decryptedMessage);
    int numWords;
    /* set up an infinite loop */
    while (1)
    {
        /* get line of input from standard input */
        printf ("\nEnter input to check or q to quit\n");
        fgets(input, 300, stdin);
        /* remove the newline character from the input */
        int i = 0;
        while (input[i] != '\n' && input[i] != '\0')
        {
            i++;
        }
        input[i] = '\0';
        /* check if user enter q or Q to quit program */
        if ( (strcmp (input, "q") == 0) || (strcmp (input, "Q") == 0) )
            break;

        printf ("%s\n", input);
        /*Start tokenizing the input into words separated by space
        We use strtok() function from string.h*/
        /*The tokenized words are added to an array of words*/

        char delim[] = " ";
        // returns first string word
        char *ptr = strtok(input, delim);
        int j = 0 ;
        // variable for length of word
        unsigned long long int* lenOfWord;
        lenOfWord = (unsigned long long int*)malloc(100 * sizeof(unsigned long long int));
        // temporary string array for individual words
        char* wordList;
        wordList = (char*)malloc(100 * sizeof(char));
        numWords = 0;
        while (ptr != NULL)
        {
            if(numWords == 0) {
                strcpy(&wordList[j], ptr);
            } else {
                // in order to properly store words
                strcpy(&wordList[j+strlen(&wordList[j])], ptr);
            }
            lenOfWord[numWords] = strlen(ptr);
            // returns null when no more space
            ptr = strtok(NULL, delim);
            j++;
            numWords++;
        }
        unsigned long long int sum = 0;
        int wordPrinted = 0;
        for(j = 0; j < numWords; j++){
            stack tempMainChars = initializeStack();
            stack tempDummyChars = initializeStack();
            for(i = sum; i < sum + lenOfWord[j]; i++) {
                char tempHolder = 'x';
                if ((validChar(wordList[i]) == 1) && (isEmpty(&tempDummyChars))) {
                    push(&tempMainChars, wordList[i]);
                }
                if (validChar(wordList[i]) == 2) {
                    if (checkMatching(&tempMainChars, wordList[i]) == 1) {
                        push(&tempDummyChars, wordList[i]);
                        tempHolder = top(&tempMainChars);
                        pop(&tempMainChars);
                    }
                }
                //printf("\n%c current letter\n", wordList[i]); // access to individual characters
                if (tempHolder != 'x') {
                    for (int x = 0; x < 300; x++) {
                        if (decryptedMessage[x] == '\0') {
                            //printf("\n This is current x value %d \n", x);
                            decryptedMessage[x] = tempHolder;
                            //printf("\n current fill %c \n", decryptedMessage[x]);
                            break;
                        }
                    }
                }
            }
            //printf(" 1");
            if(tempMainChars.inUse == 0){
                //printf(" 2");
                for(int x = 300 - 1; x != -1; x--){
                    //printf(" 3");
                    if(decryptedMessage[0] == '\0'){
                        //printf(" 4");
                        break;
                    }
                    if(decryptedMessage[x] != '\0'){
                        //printf(" 5");
                        wordPrinted = 1;
                        printf("%c", decryptedMessage[x]);
                    }
                }
            }
            emptyArray(decryptedMessage);
            free(tempDummyChars.array);
            free(tempMainChars.array);
            sum += lenOfWord[j];
            if((wordPrinted == 1) && (j != numWords - 1)){
                printf(" ");
            }
        }
        if(wordPrinted == 0){
            printf("No valid word decoded.\n");
        }
        //printf("\nTHIS IS IT\n");

/*
        while(isEmpty(&tempMainChars) == 0){
            top(&tempMainChars);
            printf(" one main char \n" );
            pop(&tempMainChars);
        }
        while(isEmpty(&tempDummyChars) == 0){
            top(&tempDummyChars);
            printf(" one Dummy char \n" );
            pop(&tempDummyChars);
        }*/
        //free(tempDummyChars.array);
        //free(tempMainChars.array);
        //free(&tempDummyChars);
        //free(&tempMainChars);

        free(wordList);
        free(lenOfWord);
    }
    printf ("\nGoodbye\n");
    return 0;
}
