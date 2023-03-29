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
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = A[i][j] + B[i][j];
        }
    }
    return A;
}

int** matrix_subtraction(int** A, int** B, size_t n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A[i][j] = A[i][j] - B[i][j];
        }
    }
    return A;
}

int** strassen(int** A, int** B, int n, int n0) {

    // changed it so "n" is a function argument and doesn't need to be computedx
    if (n <= n0) { // replaced "==" with "<="
        return standard(A, B, n);
    }
    
    size_t ndiv_2 = n / 2;

    int** m1 = new int*[ndiv_2];
    int** m2 = new int*[ndiv_2];
    int** m3 = new int*[ndiv_2];
    for (size_t i = 0; i < ndiv_2; i++) {
        m1[i] = new int[ndiv_2];
        m2[i] = new int[ndiv_2];
        m3[i] = new int[ndiv_2];
    }

    // compute a and f 
    for (size_t i = 0; i < ndiv_2; i++) {   // The following for loops assign the spliced arrays to the 
        for (size_t j = 0; j < ndiv_2; j++) { // correct values 
            m3[i][j] = A[i][j];
        }
        for (size_t j = ndiv_2; j < n; j++) {
            m1[i][j-ndiv_2] = B[i][j];
        }
    }
    // compute h
    for (size_t i = ndiv_2; i < n; i++) {
        for (size_t j = ndiv_2; j < n; j++) {
            m2[i-ndiv_2][j-ndiv_2] = B[i][j];
        }
    }
    int** p1 = strassen(m3, matrix_subtraction(m1, m2, ndiv_2), ndiv_2, n0);

    // compute b
    for (size_t i = 0; i < ndiv_2; i++) {   // The following for loops assign the spliced arrays to the 
        for (size_t j = ndiv_2; j < n; j++) {
            m1[i][j-ndiv_2] = A[i][j];
        }
    }
    int** p2 = strassen(matrix_addition(m3, m1, ndiv_2), m2, ndiv_2, n0);

    // compute d and g
    for (size_t i = ndiv_2; i < n; i++) {
        for (size_t j = ndiv_2; j < n; j++) {
            m3[i-ndiv_2][j-ndiv_2] = A[i][j]; // m3 is now d
        }
    }
    m1 = matrix_subtraction(m1, m3, ndiv_2); // m1 is now (b-d)
    for (size_t i = ndiv_2; i < n; i++) {
        for (size_t j = 0; j < ndiv_2; j++) {
            m3[i-ndiv_2][j] = B[i][j];      // m3 is now g
        }
    }
    int** p6 = strassen(m1, matrix_addition(m3, m2, ndiv_2), ndiv_2, n0);

    // compute a, e, and d
    for (size_t i = 0; i < ndiv_2; i++) {   // The following for loops assign the spliced arrays to the 
        for (size_t j = 0; j < ndiv_2; j++) { // correct values 
            m3[i][j] = A[i][j];
            m1[i][j] = B[i][j];
        }
    }
    m2 = matrix_addition(m2, m1, ndiv_2);
    for (size_t i = ndiv_2; i < n; i++) {
        for (size_t j = ndiv_2; j < n; j++) {
            m1[i-ndiv_2][j-ndiv_2] = A[i][j];
        }
    }
    int** p5 = strassen(matrix_addition(m3, m1, ndiv_2), m2, ndiv_2, n0);

    // compute e and g
    for (size_t i = 0; i < ndiv_2; i++) {   // The following for loops assign the spliced arrays to the 
        for (size_t j = 0; j < ndiv_2; j++) { // correct values 
            m2[i][j] = B[i][j];
        }
    }
    for (size_t i = ndiv_2; i < n; i++) {
        for (size_t j = 0; j < ndiv_2; j++) {
            m3[i-ndiv_2][j] = B[i][j];
        }
    }
    int** p4 = strassen(m1, matrix_subtraction(m3, m2, ndiv_2), ndiv_2, n0);

    // compute c
    for (size_t i = ndiv_2; i < n; i++) {
        for (size_t j = 0; j < ndiv_2; j++) {
            m3[i-ndiv_2][j] = A[i][j];
        }
    }  
    int** p3 = strassen(matrix_addition(m1, m3, ndiv_2), m2, ndiv_2, n0); // looks good

    // compute a and f
    for (size_t i = 0; i < ndiv_2; i++) {   // The following for loops assign the spliced arrays to the 
        for (size_t j = 0; j < ndiv_2; j++) { // correct values 
            m1[i][j] = A[i][j];
        }
    }
    m3 = matrix_subtraction(m3, m1, ndiv_2);
    for (size_t i = 0; i < ndiv_2; i++) {
        
        for (size_t j = ndiv_2; j < n; j++) {
            m1[i][j-ndiv_2] = B[i][j]; 
        }
    }
    int** p7 = strassen(m3, matrix_addition(m1, m2, ndiv_2), ndiv_2, n0);


    int** C = new int*[n];
    for(size_t i = 0; i < n; i++)
        C[i] = new int[n];

    for (size_t i = 0; i < ndiv_2; i++) {   // The following for loops assign the spliced arrays to the 
        for (size_t j = 0; j < ndiv_2; j++) { // correct values 
            C[i][j] = p4[i][j] - p2[i][j] + p5[i][j] + p6[i][j];
        }
        for (size_t j = ndiv_2; j < n; j++) {
            C[i][j] = p1[i][j-ndiv_2] + p2[i][j-ndiv_2];
        }
    }
    for (size_t i = ndiv_2; i < n; i++) {
        for (size_t j = 0; j < ndiv_2; j++) {
            C[i][j] = p3[i-ndiv_2][j] + p4[i-ndiv_2][j];
        }
        for (size_t j = ndiv_2; j < n; j++) {
            C[i][j] = p1[i-ndiv_2][j-ndiv_2] - p3[i-ndiv_2][j-ndiv_2] + p5[i-ndiv_2][j-ndiv_2] + p7[i-ndiv_2][j-ndiv_2];
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
    int** test_graph = new int*[4];
    for (int i = 0; i < 4; i++) {
        test_graph[i] = new int[4];
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i ==j) {
                test_graph[i][j] = 3;
                
            } else {
                test_graph[i][j] == 0;
            }
        }
    }
    // printf("%i", triangle_counter(4, test_graph));
    float probabilities[] = {0.01, 0.02, 0.03, 0.04, 0.05};
    vector<float> averages = triangle_tester(1024, 1, probabilities, 5);
    for (auto i: averages)
        std::cout << i << ' ';
    return 0;
}