#include <iostream>
#include <vector>
#include <list>
#include <chrono>
#include <random>

using namespace std;
using namespace chrono;

class HashTable {

private:
    vector<list<int>> table;
    int size;

public:

    HashTable(int s) : size(s) {
        table.resize(size);
    }

    int hashFunction(int key) {
        return key % size;
    }

    void insert(int key) {
        table[hashFunction(key)].push_back(key);
    }

    bool remove(int key) {

        int idx = hashFunction(key);

        for(auto it = table[idx].begin(); it != table[idx].end(); ++it) {

            if(*it == key) {
                table[idx].erase(it);
                return true;
            }
        }

        return false;
    }
};

void optimisticTest() {

    const int N = 10000;

    HashTable ht(20011);

    auto start = high_resolution_clock::now();

    for(int i = 0; i < N; i++)
        ht.insert(i);

    auto stop = high_resolution_clock::now();

    cout << "\n=== OPTYMISTYCZNY ===\n";

    cout << "Dodawanie: "
         << duration_cast<microseconds>(stop-start).count()
         << " us\n";

    start = high_resolution_clock::now();

    for(int i = 0; i < N; i++)
        ht.remove(i);

    stop = high_resolution_clock::now();

    cout << "Usuwanie: "
         << duration_cast<microseconds>(stop-start).count()
         << " us\n";
}

void averageTest() {

    const int N = 10000;

    HashTable ht(20011);

    vector<int> values;

    mt19937 rng(42);
    uniform_int_distribution<int> dist(1,1000000);

    auto start = high_resolution_clock::now();

    for(int i=0;i<N;i++) {

        int x = dist(rng);

        values.push_back(x);

        ht.insert(x);
    }

    auto stop = high_resolution_clock::now();

    cout << "\n=== SREDNI ===\n";

    cout << "Dodawanie: "
         << duration_cast<microseconds>(stop-start).count()
         << " us\n";

    start = high_resolution_clock::now();

    for(int x : values)
        ht.remove(x);

    stop = high_resolution_clock::now();

    cout << "Usuwanie: "
         << duration_cast<microseconds>(stop-start).count()
         << " us\n";
}

void pessimisticTest() {

    const int N = 10000;

    HashTable ht(20011);

    auto start = high_resolution_clock::now();

    for(int i=0;i<N;i++)
        ht.insert(i*20011);

    auto stop = high_resolution_clock::now();

    cout << "\n=== PESYMISTYCZNY ===\n";

    cout << "Dodawanie: "
         << duration_cast<microseconds>(stop-start).count()
         << " us\n";

    start = high_resolution_clock::now();

    for(int i=0;i<N;i++)
        ht.remove(i*20011);

    stop = high_resolution_clock::now();

    cout << "Usuwanie: "
         << duration_cast<microseconds>(stop-start).count()
         << " us\n";
}

int main() {

    optimisticTest();
    averageTest();
    pessimisticTest();

    return 0;
}