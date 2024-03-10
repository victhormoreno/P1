#include <math.h>
#include "pav_analysis.h"

float compute_power(const float *x, unsigned int N) {
    float P = 1e-12, sum = 0.0;
    float w[N];

    finestra_hamming(w, N);

    for (int n = 0; n < N; ++n) {
        P += x[n] * w[n] * x[n] * w[n];
        sum += w[n] * w[n];
    }

    return log10(P/sum) * 10;
}

void finestra_hamming(float *w, unsigned int N) {
    for (int n = 0; n < N; ++n) {
        w[n] = 0.53836 - 0.46164 * cos(2.0 * M_PI * n / (N - 1));
    }
}

float compute_am(const float *x, unsigned int N) {
    float A = 0.0;
    for (int n = 0; n < N; n++) A += fabs(x[n]);
    return A/N;
}

float compute_zcr(const float *x, unsigned int N, float fm) {
    float ZCR = 0.0;
    for(int n = 1; n < N+1; n++) ZCR += (x[n] * x[n-1] < 0);
    return ZCR * fm / (2 * N-2);
}
