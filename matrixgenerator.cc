#include <iostream>
#include <fstream>
#include <string>
#include <random>
using namespace std;

// input ./matrixgenerator mode dimension
int main(int _argc, char *argv[]) {
    int mode1 = stoi(argv[1]);
    int mode2 = stoi(argv[2]);
    int dimension = stoi(argv[3]);
    ofstream outfile;
    outfile.open("matrices.txt");
    
    // random generator
    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distribution1;
    uniform_int_distribution<int> distribution2;
    if (mode1 == 0) {
        uniform_int_distribution<int> distr(0,1);
        distribution1 = distr;
    } if (mode1 == 1) {
        uniform_int_distribution<int> distr(0,2);
        distribution1 = distr;
    } if (mode1 == 2) {
        uniform_int_distribution<int> distr(-1,1);
        distribution1 = distr;
    } if (mode2 == 0) {
        uniform_int_distribution<int> distr(0,1);
        distribution2 = distr;
    } if (mode2 == 1) {
        uniform_int_distribution<int> distr(0,2);
        distribution2 = distr;
    } if (mode2 == 2) {
        uniform_int_distribution<int> distr(-1,1);
        distribution2 = distr;
    }

    // write to file to generate matrix1
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            outfile << to_string(distribution1(generator));
            outfile << "\n";
        }
    }
    // write to file to generate matrix2
    for (int i = 0; i < dimension; i++) {
        for (int j = 0; j < dimension; j++) {
            outfile << to_string(distribution2(generator));
            outfile << "\n";
        }
    }
    outfile.close();
    return 0;
}