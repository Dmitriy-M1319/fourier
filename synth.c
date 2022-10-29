#include "spectrums.h"
#include <math.h>
#include <fftw3.h>

void find_max_3(int *indexes, double *a)
{
	double max = 0;
	int index = 0;
	for(int i = 0; i < 3; i++)
	{
		for(int k = 0; k < N_FOURIER; k++)
		{
			if(a[k] >= max)
			{
				int in_indexes_array = 0;
				for(int j = 0; j < 3; j++)
				{
					if(indexes[j] == k)
					{
						in_indexes_array = 1;
						break;
					}
				}
				if(!in_indexes_array)
				{
					max = a[k];
					index = k;
				}
			}
		}
		indexes[i] = index;
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
