#include <fstream>
#include <string>
#include <iostream>
#include <array>

#include "./heat_eq.hpp"

int main (int argc, char* argv[]) {
  
  //L, T, dt, dx, b(x), a0 -- a6
  double L;
  double T;
  double dt;
  double dx;
  std::string b;

  std::array<double, 7> arr;
  std::vector<double> first_layer_direct;
  std::vector<double> first_layer_indirect;


  if (argc == 13) {
    L = atof(argv[1]);
    T = atof(argv[2]);
    dx = atof(argv[3]);
    dt = atof(argv[4]);
    b = argv[5];

    arr[0] = atof(argv[6]);
    arr[1] = atof(argv[7]);
    arr[2] = atof(argv[8]);
    arr[3] = atof(argv[9]);
    arr[4] = atof(argv[10]);
    arr[5] = atof(argv[11]);
    arr[6] = atof(argv[12]);
    
  } else {
    L = 100;
    T = 10;
    dx = 9;
    dt = 0.75;
    b = "sin(x)";

    arr = {0.25, 1, 0.5, 0.3, 0.78, 0.01, 0.02};
  }

  //input your dir or whatever
  std::string fileNameDirect = "../data/direct_result.bin";
  std::string fileNameIndirect = "../data/indirect_result.bin";
  
  Heat_eq ourEq(b, arr, L, T, dx, dt);

  auto impl_res = ourEq.implicit_method(first_layer_indirect);
  auto expl_res = ourEq.explicit_method(first_layer_direct);
  
  size_t size = impl_res.size();

//  for (int i = 0; i<size; i++)
//    std::cout << first_layer[i] << "  ";
//
//  std::cout << std::endl << std::endl;
//
//  for (int i = 0; i<size; i++)
//    std::cout << impl_res[i] << "  ";
//
//  std::cout << std::endl << std::endl;
//
//  for (int i = 0; i<size; i++)
//    std::cout << expl_res[i] << "  ";

  //Stream for explicit
  std::ofstream outStreamDirect(fileNameDirect, std::ios::binary | std::ios::trunc);
  outStreamDirect.write((char*)&size, sizeof(size_t));

  for (size_t i = 0; i < first_layer_direct.size(); i++)
  {
    outStreamDirect.write((char*)&first_layer_direct[i], sizeof(double));
  }
  for (size_t i = 0; i < expl_res.size(); i++)
  {
    outStreamDirect.write((char*)&expl_res[i], sizeof(double));
  }

  outStreamDirect.close();

  //Stream for implicit
  std::ofstream outStreamIndirect(fileNameIndirect, std::ios::binary | std::ios::trunc);
  outStreamIndirect.write((char*)&size, sizeof(size_t));

  for (size_t i = 0; i < first_layer_indirect.size(); i++)
  {
    outStreamIndirect.write((char*)&first_layer_indirect[i], sizeof(double));
  }
  for (size_t i = 0; i < impl_res.size(); i++)
  {
    outStreamIndirect.write((char*)&impl_res[i], sizeof(double));
  }

  outStreamIndirect.close();
  return 0;
}