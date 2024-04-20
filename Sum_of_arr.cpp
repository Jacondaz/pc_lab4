#include <iostream>
#include <omp.h>
#include <ctime>

void printMaxThreads() {
    int max_threads = omp_get_max_threads();
    std::cout << "Max of threads: " << max_threads << std::endl;
}

int main() {
    const int size = 100000;
    int* arr = new int[size];

    srand(time(nullptr));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 100;
    }

    int sum = 0;
    double start_time = omp_get_wtime();

    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    double end_time = omp_get_wtime();
    std::cout << "Sum without OMP: " << sum << std::endl;
    std::cout << "Time taken: " << (end_time - start_time) << " seconds" << std::endl;

    sum = 0;
    start_time = omp_get_wtime();

#pragma omp parallel num_threads(4) for reduction(+:sum)
    for (int i = 0; i < size; i++) {
        sum += arr[i];
    }
    end_time = omp_get_wtime();
    std::cout << "Sum with OMP: " << sum << std::endl;
    std::cout << "Time taken: " << (end_time - start_time) << " seconds" << std::endl;

    delete[] arr;

    return 0;
}