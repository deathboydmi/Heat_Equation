#include <iostream>
#include <cmath>
#include <iomanip>
#include "./tofunction/tofunction.h"
#define PI 3.14159265358979323846

double b_x(ToFunction _b, double x) {
    return _b.Calculate(x);
}

double phi_x(double *a, double L, double x)
{
    auto phi = a[0];
    auto eto = PI / L;
    for (unsigned i = 1; i < 7; ++i)
    {
        phi += a[i] * cos(i * eto * x);
    }
    return phi;
}

int main(int argc, char *argv[])
{
    //L, T, dt, dx, b(x), a0 -- a6
    double L;
    double T;
    double dt;
    double dx;
    std::string b;

    double arr[7] = {0.25, 1, 0.5, 0.3, 0.78, 0.01, 0.02};

    if (argc == 13)
    {
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
    }
    else
    {
        L = 1;
        T = 1;
        dx = 0.01;
        dt = 0.001;
        b = "1";
    }

    ToFunction b_func(b);

    double q = dt / (dx * dx);
    int n_x = L / dx;
    int n_t = T / dt;

    double **grid = new double *[n_t];
    for (int i = 0; i < n_t; i++)
        grid[i] = new double[n_x];

    double current_x = 0;
    for (int j = 0; j < n_x; j++)
    {
        grid[0][j] = phi_x(arr, L, current_x);
        current_x += dx;
    }

    double f_x[n_x];
    current_x = 0;
    for (size_t i = 0; i < n_x; ++i)
    {
        f_x[i] = -2 * q + 1 + dt * b_x(b_func, current_x);
        current_x += dx;
    }
    
    for (size_t i = 0; i < n_t-1; i++)
    {
        for (size_t j = 1; j < n_x - 1; j++)
        {
            double value = q * (grid[i][j - 1] + grid[i][j + 1]) + grid[i][j] * f_x[j];
            grid[i+1][j] = value;
        }
        grid[i][0] = grid[i][1];
        grid[i][n_x - 1] = grid[i][n_x];
    }

    for (size_t i = 0; i < n_t; i++)
    {
        for (size_t j = 0; j < n_x; j++)
        {
            std::cout << std::setprecision(2) << grid[i][j] << "  ";
        }
        std::cout << std::endl;
    }

    return 0;
}