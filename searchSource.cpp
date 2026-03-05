#include "searchSource.h"
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
            matrix[i][j] = rand() % 100;
        }
    }
}

pair<int, int> linearSearch(vector<vector<int>>& matrix, int key) {
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] == key) {
                return {i,j};
            }
        }
    }
    return {-1,-1};

}
pair<int, int> linearSearchBarrier(vector<vector<int>>& matrix, int key) {
    int rows = matrix.size();
    vector<int>newRow(matrix[0].size(), key);
    matrix.push_back(newRow);
    cout << endl;
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    int i = 0;
    int j = 0;
    while (matrix[i][j] != key) {
        while (i != matrix.size() && matrix[i][j] != key) j++;
        i++;
    }
    matrix.erase(matrix.begin() + rows);

    if (i != rows) {
        return { i,j };
    }
    else {
        return { -1,-1 };
    }
}
