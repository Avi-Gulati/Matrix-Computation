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
    // invariant: n is an even number or is 1
    // changed it so "n" is a function argument and doesn't need to be computedx
    if (n <= n0) { // replaced "==" with "<="
        return standard(A, B, n);
    }
    
    size_t ndiv_2 = n / 2;
    size_t padding = ndiv_2;
    if (ndiv_2 % 2 && ndiv_2 != 1) {
        padding += 1;
    }
    int** a = new int*[padding];            // Creating the different spliced arrays 
    int** b = new int*[padding];
    int** c = new int*[padding];
    int** d = new int*[padding];
    int** e = new int*[padding];
    int** f = new int*[padding];
    int** g = new int*[padding];
    int** h = new int*[padding];
    for (size_t i = 0; i < padding; i++) { // Dynamically allocate memory for array of integers with ndiv_2 elements 
        a[i] = new int[padding];          // for each spliced array
        b[i] = new int[padding];
        c[i] = new int[padding];
        d[i] = new int[padding];
        e[i] = new int[padding];
        f[i] = new int[padding];
        g[i] = new int[padding];
        h[i] = new int[padding];
    }
    for (size_t i = 0; i < padding; i++) {
        for (size_t j = 0; j < padding; j++) {
            if (i < ndiv_2 && j < ndiv_2) {
                a[i][j] = A[i][j];
                e[i][j] = B[i][j];
                b[i][j] = A[i][j+ndiv_2];
                f[i][j] = B[i][j+ndiv_2];
                c[i][j] = A[i+ndiv_2][j];
                g[i][j] = B[i+ndiv_2][j];
                d[i][j] = A[i+ndiv_2][j+ndiv_2];
                h[i][j] = B[i+ndiv_2][j+ndiv_2];
            }
            else {
                a[i][j] = 0;
                e[i][j] = 0;
                b[i][j] = 0;
                f[i][j] = 0;
                c[i][j] = 0;
                g[i][j] = 0;
                d[i][j] = 0;
                h[i][j] = 0;
            }
        }
    }

    int** temp1 = matrix_subtraction(f,h,padding);
    int** p1 = strassen(a, temp1, padding, n0);
    matrix_del(temp1, padding);
    int** temp2 = matrix_addition(a,b,padding);
    int** p2 = strassen(temp2, h, padding, n0);
    matrix_del(temp2, padding);
    int** temp3 = matrix_addition(c,d,padding);
    int** p3 = strassen(temp3, e, padding, n0);
    matrix_del(temp3, padding);
    int** temp4 = matrix_subtraction(g,e,padding);
    int** p4 = strassen(d, temp4, padding, n0);
    matrix_del(temp4, padding);
    int** temp5 = matrix_addition(a,d,padding);
    int** temp6 = matrix_addition(e,h,padding);
    int** p5 = strassen(temp5, temp6, padding, n0);
    matrix_del(temp5, padding);
    matrix_del(temp6, padding);
    int** temp7 = matrix_subtraction(b,d,padding);
    int** temp8 = matrix_addition(g,h,padding);
    int** p6 = strassen(temp7, temp8, padding, n0);
    matrix_del(temp7, padding);
    matrix_del(temp8, padding);
    int** temp9 = matrix_subtraction(c,a,padding);
    int** temp10 = matrix_addition(e,f,padding);
    int** p7 = strassen(temp9, temp10, padding, n0);
    matrix_del(temp9, padding);
    matrix_del(temp10, padding);

    matrix_del(a, padding);
    matrix_del(b, padding);
    matrix_del(c, padding);
    matrix_del(d, padding);
    matrix_del(e, padding);
    matrix_del(f, padding);
    matrix_del(g, padding);
    matrix_del(h, padding);
    
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
    matrix_del(p1, padding);
    matrix_del(p2, padding);
    matrix_del(p3, padding);
    matrix_del(p4, padding);
    matrix_del(p5, padding);
    matrix_del(p6, padding);
    matrix_del(p7, padding);
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
    int** result = strassen(graph, strassen(graph, graph, n, 32), n, 32);
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
            int** graph = graph_generator(n, probabilities[i]);
            average += triangle_counter(n, graph);
            matrix_del(graph, n);
        }
        output.push_back(average / k);
    }
    return output;
}

// ./mm 0 dimension inputfile
int main(int _argc, char *argv[]) {
    int mode = stoi(argv[1]);
    if (mode == 0) {
        const int N = stoi(argv[2]);
        size_t padding = N;
        if (N % 2) {
            padding += 1;
        }
        
        // initialize matrices (array of arrays)
        ifstream matrices(argv[3]);
        
        // representation: matrix1[i][j] == ith row, jth column
        int** matrix1 = new int*[padding]; // each element is a pointer to an array.
        for(size_t i = 0; i < padding; i++)
            matrix1[i] = new int[padding]; // build rows
        for(size_t i = 0; i < padding; i++)
        {
            for(size_t j = 0; j < padding; j++)
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
        int** matrix2 = new int*[padding]; // each element is a pointer to an array.
        for(size_t i = 0; i < padding; i++)
            matrix2[i] = new int[padding]; // build rows
        for(size_t i = 0; i < padding; i++)
        {
            for(size_t j = 0; j < padding; j++)
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
        // print_matrix(matrix1, 1, N);
        // print_matrix(matrix2, 2, N);
        // int** product1 = standard(matrix1, matrix2, padding); // Commented out because the autograder does not do anything standard
        // print_matrix(product1, 3, N);
        // int** product2 = strassen(matrix1, matrix2, padding, 1);
        // print_matrix(product2, 4, N);

        // for (int i = 0; i < N; i++) {
        //     printf("%i\n",product2[i][i]);
        // }

        int numberOfBaseCases = 46;
        float* time = new float[numberOfBaseCases];
        int crossover;

        for (int i = 0; i < numberOfBaseCases; i++) {
            crossover = 55 + i; 

            auto start = std::chrono::high_resolution_clock::now();
            int** product2 = strassen(matrix1, matrix2, padding, crossover);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

            time[i] = duration.count() * 1e-9;

        }

        float min = 100;
        int indexOfMin = 0;
        for (int i = 0; i < numberOfBaseCases; i++) {
            printf("%3f, ", time[i]);
            if (time[i] < min) {
                min = time[i];
                indexOfMin = i;
            }
        }
        printf("The minimum index is %d, corresponding to %3f", indexOfMin, time[indexOfMin]);

        // delete matrices
        matrix_del(matrix1, padding);
        matrix_del(matrix2, padding);
        // matrix_del(product1, padding);
        // matrix_del(product2, padding);
        return 0;
    } else {
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
        float probabilities[] = {0.01, 0.02, 0.03, 0.04, 0.05};
        vector<float> averages = triangle_tester(1024, 1, probabilities, 5);
        for (auto i: averages)
            std::cout << i << ' ';
        return 0;
    }
}