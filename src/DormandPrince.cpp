#include "DormandPrince.h"

DormandPrince::DormandPrince(double GM, double J2, double J4, double R)
    : GM(GM), J2(J2), J4(J4), R(R) {
}

State DormandPrince::f(double t, const State& y) const {
    double x = y[0], yCoord = y[1], z = y[2];
    double Ux = y[3], Uy = y[4], Uz = y[5];

    double r = std::sqrt(x * x + yCoord * yCoord + z * z);

    double ax_c = -GM * x / (r * r * r);
    double ay_c = -GM * yCoord / (r * r * r);
    double az_c = -GM * z / (r * r * r);

    double factor_J2 = (3.0 / 2.0) * J2 * GM * R * R / (r * r * r * r * r);
    double z2_r2 = (z * z) / (r * r);

    double ax_J2 = factor_J2 * x * (1 - 5 * z2_r2);
    double ay_J2 = factor_J2 * yCoord * (1 - 5 * z2_r2);
    double az_J2 = factor_J2 * z * (3 - 5 * z2_r2);

    double factor_J4 = -(5.0 / 8.0) * J4 * GM * R * R * R * R / (r * r * r * r * r * r * r);
    double z4_r4 = (z * z) * (z * z) / (r * r * r * r);

    double ax_J4 = factor_J4 * x * (3 - 42 * z2_r2 + 63 * z4_r4);
    double ay_J4 = factor_J4 * yCoord * (3 - 42 * z2_r2 + 63 * z4_r4);
    double az_J4 = factor_J4 * z * (15 - 70 * z2_r2 + 63 * z4_r4);

    double ax = ax_c + ax_J2 + ax_J4;
    double ay = ay_c + ay_J2 + ay_J4;
    double az = az_c + az_J2 + az_J4;

    return { Ux, Uy, Uz, ax, ay, az };
}

State DormandPrince::solve(double t, const State& y, double& h, double tol) {
    std::array<State, 7> k;
    State y4, y5, error;

    for (size_t i = 0; i < 7; ++i) {
        State yi = y;
        for (size_t j = 0; j < i; ++j) {
            for (size_t d = 0; d < 6; ++d) {
                yi[d] += h * a[i][j] * k[j][d];
            }
        }
        k[i] = f(t + c[i] * h, yi);
    }

    for (size_t d = 0; d < 6; ++d) {
        y4[d] = y[d];
        y5[d] = y[d];
        for (size_t i = 0; i < 7; ++i) {
            y4[d] += h * b4[i] * k[i][d];
            y5[d] += h * b5[i] * k[i][d];
        }
    }

    double errorNorm = 0.0;
    for (size_t d = 0; d < 6; ++d) {
        error[d] = y5[d] - y4[d];
        errorNorm += error[d] * error[d];
    }
    errorNorm = std::sqrt(errorNorm);

    double safetyFactor = 0.9;
    if (errorNorm > tol) {
        h *= safetyFactor * std::pow(tol / errorNorm, 0.2);
        return solve(t, y, h, tol);
    }
    else if (errorNorm < tol / 10) {
        h *= safetyFactor * std::pow(tol / errorNorm, 0.25);
    }

    return y5;
}
