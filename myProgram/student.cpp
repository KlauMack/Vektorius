/*! \file student.cpp
    Klasių realizacijos failas.
*/
#include "student.h"

StudentBase::StudentBase(std::string vardas, std::string pavarde, Vector<double>& ND, double egzaminas)
{
    vardas_ = vardas;
    pavarde_ = pavarde;
    nd_ = ND;
    egz_ = egzaminas;
}

std::string Studentas::getVardas() const
{
    return vardas_;
}

std::string Studentas::getPavarde() const
{
    return pavarde_;
}

double Studentas::getEgz() const
{
    return egz_;
}

int Studentas::getSizeOfNd() const
{
    return nd_.size();
}

double Studentas::getNd(int i) const
{
    return nd_[i];
}

void Studentas::sortND()
{
    std::sort(nd_.begin(), nd_.end());
}