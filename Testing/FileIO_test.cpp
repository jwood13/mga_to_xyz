#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "../Lib/triplet.cpp"
#include "../src/MGA_Interaction.h"
#include "../src/MGA_Interaction.cpp"
#include <stdio.h>
bool same_triplet(triplet& t1, triplet& t2,double threshold = 1E-6){
    for (int i=0;i<2;i++){
        if (abs(t1[i]-t2[i])>threshold) return false;
    }
    return true;
}
TEST_CASE("mga Read and write the same thing"){
    particle* particle_list;	// The particle list
    particle_list = new particle[2];
    int N_rods=2;
    triplet L(21.1,19.0904,32.2211);
    particle temp;
    temp.coords=triplet(5.84237,9.06411,-7.53426) + L/2;
    temp.dir=triplet(0.640385,0.435019,-0.632981);
    temp.type=256;
    particle_list[0] = temp;
    temp.coords=triplet(-3.79558,-5.02996,3.51592) + L/2;
    temp.dir=triplet(-0.636237,-0.0506159,0.769832);
    temp.type=0;
    particle_list[1] = temp;
    // read_mga(N_rods,L,particle_list,"file_io_test.mga");
    REQUIRE(N_rods > 0);
    particle* particle_list2;	// The particle list
    int N_rods2;
    triplet L2;
    MGA_picture(particle_list,L,N_rods,"tempfile1.mga");
    read_mga(N_rods2,L2,particle_list2,"tempfile1.mga.0000");
    REQUIRE(N_rods==N_rods2);
    REQUIRE(L==L2);
    REQUIRE(particle_list[0].coords==particle_list2[0].coords);
    REQUIRE(particle_list[0].type==particle_list2[0].type);
    REQUIRE(particle_list[0].dir==particle_list2[0].dir);
    REQUIRE(particle_list[N_rods - 1].coords==particle_list2[N_rods - 1].coords);
    REQUIRE(particle_list[N_rods - 1].type==particle_list2[N_rods - 1].type);
    REQUIRE(particle_list[N_rods - 1].dir==particle_list2[N_rods - 1].dir);
    REQUIRE(remove("tempfile1.mga.0000") == 0);
    delete[] particle_list ;
    delete[] particle_list2 ;
}

TEST_CASE("xyz Read and write the same thing"){
    particle* particle_list;	// The particle list
    int N_rods;
    triplet L;
    read_mga(N_rods,L,particle_list,"file_io_test.mga");
    REQUIRE(N_rods > 0);
    particle* particle_list2;	// The particle list
    int N_rods2;
    triplet L2;
    write_xyz(particle_list,L,N_rods,"tempfile1.xyz");
    read_xyz(N_rods2,L2,particle_list2,"tempfile1.xyz");
    REQUIRE(N_rods==N_rods2);
    REQUIRE(L==L2);
    REQUIRE(particle_list[0].coords==particle_list2[0].coords);
    REQUIRE(same_triplet(particle_list[0].dir,particle_list2[0].dir));
    REQUIRE(particle_list[0].type==particle_list2[0].type);
    REQUIRE(particle_list[N_rods - 1].coords==particle_list2[N_rods - 1].coords);
    REQUIRE(same_triplet(particle_list[N_rods - 1].dir,particle_list2[N_rods - 1].dir));
    REQUIRE(particle_list[N_rods - 1].type==particle_list2[N_rods - 1].type);
    REQUIRE(remove("tempfile1.xyz") == 0);
    delete[] particle_list ;
    delete[] particle_list2 ;
}