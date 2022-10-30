#include <stdio.h>
#include <stdlib.h>
#include "spectrums.h"
#include "signals.h"
#include "synth.h"

#define NU 16
//#define DEBUG 1

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
    amp_spectrum(amps, nu, 2.0 * M_PI * NU * 2, 2.0 * M_PI * NU * 16, 0, 0, amp_modulate, out);

    /* На этом этапе получили в out выход амплитудного спектра */
    int indexes[3] = {0};
    find_max_3(indexes, amps);

#ifdef DEBUG
    puts("Indexes:");
    for(int i = 0; i < 3; i++)
    {
        printf("%d\n", indexes[i]);
    }
#endif

    filter_signal(out, indexes);

#ifdef DEBUG
    puts("");
    puts("Filter spectrum:");
    for(int i = 0; i < N_FOURIER; i++)
    {
        printf("Re %lf -- Im %lf\n", out[i][0], out[i][1]);
    }
#endif

    double synth_x[N_FOURIER];
    double synth_y[N_FOURIER];

    synth_signal(out, synth_y, synth_x);

 #ifdef DEBUG
    puts("");
    puts("Synth signal:");
    for(int i = 0; i < N_FOURIER; i++)
    {
        printf("x = %lf: y = %lf\n", synth_x[i], synth_y[i]);
    }
#endif
   
    for(int i = 0; i < N_FOURIER / 3; i++)
    {
        fprintf(plot1,"%lf %lf \n" , nu[i], amps[i]);
        fprintf(plot2,"%lf %lf \n" , nu[i], freq[i]);
        fprintf(plot3,"%lf %lf \n" , nu[i], phase[i]);
        fprintf(plot4,"%lf %lf \n" , synth_x[i], synth_y[i]);
    }

    fflush(plot1);
    fflush(plot2);
    fflush(plot3);
    fflush(plot4);

    fclose(plot1);
    fclose(plot2);
    fclose(plot3);
    fclose(plot4);
    
    fftw_free(out);

    return 0;
}
