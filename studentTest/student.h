/*! \file student.h
    Failas saugantis Base ir Derived klases.
*/
#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <algorithm>
#include "Vector.h"

/*! Base klasė "StudentBase" */

class StudentBase
{
protected:
    std::string vardas_;
    std::string pavarde_;
    StudentBase(std::string vardas, std::string pavarde);
};

/*! Derived klasė "Studentas" */

class Studentas : public StudentBase
{
private:
    Vector<double> nd_;
    double egz_;
public:
    Studentas(std::string vardas, std::string pavarde, Vector<double>& ND, double egzaminas) : 
        StudentBase(vardas, pavarde), nd_{ND}, egz_{egzaminas} {}
    void nd ( double n ) { nd_.push_back(n); };
    void egz ( double n ) { egz_ = n; }
    std::string getVardas() const;
    std::string getPavarde() const;
    double getEgz() const;
    int getSizeOfNd() const;
    double getNd(int i) const;
    void sortND();
};

inline bool operator <(Studentas s1, Studentas s2)
{
	return s1.getVardas() < s2.getVardas();
}

inline bool operator >(Studentas s1, Studentas s2)
{
	return s1.getVardas() < s2.getVardas();
}

inline bool operator <=(Studentas s1, Studentas s2)
{
	return s1.getVardas() < s2.getVardas();
}

inline bool operator >=(Studentas s1, Studentas s2)
{
	return s1.getVardas() < s2.getVardas();
}

#endif