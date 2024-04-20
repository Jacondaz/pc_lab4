#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;

void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1; 
    int n2 = r - m; 

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; ++i)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0;

    int k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            ++i;
        }
        else {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        arr[k] = R[j];
        ++j;
        ++k;
    }
}

void mergeSort(vector<int>& arr, int l, int r) {
    if (l >= r)
        return;

    int m = l + (r - l) / 2;

#pragma omp parallel sections
    {
#pragma omp section
        mergeSort(arr, l, m);
#pragma omp section
        mergeSort(arr, m + 1, r);
    }

    merge(arr, l, m, r);
}

int main() {

    const int size = 10000;
    std::vector<int> arr(size);

    srand(time(nullptr));
    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000;
    }

    cout << "Unsorted numbers: ";
    for (int x : arr)
        cout << x << " ";
    cout << endl;
    

    double start_time = omp_get_wtime();
    mergeSort(arr, 0, arr.size() - 1);
    double end_time = omp_get_wtime();

    std::cout << "Size of array: " << size << std::endl;
    std::cout << "Time without OMP: " << (end_time - start_time) << " seconds" << std::endl;

    cout << "Sorted numbers: ";
    for (int x : arr)
        cout << x << " ";
    cout << endl;
  

    return 0;
}