/*
  - From https://github.com/undees/fftw-example
  - Compile as: g++ fftw-example.cpp -lfftw3
*/

#include <iostream>
#include <fstream>
#include <cstdio>
#include <cmath>
#include <fftw3.h>

#define NUM_POINTS 100

#define REAL 0
#define IMAG 1

void acquire_from_somewhere(fftw_complex* signal) ;
void do_something_with(fftw_complex* result);

int main(void)
{
  fftw_complex signal[NUM_POINTS];
  fftw_complex result[NUM_POINTS];
  
  fftw_plan plan = fftw_plan_dft_1d(NUM_POINTS, signal, result, FFTW_FORWARD, FFTW_ESTIMATE);
  acquire_from_somewhere(signal);
  fftw_execute(plan);
  do_something_with(result);
  fftw_destroy_plan(plan);
  
  return 0;
}

void acquire_from_somewhere(fftw_complex* signal) {
  std::ifstream fin("i-500.txt");
  for (int i = 0; i < NUM_POINTS; ++i) {
    fin >> signal[i][REAL];
    signal[i][IMAG] = 0.0;
  }
  fin.close();
}

void do_something_with(fftw_complex* result) {
  std::ofstream fout("o-500.txt");
  for (int i = 0; i < NUM_POINTS; ++i) {
    //double mag = sqrt(result[i][REAL] * result[i][REAL] +
    //                  result[i][IMAG] * result[i][IMAG]);
    
    fout << result[i][REAL] << "\t" << result[i][IMAG] << "\n";
  }
  fout.close();
}


