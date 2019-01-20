
#include<iostream>
#include<cmath>
#include"triplet.h"
using namespace std;

/*class triplet
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
};*/

triplet triplet::cross(const triplet& rhs)
{
	triplet answer, lhs=*this;
	answer[0] = lhs[1]*rhs[2] - lhs[2]*rhs[1];
	answer[1] = lhs[2]*rhs[0] - lhs[0]*rhs[2];
	answer[2] = lhs[0]*rhs[1] - lhs[1]*rhs[0];
	return answer;
}

void triplet::set(double x, double y, double z)
{
	my_values[0] = x;
	my_values[1] = y;
	my_values[2] = z;
}

double triplet::norm()
{
	return sqrt(my_values[0]*my_values[0]+my_values[1]*my_values[1]+my_values[2]*my_values[2]);
}


double& triplet::operator [](unsigned int i)
{
	return my_values[i];
}

double triplet::operator [](unsigned int i) const
{
	return my_values[i];
}


triplet::triplet(double x,double y,double z)
{
	my_values[0] = x;
	my_values[1] = y;
	my_values[2] = z;
}

triplet::triplet()
{
	my_values[0] = 0.0;
	my_values[1] = 0.0;
	my_values[2] = 0.0;
}

//Global operator overloads for triplet class
triplet operator + (const triplet& lhs, const triplet& rhs)
{
	triplet answer(lhs[0]+rhs[0],lhs[1]+rhs[1],lhs[2]+rhs[2]);
	return answer;
}

triplet operator - (const triplet& lhs, const triplet& rhs)
{
	triplet answer(lhs[0]-rhs[0],lhs[1]-rhs[1],lhs[2]-rhs[2]);
	return answer;
}

triplet operator - (const triplet& lhs, const double rhs)
{
	triplet answer(lhs[0]-rhs,lhs[1]-rhs,lhs[2]-rhs);
	return answer;
}

ostream& operator << (ostream& os, const triplet& rhs)
{
	return os << rhs[0] << " " << rhs[1] << " " << rhs[2];
}

istream& operator >> (istream& is, triplet& rhs)
{
	return is >> rhs[0] >> rhs[1] >> rhs[2];
}

double operator * (const triplet& lhs, const triplet& rhs)
{
	return lhs[0]*rhs[0] + lhs[1]*rhs[1] + lhs[2]*rhs[2];
}

triplet operator * (const triplet& lhs, double rhs)
{
	triplet answer(lhs[0]*rhs,lhs[1]*rhs,lhs[2]*rhs);
	return answer;
}

triplet operator * (double lhs, const triplet& rhs)
{
	triplet answer(rhs[0]*lhs,rhs[1]*lhs,rhs[2]*lhs);
	return answer;
}

triplet operator / (const triplet& lhs, double rhs)
{
	triplet answer(lhs[0]/rhs,lhs[1]/rhs,lhs[2]/rhs);
	/*
	triplet answer = lhs;
	answer[0] = answer[0]/rhs;
	answer[1] = answer[1]/rhs;
	answer[2] = answer[2]/rhs;
	*/
	return answer;
}

bool operator == (const triplet& lhs, const triplet& rhs)
{
	if(lhs[0]==rhs[0] && lhs[1]==rhs[1] && lhs[2]==rhs[2]){return true;}
	else{return false;}
}
