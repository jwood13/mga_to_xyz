#pragma once
#ifndef PARTICLE_H
#define PARTICLE_H
#include"../Lib/triplet.h"
class particle{
  // Stores particle coords and orientation
  public:
  	particle() : coords(), dir(){};
  	triplet coords, dir;
  	int type = 0;
};
#endif
