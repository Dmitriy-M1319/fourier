#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <fftw3.h>
#define _POSIX_C_SOURCE 200809L
#include <signal.h>

#define A 1
#define NU 2
#define N 1024
#define N_FOUR 256


void sigHandler(int sig);
double f_t(double t,  double omega);
double meandr(double t, double omega);
double amp_modulate(double t, double omega_meandr, double omega_sin);
void amp_spectrum(double *a, double *t);
FILE *gp, *out, *spectrum;

int main(void)
{
    struct sigaction action;
    double amps[N_FOUR];
    double amps_t[N_FOUR];

    action.sa_handler = sigHandler;
    sigfillset(&action.sa_mask);
    action.sa_flags = SA_RESTART;

    gp = popen("gnuplot - " , "w");
    out = fopen("plot1.dat", "w");
    spectrum = fopen("spectrum.dat", "w");
    
    double t_step = 2.0 / N;
    double t = 0;
    for(int i = 0; i < N; i++)
    {
       double y = amp_modulate(t, 2 * M_PI * NU, 2 * M_PI * NU * 8); 
       fprintf(out,"%lf %lf \n" , t, y);
       t += t_step;
    }

    fflush(out);
    fprintf(gp, "plot './plot1.dat' with lines \n");
    fflush(gp);

    //amp_spectrum(amps, amps_t);
#ifdef SPECTRUM
    for(int i = 0; i < 50; i++)
    {

        fprintf(spectrum,"%lf %lf \n" , amps_t[i], 0.0);
        fprintf(spectrum,"%lf %lf \n" , amps_t[i], amps[i]);
        fprintf(spectrum, "\n\n");
    }
    fflush(spectrum);
    fprintf(gp, "plot './spectrum.dat' with lines \n");
    fflush(gp);
#endif

    for(;;){}

    fclose(gp);
    fclose(out);
    return 0;

}

void sigHandler(int sig)
{
    if(sig == SIGTERM || sig == SIGHUP || sig == SIGINT)
    {
        fclose(out);
        fclose(gp);
        exit(0);
    }
}

double f_t(double t, double omega)
{
    return A * sin(omega * t);
}

double meandr(double t, double omega)
{
    double eps = 1E-6;
    double a = sin(omega * t);
    if(a < eps)
        return 0.0;
    else 
        return 1.0;
}

double amp_modulate(double t, double omega_meandr, double omega_sin)
{ 
    return meandr(t, omega_meandr) * f_t(t, omega_sin);
}


void amp_spectrum(double *a, double *t)
{
    int f_d = 1024;
    fftw_complex *in = fftw_alloc_complex(N_FOUR);
    fftw_complex *out = fftw_alloc_complex(N_FOUR);

    fftw_plan plan = fftw_plan_dft_1d(N_FOUR, in, out, FFTW_FORWARD, FFTW_ESTIMATE);


    double t_x = 0; 
    printf("input values:\n");
    for(int i = 0; i < N_FOUR; i++)
    {
        t[i] = i * ((double)f_d / N_FOUR);
        in[i][0] = amp_modulate(t_x, 2 * M_PI * NU, 2 * M_PI * NU * 4);
        printf("X: %lf - Y: %lf\n", t_x, in[i][0]);
        t_x += 1.0 / f_d;
    }

    fftw_execute(plan);

    printf("\n\n");
    for(int i = 0; i < N_FOUR; i++)
    {
        double amp = sqrt(pow(out[i][0], 2) + pow(out[i][1], 2));
        printf("Re %lf -- Im %lf: A = %lf\n", out[i][0], out[i][1], amp);
        a[i] = amp;
    }

    fftw_destroy_plan(plan);
    fftw_free(in);
    fftw_free(out);
}
