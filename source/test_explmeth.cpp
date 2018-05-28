#include <string>
#include <vector>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <array>

#include "heat_eq.hpp"

double phi_x(double x, std::array<double, 7> arr, double L) {
  auto phi = arr[0];
  for (int i = 1; i < 7; ++i) {
    phi += arr[i]*cos(x*i*3.14/L);
  }
  return phi;
}


int main(int argc, char* argv[]) {

  double L = 100;
  double T = 10;
  double dx = 10;
  double dt = 0.01;
  std::string b = "sin(x)";
  std::array<double, 7> arr = {0.25, 1, 0.5, 0.3, 0.78, 0.01, 0.02};

  std::vector<std::vector<double>> grid;
  std::vector<double> rod;
  double current_x = 0;
  while (current_x < L) {
    rod.push_back(phi_x(current_x, arr, L));
    current_x += dx;
  }

  grid.push_back(rod);

  double current_t = 0;
  while (current_t < T) {
    std::vector<double> tmp;
    current_x = dx;
    int i = 1;
    while (current_x < L - dx) {
      tmp.push_back(dt/(dx*dx)*(rod[i-1] - 2*rod[i] + rod[i+1]) + rod[i]*(1 + dt*sin(current_x)));
      //tmp.push_back(dt/(dx*dx)*(rod[i-1] - 2*rod[i] + rod[i+1]) + rod[i]);
      current_x += dx;
      ++i;
    }
    rod.clear();
    rod.push_back(tmp[0]);
    std::for_each(tmp.cbegin(), tmp.cend(), [&](double elem){
      rod.push_back(elem);
    });
    rod.push_back(tmp[tmp.size()-1]);
    grid.push_back(rod);
    current_t += dt;
  }

  for (int i = 0; i < grid.size(); ++i) {
    for (int j = 0; j < grid[i].size(); ++j) {
      std::cout << grid[i][j] << "  ";
    }
    std::cout << std::endl;
  }

  std::cout << std::endl;
  std::cout << std::endl;

  Heat_eq ourEq(b, arr, L, T, dx, dt);
  std::vector<double> first_layer_direct, first_layer_indirect;
  auto expl_res = ourEq.explicit_method(first_layer_direct);
  std::cout << std::endl;
  std::cout << std::endl;
  auto impl_res = ourEq.implicit_method(first_layer_indirect);
  

  return 0;
}