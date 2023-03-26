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

int** matrix_addition(int** A, int** B, size_t n) {
    
    int** commputation = new int*[n];
    for(size_t i = 0; i < n; ++i)
        commputation[i] = new int[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            product[i][j] = A[i][j] + B[i][j];
        }
    }
}

int** matrix_subtraction(int** A, int** B, size_t n) {
    
    int** commputation = new int*[n];
    for(size_t i = 0; i < n; ++i)
        commputation[i] = new int[n];

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            product[i][j] = A[i][j] - B[i][j];
        }
    }
}

int** strassen(int** A, int** B, int n0) {

    size_t n = sizeof(A[1]) / sizeof(int) // Get the dimensions of A and B at this point  
    if (n == n0) {
        return standard(A, B, n0);
    }
    
    size_t ndiv_2 = n/2
    int** a = new int*[ndiv_2];            // Creating the different spliced arrays 
    int** b = new int*[ndiv_2];
    int** c = new int*[ndiv_2];
    int** d = new int*[ndiv_2];

    int** e = new int*[ndiv_2];
    int** f = new int*[ndiv_2];
    int** g = new int*[ndiv_2];
    int** h = new int*[ndiv_2];

    for (size_t i = 0; i < ndiv_2; ++i)  // Dynamically allocate memory for array of integers with ndiv_2 elements 
        a[i] = new int[ndiv_2];          // for each spliced array
        b[i] = new int[ndiv_2];
        c[i] = new int[ndiv_2];
        d[i] = new int[ndiv_2];

        e[i] = new int[ndiv_2];
        f[i] = new int[ndiv_2];
        g[i] = new int[ndiv_2];
        h[i] = new int[ndiv_2];


    for (size_t i = 0; i < ndiv_2; i++) {   // The next four for loops assign the spliced arrays to the 
        for (size_t j = 0; j < ndiv_2; j++) { // correct values 
            a[i][j] = A[i][j];
            e[i][j] = B[i][j];
        }
    }
    for (size_t i = 0; i < ndiv_2; i++) {
        for (size_t j = ndiv_2; j < n; j++) {
            b[i][j-ndiv_2] = A[i][j];
            f[i][j-ndiv_2] = B[i][j];
        }
    }
    for (size_t i = ndiv_2; i < n; i++) {
        for (size_t j = 0; j < ndiv_2; j++) {
            c[i-ndiv_2][j] = A[i][j];
            g[i-ndiv_2][j] = B[i][j];
        }
    }
    for (size_t i = ndiv_2; i < n; i++) {
        for (size_t j = ndiv_2; j < n; j++) {
            d[i-ndiv_2][j-ndiv_2] = A[i][j];
            h[i-ndiv_2][j-ndiv_2] = B[i][j];
        }
    }

    p1 = strassen(matrix_addition(a,d,ndiv_2), matrix_addition(e,h,ndiv_2));
    p2 = strassen(d, matrix_subtraction(g,e,ndiv_2));
    p3 = strassen(matrix_addition(a,b,ndiv_2), h);
    p4 = strassen(matrix_subtraction(b,d,ndiv_2), matrix_addition(g,h,ndiv_2));
    p5 = strassen(a, matrix_subtraction(f,h,ndiv_2));
    p6 = strassen(matrix_addition(c,d,ndiv_2), e);
    p7 = strassen(matrix_subtraction(a,c,ndiv_2), matrix_addition(e,f,ndiv_2));


    c11 = matrix_addition(matrix_subtraction(matrix_addition(p1, p2,ndiv_2), p3), p4);
    c12 = matrix_addition(p3, p5, ndiv_2);
    c21 = matrix_addition(p6, p2, ndiv_2);
    c22 = matrix_subtraction(matrix_subtraction(matrix_addition(p5, p1,ndiv_2), p6), p7);

    int** C = new int*[n];
    for(size_t i = 0; i < n; ++i)
        C[i] = new int[n];

    for (size_t i = 0; i < ndiv_2; i++) {   // The next four for loops assign the spliced arrays to the 
        for (size_t j = 0; j < ndiv_2; j++) { // correct values 
            C[i][j] = c11[i][j];
        }
    }
    for (size_t i = 0; i < ndiv_2; i++) {
        for (size_t j = ndiv_2; j < n; j++) {
            C[i][j] = c12[i][j-ndiv_2];
        }
    }
    for (size_t i = ndiv_2; i < n; i++) {
        for (size_t j = 0; j < ndiv_2; j++) {
            C[i][j] = c21[i-ndiv_2][j-];
        }
    }
    for (size_t i = ndiv_2; i < n; i++) {
        for (size_t j = ndiv_2; j < n; j++) {
            C[i][j] = c22[i-ndiv_2][j-ndiv_2];
        }
    }

    return C;
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