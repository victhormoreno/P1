/**
 * @file fic_wave.h
 *
 * @brief Funciones para el manejo de archivos WAVE y txt.
 *
 * Este archivo contiene las declaraciones de funciones para abrir, leer y cerrar archivos
 * WAVE, así como funciones relacionadas con la manipulación de archivos de resultados.
 *
 * @authors Víctor Moreno y Arnau Bergas
 *
 * @version 1.0
 */

#ifndef FIC_WAVE_H
#define FIC_WAVE_H


/**
 * @brief Abre un archivo de formato WAVE para lectura y recupera la frecuencia de muestreo.
 *
 * @param ficWave Nombre del archivo WAVE.
 * @param fm Puntero a la variable donde se almacenará la frecuencia de muestreo.
 * @return Puntero al archivo abierto o NULL si hay un error.
 */
FILE   *abre_wave(const char *ficWave, float *fm, bool *mono);

/**
 * @brief Lee datos desde un archivo WAVE abierto.
 *
 * @param x Puntero al buffer donde se almacenarán los datos leídos.
 * @param size Tamaño en bytes de cada elemento a leer.
 * @param nmemb Número de elementos que se intentarán leer.
 * @param fpWave Puntero al archivo WAVE abierto.
 * @return Número de elementos leídos correctamente.
 */
size_t lee_wave(void *x, size_t size, size_t nmemb, FILE *fpWave);

/**
 * @brief Cierra un archivo WAVE abierto.
 *
 * @param fpWave Puntero al archivo WAVE abierto.
 */
void   cierra_wave(FILE *fpWave);

#endif	/* FIC_WAV_H	*/
