#ifndef PAV_ANALYSIS_H
#define PAV_ANALYSIS_H

float compute_power(const float *x, unsigned int N);
float compute_am(const float *x, unsigned int N);
float compute_zcr(const float *x, unsigned int N, float fm);
void finestra_hamming(float *w, unsigned int N);

#endif	/* PAV_ANALYSIS_H	*/
