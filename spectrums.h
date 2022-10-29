#ifndef SPECTRUMS_H
#define SPECTRUMS_H

#include <fftw3.h>
#include <math.h>
#include "signals.h"

#define N_FOURIER 512
#define F_DISCRETE 2048


/**
 * Функция получения спектра модулированного сигнала;
 *
 *  a - массив выходных амплитуд спектра;
 *
 *  t - массив частот (координата X спектра);
 *
 *  omega1, omega2 - угловые частоты модулирующего и несущего сигналов;
 *
 *  phi1, phi2 - фазы сдвига сигналов;
 *
 *  func - общий указатель на функцию сигнала модуляции;
 *
 *  spec_out - массив выходных комплексных переменных спектра
 **/
void amp_spectrum(double *a, 
        double *t, 
        double omega1, 
        double omega2, 
        double phi1, 
        double phi2, 
        double (*func)(double, double, double, double, double), 
        fftw_complex *spec_out);
#endif
