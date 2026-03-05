#include <iostream>
#include <ctime>
#include <vector>
#include <algorithm>
#include <fstream>
#include <chrono>
#include <functional>
#include "search.h"
#include "searchSource.h"
using namespace std;
using namespace chrono;

double measureTime(function<long long()> func);

int main() {
    ofstream fout("result.txt");
    srand(time(NULL));

    int SIZE = 6;
    vector<vector<int>>matrix(5,vector<int>(SIZE,0));

    initVector(matrix);
    cout << "Matrix:\n";
    printArray(matrix);

    int key = rand()%100;
    cout << "key: " << key << endl;

    int resSize;
    int* result = linearSearch(matrix, key,resSize);
    cout << "\nLinear search\n";
    cout << "First index encounter: " << result[0] << " " << result[1];

    pair<int,int> resultBarrier = linearSearchBarrier(matrix, key);
    cout << "\nLinear barrier search\n";
    cout << "First index encounter: " << resultBarrier.first << " " << resultBarrier.second << endl;

    return 0;
}
