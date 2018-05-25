#include <string>
#include <vector>
#include <array>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <iomanip>
#include <iostream>

#include "./tofunction/tofunction.h"

#define PI 3.14159265358979323846

class Heat_eq {
    // input
    ToFunction _b;
    std::array<double, 7> a;

    double L;
    double T;
    double dx;
    double dt;

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

    std::vector<std::vector<double>> init_trid_matr(std::vector<std::vector<double>> &trid_matr) {
        auto q = -dt / (dx * dx);
        auto p = - 2 * q + 1;

        std::vector<double> tmp;

        tmp.push_back(p + q);
        tmp.push_back(q);
        for (size_t j = 1; j < n_x - 3; ++j) {
            tmp.push_back(0.0);
        }
        trid_matr.push_back(tmp);

        unsigned k = 0;
        for (size_t j = 1; j < n_x - 3; ++j) {
            tmp.clear();
            for (size_t i = 0; i < k; ++i) {
                tmp.push_back(0.0);
            }
            tmp.push_back(q);
            tmp.push_back(p);
            tmp.push_back(q);
            for (size_t i = 0; i < n_x - 2 - k - 3; ++i) {
                tmp.push_back(0.0);
            }
            trid_matr.push_back(tmp);
            ++k;
        }

        tmp.clear();
        for (size_t j = 1; j < n_x - 3; ++j) {
            tmp.push_back(0.0);
        }
        tmp.push_back(q);
        tmp.push_back(p + q);
        trid_matr.push_back(tmp);

        return trid_matr;
    }

    std::vector<double> TDMA(const std::vector<std::vector<double>> &matr, const std::vector<double> &fa) {
        unsigned N1 = fa.size();
        std::vector<double> res(N1);
        --N1;
        double y = matr[0][0];
        std::vector<double> a;
        std::vector<double> B;
        a.push_back(-matr[0][1] / y);
        B.push_back(fa[0] / y);

        for (int i = 1; i < N1; ++i) {
            y = matr[i][i] + matr[i][i - 1] * a[i - 1];
            a.push_back(-matr[i][i + 1] / y);
            B.push_back((fa[i] - matr[i][i - 1] * B[i - 1]) / y);
        }

        res[N1] = (fa[N1] - matr[N1][N1 - 1] * B[N1 - 1]) / (matr[N1][N1] + matr[N1][N1 - 1] * a[N1 - 1]);
        for (int i = N1 - 1; i >= 0; --i) {
            res[i] = a[i] * res[i + 1] + B[i];
        }

        return res;
    }

public:
    Heat_eq(std::string b, std::array<double, 7> a, double l, double t, double dx, double dt) :
            a(a), L(l), T(t), dx(dx), dt(dt) {
        n_x = L / dx;
        n_t = T / dt;

        expl_U.resize(n_x);
        impl_U.resize(n_x);

        _b.SetFunction(b);
    }

    std::vector<double> implicit_method() {
        std::vector<std::vector<double>> grid;
        std::vector<double> rod;

        // firsts values of grid
        double current_x = 0;
        for (size_t i = 0; i < n_x; ++i) {
            rod.push_back(phi_x(current_x));
            current_x += dx;
        }
        grid.push_back(rod);

        // tridiagonal matrix
        std::vector<std::vector<double>> trid_matr;
        init_trid_matr(trid_matr);

        std::vector<double> f_x;
        current_x = dx;
        for (size_t i = 1; i < n_x - 1; ++i) {
            f_x.push_back(1 + dt * b_x(current_x));
            current_x += dx;
        }

        for (size_t i = 0; i < n_t; ++i) {
            std::vector<double> free_vals;
            for (size_t j = 0; j < n_x - 2; ++j) {
                auto tm = rod[j] * f_x[j];
                free_vals.push_back(tm);
            }
            rod = TDMA(trid_matr, free_vals);
            rod.insert(rod.cbegin(), rod[0]);
            rod.push_back(rod.back());
            grid.push_back(rod);
        }
//        std::for_each(grid.begin(), grid.end(), [](std::vector<double>& ivec)
//        {
//            std::for_each(ivec.begin(), ivec.end(), [](double i)
//            {
//                std::cout << "  " << i;
//            });
//            std::cout << std::endl;
//        });
        return impl_U = grid.back();
    }

    std::vector<double> explicit_method() {
       
        std::vector<std::vector<double>> grid;
        std::vector<double> rod;

        double q = dt/(dx*dx);
        
        // firsts values of grid
        double current_x = 0;
        for (size_t i = 0; i < n_x; ++i) {
            rod.push_back(phi_x(current_x));
            current_x += dx;
        }
        grid.push_back(rod);

        for (size_t i = 0; i<n_t; i++)
        {
            std::vector<double> newVals;
            for(size_t j = 0; j<n_x; j++)
            {
                newVals.push_back((1-2*q)*grid[i][j] + q*grid[i][j-1] + q*grid[i][j+1]);
            }
            grid.push_back(newVals);
        }

        return expl_U = grid.back();
    }
};
