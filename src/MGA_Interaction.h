#ifndef MGA_INTERACTION_H
#define MGA_INTERACTION_H
#include<string>
#include<iomanip> // for movie output manipulation
#include"../src/particle.h"
#include"../Lib/triplet.h"

void MGA_picture(particle *& particle_list,triplet &L,const int N_rods, string fname = "mga_movie");


void read_mga(int &N_rods,triplet &L,particle *& particle_list, string filename = "mga_movie.000");
#endif
