
#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<iomanip> // for movie output manipulation
#include<regex>
#include"MGA_Interaction.h"
using std::string;

string add_suffix(string & prefix,bool xyz = false){
  // Build up the appended counter for filenames
	static int count = 0;
	stringstream ss;
	ss << prefix << "." << setw(4) << setfill('0') << count;
  //add a suffix for xyz files
  if (xyz) ss << ".xyz";
  count += 1;
	return ss.str();
}

void write_mga(particle *& particle_list,triplet &L,const int N_rods,string fname){
  // Write in a format that can be read by QMGA

	// open the file for writing to
  ofstream output_movie;  	// File containing data for VMD movie
	output_movie.open(fname.c_str(),ios::out);
	// Generate output in gbmega format
	// Output number of rods
  //	output_movie << N_total << endl;
	output_movie << N_rods << "\n";
	// Output box side lengths
	output_movie << L[0] << "\n" << L[1] << "\n" << L[2] << "\n";
	// Something for moving boundary conditions
	output_movie << "0 0" << "\n";
	// Output the coordinates and orientation of each rod
  //	typedef std::numeric_limits< double > dl;
  //	output_movie.precision(dl::digits10);  // Set coord output to max precision to avoid numerical errors when restarting from old coords
	output_movie.precision(6);

	for (int i=0;i<N_rods;i++)
	{
		// Orientational unit vector of particle
		output_movie << (particle_list[i].coords - L/2) << " 0 0 0 " << particle_list[i].dir
				<< " 0 0 0 " << i+1 << " " << particle_list[i].type << "\n";
	}
  //	for (int i=N_rods;i<N_total;i++)
  //	{
  //		// Orientational unit vector of particle
  //		output_movie << (particle_list[i].coords - L/2.) << " 0 0 0 " << particle_list[i].dir
  //				<< " 0 0 0 " << i+1 << " 1" << endl;
  //	}

	// close movie file
	output_movie.close();
}

void MGA_picture(particle *& particle_list,triplet &L,const int N_rods,string fnameprefix){
  // Outputs the current configuration in a format that can be read by QMGA. with appended suffix
	// Add a suffix counter to the filename
  string fname = add_suffix(fnameprefix);
  // Write the file
  write_mga(particle_list,L,N_rods,fname);
}

void read_mga(int &N_rods,triplet &L,particle *& particle_list, string filename){
  // An initializer that reads in a few parameters and the configuration
	ifstream inFile(filename.c_str());
  triplet dummy;
  string line;
  inFile >> N_rods;
  getline(inFile,line);
  inFile >> L[0];
  getline(inFile,line);
  inFile >> L[1];
  getline(inFile,line);
  inFile >> L[2];
  getline(inFile,line);// skip the 0 0  line
  getline(inFile,line);
  //Read the particles
  particle_list = new particle[N_rods];
  for(int k =0; k<N_rods; k++){
    inFile >> particle_list[k].coords >> dummy >> particle_list[k].dir >> dummy >> line >> particle_list[k].type;
    particle_list[k].coords = particle_list[k].coords + L/2;
    getline(inFile,line);  // skip rest of line
    //cout << particle_list[k].coords << endl;//debug output
  }
}

triplet vector_to_z_rotation_quaternion(triplet vec){
// a rotation quaternion to put the rod at vector v=(x,y,z) in the correct position is 180deg rotation around the vector between v and z
// this is equivalent to the quaternion (0, x, y, z + 1)/|(0, x, y, z + 1)|, or (0,v2) where v2 is the normalized dividing vector

  vec = vec / vec.norm(); //Normalise as a double check
  triplet vec2 = vec + triplet(0,0,1);
  return vec2/vec2.norm();
}

triplet z_rotation_quaternion_to_vector(triplet quat){
  triplet vec;
  vec[0]=2*quat[0]*quat[2];
  vec[1]=2*quat[1]*quat[2];
  vec[2]=1-2*(quat[0]*quat[0]+quat[1]*quat[1]);
  return vec;
}

void write_xyz(particle *& particle_list,triplet &L,const int N_rods,string fname){ // copied From Main program, modified to change particle type to cluster #
  // Outputs the current configuration in a format that can be read by Ovito
	// open the movie file for writing to
  ofstream output_movie;  	// File containing data for VMD movie
	output_movie.open(fname.c_str(),ios::out);

	// Generate output in gbmega format
	// Output number of rods
  //	output_movie << N_total << endl;
	output_movie << N_rods << "\n";
	// Output box side lengths
	output_movie << "Lattice=\"" << L[0] << " 0 0 0 " << L[1] << " 0 0 0 " << L[2] 
  << "\" cell_origin=\"" << L[0]/-2 << " " << L[1]/-2 << " " << L[2]/-2 << "\" "
  << "properties=pos:R:3:orientation:R:3:id:I:1:type:I:1 orientation is from quaternion Q(0,v2) such that zQ=v, the real direction\n";
  
  //	output_movie.precision(dl::digits10);  // Set coord output to max precision to avoid numerical errors when restarting from old coords
	output_movie.precision(7);

	// Output the coordinates and orientation of each rod
	for (int i=0;i<N_rods;i++)
	{
		// Orientational unit vector of particle
		output_movie << (particle_list[i].coords - L/2) << " " << vector_to_z_rotation_quaternion(particle_list[i].dir)
		<< " " << i+1 << " " << particle_list[i].type << "\n";
	}
	// close movie file
	output_movie.close();
}

void xyz_picture(particle *& particle_list,triplet &L,const int N_rods,string fnameprefix){
  // Outputs the current configuration in a format that can be read by QMGA.
	// Add a suffix counter to the filename
  string fname = add_suffix(fnameprefix,true);
  // Write the file
  write_xyz(particle_list,L,N_rods,fname);
}

void read_xyz(int &N_rods, triplet &L, particle *&particle_list, string filename) {
  // An initializer that reads in a few parameters and the configuration
  ifstream inFile(filename.c_str());
  string dummy;
  triplet dummy3;
  string line;
  string temp_type;

  getline(inFile, line);
  N_rods = stoi(line);

  getline(inFile, line); //read parameter line
  istringstream paramsline(line);
  paramsline >> dummy;
  try {
    L[0] = stod(dummy.replace(0, 9, ""));
  }catch(std::invalid_argument){
    //catch cases where there may be a space before the first lattice vector
    paramsline >> dummy;
    L[0] = stod(dummy);
  }
  paramsline >> dummy3 >> L[1];
  paramsline >> dummy3 >> dummy;
  L[2] = stod(dummy.replace(dummy.length() - 1, 1, ""));

  particle_list = new particle[N_rods];
  for (int k = 0; k < N_rods; k++) {
    inFile >> particle_list[k].coords >> particle_list[k].dir >> dummy >> temp_type;
    particle_list[k].type = stoi(std::regex_replace(temp_type,std::regex(R"([\D])"),""));
    particle_list[k].coords = particle_list[k].coords + L / 2;
    particle_list[k].dir = z_rotation_quaternion_to_vector(particle_list[k].dir);
    getline(inFile, line);  // skip rest of line
  }
  inFile.close();
}

void write_spheres_xyz(particle *& particle_list,triplet &L,const int N_rods,string fname){ // copied From Main program, modified to change particle type to cluster #
  // Outputs the current configuration in a format that can be read by Ovito
	// open the movie file for writing to
  ofstream output_movie;  	// File containing data for VMD movie
	output_movie.open(fname.c_str(),ios::out);
  int spheres_per_rod=20;
  int attractive = 15;
  double length=5;
  double sphere_spacing = length/spheres_per_rod;
  int s_type;
	// Generate output in gbmega format
	// Output number of rods
  //	output_movie << N_total << endl;
	output_movie << N_rods * spheres_per_rod << "\n";
	// Output box side lengths
	output_movie << "Lattice=\"" << L[0] << " 0 0 0 " << L[1] << " 0 0 0 " << L[2] 
  << "\" cell_origin=\"" << L[0]/-2 << " " << L[1]/-2 << " " << L[2]/-2 << "\" "
  << "properties=pos:R:3:id:I:1:type:I:1 orientation is from quaternion Q(0,v2) such that zQ=v, the real direction\n";
  
  //	output_movie.precision(dl::digits10);  // Set coord output to max precision to avoid numerical errors when restarting from old coords
	output_movie.precision(7);

	// Output the coordinates and orientation of each rod
	for (int i=0;i<N_rods;i++)
	{
		for (int j=0;j<spheres_per_rod;j++){
    if (j < attractive){
      s_type = particle_list[i].type;
    }else{
      s_type = 0;
    }
		output_movie << (particle_list[i].coords - L/2 - particle_list[i].dir * (-length/2. + sphere_spacing*j)) << " " << i+1 << " " << s_type << "\n";
    }
	}
	// close movie file
	output_movie.close();
}