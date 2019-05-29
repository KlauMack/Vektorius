#include "student.h"
#include <iostream>
#include <vector>
#include <chrono>

int main()
{
    Vector<Studentas> students;

    std::string name = "Klaudijus";
    std::string surname = "Mackonis";
    Vector<double> temp;
    for (int i = 0; i < 5; i++)
        temp.push_back(i);

    temp.shrink_to_fit();
    
    double exam = 4;
    Studentas newStudent(name, surname, temp, exam);
    students.push_back(newStudent);

    std::cout << newStudent.getVardas() << std::endl;
    std::cout << newStudent.getSizeOfNd() << std::endl;
    for (int x = 0; x < newStudent.getSizeOfNd(); x++)
        std::cout << newStudent.getNd(x) << std::endl;
}