#include <stdio.h>
#include <stdlib.h>
#include "signals.h"
#include <math.h>

#define NU 2
#define N 1024

int main(void)
{
    FILE *plot1, *plot2, *plot3;

    plot1 = fopen("plots/plot1.dat", "w");
    plot2 = fopen("plots/plot2.dat", "w");
    plot3 = fopen("plots/plot3.dat", "w");

    double t_step = 2.0 / N;
    double t = 0;
    for(int i = 0; i < N; i++)
    {
       double y = amp_modulate(t, 2 * M_PI * NU, 2 * M_PI * NU * 8, 0, 0); 
       fprintf(plot1,"%lf %lf \n" , t, y);

       y = freq_modulate(t, 2.0 * M_PI * NU * 4, 2 * M_PI * NU * 8, 0, M_PI);
       fprintf(plot2,"%lf %lf \n" , t, y);

       y = phase_modulate(t, 2.0 * M_PI, 2 * M_PI * NU * 2, 0, M_PI);
       fprintf(plot3,"%lf %lf \n" , t, y);

       t += t_step;
    }

    fflush(plot1);
    fflush(plot2);
    fflush(plot3);

    fclose(plot1);
    fclose(plot2);
    fclose(plot3);

    return 0;
}
