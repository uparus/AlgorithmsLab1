#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <functional>
#include "search.h"
#include "searchSource.h"
#include "statistic.h"
#include "searchSourceTime.h"
using namespace std;
using namespace chrono;

double measureTime(function<long long()> func);

int main() {
    ofstream fout("result.txt");
    srand(time(NULL));

    const long long SIZE = 10000000;
    vector<long long>arr(SIZE);
    initVector(arr);

    vector<long long> keys = {
        arr[0],
        arr[SIZE-1],
        arr[SIZE/2],
        -1
    };

    Statistic stats;

    for (long long key : keys) {
        fout << "\nkey: " << key << endl;

        stats.reset();
        long long linearIndex = searchLinear(arr, key, stats);
        long long linearIndexTime = searchLinear(arr, key);
        double linearTime = measureTime([&]() {
            return searchLinear(arr, key);
        });
        fout << "Linear\n";
        fout << "Total: " << stats.totalComparisons << " "
             << "Element: " << stats.elementComparisons << " "
             << "Time: " << linearTime << "\n";

        stats.reset();
        long long barrierIndex = searchBarrier(arr, key, stats);
        long long barrierIndexTime = searchBarrier(arr, key);
        double barrierTime = measureTime([&]() {
            return searchBarrier(arr, key);
        });
        fout << "Barrier\n";
        fout << "Total: " << stats.totalComparisons << " "
             << "Element: " << stats.elementComparisons << " "
             << "Time: " << barrierTime << "\n";

        stats.reset();
        long long binaryIndex = binSearch(arr, key, stats);
        long long binaryIndexTime = binSearch(arr, key);
        double binaryTime = measureTime([&]() {
            return binSearch(arr, key);
        });
        fout << "Binary\n";
        fout << "Total: " << stats.totalComparisons << " "
             << "Element: " << stats.elementComparisons << " "
             << "Time: " << binaryTime << "\n";

        stats.reset();
        long long recIndex = binSearchRecursive(arr, key, 0, SIZE - 1, stats);
        long long recIndexTime = binSearchRecursive(arr, key, 0, SIZE - 1);
        double recTime = measureTime([&]() {
            return binSearchRecursive(arr, key, 0, SIZE - 1);
        });
        fout << "Binary Recursive\n";
        fout << "Total: " << stats.totalComparisons << " "
             << "Element: " << stats.elementComparisons << " "
             << "Time: " << recTime << "\n";
    }

    fout.close();
    return 0;
}

double measureTime(function<long long()> func)
    {
    double total = 0;

    for (int i = 0; i < 10; i++) {
        auto start = high_resolution_clock::now();
        func();
        auto end = high_resolution_clock::now();

        total += duration<double>(end - start).count();
    }
    int avg = total / 10;
    return avg;
}