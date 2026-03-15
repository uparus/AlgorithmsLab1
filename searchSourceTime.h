#ifndef SEARCHSOURCETIME_H
#define SEARCHSOURCETIME_H

#include<iostream>
#include <vector>
using namespace std;

long long searchLinear(const vector<long long>&arr, long long key);
long long searchBarrier(const vector<long long>&arr,long long key);
long long binSearch(const vector<long long>&arr,long long key);
long long binSearchRecursive(const vector<long long>&arr, long long key, long long left, long long right);

#endif //SEARCHSOURCE_H
