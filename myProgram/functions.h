/*! \file functions.h
    Failas, saugantis funkcijas, nesusijusias su klasėmis.
*/
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "student.h"
#include <iostream>
#include <fstream>
#include <random>
#include <chrono>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>

/*! Funkcija generuoti "kursiokai.txt" failą */

void generate(int count)
{
    //auto start = std::chrono::high_resolution_clock::now();

    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist (1, 10);

    std::fstream outFile;
    outFile.open("kursiokai.txt", std::ios::out);

    std::string ilgiausiasZodis = "Pavarde" + std::to_string(count);
    
    outFile << std::setw(ilgiausiasZodis.size())  << std::left  << "Vardas" << std::setw(ilgiausiasZodis.size() + 2) << std::left << "Pavarde";
    for (int i = 1; i <= 5; i++)
    {
        outFile << std::setw(5) << std::left << "ND" + std::to_string(i);
    }

    outFile << "Egzaminas" << std::endl;

    int number;
    for (int j = 1; j < count; j++)
    {
        outFile << std::setw(ilgiausiasZodis.size())  << std::left << "Vardas" + std::to_string(j) << std::setw(ilgiausiasZodis.size() + 2) << std::left << "Pavarde" + std::to_string(j);
        for(int a = 1; a <= 5; a++)
        {
            number = dist(mt);
            outFile << std::setw(5) << number;
        }
        number = dist(mt);
        outFile << number << std::endl;
    }

    outFile << std::setw(ilgiausiasZodis.size())  << std::left << "Vardas" + std::to_string(count) << std::setw(ilgiausiasZodis.size() + 2) << std::left << "Pavarde" + std::to_string(count);
    for (int b = 0; b < 6; b++)
    {
        number = dist(mt);
        outFile << std::setw(5) << number;
    }

    outFile.close();

    /*auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> diff = end - start;
    std::cout << "Failo kurimo laikas sekundemis: " << diff.count() << " s\n";*/
}

/*! Funkcija, perskaityti "kursiokai.txt" failą */

void readGenerated(Vector<Studentas>& newVec)
{
    std::ifstream inFile ("kursiokai.txt");
    std::string line;

    inFile >> line;
    if (inFile.eof())
    {
        throw "File failed to open";
    }

    int ndCount = 0;

    while (line != "Egzaminas")
    {
        ndCount++;
        inFile >> line;
    }
    ndCount = ndCount - 2;

    std::string name;
    std::string surname;
    Vector<double> temp;
    double exam;
    int number;

    while (!inFile.eof())
    {
        inFile >> name;
        inFile >> surname;
        for (int i = 0; i < ndCount; i++)
        {
            inFile>> number;
            temp.push_back(number);
        }
        inFile >> exam;

        temp.shrink_to_fit();

        Studentas newStudent(name, surname, temp, exam);
        newVec.push_back(newStudent);

        temp.clear();
        temp.shrink_to_fit();
    }

    newVec.pop_back();
    inFile.close();
}

/*! Funkcija, išsaugoti vartotojo įvestus duomenis */

void readUser(Vector<Studentas>& newVec)
{
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_int_distribution<int> dist (1, 10);

    std::cout << "Įveskite studento vardą(-us) ir pavardę(-es)." << std::endl;

    std::string name;
    std::cout << "Vardas: "; std::cin >> name;

    std::string surname;
    Vector<double> temp;
    double number, exam;
    std::string input;
    int ndCount;

    while (name != "0")
    {
        std::cout << "Pavardė: "; std::cin >> surname;
        if ((int) name[0] < 10 || (int) surname[0] < 10)
        {
            std::cerr << "Pirmoji vardo raidė negali būti skaičius" << std::endl;
            exit(1);
        }

        std::cout << "Ar norite, kad studentų namų darbų ir egzaminų rezultatai būtų generuojami atsitiktinai? (taip/ne) ";
        std::cin >> input;
        if (input == "taip")
        {
            std::cout << "Įveskite namų darbų rezultatų kiekį: "; std::cin >> ndCount;
            for (int i = 0; i < ndCount; i++)
            {
                number = dist(mt);
                temp.push_back(number);
            }
            exam = dist(mt);

        }
        else if(input == "ne")
        {
            std::cout << "Įveskite studento namų darbų ir egzamino rezultatus (10-balėje sistemoje)." << std::endl;
            std::cout << "Namu darbai (baigę įveskite 0): "; std::cin >> number;
            while(number != 0)
            {
                temp.push_back(number);
                std::cin >> number;
            }
            std::cout << "Egzaminas: "; std::cin >> exam;
        }
        else
        {
            std::cerr << "prašome pasirinkti taip arba ne" << std::endl;
            exit(1);
        }

        temp.shrink_to_fit();

        Studentas newStudent(name, surname, temp, exam);
        newVec.push_back(newStudent);

        temp.uncreate();
        temp.shrink_to_fit();

        std::cout << "Vardas (spauskite 0, jei norite baigti): "; std::cin >> name;
    }
}

/*! Funkcija, skaičiuojanti vidurkį ir išvedanti duomenis į "kietiakai.txt" ir "vargšiukai.txt" failus */

void vidurkis(Vector<Studentas> &newVec)
{
    std::ofstream outFile1;
    outFile1.open("vargšiukai.txt");

    std::ofstream outFile2;
    outFile2.open("kietiakai.txt");

    outFile1 << std::setw(8) << std::left << "Vardas" << std::setw(10) << std::left << "Pavardė" <<  "Galutinis (vid)" << std::endl;
    outFile2 << std::setw(8) << std::left << "Vardas" << std::setw(10) << std::left << "Pavardė" <<  "Galutinis (vid)" << std::endl;
    unsigned int vecSize = newVec.size();

    for (unsigned int i = 0; i < vecSize; ++i)
    {
        int suma = 0;
        std::cout << newVec[i].getVardas() << std::endl; //?

        for (int x = 0; x < newVec[i].getSizeOfNd(); x++)
        {
            suma += newVec[i].getNd(x);
        }

        double vid = (double) suma / newVec[i].getSizeOfNd();

        if (vid < 5)
        {
            outFile1 << newVec[i].getVardas() << " " << newVec[i].getPavarde() << " " << vid << std::endl;
        }
        else
        {
            outFile2 << newVec[i].getVardas() << " " << newVec[i].getPavarde() << " " << vid << std::endl;
        }
    }
    outFile1.close();
    outFile2.close();
}

/*! Funkcija, skaičiuojanti medianą ir išvedanti duomenis į "kietiakai.txt" ir "vargšiukai.txt" failus */

void mediana(Vector<Studentas>& newVec)
{
    std::ofstream outFile1;
    outFile1.open("vargšiukai.txt");

    std::ofstream outFile2;
    outFile2.open("kietiakai.txt");

    outFile1 << std::setw(8) << std::left << "Vardas" << std::setw(10) << std::left << "Pavardė" <<  "Galutinis (med)" << std::endl;
    outFile2 << std::setw(8) << std::left << "Vardas" << std::setw(10) << std::left << "Pavardė" <<  "Galutinis (med)" << std::endl;
    
    double med;

    unsigned int vecSize = newVec.size();

    for (unsigned int i = 0; i < vecSize; i++)
    {
        if (newVec[i].getSizeOfNd() % 2 == 0)
        {
            med = (double) (newVec[i].getNd(newVec[i].getSizeOfNd() / 2) + newVec[i].getNd(newVec[i].getSizeOfNd() / 2 - 1)) / 2;
        }
        else
        {
            med = (double) newVec[i].getNd(newVec[i].getSizeOfNd() / 2);
        }

        if (med < 5)
        {
            outFile1 << newVec[i].getVardas() << " " << newVec[i].getPavarde() << " " << med << std::endl;
        }
        else
        {
            outFile2 << newVec[i].getVardas() << " " << newVec[i].getPavarde() << " " << med << std::endl;
        }
    }
    outFile1.close();
    outFile2.close();
}

/*! Funkcija, išvedanti klasės vektoriaus turinį */

void displayVector(const Vector<Studentas>& newVec)
{
    unsigned int vecSize = newVec.size();

    for (unsigned int i = 0; i < vecSize; i++)
    {
        std::cout << newVec[i].getVardas() << " " << newVec[i].getPavarde() << " ";
        for (unsigned j = 0; j < newVec[i].getSizeOfNd(); j++)
        {
            std::cout << newVec[i].getNd(j) << " ";
        }
        std::cout << newVec[i].getEgz() << std::endl;
    }
}

#endif