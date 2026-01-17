#include <iostream>
#include "Sorting.h"
#include "Timer.h"
#include "Random.h"
using namespace std;
int i;
Timer testTime;

void RsortedTest(const int n)
{
    int arr[n];
    for (i = 0; i < n; i++) arr[i] = n - i;
    testTime.reset();
    mergeSort(arr, 0, n - 1);
    cout << "| " << testTime.elapsed() << " | ";
}

void sortedTest(const int n)
{
    int arr[n];
    for (i = 0; i < n; i++) arr[i] = i + 1;
    testTime.reset();
    mergeSort(arr, 0, n - 1);
    cout << "| " << testTime.elapsed() << " | ";
}

void RpermutationTest (const int n)
{

    int arr[n];
    for (i = 0; i < n; i++) arr[i] = i + 1;
    for (i = 0; i < n; i++) swap(arr[i], arr[Random::get(0, n - 1)]);
    testTime.reset();
    mergeSort(arr, 0, n - 1);
    cout << "| " << testTime.elapsed() << " | ";
}

void randomTest(const int n)
{
    int arr[n], runs;
    double avgTime = 0;
    for (runs = 0; runs < 50; runs++)
    {
        for (i = 0; i < n; i++) arr[i] = Random::get(1,n);
        testTime.reset();
        mergeSort(arr, 0, n - 1);
        avgTime += testTime.elapsed();
    }
    avgTime /= 50;
    cout << "| " << testTime.elapsed() << " |\n";
}

int main()
{
    int n = 500;
    cout << "| Sorted | Rsorted | Rpermutation | Random |\n";
    cout << "n:" << n << '\n';
    sortedTest(n);
    RsortedTest(n);
    RpermutationTest(n);
    randomTest(n);

    n = 1000;
    cout << "n:" << n << '\n';
    sortedTest(n);
    RsortedTest(n);
    RpermutationTest(n);
    randomTest(n);

    n = 5000;
    cout << "n:" << n << '\n';
    sortedTest(n);
    RsortedTest(n);
    RpermutationTest(n);
    randomTest(n);

    n = 10000;
    cout << "n:" << n << '\n';
    sortedTest(n);
    RsortedTest(n);
    RpermutationTest(n);
    randomTest(n);
    
    n = 50000;
    cout << "n:" << n << '\n';
    sortedTest(n);
    RsortedTest(n);
    RpermutationTest(n);
    randomTest(n);

    return 0;
}