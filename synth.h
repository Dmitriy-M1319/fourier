#ifndef SYNTH_H
#define SYNTH_H

#include <fftw3.h>

/**
 * Функция, которая ищет три максимальные амплитуды в спектре
 *  indexes - выходной массив на 3 элемента, который содержит индексы 3 максимальных амплитуд в a;
 *  a - массив амплитуд спектра
 **/
void find_max_3(int *indexes, double *a);

/**
 * Функция, фильтрующая массив выхода БПФ по найденным индексам
 **/
void filter_signal(fftw_complex *amps, int *indexes);

/**
 * Функция, которая синтезирует сигнал из отфильтрованного спектра
 **/
void synth_signal(fftw_complex *amps, double *y_signal, double *x_signal);


/**
 * Функция, фильтрующая сигнал через экспоненциальное бегущее среднее
 *  signal_y - y-значения сигнала с шумом;
 *  new_signal - выходноу массив отфильтрованного сигнала
 **/
void filter_noise(double *signal_y, double *new_signal);

#endif
