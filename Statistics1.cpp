#include <iostream>
#include <omp.h>

using namespace std;

// Function to find the minimum value in an array using parallel reduction
int parallelMin(const int arr[], int size) {
    int min_val = arr[0];

    #pragma omp parallel for reduction(min:min_val)
    for (int i = 1; i < size; ++i) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }

    return min_val;
}

// Function to find the maximum value in an array using parallel reduction
int parallelMax(const int arr[], int size) {
    int max_val = arr[0];

    #pragma omp parallel for reduction(max:max_val)
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    return max_val;
}

// Function to find the sum of elements in an array using parallel reduction
int parallelSum(const int arr[], int size) {
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }

    return sum;
}

// Function to find the average of elements in an array using parallel reduction
double parallelAverage(const int arr[], int size) {
    int sum = parallelSum(arr, size);
    return static_cast<double>(sum) / size;
}

int main() {
    // Initialize an array of size 10
    int arr[10] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    // Find minimum value
    int min_val = parallelMin(arr, 10);
    cout << "Minimum value: " << min_val << endl;

    // Find maximum value
    int max_val = parallelMax(arr, 10);
    cout << "Maximum value: " << max_val << endl;

    // Find sum of elements
    int sum = parallelSum(arr, 10);
    cout << "Sum of elements: " << sum << endl;

    // Find average of elements
    double avg = parallelAverage(arr, 10);
    cout << "Average of elements: " << avg << endl;

    return 0;
}
