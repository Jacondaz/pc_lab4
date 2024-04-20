#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <omp.h>

using namespace std;

int main() {
    srand(time(0));

    int num_points = 1000000;
    int num_inside_circle = 0; 

    auto start_time = chrono::high_resolution_clock::now();

#pragma omp parallel num_threads(2) reduction(+:num_inside_circle)
    {
#pragma omp for
        for (int i = 0; i < num_points; ++i) {
            double x = (double)rand() / RAND_MAX;
            double y = (double)rand() / RAND_MAX;

            double distance_squared = x * x + y * y;
            if (distance_squared <= 1) {
                num_inside_circle++;
            }
        }
    }

    auto end_time = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed_time = end_time - start_time;

    double pi = 4.0 * num_inside_circle / num_points;

    cout << "Pi equal: " << pi << endl;
    cout << "Time taken: " << elapsed_time.count() << " seconds" << endl;

    return 0;
}