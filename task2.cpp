#include <iostream>
#import <ctime>
#import <cstdlib>
#include <utility>
#include <vector>
using namespace std;

void init_array(vector<vector<size_t>> &arr);
void print_array(const vector<vector<size_t>> &arr);
pair<long long,long long> linear_search(vector<vector<size_t>>&arr, size_t key);
pair<long long,long long> linear_search_barrier(const vector<vector<size_t>>&arr, size_t key);


int main() {
    srand(time(NULL));
    const size_t ROWS = 5;
    const size_t COLS = 5;
    vector<vector<size_t>> arr(ROWS,vector<size_t>(COLS));
    init_array(arr);
    size_t key = 6;
    print_array(arr);
    pair<long long,long long> res1 = linear_search(arr, key);
    cout << "pair: " << res1.first << " " << res1.second << endl;
    pair<long long,long long> res2 = linear_search_barrier(arr, key);
    cout << "pair: " << res2.first << " " << res2.second << endl;
    return 0;
}
void init_array(vector<vector<size_t>> &arr) {
    for(size_t i = 0; i < arr.size(); i++) {
        for (size_t j = 0; j < arr[0].size(); j++) {
            arr[i][j] = rand()%10000000;
        }
    }
}
void print_array(const vector<vector<size_t>> &arr) {
    for(size_t i = 0; i < arr.size(); i++) {
        for (size_t j = 0; j < arr[0].size(); j++) {
            cout << arr[i][j] << "\t";
        }
        cout << endl;
    }
}
pair<long long,long long> linear_search(vector<vector<size_t>>&arr, size_t key) {
    for (size_t i = 0; i < arr.size(); i++) {
        for (size_t j = 0; j < arr[0].size(); j++) {
            if (arr[i][j] == key) return {i,j};
        }
    }
    return {-1,-1};
}
pair<long long,long long> linear_search_barrier(const vector<vector<size_t>>&arr, size_t key) {
    vector<vector<size_t>> barrier = arr;
    size_t col = barrier[0].size();
    size_t row = barrier.size();
    for (size_t i = 0; i < row; i++) {
        barrier[i].push_back(key);
    }
    size_t i = 0;
    size_t j = 0;
    while (i < row) {
        while (barrier[i][j] != key) {
            j++;
        }
        if (j < col) {
            return {i, j};
        }
        j = 0;
        i++;
    }
    return {-1,-1};
}
