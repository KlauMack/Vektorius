#include "Vector.h"
#include "student.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <string>

void uzpildymas(size_t size) {
    /*std::vector<Studentas> v1;
    std::cout << "Užpildoma " << size << " elementais" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i++)
    {
        std::string name = "Klaudijus";
        std::string surname = "Mackonis";
        std::vector<double> temp;
        for(unsigned int i = 0; i < 5; i++)
        {
            temp.push_back(i);
        }
        double exam = 5;
        Studentas vec1(name, surname, temp, exam);
        v1.push_back(vec1);
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "std::vector laikas sekundemis: " << diff.count() << " s\n";*/ 

    Vector<Studentas> v2;

    auto start1 = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < size; i++) {
        std::string name = "Klaudijus";
        std::string surname = "Mackonis";
        Vector<double> temp;
        for(unsigned int i = 0; i < 5; i++)
        {
            temp.push_back(i);
        }
        double exam = 5;

        Studentas vec2(name, surname, temp, exam);
        v2.push_back(vec2);
    }

    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff1 = end1 - start1;
    std::cout << "Vector laikas sekundemis: " << diff1.count() << " s\n";
}

void perskirstymas(size_t size) {
    /*std::vector<Studentas> v1;
    int totalRealloc = 0;
    std::cout << "Užpildoma " << size << " elementais" << std::endl;
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < size; i++)
    {
        std::string name = "Klaudijus";
        std::string surname = "Mackonis";
        std::vector<double> temp;
        for(unsigned int i = 0; i < 5; i++)
        {
            temp.push_back(i);
        }
        double exam = 5;
        Studentas vec1(name, surname, temp, exam);
        v1.push_back(vec1);
        if (v1.size() == v1.capacity()) {
            totalRealloc++;
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "std::vector laikas sekundemis: " << diff.count() << " s\n"; 
    std::cout << "std::vector persirstymai: " << totalRealloc << std::endl;*/

    Vector<Studentas> v2;

    int totalRealloc = 0;

    for (int i = 0; i < size; i++) {
        std::string name = "Klaudijus";
        std::string surname = "Mackonis";
        Vector<double> temp;
        for(unsigned int i = 0; i < 5; i++)
        {
            temp.push_back(i);
        }
        double exam = 5;

        Studentas vec2(name, surname, temp, exam);
        v2.push_back(vec2);

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

    return 0;
}