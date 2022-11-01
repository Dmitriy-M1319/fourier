/** 
 * Программа, выполняющая синтез амплитудных спектров для сигналов с
 * амплитудной, частотной и фазовой модуляцией, а также
 * фильтрацию спектра амплитудной модуляции и синтез сигнала из него.
 * Все данные предназначены для отрисовки в программе gnuplot
 **/

#include <stdio.h>
#include <stdlib.h>
#include "spectrums.h"
#include "signals.h"
#include "synth.h"

#define NU 16
//#define DEBUG 1

int main(void)
{
    /* Файловые дескрипторы данных в формате .dat для спектров и синтезированных сигналов */
    FILE *plot1, *plot2, *plot3, *plot4, *plot5;

    plot1 = fopen("plots/amp_spectrum.dat", "w");
    plot2 = fopen("plots/freq_spectrum.dat", "w");
    plot3 = fopen("plots/phase_spectrum.dat", "w");
    plot4 = fopen("plots/synth.dat", "w");
    plot5 = fopen("plots/synth_without_noise.dat", "w");

    /* Массив амплитуд спектра амплитудной модуляции */
    double amps[N_FOURIER]; 

    /* Массив комплексных переменных спектра (для синтеза сигнала путем ОБПФ) */
    fftw_complex *out = fftw_alloc_complex(N_FOURIER);

    /* Массив амплитуд спектра амплитудной модуляции */
    double freq[N_FOURIER]; 

    /* Массив амплитуд спектра амплитудной модуляции */
    double phase[N_FOURIER]; 

    /* Массив частот спектра */
    double nu[N_FOURIER];

    /* Создаем спектры частотной, фазовой и амплитудной модуляций */
    amp_spectrum(freq, nu, 2.0 * M_PI * NU, 2.0 * M_PI * NU * 4, 0, M_PI, freq_modulate, out);
    amp_spectrum(phase, nu, 2.0 * M_PI * NU, 2.0 * M_PI * NU * 4, 0, M_PI, phase_modulate, out);
    amp_spectrum(amps, nu, 2.0 * M_PI * NU * 2, 2.0 * M_PI * NU * 16, 0, 0, amp_modulate, out);

    /* На этом этапе получили в out выход амплитудного спектра */
    /* Находим максимальные 3 амплитуды */
    int indexes[3] = {0};
    find_max_3(indexes, amps);




#ifdef DEBUG
    puts("Indexes:");
    for(int i = 0; i < 3; i++)
    {
        printf("%d\n", indexes[i]);
    }
#endif




    /* Теперь по ним фильтруем сам спектр */
    filter_signal(out, indexes);




#ifdef DEBUG
    puts("");
    puts("Filter spectrum:");
    for(int i = 0; i < N_FOURIER; i++)
    {
        printf("Re %lf -- Im %lf\n", out[i][0], out[i][1]);
    }
#endif




    /* Синтезируем сигнал из спектра */
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



    /* Проводим фильтрацию сигнала */
    double new_signal[N_FOURIER];
    filter_noise(synth_y, new_signal);



#ifdef DEBUG
    puts("Indexes:");
    for(int i = 0; i < N_FOURIER; i++)
    {
        printf("%lf\n", new_signal[i]);
    }
#endif
  
    /* Теперь просто заполняем файлы всеми необходимыми данными и закрываем потоки */
    for(int i = 0; i < N_FOURIER / 3; i++)
    {
        fprintf(plot1,"%lf %lf \n" , nu[i], amps[i]);
        fprintf(plot2,"%lf %lf \n" , nu[i], freq[i]);
        fprintf(plot3,"%lf %lf \n" , nu[i], phase[i]);
    }

    for(int i = 0; i < N_FOURIER; i++)
    {
        fprintf(plot4,"%lf %lf \n" , synth_x[i], synth_y[i]);
        fprintf(plot5,"%lf %lf \n" , synth_x[i], new_signal[i]);
    }

    fflush(plot1);
    fflush(plot2);
    fflush(plot3);
    fflush(plot4);
    fflush(plot5);

    fclose(plot1);
    fclose(plot2);
    fclose(plot3);
    fclose(plot4);
    fclose(plot5);
    
    fftw_free(out);

    return 0;
}
