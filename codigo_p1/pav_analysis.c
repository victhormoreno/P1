#include <math.h>
#include "pav_analysis.h"

float compute_power(const float *x, unsigned int N) {
    float P = 1e-6;
    for (int n = 0; n < N; n++) P += x[n] * x[n];
    return log10(P/N) * 10;
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
