#include <iostream>
#include <vector>
#include <omp.h>
#include <chrono>

using namespace std;

void parallelBubbleSort(vector<int>& arr) {
    int n = arr.size();
    bool swapped = true;

    while (swapped) {
        swapped = false;
        #pragma omp parallel for shared(arr, swapped)
        for (int i = 0; i < n - 1; i++) {
            if (arr[i] > arr[i + 1]) 
            {
                // Use a critical section to serialize access to the swapped variable
                #pragma omp critical
                {
                    swap(arr[i], arr[i + 1]);
                    swapped = true;
                }
            }
        }
    }
}

void merge(vector<int>& arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void parallelMergeSort(vector<int>& arr, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        #pragma omp parallel sections
        {
            #pragma omp section
            parallelMergeSort(arr, l, m);
            #pragma omp section
            parallelMergeSort(arr, m + 1, r);
        }
        merge(arr, l, m, r);
    }
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    
    vector<int> arr_merge = arr; // Make a copy of the original array for merge sort

    // Parallel bubble sort
    double start = omp_get_wtime();
    parallelBubbleSort(arr);
    double stop = omp_get_wtime();
    for (int i = 0; i < n; i++)
    {
        cout <<arr[i]<<"\t";     
    }
    cout << "\nTime taken for parallel bubble sort: " << stop-start << " milliseconds" << endl;
    
    // Parallel merge sort
    start = omp_get_wtime();
    parallelMergeSort(arr_merge, 0, n-1);
    stop = omp_get_wtime();
    for (int i = 0; i < n; i++)
    {
        cout <<arr_merge[i]<<"\t";     
    }
    cout << "\nTime taken for parallel merge sort: " << stop-start << " milliseconds" << endl;
    
    return 0;
}

//g++ -fopenmp program_name.cpp -o binary_name.out
