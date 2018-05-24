#include <string>
#include <vector>
#include <array>
#include <cmath>

#include "./tofunction/tofunction.h"

#define PI 3.14159265358979323846

class Heat_eq {
    // input
  ToFunction _b;
  std::array<double, 7> a;

  unsigned int L;
  unsigned int T;
  unsigned int dx;
  unsigned int dt;

    // output
  std::vector<double> expl_U;
  std::vector<double> impl_U;

    // else
  unsigned int n_x;
  unsigned int n_t;

  double b_x(double x) {
    return _b.Calculate(x);
  }

  double phi_x(double x) {
    auto phi = a[0];
    auto eto = PI / L;
    for (unsigned i = 1; i < 7; ++i) {
      phi += a[i] * cos(i * eto * x);
    }

    return phi;
  }

public:
  Heat_eq(std::string b, std::array<double, 7> a, unsigned l, unsigned t, unsigned dx, unsigned dt):
    a(a), L(l), T(t), dx(dx), dt(dt) {
      n_x = L / dx;
      n_t = T / dt;

      expl_U.resize(n_x);
      impl_U.resize(n_x);

      _b.SetFunction(b);
    }

  std::vector<double> implicit_method() {
    //
    return impl_U;
  }

  std::vector<double> explicit_method() {
    //
    return expl_U;
  }
};