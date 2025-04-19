#include <iostream>
#include <vector>
using namespace std;



class Matrix{
    public:
        char id;
        int rows;
        int cols;
        int** mat;
        Matrix(int rowNum, int colNum, char identity){
            rows = rowNum;
            cols = colNum;
            id = identity;
            mat = new int*[rows];
            for (int i = 0; i < rows; i++) {
                mat[i] = new int[cols];
            }
        }

        void transpose(){
            int newRows = cols;
            int newCols = rows;

            int** newMat = new int*[newRows];
            for (int i = 0; i < newRows; i++){
                newMat[i] = new int[newCols];
            }

            for (int i = 0; i < rows; i++){
                for (int j = 0; j < cols; j++){
                    newMat[j][i] = mat[i][j];
                }
            }
            
            for (int i = 0; i < rows; i++) {
                delete[] mat[i];
            }
            delete[] mat;

            mat = newMat;
            rows = newRows;
            cols = newCols;
        }

        void scaleM(int k){
            for (int i = 0; i < rows; i++){
                for (int j = 0; j < cols; j++){
                    mat[i][j] = k*mat[i][j];
                }
            }
        }


        void fillMatrix(){
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < cols; j++){
                    cout << "Enter Matrix " << i << " " << j << " value: ";
                    int num;
                    cin >> num;
                    mat[i][j] = num;
                }
            }
        }

        void printMatrix(){
            for(int i = 0; i < rows; i++){
                cout << "[ ";
                for(int j = 0; j < cols; j++){
                    cout << mat[i][j] << " ";
                }
                cout << "]" << endl;
            }
        }
    
};  



char makeNewMName(vector<Matrix*> &allMs){
    char newMName;
    cout << "Enter Name of new Matrix: ";
    cin >> newMName;
    if (findMatrix(newMName, allMs) == -1){
        return newMName;
    }else{
        cout << "Name Already in use, try again" << endl;
        makeNewMName(allMs);
    }
}


int* getMSize(){
    int* arr = new int[2];
    cout << "Enter Matrix Number of Rows: ";
    cin >> arr[0];
    cout << "Enter Matrix Number of Columns: ";
    cin >> arr[1];
    if (arr[0] <= 0 || arr[1] <= 0){
        cout << "0 or less row/col found, try again" << endl;
        getMSize();
    }else{
        return arr;
    }
}

int findMatrix(char id, vector<Matrix*> &allMs){
    for (int i = 0; i < allMs.size(); i++){
        if (allMs[i]->id == id){
            return i;
        }
    }
    return -1;
}

int total(Matrix *one, Matrix *two, int row, int col, int len){
    int total = 0;
    for (int i = 0; i < len; i++){
        total = total + one->mat[row][i] + two->mat[i][col];
    }
    return total;
}



int main() {
    vector<Matrix*> myMatrices;

    bool run = true;
    while(run){
        int doCommand;
        cout << "Current Num of Matrices: " << myMatrices.size() <<
        "\n 1) Create Matrix" <<
        "\n 2) Print all Matrices" <<
        "\n 3) Transpose a Matrix" <<
        "\n 4) Scalar Multipy a Matrix" <<
        "\n 5) Matrix Addition" << 
        "\n 6) Matrix Multiplication" << 
        "\n n) Any other Int to quit\n" <<
        "Choose: "
        
        
        ;
        cin >> doCommand;
        if (doCommand == 1){
            char iden;
            cout << "Name the matrix using a character: ";
            cin >> iden;
            int* arr = getMSize();
            Matrix* m = new Matrix(arr[0], arr[1], iden);
            m->fillMatrix();
            myMatrices.push_back(m);
        }else if (doCommand == 2){
            if (myMatrices.size() == 0){
                cout << "No Matrices found" << endl;
            }else{
                for (int i = 0; i < myMatrices.size(); i++){
                    cout << myMatrices[i]->id << " : " << "\n";
                    myMatrices[i]->printMatrix();
                }
            }
        }else if (doCommand == 3){
            if (myMatrices.size() == 0){
                cout << "No Matrices found" << endl;
            }else{
                char name;
                cout << "Enter an existing Matrix Name: ";
                cin >> name;
                int location = findMatrix(name, myMatrices);
                if (location == -1){
                    cout << "Matrix not found" << endl;
                }else{
                    cout << "Transposing Matrix " << name << endl;
                    cout << "Original " << name << endl;
                    myMatrices[location]->printMatrix();
                    cout << "New " << name << endl;
                    myMatrices[location]->transpose();
                    myMatrices[location]->printMatrix();
                }
            }
        }else if (doCommand == 4){
            if (myMatrices.size() == 0){
                cout << "No Matrices found" << endl;
            }else{
                int scale;
                cout << "Enter a Int to scale a Matrix By: ";
                cin >> scale;
                char name;
                cout << "Enter an existing Matrix Name: ";
                cin >> name;
                int location = findMatrix(name, myMatrices);
                if (location == -1){
                    cout << "Matrix Not found" << endl;
                }else{
                    cout << "Scalar multiplying matrix " << name << " by " << scale << endl;
                    cout << "Original " << name << " : " << endl;
                    myMatrices[location]->printMatrix();
                    cout << "New " << name << endl;
                    myMatrices[location]->scaleM(scale);
                    myMatrices[location]->printMatrix();
                }
            }
        }else if (doCommand == 5){
            if (myMatrices.size() < 2){
                cout << "Not enough Matrices found" << endl;
            }else{
                char nameOne;
                char nameTwo;
                cout << "Enter an existing Matrix Name: ";
                cin >> nameOne;
                cout << "Enter a second existing Matrix Name: ";
                cin >> nameTwo;
                int locOne = findMatrix(nameOne, myMatrices);
                int locTwo = findMatrix(nameTwo, myMatrices);
                if (locOne == -1 || locTwo == -1){
                    cout << "A matrix could not be found" << endl;
                }else{
                    bool checkRow = myMatrices[locOne]->rows == myMatrices[locTwo]->rows;
                    bool checkCol = myMatrices[locOne]->cols == myMatrices[locTwo]->cols;
                    if (checkRow && checkCol){
                        char newMName = makeNewMName(myMatrices);
                        int r = myMatrices[locOne]->rows;
                        int c = myMatrices[locOne]->cols;
                        Matrix* newM = new Matrix(r, c, newMName);
                        for (int i = 0; i < r; i++){
                            for (int j = 0; j < c; j++){
                                newM->mat[i][j] = myMatrices[locOne]->mat[i][j] + myMatrices[locTwo]->mat[i][j];
                            }
                        }
                        myMatrices.push_back(newM);
                        cout << "New Matrix " << newMName << endl;
                        newM->printMatrix();
                    }else{
                        cout << "Matrix Sizes Dont match" << endl;
                    }
                }
            }
        }else if (doCommand == 6){
            if (myMatrices.size() < 2){
                cout << "Not enough Matrices found" << endl;
            }else{
                char nameOne;
                char nameTwo;
                cout << "Enter an existing Matrix Name: ";
                cin >> nameOne;
                cout << "Enter a second existing Matrix Name: ";
                cin >> nameTwo;
                int locOne = findMatrix(nameOne, myMatrices);
                int locTwo = findMatrix(nameTwo, myMatrices);
                if (locOne == -1 || locTwo == -1){
                    cout << "A matrix could not be found" << endl;
                }else{
                    bool checkSize =  myMatrices[locOne]->cols == myMatrices[locTwo]->rows;
                    int maxSize = myMatrices[locOne]->cols;
                    if (checkSize){
                        char newMName = makeNewMName(myMatrices);
                        int r = myMatrices[locOne]->rows;
                        int c = myMatrices[locTwo]->cols;
                        Matrix* multM = new Matrix(r, c, newMName);
                        for (int i = 0; i < r; i++){
                            for (int j = 0; j < c; j++){
                                multM->mat[i][j] = total(myMatrices[locOne], myMatrices[locTwo], i, j, maxSize);
                            }
                        }
                        myMatrices.push_back(multM);
                        cout << "New Matrix " << newMName << endl;
                        multM->printMatrix();
                    }else{
                        cout << "Matrices of these Sizes will not work" << endl;
                    }
                }
            }
        }
        
        
        else{
            run = false;
        }
    }

    return 0;
}