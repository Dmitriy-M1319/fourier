#include "spectrums.h"

void amp_spectrum(double *a, 
        double *t, 
        double omega1, 
        double omega2, 
        double phi1, 
        double phi2,
        double (*func)(double, double, double, double, double),
        fftw_complex *spec_out)
{
    fftw_complex *in = fftw_alloc_complex(N_FOURIER);
    fftw_complex *out = fftw_alloc_complex(N_FOURIER);

    fftw_plan plan = fftw_plan_dft_1d(N_FOURIER, in, out, FFTW_FORWARD, FFTW_ESTIMATE);

    double t_x = 0;
    printf("input values:\n");
    for(int i = 0; i < N_FOURIER; i++)
    {
        t[i] = i * ((double)F_DISCRETE / N_FOURIER);
        in[i][0] = func(t_x, omega1, omega2, phi1, phi2);
#ifdef DEBUG
        printf("X: %lf - Y: %lf\n", t_x, in[i][0]);
#endif
        t_x += 1.0 / F_DISCRETE;
    }

    fftw_execute(plan);

    printf("\n\n");
    for(int i = 0; i < N_FOURIER; i++)
    {
        double amp = sqrt(pow(out[i][0], 2) + pow(out[i][1], 2));
#ifdef DEBUG
        printf("Re %lf -- Im %lf: A = %lf\n", out[i][0], out[i][1], amp);
#endif
        a[i] = amp;
        spec_out[i][0] = out[i][0];
        spec_out[i][1] = out[i][1];
    }

    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);
}

