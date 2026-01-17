#pragma once

void insertionSort(int arr[], int const n)
{
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void merge(int array[], int const left, int const mid, int const right)
{
    int const a1 = mid - left + 1, a2 = right - mid;
    auto *leftArray = new int[a1], *rightArray = new int[a2];
 
    for (auto i = 0; i < a1; i++) leftArray[i] = array[left + i];
    for (auto j = 0; j < a2; j++) rightArray[j] = array[mid + 1 + j];
 
    int a1i = 0, a2i = 0, merged = left;
    while (a1i < a1 && a2i < a2) {
        if (leftArray[a1i] <= rightArray[a2i]) {
            array[merged] = leftArray[a1i];
            a1i++;
        }
        else {
            array[merged] = rightArray[a2i];
            a2i++;
        }
        merged++;
    }
 
    while (a1i < a1) {
        array[merged] = leftArray[a1i];
        a1i++;
        merged++;
    }
 
    while (a2i < a2) {
        array[merged] = rightArray[a2i];
        a2i++;
        merged++;
    }

    delete[] leftArray;
    delete[] rightArray;
}

void mergeSort(int array[], int const begin, int const end)
{
    if (begin >= end) return;
    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid);
    mergeSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

void merge_insertionSort(int array[], int const begin, int const end)
{
    int const size = end - begin;
    if (size < 256) 
    {
        insertionSort(array, size);
        return;
    }
    if (begin >= end) return;
    int const mid = begin + (end - begin) / 2;
    merge_insertionSort(array, begin, mid);
    merge_insertionSort(array, mid + 1, end);
    merge(array, begin, mid, end);
}