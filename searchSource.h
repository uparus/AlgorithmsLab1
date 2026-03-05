#ifndef SEARCHSOURCE_H
#define SEARCHSOURCE_H

#include<iostream>
#include <vector>
#include "statistic.h"
using namespace std;

long long searchLinear(const vector<long long>&arr, long long key,Statistic& stats);
long long searchBarrier(vector<long long>arr,long long key,Statistic& stats);
void printArray(const vector<long long>&arr);
void initVector(vector<long long>& arr);
long long binSearch(const vector<long long>&arr,long long key,Statistic& stats);
long long binSearchRecursive(const vector<long long>&arr, long long key, long long left, long long right,Statistic& stats);

#endif //SEARCHSOURCE_H
