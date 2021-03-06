#include <iostream>
#include <fstream>
//#include <algorithm>
#include <cmath>
#include <chrono>

void sort(long long size);

void random(long long size);

int main() {
    long long size = pow(2, 20);
    random(size);
    auto start = std::chrono::steady_clock::now();
    sort(size);
    auto end = std::chrono::steady_clock::now();
    auto elapsed = duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Elapsed " << elapsed.count() << "ms" << std::endl;
    return 0;
}

void permutation(long long step) {
    std::ofstream a, b;
    std::ifstream f;
    f.open("f.txt");
    a.open("a.txt");
    b.open("b.txt");
    long long counter = 0;
    long long cur = 0;
    bool a_bin = true;
    while (f >> cur) {
        if (a_bin)
            a << ' ' << cur;
        else
            b << ' ' << cur;

        if (++counter == step) {
            counter = 0;
            a_bin = !a_bin;
        }
    }
    f.close();
    a.close();
    b.close();
}

void merge(long long step, long long size) {
    std::ifstream a, b;
    std::ofstream f;
    f.open("f.txt");
    a.open("a.txt");
    b.open("b.txt");
    long long a_pos = 0, b_pos = 0, counter = 0;
    int a_cur = 0, b_cur = 0;
    a >> a_cur;
    b >> b_cur;
    while (counter < size) {
        if (a_cur < b_cur) {
            f << ' ' << a_cur;
            a >> a_cur;
            ++a_pos;
            ++counter;
        } else {
            f << ' ' << b_cur;
            b >> b_cur;
            ++b_pos;
            ++counter;
        }
        if (a_pos == step) {
            while (b_pos != step) {
                f << ' ' << b_cur;
                b >> b_cur;
                ++b_pos;
                ++counter;
            }
            a_pos = 0;
            b_pos = 0;
        } else if (b_pos == step) {
            while (a_pos != step) {
                f << ' ' << a_cur;
                a >> a_cur;
                ++a_pos;
                ++counter;
            }
            a_pos = 0;
            b_pos = 0;
        }
    }
    f.close();
    a.close();
    b.close();
}

void sort(long long size) {
    for (long long i = 1; i <= size / 2; i *= 2) {
        permutation(i);
        merge(i, size);
    }
}

void random(long long size) {
    std::ofstream f, f_s;
    f.open("f.txt");
    f_s.open("f_start.txt");
    for (long long i = 0; i < size; ++i) {
        int num = rand();
        f << ' ' << num;
        f_s << ' ' << num;
    }
    f.close();
}
