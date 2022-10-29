#include <fftw3.h>
#include <stdio.h>
#include <stdlib.h>
#include "spectrums.h"
#include "signals.h"

#define NU 16

int main(void)
{
    FILE *plot1, *plot2, *plot3, *plot4;

    plot1 = fopen("plots/amp_spectrum.dat", "w");
    plot2 = fopen("plots/freq_spectrum.dat", "w");
    plot3 = fopen("plots/phase_spectrum.dat", "w");
    plot4 =  fopen("plots/synth.dat", "w");

    double amps[N_FOURIER]; 
    fftw_complex *out = fftw_alloc_complex(N_FOURIER);
    double freq[N_FOURIER]; 
    double phase[N_FOURIER]; 
    double nu[N_FOURIER];

    amp_spectrum(freq, nu, 2.0 * M_PI * NU * 2, 2.0 * M_PI * NU * 8, 0, M_PI, freq_modulate, out);
    amp_spectrum(phase, nu, 2.0 * M_PI * NU, 2.0 * M_PI * NU * 4, 0, M_PI, phase_modulate, out);
    amp_spectrum(amps, nu, 2.0 * M_PI * NU, 2.0 * M_PI * NU * 8, 0, 0, amp_modulate, out);

    
    for(int i = 0; i < N_FOURIER / 3; i++)
    {
        fprintf(plot1,"%lf %lf \n" , nu[i], amps[i]);
        fprintf(plot2,"%lf %lf \n" , nu[i], freq[i]);
        fprintf(plot3,"%lf %lf \n" , nu[i], phase[i]);
    }

    fflush(plot1);
    fflush(plot2);
    fflush(plot3);

    fclose(plot1);
    fclose(plot2);
    fclose(plot3);
    
    fftw_free(out);

    return 0;
}
