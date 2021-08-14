// Course:  CS213 - Programming II  - 2018
// Title:   Assignment I - Task 1 - Problem 1
// Program: CS213-2018-A1-T1-P1
// Purpose: Skeleton code for the student to start working
// Author:  Dr. Mohammad El-Ramly
// Date:    10 August 2018
// Version: 1.0

#include <iostream>
#include <iomanip>
#include <cassert>

using namespace std;

// A structure to store a matrix
struct matrix
{
  int* data;       // Pointer to 1-D array that will simulate matrix
  int row, col;
};

// Already implemented
void createMatrix (int row, int col, int num[], matrix& mat);

matrix operator+  (matrix mat1, matrix mat2) // Add if same dimensions
{
    assert((mat1.row == mat2.row) && (mat1.col == mat2.col));        //to sure if rows and cols are equal
    matrix mat;
    mat.row = mat1.row;
    mat.col = mat1.col;
    mat.data = new int[mat1.row * mat1.col];
    for(int i=0; i < mat1.row * mat1.col; i++){
        mat.data[i] = mat1.data[i] + mat2.data[i];
    }
    return mat;
}

matrix operator-  (matrix mat1, matrix mat2) // Sub if same dimensions
{
    assert((mat1.row == mat2.row) && (mat1.col == mat2.col));        //to sure if rows and cols are equal
    matrix mat;
    mat.row = mat1.row;
    mat.col = mat1.col;
    mat.data = new int[mat1.row * mat1.col];
    for(int i=0; i < mat1.row * mat1.col; i++){
        mat.data[i] = mat1.data[i] - mat2.data[i];
    }
    return mat;
}

matrix operator*  (matrix mat1, matrix mat2) // Multi if col1 == row2
{
    assert((mat1.col == mat2.row));        //to sure if rows and cols are equal
    matrix mat;
    mat.row = mat1.row;
    mat.col = mat2.col;
    mat.data = new int[mat1.row * mat2.col];
    for (int i = 0; i < mat1.row; i++) {
        for (int j = 0; j < mat2.col; j++) {
            int sum = 0;
            for (int k = 0; k < mat1.col; k++)
                sum = sum + mat1.data[i * mat1.col + k] * mat2.data[k * mat2.col + j];
            mat.data[i * mat2.col + j] = sum;
        }
    }
    return mat;

}

matrix operator+  (matrix mat1, int scalar)  // Add a scalar
{
    matrix mat;
    mat.row = mat1.row;
    mat.col = mat1.col;
    for(int i=0; i < mat1.row*mat1.col; i++){
        mat.data[i] = mat1.data[i] + scalar;
    }
    return mat;
}

matrix operator-  (matrix mat1, int scalar)  // Subtract a scalar
{
    matrix mat;
    mat.row = mat1.row;
    mat.col = mat1.col;
    for(int i=0; i < mat1.row*mat1.col; i++){
        mat.data[i] = mat1.data[i] - scalar;
    }
    return mat;
}

matrix operator*  (matrix mat1, int scalar)  // Multiple by scalar
{
    matrix new_mat;
    new_mat.row = mat1.row;
    new_mat.col = mat1.col;
    new_mat.data = new int[mat1.row * mat1.col];
    for(int i = 0; i < mat1.row * mat1.col; i++){
        new_mat.data[i] = mat1.data[i] * scalar;
    }
    return new_mat;
}


matrix operator+= (matrix& mat1, matrix mat2) // mat1 changes & return new matrix with the sum
{
    assert((mat1.row == mat2.row) && (mat1.col == mat2.col));        //to sure if rows and cols are equal
    for(int i=0; i < mat1.row * mat1.col; i++){
        mat1.data[i] += mat2.data[i];
    }
    return mat1;
}

matrix operator-= (matrix& mat1, matrix mat2) // mat1 changes + return new matrix with difference
{

    assert((mat1.row == mat2.row) && (mat1.col == mat2.col));        //to sure if rows and cols are equal
    for(int i=0; i < mat1.row * mat1.col; i++){
        mat1.data[i] -= mat2.data[i];
    }
    return mat1;
}
matrix operator+= (matrix& mat, int scalar)   // change mat & return new matrix
{
    for(int i=0; i < mat.row * mat.col; i++){
            mat.data[i] += scalar;
    }
    return mat;
}
matrix operator-= (matrix& mat, int scalar)   // change mat & return new matrix
{
    for(int i=0; i < mat.row * mat.col; i++){
            mat.data[i] -= scalar;
    }
    return mat;
}

void   operator++ (matrix& mat)   	// Add 1 to each element ++mat
{
    for(int i=0; i < mat.row*mat.col; i++){
        mat.data[i] = mat.data[i] + 1;
    }
}

void   operator-- (matrix& mat)    	// Sub 1 from each element --mat
{
    for(int i=0; i < mat.row*mat.col; i++){
        mat.data[i] = mat.data[i] - 1;
    }
}

// The last operator >> takes an istream and a matrix and return the
// the same istream so it is possible to cascade input like
// cin >> matrix1 >> matrix2 << endl;
istream& operator>> (istream& in, matrix& mat)
{
    // Input matrix like this (dim 2 x 3) cin >> 2 3 4 6 8 9 12 123
    // and return istream to allow cascading input
    cout << "Enter the number of rows: " << endl;
    in >> mat.row;
    cout << "Enter the number of columns: " << endl;
    in >> mat.col;
    cout << "Enter the matrix elements: " << endl;
    for(int i = 0; i < mat.row * mat.col; i++){
        in >> mat.data[i];
    }
    return in;
}


ostream& operator<< (ostream& out, matrix mat)
{
    // Print matrix  as follows (2 x 3)			4	 6 	  8
    // and return ostream to cascade printing	9	12  	123
    for(int i=0; i < mat.row; i++){
        for(int j=0 ; j < mat.col ;j++){
            out << mat.data[i*mat.col + j];
            out << " ";
        }
        out << "\n";
    }
    return out;
}

bool   operator== (matrix mat1, matrix mat2)	// True if identical
{
    bool check = true;
    if((mat1.col == mat2.col) && (mat1.row == mat2.row)){
        check = true;
        for(int i=0; i < mat1.col * mat1.row; i++){
            if(mat1.data[i] != mat2.data[i]){
                check = false;
            }
        }
    }
    else{
        check = false;
    }
    if(check == true){
        return true;
    }
    else{
        return false;
    }
}

bool   operator!= (matrix mat1, matrix mat2) 	// True if not same
{
    bool check = false;
    if((mat1.col != mat2.col) || (mat1.row != mat2.row)){
        check = true;
    }
    else{
        for(int i=0; i < mat1.col * mat1.row; i++){
            if(mat1.data[i] != mat2.data[i]){
                check = true;
            }
        }
    }
    if(check == true){
        return true;
    }
    else{
        return false;
    }
}

bool   isSquare   (matrix mat)  // True if square matrix
{
    if(mat.col == mat.row){
        return true;
    }
    else{
        return false;
    }
}

bool   isSymetric (matrix mat)  // True if square and symmetric
{
    if(mat.col == mat.row){
        for(int i=0; i < mat.row; i++){
            for(int j=0; j < mat.col; j++){
                if(mat.data[i * mat.col + j] == mat.data[j * mat.row + i]){
                    return true;
                }
                else{
                    return false;
                }
            }
        }
    }
    else{
        return false;
    }
}

bool   isIdentity (matrix mat)  // True if square and identity
{
    bool check = true;
    if(mat.col == mat.row){
        for(int i=0; i < mat.row; i++){
            for(int j=0; j < mat.col; j++){
                //check for diagonals element
                if(i == j && (mat.data[i * mat.col + j]) != 1)
                {
                    check = false;
                    break;
                }
                //check for rest elements
                else if(i != j && (mat.data[i * mat.col + j]) != 0)
                {
                    check = false;
                    break;
                }
            }
        }
    if(check == false)
       return false;
    else
        return true;
    }
}

matrix transpose(matrix mat)    // Return new matrix with the transpose
{
    matrix new_mat;
    new_mat.row = mat.col;
    new_mat.col = mat.row;
    new_mat.data = new int[mat.col * mat.row];
    for(int i=0; i < mat.row; i++){
        for(int j=0; j < mat.col; j++){
            new_mat.data[j * mat.row + i] = mat.data[i * mat.col + j];
        }
    }
    return new_mat;
}

//__________________________________________

int main()
{
  int data1 [] = {1,2,3,4,5,6};
  int data2 [] = {7,9,4,2,0,4};
  int data3 [] = {10,100,10,100,10,100,10,100};
  int data4 [] = {10,20,30,40,50,60};

  matrix mat1, mat2, mat3, mat4;
  createMatrix (2, 3, data1, mat1);
  createMatrix (3, 2, data2, mat2);
  createMatrix (4, 2, data3, mat3);
  createMatrix (2, 3, data4, mat4);
// The next code will not work until you write the functions
  cout << mat1 << endl;
  cout << mat2 << endl;
  cout << mat3 << endl;

  //cout << (mat1 + mat2) << endl << endl;
  cout << (mat3 + mat2) << endl << endl;
  cout << (mat1 * mat2) << endl << endl;
  ++mat1;
  cout << mat1 << endl;

  mat1+= mat4 ;
  cout << mat1 << endl;
  cout << mat2 << endl;
  cout << mat3 << endl;
  // Add more examples of using matrix
  // .......

  // UNEQUALITY CHECK
  bool check = (mat1 != mat2);
  cout << check << endl << endl;

  // Symmetric check
  int data5 [] = {1,2,3,2,3,4,3,4,5};
  matrix mat5;
  createMatrix (3, 3, data5, mat5);
  bool check2 = isSymetric(mat5);
  cout << check2 << endl << endl;

  //Identity check
  int data6 [] = {1,0,0,0,1,0,0,0,1};
  matrix mat6;
  createMatrix (3, 3, data6, mat6);
  bool check3 = isIdentity(mat6);
  cout << check3 << endl << endl;
  mat1 = transpose(mat1);
  cout << mat1 << endl << endl;

  // ISTREAM OPERATOR
  matrix mat7;
  cin >> mat7;
  cout << mat7 << endl;
  cout << mat7*2 << endl;
  return 0;
}

//__________________________________________
// Takes an array of data and stores in matrix according
// to rows and columns
void createMatrix (int row, int col, int num[], matrix& mat) {
  mat.row = row;
  mat.col = col;
  mat.data = new int [row * col];
  for (int i = 0; i < row * col; i++){
    mat.data [i] = num [i];
    //cout << mat.data[i] << endl;
  }
}
