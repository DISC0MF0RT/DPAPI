#ifndef DORMANDPRINCE_H
#define DORMANDPRINCE_H

#include <array>
#include <vector>
#include <cmath>
#include <iostream>

using State = std::array<double, 6>;

class DormandPrince {
public:
    DormandPrince(double GM, double J2, double J4, double R);

    State solve(double t, const State& y, double& h, double tol);

private:
    double GM;
    double J2;
    double J4;
    double R;

    State f(double t, const State& y) const;

    static constexpr std::array<double, 7> c = { 0.0, 1.0 / 5.0, 3.0 / 10.0, 4.0 / 5.0, 8.0 / 9.0, 1.0, 1.0 };
    static constexpr std::array<std::array<double, 7>, 7> a = { {
        {0.0}, {1.0 / 5.0, 0.0}, {3.0 / 40.0, 9.0 / 40.0, 0.0},
        {44.0 / 45.0, -56.0 / 15.0, 32.0 / 9.0, 0.0},
        {19372.0 / 6561.0, -25360.0 / 2187.0, 64448.0 / 6561.0, -212.0 / 729.0, 0.0},
        {9017.0 / 3168.0, -355.0 / 33.0, 46732.0 / 5247.0, 49.0 / 176.0, -5103.0 / 18656.0, 0.0},
        {35.0 / 384.0, 0.0, 500.0 / 1113.0, 125.0 / 192.0, -2187.0 / 6784.0, 11.0 / 84.0, 0.0}
    } };
    static constexpr std::array<double, 7> b4 = { 35.0 / 384.0, 0.0, 500.0 / 1113.0, 125.0 / 192.0, -2187.0 / 6784.0, 11.0 / 84.0, 0.0 };
    static constexpr std::array<double, 7> b5 = { 5179.0 / 57600.0, 0.0, 7571.0 / 16695.0, 393.0 / 640.0, -92097.0 / 339200.0, 187.0 / 2100.0, 1.0 / 40.0 };
};

#endif
