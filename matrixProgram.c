#include <stdio.h>
#include <stdlib.h>





void printMatrix(int m, int n, int** mat){
    for (int i = 0; i < m; i++){
        printf("[ ");
        for (int j = 0; j < n; j++){
            printf("%d", mat[i][j]);
            printf(" ");
        }
        printf("]\n");
    }
}

int** createMatrix(int m, int n) { 
    
    int** array = malloc(m * sizeof(int*)); 
    for (int i = 0; i < m; i++) { 
        array[i] = malloc(n * sizeof(int)); 
    } 
    
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            printf("Enter int for matrix A row %d col %d : ", i+1, j+1);
            scanf("%d", &array[i][j]);
        }
    }
    return array; 
} 

void deleteMatrix(int rows, int** matrix){
    for (int i = 0; i < rows; i++){
        free(matrix[i]);
    }
    free(matrix);
}

int** transpose(int rows, int cols, int** currMatrix){
    
    int** newM = malloc(cols * sizeof(int*)); 
    for (int i = 0; i < cols; i++) { 
        newM[i] = malloc(rows * sizeof(int)); 
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            newM[j][i] = currMatrix[i][j];
        }
    }

    deleteMatrix(rows, currMatrix);
    return newM;

}


int getNum(int max){
    int tempNum;
    printf("Choose a num from 1-%d : ", max);
    scanf("%d", &tempNum);
    if (tempNum >= 1 && tempNum <= max){
        return tempNum-1;
    }else{
        printf("not valid\n");
        getNum(max);
    }
}



int main() {
    
    int numOfMs = 0;
    int maxMs = 20;
    int ***matArr = (int ***)malloc(maxMs * sizeof(int **));
    int matRows[20];
    int matCols[20];
    int run = 1;
    
    
    
    while(run == 1){
        int userSelect = 1;
        printf("Current Num of Matrices: %d \nOptions: \n 1) Create Matrix (if num of Matrices is 19, Create Matrix will not work)\n 2) Print A Matrix (%d) \n 3) Transpose a Matrix\n n) Any Other Int to Exit\nSelect an option: ", numOfMs,numOfMs);
        scanf("%d", &userSelect);
        if (userSelect == 1 && numOfMs < 20){
            int tempM = 0;
            int tempN = 0;
            while(tempM == 0 || tempN == 0){
                printf("Enter m (rows) : ");
                scanf("%d", &tempM);
                printf("Enter n (cols) : ");
                scanf("%d", &tempN);
                if (tempM == 0 || tempN == 0){
                    printf("Rows or Cols cant be 0\n");
                }
            }
            int** newMatrix = createMatrix(tempM, tempN);
            matArr[numOfMs] = newMatrix;
            // mxn matrix
            matRows[numOfMs] = tempM;
            matCols[numOfMs] = tempN;

            numOfMs++;
            printMatrix(tempM, tempN, newMatrix);
            
        }else if (userSelect == 2){
            if (numOfMs == 0){
                printf("No Matrices found\n");
            }else{
                int tNum = getNum(numOfMs);
                printf("Matrix %d : \n", tNum);
                printMatrix(matRows[tNum], matCols[tNum], matArr[tNum]);
                printf("\n");
                
            }
        }else if (userSelect == 3){
            if (numOfMs == 0){
                printf("No Matrices found\n");
            }else{
                int tNum = getNum(numOfMs);
                printf("Transposing Matrix %d : \n", tNum);
                printMatrix(matRows[tNum], matCols[tNum], matArr[tNum]);

                matArr[tNum] = transpose(matRows[tNum], matCols[tNum], matArr[tNum]);
                int changeR = matRows[tNum];
                matRows[tNum] = matCols[tNum];
                matCols[tNum] = changeR;

                printf("New Matrix %d : \n", tNum);
                printMatrix(matRows[tNum], matCols[tNum], matArr[tNum]);
                printf("\n");
                
            }
        }else{
            run = 0;
        }        
    }

    return 0;
}