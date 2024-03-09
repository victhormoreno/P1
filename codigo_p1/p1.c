#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "pav_analysis.h"
#include "fic_wave.h"

int main(int argc, char *argv[]) {
    float durTrm = 0.010;
    float fm;
    int   N;
    int   trm;
    float *x;
    short *buffer;
    FILE  *fpWave;
    FILE  *fpTxt;

    if (argc != 2 && argc != 3) {
        fprintf(stderr, "Empleo: %s inputfile [outputfile]\n", argv[0]);
        return -1;
    }

    if ((fpWave = abre_wave(argv[1], &fm)) == NULL) {
        fprintf(stderr, "Error al abrir el fichero WAVE de entrada %s (%s)\n", argv[1], strerror(errno));
        return -1;
    }

    if(argv[2] != NULL){
        fpTxt = fopen(argv[2], "w"); // Open the output file for writing
        if (fpTxt == NULL) {
            fprintf(stderr, "Error al abrir el fichero de salida %s (%s)\n", argv[2], strerror(errno));
            return -1;
        }
    }

    unsigned int mono = mono_channel(fpWave);
    unsigned int bps = bits_per_sample(fpWave);
    if(mono != 1){
        printf("Error: no es monocanal\n");
        return -1;
    }
    else if(bps!=16){
        printf("Error: no tiene 16 bits per sample\n");
        return -1;
    }
    else{
        printf("Es mono canal y de 16 bits per sample, mostramos los distintos parámetros calculados:\n");
    }

    N = durTrm * fm;
    if ((buffer = malloc(N * sizeof(*buffer))) == 0 ||
        (x = malloc(N * sizeof(*x))) == 0) {
        fprintf(stderr, "Error al ubicar los vectores (%s)\n", strerror(errno));
        return -1;
    }


    trm = 0;
    while (lee_wave(buffer, sizeof(*buffer), N, fpWave) == N) {
        for (int n = 0; n < N; n++) x[n] = buffer[n] / (float) (1 << 15);

        float pwr = compute_power(x, N);
        float am = compute_am(x, N);
        float zcr = compute_zcr(x, N, fm);

        if (fpTxt != NULL) {
            fprintf(fpTxt, "%d\t%f\t%f\t%f\n", trm, pwr, am, zcr); // Write results to the output file
        } else {
            printf("%d\t%f\t%f\t%f\n", trm, pwr, am, zcr); // Print to console if no output file is provided
        }

        trm += 1;
    }

    cierra_wave(fpWave);
    free(buffer);
    free(x);

    if (fpTxt != NULL) {
    fclose(fpTxt); // Close the output file if opened
    }

    return 0;
}
