#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include "pav_analysis.h"
#include "fic_wave.h"

int main(int argc, char *argv[]) {
    float durTrm = 0.010;
    float fm;
    bool  mono, txt = false;
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

    if ((fpWave = abre_wave(argv[1], &fm, &mono)) == NULL) {
        fprintf(stderr, "Error al abrir el fichero WAVE de entrada %s (%s)\n", argv[1], strerror(errno));
        return -1;
    }

    if(argv[2] != NULL){
        fpTxt = fopen(argv[2], "w"); 
        if (fpTxt == NULL) {
            fprintf(stderr, "Error al abrir el fichero de salida %s (%s)\n", argv[2], strerror(errno));
            return -1;
        }
        txt = true;
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

        if (txt) fprintf(fpTxt, "%d\t%f\t%f\t%f\n", trm, pwr, am, zcr); // Write results to the output file
        else     printf("%d\t%f\t%f\t%f\n", trm, pwr, am, zcr); // Print to console if no output file is provided
        

        trm += 1;
    }

    cierra_wave(fpWave);
    if (txt) fclose(fpTxt); 
    
    free(buffer);
    free(x);


    return 0;
}
