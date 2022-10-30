#include "spectrums.h"
#include <math.h>
#include <fftw3.h>

void find_max_3(int *indexes, double *a)
{
    double new_a[N_FOURIER];
    for(int i = 0; i < N_FOURIER; i++)
    {
        new_a[i] = a[i];
    }

    for (int i = 0; i < N_FOURIER - 1; i++)
    {
        for (int j = 0; j < N_FOURIER - i - 1; j++)
        {
            if (new_a[j] < new_a[j + 1])
            {
                int tmp = new_a[j];
                new_a[j] = new_a[j + 1];
                new_a[j + 1] = tmp;
            }
        }
    }

    int k = 0, prev = 0;
    for(int i = 0; i < 500; i++)
    {
        if(k == 3)
            break;

        for(int j = 0; j < N_FOURIER; j++)
        {
            if((int)a[j] == (int)new_a[i] && (int)new_a[i] != prev)
            {
                indexes[k] = j;
                k++;
                prev = new_a[i];
                break;
            }
        }
    }
 
}

void filter_signal(fftw_complex *amps, int *indexes)
{
	for(int i = 0; i < N_FOURIER; i++)
	{
		int is_max = 0;
		for(int j = 0; j < 3; j++)
		{
			if(indexes[j] == i)
			{
				is_max = 1;
				break;
			}
		}

		if(!is_max)
		{
			amps[i][0] = 0.0;
			amps[i][1] = 0.0;
		}
	}
}

void synth_signal(fftw_complex *amps, double *y_signal, double *x_signal)
{
    double out[N_FOURIER];
    fftw_plan plan = fftw_plan_dft_c2r_1d(N_FOURIER, amps, out, FFTW_ESTIMATE);

    fftw_execute(plan);

    for(int i = 0; i < N_FOURIER; i++)
    {
        out[i] /= N_FOURIER;
    }

    double t_x = 0;
    for(int i = 0; i < N_FOURIER; i++)
    {
        y_signal[i] = out[i];
        x_signal[i] = t_x;
        t_x += 1.0 / F_DISCRETE; 
    }

    fftw_destroy_plan(plan);
}
