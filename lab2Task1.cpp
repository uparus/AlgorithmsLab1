#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <fstream>

using namespace std;
using namespace std::chrono;

int linearSearch(string s, string x, int& count);
int boyerMooreSearch(string s, string x, int& count);
int kmpSearch(string s, string x, int& count);
int rabinKarp(string s, string x, int& count);
string generateLongStringWithPattern(long long size, string pattern);
void runTestToCSV(ofstream& file, string s, string x);
void measureTimeToCSV(ofstream& file);

int main() {
    ofstream table1("comparisons.csv");
    table1 << "No;String;Pattern;Linear;Boyer-Moore;KMP;Rabin-Karp;Comments" << endl;

    runTestToCSV(table1, "ABCDE_FGHIJ_KLMNO", "ABCDE");
    runTestToCSV(table1, "!!!!!!!!!!!!!!!!!!?", "!!!!!?");
    runTestToCSV(table1, "A_B_C_D_E_F_G_H_I", "X_Y");
    runTestToCSV(table1, "ABCABCABCABCABCDE", "ABCABCDE");
    runTestToCSV(table1, "1010101010101011", "101011");
    runTestToCSV(table1, "QWERTYUIOPASDFGHJ", "ASDFG");
    runTestToCSV(table1, "STANCIA_DISTANCIA", "DISTANCIA");
    runTestToCSV(table1, "PYTHON_PY_PY_PY", "PYTHON");
    table1.close();

    ofstream table2("execution_time.csv");
    table2 << "Algorithm;Execution Time (sec)" << endl;
    measureTimeToCSV(table2);
    table2.close();

    cout << "Success! Files 'comparisons.csv' and 'execution_time.csv' created." << endl;

    return 0;
}

void runTestToCSV(ofstream& file, string s, string x) {
    int testNum = 1;
    int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
    
    linearSearch(s, x, c1);
    boyerMooreSearch(s, x, c2);
    kmpSearch(s, x, c3);
    rabinKarp(s, x, c4);

    file << testNum++ << ";" << s << ";" << x << ";" 
         << c1 << ";" << c2 << ";" << c3 << ";" << c4 << ";" << "-" << endl;
}
void measureTimeToCSV(ofstream& file) {
    const long n = 10000000;
    string pattern = "FoundMe123";
    const int iterations = 10;
    string text = generateLongStringWithPattern(n,pattern);

    double timeLinear = 0, timeBoyer = 0, timeKmp = 0, timeRK = 0;
    int count = 0;

    for (int i = 0; i < iterations; i++) {
        count = 0;
        auto start = high_resolution_clock::now();
        linearSearch(text, pattern, count);
        auto stop = high_resolution_clock::now();
        duration<double> diff = stop - start;
        timeLinear += diff.count();
    }
    file << "Linear Search;" << fixed << setprecision(6) << (timeLinear / iterations) << endl;

    for (int i = 0; i < iterations; i++) {
        count = 0;
        auto start = high_resolution_clock::now();
        boyerMooreSearch(text, pattern, count);
        auto stop = high_resolution_clock::now();
        duration<double> diff = stop - start;
        timeBoyer += diff.count();
    }
    file << "Boyer-Moore;" << fixed << setprecision(6) << (timeBoyer / iterations) << endl;

    for (int i = 0; i < iterations; i++) {
        count = 0;
        auto start = high_resolution_clock::now();
        kmpSearch(text, pattern, count);
        auto stop = high_resolution_clock::now();
        duration<double> diff = stop - start;
        timeKmp += diff.count();
    }
    file << "KMP Search;" << fixed << setprecision(6) << (timeKmp / iterations) << endl;

    for (int i = 0; i < iterations; i++) {
        count = 0;
        auto start = high_resolution_clock::now();
        rabinKarp(text, pattern, count);
        auto stop = high_resolution_clock::now();
        duration<double> diff = stop - start;
        timeRK += diff.count();
    }
    file << "Rabin-Karp;" << fixed << setprecision(6) << (timeRK / iterations) << endl;
}

int linearSearch(string s, string x, int& count) {
    int n = s.length(), m = x.length(), i = 0;
    while (i <= n - m) {
        int j = 0;
        while (j < m) {
            count++;
            if (s[i + j] != x[j]) break;
            j++;
        }
        if (j == m) return i;
        i++;
    }
    return -1;
}
int boyerMooreSearch(string s, string x, int& count) {
    int n = s.length(), m = x.length();
    vector<int> d(256, m);
    for (int i = 0; i <= m - 2; i++) d[(unsigned char)x[i]] = m - 1 - i;
    int i = 0;
    while (i <= n - m) {
        int j = m - 1;
        while (j >= 0) {
            count++;
            if (s[i + j] != x[j]) break;
            j--;
        }
        if (j < 0) return i;
        i += d[(unsigned char)s[i + m - 1]];
    }
    return -1;
}
int kmpSearch(string s, string x, int& count) {
    string st = x + '#' + s;
    int m = x.length(), totalLen = st.length();
    vector<int> d(totalLen, 0);
    int i = 0;
    while (i < totalLen - 1 && d[i] < m) {
        i++;
        int len = d[i - 1];
        while (len > 0) {
            count++;
            if (st[i] == st[len]) break;
            len = d[len - 1];
        }
        count++;
        if (st[i] == st[len]) d[i] = len + 1;
        else d[i] = 0;
    }
    if (d[i] == m) return (i - 2 * m);
    else return -1;
}
int rabinKarp(string s, string x, int& count) {
    int n = s.length(), m = x.length();
    int hx = 0, hs = 0;
    for (int i = 0; i < m; i++) {
        hx += (unsigned char)x[i];
        hs += (unsigned char)s[i];
    }
    for (int i = 0; i <= n - m; i++) {
        if (hs == hx) {
            int j = 0;
            while (j < m) {
                count++;
                if (s[i + j] != x[j]) break;
                j++;
            }
            if (j == m) return i;
        }
        if (i < n - m) hs = hs - (unsigned char)s[i] + (unsigned char)s[i + m];
    }
    return -1;
}

string generateLongStringWithPattern(long long size, string pattern) {
    string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string res = "";
    res.reserve(size);
    
    for (long i = 0; i < size - pattern.length(); ++i) {
        res += chars[rand() % chars.length()];
    }
    
    res += pattern; 
    return res;
}
