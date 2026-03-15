#include "searchSourceTime.h"
#include <iostream>
#include <vector>
using namespace std;

long long searchLinear(const vector<long long>&arr, long long key) {
    for (long long i = 0; i < arr.size(); i++) {
        if (arr[i] == key) {
            return i;
        }
    }
    return -1;
}
long long searchBarrier(const vector<long long>&arr, long long key ){
    vector<long long> barrier = arr;
    barrier.push_back(key);
    long long i = 0;

    while (barrier[i] != key) i++;
    if (i == barrier.size() - 1) return -1;

    return i;
}
long long binSearch(const vector<long long>&arr, long long key) {
    long long left = 0;
    long long right = arr.size() - 1;

    while (left <= right) {
        long long middle = (left+right)/2;

        if (arr[middle] == key) return middle;

        if (key < arr[middle]) {
            right = middle - 1;
        }else {
            left = middle + 1;
        }
    }
    return -1;
}
long long binSearchRecursive(const vector<long long>&arr, long long key, long long left, long long right) {
    if ( left > right) return -1;

    long long middle = (right+ left) / 2;

    if (arr[middle] == key) return middle;

    if (key < arr[middle])
        return binSearchRecursive(arr, key, left, middle - 1);
    else
        return binSearchRecursive(arr, key, middle + 1, right);
}
