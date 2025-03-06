#include <algorithm>
#include <iostream>
#include <mutex>
#include <vector>

class Sorting {
public:
    // Перегрузка для int
    static void insertionSort(int* arr, int count);
    static void bubbleSort(int* arr, int count);
    static void heapSort(int* arr, int count);

    // Шаблонные перегрузки для других типов
    template <class T>
    static void insertionSort(T* arr, int count);
    
    template <class T>
    static void bubbleSort(T* arr, int count);
    
    template <class T>
    static void heapSort(T* arr, int count);

private:
    // Определяем heapify для int
    static void heapify(int* arr, int n, int i);
    // Определяем heapify для шаблонов
    template <class T>
    static void heapify(T* arr, int n, int i);
    
    static std::recursive_mutex mtx;
};

std::recursive_mutex Sorting::mtx;

void Sorting::insertionSort(int* arr, int count) {
    if (count <= 0) return; // Обработка пустого массива
    std::lock_guard<std::recursive_mutex> locker(mtx);

    for (int i = 1; i < count; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void Sorting::bubbleSort(int* arr, int count) {
    if (count <= 0) return; // Обработка пустого массива
    std::lock_guard<std::recursive_mutex> locker(mtx);

    for (int i = 0; i < count; i++) {
        bool is_swap = false;
        for (int j = 0; j < count - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                is_swap = true;
            }
        }
        if (!is_swap) break;
    }
}

void Sorting::heapify(int* arr, int n, int i) {
    std::lock_guard<std::recursive_mutex> locker(mtx);
    int largest = i; 
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void Sorting::heapSort(int* arr, int count) {
    if (count <= 0) return; // Обработка пустого массива
    std::lock_guard<std::recursive_mutex> locker(mtx);

    for (int i = count / 2 - 1; i >= 0; i--)
        heapify(arr, count, i);
    
    for (int i = count - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// Шаблонные методы для различных типов
template <class T>
void Sorting::insertionSort(T* arr, int count) {
    if (count <= 0) return; // Обработка пустого массива
    std::lock_guard<std::recursive_mutex> locker(mtx);

    for (int i = 1; i < count; i++) {
        T key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

template <class T>
void Sorting::bubbleSort(T* arr, int count) {
    if (count <= 0) return; // Обработка пустого массива
    std::lock_guard<std::recursive_mutex> locker(mtx);

    for (int i = 0; i < count; i++) {
        bool is_swap = false;
        for (int j = 0; j < count - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                is_swap = true;
            }
        }
        if (!is_swap) break;
    }
}

template <class T>
void Sorting::heapify(T* arr, int n, int i) {
    std::lock_guard<std::recursive_mutex> locker(mtx);
    int largest = i; 
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        std::swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

template <class T>
void Sorting::heapSort(T* arr, int count) {
    if (count <= 0) return; // Обработка пустого массива
    std::lock_guard<std::recursive_mutex> locker(mtx);

    for (int i = count / 2 - 1; i >= 0; i--)
        heapify(arr, count, i);
    
    for (int i = count - 1; i > 0; i--) {
        std::swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}