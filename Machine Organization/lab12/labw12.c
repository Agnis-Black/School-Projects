#include<stdio.h>

/**
 *Function get_dim  : to get dimension of array 
 * 
 * returns: dimension of array
 */
int get_dim() {
    int dimension = 500;
    return dimension;
}


/**
 *Function get_val  : to get value in particular cell of a 2D-array 
 * 
 * @param myMat 2D-array from which to retrieve value
 * @param i first index of cell to retrieve
 * @param j second index of cell to retrieve
 * 
 * returns: dimension of array
 */
long get_val(long myMat[][get_dim()], int i, int j){
    return myMat[i][j];
}


/**
 * Function labw12  : performs matrix multiplication of two 2D matrices
 * 
 * @param myMat1 first operand (2D array)
 * @param myMat2 second operand (2D array)
 * @param result 2D array to store result of matrix multiplication
 */
void labw12(long myMat1[][get_dim()], long myMat2[][get_dim()], long result[][get_dim()])
{
    int i;
    int j;
    int k;

    for ( i = 0 ; i < get_dim() ; i++ ){
        for ( j = 0 ; j < get_dim() ; j++ ){
            result[i][j] = 0;
            for ( k = 0 ; k < get_dim() ; k++ ){
                result[i][j] += get_val(myMat1, i, k) * get_val(myMat2, k, j);
            }
        }
    }
}


/**
 * Function printMatrix  : prints 2D matrix
 * 
 * @param printMat 2D array to print
 */
void printMatrix(long printMat[][get_dim()]){
    printf("\n[");
    for (int i=0;i<get_dim();i++){ 
        printf("\n[ ");
        for (int j=0;j<get_dim();j++){
            printf("%ld  ",printMat[i][j]);
        }   
        printf(" ]\n");
    }   
    printf("]\n");    
}

int main() {
    int DIM = get_dim();    
    long mat1[DIM][DIM];
    long mat2[DIM][DIM];
    long result[DIM][DIM];
    int i=0;
    int j=0;	
    for (i=0;i<DIM;i++){ 
        for (j=0;j<DIM;j++){
            mat1[i][j] = 2*i+1 ;
            mat2[i][j] = i+j ;
        }
    } 
    
    labw12(mat1,mat2,result);
    return 0;
}
