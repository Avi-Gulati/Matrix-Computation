#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <vector>

using namespace std;

void matrix_del(int** A, int n) {
    for(size_t i = 0; i < n; i++)
        delete A[i];
    delete A;
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

int** standard(int** A, int** B, int n) {
    int** product = new int*[n];
    for(size_t i = 0; i < n; i++)
        product[i] = new int[n];
    // compute products
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            product[i][j] = 0;
            for (int k = 0; k < n; k++) {
                product[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return product;
}

int** matrix_addition(int** A, int** B, size_t n) {
    int** sum = new int*[n];
    for(size_t i = 0; i < n; i++)
        sum[i] = new int[n];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            sum[i][j] = A[i][j] + B[i][j];
        }
    }
    return sum;
}

int** matrix_subtraction(int** A, int** B, size_t n) {
    int** difference = new int*[n];
    for(size_t i = 0; i < n; i++)
        difference[i] = new int[n];    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            difference[i][j] = A[i][j] - B[i][j];
        }
    }
    return difference;
}

int** strassen(int** A, int** B, int n, int n0) {

    // changed it so "n" is a function argument and doesn't need to be computedx
    if (n <= n0) { // replaced "==" with "<="
        return standard(A, B, n);
    }
    
    size_t ndiv_2 = n / 2;
    int** a = new int*[ndiv_2];            // Creating the different spliced arrays 
    int** b = new int*[ndiv_2];
    int** c = new int*[ndiv_2];
    int** d = new int*[ndiv_2];
    int** e = new int*[ndiv_2];
    int** f = new int*[ndiv_2];
    int** g = new int*[ndiv_2];
    int** h = new int*[ndiv_2];
    for (size_t i = 0; i < ndiv_2; i++) { // Dynamically allocate memory for array of integers with ndiv_2 elements 
        a[i] = new int[ndiv_2];          // for each spliced array
        b[i] = new int[ndiv_2];
        c[i] = new int[ndiv_2];
        d[i] = new int[ndiv_2];
        e[i] = new int[ndiv_2];
        f[i] = new int[ndiv_2];
        g[i] = new int[ndiv_2];
        h[i] = new int[ndiv_2];
    }
    for (size_t i = 0; i < ndiv_2; i++) {
        for (size_t j = 0; j < ndiv_2; j++) {
            a[i][j] = A[i][j];
            e[i][j] = B[i][j];
            b[i][j] = A[i][j+ndiv_2];
            f[i][j] = B[i][j+ndiv_2];
            c[i][j] = A[i+ndiv_2][j];
            g[i][j] = B[i+ndiv_2][j];
            d[i][j] = A[i+ndiv_2][j+ndiv_2];
            h[i][j] = B[i+ndiv_2][j+ndiv_2];
        }
    }

    int** p1 = strassen(a, matrix_subtraction(f,h,ndiv_2), ndiv_2, 1);
    int** p2 = strassen(matrix_addition(a,b,ndiv_2), h, ndiv_2, 1);
    int** p3 = strassen(matrix_addition(c,d,ndiv_2), e, ndiv_2, 1);
    int** p4 = strassen(d, matrix_subtraction(g,e,ndiv_2), ndiv_2, 1);
    int** p5 = strassen(matrix_addition(a,d,ndiv_2), matrix_addition(e,h,ndiv_2), ndiv_2, 1);
    int** p6 = strassen(matrix_subtraction(b,d,ndiv_2), matrix_addition(g,h,ndiv_2), ndiv_2, 1);
    int** p7 = strassen(matrix_subtraction(c,a,ndiv_2), matrix_addition(e,f,ndiv_2), ndiv_2, 1);

    int** C = new int*[n];
    for(size_t i = 0; i < n; i++)
        C[i] = new int[n];
    for (size_t i = 0; i < ndiv_2; i++) {
        for (size_t j = 0; j < ndiv_2; j++) {
            C[i][j] = p4[i][j] - p2[i][j] + p5[i][j] + p6[i][j];
            C[i][j+ndiv_2] = p1[i][j] + p2[i][j];
            C[i+ndiv_2][j] = p3[i][j] + p4[i][j];
            C[i+ndiv_2][j+ndiv_2] = p1[i][j] - p3[i][j] + p5[i][j] + p7[i][j];
        }
    }

    // delete intermediate matrices
    matrix_del(p1, ndiv_2);
    matrix_del(p2, ndiv_2);
    matrix_del(p3, ndiv_2);
    matrix_del(p4, ndiv_2);
    matrix_del(p5, ndiv_2);
    matrix_del(p6, ndiv_2);
    matrix_del(p7, ndiv_2);
    return C;
}

int** graph_generator(int n, float p) {
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_real_distribution<float> distr(0, 1);
    
    int** graph = new int*[n];
    for(size_t i = 0; i < n; i++)
        graph[i] = new int[n];
    for (int j = 0; j < n; j++) {
        for (int i = 0; i <= j; i++) {
            int value = 0;
            if (distr(generator) <= p) {
                value = 1;
            }
            graph[i][j] = value;
            graph[j][i] = value;
        }
    }
    return graph;
}

int triangle_counter(int n, int** graph) {
    int** result = strassen(graph, strassen(graph, graph, n, 1), n, 1);
    int count = 0;
    for (int i = 0; i < n; i++) {
        count += result[i][i];
    }
    return count / 6;
}

vector<float> triangle_tester(int n, int k, float* probabilities, int np) {
    vector<float> output;
    for (int i = 0; i < np; i++) {
        int average = 0;
        for (int j = 0; j < k; j++) {
            average += triangle_counter(n, graph_generator(n, probabilities[i]));
        }
        output.push_back(average / k);
    }
    return output;
}



// Taken online from includehelp.com. We use bitshifting to find the next power of 2 of a number. 
int  computeNextPowerOfTwo( int  n )
{
	// Result is intialized as 1
	int value = 1;
	// The following while loop will run until we 
	// get a number greater than n
	while(value<n)
	{
		// value will be left shifted by 1 place in each iteration
		value=value << 1;
	}
	return value ;
}

// ./mm 0 dimension inputfile
int main(int _argc, char *argv[]) {
    int mode = stoi(argv[1]);
    const int N = stoi(argv[2]);
    

    int nextPowerOfTwo = computeNextPowerOfTwo(N);
    
    // initialize matrices (array of arrays)
    ifstream matrices(argv[3]);
    
    // representation: matrix1[i][j] == ith row, jth column
    int** matrix1 = new int*[nextPowerOfTwo]; // each element is a pointer to an array.
    for(size_t i = 0; i < nextPowerOfTwo; i++)
        matrix1[i] = new int[nextPowerOfTwo]; // build rows
    for(size_t i = 0; i < nextPowerOfTwo; i++)
    {
        for(size_t j = 0; j < nextPowerOfTwo; j++)
        {
            if (i < N && j < N) {
                string val;
                getline(matrices, val);
                matrix1[i][j] = stoi(val);
            }
            else {
                matrix1[i][j] = 0;
            }
            
        }
    }
    // representation: matrix2[i][j] == ith row, jth column
    int** matrix2 = new int*[nextPowerOfTwo]; // each element is a pointer to an array.
    for(size_t i = 0; i < nextPowerOfTwo; i++)
        matrix2[i] = new int[nextPowerOfTwo]; // build rows
    for(size_t i = 0; i < nextPowerOfTwo; i++)
    {
        for(size_t j = 0; j < nextPowerOfTwo; j++)
        {
            if (i < N && j < N) {
                string val;
                getline(matrices, val);
                matrix2[i][j] = stoi(val);
            }
            else {
                matrix2[i][j] = 0;
            }
        }
    }

    // print matrices
    print_matrix(matrix1, 1, nextPowerOfTwo);
    print_matrix(matrix2, 2, nextPowerOfTwo);
    int** product1 = standard(matrix1, matrix2, nextPowerOfTwo); // Commented out because the autograder does not do anything standard 
    int** product2 = strassen(matrix1, matrix2, nextPowerOfTwo, 1);
    print_matrix(product1, 3, nextPowerOfTwo);
    print_matrix(product2, 4, nextPowerOfTwo);

    // for (int i = 0; i < N; i++) {
    //     printf("%i\n",product2[i][i]);
    // }

    // delete matrices
    matrix_del(matrix1, N);
    matrix_del(matrix2, N);
    matrix_del(product1, N);
    matrix_del(product2, N);

    // part 3
    // print_matrix(graph_generator(4, 0.5), 10, 4);
    // int** test_graph = new int*[4];
    // for (int i = 0; i < 4; i++) {
    //     test_graph[i] = new int[4];
    // }
    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < 4; j++) {
    //         if (i ==j) {
    //             test_graph[i][j] = 3;
                
    //         } else {
    //             test_graph[i][j] == 0;
    //         }
    //     }
    // }
    // printf("%i", triangle_counter(4, test_graph));
    // float probabilities[] = {0.01, 0.02, 0.03, 0.04, 0.05};
    // vector<float> averages = triangle_tester(1024, 1, probabilities, 5);
    // for (auto i: averages)
    //     std::cout << i << ' ';
    return 0;
}