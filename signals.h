#ifndef SIGNALS_H
#define SIGNALS_H


/** Функция, задающая гармонический сигнал
 *
 *  а - амплитуда колебаний;
 *
 *  t - промежуток времени;
 *
 *  omega - угловая частота;
 *
 *  phi - фаза(сдвиг сигнала по определенной фазе) 
 **/
double harmonic(double a, double t, double omega, double phi);

/** Функция, задающий однополярный меандр с амплитудой 1
 *
 *  t - промежуток времени;
 *
 *  omega - угловая частота;
 *
 *  phi - фаза(сдвиг сигнала по определенной фазе)
 **/
int meandr(double t, double omega, double phi);

/* Амплитудная модуляция */
double amp_modulate(double t, double omega_meandr, double omega_sin, double phi1, double phi2);

/* Частотная модуляция */
double freq_modulate(double t, double omega1, double omega2, double phi1, double phi2);

/* Фазовая модуляция */
double phase_modulate(double t, double omega1, double omega2, double phi1, double phi2);
#endif

