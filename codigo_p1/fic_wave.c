#include <stdio.h>
#include "fic_wave.h"

FILE    *abre_wave(const char *ficWave, float *fm) {
    FILE    *fpWave;

    FILE    *fpWave;
    
    if ((fpWave = fopen(ficWave, "r")) == NULL) return NULL;
    
    int32_t f;
    if (fseek(fpWave, 24, SEEK_SET) < 0) return NULL;
    fread(&f, sizeof(f), 1, fpWave);
    *fm = f;
    
    if (fseek(fpWave, 44, SEEK_SET) < 0) return NULL;
    return fpWave;
}

FILE    *abre_resultados(const char *ficTxt) {
    FILE    *fpTxt;
    if ((fpTxt = fopen(ficTxt, "w")) == NULL) return NULL;
    return fpTxt;
}

size_t   lee_wave(void *x, size_t size, size_t nmemb, FILE *fpWave) {
    return fread(x, size, nmemb, fpWave);
}

void   escribe_resultados(FILE *fpTxt, int trm, float pwr, float am, float zcr) {
    fprintf(fpTxt, "%d\t%f\t%f\t%f\n", trm, pwr, am, zcr);
    return;
}

void    cierra_wave(FILE *fpWave) {
    fclose(fpWave);
}

void    cierra_resultados(FILE *fpTxt) {
    fclose(fpTxt);
}

unsigned int mono_channel(FILE *file_wav){
    unsigned int buff[1];
    fseek(file_wav, 22, SEEK_SET);
    fread(buff, sizeof(unsigned int)/2, 1, file_wav);
    return buff[0];
}

unsigned int bits_per_sample(FILE *file_wav){
   
    unsigned int buff[1];
    fseek(file_wav,34, SEEK_SET);
    fread(buff, sizeof(unsigned int)/2, 1, file_wav);
    return buff[0];
}