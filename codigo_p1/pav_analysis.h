#ifndef PAV_ANALYSIS_H
#define PAV_ANALYSIS_H

/**
 * @brief Calcula la potencia de una señal.
 *
 * @param x Puntero a la señal de entrada.
 * @param N Número de muestras en la señal.
 * @return La potencia de la señal en decibelios (dB).
 */
float compute_power(const float *x, unsigned int N);

/**
 * @brief Calcula la amplitud media de una señal.
 *
 * @param x Puntero a la señal de entrada.
 * @param N Número de muestras en la señal.
 * @return La amplitud media de la señal.
 */
float compute_am(const float *x, unsigned int N);

/**
 * @brief Calcula la tasa de cruce por cero (Zero Crossing Rate) de una señal.
 *
 * @param x Puntero a la señal de entrada.
 * @param N Número de muestras en la señal.
 * @param fm Frecuencia de muestreo de la señal.
 * @return La tasa de cruce por cero de la señal.
 */
float compute_zcr(const float *x, unsigned int N, float fm);

/**
 * @brief Crea la ventana de Hamming.
 *
 * @param w Puntero a la salida de la ventana de Hamming.
 * @param N Número de muestras en la señal.
 */
void finestra_hamming(float *w, unsigned int N);

#endif /* PAV_ANALYSIS_H */
