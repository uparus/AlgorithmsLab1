#include "searchSource.h"
#include "statistic.h"
#include <iostream>
#include <vector>
#include <functional>
using namespace std;


void printArray(const vector<vector<int>>& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}
void initVector(vector<vector<int>>& matrix) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            matrix[i][j] = rand()%100;
        }
    }
}

int* linearSearch(vector<vector<int>>& matrix, int key, int& size) {
    size = 2;
    int* result = new int[size]{-1,-1};
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == key) {
                result[0] = i;
                result[1] = j;
                return result;
            }
        }
    }
    return result;

}
pair<int,int> linearSearchBarrier(vector<vector<int>>& matrix, int key) {
    int row = matrix.size();
    int col = matrix[0].size();
    int size = row * col;

    int lastRow = (size - 1) / col;
    int lastCol = (size - 1) % col;

    int last = matrix[lastRow][lastCol];
    matrix[lastRow][lastCol] = key;

    int i = 0;
    while (matrix[i / col][i % col] != key)
        i++;

    matrix[lastRow][lastCol] = last;

    if (i < size - 1 || last == key)
        return {i / col, i % col};

    return {-1, -1};
}
