#include "searchSource.h"
#include "statistic.h"
#include <iostream>
#include <vector>
#include <functional>
using namespace std;

long long searchLinear(const vector<long long>&arr, long long key,Statistic& stats) {
    for (long long i = 0; i < arr.size(); i++) {
        stats.totalComparisons++;
        stats.elementComparisons++;
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}
long long searchBarrier(vector<long long>arr, long long key,Statistic& stats) {
    arr.push_back(key);
    long long i = 0;

    stats.elementComparisons++;
    stats.totalComparisons++;

    while (arr[i] != key) {
        i++;
        stats.elementComparisons++;
        stats.totalComparisons++;
    }

    if (i == arr.size() - 1) return -1;

    return i;
}
void printArray(const vector<long long>& arr) {
    for (auto& element : arr) cout << element << " ";
}
void initVector(vector<long long>& arr) {
    for (long long i = 0; i < arr.size(); i++) {
        arr[i] = rand() % 1000000000 + 1;
    }
    sort(arr.begin(), arr.end());
}

long long binSearch(const vector<long long>&arr, long long key,Statistic& stats) {
    long long left = 0;
    long long right = arr.size() - 1;

    while (left <= right) {
        long long middle = (left+right)/2;

        stats.elementComparisons++;
        stats.totalComparisons++;

        if (arr[middle] == key) return middle;

        stats.totalComparisons++;
        stats.elementComparisons++;

        if (key < arr[middle]) {
            right = middle - 1;
        }else {
            left = middle + 1;
        }
    }
    return -1;
}
long long binSearchRecursive(const vector<long long>&arr, long long key, long long left, long long right,Statistic& stats) {
    stats.totalComparisons++;
    if ( left > right) return -1;

    long long middle = (right+ left) / 2;

    stats.elementComparisons++;
    stats.totalComparisons++;

    if (arr[middle] == key) return middle;

    stats.elementComparisons++;
    stats.totalComparisons++;

    if (key < arr[middle])
        return binSearchRecursive(arr, key, left, middle - 1,stats);
    else
        return binSearchRecursive(arr, key, middle + 1, right,stats);
}
