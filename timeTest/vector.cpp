#include "Vector.h"
#include <iostream>
#include <vector>
#include <chrono>

void uzpildymas(size_t size) {
    std::vector<int> v1;
    Vector<int> v2;

    std::cout << "Užpildoma " << size << " elementais" << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < size; i++) {
        v1.push_back(i);
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "std::vector laikas sekundemis: " << diff.count() << " s\n"; 

    auto start1 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < size; i++) {
        v2.push_back(i);
    }

    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff1 = end1 - start1;
    std::cout << "Vector laikas sekundemis: " << diff1.count() << " s\n"; 
}

void perskirstymas(size_t size) {
    std::vector<int> v1;
    Vector<int> v2;
    int totalRealloc = 0;

    std::cout << "Užpildoma " << size << " elementais" << std::endl;

    for (int i = 0; i < size; i++) {
        v1.push_back(i);
        if (v1.size() == v1.capacity()) {
            totalRealloc++;
        }
    }

    std::cout << "Vector persirstymai: " << totalRealloc << std::endl;; 

    totalRealloc = 0;

    for (int i = 0; i < size; i++) {
        v2.push_back(i);
        if (v2.size() == v2.capacity()) {
            totalRealloc++;
        }
    }

    std::cout << "std::vector perskirstymai: " << totalRealloc << std::endl; 
}


int main()
{
    for (size_t i = 10000; i <= 100000000; i *= 10)
    {
        uzpildymas(i);
        perskirstymas(i);
    }
}