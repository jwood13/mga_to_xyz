#include <stdio.h>
#include "Lib/triplet.cpp"
#include "src/MGA_Interaction.cpp"
#include "src/MGA_Interaction.h"

int read_and_write_spheres(string filename, const int attractive_spheres = 15, const int spheres_per_rod = 20, const double length = 5) {
  particle* particle_list;  // The particle list
  int N_rods;
  triplet L;
  if (filename.substr(filename.size()-4) != ".xyz") {
    read_mga(N_rods, L, particle_list, filename);
  }else{
    read_xyz(N_rods, L, particle_list, filename);
  }
  write_spheres_xyz(particle_list, L, N_rods, filename.append("s.xyz"), attractive_spheres, spheres_per_rod, length);
}

int main(int argc, char* argv[]) {
  if (argc == 1) {

    std::cout << "Needs an Input" << endl;
    return 1;
  } else {
    return read_and_write_spheres(argv[1]);
  }
}