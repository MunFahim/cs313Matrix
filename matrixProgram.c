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

int** addMatrices(int rows, int cols, int** firstMatrix, int** secMatrix){
    int** addMatixArr = malloc(rows * sizeof(int*)); 
    for (int i = 0; i < rows; i++) { 
        addMatixArr[i] = malloc(cols * sizeof(int)); 
    } 
    
    for (int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            addMatixArr[i][j] = firstMatrix[i][j] + secMatrix[i][j];
        }
    }
    return addMatixArr;
}


int** subtractMatrix(int rows, int cols, int** firstMatrix, int** secMatrix){
    int** subMatixArr = malloc(rows * sizeof(int*)); 
    for (int i = 0; i < rows; i++) { 
        subMatixArr[i] = malloc(cols * sizeof(int)); 
    } 
    
    for (int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            subMatixArr[i][j] = firstMatrix[i][j] - secMatrix[i][j];
        }
    }
    return subMatixArr;
}

int getTotal(int** firstM, int** secondM, int row, int col, int length){
    int total = 0;
    for (int i = 0; i < length; i++){
        total = total + firstM[row][i]*secondM[i][col];
    }
    return total;
}



int** multiplyMatrices(int rows, int cols, int** firstM, int** secondM, int len){

    int** multMatrix = malloc(rows * sizeof(int*)); 
    for (int i = 0; i < rows; i++) { 
        multMatrix[i] = malloc(cols * sizeof(int)); 
    } 

    for (int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            multMatrix[i][j] = getTotal(firstM, secondM, i, j, len);
        }
    }

    return multMatrix;

}



int getNum(int max){
    int tempNum;
    printf("Choose a Matrix num from 1-%d : ", max);
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
        printf("Current Num of Matrices: %d \nOptions: \n 1) Create Matrix (if num of Matrices is 19, Create Matrix will not work)\n 2) Print A Matrix (%d) \n 3) Transpose a Matrix\n 4) Print all Matrices \n 5) Scalar Multiply a Matrix \n 6) Add two Matrices \n 7) Multiply Two Matrices\n 8) Subtract two Matrices\n n) Any Other Int to Exit\nSelect an option: ", numOfMs,numOfMs);
        scanf("%d", &userSelect);
        if (userSelect == 1){
            if (numOfMs >= 19){
                printf("Too many Matrices, restart program\n");
            }else{
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
            }
        }else if (userSelect == 2){
            if (numOfMs == 0){
                printf("No Matrices found\n");
            }else{
                int tNum = getNum(numOfMs);
                printf("Matrix %d : \n", tNum+1);
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
        }else if (userSelect == 4){
            if (numOfMs == 0){
                printf("No Matrices found\n");
            }else{
                for (int i = 0; i < numOfMs; i++){
                    printf("%d : \n", i+1);
                    printMatrix(matRows[i], matCols[i], matArr[i]);
                }
            }
        }else if (userSelect == 5){
            if (numOfMs == 0){
                printf("No Matrices found\n");
            }else{
                int scale = 0;
                int tNum = getNum(numOfMs);
                printf("Enter Int to scale Matrix by: ");
                scanf("%d", &scale);

                printf("Before Scale: \n");
                printMatrix(matRows[tNum], matCols[tNum], matArr[tNum]);

                for(int i = 0; i < matRows[tNum]; i++){
                    for (int j = 0; j < matCols[tNum]; j++){
                        matArr[tNum][i][j] = matArr[tNum][i][j]*scale;
                    }
                }

                printf("After Scale: \n");
                printMatrix(matRows[tNum], matCols[tNum], matArr[tNum]);

            }
        }else if (userSelect == 6){
            if (numOfMs < 2 || numOfMs >= 19){
                printf("No Matrices found (or less than 2) , or too many Matrices (restart program)\n");
            }else{
                
                int firstMatrix = getNum(numOfMs);
                int secMatrix = getNum(numOfMs);
                if (matRows[firstMatrix] != matRows[secMatrix] || matCols[firstMatrix] != matCols[secMatrix]){
                    printf("Matrices are different sizes, can not add\n");
                }else{
                    printf("Adding Matrix %d + %d \n", firstMatrix, secMatrix);
                    printMatrix(matRows[firstMatrix], matCols[firstMatrix], matArr[firstMatrix]);
                    printf("+\n");
                    printMatrix(matRows[secMatrix], matCols[secMatrix], matArr[secMatrix]);
                    printf("= New Matrix #%d\n", numOfMs);

    
                    int rows = matRows[firstMatrix];
                    int cols = matCols[firstMatrix];

                    matRows[numOfMs] = rows;
                    matCols[numOfMs] = cols;
                    matArr[numOfMs] = addMatrices(rows, cols, matArr[firstMatrix], matArr[secMatrix]);
                    printMatrix(matRows[numOfMs], matCols[numOfMs], matArr[numOfMs]);
                    numOfMs++;
                }
            }
        }else if (userSelect == 7){
            if (numOfMs < 2 || numOfMs >= 19){
                printf("No Matrices found (or less than 2) , or too many Matrices (restart program)\n");
            }else{
                int firstMatrix = getNum(numOfMs);
                int secMatrix = getNum(numOfMs);
                if (matCols[firstMatrix] != matRows[secMatrix]){
                    printf("First Matrix Columns not equal to Second Matrix Rows, can not multiply\n");
                }else{
                    printf("Multiplying Matrix %d + %d \n", firstMatrix, secMatrix);
                    printMatrix(matRows[firstMatrix], matCols[firstMatrix], matArr[firstMatrix]);
                    printf("*\n");
                    printMatrix(matRows[secMatrix], matCols[secMatrix], matArr[secMatrix]);
                    printf("= new Matrix #%d\n", numOfMs);

                    int rows = matRows[firstMatrix];
                    int cols = matCols[secMatrix];
                    matRows[numOfMs] = rows;
                    matCols[numOfMs] = cols;
                    matArr[numOfMs] = multiplyMatrices(rows, cols, matArr[firstMatrix], matArr[secMatrix], matCols[firstMatrix]);
                    printMatrix(rows, cols, matArr[numOfMs]);
                    numOfMs++;

                }
            }
        }else if (userSelect == 8){
            if (numOfMs < 2 || numOfMs >= 19){
                printf("No Matrices found (or less than 2), or too many Matrices (restart program)\n");
            }else{
                
                int firstMatrix = getNum(numOfMs);
                int secMatrix = getNum(numOfMs);
                if (matRows[firstMatrix] != matRows[secMatrix] || matCols[firstMatrix] != matCols[secMatrix]){
                    printf("Matrices are different sizes, can not subtract\n");
                }else{
                    printf("Subtracting Matrix %d + %d \n", firstMatrix, secMatrix);
                    printMatrix(matRows[firstMatrix], matCols[firstMatrix], matArr[firstMatrix]);
                    printf("-\n");
                    printMatrix(matRows[secMatrix], matCols[secMatrix], matArr[secMatrix]);
                    printf("= New Matrix #%d\n", numOfMs);

    
                    int rows = matRows[firstMatrix];
                    int cols = matCols[firstMatrix];

                    matRows[numOfMs] = rows;
                    matCols[numOfMs] = cols;
                    matArr[numOfMs] = subtractMatrix(rows, cols, matArr[firstMatrix], matArr[secMatrix]);
                    printMatrix(matRows[numOfMs], matCols[numOfMs], matArr[numOfMs]);
                    numOfMs++;
                }
            }
        }else{
            run = 0;
        }        
    }

    for(int i = 0; i < numOfMs; i++){
        deleteMatrix(matRows[i], matArr[i]);
    }


    return 0;
}