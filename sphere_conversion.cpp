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
  int attractive_spheres = 15;
  int spheres_per_rod = 20;
  double length = 5;
  if (argc == 1) {

    std::cout << "Needs an Input" << endl;
    return 1;
  } else {
    if (argc > 2){
      attractive_spheres = std::stoi(argv[2]);
      if (argc > 3){
        spheres_per_rod = std::stoi(argv[3]);
        if (argc > 4){
          length = std::stod(argv[4]);
        }
      }
    }
    return read_and_write_spheres(argv[1],attractive_spheres, spheres_per_rod, length);
  }
}