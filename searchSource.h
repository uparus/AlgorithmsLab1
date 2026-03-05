#ifndef SEARCHSOURCE_H
#define SEARCHSOURCE_H
#include<iostream>
#include <vector>
using namespace std;

void printArray(const vector<vector<int>>& matrix);
void initVector(vector<vector<int>>& matrix);
pair<int, int> linearSearch(vector<vector<int>>& matrix, int key);
pair<int, int> linearSearchBarrier(vector<vector<int>>& matrix, int key);

#endif //SEARCHSOURCE_H
