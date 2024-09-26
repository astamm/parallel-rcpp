//---------------------------------
#include <Rcpp.h>

// // [[Rcpp::plugins(openmp)]] // Uncomment on Windows and Linux

// [[Rcpp::export]]
bool all_finite_cpp(Rcpp::NumericVector x) // <1>
{
  unsigned int nbInputs = x.size();

  double out = 0;
  for (unsigned int i = 0;i < nbInputs;++i)
    out += x[i];

  return R_FINITE(out); // <2>
}
