
#include <iostream>
#include <vector>
#include <chrono>

using namespace std;

template <typename S> // 'S' stands for Sorting
void swap(vector<S>& arr, int i, int j) {
    S temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// Bubble Sort (Iterative)
template <typename S>
void bubblesort(vector<S>& arr) {
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr, j, j + 1);
                swapped = true;
            }
        }
        if (!swapped) {
            break; 
        }
    }
}

// Quick Sort (Recursive)
template <typename S>
int partition(vector<S>& arr, int low, int high) {
    S pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i + 1, high);
    return i + 1;
}

template <typename S>
void quicksort(vector<S>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quicksort(arr, low, pi - 1);
        quicksort(arr, pi + 1, high);
    }
}

// Merge Sort (Recursive)
template <typename S>
void merge(vector<S>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<S> leftArr(n1);
    vector<S> rightArr(n2);

    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int i = 0; i < n2; i++)
        rightArr[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (leftArr[i] <= rightArr[j]) {
            arr[k] = leftArr[i];
            i++;
        }
        else {
            arr[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = rightArr[j];
        j++;
        k++;
    }
}

template <typename S>
void mergesort(vector<S>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergesort(arr, left, mid);
        mergesort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

int main() {

    vector<int> arr = { };
    for (int i = 0; i < 10000; i++)
    {
        arr.push_back(rand() % 1000);
    }
    vector<int> arr2 = arr;
    vector<int> arr3 = arr; 

    // Measure time for Bubble Sort
    auto start_time = chrono::high_resolution_clock::now();
    bubblesort(arr);
    auto stop_time = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop_time - start_time).count();
    cout << "Bubble Sort took: " << duration << " milliseconds." << endl;

    // Measure time for Quick Sort
    start_time = chrono::high_resolution_clock::now();
    quicksort(arr2, 0, arr2.size() - 1);
    stop_time = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop_time - start_time).count();
    cout << "Quicksort took: " << duration << " milliseconds." << endl;

    // Measure time for Merge Sort
    start_time = chrono::high_resolution_clock::now();
    mergesort(arr3, 0, arr3.size() - 1);
    stop_time = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop_time - start_time).count();
    cout << "Merge Sort took: " << duration << " milliseconds." << endl;

    return 0;
}
