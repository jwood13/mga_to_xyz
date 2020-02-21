#include <stdio.h>
#include "Lib/triplet.cpp"
#include "src/MGA_Interaction.cpp"
#include "src/MGA_Interaction.h"

int read_mga_write_xyz(string filename) {
  particle* particle_list;  // The particle list
  int N_rods;
  triplet L;
  read_mga(N_rods, L, particle_list, filename);
  write_spheres_xyz(particle_list, L, N_rods, filename.append("s.xyz"));
}

int main(int argc, char* argv[]) {
  if (argc == 1) {
    // feed in the first argument as the random seed to allow easy
    // control of the seed without putting it in the params file
    std::cout << "Needs an Input" << endl;
    return 1;
  } else {
    return read_mga_write_xyz(argv[1]);
  }
}