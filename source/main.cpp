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

  if (argc == 13) {
    L = atof(argv[1]);
    T = atof(argv[2]);
    dt = atof(argv[3]);
    dx = atof(argv[4]);
    b = argv[5];

    arr[0] = atof(argv[6]);
    arr[1] = atof(argv[7]);
    arr[2] = atof(argv[8]);
    arr[3] = atof(argv[9]);
    arr[4] = atof(argv[10]);
    arr[5] = atof(argv[11]);
    arr[6] = atof(argv[12]);
    
  } else {
    L = 10;
    T = 10;
    dx = 0.01;
    dt = 0.0001;
    b = "sin(x)";

    arr = {1, 1, 1, 1, 1, 1, 1};
  }

  //input your dir or whatever
  std::string fileName = "../data/direct_result";
  
  Heat_eq ourEq(b, arr, L, T, dx, dt);

  //auto impl_res = ourEq.implicit_method();
  auto impl_res = ourEq.implicit_method();
  size_t size = impl_res.size();

  for (int i = 0; i<size; i++)
    std::cout << impl_res[i] << std::endl;

  std::ofstream outStream(fileName, std::ios::binary | std::ios::trunc);
  outStream.write((char*)&size, sizeof(size_t));

  for (int i = 0; i<impl_res.size(); i++)
    outStream.write((char*)&impl_res[i], sizeof(double));

  outStream.close();
  return 0;
}