#include <math.h>

double harmonic(double a, double t, double omega, double phi)
{
    return a * sin(omega * t + phi);
}

int meandr(double t, double omega, double phi)
{
    double eps = 1E-6;
    double a = harmonic(1, t, omega, phi);
    if(a < eps)
        return 0;
    else 
        return 1;
}

double amp_modulate(double t, double omega_meandr, double omega_sin, double phi1, double phi2)
{ 
    return meandr(t, omega_meandr, phi1) * harmonic(1, t, omega_sin, phi2);
}

double freq_modulate(double t, double omega1, double omega2, double phi1, double phi2)
{
    return (meandr(t, omega1, phi1) * harmonic(1, t, omega2, phi1))+
                (meandr(t, omega1, phi2) * harmonic(1, t, omega2 * 2, phi1));
}

double phase_modulate(double t, double omega1, double omega2, double phi1, double phi2)
{
    return (meandr(t, omega1, phi1) * harmonic(1, t, omega2, phi1)) +
                (meandr(t, omega1, phi2) * harmonic(1, t, omega2, phi2));
}
