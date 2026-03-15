#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iomanip>
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

    fout << fixed << setprecision(6);
    vector<vector<double>>result(4, vector<double>(12,0));
    int i = 0;
    for (long long key : keys) {
        int j = 0;
        stats.reset();
        long long linearIndex = searchLinear(arr, key, stats);
        double linearTime = measureTime([&]() {
            return searchLinear(arr, key);
        });
        result[i][j++] = stats.totalComparisons;
        result[i][j++] = stats.elementComparisons;
        result[i][j++] = linearTime;

        stats.reset();
        long long barrierIndex = searchBarrier(arr, key, stats);
        double barrierTime = measureTime([&]() {
            return searchBarrier(arr, key);
        });
        result[i][j++] = stats.totalComparisons;
        result[i][j++] = stats.elementComparisons;
        result[i][j++] = barrierTime;

        stats.reset();
        long long binaryIndex = binSearch(arr, key, stats);
        double binaryTime = measureTime([&]() {
            return binSearch(arr, key);
        });
        result[i][j++] = stats.totalComparisons;
        result[i][j++] = stats.elementComparisons;
        result[i][j++] = binaryTime;

        stats.reset();
        long long recIndex = binSearchRecursive(arr, key, 0, SIZE - 1, stats);
        double recTime = measureTime([&]() {
            return binSearchRecursive(arr, key, 0, SIZE - 1);
        });
        result[i][j++] = stats.totalComparisons;
        result[i][j++] = stats.elementComparisons;
        result[i][j] = recTime;
        i++;
    }
    for (int i = 0; i < result.size(); i++) {
        for (int j = 0; j < result[0].size(); j++) {
            fout << result[i][j] << "\t";
        }
        fout << endl;
    }
    fout.close();
    std::cout << "\nDone";
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
    return total / 10.0;
}
