#include <fstream>
#include <string>
#include <array>

#include "./heat_eq.hpp"

int main (int argc, char* argv[]) {
  
  //L, X, dt, dx, b(x), a0 -- a6
  double L = atof(argv[1]);
  double T = atof(argv[2]);
  double dt = atof(argv[3]);
  double dx = atof(argv[4]);
  std::string b = argv[5];
  
  std::array<double, 7> arr;
  arr[0] = atof(argv[6]);
  arr[1] = atof(argv[7]);
  arr[2] = atof(argv[8]);
  arr[3] = atof(argv[9]);
  arr[4] = atof(argv[10]);
  arr[5] = atof(argv[11]);
  arr[6] = atof(argv[12]);

  //input your dir or whatever
  std::string fileName = "../data/direct_result.bin";
  
  Heat_eq ourEq(b, arr, L, T, dx, dt);

  auto impl_res = ourEq.implicit_method();

  std::fstream outStream(fileName, std::ios::binary | std::ios::trunc | std::ios::out);
  for (int i = 0; i<impl_res.size(); i++)
    outStream << impl_res[i];

  outStream.close();
  return 0;
}