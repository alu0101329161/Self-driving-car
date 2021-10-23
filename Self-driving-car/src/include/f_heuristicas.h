  
#ifndef F_HEURISTICAS_H
#define F_HEURISTICAS_H

#include <cmath>
#include <algorithm>
#include "cell.h"

class f_heuristica
{
public:
    virtual double operator()(const Cell&, const Cell&) = 0;
};

//-----------------------DISTANCIA EUCLIDEA-------------------------

class d_euclidea : public f_heuristica
{
public:
    virtual double operator()(const Cell& i, const Cell& f) {
        return sqrt(pow((i.GetX() - f.GetX()),2) + pow((i.GetY() - f.GetY()), 2));
    }
};

//-----------------------DISTANCIA RECTILINEA-----------------------

class d_manhattan : public f_heuristica
{
public:
    virtual double operator()(const Cell& i, const Cell& f) {
        return fabs(i.GetX() - f.GetX()) + fabs(i.GetY() - f.GetY());
    }
};

//-----------------------DISTANCIA TCHEBYSEV-----------------------

class d_tchebysev : public f_heuristica
{
public:
    virtual double operator()(const Cell& i, const Cell& f) {
        return std::max((abs( i.GetX() - f.GetX())) , abs(i.GetY() - f.GetY()));
    }
};

#endif // F_HEURISTICAS_H