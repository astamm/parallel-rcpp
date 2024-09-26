//---------------------------------
#include <Rcpp.h>

// // [[Rcpp::plugins(openmp)]] // Uncomment on Windows and Linux

// [[Rcpp::export]]
bool all_finite_omp(Rcpp::NumericVector x, unsigned int ncores) // <1>
{
  unsigned int nbInputs = x.size();
  double out = 0;

#ifdef _OPENMP
#pragma omp parallel for reduction(+:out) num_threads(ncores) // <2>
#endif
  for (unsigned int i = 0;i < nbInputs;++i)
    out += x[i];

  return R_FINITE(out);
}
