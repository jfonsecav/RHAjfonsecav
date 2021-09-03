/*
  Based on : 
  - https://eigen.tuxfamily.org/dox/unsupported/group__FFT__Module.html
  - https://github.com/cryos/eigen/blob/master/unsupported/test/FFTW.cpp

  Compile as : g++ -I /usr/include/eigen3/ fft-eigen.cpp

 */

#include <iostream>
#include <fstream>
#include <unsupported/Eigen/FFT>

int main(void)
{
  const int N = 100;
  Eigen::VectorXd in(N);
  Eigen::VectorXcd out;
  Eigen::FFT<double> fft;

  // read the time data : Square signal
  // index i represents each time step
  std::ifstream fin("input.txt");
  for (int i = 0; i < N; i++)
    {
      fin >> in[i];
    }
  fin.close();

  out = fft.fwd(in);
  std::cout << out; 
  
  return 0;
}
