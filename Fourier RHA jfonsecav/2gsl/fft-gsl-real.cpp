/*
  From https://www.gnu.org/software/gsl/doc/html/fft.html

  Requires gnu gsl installed. 

  Compile as : g++ -std=c++11 fft-gsl-real.cpp -lgsl -lgslcblas

  NOTE: 

  For physical applications it is important to remember that the index
  appearing in the DFT does not correspond directly to a physical
  frequency. If the time-step of the DFT is \Delta then the
  frequency-domain includes both positive and negative frequencies,
  ranging from -1/(2\Delta) through 0 to +1/(2\Delta). The positive
  frequencies are stored from the beginning of the array up to the
  middle, and the negative frequencies are stored backwards from the
  end of the array.
*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>

#define REAL(z,i) ((z)[2*(i)])
#define IMAG(z,i) ((z)[2*(i)+1])

int main (void)
{
  int i, n = 100;
  double data[2*n]; // array to store the time signal, real and imag parts

  // initialize the computing infrastructure
  gsl_fft_complex_wavetable * wavetable;
  gsl_fft_complex_workspace * work;

  // read the time data : Square signal
  // index i represents each time step
  std::ifstream fin("input.txt");
  for (i = 0; i < n; i++)
    {
      fin >> REAL(data,i);
      IMAG(data, i) = 0.0;
    }
  fin.close();
  
  // get memory for the FFT
  work = gsl_fft_complex_workspace_alloc (n);
  wavetable = gsl_fft_complex_wavetable_alloc (n);
  // perform the fft transform (on real data)
  gsl_fft_complex_forward (data, 1, n, wavetable, work);
  // release memory
  gsl_fft_complex_wavetable_free (wavetable);

  
  // print the fftw. Regarding frequencies, check NOTE at the beginning
  for (i = 0; i < n; i++)
    {
      std::cout << REAL(data, i) << "\t" << IMAG(data, i) << "\n";
    }

  gsl_fft_complex_workspace_free (work);
  return 0;
}
