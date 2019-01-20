#pragma once
#ifndef TRIPLET_H
#define TRIPLET_H
#include<iostream>
#include<cmath>

using namespace std;

class triplet
{
public:
	triplet(double x, double y, double z);
	triplet();
	~triplet(){};
	double& operator [] (unsigned int i);
	double operator [] (unsigned int i) const;
	double norm();
	void set(double x,double y, double z);
	triplet cross(const triplet&);
private:
	double my_values[3];
};

//Global operator overloads for triplet class
triplet operator + (const triplet& lhs, const triplet& rhs);

triplet operator - (const triplet& lhs, const triplet& rhs);

triplet operator - (const triplet& lhs, const double rhs);

ostream& operator << (ostream& os, const triplet& rhs);

istream& operator >> (istream& is, triplet& rhs);

double operator * (const triplet& lhs, const triplet& rhs);

triplet operator * (const triplet& lhs, double rhs);

triplet operator * (double lhs, const triplet& rhs);

triplet operator / (const triplet& lhs, double rhs);

bool operator == (const triplet& lhs, const triplet& rhs);

#endif
