#include "skip_list.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <list>
#include <algorithm>
#include <cassert>
#include <iomanip>

using namespace std;

int main() {
    srand(280);

    const int baseSize = 100000;
    const int testSize = 1000;
    const int numBatches = 10;
    const int batchSize = baseSize / numBatches;
    clock_t begin, end;
    double elapsedTime[numBatches][3][3];

    list<int> myList;
    vector<int> myVector;
    SkipList<int> mySkipList;

    int base[baseSize];
    for (int &num : base) {
        num = rand();
    }
    int test[testSize];
    for (int &num : test) {
        num = rand();
    }

    for (int batch = 0; batch < numBatches; batch++) {
        for (int i = batchSize * batch; i < batchSize * (batch + 1); i++) {
            list<int>::const_iterator it;
            for (it = myList.begin(); it != myList.end(); it++) {
                if (*it >= base[i]) {
                    break;
                }
            }
            myList.insert(it, base[i]);
        }
        for (int i = batchSize * batch; i < batchSize * (batch + 1); i++) {
            myVector.insert(lower_bound(myVector.begin(), myVector.end(), base[i]), base[i]);
        }
        for (int i = batchSize * batch; i < batchSize * (batch + 1); i++) {
            mySkipList.insert(base[i]);
        }
        cout << "- base size " << batchSize * (batch + 1) << endl;


        cout << "  - insert " << testSize << " elements" << endl;
        begin = clock();
        for (int num : test) {
            list<int>::const_iterator it;
            for (it = myList.begin(); it != myList.end(); it++) {
                if (*it >= num) {
                    break;
                }
            }
            myList.insert(it, num);
        }
        end = clock();
        elapsedTime[batch][0][0] = double(end - begin) / CLOCKS_PER_SEC;
        cout << "    - list: " << elapsedTime[batch][0][0] << endl;

        begin = clock();
        for (int num : test) {
            myVector.insert(lower_bound(myVector.begin(), myVector.end(), num), num);
        }
        end = clock();
        elapsedTime[batch][0][1] = double(end - begin) / CLOCKS_PER_SEC;
        cout << "    - vector: " << elapsedTime[batch][0][1] << endl;

        begin = clock();
        for (int num : test) {
            mySkipList.insert(num);
        }
        end = clock();
        elapsedTime[batch][0][2] = double(end - begin) / CLOCKS_PER_SEC;
        cout << "    - SkipList: " << elapsedTime[batch][0][2] << endl;


        cout << "  - search " << testSize << " elements" << endl;
        begin = clock();
        for (int num : test) {
            bool found = false;
            for (int element : myList) {
                if (element == num) {
                    found = true;
                    break;
                }
            }
            assert(found);
        }
        end = clock();
        elapsedTime[batch][1][0] = double(end - begin) / CLOCKS_PER_SEC;
        cout << "    - list: " << elapsedTime[batch][1][0] << endl;

        begin = clock();
        for (int num : test) {
            assert(*lower_bound(myVector.begin(), myVector.end(), num) == num);
        }
        end = clock();
        elapsedTime[batch][1][1] = double(end - begin) / CLOCKS_PER_SEC;
        cout << "    - vector: " << elapsedTime[batch][1][1] << endl;

        begin = clock();
        for (int num : test) {
            assert(mySkipList.search(num));
        }
        end = clock();
        elapsedTime[batch][1][2] = double(end - begin) / CLOCKS_PER_SEC;
        cout << "    - SkipList: " << elapsedTime[batch][1][2] << endl;


        cout << "  - remove " << testSize << " elements" << endl;
        begin = clock();
        for (int num : test) {
            for (auto it = myList.begin(); it != myList.end(); it++) {
                if (*it == num) {
                    myList.erase(it);
                    break;
                }
            }
        }
        end = clock();
        elapsedTime[batch][2][0] = double(end - begin) / CLOCKS_PER_SEC;
        cout << "    - list: " << elapsedTime[batch][2][0] << endl;

        begin = clock();
        for (int num : test) {
            myVector.erase(lower_bound(myVector.begin(), myVector.end(), num));
        }
        end = clock();
        elapsedTime[batch][2][1] = double(end - begin) / CLOCKS_PER_SEC;
        cout << "    - vector: " << elapsedTime[batch][2][1] << endl;

        begin = clock();
        for (int num : test) {
            mySkipList.remove(num);
        }
        end = clock();
        elapsedTime[batch][2][2] = double(end - begin) / CLOCKS_PER_SEC;
        cout << "    - SkipList: " << elapsedTime[batch][2][2] << endl;
    }


    cout << endl << setw(10) << "[insert]"
         << setw(10) << "list" << setw(10) << "vector" << setw(10) << "SkipList" << endl;
    for (int batch = 0; batch < numBatches; batch++) {
        cout << setw(10) << batchSize * (batch + 1);
        for (double time : elapsedTime[batch][0]) {
            cout << setw(10) << fixed << setprecision(6) << time;
        }
        cout << endl;
    }


    cout << endl << setw(10) << "[search]"
         << setw(10) << "list" << setw(10) << "vector" << setw(10) << "SkipList" << endl;
    for (int batch = 0; batch < numBatches; batch++) {
        cout << setw(10) << batchSize * (batch + 1);
        for (double time : elapsedTime[batch][1]) {
            cout << setw(10) << fixed << setprecision(6) << time;
        }
        cout << endl;
    }


    cout << endl << setw(10) << "[remove]"
         << setw(10) << "list" << setw(10) << "vector" << setw(10) << "SkipList" << endl;
    for (int batch = 0; batch < numBatches; batch++) {
        cout << setw(10) << batchSize * (batch + 1);
        for (double time : elapsedTime[batch][2]) {
            cout << setw(10) << fixed << setprecision(6) << time;
        }
        cout << endl;
    }

    return 0;
} 