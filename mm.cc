#include <iostream>
#include <fstream>
#include <string>

using namespace std;


// returns dot product of two equal length arrays
int dot_product(int* u, int* v, int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += u[i] * v[i];
    }
    return sum;
}

// standard matrix multiplication algorithm
int** standard(int** A, int** B, int n) {
    int** product = new int*[n];
    for(size_t i = 0; i < n; ++i)
        product[i] = new int[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            product[i][j] = dot_product(A[i], B[j], n);
        }
    }
    return product;
}

// prints matrix
void print_matrix(int** matrix, int k, int n) {
    printf("matrix %i:\n", k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// ./mm 0 dimension inputfile
int main(int _argc, char *argv[]) {
    int mode = stoi(argv[1]);
    const int N = stoi(argv[2]);
    
    // initialize matrices (array of arrays)
    ifstream matrices(argv[3]);
    
    // representation: matrix1[i][j] == ith row, jth column
    int** matrix1 = new int*[N]; // each element is a pointer to an array.
    for(size_t i = 0; i < N; ++i)
        matrix1[i] = new int[N]; // build rows
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            string val;
            getline(matrices, val);
            matrix1[i][j] = stoi(val);
        }
    }
    // representation: matrix2[i][j] == jth row, ith column (tranpose, that way standard mutltiplication is easier)
    int** matrix2 = new int*[N]; // each element is a pointer to an array.
    for(size_t i = 0; i < N; ++i)
        matrix2[i] = new int[N]; // build rows
    for(size_t i = 0; i < N; ++i)
    {
        for(size_t j = 0; j < N; ++j)
        {
            string val;
            getline(matrices, val);
            matrix2[j][i] = stoi(val);
        }
    }

    // print matrices
    print_matrix(matrix1, 1, N);
    print_matrix(matrix2, 2, N);
    int** product = standard(matrix1, matrix2, N);
    print_matrix(product, 3, N);

    // delete matrices
    for(size_t i = 0; i < N; ++i)
        delete matrix1[i];
    delete matrix1;
    for(size_t i = 0; i < N; ++i)
        delete matrix2[i];
    delete matrix2;
    for(size_t i = 0; i < N; ++i)
        delete product[i];
    delete product;        
}