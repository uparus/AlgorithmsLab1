#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <iomanip>
#include <algorithm>
using namespace std;
using namespace std::chrono;

int linearSearch(string s,string x,int& count);
int boyerMooreSearch(string s, string x,int& count);
int kmpSearch(string s, string x,int& count);
int rabinKarp(string s, string x,int& count);
void runTest(string s, string x);
string generateLongString(long long size);
void measureTime() ;

int main() {
    cout << "Linear\tBoyer\tKmp\tRabinKarp\n ";
    runTest("ABCDE_FGHIJ_KLMNO", "ABCDE");
    runTest("!!!!!!!!!!!!!!!!!!?", "!!!!!?");
    runTest("A_B_C_D_E_F_G_H_I", "X_Y");
    runTest("ABCABCABCABCABCDE", "ABCABCDE");
    runTest("1010101010101011", "101011");
    runTest("QWERTYUIOPASDFGHJ", "ASDFG");
    runTest("STANCIA_DISTANCIA", "DISTANCIA");
    runTest("PYTHON_PY_PY_PY", "PYTHON");
    measureTime();

    return 0;
}

int linearSearch(string s,string x,int& count) {
    int n = s.length();
    int m = x.length();
    int i = 0;
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
int boyerMooreSearch(string s, string x,int& count) {
    int n = s.length();
    int m = x.length();
    vector<int> d(256,m);
    for (int i = 0;i <= m-2;i++) {
        d[(unsigned char)x[i]] = m - 1 - i;
    }

    int i = 0;
    while (i <= n-m) {
        int j = m - 1;
        while (j >= 0) {
            count++;
            if (s[i + j] != x[j]) break;
            j--;
        }
        if (j < 0) {
            return i;
        }
        i += d[(unsigned char)s[i + m - 1]];
    }
    return -1;
}
int kmpSearch(string s, string x,int& count) {
    int n = s.length();
    int m = x.length();

    string st = x + '#' + s;
    int totalLen = st.length();

    vector<int> d(totalLen,0);

    int i = 0;
    while (i < totalLen - 1 && d[i] < m) {
        i++;
        int len = d[i-1];
        while (len > 0) {
            count++;
            if (st[i] == st[len]) break;
            len = d[len - 1];
        }
        count++;
        if (st[i] == st[len]) {
            d[i] = len + 1;
        }else {
            d[i] = 0;
        }
    }
    if (d[i] == m) {
        return (i - 2 * m);
    }else return -1;
}
int rabinKarp(string s, string x,int& count) {
    int n = s.length();
    int m = x.length();

    int hx = 0;
    int hs = 0;
    for (int i = 0; i < m; i++) {
        hx += (unsigned char)x[i];
        hs += (unsigned char)s[i];
    }

    for (int i = 0;i <= n-m;i++) {
        if (hs == hx) {
            int j = 0;
            while (j < m) {
                count++;
                if (s[i + j] != x[j]) break;
                j++;
            }
            if (j == m) return i;
        }

        if (i < n - m) {
            hs = hs - (unsigned char)s[i] + (unsigned char)s[i + m];
        }
    }
    return -1;
}
void runTest(string s, string x) {
    int count1 = 0, count2 = 0, count3 = 0, count4 = 0;
    linearSearch(s, x, count1);
    boyerMooreSearch(s, x, count2);
    kmpSearch(s, x, count3);
    rabinKarp(s, x, count4);

    cout << count1 << "\t" << count2 << "\t" << count3 << "\t" << count4 << endl;
}
string generateLongString(long long size) {
    string chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    string res = "";
    res.reserve(size);
    for (long i = 0; i < size; ++i) res += chars[rand() % chars.length()];
    return res;
}
void measureTime() {
    const long n = 100000000;
    string text = generateLongString(n);
    string pattern = "FoundMe123";

    const int iterations = 10;

    auto run_test = [&](string name, int (*func)(const string, const string,int&)) {
        double total_time = 0;

        for (int i = 0; i < iterations; i++) {
            int zeroCount = 0;

            auto start = high_resolution_clock::now();
            func(text, pattern,zeroCount);
            auto stop = high_resolution_clock::now();
            duration<double> diff = stop - start;
            total_time += diff.count();
        }

        cout << fixed << setprecision(6) << (total_time / iterations) << " sec" << endl;
    };

    cout << "\n--- AVERAGE RESULTS (10 runs) ---" << endl;
    run_test("Linear Search    ", linearSearch);
    run_test("Boyer-Moore      ", boyerMooreSearch);
    run_test("KMP Search       ", kmpSearch);
    run_test("Rabin-Karp       ", rabinKarp);
}