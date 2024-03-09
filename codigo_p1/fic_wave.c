#include <stdio.h>
#include <stdbool.h>
#include "fic_wave.h"

FILE *abre_wave(const char *ficWave, float *fm, bool *mono) {
    FILE *fpWave;

    if ((fpWave = fopen(ficWave, "r")) == NULL) {
        fprintf(stderr, "Failed to open wave file\n");
        return NULL;
    }

    *fm = 16000.0; // Set the default value for sample rate

    // Seek to the position where the sample rate is stored in the file header
    if (fseek(fpWave, 24, SEEK_SET) < 0) return NULL;

    unsigned int sampleRate;
    if (fread(&sampleRate, sizeof(sampleRate), 1, fpWave) != 1) return NULL;
    *fm = (float)sampleRate;

    // Get mono channel
    unsigned short monoChannel;
    fseek(fpWave, 22, SEEK_SET);
    fread(&monoChannel, sizeof(monoChannel), 1, fpWave);
    *mono = (monoChannel == 1);

    if (!*mono) {
        fprintf(stderr, "Audio is not mono\n");
        fclose(fpWave);
        return NULL;
    }

    // Get bits per sample
    unsigned short bitsPerSample;
    fseek(fpWave, 34, SEEK_SET);
    fread(&bitsPerSample, sizeof(bitsPerSample), 1, fpWave);
    if (bitsPerSample != 16) {
        fprintf(stderr, "Audio does not have 16 bits per sample\n");
        fclose(fpWave);
        return NULL;
    }

    // Seek to the position where the audio data starts
    if (fseek(fpWave, 44, SEEK_SET) < 0) return NULL;

    return fpWave;
}

size_t   lee_wave(void *x, size_t size, size_t nmemb, FILE *fpWave) {
    return fread(x, size, nmemb, fpWave);
}

void    cierra_wave(FILE *fpWave) {
    fclose(fpWave);
}