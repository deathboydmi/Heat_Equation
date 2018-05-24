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

  std::vector<double> TDMA(const std::vector<std::vector<double>>& matr, const std::vector<double>& fa) {
    unsigned N1 = fa.size();
    std::vector<double> res(N1);
    --N1;
    double y = matr[0][0];
    std::vector<double> a(N1);
    std::vector<double> B(N1);
    a.push_back(-matr[0][1] / y);
    B.push_back(fa[0] / y);

    for (int i = 1; i < N1; ++i) {
      y = matr[i][i] + matr[i][i - 1] * a[i - 1];
      a.pushback(-matr[i][i + 1] / y);
      B.pushback((fa[i] - matr[i][i - 1] * B[i - 1]) / y);
    }

    res[N1] = (fa[N1] - matr[N1][N1 - 1] * B[N1 - 1]) / (matr[N1][N1] + matr[N1][N1 - 1] * a[N1 - 1]);
    for (int i = N1 - 1; i >= 0; --i) {
        res[i] = a[i] * res[i + 1] + B[i];
    }

    return res;
  }
public:
  Heat_eq(std::string b, std::array<double, 7> a, unsigned l, unsigned t, unsigned dx, unsigned dt):
    a(a), L(l), T(t), dx(dx), dt(dt) {
      n_x = L / dx + 1;
      n_t = T / dt + 1;

      expl_U.resize(n_x);
      impl_U.resize(n_x);

      _b.SetFunction(b);
    }

  std::vector<double> implicit_method() {
    
    return impl_U;
  }

  std::vector<double> explicit_method() {
    //
    return expl_U;
  }
};
